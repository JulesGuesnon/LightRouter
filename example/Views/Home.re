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
      text="Home"
    />
    <Router.RouterLink to_=About>
      <Text
        style=Style.[
          fontFamily("Roboto-regular.ttf"),
          fontSize(20.),
          color(Colors.black),
        ]
        text="To About"
      />
    </Router.RouterLink>
  </View>;
};