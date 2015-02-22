#include <girepository.h>
#include <gtk/gtk.h>
#include <cjs/gjs-module.h>
#include <gi/object.h>

#include <g-script.h>

static void
connect (GtkBuilder *builder, GObject *object, const gchar *signal, const gchar *handler, GObject *connect_object, GConnectFlags flags, gpointer data)
{
  const gchar *name = (gchar *) data;
  GIRepository *repository;
  gboolean success;
  GScript *script;
  GClosure *closure;

  g_return_if_fail (name != NULL);
  g_return_if_fail (connect_object == NULL); /* TODO */

  script = G_SCRIPT (gtk_builder_get_object (builder, name));

  if (!script)
  {
    g_critical ("Cannot locate script %s", name);

    return;
  }

  repository = g_irepository_get_default ();

  g_irepository_require (repository, "Gtk", NULL, G_IREPOSITORY_LOAD_FLAG_LAZY, NULL);

  g_script_set_object (script, "document", G_OBJECT (builder));

  success = g_script_evaluate (script);

  if (!success)
  {
    g_critical ("Error evaluating script for %s", handler);

    return;
  }

  closure = g_script_get_closure (script, handler);

  if (!closure)
  {
    g_critical ("Cannot locate function %s", handler);

    return;
  }

  g_signal_connect_closure (object, signal, closure, !!(flags & G_CONNECT_AFTER));
}

int
main (int argc, gchar *argv[])
{
  GtkBuilder *builder;
  GtkWidget *window;
  GError *error;

  gtk_init (&argc, &argv);

  g_debug ("Registering type: %s", g_type_name (G_TYPE_SCRIPT)); /* linker hack */

  builder = gtk_builder_new();
  error = NULL;
  gtk_builder_add_from_file (builder, "test-4.ui", &error);
  gtk_builder_set_translation_domain (builder, "test");
  gtk_builder_connect_signals_full (builder, connect, (gpointer) "script");
  g_assert_no_error (error);

  window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
  g_assert (window);

  gtk_window_present (GTK_WINDOW (window));
  gtk_main ();

  return 0;
}
