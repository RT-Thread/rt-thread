# STM32F429 armfly-v6 开发板 BSP 说明

## 简介

本文档为 RT-Thread 开发团队为 STM32F429 armfly-v6 开发板提供的 BSP (板级支持包) 说明。

主要内容如下：

- 开发板资源介绍
- BSP 快速上手
- 进阶使用方法

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。在进阶使用指南章节，将会介绍更多高级功能，帮助开发者利用 RT-Thread 驱动更多板载资源。

## 开发板介绍

armfly-v6 STM32F429 是安富莱推出的一款基于 ARM Cortex-M4 内核的开发板，最高主频为 180Mhz，该开发板具有丰富的板载资源，可以充分发挥 STM32F429 的芯片性能。

开发板外观如下图所示：

![board](figures/board.png)

该开发板常用 **板载资源** 如下：

- MCU：STM32F429IGT6，主频 180MHz，2048KB FLASH ，256KB RAM
- 外部 RAM：MT48LC4M32B2（SDRAM，16MB，32bit）
- 外部 FLASH：W25Q64BVSSIG（SPI，8MB）、HY27UF081G2A（NAND，128MB）
- 常用外设
  - LED：4个，扩展IO LED1 - LED4
  - 按键：4个，k1（PI8），K2（PC13），k3（PH4），五向摇杆
- 常用接口：USB 转串口、SD 卡接口、以太网接口、LCD 接口
- 调试接口：SWD

开发板更多详细信息请参考安富莱 [STM32 v6 开发板介绍](https://armfly.taobao.com/)。

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **板载外设**      | **支持情况** | **备注**                              |
| :----------------- | :----------: | :------------------------------------- |
| USB 转串口        |     支持     |                                       |
| 扩展IO            |     支持     |                     |
| SPI Flash         |     支持     |                                       |
| 以太网            |     支持     |                                       |
| MPU6050 |     支持     |                                       |
| SDRAM             |     支持     |                                       |
| SD卡              |   支持   |                                       |
| LCD               |   支持   | 支持 RGB 屏                                |
| CAN               | 暂不支持 |                                            |
| **片上外设**      | **支持情况** | **备注**                              |
| GPIO              |     支持     | PA0, PA1... PK15 ---> PIN: 0, 1...176 |
| UART              |     支持     | UART1                             |
| SPI               |     支持     | SPI1/2/5                              |
| I2C               |     支持     | 软件 I2C                              |
| ADC               |     支持     |                                     |
| RTC               |     支持     | 支持外部晶振和内部低速时钟 |
| WDT               |     支持     |                                       |
| FLASH | 支持 | 已适配 [FAL](https://github.com/RT-Thread-packages/fal) |
| SDIO              |   支持   |                               |
| PWM               |   支持   |                               |
| USB Device        |   暂不支持   | 即将支持                              |
| USB Host          |   暂不支持   | 即将支持                              |
| **扩展模块**      | **支持情况** | **备注**                              |
| ad7606 |   暂不支持   |                               |

## 使用说明

使用说明分为如下两个章节：

- 快速上手

    本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

- 进阶使用

    本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。


### 快速上手

本 BSP 为开发者提供 MDK4、MDK5 和 IAR 工程，并且支持 GCC 开发环境。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用数据线连接开发板到 PC，打开电源开关。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 JLink 下载程序，在通过 JLink 连接开发板的基础上，点击下载按钮即可下载程序到开发板

#### 运行结果

下载程序成功之后，系统会自动运行，观察开发板上 LED 的运行效果，LED2 - 4 常亮、LED1 会周期性闪烁。

连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     3.1.1 build Nov 19 2018
 2006 - 2018 Copyright by rt-thread team
msh >
```
### 进阶使用

此 BSP 默认只开启了 GPIO 和 串口1 的功能，如果需使用 SD 卡、Flash 等更多高级功能，需要利用 ENV 工具对BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=mdk4/mdk5/iar` 命令重新生成工程。

本章节更多详细的介绍请参考 [STM32 系列 BSP 外设驱动使用教程](../docs/STM32系列BSP外设驱动使用教程.md)。

## 注意事项

暂无

## 联系人信息

维护人:

- [zylx](https://github.com/qgyhd1234)