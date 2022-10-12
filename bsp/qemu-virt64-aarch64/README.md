# QEMU/AArch64 VIRT BSP Introduction

[中文页](README_zh.md) | English

## 1. Introduction

The AArch64 execution state was introduced with the ARMv8 ISA for machines executing A64 instructions. This project ported RT-Thread on QEMU AArch64 VIRT machine.

## 2. Compiling

Usage ARM Developer GNU ToolChain, it support Linux and Windows:
```
https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads/
```
Download the `xxx-aarch64-none-elf` of x86_64 hosted platform，set the `RTT_EXEC_PATH` is system environment after decompress the binary.

Enter directory `rt-thread/bsp/qemu-virt64-aarch64` and input:
```
scons
```

## 3. Execution

The project execution tool is `qemu-system-aarch64`, the project can be configured to `Cortex-A53/A57/A72`, GIC supports `V2/V3` version, and `V2` of GIC can use 8 processors max.

Download Windows platform from website:
```
https://www.qemu.org/download/
```
On Linux platform (Ubuntu, Deepin and so on), install QEMU by apt.
```
sudo apt update
sudo apt install qemu-system-arm
```

Please fixup the exec scripts if modify the default configuration of the project. Run qemu.bat or qemu.sh in terminal:
```
heap: [0x40042aa0 - 0x40142aa0]

 \ | /
- RT -     Thread Operating System
 / | \     4.0.4 build Aug  6 2021
 2006 - 2021 Copyright by rt-thread team
Hi, this is RT-Thread!!
msh />
```

Use VirtIO-Console in new terminal by:
````
telnet 127.0.0.1 4321
````

If use tap net mode with tap0 card, modify qemu run script config
```
-netdev user,id=net0
```
to
```
-netdev tap,id=net0,ifname=tap0
```

## 4. Condition

| Driver | Condition | Remark |
| ------ | --------- | ------ |
| UART   | Support   | UART0  |
| RTC    | Support   | - |
| GPIO   | Support   | - |
| VIRTIO BLK | Support | - |
| VIRTIO NET | Support | - |
| VIRTIO Console | Support | - |
| VIRTIO GPU | Support | 2D |
| VIRTIO Input | Support | Keyboard, Mouse, Tablet |