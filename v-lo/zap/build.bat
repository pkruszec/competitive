@echo off

call clang++ -o zap.exe zap1.cpp
call zap < 01.in
