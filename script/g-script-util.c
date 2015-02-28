/* g-script-util.c
 *
 * Copyright (C) 2015 Juan Manuel Mouriz <jmouriz@gmail.com>
 *
 * This file is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <girepository.h>

#include "g-script.h"

static gboolean evaluated = FALSE;

static GScript *
find_script (GtkBuilder *builder)
{
  GScript *script;
  GSList *objects;

  script = NULL;
  objects = gtk_builder_get_objects (builder);

  // TODO use for and break to walk list, not nested function
  void get_script (gpointer node, gpointer data)
  {
    if (G_IS_SCRIPT (node))
    {
      script = G_SCRIPT (node);
    }
  }

  g_slist_foreach (objects, get_script, NULL);

  g_slist_free (objects);

  return script;
}

static void
connect_signal (GtkBuilder *builder, GObject *object, const gchar *signal, const gchar *handler, GObject *connect_object, GConnectFlags flags, gpointer data)
{
  GIRepository *repository;
  GScript *script;
  GClosure *closure;
  gboolean success;

  g_return_if_fail (GTK_IS_BUILDER (builder));
  g_return_if_fail (connect_object == NULL); /* TODO */

  script = find_script (builder);

  if (!script)
  {
    g_critical ("Cannot locate script");

    return;
  }

  repository = g_irepository_get_default ();

  g_irepository_require (repository, "Gtk", NULL, G_IREPOSITORY_LOAD_FLAG_LAZY, NULL);

  g_script_set_object (script, "document", G_OBJECT (builder));

  if (!evaluated)
  {
    success = g_script_evaluate (script);

    evaluated = TRUE;

    if (!success)
    {
      g_critical ("Error evaluating script for %s", handler);

      return;
    }
  }

  closure = g_script_get_closure (script, handler);

  if (!closure)
  {
    g_critical ("Cannot locate function %s", handler);

    return;
  }

  g_signal_connect_closure (object, signal, closure, !!(flags & G_CONNECT_AFTER));
}

void
g_script_util_connect (GtkBuilder *builder)
{
  gtk_builder_connect_signals_full (builder, connect_signal, NULL);
}

void
g_script_module_init (void)
{
  g_debug ("Registering type: %s", g_type_name (G_TYPE_SCRIPT)); /* linker hack */
}
