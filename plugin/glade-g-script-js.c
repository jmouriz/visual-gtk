/* glade-g-script-js.c
 *
 * Copyright (C) 2013 Juan Manuel Mouriz <jmouriz@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <gladeui/glade.h>
#include <g-script-js.h>

#include "glade-g-script-js-filename.h"
#include "glade-g-script-js-javascript.h"

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

/* -------------------------------- ParamSpecs ------------------------------ */

/* This function does absolutely nothing
 * (and is for use in overriding post_create functions).
 */
void
empty (GObject * container, GladeCreateReason reason)
{
}

void
glade_g_script_js_set_property (GladeWidgetAdaptor *adaptor, GObject *object, const gchar *id, const GValue *value)
{
  if (!strcmp (id, "filename"))
  {
    glade_g_script_js_set_filename (object, value);
  }
  else if (!strcmp (id, "javascript"))
  {
    glade_g_script_js_set_javascript (object, value);
  }
  /*
  else
  {
    GWA_GET_CLASS (GTK_TYPE_WIDGET)->set_property (adaptor, object, id, value);
  }
  */
}

/*
void
glade_g_script_js_read_widget (GladeWidgetAdaptor *adaptor, GladeWidget *widget, GladeXmlNode *node)
{
  GladeProperty *prop;

  if (!glade_xml_node_verify (node, GLADE_XML_TAG_WIDGET))
  {
    return;
  }

  // First chain up and read in all the normal properties...
  GWA_GET_CLASS (GTK_TYPE_WIDGET)->read_widget (adaptor, widget, node);

  // Sync properties after a load...
  prop = glade_widget_get_property (widget, "filename");
  glade_g_script_js_set_filename (glade_widget_get_object (widget), glade_property_inline_value (prop));

  prop = glade_widget_get_property (widget, "javascript");
  glade_g_script_js_set_javascript (glade_widget_get_object (widget), glade_property_inline_value (prop));
}

void
glade_g_script_js_write_widget (GladeWidgetAdaptor *adaptor, GladeWidget  *widget,
                                GladeXmlContext    *context, GladeXmlNode *node)
{
  GladeXmlNode *attrs_node;

  if (!glade_xml_node_verify (node, GLADE_XML_TAG_WIDGET))
  {
    return;
  }

  // First chain up and read in all the normal properties...
  GWA_GET_CLASS (GTK_TYPE_WIDGET)->write_widget (adaptor, widget, context, node);
}
*/

GladeEditorProperty *
glade_g_script_js_create_eprop (GladeWidgetAdaptor *adaptor, GladePropertyClass *klass, gboolean use_command)
{
  GladeEditorProperty *eprop;

  /* Chain up.. */
  if (strncmp (glade_property_class_id (klass), "filename", strlen ("filename")) == 0)
  {
    eprop = g_object_new (GLADE_TYPE_EPROP_FILENAME, "property-class", klass, "use-command", use_command, NULL);
  }
  else if (strncmp (glade_property_class_id (klass), "javascript", strlen ("javascript")) == 0)
  {
    eprop = g_object_new (GLADE_TYPE_EPROP_JAVASCRIPT, "property-class", klass, "use-command", use_command, NULL);
  }
  /*
  else
  {
    eprop = GWA_GET_CLASS (GTK_TYPE_WIDGET)->create_eprop (adaptor, klass, use_command);
  }
  */

  return eprop;
}
