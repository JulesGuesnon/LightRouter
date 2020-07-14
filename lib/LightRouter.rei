/**
 * You need to create a module that respect the RouterConfig signature to use LightRouter
 *
 * `type route`: you probably want it to be a variant, but it can be a polymorphic variant, a string, int...
 * `let defaultRoute`: The first route on the first render
 */
module type RouterConfig = {
  type route;
  let defaultRoute: route;
};

/**
 * This is the core of LightRouter, it allows you to create as much Router as you want
 */
module Make:
  (RouterConfig: RouterConfig) =>
   {
    include RouterConfig;

    let make:
      (
        ~key: Brisk_reconciler.Key.t=?,
        ~render: RouterConfig.route =>
                 Brisk_reconciler.element(Revery_UI.React.node),
        ~style: list(Revery_UI.Style.viewStyleProps)=?,
        unit
      ) =>
      Brisk_reconciler.element(Revery_UI.viewNode);

    type state;

    /**
     * It allows you to get the current route and a function to redirect programmaticaly
     *
     * `let%hook (route, redirect) = Router.useRoute();`
     */
    let useRoute:
      (
        unit,
        Revery_UI.React.Hooks.t(
          (
            Revery_UI.React.Hooks.Reducer.t(state),
            Revery_UI.React.Hooks.Effect.t(
              Revery_UI.React.Hooks.Effect.onMount,
            )
          ) =>
          'a,
          'b,
        )
      ) =>
      (
        (
          RouterConfig.route,
          RouterConfig.route => (RouterConfig.route, RouterConfig.route),
        ),
        Revery_UI.React.Hooks.t('a, 'b),
      );

    /**
     * RouterLink allows you to have a component to redirect inside this router
     *
     * `<RouterLink to_=SomeRoute >...</RouterLink>
     */
    module RouterLink: {
      let make:
        (
          ~children: Brisk_reconciler.element(Revery_UI.React.node),
          ~to_: RouterConfig.route,
          ~onClick: unit => bool=?,
          ~style: list(Revery_UI.Style.viewStyleProps)=?,
          unit
        ) =>
        Brisk_reconciler.element(Revery_UI.React.node);
    };

    /**
     * `subscribe` allows you to register a callback everytime the route is updated
     *
     * `let unsubscribe = Router.subscribe((oldRoute, currentRoute) => {...})`
     */
    let subscribe:
      ((RouterConfig.route, RouterConfig.route) => unit, unit) => unit;

    /**
     * `redirect` allows you to redirect programmaticaly
     *
     * `let (previousRoute, currentRoute) = Router.redirect()`
     */
    let redirect:
      RouterConfig.route => (RouterConfig.route, RouterConfig.route);
  };