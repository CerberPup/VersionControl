#!/bin/bash
set -e
qmake
#sed -e "s/[[:space:]]-lGL//g" -i Makefile
make -f Makefile
