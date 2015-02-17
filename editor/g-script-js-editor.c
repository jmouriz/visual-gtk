/* g-script-js-editor.c
 *
 * Copyright (C) 2013 Juan Manuel Mouriz <jmouriz@gmail.com>
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

#include "g-script-js-editor-private.h"
#include "g-script-js-editor.h"

#include <gtksourceview/gtksource.h>
#include <g-script-js-function.h>
#include <glib/gi18n.h>

enum
{
  EDITED_SIGNAL_HANDLER,
  LAST_SIGNAL
};

enum
{
  PROP_0,
  PROP_JAVASCRIPT,
  PROP_LAST
};

static GParamSpec *properties[PROP_LAST];
static guint signals[LAST_SIGNAL] = { 0 };

static void g_script_js_editor_finalize (GObject *);

static void fill_store (GScriptJsEditorPrivate *);

static void move (GtkTextView *, GtkMovementStep, gint, gboolean, gpointer);

static void modified (GtkTextBuffer *, gpointer);

static void changed (GtkComboBox *, gpointer);

static gboolean release (GtkWidget *, GdkEvent *, gpointer);

static void g_script_js_editor_set_property (GObject *, guint, const GValue *, GParamSpec *);

static gboolean _rewind = TRUE;

typedef struct _Data
{
  GScriptJsEditorPrivate *priv;
  GScriptJsEditor *self;
  GtkWidget *combo;
  GtkWidget *editor;
} Data;

#define DATA(object) ((Data *) (object))

G_DEFINE_TYPE (GScriptJsEditor, g_script_js_editor, GTK_TYPE_FRAME);

static void
g_script_js_editor_class_init (GScriptJsEditorClass *klass)
{
  GObjectClass *object_class;
  //GtkWidgetClass *widget_class;

  object_class = G_OBJECT_CLASS (klass);
  //widget_class = GTK_WIDGET_CLASS (klass);

  object_class->finalize = g_script_js_editor_finalize;
  object_class->set_property = g_script_js_editor_set_property;
  //object_class->get_property = g_script_js_editor_get_property;
  g_type_class_add_private (object_class, sizeof (GScriptJsEditorPrivate));

  /* TODO */
  properties[PROP_JAVASCRIPT] = g_param_spec_string ("javascript",
                                                     _("Javascript"),
                                                     _("Add javascript source code to edit."),
                                                     NULL,
                                                     G_PARAM_WRITABLE);

  /* TODO */
  g_object_class_install_property (object_class, PROP_JAVASCRIPT, properties[PROP_JAVASCRIPT]);

  signals[EDITED_SIGNAL_HANDLER] = g_signal_new ("edited",
                                                 G_TYPE_FROM_CLASS (object_class),
                                                 G_SIGNAL_RUN_LAST,
                                                 G_STRUCT_OFFSET (GScriptJsEditorClass, edited),
                                                 NULL,
                                                 NULL,
                                                 g_cclosure_marshal_VOID__STRING,
                                                 G_TYPE_NONE,
                                                 1,
                                                 G_TYPE_STRING);
}


/**
 * g_script_js_editor__finalize:
 *
 * TODO
 */
static void
g_script_js_editor_finalize (GObject *object)
{
  GScriptJsEditor *editor = G_SCRIPT_JS_EDITOR (object);
  GScriptJsEditorPrivate *priv = editor->priv;

  g_script_js_free (priv->script);

  //G_OBJECT_CLASS (g_script_js_editor__parent_class)->finalize (object);
}

/**
 * g_script_js_editor_init:
 * TODO
 */
static void
g_script_js_editor_init (GScriptJsEditor *editor)
{
  GtkSourceLanguageManager *manager;
  GtkSourceLanguage *language;

  editor->priv = G_TYPE_INSTANCE_GET_PRIVATE ((editor), G_TYPE_SCRIPT_JS_EDITOR, GScriptJsEditorPrivate);

  manager = gtk_source_language_manager_get_default ();
  language = gtk_source_language_manager_get_language (manager, "js");

  editor->priv->script = g_script_js_new ();
  editor->priv->store =  gtk_list_store_new (5, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT);
  editor->priv->buffer =  gtk_source_buffer_new_with_language (language);
}

/*
 * TODO
 */
GtkWidget *
g_script_js_editor_new (void)
{
  //GtkWidget *combo;
  GtkWidget *box;
  GtkWidget *area;
  GtkCellRenderer *cell;
  GScriptJsEditor *editor;
  //GScriptJsEditorPrivate *priv;
  Data *data;

  data = (Data *) g_malloc (sizeof (Data));
  editor = (GScriptJsEditor *) g_object_new (G_TYPE_SCRIPT_JS_EDITOR, NULL);
  data->self = editor;
  data->priv = editor->priv;

  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 3);

  data->combo = gtk_combo_box_new_with_model (GTK_TREE_MODEL (data->priv->store));

  cell = gtk_cell_renderer_text_new ();
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (data->combo), cell, TRUE);
  gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (data->combo), cell, "text", 0, NULL);

  area = gtk_scrolled_window_new (NULL, NULL);

  data->editor = gtk_source_view_new_with_buffer (data->priv->buffer);

  gtk_widget_set_events (data->editor, 0);
  gtk_widget_set_events (data->editor, GDK_BUTTON_RELEASE_MASK);

  gtk_text_buffer_set_modified (GTK_TEXT_BUFFER (data->priv->buffer), FALSE);

  g_signal_connect (G_OBJECT (data->combo), "changed", G_CALLBACK (changed), data->editor);
  g_signal_connect_after (G_OBJECT (data->editor), "move-cursor", G_CALLBACK (move), data->combo);
  g_signal_connect (G_OBJECT (data->editor), "button-release-event", G_CALLBACK (release), data->combo);
  g_signal_connect (G_OBJECT (data->priv->buffer), "modified-changed", G_CALLBACK (modified), (gpointer) data);

  gtk_source_buffer_set_highlight_syntax (data->priv->buffer, TRUE);
  gtk_source_buffer_set_highlight_matching_brackets (data->priv->buffer, TRUE);

  gtk_source_view_set_show_line_numbers (GTK_SOURCE_VIEW (data->editor), TRUE);
  gtk_source_view_set_show_line_marks (GTK_SOURCE_VIEW (data->editor), TRUE);
  gtk_source_view_set_highlight_current_line (GTK_SOURCE_VIEW (data->editor), TRUE);
  gtk_source_view_set_tab_width (GTK_SOURCE_VIEW (data->editor), 8);
  gtk_source_view_set_auto_indent (GTK_SOURCE_VIEW (data->editor), TRUE);
  gtk_source_view_set_insert_spaces_instead_of_tabs (GTK_SOURCE_VIEW (data->editor), TRUE);
  gtk_source_view_set_show_right_margin (GTK_SOURCE_VIEW (data->editor), TRUE);
  gtk_source_view_set_right_margin_position (GTK_SOURCE_VIEW (data->editor), 80);
  //gtk_source_view_set_smart_home_end (GTK_SOURCE_VIEW (data->editor), TRUE);
  
  gtk_box_pack_start (GTK_BOX (box), data->combo, FALSE, FALSE, 0);
  gtk_container_add (GTK_CONTAINER (area), data->editor);
  gtk_box_pack_start (GTK_BOX (box), area, TRUE, TRUE, 0);
  gtk_container_add (GTK_CONTAINER (editor), box);

  gtk_widget_grab_focus (data->editor);
 
  //gtk_widget_show_all (editor);

  return GTK_WIDGET (editor);
}

/*
 * TODO
 */
gboolean
g_script_js_editor_set_javascript (GScriptJsEditor *editor, const gchar *javascript)
{
  GScriptJsEditorPrivate *priv;
  GtkTextIter cursor;

  g_return_val_if_fail (G_IS_SCRIPT_JS_EDITOR (editor), FALSE);

  priv = editor->priv;

  fill_store (priv);
  //g_object_unref (priv->store);
  gtk_text_buffer_set_text (GTK_TEXT_BUFFER (priv->buffer), javascript, -1);

  gtk_text_buffer_get_start_iter (GTK_TEXT_BUFFER (priv->buffer), &cursor);
  gtk_text_buffer_place_cursor (GTK_TEXT_BUFFER (priv->buffer), &cursor);

  //gtk_text_view_place_cursor_onscreen (GTK_TEXT_VIEW (view));

  g_script_js_set_javascript (priv->script, javascript);

  return TRUE;
}

/*
 * TODO
 */
const gchar *
g_script_js_editor_get_javascript (GScriptJsEditor *editor)
{
  g_return_val_if_fail (G_IS_SCRIPT_JS_EDITOR (editor), FALSE);

  return g_script_js_get_javascript (editor->priv->script);
}

static void
modified (GtkTextBuffer *buffer, gpointer data)
{
  GScriptJsEditor *self;
  GtkWidget *combo;
  GtkWidget *editor;
  GtkTextIter start;
  GtkTextIter end;
  GScriptJsEditorPrivate *priv;
  gboolean modified;
  gchar *javascript;

  modified = gtk_text_buffer_get_modified (buffer);

  if (!modified)
  {
    return;
  }

  priv = DATA (data)->priv;
  self = DATA (data)->self;
  combo = DATA (data)->combo;
  editor = DATA (data)->editor;

  gtk_text_buffer_get_bounds (buffer, &start, &end);

  javascript = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);

  g_script_js_set_javascript (priv->script, javascript);

  fill_store (priv);

  //_rewind = FALSE;
  //gtk_combo_box_set_active (GTK_COMBO_BOX (combo), 0);
  move (GTK_TEXT_VIEW (editor), GTK_MOVEMENT_DISPLAY_LINES, 0, FALSE, combo);

  g_signal_emit (self, signals[EDITED_SIGNAL_HANDLER], 0, javascript);

  g_free (javascript);

  gtk_text_buffer_set_modified (buffer, FALSE);
}

static void
changed (GtkComboBox *combo, gpointer view)
{
  GtkTreeIter active;
  GtkTextIter cursor;
  GtkTreeModel *model;
  GtkTextBuffer *buffer;
  gboolean success;
  gint line;
  gint column;

  model = gtk_combo_box_get_model (combo);

  success = gtk_combo_box_get_active_iter (combo, &active);

  if (!success)
  {
    return;
  }

  gtk_tree_model_get (model, &active, 1, &line, 2, &column, -1);

  buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

  if (line == 0)
  {
    gtk_text_buffer_get_start_iter (GTK_TEXT_BUFFER (buffer), &cursor);
  }
  else
  {
    gtk_text_buffer_get_iter_at_line_offset (buffer, &cursor, line - 1, column);
  }

  if (_rewind)
  {
    (void) gtk_text_view_scroll_to_iter (GTK_TEXT_VIEW (view), &cursor, 0.0, FALSE, 0.0, 0.0);

    gtk_text_view_place_cursor_onscreen (GTK_TEXT_VIEW (view));

    gtk_text_buffer_place_cursor (buffer, &cursor);
  }
  else
  {
    _rewind = TRUE;
  }

  gtk_widget_grab_focus (GTK_WIDGET (view));
}

static gboolean
release (GtkWidget *editor, GdkEvent *event, gpointer combo)
{
  move (GTK_TEXT_VIEW (editor), GTK_MOVEMENT_DISPLAY_LINES, 0, FALSE, combo);

  return FALSE;
}

static void
move (GtkTextView *editor, GtkMovementStep step, gint count, gboolean select, gpointer combo)
{
  GtkTextMark *mark;
  GtkTextIter cursor;
  GtkTextBuffer *buffer;
  GtkTreeModel *model;
  GtkTreeIter node;
  gboolean success;
  gint index;
  gint last;
  GScriptJsPosition start;
  GScriptJsPosition end;
  gint line;
  gint column;

  buffer = gtk_text_view_get_buffer (editor);

  mark = gtk_text_buffer_get_insert (GTK_TEXT_BUFFER (buffer));

  gtk_text_buffer_get_iter_at_mark (GTK_TEXT_BUFFER (buffer), &cursor, mark);

  line = gtk_text_iter_get_line (&cursor) + 1;
  column = gtk_text_iter_get_line_offset (&cursor);

  model = gtk_combo_box_get_model (GTK_COMBO_BOX (combo));

  last = 1;
  index = -1;

  success = gtk_tree_model_get_iter_first (model, &node);

  if (!success)
  {
    g_warning ("Functions list is empty but it must contains almost one element for \"global\" context.");

    return;
  }

  while ((success = gtk_tree_model_iter_next (model, &node)))
  {
    gtk_tree_model_get (model, &node, 1, &start.line, 2, &start.column, 3, &end.line, 4, &end.column, -1);

    if ((line > start.line && line < end.line) ||
       ((line == start.line && column >= start.column) ||
       (line == end.line && column <= end.column)))
    {
      index = last;

      break;
    }

    last++;
  }

  g_signal_handlers_disconnect_by_func ((gpointer) combo, changed, editor);
  _rewind = FALSE;
  gtk_combo_box_set_active (GTK_COMBO_BOX (combo), index == -1 ? 0 : index);
  g_signal_connect (G_OBJECT (combo), "changed", G_CALLBACK (changed), editor);
}

static void
fill_store (GScriptJsEditorPrivate *priv)
{
  GScriptJsFunction *function;
  GSList *functions;
  GSList *node;

  functions = g_script_js_get_functions (priv->script);

  if (functions)
  {
    gtk_list_store_clear (priv->store);

    gtk_list_store_insert_with_values (priv->store, NULL, -1, 0, "global", 1, 0, 2, 0, 3, 0, 4, 0, -1);

    for (node = functions; node != NULL; node = g_slist_next (node))
    {
      function = G_SCRIPT_JS_FUNCTION (node->data);

      gtk_list_store_insert_with_values (priv->store, NULL, -1,
                                         0, function->name,
                                         1, function->start.line,
                                         2, function->start.column,
                                         3, function->end.line,
                                         4, function->end.column,
                                         -1);
    }
  }
}

/**
 * g_script_editor_js_set_property:
 * @object: (in): A #GObject.
 * @prop_id: (in): The property identifier.
 * @value: (in): The given property.
 * @pspec: (in): A #ParamSpec.
 *
 * Set a given #GObject property.
 */
static void
g_script_js_editor_set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
  GScriptJsEditor *editor = G_SCRIPT_JS_EDITOR (object);
  GScriptJsEditorPrivate *priv = editor->priv;

  switch (prop_id)
  {
    case PROP_JAVASCRIPT:
    {
      const gchar *javascript = g_value_get_string (value);
  
      if (javascript)
      {
        g_script_js_set_javascript (priv->script, javascript);
      }
      break;
    }
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
  }
}
