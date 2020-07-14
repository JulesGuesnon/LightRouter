open Revery;
open Revery.UI;

let%component make = () => {
  let%hook (_, redirect) = Router.useRoute();

  <View>
    <Text style=Style.[color(Colors.black)] text="About" />
    <Components.Clickable
      onClick={_ => redirect(Error("Some random error")) |> ignore}>
      <Text style=Style.[color(Colors.black)] text="Oh no, an error" />
    </Components.Clickable>
  </View>;
};