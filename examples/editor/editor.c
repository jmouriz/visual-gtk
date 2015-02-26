#include <gtk/gtk.h>
#include "g-script-editor.h"

void
edited (GScriptEditor *editor, const gchar *javascript, gpointer data)
{
  g_print ("--- signal edited ---\n");
  g_print ("%s\n", javascript);
}

int
main (int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *editor;
  GScript *script;
  gchar *javascript;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  gtk_container_set_border_width (GTK_CONTAINER (window), 12);

  gtk_widget_set_size_request (window, 500, 300);

  g_signal_connect (G_OBJECT (window), "delete-event", G_CALLBACK (gtk_main_quit), NULL);

  editor = g_script_editor_new ();
  script = g_script_new ();

  if (1)
  {
    g_script_set_filename (script, "test.js");
  }

  javascript = g_strdup (g_script_get_javascript (script));
  g_script_editor_set_javascript (G_SCRIPT_EDITOR (editor), javascript);

  g_script_free (script);

  if (javascript)
  {
    g_free (javascript);
  }

  gtk_container_add (GTK_CONTAINER (window), editor);

  gtk_widget_show_all (window);

  g_signal_connect (G_OBJECT (editor), "edited", G_CALLBACK (edited), NULL);

  gtk_main ();

  return 0;
}
