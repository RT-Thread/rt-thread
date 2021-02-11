# Maxim-MAX32660- EVSYS说明

## 简介

该文件夹主要存放所有主芯片为MAX32660的板级支持包。开发板上面的主芯片是[MAX32660](https://www.maximintegrated.com/en/products/microcontrollers/MAX32660.html)

芯片Datasheet: [MAX32660_datasheet](https://datasheets.maximintegrated.com/en/ds/MAX32660.pdf)

芯片User Guide：[MAX32660_UserGuide](https://pdfserv.maximintegrated.com/en/an/AN6659.pdf)

开发板介绍页面:  [MAX32660-EVSYS](https://www.maximintegrated.com/en/products/microcontrollers/MAX32660-EVSYS.html)

开发板datasheet： [MAX32660-EVSYS.pdf)](https://datasheets.maximintegrated.com/en/ds/MAX32660-EVSYS.pdf)

支持IDE: keil， [eclipse](https://www.maximintegrated.com/en/design/software-description.html/swpart=SFW0001500A)

本文主要内容如下：

- 开发板资源介绍

## MAX32660芯片介绍

- RAM  96KB    0x20000000~0x20018000

- ROM  256KB   0x0 ~ 0x40000

- 16KB I-cache

- UART 2个  UART0  UART1

- GPIO  14个

- I2C  2个 Master/Slave 高速3.4Mbps

- ARM Cortex-M4F, 96MHz

- MPU

- SPI 2个  Master/Slave 

- I2S  Master/Slave

- 4 channel DMA

- 3个 32bit  Timer

- Watchdog 

- RTC

  

## 开发板介绍

MAX32660-EVSYS是美信官方的开发板，搭载MAX32660芯片，基于ARM Cortex-M4F内核，最高主频96MHz，具有丰富的外设资源，内核带有FPU。

开发板外观如下图所示

![](doc/images/board.jpg)

MAX32660-EVSYS开发板常用 **板载资源** 如下：

- MCU：MAX32660
- 板载设
  - LED：1个，GPIO P0_13 ，高电平点亮，低电平灭 。
  - 按键：1个，GPIO P0_12,   按下低电平，松开高电平。
- 调试接口：板载CMSIS-DAP调试器。

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设** | **支持情况** |   **备注**   |
| :----------- | :----------: | :----------: |
| GPIO         |              |              |
| UART         |     支持     | UART0, UART1 |
| PWM          |              |              |
| SPI          |              |              |
| RTC          |              |              |
| I2S          |              |              |
| I2C          |              |              |
| TIMER        |              |              |
| Watchdog     |              |              |



### 进阶使用

此 BSP 默认只开启了串口 的功能，更多高级功能需要利用 env 工具对 BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

4. 输入`scons --target=mdk4/mdk5/iar` 命令重新生成工程。

## 注意事项

目前仅支持keil5环境

## 联系人信息

维护人:

-  [supperthomas], 邮箱：<78900636@qq.com>