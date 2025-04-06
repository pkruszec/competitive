@echo off

call clang++ -o prog.exe prog.cpp
call prog < 01.in
:: call prog < 02.in
:: call prog < 04.in
