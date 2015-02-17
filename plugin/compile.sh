echo -n "Compiling glade-g-script-js-filename.o: "
gcc -c glade-g-script-js-filename.c -o glade-g-script-js-filename.o -I. -I../script $(pkg-config --cflags gladeui-2.0 gtksourceview-3.0) -finstrument-functions -g -ggdb -fPIC #WIN32:-no-undefined
echo Done
echo -n "Compiling glade-g-script-js-javascript.o: "
gcc -c glade-g-script-js-javascript.c -o glade-g-script-js-javascript.o -I. -I../script -I../editor $(pkg-config --cflags gladeui-2.0 gtksourceview-3.0) -finstrument-functions -g -ggdb -fPIC #WIN32:-no-undefined
echo Done
echo -n "Compiling glade-g-script-js.o: "
gcc -c glade-g-script-js.c -o glade-g-script-js.o -I. -I../script $(pkg-config --cflags gladeui-2.0 gtksourceview-3.0) -finstrument-functions -g -ggdb -fPIC #WIN32:-no-undefined
echo Done
echo -n "Linking libglade-g-script-js.so: "
gcc --shared glade-g-script-js-filename.o glade-g-script-js-javascript.o glade-g-script-js.o -o libglade-g-script-js.so -L../script -L../editor -lg-script-js -lg-script-js-editor $(pkg-config --libs gladeui-2.0 gtksourceview-3.0) -g -ggdb 
echo Done
