@echo off

call clang++ -g -o gil.exe gil.cpp
call gil < 01.in
call gil < 02.in
call gil < 03.in
call gil < 04.in
call gil < 05.in
