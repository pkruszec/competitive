#!/bin/sh
set -xe

g++ -o prog prog.cpp
./prog < 01.in

