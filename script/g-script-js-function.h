/* g-script-js-function.h
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

#ifndef G_SCRIPT_JS_FUNCTION_H
#define G_SCRIPT_JS_FUNCTION_H

#include <glib-object.h>

G_BEGIN_DECLS

#define G_SCRIPT_JS_FUNCTION(object) ((GScriptJsFunction *) object)

typedef struct _GScriptJsPosition
{
  gint line;
  gint column;
} GScriptJsPosition;

typedef struct _GScriptJsFunction
{
  gchar *name;
  GScriptJsPosition start;
  GScriptJsPosition end;
} GScriptJsFunction;

GScriptJsFunction *g_script_js_function_new  (const gchar       *name,
                                              GScriptJsPosition  start,
                                              GScriptJsPosition  end);

void               g_script_js_function_free (GScriptJsFunction *function);

G_END_DECLS

#endif /* G_SCRIPT_JS_FUNCTION_H */
