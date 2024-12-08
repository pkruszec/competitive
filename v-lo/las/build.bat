@echo off

call clang++ -o las.exe las.cpp
echo [INFO] Build finished

call las < 01.in
call las < 02.in
call las < 03.in
call las < 04.in
