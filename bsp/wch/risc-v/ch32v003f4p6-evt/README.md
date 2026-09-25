# ch32v003f4p6-evt BSP 说明

## 1 开发板简介

CH32V003F4P6-EVT 是 WCH 推出的一款基于 RISC-V 内核的开发板，最高主频为 48MHz。

**基本特性：**

- MCU：CH32V003F4P6，主频 48MHz，Flash 16KB，SRAM 2KB
- 封装：TSSOP20
- USB：1 个 Type-C，只供电
- 板上无 WCH-Link，需外接

更多信息请访问 [CH32V003](https://www.wch.cn/products/CH32V003.html) 以及 [openwch/ch32v003](https://github.com/openwch/ch32v003)

## 2 编译说明

板级包支持 RISC-V GCC 开发环境，以下是具体版本信息：

| IDE/编译器 | 已测试版本           |
| ---------- | -------------------- |
| GCC        | WCH RISC-V GCC 8.2.0 |

## 3 使用说明

> 本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果。

### 3.1 使用 Env 编译 BSP

1. [下载 WCH 编译工具链](https://github.com/NanjingQinheng/sdk-toolchain-RISC-V-GCC-WCH)
2. 下载 Env 工具 [最新版本](https://github.com/RT-Thread/env-windows/releases)
3. 在当前 BSP 目录下执行 `scons --exec-path=工具链的bin目录`
4. 编译完成之后会生成 **rtthread.bin** 文件。默认只打开 GPIO 和 UART1。

### 3.2 硬件连接

使用杜邦线连接 WCH-LinkE：3V3–VCC，GND–GND，SWDIO–PD1。不接 SWCLK，不要用 LinkE 的 5V 给板子供电。

串口另外交叉连接：LinkE 的 TX 接板子 PD6，RX 接板子 PD5。

### 3.3 下载

打开 WCH-LinkUtility，Series 选择 CH32V003，选择刚刚生成的 **rtthread.bin** 进行下载。不要勾选 Erase All。

> 注意：Chip Mem 不要点 Set。芯片正在运行时直接下载会失败，要先拉住复位再下载。

### 3.4 运行结果

在终端工具里打开 WCH-Link 的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息和 `msh >`。
