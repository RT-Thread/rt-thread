qemu-system-riscv64 -nographic -machine virt -cpu rv64,v=true,vlen=128,vext_spec=v1.0 -m 256M -kernel rtthread.bin -s -S \
-drive if=none,file=sd.bin,format=raw,id=blk0 -device virtio-blk-device,drive=blk0,bus=virtio-mmio-bus.0 \
-device virtio-serial-device -chardev socket,host=127.0.0.1,port=4321,server=on,wait=off,telnet=on,id=console0 -device virtserialport,chardev=console0
