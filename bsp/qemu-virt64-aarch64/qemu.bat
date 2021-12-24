@echo off
if exist sd.bin goto run
qemu-img create -f raw sd.bin 64M

:run
qemu-system-aarch64 -M virt -cpu cortex-a53 -smp 4 -kernel rtthread.elf -drive if=none,file=sd.bin,format=raw,id=blk0 -device virtio-blk-device,drive=blk0,bus=virtio-mmio-bus.0 -nographic