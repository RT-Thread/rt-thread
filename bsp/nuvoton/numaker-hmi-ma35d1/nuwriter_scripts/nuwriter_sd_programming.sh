#!/bin/bash

set -x -e

python3 nuwriter.py -c header-sd.json

python3 nuwriter.py -p pack-sd.json

python3 nuwriter.py -a ddrimg/enc_ddr3_winbond_256mb.bin

python3 nuwriter.py -w sd pack/pack.bin
