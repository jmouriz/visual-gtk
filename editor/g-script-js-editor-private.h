/* g-script-js-editor--private.h
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

#ifndef G_SCRIPT_JS_EDITOR_PRIVATE_H
#define G_SCRIPT_JS_EDITOR_PRIVATE_H

#include <gtk/gtk.h>
#include <gtksourceview/gtksourceview.h>
#include <g-script-js.h>

G_BEGIN_DECLS

struct _GScriptJsEditorPrivate
{
  GtkListStore *store;
  GtkSourceBuffer *buffer;
  GScriptJs *script;
};

G_END_DECLS

#endif /* G_SCRIPT_JS_EDITOR_PRIVATE_H */
