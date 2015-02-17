#include <gtk/gtk.h>
#include <cjs/gjs-module.h>

#include "g-script-js.h"

static void
connect (GtkBuilder *builder, GObject *object, const gchar *signal, const gchar *handler, GObject *connect_object, GConnectFlags flags, gpointer data)
{
  const gchar *name = (gchar *) data;
  gboolean success;
  GScriptJs *script;
  GClosure *closure;

  g_return_if_fail (name != NULL);
  g_return_if_fail (connect_object == NULL); /* TODO */

  script = G_SCRIPT_JS (gtk_builder_get_object (builder, name));

  g_script_js_set_object (script, "builer", G_OBJECT (builder));

  if (!script)
  {
    g_critical ("Cannot locate script %s", name);

    return;
  }

  success = g_script_js_evaluate (script);

  if (!success)
  {
    g_critical ("Error evaluating script for %s", handler);

    return;
  }

  closure = g_script_js_get_closure (script, handler);

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

  g_debug ("Registering type: %s", g_type_name (G_TYPE_SCRIPT_JS)); /* linker hack */

  builder = gtk_builder_new();
  error = NULL;
  gtk_builder_add_from_file (builder, "test-3.ui", &error);
  gtk_builder_connect_signals_full (builder, connect, (gpointer) "script");
  g_assert_no_error (error);

  window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
  g_assert (window);

  gtk_window_present (GTK_WINDOW (window));
  gtk_main ();

  return 0;
}
