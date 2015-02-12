/* g-script-js-editor.h
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

#ifndef G_SCRIPT_JS_EDITOR_H
#define G_SCRIPT_JS_EDITOR_H

#include <gtk/gtk.h>
#include <g-script-js.h>

G_BEGIN_DECLS

#define G_TYPE_SCRIPT_JS_EDITOR            (g_script_js_editor_get_type())
#define G_SCRIPT_JS_EDITOR(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_SCRIPT_JS_EDITOR, GScriptJsEditor))
#define G_SCRIPT_JS_EDITOR_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_SCRIPT_JS_EDITOR, GScriptJsEditor const))
#define G_SCRIPT_JS_EDITOR_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  G_TYPE_SCRIPT_JS_EDITOR, GScriptJsEditorClass))
#define G_IS_SCRIPT_JS_EDITOR(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_SCRIPT_JS_EDITOR))
#define G_IS_SCRIPT_JS_EDITOR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  G_TYPE_SCRIPT_JS_EDITOR))
#define G_SCRIPT_JS_EDITOR_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  G_TYPE_SCRIPT_JS_EDITOR, GScriptJsEditorClass))

typedef struct _GScriptJsEditor        GScriptJsEditor;
typedef struct _GScriptJsEditorClass   GScriptJsEditorClass;
typedef struct _GScriptJsEditorPrivate GScriptJsEditorPrivate;

struct _GScriptJsEditor
{
  GtkBox parent;

  /*< private >*/
  GScriptJsEditorPrivate *priv;
};

struct _GScriptJsEditorClass
{
  GtkBoxClass parent_class;
};

GType            g_script_js_editor_get_type      (void) G_GNUC_CONST;

GtkWidget       *g_script_js_editor_new           (void);

void             g_script_js_editor_free          (GScriptJsEditor *js);

gboolean         g_script_js_editor_set_script    (GScriptJsEditor *editor,
                                                   GScriptJs       *script);

G_END_DECLS

#endif /* G_SCRIPT_JS_EDITOR_H */
