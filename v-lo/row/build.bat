@echo off
:: setlocal EnableDelayedExpansion

call clang++ -O2 -o row.exe row.cpp
:: call :run_test 08.in

call :run_test 01.in
call :run_test 02.in
call :run_test 03.in
call :run_test 04.in
call :run_test 05.in
call :run_test 06.in
call :run_test 07.in
call :run_test 08.in
call :run_test 09.in
call :run_test 10.in

goto:eof

:run_test
echo ---- %~1 ----
call row < %~1
goto:eof
