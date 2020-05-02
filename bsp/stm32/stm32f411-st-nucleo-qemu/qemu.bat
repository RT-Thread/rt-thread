@echo off
if exist sd.bin goto run
qemu-img create -f raw sd.bin 64M

:run
E:\env\tools\qemu\xPacks\@xpack-dev-tools\qemu-arm\2.8.0-8.1\.content\bin\qemu-system-gnuarmeclipse --board NUCLEO-F411RE --image rtthread.elf -sd sd.bin 

