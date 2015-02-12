#include <gtk/gtk.h>
#include "g-script-js-editor.h"

int
main (int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *editor;
  GScriptJs *script;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  gtk_container_set_border_width (GTK_CONTAINER (window), 12);

  gtk_widget_set_size_request (window, 200, 200);

  g_signal_connect (G_OBJECT (window), "delete-event", G_CALLBACK (gtk_main_quit), NULL);

  editor = g_script_js_editor_new ();
  script = g_script_js_new ();

  g_script_js_set_source (script, "script.js");

  g_script_js_editor_set_script (G_SCRIPT_JS_EDITOR (editor), script);

  gtk_container_add (GTK_CONTAINER (window), editor);

  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}
