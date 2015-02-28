#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include <g-script.h>

int
main (int argc, char *argv[])
{
  GOptionContext *context;
  GtkBuilder *builder;
  GtkWindow *window;
  GError *error;
  gchar *path;
  gchar *filename;
  gchar *script;
  gchar **args;
  int failure;

  error = NULL;
  script = NULL;
  path = NULL;
  filename = NULL;

  GOptionEntry entries[] =
  {
    { "filename", 'f', 0, G_OPTION_ARG_FILENAME, &filename, "Glade UI with inline GScript filename to run.", "f" },
    { NULL }
  };

  gtk_init (&argc, &argv);
  g_script_module_init ();

  context = g_option_context_new ("- run a Glade UI with inline GScript.");

  g_option_context_add_main_entries (context, entries, "g-script");
  g_option_context_add_group (context, gtk_get_option_group (TRUE));

#ifdef G_OS_WIN32
  args = g_win32_get_command_line ();
#else
  args = g_strdupv (argv);
#endif

  if (!g_option_context_parse_strv (context, &args, &error))
  {
    g_print ("%s\n", error->message);

    g_error_free (error);

    return 1;
  }

  g_option_context_free (context);

  g_strfreev (args);

  if (!filename)
  {
    if (argc > 1)
    {
      filename = g_strdup (argv[1]);
    }
    else
    {
      g_print ("You must provide a file to run.\n");

      return 1;
    }
  }

  if (!g_file_test (filename, G_FILE_TEST_IS_REGULAR))
  {
    g_print ("%s is not a regular file.\n", filename);

    g_free (filename);

    return 1;
  }

  path = g_path_get_dirname (filename);

  failure = g_chdir (path);

  g_free (path);

  if (failure)
  {
    g_print ("Can not change directory to %s.\n", path);

    g_free (filename);

    return 1;
  }

  script = g_path_get_basename (filename);

  g_free (filename);

  builder = gtk_builder_new ();
  error = NULL;

  gtk_builder_add_from_file (builder, script, &error);

  g_free (script);

  if (error)
  {
    g_print ("%s\n", error->message);

    g_error_free (error);

    return 1;
  }

  g_script_util_connect (builder);

  // TODO to handle errors
  window = GTK_WINDOW (gtk_builder_get_object (builder, "window"));
  g_assert (window);

  gtk_window_present (window);

  gtk_main ();

  return 0;
}
