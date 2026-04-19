Below is the deep version: first how rendering really works, then how HTML/CSS interact with JS, then a realistic plan for a **minimal browser in C#** without using an existing browser component.

---

# 1. Rendering, deeply

A browser does not “draw HTML.” It transforms source text into several internal representations, then computes geometry, then issues drawing commands, then composites layers to the screen. The classic high-level path is:

**bytes → tokens → DOM/CSSOM → style → render/layout tree → layout → paint → compositing → pixels**. ([developer.mozilla.org][1])

## 1.1 From network bytes to a document

The browser first receives bytes from the network, determines the character encoding, and feeds the stream into the HTML parser. The HTML parsing rules are defined as a state machine with well-defined error recovery, which is why browsers can render lots of malformed HTML consistently. ([html.spec.whatwg.org][2])

Important consequence: parsing is **incremental**. The browser does not have to wait for the whole file before starting work. It can begin parsing and even rendering while bytes are still arriving. This is a major reason pages can start appearing before they are fully loaded. The HTML Standard also defines script-processing hooks that interact with parsing. ([html.spec.whatwg.org][3])

## 1.2 DOM construction

The parser turns input into tokens like start tags, end tags, text, and comments, then builds the **DOM tree**. The DOM is a semantic tree of document nodes, not a paint tree. Hidden nodes, script tags, and metadata all live there, even if they never become visible content. ([html.spec.whatwg.org][2])

Example:

```html
<div class="card">
  <h1>Hello</h1>
  <p>World</p>
</div>
```

Becomes conceptually:

```text
Document
└── html
    └── body
        └── div.card
            ├── h1
            │   └── "Hello"
            └── p
                └── "World"
```

## 1.3 CSS parsing and CSSOM

CSS is parsed separately into rules and selectors, often described at a high level as the **CSSOM**. CSS is especially important because style computation cannot finish until the relevant CSS has been loaded and parsed. MDN describes the critical rendering path as depending on both the DOM and the CSSOM before render tree construction and layout can proceed. ([developer.mozilla.org][1])

Example rule set:

```css
.card { width: 300px; padding: 16px; }
h1 { font-size: 24px; }
p { color: gray; }
```

Internally, the browser stores selectors plus declarations:

```text
Rule 1: selector ".card"
  width = 300px
  padding = 16px

Rule 2: selector "h1"
  font-size = 24px
```

## 1.4 Style resolution

Now the browser answers a much harder question:

> For each DOM node, what is the final computed value of every relevant CSS property?

That means:

* matching selectors to elements
* resolving specificity and cascade
* inheriting inherited properties
* applying default user-agent styles
* computing values such as `em`, `%`, `inherit`, `auto`, etc.

This stage is often called **style calculation** or **style resolution**. Chromium’s rendering architecture explicitly separates phases such as style, layout, paint, and compositing. ([Chrome for Developers][4])

For a `<p>` inside a gray container, the browser might compute:

```text
display: block
font-size: 16px
color: rgb(128,128,128)
margin-top: 16px
margin-bottom: 16px
```

This is the first place where CSS becomes concrete enough to drive layout.

## 1.5 Render tree vs DOM tree

The **render tree** is not the DOM. It includes only what is relevant for visual output. Nodes with `display: none` are omitted; pseudo-elements and generated content may appear even though they are not DOM nodes. MDN’s “How browsers work” notes that render tree construction starts from the DOM and uses computed styles to determine what is actually rendered. ([developer.mozilla.org][5])

Examples:

* `display: none` element: in DOM, not in render tree
* `visibility: hidden` element: in render tree, but not visible
* `::before { content: "★"; }`: not in DOM, but represented for rendering

That distinction matters because DOM operations and rendering operations are related, but not identical.

## 1.6 Layout: computing geometry

Layout computes the size and position of renderable boxes. Chromium’s RenderingNG docs describe the layout output as a fragment tree that captures position and size. ([Chrome for Developers][6])

At minimum, layout answers:

* How wide is each element?
* How tall is it?
* Where is its top-left corner?
* How do inline elements wrap?
* Where do scrollable overflows occur?

For block layout, a simplified mental model is:

```text
parent content box width = viewport width - margins - borders - padding
child width = specified width or shrink/expand rules
child y = previous sibling's bottom
child height = content height + padding + border
```

Real browsers have many layout modes:

* normal flow
* inline formatting
* flexbox
* grid
* tables
* positioned layout
* fragmentation across pages/columns

But a tiny browser can start with just block layout and simple inline text.

## 1.7 Paint: turning layout into draw commands

Once layout knows what exists and where, the browser generates paint instructions: draw background, border, text, image, shadows, etc. MDN and Chromium both describe paint as a distinct stage after layout and before compositing. ([developer.mozilla.org][1])

Conceptually:

```text
DrawRect(x=0, y=0, w=300, h=100, color=white)
DrawBorder(...)
DrawText("Hello", x=16, y=32, font=24px)
DrawText("World", x=16, y=64, font=16px, color=gray)
```

This is no longer HTML or CSS. It is graphics work.

## 1.8 Compositing: assembling layers efficiently

Modern browsers often separate some content into layers and let the GPU composite them. Chromium’s RenderingNG materials describe compositing as distinct from style, layout, and paint, and discuss “CompositeAfterPaint” as an architecture that improves reliability and performance. ([Chrome for Developers][7])

Why compositing exists:

* scrolling without repainting everything
* animating transforms or opacity on separate layers
* video and canvas integration
* clipping and stacking contexts

Typical layer candidates:

* fixed-position elements
* transformed elements
* opacity animations
* video/canvas
* isolated stacking contexts

A simplified model:

```text
Layer 0: page background and normal content
Layer 1: fixed header
Layer 2: transformed modal
GPU: blend layers in z-order
```

## 1.9 Invalidation: what happens after a change

The browser rarely recomputes the entire page from scratch. It tracks what changed and invalidates the smallest possible set of work:

* style invalidation
* layout invalidation
* paint invalidation
* layer invalidation

If you change `color`, you may only need style + paint.
If you change `width`, you may need style + layout + paint + composite.
If you animate `transform`, often layout can be skipped and only compositing changes. Chromium documents emphasize this separation because it strongly affects performance. ([Chrome for Developers][4])

## 1.10 Main thread pressure and jank

Long tasks on the main thread can block rendering and cause jank. MDN defines jank as sluggishness often caused by long tasks on the main thread or blocking rendering. ([developer.mozilla.org][8])

This is why certain DOM patterns are expensive:

* repeatedly reading layout information after writing styles
* changing many nodes one at a time
* large synchronous JavaScript tasks
* forcing reflow in a loop

A classic problem is “layout thrashing”:

```js
for (const el of items) {
  el.style.width = "100px";      // write
  console.log(el.offsetWidth);   // read -> forces layout
}
```

Each read may force the engine to flush pending style/layout work.

---

# 2. HTML + CSS + JS together

Now the key interaction: HTML creates structure, CSS determines presentation, JS can mutate both and trigger more work.

## 2.1 HTML drives discovery

As the parser walks HTML, it discovers:

* external stylesheets
* scripts
* images
* iframes
* fonts and other resources

Some of these can block progress. MDN’s critical rendering path docs explain that CSS is render-blocking for initial render, and classic scripts can block parsing depending on how they are included. ([developer.mozilla.org][1])

## 2.2 CSS can block first paint

The browser usually needs relevant CSS before it can safely present the page, because without CSS the geometry and style may be wrong. That is why external stylesheets are so important to the critical path. ([developer.mozilla.org][1])

## 2.3 Script processing changes parsing behavior

The HTML Standard defines a script processing model. Traditional synchronous `<script>` tags can pause parsing so the script can execute immediately in document order. `defer` and `async` change that behavior. ([html.spec.whatwg.org][3])

Very simplified:

```html
<p>One</p>
<script src="a.js"></script>
<p>Two</p>
```

The parser may:

1. parse `<p>One</p>`
2. stop to fetch/execute `a.js` as required by the model
3. continue with `<p>Two</p>`

Why? Because JS is allowed to inspect and modify the document during parsing, including historical features like `document.write()`.

## 2.4 JavaScript execution model

MDN describes JavaScript’s execution model as a single-threaded call stack with tasks, jobs/microtasks, and an event loop abstraction; engines optimize heavily underneath that model. ([developer.mozilla.org][9])

Practical browser view:

* JS runs on the main thread in many cases
* DOM operations are synchronous from JS’s point of view
* rendering updates are often deferred until the browser gets a chance to render
* promise callbacks run in the microtask queue before the next rendering opportunity

## 2.5 Engine internals

Modern JS engines parse source code and execute it through multiple tiers. MDN describes modern engines as using JIT compilation, and V8 documents that code is first compiled to Ignition bytecode and then optimized further for hot code paths. ([developer.mozilla.org][10])

Conceptually:

1. source code → tokens/parser → AST/internal representation
2. baseline/interpreter execution
3. profiling and feedback collection
4. optimized machine code for hot paths
5. deoptimization if assumptions become invalid

This matters for browser design because your “minimal browser” does not need this sophistication. A tiny browser can host a scripting engine and just provide DOM hooks.

## 2.6 DOM mutation and rendering

Suppose JS does:

```js
document.querySelector("#title").textContent = "Hi";
document.body.style.background = "black";
```

That can trigger:

* DOM tree mutation
* style invalidation
* paint invalidation
* maybe layout if sizes changed

Browsers typically batch many updates and render on the next frame, instead of repainting after every single statement. That batching is a huge reason rendering can remain efficient under normal usage.

## 2.7 The real mental model

Think of browser rendering as two cooperating subsystems:

### Document subsystem

* network loading
* HTML parsing
* CSS parsing
* JS execution
* DOM/CSSOM/state

### Graphics subsystem

* style computation
* layout
* paint list generation
* compositing
* raster/display

JavaScript sits between them and can perturb both.

---

# 3. How to write a minimal browser in C# without a browser control

Now the practical part.

A **real browser** is enormous. If you are building this from scratch in C#, the sensible target is:

> A toy browser that loads HTML, parses a tiny subset of CSS, performs simple block layout, draws text and rectangles, optionally runs tiny JS with a host object.

That is achievable. A full browser engine is not.

## 3.1 Scope for a teachable mini-browser

Keep the first version limited to:

### HTML

* `html`, `body`, `div`, `span`, `p`, `h1`, `a`, `img`
* text nodes
* attributes: `id`, `class`, `src`, `href`, `style`

### CSS

* selectors: tag, `.class`, `#id`
* properties: `display`, `width`, `height`, `margin`, `padding`, `background`, `color`, `font-size`
* values: px only

### Layout

* block layout only
* inline text drawn inside block boxes
* vertical stacking
* simple word wrapping

### Rendering

* backgrounds
* borders
* text
* maybe images

### JS

* optional in phase 2
* support `<script>` with a simple engine
* expose a tiny DOM API:

  * `getElementById`
  * `setText`
  * `setStyle`
  * `requestRender`

## 3.2 Architecture

Use layers like this:

```text
MiniBrowserApp
├── Networking
│   └── HtmlLoader
├── Parsing
│   ├── HtmlTokenizer
│   ├── HtmlParser
│   └── CssParser
├── DOM
│   ├── Node
│   ├── ElementNode
│   └── TextNode
├── Style
│   ├── CssRule
│   ├── SelectorMatcher
│   └── StyleResolver
├── Layout
│   ├── LayoutBox
│   └── LayoutEngine
├── Painting
│   ├── DisplayCommand
│   └── Painter
└── Scripting
    └── JsRuntimeHost
```

## 3.3 UI choice

Use a normal desktop UI toolkit such as:

* **WinForms** for simplicity
* or **WPF** if you want richer text/drawing control

For the minimal example, WinForms is simpler because you can override `OnPaint` and draw with `Graphics`.

---

# 4. A minimal implementation plan

## Phase 1: load and render static HTML

1. Fetch HTML with `HttpClient`
2. Parse into DOM
3. Parse CSS from `<style>` blocks and inline styles
4. Compute styles
5. Build layout boxes
6. Paint boxes

## Phase 2: add links, images, resize

* click hit testing
* image fetching
* relayout on window resize

## Phase 3: add JS

* embed a standalone JS engine library, not a browser control
* expose host DOM objects
* run `<script>` tags
* rerender after DOM/style changes

A library such as **Jint** can be used for JavaScript interpretation in .NET without embedding a browser engine; that is very different from using an existing web browser component. This is an implementation choice, not a browser component. The JS semantics still will not match a real browser unless you build the DOM and event APIs around it yourself.

---

# 5. Core data structures in C#

## 5.1 DOM nodes

```csharp
public abstract class DomNode
{
    public DomNode? Parent { get; set; }
    public List<DomNode> Children { get; } = new();
}

public sealed class ElementNode : DomNode
{
    public string TagName { get; }
    public Dictionary<string, string> Attributes { get; } = new();
    public Dictionary<string, string> ComputedStyle { get; } = new();

    public ElementNode(string tagName)
    {
        TagName = tagName.ToLowerInvariant();
    }

    public string? Id => Attributes.TryGetValue("id", out var v) ? v : null;

    public IEnumerable<string> Classes =>
        Attributes.TryGetValue("class", out var v)
            ? v.Split(' ', StringSplitOptions.RemoveEmptyEntries)
            : Enumerable.Empty<string>();
}

public sealed class TextNode : DomNode
{
    public string Text { get; set; }

    public TextNode(string text)
    {
        Text = text;
    }
}
```

## 5.2 CSS rules

```csharp
public sealed class CssRule
{
    public string Selector { get; set; } = "";
    public Dictionary<string, string> Declarations { get; } = new();
}
```

## 5.3 Layout boxes

```csharp
public sealed class LayoutBox
{
    public DomNode Node { get; }
    public RectangleF Bounds { get; set; }
    public List<LayoutBox> Children { get; } = new();

    public LayoutBox(DomNode node)
    {
        Node = node;
    }
}
```

---

# 6. Very small HTML parser

Do not try to implement the full HTML Standard parser first. Start with a tiny XML-like subset and accept only simple, well-formed HTML.

```csharp
public static class TinyHtmlParser
{
    public static ElementNode Parse(string html)
    {
        var root = new ElementNode("document");
        var stack = new Stack<ElementNode>();
        stack.Push(root);

        var i = 0;
        while (i < html.Length)
        {
            if (html[i] == '<')
            {
                if (i + 1 < html.Length && html[i + 1] == '/')
                {
                    int end = html.IndexOf('>', i);
                    if (end < 0) break;
                    if (stack.Count > 1) stack.Pop();
                    i = end + 1;
                }
                else
                {
                    int end = html.IndexOf('>', i);
                    if (end < 0) break;

                    string tagContent = html.Substring(i + 1, end - i - 1).Trim();
                    bool selfClosing = tagContent.EndsWith("/");

                    if (selfClosing)
                        tagContent = tagContent[..^1].Trim();

                    var parts = SplitTag(tagContent);
                    var tagName = parts[0];
                    var el = new ElementNode(tagName);

                    foreach (var (k, v) in ParseAttributes(parts.Skip(1)))
                        el.Attributes[k] = v;

                    stack.Peek().Children.Add(el);
                    el.Parent = stack.Peek();

                    if (!selfClosing && tagName != "img" && tagName != "br" && tagName != "meta")
                        stack.Push(el);

                    i = end + 1;
                }
            }
            else
            {
                int next = html.IndexOf('<', i);
                if (next < 0) next = html.Length;
                var text = html.Substring(i, next - i);
                if (!string.IsNullOrWhiteSpace(text))
                {
                    var tn = new TextNode(text);
                    stack.Peek().Children.Add(tn);
                    tn.Parent = stack.Peek();
                }
                i = next;
            }
        }

        return root;
    }

    private static List<string> SplitTag(string input)
    {
        var result = new List<string>();
        var sb = new System.Text.StringBuilder();
        bool inQuote = false;
        char quoteChar = '"';

        foreach (var ch in input)
        {
            if ((ch == '"' || ch == '\''))
            {
                if (!inQuote)
                {
                    inQuote = true;
                    quoteChar = ch;
                }
                else if (quoteChar == ch)
                {
                    inQuote = false;
                }
                sb.Append(ch);
            }
            else if (char.IsWhiteSpace(ch) && !inQuote)
            {
                if (sb.Length > 0)
                {
                    result.Add(sb.ToString());
                    sb.Clear();
                }
            }
            else
            {
                sb.Append(ch);
            }
        }

        if (sb.Length > 0) result.Add(sb.ToString());
        return result;
    }

    private static IEnumerable<(string key, string value)> ParseAttributes(IEnumerable<string> parts)
    {
        foreach (var part in parts)
        {
            int eq = part.IndexOf('=');
            if (eq < 0)
            {
                yield return (part.ToLowerInvariant(), "");
            }
            else
            {
                string key = part[..eq].ToLowerInvariant();
                string value = part[(eq + 1)..].Trim('"', '\'');
                yield return (key, value);
            }
        }
    }
}
```

This is intentionally tiny and not spec-compliant.

---

# 7. Tiny CSS parser and matcher

## 7.1 Parser

```csharp
public static class TinyCssParser
{
    public static List<CssRule> Parse(string css)
    {
        var rules = new List<CssRule>();
        var chunks = css.Split('}', StringSplitOptions.RemoveEmptyEntries);

        foreach (var chunk in chunks)
        {
            var parts = chunk.Split('{', 2);
            if (parts.Length != 2) continue;

            var selector = parts[0].Trim();
            var body = parts[1].Trim();

            var rule = new CssRule { Selector = selector };

            foreach (var decl in body.Split(';', StringSplitOptions.RemoveEmptyEntries))
            {
                var kv = decl.Split(':', 2);
                if (kv.Length != 2) continue;
                rule.Declarations[kv[0].Trim().ToLowerInvariant()] = kv[1].Trim();
            }

            rules.Add(rule);
        }

        return rules;
    }
}
```

## 7.2 Selector matching

```csharp
public static class SelectorMatcher
{
    public static bool Matches(ElementNode el, string selector)
    {
        selector = selector.Trim();

        if (selector.StartsWith("#"))
            return el.Id == selector[1..];

        if (selector.StartsWith("."))
            return el.Classes.Contains(selector[1..]);

        return el.TagName == selector.ToLowerInvariant();
    }
}
```

## 7.3 Style resolution

```csharp
public static class StyleResolver
{
    private static readonly Dictionary<string, string> DefaultStyles = new()
    {
        ["display"] = "block",
        ["color"] = "black",
        ["background"] = "transparent",
        ["font-size"] = "16"
    };

    public static void ApplyStyles(DomNode node, List<CssRule> rules)
    {
        if (node is ElementNode el)
        {
            foreach (var kv in DefaultStyles)
                el.ComputedStyle[kv.Key] = kv.Value;

            foreach (var rule in rules)
            {
                if (SelectorMatcher.Matches(el, rule.Selector))
                {
                    foreach (var decl in rule.Declarations)
                        el.ComputedStyle[decl.Key] = decl.Value;
                }
            }

            if (el.Attributes.TryGetValue("style", out var inlineStyle))
            {
                foreach (var decl in inlineStyle.Split(';', StringSplitOptions.RemoveEmptyEntries))
                {
                    var kv = decl.Split(':', 2);
                    if (kv.Length == 2)
                        el.ComputedStyle[kv[0].Trim().ToLowerInvariant()] = kv[1].Trim();
                }
            }
        }

        foreach (var child in node.Children)
            ApplyStyles(child, rules);
    }
}
```

This skips cascade order, specificity, inheritance, shorthand expansion, units, and many other real CSS details.

---

# 8. Layout engine

A tiny block layout engine can place block elements vertically.

```csharp
public static class LayoutEngine
{
    public static LayoutBox BuildLayout(DomNode node, float x, float y, float availableWidth)
    {
        var box = new LayoutBox(node);

        if (node is TextNode text)
        {
            box.Bounds = new RectangleF(x, y, availableWidth, 20);
            return box;
        }

        if (node is ElementNode el)
        {
            float margin = GetPx(el, "margin", 0);
            float padding = GetPx(el, "padding", 0);
            float width = GetPx(el, "width", availableWidth - margin * 2);
            float cursorY = y + margin + padding;
            float contentX = x + margin + padding;
            float contentWidth = Math.Max(0, width - padding * 2);

            foreach (var child in el.Children)
            {
                var childBox = BuildLayout(child, contentX, cursorY, contentWidth);
                box.Children.Add(childBox);
                cursorY = childBox.Bounds.Bottom;
            }

            float height = Math.Max(GetPx(el, "height", 0), (cursorY - y) + padding + margin);
            if (height <= 0) height = padding * 2 + 20;

            box.Bounds = new RectangleF(x + margin, y + margin, width, height);
        }

        return box;
    }

    private static float GetPx(ElementNode el, string name, float fallback)
    {
        if (!el.ComputedStyle.TryGetValue(name, out var value))
            return fallback;

        value = value.Trim().ToLowerInvariant().Replace("px", "");
        return float.TryParse(value, out var f) ? f : fallback;
    }
}
```

Again, this is intentionally simplistic.

---

# 9. Painting

Convert layout boxes into drawing commands or draw directly.

```csharp
public static class Painter
{
    public static void Paint(Graphics g, LayoutBox box)
    {
        if (box.Node is ElementNode el)
        {
            var bg = ParseColor(Get(el, "background", "transparent"));
            if (bg.HasValue)
            {
                using var brush = new SolidBrush(bg.Value);
                g.FillRectangle(brush, box.Bounds);
            }

            using var pen = new Pen(Color.LightGray);
            g.DrawRectangle(pen, box.Bounds.X, box.Bounds.Y, box.Bounds.Width, box.Bounds.Height);
        }

        if (box.Node is TextNode text)
        {
            using var brush = new SolidBrush(Color.Black);
            g.DrawString(text.Text.Trim(), SystemFonts.DefaultFont, brush, box.Bounds.Location);
        }

        foreach (var child in box.Children)
            Paint(g, child);
    }

    private static string Get(ElementNode el, string key, string fallback) =>
        el.ComputedStyle.TryGetValue(key, out var v) ? v : fallback;

    private static Color? ParseColor(string value)
    {
        value = value.Trim().ToLowerInvariant();
        return value switch
        {
            "transparent" => null,
            "white" => Color.White,
            "black" => Color.Black,
            "gray" => Color.Gray,
            "red" => Color.Red,
            "green" => Color.Green,
            "blue" => Color.Blue,
            _ => null
        };
    }
}
```

---

# 10. Hooking it into a WinForms surface

```csharp
public sealed class BrowserView : Control
{
    public LayoutBox? RootLayout { get; set; }

    public BrowserView()
    {
        DoubleBuffered = true;
        ResizeRedraw = true;
    }

    protected override void OnPaint(PaintEventArgs e)
    {
        base.OnPaint(e);
        e.Graphics.Clear(Color.White);

        if (RootLayout != null)
            Painter.Paint(e.Graphics, RootLayout);
    }
}
```

And the form:

```csharp
public partial class MainForm : Form
{
    private readonly BrowserView _view = new() { Dock = DockStyle.Fill };

    public MainForm()
    {
        Controls.Add(_view);
        Load += async (_, _) => await LoadPageAsync("https://example.com");
    }

    private async Task LoadPageAsync(string url)
    {
        using var client = new HttpClient();
        var html = await client.GetStringAsync(url);

        var dom = TinyHtmlParser.Parse(html);

        var cssText = ExtractStyleBlocks(dom);
        var rules = TinyCssParser.Parse(cssText);

        StyleResolver.ApplyStyles(dom, rules);

        _view.RootLayout = LayoutEngine.BuildLayout(dom, 10, 10, ClientSize.Width - 20);
        _view.Invalidate();
    }

    private static string ExtractStyleBlocks(ElementNode root)
    {
        var sb = new System.Text.StringBuilder();
        Walk(root, node =>
        {
            if (node is ElementNode el && el.TagName == "style")
            {
                foreach (var child in el.Children.OfType<TextNode>())
                    sb.AppendLine(child.Text);
            }
        });
        return sb.ToString();
    }

    private static void Walk(DomNode node, Action<DomNode> visitor)
    {
        visitor(node);
        foreach (var child in node.Children)
            Walk(child, visitor);
    }
}
```

This gives you the bones of a working toy renderer.

---

# 11. Adding JavaScript in C#

If you want JS, the sane route is:

* embed a pure .NET JS interpreter
* expose your own DOM bridge
* manually rerender after mutations

## 11.1 Host API

Create a small browser host object:

```csharp
public sealed class ScriptDomHost
{
    private readonly ElementNode _root;
    private readonly Action _requestRender;

    public ScriptDomHost(ElementNode root, Action requestRender)
    {
        _root = root;
        _requestRender = requestRender;
    }

    public ElementNode? GetElementById(string id) => FindById(_root, id);

    public void SetText(string id, string text)
    {
        var el = GetElementById(id);
        if (el == null) return;

        el.Children.Clear();
        var tn = new TextNode(text) { Parent = el };
        el.Children.Add(tn);
        _requestRender();
    }

    public void SetStyle(string id, string property, string value)
    {
        var el = GetElementById(id);
        if (el == null) return;

        el.ComputedStyle[property.ToLowerInvariant()] = value;
        _requestRender();
    }

    private static ElementNode? FindById(ElementNode node, string id)
    {
        if (node.Id == id) return node;

        foreach (var child in node.Children.OfType<ElementNode>())
        {
            var found = FindById(child, id);
            if (found != null) return found;
        }

        return null;
    }
}
```

## 11.2 Executing script

With a JS interpreter library, conceptually:

```csharp
// pseudo-usage
var host = new ScriptDomHost(dom, () =>
{
    _view.RootLayout = LayoutEngine.BuildLayout(dom, 10, 10, ClientSize.Width - 20);
    _view.Invalidate();
});

engine.SetValue("browser", host);
engine.Execute(@"
    browser.SetText('title', 'Changed by JS');
    browser.SetStyle('title', 'background', 'blue');
");
```

This is not a standards-compliant browser DOM. It is a controlled host environment.

---

# 12. What makes this hard in real browsers

Your toy browser will work for demos, but real browsers are difficult because of:

## HTML parsing complexity

The actual HTML parser is not a simple tree parser. It has insertion modes, foster parenting, foreign content rules, script pauses, character encoding handling, and well-defined recovery. The WHATWG parsing spec is large for a reason. ([html.spec.whatwg.org][2])

## CSS complexity

Real CSS requires:

* specificity and full cascade
* inheritance
* thousands of properties and interactions
* multiple formatting contexts
* pseudo-classes and pseudo-elements
* fonts, line breaking, bidi, writing modes

## Layout complexity

Text layout alone is a deep field:

* font metrics
* shaping
* ligatures
* bidi text
* line breaking
* inline formatting contexts

## JS/DOM integration

Scripts can mutate the DOM during parsing, schedule microtasks, observe layout-affecting state, and depend on subtle event ordering. The HTML script processing model plus JS execution model makes this much more than “just run a script.” ([html.spec.whatwg.org][3])

## Rendering performance

Modern engines maintain careful invalidation, display lists, fragment trees, and compositor layers to avoid unnecessary work. Chromium’s RenderingNG docs are a good picture of the sophistication involved. ([Chrome for Developers][4])

---

# 13. A good roadmap if you actually want to build it

## Step 1

Build a static renderer:

* parse tiny HTML
* parse tiny CSS
* layout blocks
* paint rectangles and text

## Step 2

Add interaction:

* scroll offset
* hit testing
* links
* image loading

## Step 3

Add better text:

* inline layout
* word wrapping
* line boxes

## Step 4

Add JS host:

* small DOM bridge
* script execution
* rerender scheduling

## Step 5

Improve correctness:

* style inheritance
* selector specificity
* better invalidation
* relative units and percentages

---

# 14. Practical advice

For learning, the best version is not “build Chrome in C#.” It is:

> build a renderer that proves you understand DOM, CSS, layout, paint, and JS-host interaction.

That gives you the right mental model.

The three most important design choices are:

1. **Keep the supported web subset tiny**
2. **Separate DOM, style, layout, and paint into different modules**
3. **Treat JavaScript as a host-integrated scripting layer, not as magic**

---

# 15. The shortest expert summary

Rendering is a pipeline:

* HTML parsing builds the DOM
* CSS parsing builds style rules
* style resolution computes used/computed values
* render/layout structures determine what is visible and where
* paint produces draw commands
* compositing assembles layers efficiently on screen ([developer.mozilla.org][1])

JavaScript does not “draw” directly. It mutates document state, which invalidates style/layout/paint work, and the browser schedules rendering around the execution model and event loop. ([developer.mozilla.org][9])

A minimal C# browser should therefore be built as:

* parser
* DOM
* style system
* layout engine
* painter
* optional JS host

not as one big class.



[1]: https://developer.mozilla.org/en-US/docs/Web/Performance/Guides/Critical_rendering_path?utm_source=chatgpt.com "Critical rendering path - Performance - MDN Web Docs"
[2]: https://html.spec.whatwg.org/multipage/parsing.html?utm_source=chatgpt.com "the HTML parsing spec"
[3]: https://html.spec.whatwg.org/multipage/?utm_source=chatgpt.com "Living Standard"
[4]: https://developer.chrome.com/docs/chromium/renderingng-architecture?utm_source=chatgpt.com "RenderingNG architecture | Chromium - Chrome for Developers"
[5]: https://developer.mozilla.org/en-US/docs/Web/Performance/Guides/How_browsers_work?utm_source=chatgpt.com "Populating the page: how browsers work - MDN Web Docs"
[6]: https://developer.chrome.com/docs/chromium/renderingng-data-structures?utm_source=chatgpt.com "Key data structures in RenderingNG | Chromium"
[7]: https://developer.chrome.com/docs/chromium/renderingng?utm_source=chatgpt.com "RenderingNG | Chromium - Chrome for Developers"
[8]: https://developer.mozilla.org/en-US/docs/Glossary/Jank?utm_source=chatgpt.com "Jank - Glossary - MDN Web Docs"
[9]: https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Execution_model?utm_source=chatgpt.com "JavaScript execution model - MDN Web Docs"
[10]: https://developer.mozilla.org/en-US/docs/Glossary/Engine/JavaScript?utm_source=chatgpt.com "JavaScript engine - Glossary - MDN Web Docs"
