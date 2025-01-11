@echo off

:: call clang++ -std=c++17 -o prz.exe prz.cpp
call cl /nologo /EHsc /std:c++20 /Fe:prz prz.cpp

@REM call prz < 07.in
@REM goto :eof

call prz < 01.in
call prz < 02.in
call prz < 03.in
call prz < 04.in
call prz < 05.in
call prz < 06.in
call prz < 07.in
call prz < 08.in
