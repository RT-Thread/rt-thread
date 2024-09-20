#/bin/sh
set -e

PROJECT_PATH=$1
IMAGE_NAME=$2

if [ -z "$PROJECT_PATH" ] || [ -z "$IMAGE_NAME" ]; then
	echo "Usage: $0 <PROJECT_DIR> <IMAGE_NAME>"
	exit 1
fi

ROOT_PATH=$(pwd)
echo ${ROOT_PATH}

. board_env.sh

echo "start compress kernel..."

if check_board ${PROJECT_PATH} ; then
	echo "board type: ${BOARD_TYPE}"
	echo "storage type: ${STORAGE_TYPE}"
else
	echo "board type not found"
	exit 1
fi

lzma -c -9 -f -k ${PROJECT_PATH}/${IMAGE_NAME} > ${PROJECT_PATH}/dtb/${BOARD_TYPE}/Image.lzma

mkdir -p ${ROOT_PATH}/output/${BOARD_TYPE}
./pre-build/tools/mkimage -f ${PROJECT_PATH}/dtb/${BOARD_TYPE}/multi.its -r ${ROOT_PATH}/output/${BOARD_TYPE}/boot.${STORAGE_TYPE}

if [ "${STORAGE_TYPE}" == "spinor" ] || [ "${STORAGE_TYPE}" == "spinand" ]; then
	
	IMGTOOL_PATH=${ROOT_PATH}/pre-build/tools/common/image_tool
	FLASH_PARTITION_XML=${ROOT_PATH}/pre-build/boards/${BOARD_TYPE}/partition/partition_"${STORAGE_TYPE}".xml
	python3 "$IMGTOOL_PATH"/raw2cimg.py "${ROOT_PATH}"/output/"${BOARD_TYPE}"/boot."$STORAGE_TYPE" "${ROOT_PATH}/output/${BOARD_TYPE}" "$FLASH_PARTITION_XML"
fi

exit 0