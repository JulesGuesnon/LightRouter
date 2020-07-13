# :bulb: LightRouter

LightRouter is a Router (pretty obvious right?) for [Revery](https://github.com/revery-ui/revery).

## :zap: Requirements

-   The reason native package manager [Esy](https://esy.sh/)

## :wrench: Installation

### Add the module

In the folder of the project, open a terminal and run:

```bash
esy add re-light-router
```

### Add it to dune

In your dune file add `LightRouter` in your `libraries`:

```
(...
	(libraries ... LightRouter)
)
```

### Build

Well now you just have to build:

```bash
esy build
```

## :fire: Usage

**There's a complete example in the [example](/example) folder, you can take a look here if you wanna see a full application**

### Create the router

You need to define the configuration of the router and then make one

```reason
/* Router.re */
open  LightRouter;

module  RouterConfig  = {
	/* Define your routes */
	type  route  =
	|  Home
	|  About
	|  Error(string);

	/* Set de the default one */
	let  defaultRoute  =  Home;
};

include  Make(RouterConfig);
```

### Use it

Setup the router where you want in your application:

```reason
/* App.re */
open Revery;
open Revery.UI;


let make = () => {
	...
	<Router
		/* Router is just a View that has as children the result of the render props */
		/* so you can pass your style if you want */
		style=Style.[
			backgroundColor(Colors.red)
		]
		render={route =>
			switch (route) {
			|  Home  =>  <Home  />
			|  About  =>  <About  />
			|  Error(message) =>  <Error  message  />
			}
		}
	/>
	...
}
```

### Change the route

Use the `RouterLink` to redirect in your app:

```reason
/* Home.re */
open Revery;
open Revery.UI;


let make = () => {
	...
	<Router.RouterLink
		to_=Home
		/* onClick and style are not required */
		onClick={() => {
			print_endline("Clicked");
			true;
		}}
		style=Style.[...]
	>
		<Text
			style=...
			text="Link to home"
		/>
	</Router.RouterLink>
	...
}
```

You probably noticed the `true` at the end of the `onClick`. This boolean allows you to prevent or allow the redirection.

```reason
/* Home.re */
open Revery;
open Revery.UI;


let make = () => {
	...
	<Router.RouterLink
		to_=Home
		/* onClick and style are not required */
		onClick={() => {
			print_endline("You will never be redirected");
			/* By returning false, it will prevent the redirection */
			false;
		}}
		style=Style.[...]
	>
		<Text
			style=...
			text="Link to home"
		/>
	</Router.RouterLink>
	...
}
```

### Retrieve the route in a component

If a component need an information about the route in your app, you can use the `useRoute` hook in order to get the current route and the name of it.

```reason
/* About.re */
open Revery;
open Revery.UI;

let stringOfRoute = route => {...}

let%component make = () => {
	let%hook (route, redirect) = Router.useRoute();
	...
	<Text
		style=...
		text={"Current Route: " ++ stringOfRoute(name)}
	/>
	<Clickable onClick={_ => {
		print_endline("Programmatic redirection");
		redirect(Home);
	}}>
		<Text
			style=...
			text="Click me"
		>
	</Clickable>
	...
}
```

### Retrieve the route outside of a component

You may need the route outside of a component. You can subscribe to the route changes and trigger a callback every time the it changes:

```reason
/* NotAComponent.re */
let callMeOnRouteUpdate = (previousRoute, currentRoute) => {...}

/* Calling `unsubscribe` wont call anymore callMeOnRouteUpdate */
let unsubscribe = Router.subscribe(callMeOnRouteUpdate);
```

### Programmatic redirection outside of component

If you need to redirect the user from a function that is not related to components, it's easy:

```reason
/* Somewhere.re */

let myFunction = () => {
	Router.redirect(Home);
}
```

## :arrow_right: Todo

- Programmatic navigation
