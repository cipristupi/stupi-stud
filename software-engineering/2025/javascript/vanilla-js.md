# Understanding Vanilla JavaScript

"Vanilla JavaScript" refers to using plain, unadulterated JavaScript without any external libraries or frameworks like jQuery, React, Angular, or Vue.js. It is the core, native language that runs in web browsers, providing the fundamental building blocks for creating dynamic and interactive web experiences.

## Why is learning Vanilla JavaScript important?

Understanding Vanilla JavaScript is crucial for several reasons:

-   **Foundation:** Frameworks and libraries are built on top of Vanilla JavaScript. A strong understanding of the core language makes it significantly easier to learn and effectively use these tools.
-   **Performance:** Code written in Vanilla JavaScript can often be more performant as there's no overhead from a library or framework. You have direct control over how the code interacts with the browser.
-   **Deeper Understanding:** Working directly with the browser's Web APIs (like the DOM) provides a deeper understanding of how web pages work and how JavaScript interacts with them.
-   **Debugging:** When you understand the underlying JavaScript, debugging issues in frameworks becomes much more manageable.
-   **Flexibility:** For smaller projects or specific tasks, using Vanilla JavaScript can be more efficient and lightweight than bringing in an entire framework.
-   **Career Prospects:** A solid grasp of Vanilla JavaScript is a highly valued skill by employers, demonstrating a fundamental understanding of web technologies.

## Core Concepts of Vanilla JavaScript:

To master Vanilla JavaScript, you need to understand its fundamental concepts:

-   **Syntax and Basics:**
    -   **Variables:** Declaring and assigning values using `var`, `let`, and `const`. Understanding the differences between them (scope, reassignment).
    -   **Data Types:** Primitive types (strings, numbers, booleans, null, undefined, symbol, bigint) and the object type.
    -   **Operators:** Arithmetic, assignment, comparison, logical, and more.
    -   **Control Flow:**
        -   **Conditional Statements:** `if`, `else if`, `else`, `switch`.
        -   **Loops:** `for`, `while`, `do...while`, `for...in`, `for...of`.
-   **Functions:**
    -   Defining and calling functions.
    -   Function parameters and arguments.
    -   Return values.
    -   Function expressions and arrow functions (ES6+).
    -   Scope (global, local, block) and closures.
-   **Objects:**
    -   Creating objects using object literals and constructors.
    -   Accessing and modifying object properties and methods.
    -   `this` keyword (understanding its context).
    -   Prototypes and prototypal inheritance.
    -   Classes (ES6+) as a syntactic sugar over prototypes.
-   **Arrays:**
    -   Creating and manipulating arrays.
    -   Array methods (e.g., `push`, `pop`, `shift`, `unshift`, `splice`, `slice`, `forEach`, `map`, `filter`, `reduce`).
-   **The Document Object Model (DOM):**
    -   Understanding the DOM tree structure.
    -   Selecting DOM elements (e.g., `getElementById`, `querySelector`, `querySelectorAll`).
    -   Manipulating the DOM (changing content, attributes, styles).
    -   Creating and removing elements.
    -   Traversing the DOM (navigating between parent, child, and sibling nodes).
-   **Events:**
    -   Understanding different types of events (click, mouseover, keydown, submit, etc.).
    -   Adding event listeners (`addEventListener`).
    -   Event object and its properties.
    -   Event bubbling and capturing.
    -   Event delegation.
-   **Asynchronous JavaScript:**
    -   Understanding the event loop.
    -   Callbacks.
    -   Promises (handling asynchronous operations more effectively).
    -   Async/Await (syntactic sugar for working with Promises).
    -   Making HTTP requests (e.g., using the `Workspace` API or `XMLHttpRequest`).

## Study Materials:

Here are some resources to help you learn Vanilla JavaScript:

**Text-Based Tutorials and Documentation:**

-   **MDN Web Docs (Mozilla Developer Network):** This is an official and comprehensive resource for web technologies, including JavaScript. Their JavaScript guide is excellent for beginners and experienced developers alike.
    -   [https://developer.mozilla.org/en-US/docs/Web/JavaScript](https://developer.mozilla.org/en-US/docs/Web/JavaScript)
-   **The Modern JavaScript Tutorial:** This provides a thorough and well-structured guide to JavaScript, covering everything from the basics to more advanced topics.
    -   [https://javascript.info/](https://javascript.info/)
-   **W3Schools JavaScript Tutorial:** A popular resource with simple explanations and interactive examples.
    -   [https://www.w3schools.com/js/](https://www.w3schools.com/js/)

**Video Tutorials and Courses:**

-   **Traversy Media (YouTube Channel):** Offers many crash courses and tutorials on Vanilla JavaScript and DOM manipulation.
    -   [https://www.youtube.com/user/ traversymedia](https://www.youtube.com/user/ traversymedia) (Look for their JavaScript and DOM manipulation playlists)
-   **freeCodeCamp (YouTube Channel):** Provides full-length courses on JavaScript, often including building projects with Vanilla JS.
    -   [https://www.youtube.com/freecodecamp](https://www.youtube.com/freecodecamp) (Search for JavaScript full courses)
-   **The Codeholic (YouTube Channel):** Offers practical examples and tutorials focusing on various JavaScript concepts and projects using Vanilla JS.
    -   [https://www.youtube.com/@TheCodeholic](https://www.youtube.com/@TheCodeholic) (Explore their Vanilla JavaScript playlists)

Remember that consistent practice is key to mastering Vanilla JavaScript. Try building small projects and experimenting with the concepts as you learn them.

## Vanilla JavaScript Project Ideas:

Here are some project ideas you can implement using only Vanilla JavaScript, ranging from beginner-friendly to slightly more challenging:

**Beginner Projects:**

1.  **To-Do List:** A classic project to practice DOM manipulation (adding, removing, and marking items as complete), event handling (clicks, input), and possibly local storage to save the list.
2.  **Basic Counter:** Create a simple page with a number displayed, and buttons to increment and decrement the number. This is great for learning event listeners and updating text content.
3.  **Magic Eight Ball:** A simple application where a user asks a question, clicks a button, and a random answer is displayed from a predefined list. Focuses on arrays, random number generation, and text manipulation.
4.  **Color Flipper:** A webpage with a button that, when clicked, changes the background color of the page to a random color (either from a predefined list or generated randomly). Good for practicing DOM manipulation and working with styles.
5.  **Modal/Popup Window:** Create a button that opens a modal window and a way to close it (e.g., a close button or clicking outside the modal). This involves manipulating element visibility and handling click events.

**Intermediate Projects:**

6.  **Quiz Application:** Create a multiple-choice quiz. This will involve handling user input, checking answers, keeping score, and dynamically updating the questions and results displayed on the page.
7.  **Image Carousel/Slider:** Build a component that displays a series of images, with navigation buttons (previous/next) and possibly indicators. This is good for practicing DOM manipulation, event handling, and managing state (which image is currently displayed).
8.  **Recipe Finder (Basic):** A simple application where users can search for recipes based on keywords. You could have a predefined list of recipes in a JavaScript array of objects and filter/display them based on the search input.
9.  **Weather App (using a free API):** Fetch weather data from a public API (like OpenWeatherMap - you'll need an API key, usually free for basic use) based on user input (city name) and display the information. This introduces working with asynchronous JavaScript (`Workspace` API, Promises/Async/Await) and handling JSON data.
10. **Calculator:** Implement a basic calculator with arithmetic operations. This is a good challenge for handling multiple button clicks, managing input as a string, and evaluating mathematical expressions.

**Slightly More Advanced Projects:**

11. **Drawing App (Basic Canvas):** Use the HTML5 Canvas API to create a simple drawing application where users can draw lines or shapes with different colors. This involves working with the Canvas API and handling mouse events (mousedown, mousemove, mouseup).
12. **Simple Game (e.g., Snake, Tetris - simplified):** Building a classic arcade game can be a great way to practice game loops, handling user input for movement, collision detection, and updating the game state on the screen. Start with a very simplified version.
13. **Markdown Previewer:** Create a simple editor where a user can type Markdown text on one side and see the rendered HTML output on the other side in real-time. You would need to implement a basic Markdown parsing logic in JavaScript.
14. **SPA (Single Page Application) - Basic Routing:** Build a simple application with multiple "pages" or views without full page reloads. You can achieve basic routing by dynamically showing and hiding different sections of the page based on the URL hash or by manipulating the DOM.
15. **Data Visualization (Basic):** Use Vanilla JavaScript to render simple charts or graphs based on a small dataset. You could manipulate SVG or use the Canvas API to draw the visualizations.

When working on these projects, focus on:

-   **Breaking down the problem:** Divide the project into smaller, manageable tasks.
-   **DOM Manipulation:** Practice selecting, creating, modifying, and removing HTML elements.
-   **Event Handling:** Get comfortable with adding and responding to user interactions.
-   **Data Structures:** Utilize arrays and objects to organize your data.
-   **Functions:** Write reusable blocks of code.
-   **Problem Solving:** Figure out how to implement the required logic using only native JavaScript features.

## Revealing Module Pattern vs. Prototype Pattern

Let's explore the Revealing Module Pattern and the Prototype pattern in Vanilla JavaScript. They serve different primary purposes but are both important concepts in structuring JavaScript code.

### Revealing Module Pattern

**Description:**

The Revealing Module Pattern is a design pattern that leverages JavaScript's closures to create modules with private and public members. It's an evolution of the Module Pattern, aiming for cleaner syntax by "revealing" the public methods and properties through an object literal returned from an Immediately Invoked Function Expression (IIFE).

The core idea is to define all functions and variables inside a private scope (created by the IIFE). You then return an object literal that holds references to the functions and variables you want to expose as public. This provides excellent **encapsulation**, preventing external code from directly accessing or modifying the private members.

**Key characteristics:**

-   Uses an IIFE to create a private scope.
-   All logic and data are defined within this private scope.
-   Returns an object literal that exposes the public interface by referencing the private members.
-   Excellent for managing private state and methods.
-   Doesn't directly facilitate inheritance in the traditional OOP sense between modules created this way.

**Example: A Simple Counter Module**

```javascript
const Counter = (function () {
    // Private variable
    let count = 0;

    // Private function
    function changeBy(val) {
        count += val;
        console.log(`Count is now: ${count}`);
    }

    // Publicly revealed methods
    return {
        increment: function () {
            changeBy(1);
        },
        decrement: function () {
            changeBy(-1);
        },
        reset: function () {
            count = 0;
            console.log("Count reset.");
        }
        // You can also reveal private data, though less common for state you want to protect
        // currentCount: count // This would expose the *initial* value, not the live one
    };
})(); // The parentheses immediately invoke the function

// Using the Counter module
Counter.increment(); // Output: Count is now: 1
Counter.increment(); // Output: Count is now: 2
Counter.decrement(); // Output: Count is now: 1
Counter.reset(); // Output: Count reset.
Counter.increment(); // Output: Count is now: 1

// Trying to access private members (will fail)
// console.log(Counter.count);      // Output: undefined
// Counter.changeBy(10);          // Error: Counter.changeBy is not a function
```

### Prototype Pattern

**Description:**

The Prototype pattern in JavaScript is fundamental to how inheritance works in the language. Every object in JavaScript has an internal property called `[[Prototype]]` (exposed via `__proto__` in some environments, though accessing `__proto__` directly is generally discouraged in favor of `Object.getPrototypeOf()` and `Object.setPrototypeOf()`). This `[[Prototype]]` links to another object, which is its prototype. When you try to access a property or method on an object, and it's not found directly on the object, JavaScript looks up the `[[Prototype]]` chain until it finds the property or reaches the end of the chain (`null`).

The Prototype pattern, as a design pattern, specifically leverages this mechanism to create new objects based on existing ones, allowing for the sharing of properties and methods. This is often done using constructor functions and modifying their `prototype` property, or by using `Object.create()`.

**Key characteristics:**

-   Based on JavaScript's built-in prototypal inheritance.
-   Objects inherit properties and methods from their prototype.
-   Methods are typically defined on the constructor's `prototype` property to be shared efficiently among instances.
-   Naturally supports inheritance chains.
-   Encapsulation of private data on instances is less straightforward than with closures in the Module Pattern (though conventions and newer features like private class fields help).

**Example: A `Dog` Object using Prototypes (and ES6 Class equivalent for clarity)**

**Using Constructor Function and `prototype`:**

```javascript
// Constructor Function
function Dog(name, breed) {
    this.name = name; // Instance property
    this.breed = breed; // Instance property
}

// Adding methods to the prototype (shared by all Dog instances)
Dog.prototype.bark = function () {
    console.log(`${this.name} barks! Woof!`);
};

Dog.prototype.getDetails = function () {
    console.log(`${this.name} is a ${this.breed}.`);
};

// Creating instances
const dog1 = new Dog("Buddy", "Golden Retriever");
const dog2 = new Dog("Lucy", "Beagle");

// Using the objects and their methods
dog1.bark(); // Output: Buddy barks! Woof!
dog2.getDetails(); // Output: Lucy is a Beagle.

// Checking the prototype chain
// console.log(dog1.__proto__ === Dog.prototype); // true (in browsers, though use getPrototypeOf)
// console.log(Object.getPrototypeOf(dog1) === Dog.prototype); // true
```

**Using ES6 `class` (Syntactic Sugar for Prototypes):**

```javascript
class Dog {
    constructor(name, breed) {
        this.name = name; // Instance property
        this.breed = breed; // Instance property
    }

    // Methods are automatically added to the prototype
    bark() {
        console.log(`${this.name} barks! Woof!`);
    }

    getDetails() {
        console.log(`${this.name} is a ${this.breed}.`);
    }
}

// Creating instances
const dog3 = new Dog("Max", "German Shepherd");

// Using the object
dog3.bark(); // Output: Max barks! Woof!
```

### Comparison: Revealing Module Pattern vs. Prototype Pattern

| Feature               | Revealing Module Pattern                                                                                                       | Prototype Pattern (and ES6 Classes)                                                                                                   |
| :-------------------- | :----------------------------------------------------------------------------------------------------------------------------- | :------------------------------------------------------------------------------------------------------------------------------------ |
| **Primary Use**       | Encapsulation, organizing code into modules, controlling public API, managing private state.                                   | Object creation, sharing methods/properties among instances, inheritance.                                                             |
| **Encapsulation**     | Stronger out-of-the-box privacy using closures.                                                                                | Properties on `this` are public by default. Privacy requires conventions or newer language features.                                  |
| **Inheritance**       | Not designed for traditional OOP inheritance between modules.                                                                  | Core mechanism for inheritance in JavaScript.                                                                                         |
| **Instance Creation** | Typically creates a single instance (a module object) or multiple independent instances via factory functions within the IIFE. | Used with constructor functions (`new`) or `Object.create()` to create multiple instances that share a prototype.                     |
| **'this' Keyword**    | Usage of `this` within the module's public methods needs care if those methods are intended to be used in different contexts.  | `this` inside constructor functions and prototype methods refers to the instance being created or the object the method is called on. |
| **Syntax**            | Uses IIFEs and returning object literals.                                                                                      | Uses constructor functions and the `prototype` property, or the `class` keyword.                                                      |

**When to use which:**

-   **Revealing Module Pattern:** Ideal for creating self-contained units of code that manage their own state and expose a public API, without needing to create multiple instances with shared methods in the OOP sense. Useful for utilities, singletons (though be mindful of true singleton implementation), or organizing larger applications into logical modules.
-   **Prototype Pattern (and ES6 Classes):** Essential for creating blueprints for objects where you expect to create multiple instances that share common behavior and potentially inherit from other blueprints. This is the standard way to implement classical OOP concepts in JavaScript.

While ES6 classes provide a cleaner syntax, understanding the Prototype pattern is crucial for a deep understanding of JavaScript's object model and inheritance. The Revealing Module Pattern remains valuable for encapsulation and code organization, especially when you need to manage private data effectively.

---

Here are the resources to learn about Vanilla JavaScript, covering the concepts and patterns discussed, in markdown format:

---

# Vanilla JavaScript Learning Resources

Here is a compilation of recommended resources, including text-based tutorials, documentation, and video courses, to help you learn Vanilla JavaScript.

## Text-Based Tutorials and Documentation

These resources provide comprehensive explanations and references for JavaScript concepts.

-   **MDN Web Docs (Mozilla Developer Network)**

    -   **Description:** An official, reliable, and comprehensive resource for web technologies, including in-depth documentation on JavaScript, its features, and Web APIs (like the DOM). Excellent for both beginners and experienced developers as a reference.
    -   **Link:** [https://developer.mozilla.org/en-US/docs/Web/JavaScript](https://developer.mozilla.org/en-US/docs/Web/JavaScript)

-   **The Modern JavaScript Tutorial**

    -   **Description:** A free, detailed, and well-structured tutorial that covers JavaScript from the basics all the way up to advanced topics, including OOP and asynchronous programming.
    -   **Link:** [https://javascript.info/](https://javascript.info/)

-   **W3Schools JavaScript Tutorial**

    -   **Description:** A popular resource known for its simple explanations, interactive examples, and "Try it Yourself" editor, making it approachable for absolute beginners.
    -   **Link:** [https://www.w3schools.com/js/](https://www.w3schools.com/js/)

## Video Tutorials and Courses

These YouTube channels offer video-based learning, often with practical examples and project building.

-   **Traversy Media (YouTube Channel)**

    -   **Description:** Offers many crash courses and tutorials on web development topics, including excellent playlists specifically on Vanilla JavaScript and DOM manipulation. Great for learning by building.
    -   **Link:** Search for "Traversy Media JavaScript" or "Traversy Media DOM Crash Course" on YouTube. (e.g., [https://www.youtube.com/@TraversyMedia](https://www.youtube.com/@TraversyMedia))

-   **freeCodeCamp (YouTube Channel)**

    -   **Description:** Provides full-length, comprehensive video courses on programming and web development. Their JavaScript courses often cover core concepts and involve building projects using Vanilla JS.
    -   **Link:** Search for "freeCodeCamp JavaScript Course" on YouTube. (e.g., [https://www.google.com/search?q=https://www.youtube.com/%40freeCodeCamp](https://www.google.com/search?q=https://www.youtube.com/%40freeCodeCamp))

-   **The Codeholic (YouTube Channel)**

    -   **Description:** Offers practical examples, tutorials, and project-based learning focused on various JavaScript concepts and building applications with Vanilla JS.
    -   **Link:** Search for "The Codeholic Vanilla JavaScript" on YouTube. (e.g., [https://www.youtube.com/@TheCodeholic](https://www.youtube.com/@TheCodeholic))

Use these resources in combination to get both theoretical understanding and practical experience with Vanilla JavaScript. Happy learning\!

---

### Web Sockets

Web Sockets provide a persistent, full-duplex communication channel between a client (your browser) and a server over a single TCP connection. This allows for real-time data exchange, unlike traditional HTTP requests which are
unidirectional and require a new connection for each request.

**Usage:** Ideal for applications requiring live updates, such as chat applications, real-time notifications, collaborative tools, and online games.

**Vanilla JavaScript Example:**

```javascript
// Establish a WebSocket connection
const socket = new WebSocket("ws://your-websocket-server-url");

// Event handler for when the connection is opened
socket.onopen = (event) => {
    console.log("WebSocket connection opened:", event);
    // Send a message to the server
    socket.send("Hello Server!");
};

// Event handler for receiving messages from the server
socket.onmessage = (event) => {
    console.log("Message from server:", event.data);
};

// Event handler for WebSocket errors
socket.onerror = (event) => {
    console.error("WebSocket error:", event);
};

// Event handler for when the connection is closed
socket.onclose = (event) => {
    if (event.wasClean) {
        console.log(
            `WebSocket connection closed cleanly, code=${event.code}, reason=${event.reason}`
        );
    } else {
        console.error("WebSocket connection died");
    }
};

// To close the connection
// socket.close();
```

### Storage Types, Usage, and Comparison

Browsers provide several ways to store data on the client-side. Here are the main types in vanilla JavaScript:

| Storage Type     | Description                                                                                                                               | Capacity                                            | Expiration                                                               | Accessible From                                       |
| ---------------- | ----------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------- | ------------------------------------------------------------------------ | ----------------------------------------------------- |
| `localStorage`   | Stores data with no expiration date. Data persists until explicitly deleted.                                                              | 5-10 MB                                             | None (persists until cleared)                                            | All windows and tabs from the same origin             |
| `sessionStorage` | Stores data for the duration of a single session. Data is cleared when the browser tab is closed.                                         | 5-10 MB                                             | When the browser tab or window is closed.                                | Only within the same tab/window from the same origin  |
| Cookies          | Small text files stored by websites on a user's computer. Can have an expiration date and are sent with every HTTP request to the server. | 4 KB                                                | Can be set manually or expire when the browser closes (session cookies). | Server (HTTP headers) and Client ( `document.cookie`) |
| IndexedDB        | A low-level API for client-side storage of significant amounts of structured data, including files/blobs.                                 | Varies (can be large, e.g., hundreds of MB or more) | Persistent until explicitly deleted.                                     | Same origin                                           |

**Usage:**

-   **`localStorage`:** Storing user preferences (e.g., theme, language), offline data, or shopping cart contents.
-   **`sessionStorage`:** Storing temporary data related to the current session, like form data that needs to be
    retained across page reloads within the same tab.
-   **Cookies:** Primarily used for
    session management (e.g.,
    user authentication),
    tracking user behavior, and
    personalization. Due to their small size and being sent with every HTTP request, they are not suitable for
    large amounts of data.
-   **IndexedDB:** Storing large amounts of structured data locally, suitable for offline applications, caching large
    datasets, or storing user-generated content.

**Vanilla JavaScript Examples:**

**`localStorage` and `sessionStorage`:**

```javascript
// Setting data
localStorage.setItem("username", "JohnDoe");
sessionStorage.setItem("session_id", "abcdef123");

// Getting data
const username = localStorage.getItem("username");
const sessionId = sessionStorage.getItem("session_id");

console.log("Local Storage Username:", username);
console.log("Session Storage Session ID:", sessionId);

// Removing data
localStorage.removeItem("username");
// sessionStorage.removeItem('session_id');

// Clearing all data
// localStorage.clear();
// sessionStorage.clear();
```

**Cookies:**

Working with cookies directly using `document.cookie` can be cumbersome due to the need to manually parse and
serialize the cookie string. Libraries often simplify this.

```javascript
// Setting a cookie (basic example)
document.cookie =
    "mycookie=myvalue; expires=Thu, 18 Dec 2025 12:00:00 UTC; path=/";

// Getting cookies
const allCookies = document.cookie;
console.log("All Cookies:", allCookies);

// Function to get a specific cookie (more involved)
function getCookie(name) {
    const nameEQ = name + "=";
    const ca = document.cookie.split(";");
    for (let i = 0; i < ca.length; i++) {
        let c = ca[i];
        while (c.charAt(0) === " ") c = c.substring(1, c.length);
        if (c.indexOf(nameEQ) === 0)
            return c.substring(nameEQ.length, c.length);
    }
    return null;
}

const myCookieValue = getCookie("mycookie");
console.log("My Cookie Value:", myCookieValue);
```

**IndexedDB:**

IndexedDB has a more complex API based on requests and transactions due to its asynchronous nature and ability to
handle structured data. A basic example involves opening a database, creating an object store, and adding data.

```javascript
// Opening a database
const request = indexedDB.open("myDatabase", 1);

request.onerror = (event) => {
    console.error("IndexedDB error:", event.target.errorCode);
};

request.onupgradeneeded = (event) => {
    const db = event.target.result;
    // Create an object store
    const objectStore = db.createObjectStore("myObjectStore", {
        keyPath: "id"
    });
    // Create an index
    objectStore.createIndex("name", "name", { unique: false });
};

request.onsuccess = (event) => {
    const db = event.target.result;
    console.log("IndexedDB opened successfully");

    // Example of adding data
    const transaction = db.transaction(["myObjectStore"], "readwrite");
    const objectStore = transaction.objectStore("myObjectStore");
    const addRequest = objectStore.add({ id: 1, name: "Example Item" });

    addRequest.onsuccess = () => {
        console.log("Data added to IndexedDB");
    };

    addRequest.onerror = (event) => {
        console.error("Error adding data:", event.target.errorCode);
    };

    transaction.oncomplete = () => {
        console.log("Transaction complete");
    };
};
```

### AJAX (Asynchronous JavaScript and XML)

AJAX is a technique for making asynchronous HTTP requests from the client-side to a server without requiring a
full page reload. While "XML" is in the name, it's commonly used with JSON today. The core object for AJAX in vanilla
JavaScript is `XMLHttpRequest`.

**Usage:** Updating parts of a web page dynamically, fetching data from a server in the background, submitting form
data without a page refresh.

**Vanilla JavaScript Example (using `XMLHttpRequest`):**

```javascript
const xhr = new XMLHttpRequest();

xhr.open(
    "GET",
    "[https://api.example.com/data](https://api.example.com/data)",
    true
); // true for asynchronous

xhr.onreadystatechange = () => {
    if (xhr.readyState === XMLHttpRequest.DONE) {
        if (xhr.status === 200) {
            // Request was successful
            console.log("AJAX response:", xhr.responseText);
            try {
                const data = JSON.parse(xhr.responseText);
                console.log("Parsed JSON data:", data);
            } catch (e) {
                console.error("Error parsing JSON:", e);
            }
        } else {
            // There was an error
            console.error("AJAX error:", xhr.status, xhr.statusText);
        }
    }
};

xhr.onerror = () => {
    console.error("AJAX request failed");
};

xhr.send(); // Send the request
```

### Calls to Web API (using Fetch API)

The Fetch API is a more modern and flexible alternative to `XMLHttpRequest` for making HTTP requests. It's promise-based,
which simplifies handling asynchronous operations.

**Usage:** Same use cases as AJAX, but with a cleaner and more powerful API for handling requests and responses.

**Vanilla JavaScript Example (using Fetch API):**

```javascript
// GET request
fetch("[https://api.example.com/data](https://api.example.com/data)")
    .then((response) => {
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        return response.json(); // Parse the response as JSON
    })
    .then((data) => {
        console.log("Fetch API GET data:", data);
    })
    .catch((error) => {
        console.error("Fetch API GET error:", error);
    });

// POST request
const postData = {
    name: "Test User",
    job: "Developer"
};

fetch("[https://api.example.com/users](https://api.example.com/users)", {
    method: "POST", // Specify the method
    headers: {
        "Content-Type": "application/json" // Set the content type
    },
    body: JSON.stringify(postData) // Convert data to a JSON string
})
    .then((response) => {
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        return response.json();
    })
    .then((data) => {
        console.log("Fetch API POST data:", data);
    })
    .catch((error) => {
        console.error("Fetch API POST error:", error);
    });
```

The Fetch API is generally preferred over `XMLHttpRequest` for new developments due to its modern design and
ease of use with Promises.

### Communication Between Windows

In vanilla JavaScript, there are several ways to enable communication between different browser windows or tabs originating from the same domain. The choice of method depends on the specific requirements of your application, such as whether the communication needs to be broadcast to all tabs or targeted at a specific window, and whether the windows are from the same origin or different origins.

Here are the primary methods for inter-window communication in vanilla JavaScript:

### 1\. `window.postMessage()`

The `window.postMessage()` method provides a secure way to enable cross-origin communication between Window objects. This includes communication between a window and an iframe embedded within it, or between a window that opened another window (the opener and the opened).

-   **Usage:** Sending data securely between windows/frames from different origins, or as a general messaging mechanism between related windows from the same origin.
-   **Mechanism:** A message is dispatched on a target window. The receiving window listens for 'message' events. The event object contains the data sent, the origin of the sending window, and a reference to the sending window.

**Vanilla JavaScript Example:**

**In the sender window (e.g., `opener.html`):**

```javascript
const popup = window.open(
    "receiver.html",
    "receiverWindow",
    "width=400,height=400"
);

// Send a message to the popup window once it has loaded
if (popup) {
    popup.onload = () => {
        popup.postMessage("Hello from opener!", "YOUR_RECEIVER_ORIGIN"); // Replace YOUR_RECEIVER_ORIGIN
    };
}

// Listen for messages from the receiver window
window.addEventListener("message", (event) => {
    // Important: Verify the origin of the message for security
    if (event.origin === "YOUR_RECEIVER_ORIGIN") {
        // Replace YOUR_RECEIVER_ORIGIN
        console.log("Message from receiver:", event.data);
    } else {
        console.warn("Message from unknown origin:", event.origin);
    }
});
```

**In the receiver window (e.g., `receiver.html`):**

```javascript
// Listen for messages from the opener window
window.addEventListener("message", (event) => {
    // Important: Verify the origin of the message for security
    if (event.origin === "YOUR_OPENER_ORIGIN") {
        // Replace YOUR_OPENER_ORIGIN
        console.log("Message from opener:", event.data);

        // Send a reply back to the opener
        event.source.postMessage("Hello back from receiver!", event.origin);
    } else {
        console.warn("Message from unknown origin:", event.origin);
    }
});
```

**Important Security Note:** Always verify the `origin` property of the incoming message event to ensure you are only processing messages from trusted sources. When sending messages, provide the target origin as the second argument to `postMessage` to prevent sending data to unintended windows.

### 2\. Broadcast Channel API

The `BroadcastChannel` API allows communication between Browse contexts (windows, tabs, or iframes) on the same origin. It's like a publish-subscribe system where multiple contexts can subscribe to a channel and broadcast messages to all other contexts subscribed to the same channel.

-   **Usage:** Broadcasting messages to all open windows/tabs of the same application. Useful for synchronizing state across multiple tabs, like logout events or theme changes.
-   **Mechanism:** Create a `BroadcastChannel` object with a specific name in each context that needs to communicate. Messages sent on this channel will be received by all other `BroadcastChannel` objects with the same name in other contexts of the same origin.

**Vanilla JavaScript Example:**

**In multiple windows/tabs (same origin):**

```javascript
// Create or connect to a broadcast channel named 'my_channel'
const channel = new BroadcastChannel("my_channel");

// Listen for messages on the channel
channel.onmessage = (event) => {
    console.log("Message received on broadcast channel:", event.data);
};

// Send a message on the channel
function sendMessageToOtherTabs(message) {
    channel.postMessage(message);
}

// Example usage:
// sendMessageToOtherTabs('Hello to all tabs!');

// Close the channel when no longer needed
// channel.close();
```

### 3\. `localStorage` with the `storage` Event

This method leverages the `storage` event that fires on a window when a change is made to `localStorage` from a _different_ window of the same origin. While not a direct messaging channel, it can be used to signal changes or pass small amounts of data between tabs.

-   **Usage:** Simple signaling or sharing small data updates between tabs of the same origin. Can be a workaround if `BroadcastChannel` is not suitable or supported (though `BroadcastChannel` has good support in modern browsers).
-   **Mechanism:** One window writes to `localStorage`. Other windows listening for the 'storage' event are notified of the change. The event object contains information about the key, old value, new value, and the URL of the document that changed the storage.

**Vanilla JavaScript Example:**

**In one window/tab:**

```javascript
function sendStorageMessage(message) {
    // Set a unique key to avoid conflicts and ensure the event fires
    const key = "inter_tab_message_" + Date.now();
    localStorage.setItem(key, message);
    // Optionally remove the item immediately if you only need the event
    // localStorage.removeItem(key);
}

// Example usage:
// sendStorageMessage('Hello via storage!');
```

**In other windows/tabs (same origin) listening for changes:**

```javascript
window.addEventListener("storage", (event) => {
    // Check if the change is relevant to your inter-tab communication
    if (event.key && event.key.startsWith("inter_tab_message_")) {
        console.log("Storage event received:", event);
        console.log("Message from another tab:", event.newValue);
        // Optionally remove the item if it wasn't removed by the sender
        localStorage.removeItem(event.key);
    }
});
```

**Limitations:**

-   Only works for same-origin windows.
-   The `storage` event is _not_ fired in the window that made the `localStorage` change.
-   Data passed is limited to what can be stored in `localStorage` (strings).
-   Changes to the _same_ key in quick succession might not reliably trigger events in all tabs. Using unique keys or a more robust mechanism is recommended for reliable messaging.

### Other Possibilities (More Advanced/Specific)

-   **SharedWorker:** A type of web worker that can be shared by multiple Browse contexts of the same origin. They can be used as a central hub for communication between these contexts. More complex to set up than `BroadcastChannel`.
-   **Server-Side Communication (e.g., WebSockets):** While not a direct client-to-client method, windows/tabs can communicate by sending messages to a server, which then broadcasts or sends them to other connected clients. This is suitable for real-time communication that needs to involve the server or synchronize state across different users/browsers.

The `BroadcastChannel` API is generally the most straightforward and recommended approach for broadcasting messages between same-origin windows/tabs in modern vanilla JavaScript. For cross-origin communication, `window.postMessage()` is the standard and secure method.

Okay, here are resources to learn more about each of the concepts, and then all the information provided so far formatted in Markdown.

### Resources to Learn More

Here are some excellent resources, primarily from the Mozilla Developer Network (MDN), which is a comprehensive and reliable source for web documentation:

-   **Web Sockets:**

    -   [MDN Web Docs: The WebSocket API](https://developer.mozilla.org/en-US/docs/Web/API/WebSockets_API)
    -   [The Modern JavaScript Tutorial: WebSocket](https://javascript.info/websocket)

-   **Storage Types (localStorage, sessionStorage, Cookies, IndexedDB):**

    -   [MDN Web Docs: Web Storage API](https://developer.mozilla.org/en-US/docs/Web/API/Web_Storage_API) (`localStorage` and `sessionStorage`)
    -   [MDN Web Docs: Using cookies](https://developer.mozilla.org/en-US/docs/Web/HTTP/Cookies)
    -   [MDN Web Docs: IndexedDB API](https://developer.mozilla.org/en-US/docs/Web/API/IndexedDB_API)
    -   [JavaScript.info: Local Storage and Session Storage](https://www.google.com/search?q=https://javascript.info/localstorage-sessionstorage)

-   **AJAX (XMLHttpRequest):**

    -   [MDN Web Docs: XMLHttpRequest](https://developer.mozilla.org/en-US/docs/Web/API/XMLHttpRequest)
    -   [The Modern JavaScript Tutorial: XMLHttpRequest](https://javascript.info/xmlhttprequest)

-   **Calls to Web API (Fetch API):**

    -   [MDN Web Docs: Fetch API](https://developer.mozilla.org/en-US/docs/Web/API/Fetch_API)
    -   [The Modern JavaScript Tutorial: Fetch](https://javascript.info/fetch)

-   **Communication Between Windows:**

    -   [MDN Web Docs: Window.postMessage()](https://developer.mozilla.org/en-US/docs/Web/API/Window/postMessage)
    -   [MDN Web Docs: Broadcast Channel API](https://developer.mozilla.org/en-US/docs/Web/API/BroadcastChannel)
    -   [MDN Web Docs: StorageEvent](https://developer.mozilla.org/en-US/docs/Web/API/StorageEvent)

These resources provide in-depth explanations, examples, and API references for each topic.
