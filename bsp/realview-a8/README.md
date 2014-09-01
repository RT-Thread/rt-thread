VMM BSP on realview-pb-a8

This is a demo program that run RT-Thread VMM(Virtual Machine Module) on
the single core RealView-PB-A8.

To compile it, you need buildroot and a linux 3.8.x source tree. You should
build the patched Linux kernel and builroot before building the VMM. This
directory has a "mk.sh" helper script to build both the RT-Thread, Linux kernel
module and the ramdisk.

Linux console is serial0 and RT-Thread console is serial1.
