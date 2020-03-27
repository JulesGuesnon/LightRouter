open Revery;
open Revery.UI;

let make = () => {
  <View>
    <Text
      style=Style.[
        fontFamily("Roboto-regular.ttf"),
        fontSize(30.),
        color(Colors.black),
      ]
      text="About"
    />
    <Router.RouterLink to_={Error("Some random error")}>
      <Text
        style=Style.[
          fontFamily("Roboto-regular.ttf"),
          fontSize(20.),
          color(Colors.black),
        ]
        text="Oh no, an error"
      />
    </Router.RouterLink>
  </View>;
};