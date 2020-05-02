@echo off
if exist sd.bin goto run
qemu-img create -f raw sd.bin 64M

:run
start E:\env\tools\qemu\xPacks\@xpack-dev-tools\qemu-arm\2.8.0-8.1\.content\bin\qemu-system-gnuarmeclipse  --board NUCLEO-F411RE --mcu STM32F411RE  --image rtthread.elf  -S -s -sd sd.bin

