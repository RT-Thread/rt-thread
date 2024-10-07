#!/bin/bash

function check_board()
{
	local config_file=$1/.config

	board_type=$(grep -E '^CONFIG_BOARD_TYPE_.*=y' "$config_file" | sed 's/CONFIG_BOARD_TYPE_//;s/=y$//')

	if [ -z "$board_type" ]; then
		echo "No board type found in the config file."
		return 1
	fi

	BOARD_TYPE=$(echo "$board_type" | tr '[:upper:]' '[:lower:]')
	STORAGE_TYPE="${BOARD_TYPE##*_}"

	soc_type=$(grep -E '^CONFIG_SOC_TYPE_.*=y' "$config_file" | sed 's/CONFIG_SOC_TYPE_//;s/=y$//')
	if [ -z "$soc_type" ]; then
		echo "No soc type found in the config file."
		return 1
	fi

	SOC_TYPE=$(echo "$soc_type" | tr '[:upper:]' '[:lower:]')

	export BOARD_TYPE STORAGE_TYPE SOC_TYPE
	
	return 0
}