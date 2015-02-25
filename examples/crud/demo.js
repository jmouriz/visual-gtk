const GLib = imports.gi.GLib;
const Gda  = imports.gi.Gda;

var connection = new Gda.Connection ({
                                        provider:   Gda.Config.get_provider("SQLite"),
                                        cnc_string: "DB_DIR=" + GLib.get_home_dir () + ";DB_NAME=demo"
                                     });
connection.open ();

var data = connection.execute_select_command ("select * from demo order by 1");
var iter = data.create_iter ();

while (iter.move_next ())
{
  var a = Gda.value_stringify (iter.get_value_at (0));
  var b = Gda.value_stringify (iter.get_value_at (1));

  print(a, b);
}

connection.close ();
