#!/bin/sh
set -e

c++ -O3 -std=c++20 -o zam-linux zam.cpp

for f in in/*.in; do
    output="$(./zam-linux < $f)"
    filename="$(basename -- "$f")"
    extension="${filename##*.}"
    filename="out/${filename%.*}.out"
    expected="$(cat $filename)"

    if [ $expected != $output ]
    then
        printf "exp %s got %s\n" $expected $output
    fi
    # echo $filename $expected $output
done
