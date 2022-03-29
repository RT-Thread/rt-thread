# RK3568 BSP Introduction

[中文页](README_zh.md) | English

## 1. Introduction

RK3568 is a general-purpose SOC, quad-core 64-bit Cortex-A55 processor, with 22nm lithography process, has frequency up to 2.0GHz and Mali G52 GPU, support 4K decoding and 1080P encoding. Support mangy interfaces such as SATA/PCIE/USB3.0, an 0.8T NPU for lightweight AI applications. Support dual Gigabit Ethernet ports, LPDDR4 memory, etc.

This project ported RT-Thread on RK3568, you can use the RADXA ROCK 3A version of the RK3568 in low-priced, which can even replace the Raspberry Pi 4B.

## 2. Compiling

Usage ARM Developer GNU ToolChain, it support Linux and Windows:
```
https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads/
```
Download the `xxx-aarch64-none-elf` of x86_64 hosted platform, set the `RTT_EXEC_PATH` is system environment after decompress the binary.

Enter directory `rt-thread/bsp/qemu-virt64-aarch64` and input:
```
scons
```

## 3. Execution

RK3568 has different Kernel install methods according to different boardsit, recommend to install into the SD card: ([Official](https://wiki.t-firefly.com/en/ROC-RK3568-PC/hardware_doc.html)|[RADXA ROCK 3A](https://wiki.radxa.com/Rock3/install/microSD)).

After install Kernel, storage the `rtthread.bin` to EFI partition (the second partition), and add this line in the front of `boot.cmd` in this partition:
```shell
fatload mmc 1:1 0x208000 /rtthread.bin;dcache flush;go 0x208000
```
After modifying the script, build a binary script `boot.scr ` in this partition:
```shell
# Install the uboot-mkimage package on Linux, or use MSYS2 to install the u-boot-tools package on Windows
mkimage -C none -A arm -T script -d boot.cmd boot.scr
```

According to different boards, the serial port can support up to UART0~9, this project uses UART2 ([Official](https://wiki.t-firefly.com/en/ROC-RK3568-PC/debug.html)|[RADXA ROCK 3A](https://wiki.radxa.com/Rock3/dev/serial-console)) by default, the baud rate is 1500000, please make sure that the serial port used supports this baud rate.

```
heap: [0x002663f0 - 0x042663f0]

 \ | /
- RT -     Thread Operating System
 / | \     4.1.0 build Mar 19 2022 17:17:29
 2006 - 2022 Copyright by RT-Thread team
Hi, this is RT-Thread!!
msh />
```

## 4. Condition

| Driver | Condition | Remark |
| ------ | --------- | ------ |
| UART   | Support   | UART0~9 |
