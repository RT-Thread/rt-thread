if [ ! -f "sd.bin" ]; then
    dd if=/dev/zero of=sd.bin bs=1024 count=65536
fi

qemu-system-aarch64 -M raspi4b -serial stdio \
    -kernel rtthread.bin \
    -drive if=sd,file=sd.bin \
    -dtb bcm2711-rpi-4-b.dtb \
    -append 'printk.time=0 earlycon=pl011,0xfe201000 console=ttyAMA0 root=ram0 rw'
