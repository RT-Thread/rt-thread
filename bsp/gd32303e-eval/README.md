# GD32303E-EVAL #

## 1. 简介

[GD32303E-EVAL](http://gd32mcu.21ic.com/site)是兆易科技提供的开发板，使用 GD32F303ZET6 作为主控制器。提供包括扩展引脚在内的及 SWD, Reset, Boot, User button key, LED, CAN, I2C, I2S, USART, RTC, LCD, SPI, ADC, DAC, EXMC, CTC, SDIO,USBD, GD-Link 等外设资源。

板载主要资源如下：

| 硬件 | 描述 |
| -- | -- |
|CPU| Cortex-M4|
|主频| 120MHz |
|SRAM| 64KB |
|Flash| 512KB |

## 2. 编译说明

GD32303E-EVAL板级包支持MDK5、IAR开发环境和GCC编译器，以下是具体版本信息： 

| IDE/编译器 | 已测试版本 |
| -- | -- |
| MDK5 | MDK5.25 |
| IAR | IAR8.20 |
| GCC | GCC 5.4.1 20160919 (release) | 

## 3. 烧写及执行

供电方式：开发板使用 Mini USB 接口或者 DC-005 连接器提供 5V 电源。

下载程序：下载程序到开发板需要一套 JLink 或者使用 GD-Link 工具。

解决IDE "Missing Device(s)"问题"
* MDK5: 安装GigaDevice.GD32F30x_AddOn.1.0.1.exe，在 Folder Selection 中的 Destination Folder 那一栏选择 Keil uVision5 软件的安装目录，如 C:\Keil_v5，然后在 Option for Target 的 Device 选择对应的器件，同时在 Option forTarget 的 C/C++中添加路径 C:\Keil_v5\ARM\Pack\ARM\CMSIS\4.2.0\CMSIS\Include。

* IAR：安装 IAR_GD32F30x_ADDON.1.0.0.exe

### 3.1 配置和仿真

工程已经默认使能了RT-Thread UART驱动、GPIO驱动、SPI驱动、I2C驱动。若想进一步配置工程请
使用ENV工具。

### 3.2 运行结果

打开MDK或者IAR工程，进入仿真后全速运行，将会在串口0上看到RT-Thread的启动logo信息：

```
 \ | /
- RT -     Thread Operating System
 / | \     3.0.3 build Apr 26 2018
 2006 - 2018 Copyright by rt-thread team
msh />

```

## 4. 驱动支持情况及计划

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | UART0/1/2/3/4 |
| GPIO | 支持 |  |
| SPI | 支持 | SPI0/1/2 |
| I2C | 支持 | I2C0/1|

### 4.1 IO在板级支持包中的映射情况

| IO号 | 板级包中的定义 |
| -- | -- |
| PA9 | USART0 TX |
| PA10 | USART0 RX |
| PA2 | USART1 TX |
| PA3 | USART1 RX |
| PA5| SPI0 SCK |
| PA6 | SPI0 MISO |
| PA6 | SPI0 MOSI |
| PB13| SPI1 SCK |
| PB14 | SPI1 MISO |
| PB15 | SPI1 MOSI |
| PB6| I2C0 SCL |
| PB7 | I2C0 SDA |
| PB10| I2C1 SCL |
| PB11 | I2C1 SDA |

## 5. 联系人信息

维护人：

- [misonyo](https://github.com/misonyo)

## 6. 参考

* [GD32303E-EVAL](http://gd32mcu.21ic.com/site)


