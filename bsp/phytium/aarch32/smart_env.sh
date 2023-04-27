#!/bin/bash


# usage:
# source smart-env.sh [arch]
# example: source smart-env.sh          # arm
# example: source smart-env.sh aarch64  # aarch64


# supported arch list
supported_arch="arm"


def_arch="unknown"


# find arch in arch list
if [ -z $1 ]
then
    def_arch="arm" # default arch is arm
else
    for arch in $supported_arch
    do
        if [ $arch = $1 ]
        then
            def_arch=$arch
            break
        fi
    done
fi


# set env and download toolchain

check_toolchain() {
  if [ "$def_arch" = "arm" ]; then
    toolchain_path="./tools/gnu_gcc/arm-linux-musleabi_for_x86_64-pc-linux-gnu"
    if [ ! -d "$toolchain_path" ]; then
      cd ./tools
      python3 ./get_toolchain.py
      cd ..
      if [ $? -ne 0 ]; then
        echo "Failed to download toolchain"
        return 1
      fi
    fi
    return 0
  else
    echo "unknown arch!"
    return 1
  fi
}
case $def_arch in
    "arm")
        if check_toolchain; then
        export RTT_CC=gcc
        export RTT_EXEC_PATH=$(pwd)/tools/gnu_gcc/arm-linux-musleabi_for_x86_64-pc-linux-gnu/bin
        export RTT_CC_PREFIX=arm-linux-musleabi-
        fi
        ;;
    *)  echo "unknown arch!"
        return 1
esac


# export RTT_EXEC_PATH
export PATH=$PATH:$RTT_EXEC_PATH


echo "Arch      => ${def_arch}"
echo "CC        => ${RTT_CC}"
echo "PREFIX    => ${RTT_CC_PREFIX}"
echo "EXEC_PATH => ${RTT_EXEC_PATH}"
