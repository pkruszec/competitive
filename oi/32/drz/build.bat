@echo off

call clang++ -std=c++17 -g -o prog.exe prog.cpp
call prog < 01.in
