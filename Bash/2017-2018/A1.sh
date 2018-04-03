#!/bin/bash
mkdir -p "$1/build"
mkdir -p "$1/bin"

gcc -c "$1/src/$2.c" -o "$1/build/$2.o"
gcc -c "$1/src/$3.c" -o "$1/build/$3.o"

gcc -o "$1/bin/$4" "$1/build/$2.o" "$1/build/$3.o"

#Wojciech Buczek
