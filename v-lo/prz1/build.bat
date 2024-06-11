@echo off

if not exist build mkdir build

set arg=%1
set common=-std=c++17 -g

if "%arg%" == "dbg" (
    pushd build
        call clang++ %common% -D PRZ1_REDIRECT=1 -o prz1.exe ..\prz1.cpp
    popd
) else (
    pushd build
        call clang++ %common% -o unit.exe ..\unit.cpp
    popd

    call build\unit.exe %*
)
