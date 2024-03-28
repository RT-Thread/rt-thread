#!/bin/bash

PROJECT_PATH=$1
IMAGE_NAME=$2

if [ -z "$PROJECT_PATH" ] || [ -z "$IMAGE_NAME" ]; then
	echo "Usage: $0 <PROJECT_DIR> <IMAGE_NAME>"
	exit 1
fi

ROOT_PATH=$(pwd)
echo $ROOT_PATH

function get_board_type()
{
	BOARD_CONFIG=("CONFIG_BOARD_TYPE_MILKV_DUO" "CONFIG_BOARD_TYPE_MILKV_DUO_SPINOR" "CONFIG_BOARD_TYPE_MILKV_DUO_SPINAND" "CONFIG_BOARD_TYPE_MILKV_DUO256M")
	BOARD_VALUE=("milkv-duo" "milkv-duo-spinor" "milkv-duo-spinand" "milkv-duo256m")

	for ((i=0;i<${#BOARD_CONFIG[@]};i++))
	do
		config_value=$(grep -w "${BOARD_CONFIG[i]}" ${PROJECT_PATH}/.config | cut -d= -f2)
		if [ "$config_value" == "y" ]; then
			BOARD_TYPE=${BOARD_VALUE[i]}
			break
		fi
	done
}

get_board_type
echo "board_type: ${BOARD_TYPE}"

COUNTRY=China
function get_country()
{
	restult=$(curl -m 10 -s http://www.ip-api.com/json)
	COUNTRY=$(echo $restult | sed 's/.*"country":"\([^"]*\)".*/\1/')
	echo "Country: $COUNTRY"
}

if [ "$COUNTRY" == "China" ]; then
	cvitek_bootloader_url=https://gitee.com/flyingcys/cvitek_bootloader
else
	cvitek_bootloader_url=https://github.com/flyingcys/cvitek_bootloader
fi

if [ ! -d cvitek_bootloader ]; then
	echo "cvitek_bootloader not exist, clone it from ${cvitek_bootloader_url}"
	git clone ${cvitek_bootloader_url}

	if [ $? -ne 0 ]; then
    	echo "Failed to clone ${cvitek_bootloader_url} !"
      	exit 1
    fi
fi

export BLCP_2ND_PATH=${PROJECT_PATH}/${IMAGE_NAME}

pushd cvitek_bootloader

. env.sh

get_build_board ${BOARD_TYPE}

echo "board: ${MV_BOARD_LINK}"

if [ ! -d opensbi/build/platform/generic ] || [ ! -d fsbl/build/${MV_BOARD_LINK} ] ||  [ ! -d u-boot-2021.10/build/${MV_BOARD_LINK} ]; then
	do_build
	
	CHIP_ARCH_L=$(echo $CHIP_ARCH | tr '[:upper:]' '[:lower:]')
	cp -rf build/output/${MV_BOARD_LINK}/cvi_board_memmap.ld ${ROOT_PATH}/c906_little/board/script/${CHIP_ARCH_L}
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