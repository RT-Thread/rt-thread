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

./script/sdcard.sh > /dev/null
result=$?

if [ $result -eq 1 ]; then
	echo "ERROR: The kernel file to be flashed does not exist!"
	exit 1
fi
if [ $result -eq 2 ]; then
	echo "ERROR: The USB/SDcard does not exist!"
	exit 1
fi

echo "INFO: The kernel file has been flashed to the USB/SDcard successfully!"

popd > /dev/null
