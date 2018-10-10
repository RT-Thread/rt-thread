#  i.MX RT1050 Arch Mix

## 1. 简介

i.MX RT 1050系列芯片，是由 NXP 半导体公司推出的跨界处理器芯片。它基于应用处理器的芯片架构，采用了微控制器的内核Cortex-M7，从而具有应用处理器的高性能及丰富的功能，又具备传统微控制器的易用、实时及低功耗的特性。

BSP默认支持的i.MX RT1052处理器具备以下简要的特性：

| 介绍 | 描述 |
| ---- | ---- |
| 主CPU平台 | ARM Cortex-M7 |
| 最高频率 | 600MHz |
| 内部存储器 | 512KB  SRAM |
| 外部存储器接口 | NAND、eMMC、QuadSPI NOR Flash 和 Parallel NOR Flash |

## 2. 编译说明

i.MX RT1050板级包支持MDK5﹑IAR开发环境和GCC编译器，以下是具体版本信息：

| IDE/编译器 | 已测试版本 |
| ---------- | --------- |
| MDK5 | MDK525 |
| IAR | IAR 8.11.3.13984 |
| GCC | GCC 5.4.1 20160919 (release) |

## 3.BSP使用

### 3.1 配置工程

i.MX RT1052 BSP 支持多种 Flash，包括 Hyper Flash 和 QSPI Flash。如果不是 QSPI Flash 版本，那么需要重新配置并生成工程：

- 在 bsp 下打开 env 工具
- 输入`menuconfig`命令，`RT1052 Flash select (***)-->`选择正确的 Flash 版本。
- 输入`scons --target=mdk5 -s`或`scons --target=iar`来生成需要的工程

### 3.2 下载和仿真

连接外置仿真器 Jlink 后，就可以进行下载和仿真。使用 TTL 转串口工具连接开发板上 J3 的19/20 引脚，在终端工具里打开相应的串口。(19 接 TX，20 接 RX)

### 3.3 运行结果

如果编译 & 烧写无误，当复位设备后，会在串口上看到RT-Thread的启动logo信息：

```
 \ | /
- RT -     Thread Operating System
 / | \     3.1.1 build Oct  9 2018
 2006 - 2018 Copyright by rt-thread team
using armcc, version: 5060750
build time: Oct  9 2018 14:21:49
msh />[I/[SDIO]] SD card capacity 123904 KB.
[I/[SDIO]] probe mmcsd block device!
found part[0], begin: 67584, size: 120.958MB
File System initialized!
```

## 4. 驱动支持情况及计划

| 驱动 | 支持情况  | 备注 |
| ------ | ----  | ------ |
| UART | 支持 | UART 1~3/8 |
| GPIO | 支持 |  |
| IIC | 支持 | IIC 1/3/4 |
| SPI | 支持 | SPI 3/4 |
| LCD | 支持 |  |
| RTC | 支持 |  |
| SDIO | 支持 | 暂时仅仅支持一个SDIO，还不支持中断方式 |
| SDRAM | 支持 | 32M SDRAM，后面 2M 作为 Non Cache 区域 |

## 5. 联系人信息

维护人：

- [tanek](https://github.com/TanekLiang)
- [liu2guang](https://github.com/liu2guang)

## 6. 参考

- [MIMXRT1050-EVK: i.MX RT1050评估套件概述](https://www.nxp.com/cn/products/processors-and-microcontrollers/applications-processors/i.mx-applications-processors/i.mx-rt-series/i.mx-rt1050-evaluation-kit:MIMXRT1050-EVK)
- [MIMXRT1050 EVK Board Hardware User’s Guide ](https://www.nxp.com/docs/en/user-guide/MIMXRT1050EVKHUG.pdf)
- [i.MX RT Series Crossover Processor Quick Start Guide](https://www.nxp.com/docs/en/user-guide/IMXRT1050EVKQSG.pdf)
- [i.MX RT Series Crossover Processor Fact Sheet](https://www.nxp.com/docs/en/fact-sheet/IMXRTSERIESFS.pdf)
- [Evaluation Kit Based on i.MX RT1050 Crossover Processors](https://www.nxp.com/docs/en/fact-sheet/IMXRT1050EVKFS.pdf)
