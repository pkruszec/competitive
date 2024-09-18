@echo off

call clang++ ana.cpp -o ana.exe
call ana.exe < input.txt
