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

GType         g_script_js_get_type      (void) G_GNUC_CONST;

GScriptJs    *g_script_js_new           (void);

void          g_script_js_free          (GScriptJs *js);

GClosure     *g_script_js_get_closure   (GScriptJs   *js,
                                         const gchar *function);

gboolean      g_script_js_set_script    (GScriptJs   *js,
                                         const gchar *script);

gboolean      g_script_js_set_source    (GScriptJs   *js,
                                         const gchar *source);

gchar        *g_script_js_get_script    (GScriptJs   *js);

gchar        *g_script_js_get_source    (GScriptJs   *js);

GSList       *g_script_js_get_functions (GScriptJs   *js);

void          g_script_js_set_object    (GScriptJs   *js,
                                         const gchar *name,
                                         GObject     *object);

gboolean      g_script_js_save          (GScriptJs   *js);

gboolean      g_script_js_evaluate      (GScriptJs   *js);

G_END_DECLS

#endif /* G_SCRIPT_JS_H */
