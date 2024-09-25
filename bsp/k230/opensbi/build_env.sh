#/bin/sh
cp ../kernel/bsp/maix3/rtthread.bin ./
export CROSS_COMPILE=~/.tools/gnu_gcc/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu/bin/riscv64-unknown-linux-musl-
export PLATFORM=kendryte/fpgac908
make FW_PAYLOAD_PATH=rtthread.bin FW_FDT_PATH=hw.dtb
