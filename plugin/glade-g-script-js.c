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

#include "glade-g-script-js.h"
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

/* This function is used to stop default handlers  */ // (-?-)
static void
glade_gtk_stop_emission_POINTER (gpointer instance, gpointer dummy, gpointer data)
{
  g_signal_stop_emission (instance, GPOINTER_TO_UINT (data), 0);
}

/* ----------------------------- GScriptJs ------------------------------ */

/* Initialize needed pspec types from here */
/*
void
glade_g_script_js_init (const gchar *name)
{
  //g_print("Registering type: %s\n", g_type_name(G_TYPE_SCRIPT_JS));
  //g_print("Initializing %s\n", name);
  //gtk_init(NULL, NULL);
  //g_debug("Registering type: %s", g_type_name(G_TYPE_SCRIPT_JS));
}
*/

/*
void
glade_g_script_js_post_create (GladeWidgetAdaptor *adaptor, GObject *object, GladeCreateReason reason)
{
  //GladeWidget *glabel = glade_widget_get_from_gobject (object); //(?)

  gtk_container_add (GTK_CONTAINER (object), gtk_label_new ("[ editor ]"));

  gtk_widget_show_all (GTK_WIDGET (object));

  //if (reason == GLADE_CREATE_USER)
  //{
  //  glade_widget_property_set_sensitive (glabel, "mnemonic-widget", FALSE, MNEMONIC_INSENSITIVE_MSG);
  //}
}
*/

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
  else
  {
    GWA_GET_CLASS (GTK_TYPE_WIDGET)->set_property (adaptor, object, id, value);
  }
}

void
glade_g_script_js_read_widget (GladeWidgetAdaptor *adaptor, GladeWidget *widget, GladeXmlNode *node)
{
  GladeProperty *prop;

  if (!glade_xml_node_verify (node, GLADE_XML_TAG_WIDGET))
  {
    return;
  }

  /* First chain up and read in all the normal properties... */
  GWA_GET_CLASS (GTK_TYPE_WIDGET)->read_widget (adaptor, widget, node); /* (?) */

  /* sync filename property after a load... */
  prop = glade_widget_get_property (widget, "filename");
  glade_g_script_js_set_filename (glade_widget_get_object (widget), glade_property_inline_value (prop));

  /* sync javascript property after a load... */
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

  /* First chain up and read in all the normal properties.. */
  GWA_GET_CLASS (GTK_TYPE_WIDGET)->write_widget (adaptor, widget, context, node);
}

/*
gchar *
glade_g_script_js_string_from_value (GladeWidgetAdaptor *adaptor, GladePropertyClass *klass, const GValue *value)
{
  return GWA_GET_CLASS (GTK_TYPE_WIDGET)->string_from_value (adaptor, klass, value);
}
*/

GladeEditorProperty *
glade_g_script_js_create_eprop (GladeWidgetAdaptor *adaptor, GladePropertyClass *klass, gboolean use_command)
{
  GladeEditorProperty *eprop;

  g_print ("%s (%d) : %s (%s)\n", __FILE__, __LINE__, __FUNCTION__, glade_property_class_id (klass));

  /* chain up.. */
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

  g_object_set_data (G_OBJECT (eprop), "adaptor", adaptor);

  return eprop;
}

/*
GladeEditable *
glade_g_script_js_create_editable (GladeWidgetAdaptor *adaptor, GladeEditorPageType type)
{
  GladeEditable *editable;

  editable = GWA_GET_CLASS (GTK_TYPE_WIDGET)->create_editable (adaptor, type);

  if (GLADE_PAGE_GENERAL == type)
  {
    //return (GladeEditable *) glade_g_script_js_editor_new (adaptor, editable);
  }

  return editable;
}

GladeWidget *
glade_g_script_js_create_widget (GladeWidgetAdaptor *adaptor, gchar *property, va_list properties)
{
  g_print ("%s (%d) : %s\n", __FILE__, __LINE__, __FUNCTION__);

  return GLADE_WIDGET (g_object_new_valist (GLADE_TYPE_WIDGET, property, properties));
}
*/

void
glade_g_script_js_post_create (GladeWidgetAdaptor *adaptor, GObject *object, GladeCreateReason reason)
{
  if (reason == GLADE_CREATE_USER)
  {
    g_print ("%s (%d) : %s\n", __FILE__, __LINE__, __FUNCTION__);
  }
}
