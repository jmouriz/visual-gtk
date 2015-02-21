VERSION=0.1

echo -n "Compiling g-script-js.o: "
gcc -c g-script-js.c -o g-script-js.o -I. $(pkg-config --cflags gtk+-3.0 cjs-1.0 cjs-internals-1.0) -Wall -g -ggdb -fPIC
echo Done
echo -n "Compiling g-script-js-function.o: "
gcc -c g-script-js-function.c -o g-script-js-function.o -I. $(pkg-config --cflags gtk+-3.0 cjs-1.0 cjs-internals-1.0) -Wall -g -ggdb -fPIC
echo Done
echo -n "Linking libg-script-js.so: "
gcc --shared g-script-js.o g-script-js-function.o -o libg-script-js.so $(pkg-config --libs gtk+-3.0 cjs-1.0 cjs-internals-1.0) -Wall -g -ggdb
echo Done

gcc -c introspector.c -o introspector.o $(pkg-config --cflags gobject-introspection-1.0)
gcc introspector.o -o introspector -L. -lg-script-js $(pkg-config --libs gobject-introspection-1.0)

g-ir-scanner g-script-js.[ch] --program=./introspector $(pkg-config --cflags gobject-introspection-1.0) --include=GObject-2.0 \
  --namespace=GScriptJs --nsversion=$VERSION --output=GScriptJs-$VERSION.gir --warn-all

g-ir-compiler GScriptJs-$VERSION.gir --output=GScriptJs-$VERSION.typelib

#--xmllint --dtdvalid $CATALOGS/glade-catalog.dtd --noout catalog.xml 
