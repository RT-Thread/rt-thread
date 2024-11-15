#!/bin/bash

PROJECT_PATH=$1
IMAGE_NAME=$2

if [ -z "$PROJECT_PATH" ] || [ -z "$IMAGE_NAME" ]; then
	echo "Usage: $0 <PROJECT_DIR> <IMAGE_NAME>"
	exit 1
fi

ROOT_PATH=$(pwd)
echo $ROOT_PATH

. board_env.sh

get_board_type
echo "board_type: ${BOARD_TYPE}"

check_bootloader || exit 0

export BLCP_2ND_PATH=${PROJECT_PATH}/${IMAGE_NAME}

pushd cvitek_bootloader

. env.sh

get_build_board ${BOARD_TYPE}

echo "board: ${MV_BOARD_LINK}"

if [ ! -d opensbi/build/platform/generic ] || [ ! -d fsbl/build/${MV_BOARD_LINK} ] ||  [ ! -d u-boot-2021.10/build/${MV_BOARD_LINK} ]; then
	do_build

else
	echo "Build already done, skip build"

	do_combine

	if [ $? -ne 0 ]; then
		do_build
	fi
fi

popd

mkdir -p output/${MV_BOARD}
cp -rf cvitek_bootloader/install/soc_${MV_BOARD_LINK}/fip.bin output/${MV_BOARD}/fip.bin
