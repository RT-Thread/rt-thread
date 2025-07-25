#!/bin/bash

source ./utils.sh

BSP_PATH=$(realpath $(dirname $0))
echo "BSP_PATH: $BSP_PATH"

download_rttpkgtool $BSP_PATH
result=$?
if [ $result -ne 0 ]; then
	echo "ERROR: rttpkgtool is unavailable! Please check your network connection!"
	exit 1
fi

pushd $BSP_PATH/rttpkgtool > /dev/null
DPT_PATH_KERNEL=$BSP_PATH ./script/mkpkg.sh
popd > /dev/null
