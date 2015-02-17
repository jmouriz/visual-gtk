/* glade-g-script-js-editor.c
 *
 * Copyright (C) 2013 Juan Manuel Mouriz <jmouriz@gmail.com>
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

#include <gladeui/glade.h>

#include "glade-g-script-js.h"
#include "glade-g-script-js-filename.h"

GLADE_MAKE_EPROP (GladeEPropFilename, glade_eprop_filename)

//GType glade_eprop_filename_get_type (void) G_GNUC_CONST;

static void glade_eprop_filename_changed (GladeEditorProperty *, GladeProperty *, gpointer);

static void
glade_eprop_filename_finalize (GObject *object)
{
  /* Chain up */
  GObjectClass *parent_class =
      g_type_class_peek_parent (G_OBJECT_GET_CLASS (object));

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

static void
glade_eprop_filename_load (GladeEditorProperty *eprop, GladeProperty *property)
{
  GladeEditorPropertyClass *parent_class = g_type_class_peek_parent (GLADE_EDITOR_PROPERTY_GET_CLASS (eprop));
  GladeEPropFilename *filename = GLADE_EPROP_FILENAME (eprop);
  GValue *value;
  const gchar *string;

  parent_class->load (eprop, property);

  if (!property)
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

  //g_print ("%s (%d) : %s (%s) | %s\n", __FILE__, __LINE__, __FUNCTION__, string, G_OBJECT_TYPE_NAME (script));
  g_print ("%p\n", script);

  if (string)
  {
    gtk_file_chooser_set_filename (GTK_FILE_CHOOSER (filename->editor), string);
  }

  //glade_editor_property_commit (eprop, value);
}

void
glade_eprop_filename_file_set (GtkFileChooserButton *widget, gpointer data)
{
  gchar *filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (widget));
  GValue value = G_VALUE_INIT;

  g_value_init (&value, G_TYPE_STRING);
  g_value_take_string (&value, filename);
  
  g_print ("%s (%d) : %s (%s)\n", __FILE__, __LINE__, __FUNCTION__, filename);

  glade_editor_property_commit (GLADE_EDITOR_PROPERTY (data), &value);

  g_free (filename);
}

static GtkWidget *
glade_eprop_filename_create_input (GladeEditorProperty *eprop)
{
  GladeEPropFilename *filename = GLADE_EPROP_FILENAME (eprop);

  filename->editor = gtk_file_chooser_button_new ("Choose filename", GTK_FILE_CHOOSER_ACTION_OPEN);

  //gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (filename->editor), "Untitled document");

  g_signal_connect (G_OBJECT (filename->editor), "file-set", G_CALLBACK (glade_eprop_filename_file_set), (gpointer) eprop);

  gtk_widget_show_all (filename->editor);

  return filename->editor;
}

void
glade_g_script_js_set_filename (GObject *object, const GValue *value)
{
  if (g_value_get_string (value) == NULL)
  {
    return;
  }

  g_script_js_set_filename (G_SCRIPT_JS (object), g_value_get_string (value));
}
