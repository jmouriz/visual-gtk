TARGET=editor

CC=gcc
INCLUDES=`pkg-config --cflags gtk+-3.0` -I../../script -I../../editor
FLAGS=$(INCLUDES) -Wall -g -ggdb -fPIC
LIBRARIES=`pkg-config --libs gtk+-3.0` -L../../script/.libs -L../../editor/.libs -lgscript -lgscript-editor

all: $(TARGET)

$(TARGET): $(TARGET).o
	@echo [Linking] $@
	@$(CC) $< $(LIBRARIES) -o $@ 

$(TARGET).o: $(TARGET).c
	@echo [Compiling] $@
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo [Cleaning]
	@-rm *.o *.ui~ $(TARGET)
