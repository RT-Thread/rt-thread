#! /bin/bash

export LC_ALL=C.UTF-8
export LANG=C.UTF-8

usage() {
	echo "usage: ./mkimage.sh [partition_setting]"
}

CUR_DIR=$(pwd)
TOOLS=$CUR_DIR/../tools
IMAGE=$CUR_DIR/image

rm -rf $CUR_DIR/rtthread.bin $IMAGE/rtthread.img $IMAGE/Firmware*
scons -c
scons -j16
cp -r $CUR_DIR/rtthread.bin $IMAGE/rtthread.img
$TOOLS/resource_header_tool pack --json $IMAGE/config.json $IMAGE/rtthread.img > /dev/null

echo 'Image: rthread image is ready'

if [ ! -n "$1" ] ;then
    $TOOLS/firmware_merger -p $CUR_DIR/board/common/setting.ini $IMAGE/
else
    $TOOLS/firmware_merger -p $1 $IMAGE/
fi

echo 'Image: firmware image is ready'
