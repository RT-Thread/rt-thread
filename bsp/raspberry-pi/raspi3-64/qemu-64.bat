@echo off
if exist sd.bin goto run
qemu-img create -f raw sd.bin 64M

:run
qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial null -serial stdio -sd sd.bin