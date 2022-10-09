# RK3568 板级支持包说明

中文页 | [English](README.md)

## 1. 简介

RK3568 是一款定位中高端的通用型 SOC，采用 22nm 制程工艺，集成四核 2GHz，Cortex-A55 架构和 Mali G52 GPU，支持 4K 解码和 1080P 编码。支持 SATA/PCIE/USB3.0 等各类型外围接口，内置独立的 0.8T NPU，可用于轻量级 AI 应用。支持双千兆以太网口，LPDDR4 内存等。

这份 RT-Thread BSP是针对 RK3568 的一份移植。开发者可选择使用 RADXA ROCK 3A 版本的 RK3568 廉价体验，其甚至可超量替代树莓派4B。

## 2. 编译说明

建议使用ARM Developer GNU交叉编译工具链，目前支持Linux/Windows平台：
```
https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-a/downloads/
```
下载x86_64 Hosted平台下载对应的`xxx-aarch64-none-elf`二进制包，解压后设置`RTT_EXEC_PATH`环境变量为该编译器的bin目录下即可。

进入到`rt-thread/bsp/rockchip/rk3568`目录进行输入：
```
scons
```
可以看到正常生成`rtthread.elf`与`rtthread.bin`文件。

或者通过 `scons --exec-path="GCC工具链路径"` 命令，在指定工具链位置的同时直接编译。

## 3. 执行

RK3568 根据不同的开发板实现有不同的 Kernel 烧写方式，推荐烧录进 SD 卡：（[官方板](https://wiki.t-firefly.com/zh_CN/ROC-RK3568-PC/hardware_doc.html)|[RADXA ROCK 3A](https://wiki.radxa.com/Rock3/install/microSD)）。

在烧写完 Kernel 后，将`rtthread.bin`放入 EFI 分区（第二分区），并在该分区的`boot.cmd`最前面中添加如下行：
```shell
fatload mmc 1:1 0x208000 /rtthread.bin;dcache flush;go 0x208000
```
修改脚本后，在该分区生成二进制脚本`boot.scr`:
```shell
# Linux 下安装 uboot-mkimage 软件包，Windows 下使用 MSYS2 安装 u-boot-tools 软件包
mkimage -C none -A arm -T script -d boot.cmd boot.scr
```

根据不同的开发板实现串口最多可支持到 UART0~9，本工程默认使用 UART2（[官方板](https://wiki.t-firefly.com/zh_CN/ROC-RK3568-PC/debug.html)|[RADXA ROCK 3A](https://wiki.radxa.com/Rock3/dev/serial-console)），波特率 1500000，请确保使用的串口支持该波特率。

```
heap: [0x002663f0 - 0x042663f0]

 \ | /
- RT -     Thread Operating System
 / | \     4.1.0 build Mar 19 2022 17:17:29
 2006 - 2022 Copyright by RT-Thread team
Hi, this is RT-Thread!!
msh />
```

## 4.支持情况

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | UART0~9 |
