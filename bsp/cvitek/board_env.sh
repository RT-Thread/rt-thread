#!/bin/bash

function get_board_type()
{
	BOARD_CONFIG=("CONFIG_BOARD_TYPE_MILKV_DUO" "CONFIG_BOARD_TYPE_MILKV_DUO_SPINOR" "CONFIG_BOARD_TYPE_MILKV_DUO_SPINAND" "CONFIG_BOARD_TYPE_MILKV_DUO256M" "CONFIG_BOARD_TYPE_MILKV_DUO256M_SPINOR" "CONFIG_BOARD_TYPE_MILKV_DUO256M_SPINAND" "CONFIG_BOARD_TYPE_MILKV_DUOS")
	BOARD_VALUE=("milkv-duo" "milkv-duo-spinor" "milkv-duo-spinand" "milkv-duo256m" "milkv-duo256m-spinor" "milkv-duo256m-spinand" "milkv-duos-sd")
	STORAGE_VAUE=("sd" "spinor" "spinand" "sd" "spinor" "spinand" "sd")

	for ((i=0;i<${#BOARD_CONFIG[@]};i++))
	do
		config_value=$(grep -w "${BOARD_CONFIG[i]}" ${PROJECT_PATH}/.config | cut -d= -f2)
		if [ "$config_value" == "y" ]; then
			BOARD_TYPE=${BOARD_VALUE[i]}
			STORAGE_TYPE=${STORAGE_VAUE[i]}
			break
		fi
	done
    export BOARD_TYPE=${BOARD_TYPE}
    export STORAGE_TYPE=${STORAGE_TYPE}
}

function check_bootloader()
{
	restult=$(curl -m 10 -s http://www.ip-api.com/json)
	COUNTRY=$(echo $restult | sed 's/.*"country":"\([^"]*\)".*/\1/')
	echo "Country: $COUNTRY"

	if [ "$COUNTRY" == "China" ]; then
		BOOTLOADER_URL=https://gitee.com/flyingcys/cvitek_bootloader
	else
		BOOTLOADER_URL=https://github.com/flyingcys/cvitek_bootloader
	fi

	if [ ! -d cvitek_bootloader ]; then
	echo "cvitek_bootloader not exist, clone it from ${BOOTLOADER_URL}"
	git clone ${BOOTLOADER_URL}

	if [ $? -ne 0 ]; then
    	echo "Failed to clone ${BOOTLOADER_URL} !"
      	exit 1
    fi
fi
}

