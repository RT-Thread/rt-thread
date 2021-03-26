# GD32103C-EVAL

## 简介

GD32103C-EVAL是-兆易创新推出的一款GD32F103VCT6系列的评估板，板载资源主要如下：

| 硬件      | 描述          |
| --------- | ------------- |
| 芯片型号  | GD32F103VCT6  |
| CPU       | ARM Cortex M3 |
| 主频      | 108M          |
| 片内SRAM  | 48K           |
| 片内FLASH | 256K          |
| 片外FLASH | 1Gb           |

## 编译说明

GD32103C-EVAL板级包支持MDK4﹑MDK5﹑IAR开发环境和GCC编译器，以下是具体版本信息：

| IDE/编译器 | 已测试版本                   |
| ---------- | ---------------------------- |
| GCC        |gcc version 6.2.1 20161205 (release) |

## 烧写及执行

供电方式：开发板使用 Mini USB 接口或者 DC-005 连接器提供 5V 电源。

下载程序：下载程序到开发板需要一套 JLink 或者使用 GD-Link 工具。

串口连接：使用串口线连接到COM1(UART0)，或者使用USB转TTL模块连接PA9(MCU TX)和PA10(MCU RX)。

### 运行结果

如果编译 & 烧写无误，当复位设备后，会在串口上看到RT-Thread的启动logo信息：

```bash
 \ | /
- RT -     Thread Operating System
 / | \     4.0.3 build Jan  4 2021
 2006 - 2021 Copyright by rt-thread team
msh />
```
## 驱动支持情况及计划

| 驱动      | 支持情况 |            备注            |
| --------- | -------- | :------------------------: |
| UART      | 支持     |          UART0~4           |
| GPIO      | 支持     |          GPIOA~G           |
| ADC       | 支持     |          ADC0~1            |
| HWTIMER   | 支持     |          TIMER0~7          |
| RTC       | 支持     |          RTC               |
| WDT       | 支持     |    Free watchdog timer     |
| IIC       | 未支持   |          I2C0~1            |
| SPI       | 未支持   |          SPI0~2            |
| ETH       | 未支持   |                            |
| LCD       | 未支持   |                            |
| SDRAM     | 未支持   |                            |
| SPI FLASH | 未支持   |                            |

### IO在板级支持包中的映射情况

| IO号 | 板级包中的定义 |
| ---- | -------------- |
| PC0  | LED1           |
| PC2  | LED2           |
| PE0  | LED3           |
| PE1  | LED4           |
| PA0  | KEY1           |
| PC13 | KEY2           |
| PB14 | KEY3           |

## 联系人信息

维护人：[iysheng](https://github.com/iysheng)
