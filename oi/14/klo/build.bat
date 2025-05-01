@echo off

call clang++ -g -o prog.exe prog.cpp
call prog < 01.in
