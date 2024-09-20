#!/bin/bash
set -e

PROJECT_PATH=$1
IMAGE_NAME=$2

if [ -z "$PROJECT_PATH" ] || [ -z "$IMAGE_NAME" ]; then
	echo "Usage: $0 <PROJECT_DIR> <IMAGE_NAME>"
	exit 1
fi

function do_combine()
{
	local PROJECT_PATH=$1
	local IMAGE_NAME=$2

	BLCP_IMG_RUNADDR=0x05200200
	BLCP_PARAM_LOADADDR=0
	NAND_INFO=00000000
	NOR_INFO='FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF'
	FIP_COMPRESS=lzma

	BUILD_PLAT=${ROOT_PATH}/pre-build/fsbl/build/${SOC_TYPE}

	CHIP_CONF_PATH=${BUILD_PLAT}/chip_conf.bin
	DDR_PARAM_TEST_PATH=${ROOT_PATH}/pre-build/fsbl/test/ddr_param.bin
	BLCP_PATH=${ROOT_PATH}/pre-build/fsbl/test/empty.bin

	MONITOR_PATH=${ROOT_PATH}/pre-build/opensbi/${BOARD_TYPE}/fw_dynamic.bin
	LOADER_2ND_PATH=${ROOT_PATH}/pre-build/u-boot-2021.10/${BOARD_TYPE}/u-boot-raw.bin

	BLCP_2ND_PATH=$PROJECT_PATH/$IMAGE_NAME

	echo "Combining fip.bin..."
	. ./pre-build/fsbl/build/${SOC_TYPE}/blmacros.env && \
	python3 ./pre-build/fsbl/plat/fiptool.py -v genfip \
	${ROOT_PATH}/output/${BOARD_TYPE}/fip.bin \
	--MONITOR_RUNADDR="${MONITOR_RUNADDR}" \
	--BLCP_2ND_RUNADDR="${BLCP_2ND_RUNADDR}" \
	--CHIP_CONF=${CHIP_CONF_PATH} \
	--NOR_INFO=${NOR_INFO} \
	--NAND_INFO=${NAND_INFO} \
	--BL2=${BUILD_PLAT}/bl2.bin \
	--BLCP_IMG_RUNADDR=${BLCP_IMG_RUNADDR} \
	--BLCP_PARAM_LOADADDR=${BLCP_PARAM_LOADADDR} \
	--BLCP=${BLCP_PATH} \
	--DDR_PARAM=${DDR_PARAM_TEST_PATH} \
	--BLCP_2ND=${BLCP_2ND_PATH} \
	--MONITOR=${MONITOR_PATH} \
	--LOADER_2ND=${LOADER_2ND_PATH} \
	--compress=${FIP_COMPRESS}
}

ROOT_PATH=$(pwd)
echo $ROOT_PATH

. board_env.sh

if check_board ${PROJECT_PATH} ; then
	echo "board type: ${BOARD_TYPE}"
	echo "storage type: ${STORAGE_TYPE}"
else
	echo "board type not found"
	exit 1
fi

mkdir -p output/${BOARD_TYPE}
do_combine $PROJECT_PATH $IMAGE_NAME
	
echo "=== Done fip combine for ${BOARD_TYPE} successfully! ==="

exit 0