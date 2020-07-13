module type RouterConfig = {
  type route;
  let defaultRoute: route;
};

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

    let subscribe:
      ((RouterConfig.route, RouterConfig.route) => unit, unit) => unit;

    let redirect:
      RouterConfig.route => (RouterConfig.route, RouterConfig.route);
  };