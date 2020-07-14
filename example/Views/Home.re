open Revery;
open Revery.UI;

let make = () => {
  <View>
    <Text style=Style.[color(Colors.black)] text="Home" />
    <Router.RouterLink to_=About>
      <Text style=Style.[color(Colors.black)] text="To About" />
    </Router.RouterLink>
  </View>;
};