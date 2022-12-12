# RT-Smart QEMU SYSTEM RISC-V RV64 BSP

English | [中文](./README_ch.md)

## 1. Introduction

QEMU can emulate both 32-bit and 64-bit RISC-V CPUs. Use the qemu-system-riscv64 executable to simulate a 64-bit RISC-V machine, qemu-system-riscv32 executable to simulate a 32-bit RISC-V machine.

QEMU has generally good support for RISC-V guests. It has support for several different machines. The reason we support so many is that RISC-V hardware is much more widely varying than x86 hardware. RISC-V CPUs are generally built into “system-on-chip” (SoC) designs created by many different companies with different devices, and these SoCs are then built into machines which can vary still further even if they use the same SoC.

For most boards the CPU type is fixed (matching what the hardware has), so typically you don’t need to specify the CPU type by hand, except for special cases like the virt board.

## 2. Building

It's tedious to properly build a kernel since each RISC-V toolchain is specified to one RISC-V ISA. So you have to use different toolchain for different RISC-V ISAs.
Here we focus on 2 types of ISA: `rv64imafdcv` and `rv64imac`.

If you are not sure what kinds of ISA you need, then `rv64imac` should satisfied your case most time. Given a riscv toolchain, you can check the ISA it supports like this:

```bash
root@a9025fd90fd4:/home/rtthread-smart# riscv64-unknown-linux-musl-gcc -v
Using built-in specs.
COLLECT_GCC=riscv64-unknown-linux-musl-gcc
COLLECT_LTO_WRAPPER=/home/rtthread-smart/tools/gnu_gcc/riscv64-linux-musleabi_for_x86_64-pc-linux-gnu/bin/../libexec/gcc/riscv64-unknown-linux-musl/10.1.0/lto-wrapper
Target: riscv64-unknown-linux-musl
Configured with: /builds/alliance/risc-v-toolchain/riscv-gcc/configure --target=riscv64-unknown-linux-musl --prefix=/builds/alliance/risc-v-toolchain/install-native/ --with-sysroot=/builds/alliance/risc-v-toolchain/install-native//riscv64-unknown-linux-musl --with-system-zlib --enable-shared --enable-tls --enable-languages=c,c++ --disable-libmudflap --disable-libssp --disable-libquadmath --disable-libsanitizer --disable-nls --disable-bootstrap --src=/builds/alliance/risc-v-toolchain/riscv-gcc --disable-multilib --with-abi=lp64 --with-arch=rv64imac --with-tune=rocket 'CFLAGS_FOR_TARGET=-O2   -mcmodel=medany -march=rv64imac -mabi=lp64 -D __riscv_soft_float' 'CXXFLAGS_FOR_TARGET=-O2   -mcmodel=medany -march=rv64imac -mabi=lp64 -D __riscv_soft_float'
Thread model: posix
Supported LTO compression algorithms: zlib
gcc version 10.1.0 (GCC) 
```

The `-march=***` is what you are looking for. And the `-mabi=***` is also an important message to configure compiling script.

Steps to build kernel:

1. in `$RTT_ROOT/bsp/qemu-virt64-riscv/rtconfig.py:40`, make sure `-march=***` and `-mabi=***` is identical to your toolchain
1. if your -march contains characters v/d/f, then: configure kernel by typing `scons --menuconfig` and select `Using RISC-V Vector Extension` / `Enable FPU`
1. `scons`

## 3. Execution

It's recommended to clone the latest QEMU release and build it locally.
Make sure QEMU is ready by typing `qemu-system-riscv64 --version` in your shell.

Using `qemu-nographic.sh` or `qemu-nographic.bat` to start simulation.

> if your -march contains characters v, using qemu-v-nographic.*
