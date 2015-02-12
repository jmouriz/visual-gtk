typedef struct
{
  GladeEditorProperty parent_instance;
  GladeNameContext *context;

  GtkWidget *editor;
} GladeEPropScript;

//GLADE_MAKE_EPROP (GladeEPropScript, glade_eprop_script)

#define GLADE_EPROP_SCRIPT(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GLADE_TYPE_EPROP_SCRIPT, GladeEPropScript))
#define GLADE_EPROP_SCRIPT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GLADE_TYPE_EPROP_SCRIPT, GladeEPropScriptClass))
#define GLADE_IS_EPROP_SCRIPT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GLADE_TYPE_EPROP_SCRIPT))
#define GLADE_IS_EPROP_SCRIPT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GLADE_TYPE_EPROP_SCRIPT))
#define GLADE_EPROP_SCRIPT_GET_CLASS(o)    (G_TYPE_INSTANCE_GET_CLASS ((o), GLADE_EPROP_SCRIPT, GladeEPropScriptClass))

#define GLADE_TYPE_EPROP_SCRIPT (glade_eprop_script_get_type())

GType glade_eprop_script_get_type (void) G_GNUC_CONST;
