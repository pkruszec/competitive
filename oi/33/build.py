#!/usr/bin/env python3
from cp import *

clean_folder()
if build_file("xpl.cpp"):
    sio2jail_run_tests("./xpl.out", "xpl/in/gen*.in", "xpl/out/", "xpl.csv", 0.5)

