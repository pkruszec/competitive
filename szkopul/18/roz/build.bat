@echo off

call clang++ -o roz.exe roz.cpp
call roz < 01.in
:: call roz < 02.in
