# NOTE: Don't execute this script directly. It should be sourced by another script.
# Description: This script contains utility functions.

function get_board_type()
{
	local project_path=$1
	local supported_board_configs=("CONFIG_BOARD_TYPE_MILKV_DUO" "CONFIG_BOARD_TYPE_MILKV_DUO256M" "CONFIG_BOARD_TYPE_MILKV_DUOS")
	local supported_board_types=("duo" "duo256m" "duos")

	local board_type="N/A"

	for ((i=0; i< ${#supported_board_configs[@]}; i++))
	do
		config_value=$(grep -w "${supported_board_configs[i]}" ${project_path}/.config | cut -d= -f2)
		if [ "$config_value" == "y" ]; then
			board_type=${supported_board_types[i]}
			break
		fi
	done

	echo ${board_type}
}

function download_rttpkgtool()
{
	local project_path=$1
	local restult=$(curl -m 10 -s http://www.ip-api.com/json)
	local country=$(echo $restult | sed 's/.*"country":"\([^"]*\)".*/\1/')
	#echo "Country: $country"

	if [ "$country" == "China" ]; then
		local url_rttpkgtool="https://gitee.com/unicornx/rttpkgtool.git"
	else
		local url_rttpkgtool="https://github.com/plctlab/rttpkgtool.git"
	fi
	#echo "rttpkgtool URL: ${url_rttpkgtool}"

	if [ ! -d ${project_path}/rttpkgtool ]; then
		echo "rttpkgtool does not exist, clone it from ${url_rttpkgtool}"
		git clone ${url_rttpkgtool} ${project_path}/rttpkgtool

		if [ $? -ne 0 ]; then
			echo "Failed to clone ${url_rttpkgtool} !"
			exit 1
		fi
	else
		echo "rttpkgtool already exists"
		pushd ${project_path}/rttpkgtool
		git checkout main
		git pull
		popd
	fi
}