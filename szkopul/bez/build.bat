@echo off

call clang++ -o bez.exe bez.cpp
:: call python test.py
:: call diff -u result.txt result_new.txt

echo --- INPUT1 ---
call bez < tests\input01.txt
echo --- INPUT2 ---
call bez < tests\input02.txt
echo --- INPUT3 ---
call bez < tests\input03.txt
echo --- INPUT4 ---
call bez < tests\input04.txt
echo --- INPUT5 ---
call bez < tests\input05.txt
