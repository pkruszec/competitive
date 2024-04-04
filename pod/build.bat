@echo off
clang-cl -std:c++20 -D POD_DEBUG -Zi pod.cpp

call pod.exe test1.txt && echo:
call pod.exe test2.txt && echo:
call pod.exe test3.txt && echo:
call pod.exe test4.txt && echo:
