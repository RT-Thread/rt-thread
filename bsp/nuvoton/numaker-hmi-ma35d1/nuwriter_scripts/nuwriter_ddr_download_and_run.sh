#!/bin/bash

set -x -e

python3 nuwriter.py -a ddrimg/enc_ddr3_winbond_256mb.bin;

python3 nuwriter.py -o execute -w ddr 0x80400000 ../rtthread.bin

