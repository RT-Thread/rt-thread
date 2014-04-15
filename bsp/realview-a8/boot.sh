#!/bin/sh -e
scons -j12
qemu-system-arm -M realview-pb-a8 -kernel rtthread-realview.elf -serial vc -serial stdio
