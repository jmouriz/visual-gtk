/* g-script.h
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

#ifndef G_SCRIPT_H
#define G_SCRIPT_H

#include <glib-object.h>

G_BEGIN_DECLS

#define G_TYPE_SCRIPT_JS            (g_script_get_type())
#define G_SCRIPT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_SCRIPT_JS, GScript))
#define G_SCRIPT_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_SCRIPT_JS, GScript const))
#define G_SCRIPT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  G_TYPE_SCRIPT_JS, GScriptClass))
#define G_IS_SCRIPT_JS(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_SCRIPT_JS))
#define G_IS_SCRIPT_JS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  G_TYPE_SCRIPT_JS))
#define G_SCRIPT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  G_TYPE_SCRIPT_JS, GScriptClass))

typedef struct _GScript        GScript;
typedef struct _GScriptClass   GScriptClass;
typedef struct _GScriptPrivate GScriptPrivate;

struct _GScript
{
  GObject parent;

  /*< private >*/
  GScriptPrivate *priv;
};

struct _GScriptClass
{
  GObjectClass parent_class;
};

GType         g_script_get_type       (void) G_GNUC_CONST;

GScript    *g_script_new            (void);

void          g_script_free           (GScript *script);

GClosure     *g_script_get_closure    (GScript   *script,
                                          const gchar *function);

gboolean      g_script_set_filename   (GScript   *script,
                                          const gchar *filename);

gboolean      g_script_set_javascript (GScript   *script,
                                          const gchar *javascript);

gchar        *g_script_get_filename   (GScript   *script);

gchar        *g_script_get_javascript (GScript   *script);

GSList       *g_script_get_functions  (GScript   *script);

void          g_script_set_object     (GScript   *script,
                                          const gchar *name,
                                          GObject     *object);

gboolean      g_script_save           (GScript   *script);

gboolean      g_script_evaluate       (GScript   *script);

G_END_DECLS

#endif /* G_SCRIPT_H */
