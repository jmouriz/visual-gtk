gcc -c g-script-js-editor.c -o g-script-js-editor.o -I. -I.. $(pkg-config --cflags gtk+-3.0 gtksourceview-3.0) -Wall -g -ggdb -fPIC
gcc --shared g-script-js-editor.o -o libg-script-js-editor.so -L. -L.. -lg-script-js $(pkg-config --libs gtk+-3.0 gtksourceview-3.0) -Wall -g -ggdb
#gcc -c editor.c -o editor.o -I. -I.. $(pkg-config --cflags gtk+-3.0) -Wall -g -ggdb
#gcc editor.o -o editor -L. -lg-script-js-editor $(pkg-config --libs gtk+-3.0) -Wall -g -ggdb
