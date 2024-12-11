@echo off

call clang++ -DPERF -O3 -o las.exe las.cpp
echo [INFO] Build finished

:: call las < 01.in
:: call las < 02.in
:: call las < 03.in
:: call las < 04.in
call las < 05.in
:: call las < 06.in
