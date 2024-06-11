@echo off

if not exist build mkdir build

set arg=%1
set common=-std=c++17 -g

if "%arg%" == "ship" (
    pushd build
        call clang++ %common% -D PRZ1_REDIRECT=1 -o prz1.exe ..\prz1.cpp
    popd

    call build\prz1.exe test1.txt && echo:
    call build\prz1.exe test2.txt && echo:
    call build\prz1.exe test3.txt && echo:
) else (
    pushd build
        call clang++ %common% -o unit.exe ..\unit.cpp
    popd

    call build\unit.exe
)
