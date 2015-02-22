typedef struct
{
  GladeEditorProperty parent_instance;
  GtkWidget *editor;
} GladeEPropFilename;

#define GLADE_EPROP_FILENAME(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GLADE_TYPE_EPROP_FILENAME, GladeEPropFilename))
#define GLADE_EPROP_FILENAME_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GLADE_TYPE_EPROP_FILENAME, GladeEPropFilenameClass))
#define GLADE_IS_EPROP_FILENAME(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GLADE_TYPE_EPROP_FILENAME))
#define GLADE_IS_EPROP_FILENAME_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GLADE_TYPE_EPROP_FILENAME))
#define GLADE_EPROP_FILENAME_GET_CLASS(o)    (G_TYPE_INSTANCE_GET_CLASS ((o), GLADE_EPROP_FILENAME, GladeEPropFilenameClass))

#define GLADE_TYPE_EPROP_FILENAME (glade_eprop_filename_get_type())

GType glade_eprop_filename_get_type (void) G_GNUC_CONST;

void glade_g_script_set_filename (GObject *object, const GValue *value);
