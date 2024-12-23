@echo off

call clang++ mysz.cpp -std=c++17 -o mysz.exe
call mysz.exe < 01.in
call mysz.exe < 02.in
