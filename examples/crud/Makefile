TARGETS=demo

CC=gcc
INCLUDES=`pkg-config --cflags gtk+-3.0` -I../../script
FLAGS=$(INCLUDES) -Wall -g -ggdb -fPIC
LIBRARIES=`pkg-config --libs gtk+-3.0` -L../../script/.libs -lgscript

all: $(TARGETS) demo.db

demo: demo.o
	@echo [Linking] $@
	@$(CC) $< $(LIBRARIES) -o $@ 

demo.o: demo.c
	@echo [Compiling] $@
	@$(CC) $(FLAGS) -c $< -o $@

demo.db: demo.sql
	@echo [Generating] $@
	@sqlite3 $@ < $<

clean:
	@echo [Cleaning]
	@-rm *.o *.ui~ demo.db $(TARGETS)
