#!/bin/bash

function mediana()
{
    arg=("$@")
    #echo ${arg[@]}
    readarray -t sorted < <(for a in "${arg[@]}"; do echo "$a"; done | sort -n)
    l=${#sorted[@]}

    if ((l%2 == 1)); then
        mid=$(($l/2))
        echo ${sorted[$mid]}
    else
        mid=$(($l/2))
        secondMid=$(($mid-1))
        q=${sorted[$mid]}
        p=${sorted[$secondMid]}
        med=$((q+p))
        med=$(($med/2))
        echo $med
    fi
}

stdio=$(cat)
mapfile -t list <<<"$stdio"
length=${#list[@]}
allMedian="$(mediana ${list[@]})"

numberOfFives=$((length/5))

if ((length%5 != 0)); then
    numberOfFives=$(($numberOfFives + 1))
fi

for ((x=0;x<$numberOfFives;x++)); do
    y=$((x*5))
    m="$(mediana ${list[@]:$y:5})"
    medians+=($m)
done
medianOfMedians="$(mediana ${medians[@]})"
echo $allMedian $medianOfMedians


#Wojciech Buczek