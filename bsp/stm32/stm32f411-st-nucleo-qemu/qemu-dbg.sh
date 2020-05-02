#!/bin/bash



qemu-system-gnuarmeclipse --verbose --verbose --board NUCLEO-F411RE --mcu STM32F411RE --gdb tcp::1234 -S -d unimp,guest_errors  --image rtthread.elf --semihosting-config enable=on,target=native --semihosting-cmdline hello_rtos 1 2 3

