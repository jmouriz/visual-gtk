#gcc -c glade-g-script-js.c -o glade-g-script-js.o -module -avoid-version $(pkg-config --cflags gladeui-2.0) #WIN32:-no-undefined
#gcc -c glade-g-script-js-editor.c -o glade-g-script-js-editor.o -module -avoid-version $(pkg-config --flags gladeui-2.0) #WIN32:-no-undefined
gcc -c glade-g-script-js-script.c -o glade-g-script-js-script.o -I. -I../script $(pkg-config --cflags gladeui-2.0 gtksourceview-3.0) -g -ggdb -fPIC #WIN32:-no-undefined
gcc -c glade-g-script-js-source.c -o glade-g-script-js-source.o -I. -I../script -I../editor $(pkg-config --cflags gladeui-2.0 gtksourceview-3.0) -g -ggdb -fPIC #WIN32:-no-undefined
#gcc -c glade-g-script-js-editor.c -o glade-g-script-js-editor.o -I. -I../script -I../editor $(pkg-config --cflags gladeui-2.0 gtksourceview-3.0) -g -ggdb -fPIC #WIN32:-no-undefined
gcc -c glade-g-script-js.c -o glade-g-script-js.o -I. -I../script $(pkg-config --cflags gladeui-2.0 gtksourceview-3.0) -g -ggdb -fPIC #WIN32:-no-undefined
gcc --shared glade-g-script-js-script.o glade-g-script-js-source.o glade-g-script-js.o -o libglade-g-script-js.so -L../script -L../editor -lg-script-js -lg-script-js-editor $(pkg-config --libs gladeui-2.0 gtksourceview-3.0) -g -ggdb 
#gcc --shared glade-g-script-js-script.o glade-g-script-js-source.o glade-g-script-js-editor.o glade-g-script-js.o -o libglade-g-script-js.so -L../script -L../editor -lg-script-js -lg-script-js-editor $(pkg-config --libs gladeui-2.0 gtksourceview-3.0) -g -ggdb 
