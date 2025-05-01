@echo off

clang++ usu.cpp -o usu.exe
call usu < input01.txt
call usu < input02.txt
call usu < input03.txt
call usu < input04.txt
