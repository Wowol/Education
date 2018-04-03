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

find . -name "*.c" -print0 | xargs -0 -I {} sh -c "gcc '{}' -c -o '../build/{}'.o"

cd "../build"

find . -name "*.c.o" -print0 | xargs -0 gcc -o "../bin/$programName"

#Wojciech Buczek