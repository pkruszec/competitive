#!/usr/bin/env python3
from cp import *

clean_folder()
if build_file("egz.cpp"):
    run_with_file("./egz", "in/egz/02.in")

