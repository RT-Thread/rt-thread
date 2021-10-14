if [ ! -f "sd.bin" ]; then
dd if=/dev/zero of=sd.bin bs=1024 count=65536
fi
qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial null -serial stdio -sd sd.bin -nographic -monitor pty