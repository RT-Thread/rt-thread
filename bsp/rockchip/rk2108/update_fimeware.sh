#!/bin/sh

export LC_ALL=C.UTF-8
export LANG=C.UTF-8

usage() {
	echo "usage: ./update_firmware.sh"
}

CUR_DIR=$(pwd)
TOOLS=$CUR_DIR/../tools

$TOOLS/upgrade_tool db $CUR_DIR/image/rk2108_db_loader.bin
$TOOLS/upgrade_tool wl 0 $CUR_DIR/image/Firmware.img
$TOOLS/upgrade_tool rd
