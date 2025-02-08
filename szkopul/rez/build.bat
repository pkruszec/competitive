@echo off

call clang++ -o rez.exe rez.cpp
call rez < 01.in
