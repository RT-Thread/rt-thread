#!/bin/bash

declare -A download_urls=(
["arm-none-eabi-gcc"]="https://github.com/RT-Thread/toolchains-ci/releases/download/v1.3/gcc-arm-none-eabi-10-2020-q4-major-x86_64-linux.tar.bz2"
["mips-sde-elf-gcc"]="https://github.com/RT-Thread/toolchains-ci/releases/download/v1.1/mips-2016.05-7-mips-sde-elf-i686-pc-linux-gnu.tar.bz2"
["aarch64-none-elf-gcc"]="https://github.com/RT-Thread/toolchains-ci/releases/download/v1.6/gcc-arm-10.2-2020.11-x86_64-aarch64-none-elf.tar.xz"
["riscv64-unknown-elf-gcc"]="https://github.com/RT-Thread/toolchains-ci/releases/download/v1.4/riscv64-unknown-elf-toolchain-10.2.0-2020.12.8-x86_64-linux-ubuntu14.tar.gz"
["riscv32-unknown-elf-gcc"]="https://github.com/hpmicro/riscv-gnu-toolchain/releases/download/2022.05.15/riscv32-unknown-elf-newlib-multilib_2022.05.15_linux.tar.gz"
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
	local destination=$2
	echo "Extracting $file_name to $destination..."
	case "$file_name" in
		*.tar.bz2) tar -xjf "$file_name" -C "$destination" --strip-components=1;;
		*.tar.gz)  tar -xzf "$file_name" -C "$destination" --strip-components=1;;
		*.tar.xz)  tar -xJf "$file_name" -C "$destination" --strip-components=1;;
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

	local target_dir="/opt/$toolchain_name"
	echo "target_dir $target_dir..."
	mkdir -p "$target_dir"
	extract_file "$file_name" "$target_dir"

	rm $file_name

	echo "Installed: $target_dir"

	local toolchain_bin="$target_dir/bin"
	if [[ ":$PATH:" != *":$toolchain_bin:"* ]]; then
		echo "Adding $toolchain_bin to PATH..."
		export PATH="$PATH:$toolchain_bin"
		echo "export PATH=\$PATH:$toolchain_bin" >> ~/.bashrc
	fi
	#need source toolchain.sh or source ~/.bashrc to work

	#local toolchain_exec=$(find "$toolchain_bin" -type f -executable | head -n 1)
	local toolchain_exec=$(which "$toolchain_name")
	if [ -x "$toolchain_exec" ]; then
		echo "Testing executable: $toolchain_exec"
		$toolchain_exec --version
	else
		echo "No executable found in $toolchain_bin"
	fi
}

if [[ $# -eq 1 ]]; then
	if [[ "$1" == "help" ]]; then
		show_help
	elif [ "$1" == "all" ]; then
		for toolchain in "${!download_urls[@]}"; do
			install_toolchain "$toolchain"
		done
	else
		install_toolchain "$1"
	fi
else
	show_help  
fi
