g++ -c script.c -o script.o -I.. $(pkg-config --cflags gtk+-3.0 cjs-1.0) -Wall -g -ggdb
gcc script.o -o script -L.. -lg-script-js $(pkg-config --libs gtk+-3.0) -Wall -g -ggdb
gcc -c editor.c -o editor.o -I../editor -I.. $(pkg-config --cflags gtk+-3.0) -Wall -g -ggdb
gcc editor.o -o editor -L../editor -L.. -lg-script-js -lg-script-js-editor $(pkg-config --libs gtk+-3.0) -Wall -g -ggdb
gcc -c test-1.c -o test-1.o -I.. $(pkg-config --cflags gobject-2.0) -Wall -g -ggdb
gcc test-1.o -o test-1 -L.. -lg-script-js $(pkg-config --libs gobject-2.0) -Wall -g -ggdb
