/* glade-g-script-js-source.c
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

#include <gladeui/glade.h>
//#include <gtksourceview/gtksourceview.h>
//#include <gtksourceview/gtksource.h>
#include <g-script-js-editor.h>

#include "glade-g-script-js-source.h"

GLADE_MAKE_EPROP (GladeEPropSource, glade_eprop_source)

//GType glade_eprop_source_get_type (void) G_GNUC_CONST;

static void
glade_eprop_source_finalize (GObject *object)
{
  /* Chain up */
  GObjectClass *parent_class =
      g_type_class_peek_parent (G_OBJECT_GET_CLASS (object));

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

static void
glade_eprop_source_load (GladeEditorProperty *eprop, GladeProperty *property)
{
  GladeEditorPropertyClass *parent_class = g_type_class_peek_parent (GLADE_EDITOR_PROPERTY_GET_CLASS (eprop));
  GladeEPropSource *source = GLADE_EPROP_SOURCE (eprop);

  parent_class->load (eprop, property);

  if (source->context)
  {
    glade_name_context_destroy (source->context);
  }

  source->context = NULL;

  if (!property)
  {
    return;
  }

  source->context = glade_name_context_new ();
}

static GtkWidget *
glade_eprop_source_create_input (GladeEditorProperty *eprop)
{
  //GladeEPropSource *source = GLADE_EPROP_SOURCE (eprop);
  GtkWidget *editor;

  g_print ("%s (%d) : %s\n", __FILE__, __LINE__, __FUNCTION__);
  
  editor = g_script_js_editor_new ();

  gtk_widget_set_size_request (editor, -1, 200);
  //editor = gtk_entry_new ();
  //gtk_entry_set_placeholder_text (GTK_ENTRY (editor), "source");

  gtk_widget_show_all (editor);

  return editor;

  //GladeEPropScript *script = GLADE_eprop_source (eprop);
  //GtkSourceLanguageManager *manager;
  //GtkSourceLanguage *language;
  //GtkSourceBuffer *buffer;
  //GtkWidget *window;
  //GtkWidget *view;

  //window = gtk_scrolled_window_new (NULL, NULL);

  //gtk_scrolled_window_set_min_content_height (GTK_SCROLLED_WINDOW (window), 150);
  //gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (window), GTK_SHADOW_OUT);

  //manager = gtk_source_language_manager_get_default ();
  //language = gtk_source_language_manager_get_language (manager, "js");
  //buffer =  gtk_source_buffer_new_with_language (language);
  //script->editor = gtk_source_view_new_with_buffer (buffer);

  //gtk_container_add (GTK_CONTAINER (window), script->editor);

  //gtk_source_buffer_set_highlight_syntax (buffer, TRUE);
  //gtk_source_buffer_set_highlight_matching_brackets (buffer, TRUE);

  //gtk_source_view_set_show_line_numbers (GTK_SOURCE_VIEW (script->editor), TRUE);
  //gtk_source_view_set_show_line_marks (GTK_SOURCE_VIEW (script->editor), TRUE);
  //gtk_source_view_set_highlight_current_line (GTK_SOURCE_VIEW (script->editor), TRUE);
  //gtk_source_view_set_tab_width (GTK_SOURCE_VIEW (script->editor), 8);
  //gtk_source_view_set_auto_indent (GTK_SOURCE_VIEW (script->editor), TRUE);
  //gtk_source_view_set_insert_spaces_instead_of_tabs (GTK_SOURCE_VIEW (script->editor), TRUE);
  //gtk_source_view_set_show_right_margin (GTK_SOURCE_VIEW (script->editor), TRUE);
  //gtk_source_view_set_right_margin_position (GTK_SOURCE_VIEW (script->editor), 80);
  //gtk_source_view_set_smart_home_end (GTK_SOURCE_VIEW (script->editor), TRUE);

  //gtk_widget_show_all (window);

  //return window;
}
