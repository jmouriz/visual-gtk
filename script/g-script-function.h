/* g-script-function.h
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

#ifndef G_SCRIPT_FUNCTION_H
#define G_SCRIPT_FUNCTION_H

#include <glib-object.h>

G_BEGIN_DECLS

#define G_SCRIPT_FUNCTION(object) ((GScriptFunction *) object)

typedef struct _GScriptPosition
{
  gint line;
  gint column;
} GScriptPosition;

typedef struct _GScriptFunction
{
  gchar *name;
  GScriptPosition start;
  GScriptPosition end;
} GScriptFunction;

GScriptFunction *g_script_function_new  (const gchar       *name,
                                              GScriptPosition  start,
                                              GScriptPosition  end);

void               g_script_function_free (GScriptFunction *function);

G_END_DECLS

#endif /* G_SCRIPT_FUNCTION_H */
