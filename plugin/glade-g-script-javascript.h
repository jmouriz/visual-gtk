#ifndef GLADE_G_SCRIPT_JAVASCRIPT_H
#define GLADE_G_SCRIPT_JAVASCRIPT_H

G_BEGIN_DECLS

typedef struct
{
  GladeEditorProperty parent_instance;
  GtkWidget *editor;
} GladeEPropJavascript;

#define GLADE_EPROP_JAVASCRIPT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GLADE_TYPE_EPROP_JAVASCRIPT, GladeEPropJavascript))
#define GLADE_EPROP_JAVASCRIPT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GLADE_TYPE_EPROP_JAVASCRIPT, GladeEPropJavascriptClass))
#define GLADE_IS_EPROP_JAVASCRIPT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GLADE_TYPE_EPROP_JAVASCRIPT))
#define GLADE_IS_EPROP_JAVASCRIPT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GLADE_TYPE_EPROP_JAVASCRIPT))
#define GLADE_EPROP_JAVASCRIPT_GET_CLASS(o)    (G_TYPE_INSTANCE_GET_CLASS ((o), GLADE_EPROP_JAVASCRIPT, GladeEPropJavascriptClass))

#define GLADE_TYPE_EPROP_JAVASCRIPT (glade_eprop_javascript_get_type())

GType glade_eprop_javascript_get_type (void) G_GNUC_CONST;

void glade_g_script_set_javascript (GObject *object, const GValue *value);

G_END_DECLS

#endif /* GLADE_G_SCRIPT_JAVASCRIPT_H */
