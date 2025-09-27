#!/usr/bin/env python3
from cp import *

clean_folder()
if build_file("her.cpp"):
    run_with_file("./her", "in/her/02.in")

