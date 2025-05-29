@echo off

:: clang++ -g -o prog.exe prog.cpp
cl /nologo /EHsc /Zi /Feprog prog.cpp
prog < 01.in
