@echo off

call clang++ -o liz_100.exe liz.cpp
:: call liz < 01.in
:: call liz < 02.in
:: call liz < 03.in
:: call liz_opt < 04.in

:: call hyperfine --warmup 2 "liz_bsearch < 04.in > NUL" "liz_bsearch_precheck < 04.in > NUL" "liz_100 < 04.in > NUL"
