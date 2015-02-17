#!/bin/bash

FLAGS="-I../script `pkg-config --cflags gtk+-3.0 cjs-1.0` -Wall -g -ggdb"
LIBS="-L../script -lg-script-js `pkg-config --libs gtk+-3.0 cjs-1.0` -Wall -g -ggdb"

function compile
{
  file=$*

  echo -n "Compiling $file.o: "
  gcc -c $file.c -o $file.o $FLAGS
  echo Done
}

function link
{
  file=$*

  echo -n "Linking $file: "
  gcc $file.o -o $file $LIBS
  echo Done
}

function build
{
  file=$*

  compile $file
  link $file
}

build test-1 # not need gtk+-3.0 and cjs-1.0, only gobject-2.0
build test-2
build test-3
