#!/bin/bash

usage ()
{
	echo "Usage:"
	echo "./run.sh [<path_to_image>]"
	echo "Note: if <path_to_image> is not provided, will create a 'sd.bin'"
	echo "in the current directory and load it by default."
}

path_image=${1}

if [ -z $path_image ]; then
	path_image="./sd.bin"
	if [ ! -f $path_image ]; then
		dd if=/dev/zero of=$path_image bs=1024 count=65536
		mkfs.fat $path_image
	fi
fi

if [ ! -f $path_image ]; then
	echo "ERROR: $path_image does not exist!"
	usage
	exit
fi

QEMU_CMD="qemu-system-riscv64 -nographic -machine virt -m 256M -kernel rtthread.bin"

if grep -q "#define RT_USING_SMP" ./rtconfig.h 2>/dev/null; then
    hart_num=$(grep "RT_CPUS_NR = [0-9]*;" ./link_cpus.lds 2>/dev/null | awk -F'[=;]' '{gsub(/ /, "", $2); print $2}')
    if [ -z "$hart_num" ] || [ "$hart_num" -lt 1 ]; then
        echo "Warning: Invalid or missing RT_CPUS_NR, defaulting to 1"
        hart_num=1
    fi
    QEMU_CMD="$QEMU_CMD -smp $hart_num"
fi

QEMU_CMD="$QEMU_CMD \
-drive if=none,file=$path_image,format=raw,id=blk0 -device virtio-blk-device,drive=blk0,bus=virtio-mmio-bus.0 \
-netdev user,id=tap0 -device virtio-net-device,netdev=tap0,bus=virtio-mmio-bus.1 \
-device virtio-serial-device -chardev socket,host=127.0.0.1,port=4321,server=on,wait=off,telnet=on,id=console0 -device virtserialport,chardev=console0"

eval $QEMU_CMD