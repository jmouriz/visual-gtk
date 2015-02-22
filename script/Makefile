CC=gcc
INCLUDES=`pkg-config --cflags gtk+-3.0 cjs-1.0 cjs-internals-1.0`
FLAGS=$(INCLUDES) -Wall -g -ggdb -fPIC
LIBRARIES=`pkg-config --libs gtk+-3.0 cjs-1.0 cjs-internals-1.0`

OBJECTS=g-script.lo g-script-function.lo

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
	libtool link $(CC) $(LIBRARIES) $(OBJECTS) -rpath `pwd`/.libs -o $@ 

$(TYPELIB): $(GIR)
	g-ir-compiler $(GIR) --output=$(TYPELIB)

$(GIR): g-script.c g-script.h
	#libtool exec g-ir-scanner $^ --warn-all --library=gscript -L.libs $(INCLUDES) --include=GObject-2.0 --namespace=$(NAMESPACE) --nsversion=$(VERSION) --output=$@
	libtool exec g-ir-scanner $^ --warn-all --no-libtool --library=gscript -L.lib$(INCLUDES) --include=GObject-2.0 --namespace=$(NAMESPACE) --nsversion=$(VERSION) --output=$@

g-script.lo: g-script.c g-script.h g-script-private.h
	libtool compile $(CC) $(FLAGS) -c $< -o $@

g-script-function.lo: g-script-function.c g-script-function.h
	libtool compile $(CC) $(FLAGS) -c $< -o $@

clean:
	-rm *.o *.lo *.la $(TYPELIB) $(GIR)
	-rm -rf .libs tmp-introspect*


