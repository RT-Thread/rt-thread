# NUCLEO-WL55JC2 开发板的 BSP 说明

## 简介

本文档为 ST 官方 NUCLEO-WL55JC2 开发板的 BSP (板级支持包) 说明。

主要内容如下：

- 开发板资源介绍
- BSP 快速上手
- 进阶使用方法

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。在进阶使用指南章节，将会介绍更多高级功能，帮助开发者利用 RT-Thread 驱动更多板载资源。

## 开发板介绍

对于 NUCLEO-WL55JC2 Cortex-M4，绿色的 Nucleo 标志显示了这款芯片是低功耗系列，板载 ST-LINK/V3E 调试器/编程器，迷你尺寸，mirco USB 接口，可数的外设，Arduino™ nano 兼容的接口。

开发板外观如下图所示：

![board](figures/NUCLEO-WL55JC2.png)

该开发板常用 **板载资源** 如下：

- MCU：STM32WLJC2，主频 48MHz，256KB FLASH ，64KB RAM（32KB+32KB）。
- 常用外设:
  - LED：USB communication(LED6 双色),power LED(LED5 黄绿色),3个User LED(LED1 蓝色、LED2 黄绿色、LED3 红色)
  - 按键：复位按键(B4)，3个 User Button(B1、B2、B3)。
- 常用接口：USB 支持 3 种不同接口：虚拟 COM 端口、大容量存储和调试端口。
- 调试接口：板载 ST-LINK/V3E 调试器。

开发板更多详细信息请参考【STMicroelectronics】 [STM32WL-Serials](https://www.st.com/en/microcontrollers-microprocessors/stm32wl-series.html)。

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **板载外设**      | **支持情况** | **备注**                              |
| :----------------- | :----------: | :------------------------------------- |
| 板载 ST-LINK 转串口 |     支持     | LPUART1                              |
| **片上外设**      | **支持情况** | **备注**                              |
| GPIO              |     支持     | LED1(PB15)\LED2(PB9)\LED3(PB11) |
| UART              |     支持     | LPUART1    |
| **扩展模块**      | **支持情况** | **备注** |

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

下载程序成功之后，系统会自动运行，观察开发板上 LED 的运行效果，LED6 和 LED5 常亮、LED1\LED2\LED3 会周期性闪烁。

USB 虚拟 COM 端口默认连接LPUART1，在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     4.0.3 build Sep  9 2020
 2006 - 2020 Copyright by rt-thread team
msh >
```
### 进阶使用

此 BSP 默认只开启了 GPIO 和 LPUART1的功能，如果需使用更多高级功能，需要利用 ENV 工具对 BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=mdk4/mdk5/iar` 命令重新生成工程。

本章节更多详细的介绍请参考 [STM32 系列 BSP 外设驱动使用教程](../docs/STM32系列BSP外设驱动使用教程.md)。

## 注意事项

- 开机时如果不能打印 RT-Thread 版本信息，请重新选择 PC 端串口调试软件的串口号.

## 联系人信息

维护人:

-  [forest-rain] 邮箱：<693097971@qq.com>