CC=gcc
INCLUDES=`pkg-config --cflags gtksourceview-3.0` -I../script
FLAGS=$(INCLUDES) -Wall -g -ggdb -fPIC
LIBRARIES=`pkg-config --libs gtksourceview-3.0` -L../script/.libs -lgscript

OBJECTS=g-script-editor.lo
SOURCES=g-script-editor.c g-script-editor.h g-script-editor-private.h

all: libgscript-editor.la

libgscript-editor.la: $(OBJECTS)
	@echo [Linking] $@
	@libtool link --silent $(CC) $(LIBRARIES) $(OBJECTS) -rpath `pwd`/.libs -o $@ 

g-script-editor.lo: $(SOURCES)
	@echo [Compiling] $@
	@libtool compile --silent $(CC) $(FLAGS) -c $< -o $@

clean:
	@echo [Cleaning]
	@-rm *.o *.lo *.la
	@-rm -rf .libs


