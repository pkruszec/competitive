@echo off

if not exist build mkdir build

set common=-std=c++17 -g

pushd build
    call clang++ %common% -D POR_REDIRECT=1 -o por.exe ..\por.cpp

    call por < ..\tests\test1.txt
    call por < ..\tests\test2.txt
    call por < ..\tests\test3.txt
popd
