#!/usr/bin/env python3
from cp import *

clean_folder()
if build_file("inw.cpp"):
    sio2jail_with_file("./inw.out", "in/inw/01.in")
