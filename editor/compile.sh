echo -n "Compiling g-script-js-editor.o: "
gcc -c g-script-js-editor.c -o g-script-js-editor.o -I. -I../script $(pkg-config --cflags gtk+-3.0 gtksourceview-3.0) -Wall -g -ggdb -fPIC
echo Done
echo -n "Linking libg-script-js-editor.so: "
gcc --shared g-script-js-editor.o -o libg-script-js-editor.so -L. -L../script -lg-script-js $(pkg-config --libs gtk+-3.0 gtksourceview-3.0) -Wall -g -ggdb
echo Done
