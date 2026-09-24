# ch32v203c-evt-r0 BSP 说明

## 1 开发板简介

CH32V203C8T6-EVT-R0 是 WCH 推出的一款基于 RISC-V 内核的开发板，最高主频为 144MHz。

**基本特性：**

- MCU：CH32V203C8T6，主频 144MHz，Flash 64KB，SRAM 20KB
- 封装：LQFP48
- LED：板载灯默认没有接到引脚，使用时要自己接杜邦线
- USB：1 个 Type-C
- 板上无 WCH-Link，需外接

更多信息请访问 [CH32V203](https://www.wch.cn/products/CH32V203.html) 以及 [openwch/ch32v20x](https://github.com/openwch/ch32v20x)

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
3. 将 [CH32V20x-SDK-for-RTT](https://github.com/kaidegit/CH32V20x-SDK-for-RTT) clone 到 `packages/CH32V20x-SDK-for-RTT`
4. 在当前 BSP 目录下执行 `scons --exec-path=工具链的bin目录`
5. 编译完成之后会生成 **rtthread.bin** 文件。默认只打开 GPIO 和 UART1。

### 3.2 硬件连接

使用杜邦线连接 WCH-LinkE：3V3–3V3，GND–GND，SWDIO–PA13，SWCLK–PA14。不要用 LinkE 的 5V 给板子供电。

串口另外交叉连接：LinkE 的 TX 接板子 PA10，RX 接板子 PA9。

### 3.3 下载

打开 WCH-LinkUtility，Series 选择 CH32V20X，选择刚刚生成的 **rtthread.bin** 进行下载。不要勾选 Erase All。

> 注意：Chip Mem 不要点 Set。本板按手册是 64K Flash + 20K SRAM，不要设成 224K ROM + 96K RAM。界面上的 Flash Size 224KB 是 V203 系列的总容量。

### 3.4 运行结果

在终端工具里打开 WCH-Link 的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息和 `msh >`。
