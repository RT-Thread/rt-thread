#!/bin/bash

# 定义从YML文件获取所有工具链链接的函数
get_all_toolchains() {
	local script_dir="$(dirname "$(readlink -f "$0")")"
	local yml_file="$script_dir/toolchain_bsp.yml"
	if [ ! -f "$yml_file" ]; then
		echo "YML file not found in the script's directory."
		exit 1
	fi
	all_urls=$(grep 'http' "$yml_file" | sed 's/.*: //')
	echo "$all_urls"
}

get_download_url() {
	local toolchain_name=$1
	local yml_file="$script_dir/toolchain_bsp.yml"
	if [ ! -f "$yml_file" ]; then
		echo "YML file not found in the script's directory."
		exit 1
	fi
	# 查找特定工具链名称的下载链接
	download_url=$(curl -s $yml_file | grep -A 1 "$toolchain_name" | grep 'http' | sed 's/.*: //')
	echo $download_url
}

if [ $# -lt 1 ]; then
	echo "Usage: $0 <toolchain_name | all>"
	exit 1
fi

toolchain_name=$1

if [ "$toolchain_name" == "all" ]; then
	urls=$(get_all_toolchains)
	for url in $urls; do
		file_name=$(basename $url)
		echo "Downloading $file_name..."
		wget -q $url
		echo "Extracting $file_name..."
		sudo tar xjf $file_name -C /opt
		extracted_dir="/opt/$(basename $file_name .tar.bz2)"
		echo "Installed: $extracted_dir"
	done
else
	# 单个工具链的安装
	download_url=$(get_download_url $toolchain_name)
	if [ -z "$download_url" ]; then
		echo "Toolchain not found in yml file."
		exit 1
	fi
	file_name=$(basename $download_url)
	echo "Downloading $file_name..."
	wget -q $download_url
	echo "Extracting $file_name..."
	sudo tar xjf $file_name -C /opt
	extracted_dir="/opt/$(basename $file_name .tar.bz2)"
fi
