@echo off

clang++ wal.cpp -std=c++20 -o wal.exe

echo === MANUAL TEST OUTPUT ===
call wal < input01.txt
call wal < input02.txt
call wal < input03.txt
call wal < input04.txt
call wal < input05.txt
call wal < input06.txt
call wal < input07.txt
call wal < input08.txt
call wal < input09.txt

echo === GENERATED TEST OUTPUT ===
for /f %%f in ('dir /b test') do call wal < test\%%f
