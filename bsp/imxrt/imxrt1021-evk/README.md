#  i.MX RT1020

## 1. 简介

i.MX RT 1020系列芯片，是由 NXP 半导体公司推出的跨界处理器芯片。它基于应用处理器的芯片架构，采用了微控制器的内核Cortex-M7，从而具有应用处理器的高性能及丰富的功能，又具备传统微控制器的易用、实时及低功耗的特性。

BSP默认支持的i.MX RT1021处理器具备以下简要的特性：

| 介绍 | 描述 |
| ---- | ---- |
| 主CPU平台 | ARM Cortex-M7 |
| 最高频率 | 500MHz |
| 内部存储器 | 256KB  SRAM |
| 外部存储器接口 | NAND、eMMC、QuadSPI NOR Flash 和 Parallel NOR Flash |

## 2. 编译说明

i.MX RT1021板级包支持MDK5﹑IAR开发环境和GCC编译器，以下是具体版本信息：

| IDE/编译器 | 已测试版本 |
| ---------- | --------- |
| MDK5 | MDK525 |
| IAR | IAR 8.11.3.13984 |

## 3.BSP使用

### 3.1 配置工程

i.MX RT1021 BSP支持多块开发板，包括官方开发板MIMXRT1020-EVK。如果不是基于官方开发板，那么需要重新配置并生成工程：

- 在bsp下打开env工具
- 输入`menuconfig`命令，`RT1021 Board select (***)-->`选择正确的开发板。
- 输入`scons --target=mdk5 -s`或`scons --target=iar`来生成需要的工程

### 3.2 下载和仿真

#### 3.2.1 MIMXRT1021-EVK

EVK开发板有板载OpenSDA仿真器，仿真器还连接到i.MX RT1021的UART1。使用USB线连接电脑和仿真器的USB口(J23)，就可以进行下载和仿真。在终端工具里打开仿真器的虚拟串口。

### 3.3 运行结果

如果编译 & 烧写无误，当复位设备后，会在串口上看到RT-Thread的启动logo信息：

```

 \ | /
- RT -     Thread Operating System
 / | \     3.0.4 build May  2 2018
 2006 - 2018 Copyright by rt-thread team
lwIP-2.0.2 initialized!
using armcc, version: 5060750
build time: May  2 2018 21:52:40
msh />[PHY] wait autonegotiation complete...
SD card capacity 123904 KB
probe mmcsd block device!
found part[0], begin: 32256, size: 120.992MB
File System initialized!
[PHY] wait autonegotiation complete...
```

## 4. 驱动支持情况及计划

| 驱动 | 支持情况  | 备注 |
| ------ | ----  | ------ |
| UART | 支持 | UART 1~8 |
| GPIO | 支持 |  |
| IIC | 支持 | IIC 1~4 |
| SPI | 支持 | SPI 1~4 |
| ETH | 支持 | 暂时仅支持官方的ETH |
| LCD | 支持 |  |
| RTC | 支持 |  |
| SDIO | 支持 | 暂时仅仅支持一个SDIO，还不支持中断方式 |
| SDRAM | 支持 | 32M SDRAM，后面2M作为Non Cache区域 |

## 5. 联系人信息

维护人：


## 6. 参考

- [MIMXRT1020-EVK: i.MX RT1020评估套件概述](https://www.nxp.com/support/developer-resources/software-development-tools/i.mx-developer-resources/i.mx-rt1020-evaluation-kit:MIMXRT1020-EVK)
- [MIMXRT1020芯片主页](https://www.nxp.com/products/processors-and-microcontrollers/arm-based-processors-and-mcus/i.mx-applications-processors/i.mx-rt-series/i.mx-rt1020-crossover-processor-with-arm-cortex-m7-core:i.MX-RT1020?)
