#!/bin/bash

export RTT_CC=gcc
export RTT_EXEC_PATH=$(pwd)/tools/arm-linux-musleabi_for_x86_64-pc-linux-gnu/bin
export RTT_CC_PREFIX=arm-linux-musleabi-
export PATH=$PATH:$RTT_EXEC_PATH

echo "arch      => arm"
echo "CC        => ${RTT_CC}"
echo "PREFIX    => ${RTT_CC_PREFIX}"
echo "EXEC_PATH => ${RTT_EXEC_PATH}"
