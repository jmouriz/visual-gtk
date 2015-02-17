/* g-script-js.h
 *
 * Copyright (C) 2011 Christian Hergert <chris@dronelabs.com>
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

#ifndef G_SCRIPT_JS_H
#define G_SCRIPT_JS_H

#include <glib-object.h>

G_BEGIN_DECLS

#define G_TYPE_SCRIPT_JS            (g_script_js_get_type())
#define G_SCRIPT_JS(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_SCRIPT_JS, GScriptJs))
#define G_SCRIPT_JS_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_SCRIPT_JS, GScriptJs const))
#define G_SCRIPT_JS_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  G_TYPE_SCRIPT_JS, GScriptJsClass))
#define G_IS_SCRIPT_JS(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_SCRIPT_JS))
#define G_IS_SCRIPT_JS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  G_TYPE_SCRIPT_JS))
#define G_SCRIPT_JS_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  G_TYPE_SCRIPT_JS, GScriptJsClass))

typedef struct _GScriptJs        GScriptJs;
typedef struct _GScriptJsClass   GScriptJsClass;
typedef struct _GScriptJsPrivate GScriptJsPrivate;

struct _GScriptJs
{
  GObject parent;

  /*< private >*/
  GScriptJsPrivate *priv;
};

struct _GScriptJsClass
{
  GObjectClass parent_class;
};

GType         g_script_js_get_type       (void) G_GNUC_CONST;

GScriptJs    *g_script_js_new            (void);

void          g_script_js_free           (GScriptJs *script);

GClosure     *g_script_js_get_closure    (GScriptJs   *script,
                                          const gchar *function);

gboolean      g_script_js_set_filename   (GScriptJs   *script,
                                          const gchar *filename);

gboolean      g_script_js_set_javascript (GScriptJs   *script,
                                          const gchar *javascript);

gchar        *g_script_js_get_filename   (GScriptJs   *script);

gchar        *g_script_js_get_javascript (GScriptJs   *script);

GSList       *g_script_js_get_functions  (GScriptJs   *script);

void          g_script_js_set_object     (GScriptJs   *script,
                                          const gchar *name,
                                          GObject     *object);

gboolean      g_script_js_save           (GScriptJs   *script);

gboolean      g_script_js_evaluate       (GScriptJs   *script);

G_END_DECLS

#endif /* G_SCRIPT_JS_H */
