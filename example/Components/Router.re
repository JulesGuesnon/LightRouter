open LightRouter;

module RouterConfig = {
  type route =
    | Home
    | About
    | Error(string);

  let defaultRoute = Home;

  let nameFromRoute = route =>
    switch (route) {
    | Home => "Home"
    | About => "About"
    | Error(_) => "Error"
    };
};

include Make(RouterConfig);