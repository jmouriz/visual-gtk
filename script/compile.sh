gcc -c g-script-js.c -o g-script-js.o -I. $(pkg-config --cflags gtk+-3.0 cjs-1.0 cjs-internals-1.0) -Wall -g -ggdb -fPIC
gcc -c g-script-js-function.c -o g-script-js-function.o -I. $(pkg-config --cflags gtk+-3.0 cjs-1.0 cjs-internals-1.0) -Wall -g -ggdb -fPIC
gcc --shared g-script-js.o g-script-js-function.o -o libg-script-js.so $(pkg-config --libs gtk+-3.0 cjs-1.0 cjs-internals-1.0) -Wall -g -ggdb
#gcc -c script.c -o script.o -I. $(pkg-config --cflags gtk+-3.0 gjs-1.0) -Wall -g -ggdb
#gcc script.o -o script -L. -lg-script-js $(pkg-config --libs gtk+-3.0) -Wall -g -ggdb
#CATALOGS=$(pkg-config --variable=catalogdir gladeui-2.0)
#MODULES=$(pkg-config --variable=moduledir gladeui-2.0)
#--xmllint --dtdvalid $CATALOGS/glade-catalog.dtd --noout catalog.xml 
#export GLADE_CATALOG_SEARCH_PATH=.
#export GLADE_MODULE_SEARCH_PATH=.
