#!/bin/bash

if [ ! -f "sd.bin" ];then
dd if=/dev/zero of=sd.bin bs=1024 count=65536
fi
qemu-system-gnuarmeclipse --verbose --verbose --board NUCLEO-F411RE --mcu STM32F411RE -d unimp,guest_errors  --image rtthread.elf  -sd sd.bin 

