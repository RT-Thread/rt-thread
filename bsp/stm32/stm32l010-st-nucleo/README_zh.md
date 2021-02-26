
# NUCLEO-L010RB 开发板 BSP 说明

## 简介

本文档为ST官方 NUCLEO-L010RB 开发板的 BSP (板级支持包) 说明。

主要内容如下：

- 开发板资源介绍
- BSP 快速上手
- 进阶使用方法

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。在进阶使用指南章节，将会介绍更多高级功能，帮助开发者利用 RT-Thread 驱动更多板载资源。

## 开发板介绍

NUCLEO-L010RB 开发板是 ST 官方推出的一款基于 ARM Cortex-M0+ 内核的开发板，绿色的 Nucleo 标志显示了这款芯片是低功耗系列，板载 ST-LINK/V2-1 调试器/编程器，该开发板具有丰富的扩展接口，且与Arduino™ nano 接口兼容，可以方便验证 STM32L010RB 芯片的性能。

开发板外观如下图所示：

![board](figures/board.jpg)

该开发板常用 **板载资源** 如下：

- MCU：STM32L010RB
	- 主频 32MHz
	- 128KB FLASH
	- 20KB RAM
	- 512 byte EEPROM
- 常用外设
  - LED：3个，USB communication(LD1 双色)，power LED(LD3 红色)，user LED(LD2 黄色)
  - 按键：1个，B1（兼具唤醒功能，PC13），B2（RESET）
- 常用接口：USB 支持 3 种不同接口：虚拟 COM 端口、大容量存储和调试端口；arduino 接口等
- 调试接口：标准 SWD

开发板更多详细信息请参考[STMicroelectronics NUCLEO-L010RB](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-mpu-eval-tools/stm32-mcu-mpu-eval-tools/stm32-nucleo-boards/nucleo-l010rb.html#overview)。

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **板载外设**      | **支持情况** | **备注**                              |
| :----------------- | :----------: | :------------------------------------- |
| 板载 ST-LINK 转串口        |     支持     |                             |
| **片上外设**      | **支持情况** | **备注**                              |
| GPIO              |     支持     | PA0, PA1... PC15 ---> PIN: 0, 1...47 |
| UART              |     支持     | UART2                             |
| SPI               |   暂不支持   |                            |
| I2C               |   暂不支持   |                     |
| RTC               |   暂不支持   |                        |
| PWM               |   暂不支持   |                       |
| USB Device        |   暂不支持   |                      |
| IWG               |   暂不支持   |                         |
| **扩展模块**      | **支持情况** | **备注**                                                                  |

## 使用说明

使用说明分为如下两个章节：

- 快速上手

    本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

- 进阶使用

    本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。


### 快速上手

本 BSP 为开发者提供 MDK5 和 IAR 工程，并且支持 GCC 开发环境。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用数据线连接开发板到 PC，打开电源开关。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 ST-LINK 仿真器下载程序，在通过 microUSB 连接开发板的基础上，点击下载按钮即可下载程序到开发板

#### 运行结果

下载程序成功之后，系统会自动运行，观察开发板上 LED 的运行效果，红色 LED1 和 LED3 常亮、黄色 LED2 会周期性闪烁。

USB 虚拟 COM 端口默认连接串口 2，在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     4.0.3 build Apr  9 2020
 2006 - 2020 Copyright by rt-thread team
msh >

```
### 进阶使用

此 BSP 默认只开启了 GPIO 和 串口 2 的功能，如果需使用更多高级功能，需要利用 ENV 工具对BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=mdk5/iar` 命令重新生成工程。

本章节更多详细的介绍请参考 [STM32 系列 BSP 外设驱动使用教程](../docs/STM32系列BSP外设驱动使用教程.md)。

## 注意事项

- 开机时如果不能打印 RT-Thread 版本信息，请将BSP中串口 GPIO 速率调低
- 开机时如果不能打印 RT-Thread 版本信息，请重新选择 PC 端串口调试软件的串口号

## 联系人信息

- 维护人: [xph](https://github.com/xupenghu)
- 邮箱：<xupenghu@outlook.com>
