let init = app => {
  Timber.App.enable();
  Timber.App.setLevel(Timber.Level.perf);

  let win = Revery.App.createWindow(app, "LightRouter example");

  Revery.Window.setBackgroundColor(win, Revery.Colors.white);
  Revery.Window.maximize(win);

  let _: Revery.UI.renderFunction = Revery.UI.start(win, <App />);
  ();
};

Revery.App.start(init);