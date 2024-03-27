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

echo "start compress kernel..."

lzma -c -9 -f -k ${PROJECT_PATH}/${IMAGE_NAME} > ${PROJECT_PATH}/Image.lzma

mkdir -p ${ROOT_PATH}/output/${BOARD_TYPE}
./mkimage -f ${PROJECT_PATH}/multi.its -r ${ROOT_PATH}/output/${BOARD_TYPE}/boot.sd