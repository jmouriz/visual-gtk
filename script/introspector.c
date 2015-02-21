#include <girepository.h>
#include "g-script-js.h"

int
main (int argc, char *argv[])
{
  GOptionContext *ctx;
  GError *error = NULL;
  GScriptJs *script;

  script = g_script_js_new ();

  ctx = g_option_context_new (NULL);
  g_option_context_add_group (ctx, g_irepository_get_option_group ());  

  if (!g_option_context_parse (ctx, &argc, &argv, &error))
  {
    g_print ("introspector: %s\n", error->message);
    return 1;
  }

  return 0;
}
