open Revery;
open Revery.UI;

let make = (~message, ()) => {
  <View>
    <Text
      style=Style.[
        fontFamily("Roboto-regular.ttf"),
        fontSize(30.),
        color(Colors.black),
      ]
      text={"Error: " ++ message}
    />
    <Router.RouterLink to_=Home>
      <Text
        style=Style.[
          fontFamily("Roboto-regular.ttf"),
          fontSize(20.),
          color(Colors.black),
        ]
        text="Back to basics"
      />
    </Router.RouterLink>
  </View>;
};