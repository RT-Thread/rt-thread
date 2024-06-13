#!/bin/bash

export RTT_CC=gcc
export RTT_EXEC_PATH=$(pwd)/tools/gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf/bin
export RTT_CC_PREFIX=aarch64-none-elf-
export PATH=$PATH:$RTT_EXEC_PATH

echo "arch      => aarch64"
echo "CC        => ${RTT_CC}"
echo "PREFIX    => ${RTT_CC_PREFIX}"
echo "EXEC_PATH => ${RTT_EXEC_PATH}"
