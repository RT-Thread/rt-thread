# VANGOV85XXP-EVAL

## 简介

VANGOV85XXP-EVAL是-杭州万高科技推出的一款基于V85XXP的评估板，板载资源主要如下：

| 硬件      | 描述          |
| --------- | ------------- |
| 芯片型号  | V8530P        |
| CPU       | ARM Cortex M0 |
| 主频      | 26M           |
| 片内SRAM  | 64K           |
| 片内FLASH | 512K          |

## 数据手册

[产品页面](http://www.vangotech.com/product.php?areas=0&bigs=1&smalls=4&id=65)
[datasheet](http://www.vangotech.com/uploadpic/162798394156.pdf)

## 编译说明

VANGOV85XXP-EVAL板级包支持MDK4﹑MDK5﹑IAR开发环境和GCC编译器，以下是具体版本信息：

| IDE/编译器 | 已测试版本                   |
| ---------- | ---------------------------- |
| GCC        |gcc version 6.2.1 20161205 (release) |

## 烧写及执行

供电方式：开发板使用 USB TypeA 接口或者 DC-005 连接器提供 5V 电源。

下载程序：下载程序到开发板需要一套 JLink 或者使用 SD612 工具。

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
| UART      | 支持     |          UART0~5           |
| GPIO      | 支持     |          GPIOA~F           |
| ADC       | 未支持   |          ADC0~7            |
| HWTIMER   | 未支持   |          TIMER0~3          |
| RTC       | 未支持   |          RTC               |
| WDT       | 未支持   |    Free watchdog timer     |
| IIC       | 未支持   |          I2C0              |
| SPI       | 未支持   |          SPI0~1            |
| LCD       | 未支持   |                            |
| SDRAM     | 未支持   |                            |
| SPI FLASH | 未支持   |                            |

### IO在板级支持包中的映射情况

| IO号 | 板级包中的定义  |
| ---- | -------------- |
| PC0  | LED1           |
| PC2  | LED2           |
| PE0  | LED3           |
| PE1  | LED4           |
| PA0  | KEY1           |
| PC13 | KEY2           |
| PB14 | KEY3           |

## 联系人信息

维护人：[zhuxw-z](https://github.com/zhuxw-z)
