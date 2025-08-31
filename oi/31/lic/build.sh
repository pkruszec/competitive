#!/bin/sh
set -xe

mkdir -p bin/
g++ -o bin/lic -O3 -static -std=c++20 lic.cpp

bin/lic < in/02.in
