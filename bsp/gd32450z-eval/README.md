# GD32450Z-EVAL

## 简介

GD32450Z-EVAL是-兆易创新推出的一款GD32F450系列的评估板，板载资源主要如下：

| 硬件      | 描述          |
| --------- | ------------- |
| 芯片型号  | GD32F450ZKT6  |
| CPU       | ARM Cortex M4 |
| 主频      | 200M          |
| 片内SRAM  | 256K          |
| 片外SDRAM | 32M           |
| 片内FLASH | 3072K         |

## 编译说明

GD32450Z-EVAL板级包支持MDK4﹑MDK5﹑IAR开发环境和GCC编译器，以下是具体版本信息：

| IDE/编译器 | 已测试版本                   |
| ---------- | ---------------------------- |
| MDK4       | MDK4.74                      |
| MDK5       | MDK524a                      |
| IAR        | IAR 7.60~IAR8.20             |
| GCC        | GCC 5.4.1 20160919 (release) |

## 烧写及执行

供电方式：开发板使用 Mini USB 接口或者 DC-005 连接器提供 5V 电源。

下载程序：下载程序到开发板需要一套 JLink 或者使用 GD-Link 工具。

串口连接：使用串口线连接到COM1(UART0)，或者使用USB转TTL模块连接PA9(MCU TX)和PA10(MCU RX)。

### 运行结果

如果编译 & 烧写无误，当复位设备后，会在串口上看到RT-Thread的启动logo信息：

```bash
 \ | /
- RT -     Thread Operating System
 / | \     3.0.4 build May 22 2018
 2006 - 2018 Copyright by rt-thread team
finsh />

```
## 驱动支持情况及计划

| 驱动      | 支持情况 |            备注            |
| --------- | -------- | :------------------------: |
| UART      | 支持     |          UART0~7           |
| GPIO      | 未支持   |                            |
| IIC       | 未支持   |                            |
| SPI       | 支持     |           SPI0~5           |
| ETH       | 支持     |                            |
| LCD       | 支持     | 支持FrameBuffer模式LCD显示 |
| SDRAM     | 支持     |                            |
| SPI FLASH | 支持     |                            |

### IO在板级支持包中的映射情况

| IO号 | 板级包中的定义 |
| ---- | -------------- |
| PD4  | LED1           |
| PD5  | LED2           |
| PG3  | LED3           |
| PA9  | KEY1           |
| PC13 | KEY2           |
| PB14 | KEY3           |

## 联系人信息

维护人：[tanek](https://github.com/liangyongxiang)
