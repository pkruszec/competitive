@echo off

if not exist build mkdir build

pushd build
    call clang++ -std=c++20 -o ban.exe ..\ban.cpp
popd
