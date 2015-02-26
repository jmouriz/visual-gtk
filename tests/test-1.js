var get_version = function()
{
  return Gtk.MAJOR_VERSION + '.' + Gtk.MINOR_VERSION + '.' + Gtk.MICRO_VERSION
}

function onClicked(widget, data)
{
  let w = new Gtk.Window();
  let c = new Gtk.Box();
  let l = new Gtk.Label();
  let b = new Gtk.Button();

  b.set_label("View GTK+ version");
  b.connect("clicked", function()
  {
    alert("GTK+ " + get_version())
  });

  l.set_text("You clicked on '" + widget.get_label() + "'");

  c.set_orientation(Gtk.Orientation.VERTICAL);
  c.add(l);
  c.add(b);

  w.set_default_size(320, 120);
  w.add(c);
  w.show_all();
}

function onQuit()
{
  quit();
}
