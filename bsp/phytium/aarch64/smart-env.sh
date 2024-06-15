#!/bin/bash

export RTT_CC=gcc
export RTT_EXEC_PATH=$(pwd)/tools/aarch64-linux-musleabi_for_x86_64-pc-linux-gnu/bin
export RTT_CC_PREFIX=aarch64-linux-musleabi-
export PATH=$PATH:$RTT_EXEC_PATH

echo "arch      => aarch64"
echo "CC        => ${RTT_CC}"
echo "PREFIX    => ${RTT_CC_PREFIX}"
echo "EXEC_PATH => ${RTT_EXEC_PATH}"
