/* g-script-editor.h
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

#ifndef G_SCRIPT_EDITOR_H
#define G_SCRIPT_EDITOR_H

#include <gtk/gtk.h>
#include <g-script.h>

G_BEGIN_DECLS

#define G_TYPE_SCRIPT_EDITOR            (g_script_editor_get_type())
#define G_SCRIPT_EDITOR(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_SCRIPT_EDITOR, GScriptEditor))
#define G_SCRIPT_EDITOR_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_SCRIPT_EDITOR, GScriptEditor const))
#define G_SCRIPT_EDITOR_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  G_TYPE_SCRIPT_EDITOR, GScriptEditorClass))
#define G_IS_SCRIPT_EDITOR(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_SCRIPT_EDITOR))
#define G_IS_SCRIPT_EDITOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  G_TYPE_SCRIPT_EDITOR))
#define G_SCRIPT_EDITOR_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  G_TYPE_SCRIPT_EDITOR, GScriptEditorClass))

typedef struct _GScriptEditor        GScriptEditor;
typedef struct _GScriptEditorClass   GScriptEditorClass;
typedef struct _GScriptEditorPrivate GScriptEditorPrivate;

struct _GScriptEditor
{
  GtkFrame parent;

  /*< private >*/
  GScriptEditorPrivate *priv;
};

struct _GScriptEditorClass
{
  GtkFrameClass parent_class;

  void (*edited) (GScriptEditor *, const gchar *);
};

GType            g_script_editor_get_type       (void) G_GNUC_CONST;

GtkWidget       *g_script_editor_new            (void);

void             g_script_editor_free           (GScriptEditor *editor);

gboolean         g_script_editor_set_javascript (GScriptEditor *editor,
                                                 const gchar   *javascript);

const gchar     *g_script_editor_get_javascript (GScriptEditor *editor);

G_END_DECLS

#endif /* G_SCRIPT_EDITOR_H */
