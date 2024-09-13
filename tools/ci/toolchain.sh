#!/bin/bash

# 定义工具链下载链接
declare -A download_urls=(
["arm-none-eabi-gcc"]="https://github.com/RT-Thread/toolchains-ci/releases/download/v1.3/gcc-arm-none-eabi-10-2020-q4-major-x86_64-linux.tar.bz2"
["mips-sde-elf-gcc"]="https://github.com/RT-Thread/toolchains-ci/releases/download/v1.6/gcc-arm-10.2-2020.11-x86_64-aarch64-none-elf.tar.xz"
["riscv64-unknown-elf-gcc"]="https://github.com/RT-Thread/toolchains-ci/releases/download/v1.4/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-ubuntu14.tar.gz"
["riscv32-unknown-elf-gcc"]="https://github.com/hpmicro/riscv-gnu-toolchain/releases/download/2022.05.15/riscv32-unknown-elf-newlib-multilib_2022.05.15_linux.tar.gz"
["llvm-arm"]="https://github.com/ARM-software/LLVM-embedded-toolchain-for-Arm/releases/download/release-16.0.0/LLVMEmbeddedToolchainForArm-16.0.0-Linux-x86_64.tar.gz"
["riscv-none-embed-gcc"]="https://github.com/RT-Thread/toolchains-ci/releases/download/v1.5/xpack-riscv-none-embed-gcc-8.3.0-2.3-linux-x64.tar.gz"
["riscv32-esp-elf-gcc"]="https://github.com/espressif/crosstool-NG/releases/download/esp-2022r1-RC1/riscv32-esp-elf-gcc11_2_0-esp-2022r1-RC1-linux-amd64.tar.xz"
["clang"]="https://github.com/ARM-software/LLVM-embedded-toolchain-for-Arm/releases/download/release-16.0.0/LLVMEmbeddedToolchainForArm-16.0.0-Linux-x86_64.tar.gz"

)

show_help() {
	echo "Available toolchains:"
	for key in "${!download_urls[@]}"; do
		echo "  - $key"
	done
}

extract_file() {
	local file_name=$1
	local destination=${2:-/opt}  # 默认解压到/opt目录
	case "$file_name" in
		*.tar.bz2) tar -xjf "$file_name" -C "$destination";;
		*.tar.gz)  tar -xzf "$file_name" -C "$destination";;
		*.tar.xz)  tar -xJf "$file_name" -C "$destination";;
		*) echo "Unsupported file format: $file_name"; exit 1;;
	esac
	echo "Extracted to $destination"
}

install_toolchain() {
	local toolchain_name=$1
	local url="${download_urls[$toolchain_name]}"
	if [ -z "$url" ]; then
		echo "Toolchain not found."
		exit 1
	fi
	local file_name=$(basename "$url")
	echo "Downloading $file_name..."
	wget -q "$url"
	echo "Extracting $file_name..."
	extract_file "$file_name"
	local extracted_dir="/opt/$(basename "$file_name" .tar.*)"
	echo "Installed: $extracted_dir"
}

if [[ "$1" == "help" ]]; then
	show_help
elif [ "$1" == "all" ]; then
	for toolchain in "${!download_urls[@]}"; do
		install_toolchain "$toolchain"
	done
else
	install_toolchain "$1"
fi
