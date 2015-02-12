echo -n "Compiling glade-g-script-js-script.o: "
gcc -c glade-g-script-js-script.c -o glade-g-script-js-script.o -I. -I../script $(pkg-config --cflags gladeui-2.0 gtksourceview-3.0) -g -ggdb -fPIC #WIN32:-no-undefined
echo Done
echo -n "Compiling glade-g-script-js-source: "
gcc -c glade-g-script-js-source.c -o glade-g-script-js-source.o -I. -I../script -I../editor $(pkg-config --cflags gladeui-2.0 gtksourceview-3.0) -g -ggdb -fPIC #WIN32:-no-undefined
echo Done
echo -n "Compiling glade-g-script-js.o: "
gcc -c glade-g-script-js.c -o glade-g-script-js.o -I. -I../script $(pkg-config --cflags gladeui-2.0 gtksourceview-3.0) -g -ggdb -fPIC #WIN32:-no-undefined
echo Done
echo -n "Linking libglade-g-script-js.so: "
gcc --shared glade-g-script-js-script.o glade-g-script-js-source.o glade-g-script-js.o -o libglade-g-script-js.so -L../script -L../editor -lg-script-js -lg-script-js-editor $(pkg-config --libs gladeui-2.0 gtksourceview-3.0) -g -ggdb 
echo Done
