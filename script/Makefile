CC=gcc
INCLUDES=`pkg-config --cflags gtk+-3.0 cjs-1.0 cjs-internals-1.0 gobject-introspection-1.0`
FLAGS=$(INCLUDES) -Wall -g -ggdb -fPIC
LIBRARIES=`pkg-config --libs gtk+-3.0 cjs-1.0 cjs-internals-1.0 gobject-introspection-1.0`

OBJECTS=g-script.lo g-script-function.lo g-script-util.lo

NAMESPACE=G
VERSION=0.1
GIR=$(NAMESPACE)-$(VERSION).gir
TYPELIB=$(NAMESPACE)-$(VERSION).typelib
#NAME=$(NAMESPACE)Script
#GIFILENAME=$(NAMESPACE)Script-$(VERSION)
#GIR=$(GIFILENAME).gir
#TYPELIB=$(GIFILENAME).typelib

all: libgscript.la $(TYPELIB)

libgscript.la: $(OBJECTS)	
	@echo [Linking] $@
	@libtool link --silent $(CC) $(LIBRARIES) $(OBJECTS) -rpath `pwd`/.libs -o $@ 

$(TYPELIB): $(GIR)
	@echo [Generating] $@
	@libtool exec --silent g-ir-compiler $(GIR) --output=$(TYPELIB)

$(GIR): g-script.c g-script.h
	@echo [Scanning] $@
	@libtool exec --silent g-ir-scanner --quiet --warn-all $^ --no-libtool --library=gscript -L.lib$(INCLUDES) --include=GObject-2.0 --namespace=$(NAMESPACE) --nsversion=$(VERSION) --output=$@

g-script.lo: g-script.c g-script.h g-script-private.h
	@echo [Compiling] $@
	@libtool compile --silent $(CC) $(FLAGS) -c $< -o $@

g-script-function.lo: g-script-function.c g-script-function.h
	@echo [Compiling] $@
	@libtool compile --silent $(CC) $(FLAGS) -c $< -o $@

g-script-util.lo: g-script-util.c g-script-util.h
	@echo [Compiling] $@
	@libtool compile --silent $(CC) $(FLAGS) -c $< -o $@

clean:
	@echo [Cleaning]
	@-rm *.o *.lo *.la $(TYPELIB) $(GIR)
	@-rm -rf .libs tmp-introspect*


