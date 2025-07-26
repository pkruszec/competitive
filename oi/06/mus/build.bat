@echo off

call cl /nologo /EHsc /Zi prog.cpp
call prog < 02.in
