open TestFramework;

module Config = {
  type route =
    | Home
    | Hello
    | Error(string);

  let defaultRoute = Home;
};

module Router = LightRouter.Make(Config);

let {describe, _} =
  describeConfig
  |> withLifecycle(testLifecycle =>
       testLifecycle |> beforeEach(() => Router.redirect(Home) |> ignore)
     )
  |> build;

describe("LightRouter", _ => {
  describe("Route update", ({test}) => {
    test("The subscription must be called on route update", ({expect}) => {
      let subscribeMock = ((_, _) => ()) |> Mock.mock2;

      let unsubscribe = subscribeMock |> Mock.fn |> Router.subscribe;

      Router.redirect(Hello) |> ignore;

      expect.mock(subscribeMock).toBeCalled();

      Router.redirect(Home) |> ignore;
      Router.redirect(Error("oh no")) |> ignore;
      Router.redirect(Hello) |> ignore;

      expect.mock(subscribeMock).toBeCalledTimes(4);

      unsubscribe();

      Router.redirect(Home) |> ignore;

      expect.mock(subscribeMock).toBeCalledTimes(4);

      ();
    });

    test("The route must be the correct one on update", ({expect}) => {
      let (oldRoute, currentRoute) = Router.redirect(Hello);

      expect.same(oldRoute, Config.Home);
      expect.same(currentRoute, Config.Hello);

      let message = "Some error";

      let (_, currentRoute) = Router.redirect(Error(message));

      switch (currentRoute) {
      | Error(e) => expect.string(e).toEqual(message)
      | _ => failwith("Router didn't redirect to Error route")
      };
    });
  })
});