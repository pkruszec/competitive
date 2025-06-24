#!/bin/bash

# Create named pipes for communication

declare -a FDS
coproc FDS { ./porsoc.e; }
$1 <&${FDS[0]} >&${FDS[1]}

