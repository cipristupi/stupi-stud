| Concept                               | Angular                                                                                                                | React                                                                                                                                                                 | Vue                                                                                                                          |
| ------------------------------------- | ---------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------- |
| **Component Lifecycle**               | Comprehensive hooks:                                                                                                   | Functional Components with Hooks:                                                                                                                                     | Clear hooks:                                                                                                                 |
|                                       | - `ngOnInit`, `ngOnChanges`, `ngDoCheck`                                                                               | - `useEffect` for side effects (replaces many class-based methods).                                                                                                   | - Options API: `beforeCreate`, `created`, `beforeMount`, `mounted`, `beforeUpdate`, `updated`, `beforeUnmount`, `unmounted`. |
|                                       | - `ngAfterContentInit`, `ngAfterContentChecked`                                                                        | Class Components:                                                                                                                                                     | - Composition API: `setup`, `onMounted`, `onUpdated`, `onUnmounted`.                                                         |
|                                       | - `ngAfterViewInit`, `ngAfterViewChecked`                                                                              | - Distinct methods (`componentDidMount`, `componentDidUpdate`, `componentWillUnmount`).                                                                               |                                                                                                                              |
|                                       | - `ngOnDestroy`                                                                                                        | Tied to state and prop changes.                                                                                                                                       | Reactivity system influences update hooks.                                                                                   |
|                                       | Tied to change detection.                                                                                              |                                                                                                                                                                       |                                                                                                                              |
| **Style Encapsulation**               | Built-in View Encapsulation:                                                                                           | No built-in encapsulation. Relies on conventions and libraries:                                                                                                       | `scoped` attribute in `<style>` blocks (uses attributes).                                                                    |
|                                       | - `Emulated` (Default, uses attributes)                                                                                | - CSS Modules, Styled Components, Emotion, BEM.                                                                                                                       | Supports `:deep()` pseudo-selector for parent to child styling.                                                              |
|                                       | - `Shadow DOM` (native)                                                                                                | Styling between parent/child typically via props or shared styling solutions.                                                                                         | Also supports CSS Modules and Shadow DOM.                                                                                    |
|                                       | - `None` (global)                                                                                                      |                                                                                                                                                                       |                                                                                                                              |
|                                       | Styling parent to child often requires overriding encapsulation (e.g., deprecated `::ng-deep`) or using CSS variables. |                                                                                                                                                                       |                                                                                                                              |
| **Communication: Parent-Child**       | `@Input()` decorator to pass data down.                                                                                | Pass data as props.                                                                                                                                                   | Pass data as props (declared in `props` option or `defineProps`).                                                            |
| **Communication: Child-Parent**       | `@Output()` decorator with `EventEmitter` to emit custom events.                                                       | Parent passes a callback function as a prop to the child; child calls the function.                                                                                   | Child emits custom events using `$emit`. Parent listens using `v-on` or `@`.                                                 |
| **Communication: Siblings**           | Via a common parent component acting as an intermediary or using a shared service.                                     | Via a common parent component acting as an intermediary or using state management.                                                                                    | Via a common parent component acting as an intermediary or using an event bus (less common now) or state management.         |
| **State Management: Component Level** | Component class properties.                                                                                            | Functional Components: `useState` and `useReducer` Hooks.                                                                                                             | Options API: `data()` function.                                                                                              |
|                                       |                                                                                                                        | Class Components: `this.state` and `this.setState`.                                                                                                                   | Composition API: `ref` for primitives, `reactive` for objects.                                                               |
| **State Management: Global Level**    | Primarily **NgRx** (Redux-inspired, reactive) or **NGXS** (more opinionated).                                          | **Context API** (built-in, for simpler cases), **Redux** (popular, predictable, often with Redux Toolkit), **MobX** (observable-based), **Recoil**, **Zustand**, etc. | **Pinia** (official for Vue 3, simple, type-safe), **Vuex** (official for Vue 2, maintained for Vue 3, Flux-inspired).       |
|                                       | Centralized store, actions, reducers, selectors, effects.                                                              | Various paradigms and libraries available.                                                                                                                            | Centralized store, state, getters, mutations, actions.                                                                       |



Here are some resources to help you learn Angular, React, and Vue, with a focus on the concepts we discussed. The official documentation for each framework is generally the best place to start for accurate and in-depth information.

### General Learning Resources (Official Documentation)

* **Angular:** The official Angular documentation is comprehensive and well-structured.
    * [Angular Official Documentation](https://angular.dev/)
* **React:** The official React documentation is known for its clear explanations and examples, especially the new beta documentation which uses functional components and Hooks.
    * [React Official Documentation](https://react.dev/)
* **Vue:** The official Vue.js documentation is highly regarded for its readability and thoroughness.
    * [Vue.js Official Documentation](https://vuejs.org/guide/)

### Resources by Concept and Framework

Here are specific areas within the documentation and other resources relevant to each concept:

#### Component Lifecycle:

* **Angular:**
    * [Component Lifecycle - Angular Official Docs](https://angular.dev/guide/components/lifecycle)
* **React:**
    * [Lifecycle of Reactive Effects (for Functional Components with Hooks) - React Official Docs](https://react.dev/learn/lifecycle-of-reactive-effects)
    * [Using the Effect Hook (useEffect) - React Official Docs](https://react.dev/reference/react/useEffect)
    * [Component Lifecycle (for Class Components) - React Official (Legacy) Docs](https://react.dev/reference/react/Component#the-component-lifecycle)
* **Vue:**
    * [Lifecycle Hooks (Options API) - Vue.js Official Docs](https://vuejs.org/guide/essentials/lifecycle.html)
    * [Lifecycle Hooks (Composition API) - Vue.js Official Docs](https://vuejs.org/guide/essentials/composition-api.html#lifecycle-hooks)

#### Style Encapsulation:

* **Angular:**
    * [Component Styles - View Encapsulation - Angular Official Docs](https://angular.dev/guide/components/styling) (Look for the "View encapsulation" section)
* **React:** React's approach relies on external methods. Look for resources on:
    * [Adding a CSS Modules Stylesheet - React Official Docs](https://react.dev/learn/adding-component-styles#adding-a-css-modules-stylesheet)
    * Styled Components Documentation: [https://styled-components.com/](https://styled-components.com/)
    * Emotion Documentation: [https://emotion.sh/](https://emotion.sh/)
* **Vue:**
    * [Component Style Scoping - Vue.js Official Docs](https://vuejs.org/api/sfc-css-features.html#scoped-css)
    * [Deep Selectors - Vue.js Official Docs](https://vuejs.org/api/sfc-css-features.html#deep-selectors)
    * [CSS Modules - Vue.js Official Docs](https://vuejs.org/api/sfc-css-features.html#css-modules)

#### Communication Between Components:

* **Angular:**
    * [Sharing data between child and parent directives and components (@Input and @Output) - Angular Official Docs](https://angular.dev/guide/components/inputs-outputs)
    * For sibling or more complex communication: See State Management or Shared Services documentation within the Angular guide.
* **React:**
    * [Passing Props to a Component (Parent to Child) - React Official Docs](https://react.dev/learn/passing-props-to-a-component)
    * [Passing Data Deeply with Context (Alternative to prop drilling) - React Official Docs](https://react.dev/learn/passing-data-deeply-with-context)
    * For Child to Parent: This is typically done by passing callback functions as props. The React docs cover this concept within examples of handling events or lifting state up.
    * For Siblings: See State Management or lifting state up to a common ancestor in the React documentation.
* **Vue:**
    * [Props (Parent to Child) - Vue.js Official Docs](https://vuejs.org/guide/components/props.html)
    * [Emits (Child to Parent Custom Events) - Vue.js Official Docs](https://vuejs.org/guide/components/events.html)
    * For Siblings or more complex communication: See State Management or Provide/Inject.
    * [Provide / Inject - Vue.js Official Docs](https://vuejs.org/guide/components/provide-inject.html)

#### State Management:

* **Angular:**
    * Component-level state is standard TypeScript class properties. Refer to general component guides in the Angular docs.
    * Global State (NgRx): [NgRx Official Documentation](https://ngrx.io/)
    * Global State (NGXS): [NGXS Official Documentation](https://www.ngxs.io/)
* **React:**
    * Component-level state (`useState`, `useReducer`): Covered extensively in the React documentation under Hooks.
    * Global State (Context API): [Scaling with Context and a Reducer - React Official Docs](https://react.dev/learn/scaling-up-with-reducer-and-context)
    * Global State (Redux): [Redux Official Documentation](https://redux.js.org/) (Recommend learning with Redux Toolkit)
    * Global State (MobX): [MobX Official Documentation](https://mobx.js.org/)
    * Global State (Zustand): [Zustand GitHub Page](https://github.com/pmndrs/zustand)
* **Vue:**
    * Component-level state (`data`, `ref`, `reactive`): Covered in the Vue.js official docs under "Essentials" and "Composition API".
    * Global State (Pinia - Recommended for Vue 3): [Pinia Official Documentation](https://pinia.vuejs.org/)
    * Global State (Vuex - For Vue 2 and compatible with Vue 3): [Vuex Official Documentation](https://vuex.vuejs.org/)

These resources should provide a strong foundation for understanding how each framework handles these core concepts. Remember to practice by building small applications to solidify your learning!