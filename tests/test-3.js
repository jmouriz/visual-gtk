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
  let dialog = new Gtk.Dialog();
  let box = dialog.get_content_area();
  let label = new Gtk.Label();
  let button = new Gtk.Button();

  button.set_label("View GTK+ version");
  button.connect("clicked", function()
  {
    alert("GTK+ " + version())
  });

  label.set_text("You clicked on '" + widget.get_label() + "'");

  box.add(label);
  box.add(button);

  box.show_all();

  dialog.run();
  dialog.destroy();
}

function onQuit()
{
  Gtk.main_quit()
}
