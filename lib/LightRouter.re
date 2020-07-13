open Revery.UI;

module type RouterConfig = {
  type route;
  let defaultRoute: route;
};

module Make = (RouterConfig: RouterConfig) => {
  include RouterConfig;

  module Store = {
    let subscriptions = ref([]);
    let oldRoute = ref(RouterConfig.defaultRoute);
    let route = ref(RouterConfig.defaultRoute);

    let updateRoute = newRoute => {
      oldRoute := route^;
      route := newRoute;

      subscriptions^ |> List.iter(sub => sub(oldRoute^, newRoute));
      (oldRoute^, newRoute);
    };

    let subscribe = cb => {
      subscriptions := List.append(subscriptions^, [cb]);

      () => {
        subscriptions := List.filter(c => c !== cb, subscriptions^);
      };
    };
  };

  type action =
    | Route(RouterConfig.route);

  type state = {currentRoute: RouterConfig.route};

  let reducer = (action, _) => {
    switch (action) {
    | Route(route) => {currentRoute: route}
    };
  };

  let useRoute = () => {
    let%hook (state, dispatch) =
      Hooks.reducer(~initialState={currentRoute: Store.route^}, reducer);

    let%hook _ =
      Hooks.effect(
        OnMount,
        () => {
          let unsubscribe =
            Store.subscribe((_, newRoute) => {dispatch(Route(newRoute))});
          Some(unsubscribe);
        },
      );

    (state.currentRoute, Store.updateRoute);
  };

  let%component make = (~render, ~style=?, ()) => {
    let%hook (state, dispatch) =
      Hooks.reducer(~initialState={currentRoute: Store.route^}, reducer);

    let%hook () =
      Hooks.effect(
        OnMount,
        () => {
          let _ = Store.updateRoute(RouterConfig.defaultRoute);
          Some(
            Store.subscribe((_, newRoute) => dispatch(Route(newRoute))),
          );
        },
      );

    <View
      style={
        switch (style) {
        | Some(s) => s
        | None => []
        }
      }>
      {render(state.currentRoute)}
    </View>;
  };

  module RouterLink = {
    let make = (~children, ~to_, ~onClick=?, ~style=?, ()) => {
      <Components.Clickable
        onClick={_ => {
          switch (onClick) {
          | Some(c) =>
            if (c()) {
              let _ = Store.updateRoute(to_);
              ();
            }
          | None =>
            let _ = Store.updateRoute(to_);
            ();
          }
        }}
        style={
          switch (style) {
          | Some(s) => s
          | None => []
          }
        }>
        children
      </Components.Clickable>;
    };
  };

  let subscribe = Store.subscribe;
  let redirect = Store.updateRoute;
};