open Revery;
open Revery.UI;

let outsideRedirect = _ => {
  Router.redirect(Home) |> ignore;
};

let make = (~message, ()) => {
  <View>
    <Text style=Style.[color(Colors.black)] text={"Error: " ++ message} />
    <Components.Clickable onClick=outsideRedirect>
      <Text style=Style.[color(Colors.black)] text="Back to basics" />
    </Components.Clickable>
  </View>;
};