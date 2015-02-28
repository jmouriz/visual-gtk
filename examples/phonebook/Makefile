TARGET=phonebook

CC=gcc
INCLUDES=`pkg-config --cflags gtk+-3.0` -I../../script
FLAGS=$(INCLUDES) -Wall -g -ggdb -fPIC
LIBRARIES=`pkg-config --libs gtk+-3.0` -L../../script/.libs -lgscript

all: $(TARGET).db

$(TARGET).db: $(TARGET).sql
	@echo [Generating] $@
	@sqlite3 $@ < $<

clean:
	@echo [Cleaning]
	@-rm *.o *.ui~ $(TARGET).db
