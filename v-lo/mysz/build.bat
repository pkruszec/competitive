@echo off

call clang++ mysz.cpp -std=c++17 -o mysz.exe

if "%1" == "run" (
   call mysz.exe < input.txt
)
