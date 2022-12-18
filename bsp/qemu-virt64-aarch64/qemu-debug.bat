@echo off
if exist sd.bin goto run
qemu-img create -f raw sd.bin 64M

:run
qemu-system-aarch64 -M virt,gic-version=2 -cpu cortex-a53 -smp 4 -kernel rtthread.bin -nographic ^
-drive if=none,file=sd.bin,format=raw,id=blk0 -device virtio-blk-device,drive=blk0,bus=virtio-mmio-bus.0 ^
-netdev user,id=net0 -device virtio-net-device,netdev=net0,bus=virtio-mmio-bus.1 -s -S ^
-device virtio-serial-device -chardev socket,host=127.0.0.1,port=4321,server=on,wait=off,telnet=on,id=console0 -device virtserialport,chardev=console0
