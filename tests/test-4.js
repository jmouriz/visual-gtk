var Gtk = imports.gi.Gtk;

var version = function()
{
  return Gtk.MAJOR_VERSION + '.' + Gtk.MINOR_VERSION + '.' + Gtk.MICRO_VERSION
}

function alert(message)
{
  let dialog = new Gtk.MessageDialog();

  dialog.add_button("Close", 0);
  dialog.set_markup(message);
  dialog.run();
  dialog.destroy();
}

function onClicked(widget, data)
{
  let window = document.get_object("window");

  window.connect("delete-event", backdoorQuit);
  window.title = "It's works";
}

function backdoorQuit()
{
  print("backdoor");

  onQuit();
}

function onQuit()
{
  Gtk.main_quit()
}
