#!/bin/bash

showStandardInput=0
numberOfHelp=0
returnError=0
nextArgIsFile=0
files=""
IFS=' ';

for arg in "$@"
do
    if [ $nextArgIsFile == 1 ]; then
        files="$files$arg "
        nextArgIsFile=0
        continue
    fi
    case "$arg" in
        "-s"|"--stdin") 
            showStandardInput=1 ;;
        "-h"|"--help") 
            numberOfHelp=$((numberOfHelp+1)) ;;
        "-f")
            nextArgIsFile=1 ;;
    esac
    if [[ $arg == --file* ]]; then

        IFS='=';

        read -r temp fileName <<< "$arg"
        
        if [ -z $fileName ]; then
            exit 10
        fi

        IFS=' ';

        
        files="$files$fileName "
    fi
done

if [ $nextArgIsFile == 1 ]; then
    exit 10
fi

if [ $showStandardInput == 1 ]; then
    stdin="$(cat /dev/stdin)"
    echo $stdin
fi
echo $numberOfHelp

echo $files

#Wojciech Buczek