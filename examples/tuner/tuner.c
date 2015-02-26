#include <gtk/gtk.h>
#include <g-script.h>

int
main (int argc, gchar *argv[])
{
  gtk_init (&argc, &argv);
  g_script_module_init ();

  GtkBuilder *builder = gtk_builder_new_from_file("tuner.ui");
  g_script_util_connect (builder);

  GtkWindow *window = GTK_WINDOW (gtk_builder_get_object (builder, "window"));
  g_assert (window);

  gtk_window_present (window);

  gtk_main ();

  return 0;
}
