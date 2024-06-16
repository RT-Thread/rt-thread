#!/bin/bash

export RTT_CC=gcc
export RTT_EXEC_PATH=$(pwd)/tools/gcc-arm-10.3-2021.07-x86_64-arm-none-eabi/bin
export RTT_CC_PREFIX=arm-none-eabi-
export PATH=$PATH:$RTT_EXEC_PATH

echo "arch      => aarch64"
echo "CC        => ${RTT_CC}"
echo "PREFIX    => ${RTT_CC_PREFIX}"
echo "EXEC_PATH => ${RTT_EXEC_PATH}"
