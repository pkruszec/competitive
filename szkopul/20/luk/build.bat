@echo off

call clang++ -o luk.exe luk.cpp
call luk < 01.in
call luk < 02.in
call luk < 03.in
call luk < 04.in
call luk < 05.in
call luk < 06.in
