/* g-script-util.h
 *
 * Copyright (C) 2015 Juan Manuel Mouriz <jmouriz@gmail.com>
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

#ifndef G_SCRIPT_UTIL_H
#define G_SCRIPT_UTIL_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

void g_script_util_connect (GtkBuilder *builder);

void g_script_module_init  (void);

G_END_DECLS

#endif /* G_SCRIPT_UTIL_H */
