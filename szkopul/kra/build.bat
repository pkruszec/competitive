@echo off

call clang++ -o kra.exe kra.cpp
call kra < 01.in
call kra < 02.in
call kra < 03.in
call kra < 04.in
