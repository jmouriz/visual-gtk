imports.searchPath.unshift('.'); 

var module = imports.module;

function onClicked(widget, data)
{
  let dialog = new Gtk.Dialog();
  let box = dialog.get_content_area();
  let label = new Gtk.Label();
  let button = new Gtk.Button();

  button.set_label("View GTK+ version");
  button.connect("clicked", function()
  {
    module.alert("GTK+ " + module.version())
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
  module.quit();
}
