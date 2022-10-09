# QEMU/AArch64 VIRT板级支持包说明

中文页 | [English](README.md)

## 1. 简介

AArch64是一种采用ARMv8 ISA，用于执行A64指令的机器的64位执行模式。本工程是在QEMU的AArch64 VIRT版本上进行的一份移植。

## 2. 编译说明

建议使用ARM Developer GNU交叉编译工具链，目前支持Linux/Windows平台：
```
https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads/
```
下载x86_64 Hosted平台下载对应的`xxx-aarch64-none-elf`二进制包，解压后设置`RTT_EXEC_PATH`环境变量为该编译器的bin目录下即可。

进入到`rt-thread/bsp/qemu-virt64-aarch64`目录进行输入：
```
scons
```
可以看到正常生成`rtthread.elf`与`rtthread.bin`文件。

或者通过 `scons --exec-path="GCC工具链路径"` 命令，在指定工具链位置的同时直接编译。

## 3. 执行

本工程执行环境为`qemu-system-aarch64`模拟器，工程可配置为使用`Cortex-A53/A57/A72`等芯片，GIC支持`V2/V3`版本，其中`V2`最多可配置8个处理器。

Windows平台下，可以在此获取到QEMU：
```
https://www.qemu.org/download/
```
Linux平台下，以Ubuntu、Deepin系列发行版为例，可通过该命令安装QEMU：
```
sudo apt update
sudo apt install qemu-system-arm
```

工程默认配置修改后请注意修改运行脚本。在终端执行qemu.bat或qemu.sh可以看到程序运行：
```
heap: [0x40042aa0 - 0x40142aa0]

 \ | /
- RT -     Thread Operating System
 / | \     4.0.4 build Aug  6 2021
 2006 - 2021 Copyright by rt-thread team
Hi, this is RT-Thread!!
msh />
```

如果需要使用VirtIO-Console，请在新终端使用以下命令连接控制台：
```
telnet 127.0.0.1 4321
```

如果使用tap网卡模式，以设备tap0为例，将qemu运行脚本
```
-netdev user,id=net0
```
修改为
```
-netdev tap,id=net0,ifname=tap0
```

## 4.支持情况

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | UART0 |
| RTC  | 支持 | - |
| GPIO | 支持 | - |
| VIRTIO BLK | 支持 | - |
| VIRTIO NET | 支持 | - |
| VIRTIO Console | 支持 | - |
| VIRTIO GPU | 支持 | 2D |
| VIRTIO Input | 支持 | Keyboard, Mouse, Tablet |