@echo off

call clang++ faktoryzacja.cpp -o faktoryzacja.exe
call faktoryzacja < input1.txt
