open Revery;
open Revery.UI;

let%component make = () => {
  let%hook (_, name) = Router.useRoute();

  <View
    style=Style.[
      position(`Absolute),
      left(0),
      right(0),
      top(0),
      height(60),
    ]>
    <Text
      style=Style.[
        fontFamily("Roboto-Regular.ttf"),
        fontSize(20.),
        color(Colors.black),
      ]
      text={"Current route: " ++ name}
    />
  </View>;
};