if [ ! -f "sd.bin" ]; then
dd if=/dev/zero of=sd.bin bs=1024 count=65536
mkfs.fat sd.bin
fi
qemu-system-aarch64 -M virt,gic-version=2 -cpu cortex-a53 -smp 4 -kernel rtthread.bin -serial stdio \
-drive if=none,file=sd.bin,format=raw,id=blk0 -device virtio-blk-device,drive=blk0,bus=virtio-mmio-bus.0 \
-netdev user,id=net0 -device virtio-net-device,netdev=net0,bus=virtio-mmio-bus.1 \
-device virtio-gpu-device,xres=800,yres=600,bus=virtio-mmio-bus.2 \
-device virtio-keyboard-device,bus=virtio-mmio-bus.3 \
-device virtio-mouse-device,bus=virtio-mmio-bus.4 \
-device virtio-tablet-device,bus=virtio-mmio-bus.5 \
-device virtio-serial-device -chardev socket,host=127.0.0.1,port=4321,server=on,wait=off,telnet=on,id=console0 -device virtserialport,chardev=console0
