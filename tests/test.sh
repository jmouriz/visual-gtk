#!/bin/bash

function test
{
  file=$*

  echo -n "Testing $file.ui: "
  glade $file.ui
  echo Done
}

test test-2
test test-3

rm *.ui~
