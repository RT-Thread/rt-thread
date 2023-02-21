#!/bin/sh
mkimage -A riscv -O linux -T kernel -C none -a 0x45000000 -e 0x45000000 -d rtthread.bin rtthread.img