#!/bin/bash

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
		git clone -b for-k230 ${url_rttpkgtool} ${project_path}/rttpkgtool

		if [ $? -ne 0 ]; then
			echo "Failed to clone ${url_rttpkgtool} !"
			exit 1
		fi
	else
		echo "rttpkgtool already exists"
		pushd ${project_path}/rttpkgtool
		git checkout for-k230
		git pull
		popd
	fi
}

BSP_PATH=$(realpath $(dirname $0))
echo "BSP_PATH: $BSP_PATH"

download_rttpkgtool $BSP_PATH

pushd $BSP_PATH/rttpkgtool > /dev/null
DPT_PATH_KERNEL=$BSP_PATH ./script/mkpkg.sh
popd > /dev/null
