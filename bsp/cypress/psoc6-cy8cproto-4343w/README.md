# Cypress Psoc6-CY8CKIT-062S2-43012 说明

## 简介

本文档为 `RT-Thread` 为 `PSoC6 CY8CKIT-062S2-43012`开发板提供的 BSP (板级支持包) 说明。

主要内容如下：

- 开发板资源介绍
- BSP 快速上手
- 进阶使用方法

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。在进阶使用指南章节，将会介绍更多高级功能，帮助开发者利用 `RT-Thread` 驱动更多板载资源。

## 开发板介绍

`PSoC6 CY8CKIT-062S2-43012` 是赛普拉斯推出的一款32位双核CPU子系统（ ARM Cortex-M4 和 ARM Cortex-M0）的开发板，具有单周期乘法的150-MHz Arm Cortex-M4F CPU (浮点和存储器保护单元)，100-MHz Cortex M0+ CPU，带单周期乘法和MPU，可以充分发挥 PSoC6 双核芯片性能。

开发板外观详细信息：[CY8CPROTO-062-4343W - Infineon Technologies](https://www.infineon.com/cms/en/product/evaluation-boards/cy8cproto-062-4343w/)

该开发板核心 **板载资源** 如下：

- MCU：CY8C624ABZI-S2D44，Cortex-M4主频 150MHz，Cortex-M0主频 100MHz，2MB Flash 和 1MB SRAM
	    MCU手册更多详细信息请参考文档 [PSoC 6 MCU: CY8C62x8, CY8C62xA Datasheet (infineon.com)](https://www.infineon.com/dgdl/Infineon-PSOC_6_MCU_CY8C62X8_CY8C62XA-DataSheet-v17_00-EN.pdf?fileId=8ac78c8c7d0d8da4017d0ee7d03a70b1)
- 板载资源：microSD card , 64-Mb Quad-SPI NOR flash， CYW43012 Wi-Fi + Bluetooth Combo Chip
- 开发环境：ModusToolbox 2.0/MDK V5
		PSoC® Creator™ 下载链接 [ModusToolbox™ Software - Infineon Technologies](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software/)
- 开发板：CY8CKIT-062-BLE PSoC 6 BLE Pioneer Kit
		开发板更多详细信息请参考文档 https://www.cypress.com/file/390496/download

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设** | **支持情况** |   **备注**    |
| :----------: | :----------: | :-----------: |
|  USB 转串口  |     支持     |       —       |
|     GPIO     |     支持     |       —       |
|     UART     |     支持     |    UART0-5    |
|     I2C      |     支持     | 软件+硬件 I2C |
|     RTC      |     支持     |       —       |
|     WDT      |     支持     |       —       |
|     PWM      |     支持     |       —       |
|     SPI      |     支持     |       —       |
|  HardTimer   |   暂不支持   |       —       |
|     DAC      |   暂不支持   |       —       |
|    Flash     |   暂不支持   |       —       |
|     SDIO     |   暂不支持   |       —       |
|  USB Device  |   暂不支持   |       —       |
|   USB Host   |   暂不支持   |       —       |

## 使用说明

- 快速上手

    本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。


### 快速上手

本 BSP 是以 MDK V5 开发环境（编译器：ARMClang ），接下来介绍如何将系统运行起来。

#### 硬件连接

使用数据线连接开发板到 PC。

#### 编译下载
1、配置工程：

首先打开 MDK ，若没有安装 `Cypress-PSoC6` 的芯片支持包会提示在线安装，根据提示安装即可。若受网络问题，可以进入 [keil](https://www.keil.com/dd2/pack) 官网下载安装包，离线安装。

![mdk_package](./figures/mdk_package.png)

2、 编译此工程：在安装好芯片支持包后，在 `MDK`工程中进行编译。

3、下载此工程：


工程默认配置使用板载 `DAP-LINK` 使用 `SWD` 方式下载程序，使用数据线连接开发板，编译之后直接点击下载按钮即可。

#### 运行结果

下载程序成功之后，系统会自动运行。打开终端工具串口助手，选择波特率为 115200。复位设备后，LED 将会以 500HZ 的频率闪烁，而且在终端上可以看到 `RT-Thread` 的输出信息：

注：推荐使用串口调试助手如：`MobaXterm`

```

 \ | /
- RT -     Thread Operating System
 / | \     4.1.1 build Jul 25 2022 18:03:35
 2006 - 2022 Copyright by RT-Thread team
msh >
```

## 联系人信息

维护人:

- [Rbb666](https://github.com/Rbb666)