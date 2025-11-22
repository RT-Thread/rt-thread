QEMU_CMD="qemu-system-riscv64 -nographic -machine virt -m 256M -kernel rtthread.bin -s -S"

if grep -q "#define RT_USING_SMP" ./rtconfig.h 2>/dev/null; then
    hart_num=$(grep "RT_CPUS_NR = [0-9]*;" ./link_cpus.lds | awk -F'[=;]' '{gsub(/ /, "", $2); print $2}')
    if [ -z "$hart_num" ]; then
        hart_num=1
    fi
    QEMU_CMD="$QEMU_CMD -smp $hart_num"
fi

QEMU_CMD="$QEMU_CMD \
-drive if=none,file=sd.bin,format=raw,id=blk0 -device virtio-blk-device,drive=blk0,bus=virtio-mmio-bus.0 \
-netdev user,id=tap0 -device virtio-net-device,netdev=tap0,bus=virtio-mmio-bus.1 \
-device virtio-serial-device -chardev socket,host=127.0.0.1,port=4321,server=on,wait=off,telnet=on,id=console0 -device virtserialport,chardev=console0"

eval $QEMU_CMD