#!/bin/sh

set -e

# local variable
TISDK_DIR=/home/grissiom/ti-sdk-am335x-evm-06.00.00.00/

# external variable {{{
ROOTFS_DIR=${ROOTFS_DIR:-~/remotedir/buildroot-rootfs/}
KDIR=${KDIR:-$PWD/../../bfm-kernel/}

TOOLCHAIN_DIR=${TOOLCHAIN_DIR:-${TISDK_DIR}/linux-devkit/sysroots/i686-arago-linux/usr/bin}
TOOLCHAIN_PREFIX=${TOOLCHAIN_PREFIX:-"arm-linux-gnueabihf-"}
# }}}

export PATH="${TOOLCHAIN_DIR}:$PATH"

make -C $KDIR M=$PWD ARCH=arm CROSS_COMPILE="${TOOLCHAIN_PREFIX}" V=0

#sudo PATH="${TOOLCHAIN_DIR}:$PATH" \
     #make -C $KDIR M=$PWD ARCH=arm CROSS_COMPILE=${TOOLCHAIN_PREFIX} \
     #INSTALL_MOD_PATH=${ROOTFS_DIR} modules_install
