open Revery;
open Revery.UI;

let make = () => {
  <View
    style=Style.[
      position(`Absolute),
      left(0),
      right(0),
      top(0),
      bottom(0),
      justifyContent(`Center),
      alignItems(`Center),
      backgroundColor(Color.hex("#f8f9fc")),
    ]>
    <Topbar />
    <Router
      style=Style.[
        position(`Absolute),
        left(0),
        right(0),
        bottom(0),
        top(60),
        justifyContent(`Center),
        alignItems(`Center),
      ]
      render={route =>
        switch (route) {
        | Home => <Home />
        | About => <About />
        | Error(message) => <Error message />
        }
      }
    />
  </View>;
};