TARGETS=editor

CC=gcc
INCLUDES=`pkg-config --cflags gtk+-3.0` -I../../script -I../../editor
FLAGS=$(INCLUDES) -Wall -g -ggdb -fPIC
LIBRARIES=`pkg-config --libs gtk+-3.0` -L../../script/.libs -L../../editor/.libs -lgscript -lgscript-editor

all: $(TARGETS)

editor: editor.o
	@echo [Linking] $@
	@$(CC) $< $(LIBRARIES) -o $@ 

editor.o: editor.c
	@echo [Compiling] $@
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo [Cleaning]
	@-rm *.o *.ui~ $(TARGETS)
