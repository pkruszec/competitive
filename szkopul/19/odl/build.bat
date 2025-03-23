@echo off

call clang++ -o odl.exe odl.cpp
call odl < 01.in
