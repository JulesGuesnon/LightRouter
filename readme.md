# :bulb: LightRouter

LightRouter is a Router (pretty obvious right?) for [Revery](https://github.com/revery-ui/revery).

## :zap: Requirements

-   The reason native package manager [Esy](https://esy.sh/)

## :wrench: Installation

In the folder of the project, open a terminal and run:

```bash
esy add light-router
```

## :fire: Usage

**There's a complete example in the [example](/example) folder you can take a look here if you wanna se a full application**

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

	/* Make a function to convert your routes to string */
	let  nameFromRoute  = route =>
		switch (route) {
		|  Home  =>  "Home"
		|  About  =>  "About"
		|  Error(_) =>  "Error"
		};
};

include  Make(RouterConfig);
```

### Use it

Setup the router wherever you want in your application:

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
		onClick={() => print_endline("Clicked")}
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

If a component need an information in you app, you can use the `useRoute` hook in order to get the current route and the name of it.

```reason
/* About.re */
open Revery;
open Revery.UI;


let%component make = () => {
	let%hook (_route, name) = Router.useRoute();
	...
	<Text
		style=...
		text={"Current Route: " ++ name}
	/>
	...
}
```

### Retrieve the route outside of a component

you may need the route outside of a component. You can subscribe to the route change and trigger a callback every time the route change:

```reason
/* NotAComponent.re */
let callMeOnRouteUpdate = (previousRoute, currentRoute) => ...

Router.Store.subscribe(callMeOnRouteUpdate)
```

Need to unsubscribe ? You can:

```reason
/* Unsubscribe.re */
Router.Store.unsubscribe(NotAComponent.callMeOnRouteUpdate)
```
