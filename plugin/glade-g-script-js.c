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

//#include "glade-g-script-js-editor.h"
#include "glade-g-script-js-script.h"
#include "glade-g-script-js-source.h"

//#include <gladeui/glade-editor-property.h>
//#include <gladeui/glade-base-editor.h>
//#include <gladeui/glade-xml-utils.h>

#include <g-script-js.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

static void glade_g_script_js_set_script (GObject *, const GValue *);
static void glade_g_script_js_set_source (GObject *, const GValue *);

/* -------------------------------- ParamSpecs ------------------------------ */
/* This function does absolutely nothing
 * (and is for use in overriding post_create functions).
 */
void
empty (GObject * container, GladeCreateReason reason)
{
}

/* This function is used to stop default handlers  */
static void
glade_gtk_stop_emission_POINTER (gpointer instance, gpointer dummy, gpointer data)
{
  g_signal_stop_emission (instance, GPOINTER_TO_UINT (data), 0);
}

/* Initialize needed pspec types from here */
void
glade_g_script_js_init (const gchar *name)
{
  g_print("Registering type: %s\n", g_type_name(G_TYPE_SCRIPT_JS));
  g_print("Initializing %s\n", name);
  //gtk_init(NULL, NULL);
  //g_debug("Registering type: %s", g_type_name(G_TYPE_SCRIPT_JS));
}

/* ----------------------------- GScriptJs ------------------------------ */
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
  if (!strcmp (id, "script"))
  {
    glade_g_script_js_set_script (object, value);
  }
  else if (!strcmp (id, "source"))
  {
    glade_g_script_js_set_source (object, value);
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

  /* First chain up and read in all the normal properties.. */
  GWA_GET_CLASS (GTK_TYPE_WIDGET)->read_widget (adaptor, widget, node);

  /* sync script property after a load... */
  prop = glade_widget_get_property (widget, "script");
  glade_g_script_js_set_script (glade_widget_get_object (widget), glade_property_inline_value (prop));

  /* sync source property after a load... */
  prop = glade_widget_get_property (widget, "source");
  glade_g_script_js_set_source (glade_widget_get_object (widget), glade_property_inline_value (prop));
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
  if (strncmp (glade_property_class_id (klass), "script", strlen ("script")) == 0)
  {
    eprop = g_object_new (GLADE_TYPE_EPROP_SCRIPT, "property-class", klass, "use-command", use_command, NULL);
  }
  else if (strncmp (glade_property_class_id (klass), "source", strlen ("source")) == 0)
  {
    eprop = g_object_new (GLADE_TYPE_EPROP_SOURCE, "property-class", klass, "use-command", use_command, NULL);
  }
  else
  {
    eprop = GWA_GET_CLASS (GTK_TYPE_WIDGET)->create_eprop (adaptor, klass, use_command);
  }

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
*/

static void
glade_g_script_js_set_script (GObject *object, const GValue *value)
{
  GladeWidget *widget;

  widget = glade_widget_get_from_gobject (object);

  if (g_value_get_string (value) == NULL)
  {
    return;
  }

  g_script_js_set_script (G_SCRIPT_JS (object), g_value_get_string (value));
}

static void
glade_g_script_js_set_source (GObject *object, const GValue *value)
{
  GladeWidget *widget;

  widget = glade_widget_get_from_gobject (object);

  if (g_value_get_string (value) == NULL)
  {
    return;
  }

  g_script_js_set_source (G_SCRIPT_JS (object), g_value_get_string (value));
}
