@echo off

call clang++ -O3 kom.cpp -o kom.exe
call kom < 01.in
echo Running test
call @kom < 04.in
