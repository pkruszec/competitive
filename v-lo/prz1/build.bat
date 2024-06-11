@echo off

if not exist build mkdir build

pushd build
    call clang++ -std=c++20 -D PRZ1_REDIRECT=1 -g -o prz1.exe ..\prz1.cpp
popd

call build\prz1.exe test1.txt && echo:
call build\prz1.exe test2.txt && echo:
call build\prz1.exe test3.txt && echo:
