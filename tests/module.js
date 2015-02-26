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

function quit()
{
  Gtk.main_quit()
}
