echo -n "Compiling glade-g-script-filename.o: "
gcc -c glade-g-script-filename.c -o glade-g-script-filename.o -I. -I../script $(pkg-config --cflags gladeui-2.0 gtksourceview-3.0) -finstrument-functions -g -ggdb -fPIC #WIN32:-no-undefined
echo Done
echo -n "Compiling glade-g-script-javascript.o: "
gcc -c glade-g-script-javascript.c -o glade-g-script-javascript.o -I. -I../script -I../editor $(pkg-config --cflags gladeui-2.0 gtksourceview-3.0) -finstrument-functions -g -ggdb -fPIC #WIN32:-no-undefined
echo Done
echo -n "Compiling glade-g-script.o: "
gcc -c glade-g-script.c -o glade-g-script.o -I. -I../script $(pkg-config --cflags gladeui-2.0 gtksourceview-3.0) -finstrument-functions -g -ggdb -fPIC #WIN32:-no-undefined
echo Done
echo -n "Linking libglade-gscript.so: "
gcc --shared glade-g-script-filename.o glade-g-script-javascript.o glade-g-script.o -o libglade-gscript.so -L../script/.libs -L../editor/.libs -lgscript -lgscript-editor $(pkg-config --libs gladeui-2.0 gtksourceview-3.0) -g -ggdb 
echo Done
