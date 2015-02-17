echo -n "Compiling script.o: "
gcc -c script.c -o script.o -I../script $(pkg-config --cflags gtk+-3.0 cjs-1.0) -Wall -g -ggdb
echo Done
echo -n "Linking script: "
gcc script.o -o script -L../script -lg-script-js $(pkg-config --libs gtk+-3.0) -Wall -g -ggdb
echo Done
echo -n "Compiling editor: "
gcc -c editor.c -o editor.o -I../editor -I../script $(pkg-config --cflags gtk+-3.0) -Wall -g -ggdb
echo Done
echo -n "Linking editor "
gcc editor.o -o editor -L../editor -L../script -lg-script-js -lg-script-js-editor $(pkg-config --libs gtk+-3.0) -Wall -g -ggdb
echo Done
