@echo off

call clang++ -o tet.exe tet.cpp
call tet < 01.in
:: call tet < 02.in
