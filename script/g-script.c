/* g-script.c
 *
 * Copyright (C) 2011 Christian Hergert <chris@dronelabs.com>
 * Copyright (C) 2014 Juan Manuel Mouriz <jmouriz@gmail.com>
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

#include "g-script-private.h"

#include <gi/object.h>
#include <gi/closure.h>
#include <gi/value.h>
#include <glib/gi18n.h>

#include "g-script.h"
#include "g-script-function.h"

#define MODULES "/usr/share/gscript/modules"

#define G_SCRIPT_TYPE G_TYPE_SCRIPT
#define IS_G_SCRIPT   G_IS_SCRIPT

enum
{
  PROP_0,
  PROP_FILENAME,
  PROP_JAVASCRIPT,
  N_PROPERTIES
};

static GParamSpec *gParamSpecs[N_PROPERTIES];

static void     gtk_buildable_init               (GtkBuildableIface *);

static gboolean g_script_introspect_functions (GScript *);

static void     g_script_filename_free        (GScript *);

static void     g_script_javascript_free      (GScript *);

/**
 * SECTION: g-script
 * @short_description: A script runner.
 *
 * The #GScript is a blah, blah, blah...
 */
G_DEFINE_TYPE_WITH_CODE(GScript, g_script, G_TYPE_OBJECT,
                        G_IMPLEMENT_INTERFACE(GTK_TYPE_BUILDABLE,
                                              gtk_buildable_init))

/**
 * g_script_finalize:
 * @object: (in): A #GScript.
 *
 * Finalizer for a #GScript instance. Frees any resources held by
 * the instance.
 *
 * Returns: None.
 * Side effects: None.
 */
static void
g_script_finalize (GObject *object)
{
  GScript *script = G_SCRIPT (object);
  GScriptPrivate *priv = script->priv;

  g_script_free (script);

  g_clear_object (&priv->context);

  G_OBJECT_CLASS (g_script_parent_class)->finalize (object);
}

static void
g_script_functions_free (GScript *script)
{
  GScriptPrivate *priv = script->priv;

  if (priv->functions)
  {
    g_slist_free_full (priv->functions, (GDestroyNotify) g_script_function_free);
    priv->functions = NULL;
  }
}

/* estas dos funciones me hacen un poco de ruido */

static void
g_script_filename_free (GScript *script)
{
  GScriptPrivate *priv = script->priv;

  if (priv->filename)
  {
    g_free (priv->filename);
  }

  g_script_functions_free (script);
}

static void
g_script_javascript_free (GScript *script)
{
  GScriptPrivate *priv = script->priv;

  if (priv->javascript)
  {
    g_free (priv->javascript);
  }

  g_script_functions_free (script);
}

/*
 * TODO
 */
void
g_script_free (GScript *script)
{
  if (!script) return;

  g_return_if_fail (IS_G_SCRIPT (script));

  g_script_javascript_free (script);

  g_script_filename_free (script);
}

/**
 * g_script_get_closure:
 * @script: (in): A #GScript.
 * @function: (in): TODO
 *
 * TODO
 *
 * Returns: A #GClosure.
 *
 * Esta es la función mágica de Christian
 */
GClosure *
g_script_get_closure (GScript *script, const gchar *function)
{
  GScriptPrivate *priv;
  JSContext *context;
  JSObject *callable;
  GClosure *closure;
  JSObject *global;
  JSBool success;
  jsval value = { 0 };

  g_return_val_if_fail (IS_G_SCRIPT (script), NULL);

  callable = NULL;
  priv = script->priv;
  context = (JSContext *) gjs_context_get_native_context (priv->context);

  g_assert (context);

  JS_BeginRequest (context);

  global = gjs_get_import_global (context);

  g_assert (global);

  success = JS_GetProperty (context, global, function, &value);

  g_assert_cmpint (success, ==, JS_TRUE);
  g_assert (JSVAL_IS_OBJECT (value));
  g_assert (!JSVAL_IS_NULL (value));
  g_assert (!JSVAL_IS_VOID (value));

  callable = JSVAL_TO_OBJECT (value);

  g_assert (callable);
  g_assert (JS_ObjectIsFunction (context, callable));

  closure = gjs_closure_new_marshaled (context, callable, function);

  g_assert (closure);
  g_assert (gjs_closure_is_valid (closure));

  JS_EndRequest (context);

  return closure;
}

/*
 * TODO
 */
gboolean
g_script_set_javascript (GScript *script, const gchar *javascript)
{
  GScriptPrivate *priv;

  g_return_val_if_fail (IS_G_SCRIPT (script), FALSE);
  g_return_val_if_fail (javascript != NULL, FALSE);

  priv = script->priv;

  g_script_javascript_free (script);

  priv->javascript = g_strdup (javascript);

  return g_script_introspect_functions (script);
}

/*
 * TODO split in set_script and load_script
 */
gboolean
g_script_set_filename (GScript *script, const gchar *filename)
{
  GScriptPrivate *priv;
  GFile *file;
  GError *error;
  gboolean success;
  char *javascript;
  gsize length;

  g_return_val_if_fail (IS_G_SCRIPT (script), FALSE);
  g_return_val_if_fail (filename != NULL, FALSE);

  priv = script->priv;

  file = g_file_new_for_path (filename);
  error = NULL;

  success = g_file_load_contents (file, NULL, &javascript, &length, NULL, &error);

  if (success)
  {
    success = g_script_set_javascript (script, javascript);

    g_script_javascript_free (script);

    priv->filename = g_strdup (filename);
    priv->javascript = g_strdup (javascript);

    g_free (javascript);
  }
  else
  {
    g_critical ("%s", error->message);

    g_error_free (error);
  }

  return success;
}

/*
 * TODO
 */
gboolean
g_script_save (GScript *script)
{
  return FALSE;
}

/*
 * TODO
 */
gchar * /* const */
g_script_get_filename (GScript *script)
{
  g_return_val_if_fail (IS_G_SCRIPT (script), NULL);

  return script->priv->filename;
}
 
/*
 * TODO
 */
gchar *
g_script_get_javascript (GScript *script)
{
  g_return_val_if_fail (IS_G_SCRIPT (script), NULL);

  return script->priv->javascript;
}

/*
 * TODO
 */
GjsContext *
g_script_get_context (GScript *script)
{
  g_return_val_if_fail (IS_G_SCRIPT (script), NULL);

  return script->priv->context;
}

/**
 * g_script_get_functions:
 * @script: A #GScript.
 *
 * TODO
 *
 * Return value: (element-type GScript) (transfer container): A #GSList of ##GScript.
 */
GSList *
g_script_get_functions (GScript *script)
{
  g_return_val_if_fail (IS_G_SCRIPT (script), NULL);

  return script->priv->functions;
}
 
/*
 * TODO
 */
gboolean
g_script_evaluate (GScript *script)
{
  GError *error;
  gboolean success;
  gchar *javascript;
  glong length;
  const gchar *include = "var Gtk = imports.gi.Gtk;\n";

  g_return_val_if_fail (IS_G_SCRIPT (script), FALSE);

  error = NULL;
  javascript = g_strconcat (include, script->priv->javascript, NULL);
  length  = g_utf8_strlen (javascript, G_MAXLONG);

  success = gjs_context_eval (script->priv->context, javascript, length, "__gtk_builder__", NULL, &error);

  g_free (javascript);

  if (!success)
  {
    g_debug ("%s", error->message);

    g_error_free (error);

    return FALSE;
  }

  return TRUE;
}

/**
 * g_script_set_property:
 * @object: (in): A #GObject.
 * @prop_id: (in): The property identifier.
 * @value: (in): The given property.
 * @pspec: (in): A #ParamSpec.
 *
 * Set a given #GObject property.
 */
static void
g_script_set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
  GScript *script = G_SCRIPT (object);

  switch (prop_id)
  {
    case PROP_FILENAME:
    {
      const gchar *filename = g_value_get_string (value);

      if (filename)
      {
        g_script_set_filename (script, filename);
      }
      break;
    }
    case PROP_JAVASCRIPT:
    {
      const gchar *javascript = g_value_get_string (value);
  
      if (javascript)
      {
        g_script_set_javascript (script, javascript);
      }
      break;
    }
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
  }
}

/**
 * g_script_get_property:
 * @object: (in): A #GObject.
 * @prop_id: (in): The property identifier.
 * @value: (out): TODO
 * @pspec: (in): A #ParamSpec.
 *
 * Set a given #GObject property.
 */
static void
g_script_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
  GScript *script = G_SCRIPT (object);
  GScriptPrivate *priv = script->priv;

  switch (prop_id)
  {
    case PROP_FILENAME:
      g_value_set_string (value, priv->filename);
      break;
    case PROP_JAVASCRIPT:
      g_value_set_string (value, priv->javascript);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
  }
}

/**
 * g_script_new: (constructor)
 *
 * Allocates a new #GScript.
 *
 * Return value: (transfer full): A new #GScript.
 */
GScript *
g_script_new (void)
{
  return G_SCRIPT (g_object_new (G_SCRIPT_TYPE, NULL));
}

/**
 * g_script_class_init:
 * @klass: (in): A #GScriptClass.
 *
 * Initializes the #GScriptClass and prepares the vtable.
 *
 * Returns: None.
 * Side effects: None.
 */
static void
g_script_class_init (GScriptClass *klass)
{
  GObjectClass *object_class;

  object_class = G_OBJECT_CLASS (klass);
  object_class->finalize = g_script_finalize;
  object_class->set_property = g_script_set_property;
  object_class->get_property = g_script_get_property;
  g_type_class_add_private(object_class, sizeof (GScriptPrivate));

  /**
   * GScript:filename:
   *
   * A external script filename.
   */
  gParamSpecs[PROP_FILENAME] = g_param_spec_string ("filename",
                                                    _("Filename"),
                                                    _("Add script filename to evaluate."),
                                                    NULL,
                                                    G_PARAM_WRITABLE);

  /**
   * GScript:javascript:
   *
   * A internal JavaScript code to evaluate.
   */
  gParamSpecs[PROP_JAVASCRIPT] = g_param_spec_string ("javascript",
                                                      _("Javascript"),
                                                      _("Add source code to evaluate."),
                                                      NULL,
                                                      G_PARAM_WRITABLE);

  // functions RO
  g_object_class_install_property(object_class, PROP_FILENAME, gParamSpecs[PROP_FILENAME]);

  g_object_class_install_property(object_class, PROP_JAVASCRIPT, gParamSpecs[PROP_JAVASCRIPT]);
}

/**
 * g_script_init:
 * @script: (in): A #GScript.
 *
 * Initializes the newly created #GScript instance.
 *
 * Return value: None.
 */
static void
g_script_init (GScript *script)
{
  script->priv = G_TYPE_INSTANCE_GET_PRIVATE(script, G_SCRIPT_TYPE, GScriptPrivate);

  script->priv->context = gjs_context_new ();

  script->priv->functions = NULL;
  script->priv->filename = NULL;
  script->priv->javascript = NULL;
}

static void
gtk_buildable_init (GtkBuildableIface *iface)
{
}

/*
 * TODO
 */
void
g_script_set_object (GScript *script, const gchar *name, GObject *object)
{
  JSContext *context;
  JSObject *global;
  JSObject *instance;
  JSBool ok;
  jsval value;
  GScriptPrivate *priv;

  priv = script->priv;

  context = (JSContext *) gjs_context_get_native_context (priv->context);

  //JS_BeginRequest (context);

  global = gjs_get_import_global (context);
  instance = gjs_object_from_g_object (context, object);
  value = OBJECT_TO_JSVAL (instance);

  //ok = JS_DefineProperty (context, global, name, value, JS_PropertyStub, JS_StrictPropertyStub,
  //                        GJS_MODULE_PROP_FLAGS | JSPROP_READONLY);
  ok = JS_DefineProperty (context, global, name, value, NULL, NULL,
                          JSPROP_READONLY | JSPROP_PERMANENT);

  g_assert_cmpint (ok, ==, JS_TRUE);

  //JS_EndRequest (context);
}

static void
parse_functions_list (char *string, GSList **list)
{
  char *buffer;
  char *token;
  char *name;
  char *value;
  GScriptPosition start;
  GScriptPosition end;
  GScriptFunction *function;

  //*list = NULL;

  // TODO: use g_strsplit and g_strfreev instead strtok and strtok_r
  for (token = strtok_r (string, "|", &buffer); token != NULL; token = strtok_r (NULL, "|", &buffer))
  {
    name = strtok (token, ":");
    value = strtok (NULL, ":");
    start.line = atoi (value);
    value = strtok (NULL, ":");
    start.column = atoi (value);
    value = strtok (NULL, ":");
    end.line = atoi (value);
    value = strtok (NULL, ":");
    end.column = atoi (value);

    function = g_script_function_new (name, start, end);

    *list = g_slist_append (*list, (gpointer) function);
  }
}

static gboolean
g_script_introspect_functions (GScript *script)
{
  JSContext *context;
  JSObject *global;
  JSString *string;
  GError *error;
  gboolean success;
  JSBool ok;
  jsid property;
  jsval value;
  gchar *buffer;
  glong length;
  GScriptPrivate *priv;

  const gchar *path = g_getenv ("GSCRIPT_MODULE_SEARCH_PATH");

  if (!path)
  {
    path = MODULES;
  }

  /* javascript reflection code to parse script */
  const gchar *javascript = "var a=p.split(':');for(var j in a){imports.searchPath.unshift("
                            "a[j])}var m=imports.parser;function i(n){return n.id.name+':'+"
                            "n.loc.start.line+':'+n.loc.start.column+':'+n.loc.end.line+':'"
                            "+n.loc.end.column}var r=m.parse(c,{loc:true});var s='';for(var"
                            " e in r.body){var n=r.body[e];if(n.type=='VariableDeclaration'"
                            ")for(e in n.declarations){var d=n.declarations[e];if(d.init.ty"
                            "pe=='FunctionExpression')s+=i(d)+'|'}else if(n.type=='Function"
                            "Declaration')s+=i(n)+'|'}";

  priv = script->priv;

  g_return_val_if_fail (priv->javascript != NULL, FALSE);

  g_script_functions_free (script);

  context = (JSContext *) gjs_context_get_native_context (priv->context);

  JS_BeginRequest (context);

  global = gjs_get_import_global (context);

  /* set external parser module path */
  length = g_utf8_strlen (path, G_MAXLONG);
  success = gjs_string_from_utf8 (context, path, (gssize) length, &value);

  g_assert_cmpint (success, ==, TRUE);

  ok = JS_DefineProperty (context, global, "p", value, JS_PropertyStub, JS_StrictPropertyStub,
                          GJS_MODULE_PROP_FLAGS | JSPROP_READONLY);

  g_assert_cmpint (ok, ==, JS_TRUE);

  /* set code to parse */
  length = g_utf8_strlen (priv->javascript, G_MAXLONG);
  success = gjs_string_from_utf8 (context, priv->javascript, (gssize) length, &value);

  g_assert_cmpint (success, ==, TRUE);

  ok = JS_DefineProperty (context, global, "c", value, JS_PropertyStub, JS_StrictPropertyStub,
                          GJS_MODULE_PROP_FLAGS | JSPROP_READONLY);

  g_assert_cmpint (ok, ==, JS_TRUE);

  /* run code (parse script) */
  error = NULL;
  length = g_utf8_strlen (javascript, G_MAXLONG);
  success = gjs_context_eval (priv->context, javascript, length, "__gtk_builder_internal__", NULL, &error);

  if (!success)
  {
    if (error)
    {
      g_debug ("%s", error->message);

      g_error_free (error);
    }

    return FALSE;
  }

  /* get result (functions list) */
  string = JS_InternString (context, "s");
  property = INTERNED_STRING_TO_JSID (string);
  ok = JS_GetPropertyById (context, global, property, &value);

  g_assert_cmpint (ok, ==, JS_TRUE);
  g_assert (JSVAL_IS_STRING (value));
  g_assert (!JSVAL_IS_NULL (value));
  g_assert (!JSVAL_IS_VOID (value));

  success = gjs_string_to_utf8 (context, value, &buffer);

  g_assert_cmpint (success, ==, TRUE);

  /* load internal functions list from parser result */
  parse_functions_list (buffer, &priv->functions);

  free (buffer);

  JS_EndRequest (context);

  return TRUE;
}
