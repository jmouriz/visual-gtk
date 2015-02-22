#include <g-script.h>
#include <g-script-function.h>

int
main (int argc, char *argv[])
{
  GScript *script;

  script = g_script_new ();

  g_script_set_filename (script, "test-1.js");
  g_message ("%s", g_script_get_filename (script));
  g_script_set_javascript (script, "var Gtk = imports.gi.Gtk;");
  g_message ("%s", g_script_get_javascript (script));
  g_script_set_javascript (script, "function hello() { print('hello') }");
  g_message ("%s", g_script_get_javascript (script));

  return 0;
}
