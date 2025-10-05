#!/usr/bin/env python3
from cp import *

clean_folder()
if build_file("inw.cpp"):
    run_with_file("./inw", "in/inw/01.in")

