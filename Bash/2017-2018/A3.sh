#!/bin/bash
catalog="$1"
programName="$2"
srcCatalog="$1/src"
buildCatalog="$1/build"
binCatalog="$1/bin"

mkdir -p "$binCatalog"
mkdir -p "$buildCatalog"

cd "$srcCatalog"

find . -type d -print0 | xargs -0 -I {} sh -c "mkdir -p '../build/{}'"

find . -name "*.c" | sed -r 's:(.*)c:gcc "\1c" -c -o "../build/\1o":g' | bash

find . -name "*.c" | sed -r 's:(.*)c:../build/\1o:g' | xargs -d '\n' gcc -o "../bin/$programName" 

#Wojciech Buczek