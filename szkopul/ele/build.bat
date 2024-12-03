@echo off

call clang++ ele.cpp -o ele.exe
call ele.exe < input01.txt
call ele.exe < input02.txt
call ele.exe < input03.txt
