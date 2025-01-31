@echo off

call clang++ -o bro.exe bro.cpp
call bro < 01.in
