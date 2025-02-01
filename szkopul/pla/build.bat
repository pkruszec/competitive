@echo off

call clang++ -o pla.exe pla.cpp
:: call cl /nologo /EHsc pla.cpp
call pla < 01.in
call pla < 02.in
