@echo off

clang++ wal.cpp -std=c++20 -o wal.exe

echo === MANUAL TEST OUTPUT ===
for /f %%f in ('dir /b input') do call wal < input\%%f

echo === GENERATED TEST OUTPUT ===
for /f %%f in ('dir /b test') do call wal < test\%%f
