#include <g-script-js.h>
#include <g-script-js-function.h>

int
main (int argc, char *argv[])
{
  GScriptJs *script;

  script = g_script_js_new ();

  g_script_js_set_source (script, "script.js");
  g_message ("%s", g_script_js_get_script (script));
  g_script_js_set_script (script, "var Gtk = imports.gi.Gtk;");
  g_message ("%s", g_script_js_get_script (script));
  g_script_js_set_script (script, "function hello() { print('hello') }");
  g_message ("%s", g_script_js_get_script (script));

  return 0;
}
