/* glade-g-script-javascript.c
 *
 * Copyright (C) 2015 Juan Manuel Mouriz <jmouriz@gmail.com>
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <string.h>

#include <gladeui/glade.h>
#include <g-script-editor.h>

#include "glade-g-script.h"

#include "glade-g-script-javascript.h"

GLADE_MAKE_EPROP (GladeEPropJavascript, glade_eprop_javascript)

static gboolean busy = FALSE;

static void
glade_eprop_javascript_finalize (GObject *object)
{
  GObjectClass *parent_class = g_type_class_peek_parent (G_OBJECT_GET_CLASS (object));

  /* Chain up */
  G_OBJECT_CLASS (parent_class)->finalize (object);
}

static void
glade_eprop_javascript_load (GladeEditorProperty *eprop, GladeProperty *property)
{
  GladeEditorPropertyClass *parent_class = g_type_class_peek_parent (GLADE_EDITOR_PROPERTY_GET_CLASS (eprop));
  GladeEPropJavascript *javascript = GLADE_EPROP_JAVASCRIPT (eprop);
  GValue *value;
  const gchar *string;

  /* Chain up */
  parent_class->load (eprop, property);

  if (!property || busy)
  {
    return;
  }

  value = g_new0 (GValue, 1);

  glade_property_get_value (property, value);

  string = g_value_get_string (value);

  if (value)
  {
    g_free (value);
  }

  if (string)
  {
    g_script_editor_set_javascript (G_SCRIPT_EDITOR (javascript->editor), string);
  }
}

void
glade_eprop_javascript_edited (GScriptEditor *editor, const gchar *javascript, gpointer data)
{
  GValue value = G_VALUE_INIT;

  g_value_init (&value, G_TYPE_STRING);
  g_value_take_string (&value, (gchar *) javascript);
  
  busy = TRUE;
  glade_editor_property_commit (GLADE_EDITOR_PROPERTY (data), &value);
  busy = FALSE;
}

static GtkWidget *
glade_eprop_javascript_create_input (GladeEditorProperty *eprop)
{
  GladeEPropJavascript *javascript = GLADE_EPROP_JAVASCRIPT (eprop);

  javascript->editor = g_script_editor_new ();

  g_signal_connect (G_OBJECT (javascript->editor), "edited", G_CALLBACK (glade_eprop_javascript_edited), (gpointer) eprop);

  gtk_widget_set_size_request (javascript->editor, -1, 200);

  gtk_widget_show_all (javascript->editor);

  return javascript->editor;
}

void
glade_g_script_set_javascript (GObject *object, const GValue *value)
{
  //GladeWidget *editor;
  //editor = glade_widget_get_from_gobject (object);

  if (g_value_get_string (value) == NULL)
  {
    return;
  }

  g_script_set_javascript (G_SCRIPT (object), g_value_get_string (value));
}
