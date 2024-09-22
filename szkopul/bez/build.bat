@echo off

call clang++ -o bez.exe bez.cpp
echo --- INPUT1 ---
call bez < input.txt
echo --- INPUT2 ---
call bez < input2.txt

