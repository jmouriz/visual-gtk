#include <g-script-js.h>
#include <g-script-js-function.h>

int
main (int argc, char *argv[])
{
  GScriptJs *script;

  script = g_script_js_new ();

  g_script_js_set_filename (script, "test-1.js");
  g_message ("%s", g_script_js_get_filename (script));
  g_script_js_set_javascript (script, "var Gtk = imports.gi.Gtk;");
  g_message ("%s", g_script_js_get_javascript (script));
  g_script_js_set_javascript (script, "function hello() { print('hello') }");
  g_message ("%s", g_script_js_get_javascript (script));

  return 0;
}
