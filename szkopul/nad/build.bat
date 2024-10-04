@echo off

set opts=-Wall -Wextra -std=c++17 -g -DREMEDY
set code=%cd%
call clang++ %opts% %code%\nad.cpp -o nad.exe

:: call nad < input01.txt
:: call nad < input02.txt
