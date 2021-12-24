if [ ! -f "sd.bin" ]; then
dd if=/dev/zero of=sd.bin bs=1024 count=65536
fi
qemu-system-aarch64 -M virt -cpu cortex-a53 -smp 4 -kernel rtthread.elf -nographic -drive if=none,file=sd.bin,format=raw,id=blk0 -device virtio-blk-device,drive=blk0,bus=virtio-mmio-bus.0 -monitor pty
