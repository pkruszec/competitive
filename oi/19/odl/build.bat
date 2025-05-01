@echo off

call clang++ -g -fsanitize=address -fno-omit-frame-pointer -o odl.exe odl.cpp
call odl < 01.in
