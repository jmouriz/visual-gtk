#CATALOGS=$(pkg-config --variable=catalogdir gladeui-2.0)
#MODULES=$(pkg-config --variable=moduledir gladeui-2.0)
export PATH=$PATH:$(pwd)/sources
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/script/.libs:$(pwd)/plugin:$(pwd)/editor/.libs
export GI_TYPELIB_PATH=$GI_TYPELIB_PATH:$(pwd)/script
export GLADE_CATALOG_SEARCH_PATH=$GLADE_CATALOG_SEARCH_PATH:$(pwd)/plugin:$(pwd)/plugin/.libs
export GLADE_MODULE_SEARCH_PATH=$GLADE_MODULE_SEARCH_PATH:$(pwd)/plugin/.libs
export XDG_DATA_DIRS=$XDG_DATA_DIRS:$(pwd)/plugin
export GSCRIPT_MODULE_SEARCH_PATH=$GSCRIPT_MODULE_SEARCH_PATH:$(pwd)/modules
