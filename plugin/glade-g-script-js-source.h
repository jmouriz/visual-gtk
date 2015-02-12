typedef struct
{
  GladeEditorProperty parent_instance;
  GladeNameContext *context;

  GtkWidget *editor;
} GladeEPropSource;

//GLADE_MAKE_EPROP (GladeEPropSource, glade_eprop_source)

#define GLADE_EPROP_SOURCE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GLADE_TYPE_EPROP_SOURCE, GladeEPropSource))
#define GLADE_EPROP_SOURCE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GLADE_TYPE_EPROP_SOURCE, GladeEPropSourceClass))
#define GLADE_IS_EPROP_SOURCE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GLADE_TYPE_EPROP_SOURCE))
#define GLADE_IS_EPROP_SOURCE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GLADE_TYPE_EPROP_SOURCE))
#define GLADE_EPROP_SOURCE_GET_CLASS(o)    (G_TYPE_INSTANCE_GET_CLASS ((o), GLADE_EPROP_SOURCE, GladeEPropSourceClass))

#define GLADE_TYPE_EPROP_SOURCE (glade_eprop_source_get_type())

GType glade_eprop_source_get_type (void) G_GNUC_CONST;
