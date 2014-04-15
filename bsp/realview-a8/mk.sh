#!/bin/sh

set -e

KDIR=~/linux-git
BUILD_ROOT_DIR=/temp-build/buildroot-2014.02/

scons -j20
mkdir -p $BUILD_ROOT_DIR/output/target/vmm
cp rtthread.bin $BUILD_ROOT_DIR/output/target/vmm

(
cd ./linux_vmm/
export PATH=/opt/gcc-linaro-arm-linux-gnueabihf-4.8-2013.10_linux/bin/:"$PATH"
make -C $KDIR M=$PWD VMM_HDR_DIR=$PWD/../ ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
cp rtvmm.ko $BUILD_ROOT_DIR/output/target/root/
)

make -C $BUILD_ROOT_DIR
