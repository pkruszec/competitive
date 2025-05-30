@echo off

cl /nologo /std:c++17 /Zi /EHsc /Fe:prog.exe prog.cpp
:: prog < 01.in
prog < 02.in
