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
//#include <gladeui/glade-widget-adaptor.h>
//#include <gdk/gdkkeysyms.h>

#include "glade-g-script-js-script.h"

GLADE_MAKE_EPROP (GladeEPropScript, glade_eprop_script)

//GType glade_eprop_script_get_type (void) G_GNUC_CONST;

static void
glade_eprop_script_finalize (GObject *object)
{
  /* Chain up */
  GObjectClass *parent_class =
      g_type_class_peek_parent (G_OBJECT_GET_CLASS (object));

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

static void
glade_eprop_script_load (GladeEditorProperty *eprop, GladeProperty *property)
{
  GladeEditorPropertyClass *parent_class = g_type_class_peek_parent (GLADE_EDITOR_PROPERTY_GET_CLASS (eprop));
  GladeEPropScript *script = GLADE_EPROP_SCRIPT (eprop);

  parent_class->load (eprop, property);

  if (script->context)
  {
    glade_name_context_destroy (script->context);
  }

  script->context = NULL;

  if (!property)
  {
    return;
  }

  script->context = glade_name_context_new ();
}

static GtkWidget *
glade_eprop_script_create_input (GladeEditorProperty *eprop)
{
  //GladeEPropScript *script = GLADE_EPROP_SCRIPT (eprop);
  GtkWidget *editor;

  g_print ("%s (%d) : %s\n", __FILE__, __LINE__, __FUNCTION__);
  
  editor = gtk_file_chooser_button_new ("Choose script", GTK_FILE_CHOOSER_ACTION_OPEN);

  gtk_widget_show_all (editor);

  return editor;
}
