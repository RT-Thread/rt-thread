# STM32F103C8T6最小系统板(BluePill) BSP 说明

[[English]](README.md)

## 简介

本文档为 STM32F103C8T6最小系统板(BluePill) 的 BSP (板级支持包) 说明。

主要内容如下：

- 开发板资源介绍
- BSP 快速上手
- 进阶使用方法

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。在进阶使用指南章节，将会介绍更多高级功能，帮助开发者利用 RT-Thread 驱动更多板载资源。



## 开发板介绍

STM32F103C8T6最小系统，采用SWD调试接口，可以用3个接口就能完成调试下载的任务，采用了官方建议的负载RTC晶振方案，小体积高频率的STM32实验板

开发板外观如下图所示：

![board](figures/Bluepill_pinout.png)

该开发板常用 **板载资源** 如下：

- MCU：STM32F103C8T6，主频 72MHz，64KB FLASH ，20KB RAM
- 外部 RAM：无
- 外部 FLASH：无
- 常用外设
  - LED：1个 PC13
- 常用接口：无
- 调试接口：SWD调试接口



## 外设支持

本 BSP 目前对外设的支持情况如下：

| **板载外设**      | **支持情况** | **备注**                              |
| :----------------- | :----------- | :------------------------------------- |
| 	黄色LED		    |     支持      |       PC13                          |
| **片上外设**      | **支持情况** | **备注**                              |
| GPIO              |              |          |
| UART              |     支持     | UART1                                |



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

> 工程默认配置使用 J-Link 仿真器下载程序，在通过 J-Link 连接开发板的基础上，点击下载按钮即可下载程序到开发板

#### 运行结果

下载程序成功之后，系统会自动运行，LED 闪烁

连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     4.0.1 build Mar 10 2019
 2006 - 2019 Copyright by rt-thread team
msh >
```
### 进阶使用

此 BSP 默认只开启了 GPIO 和 串口1 的功能，如果需使用 ADC、SPI等更多高级功能，再用 ENV 工具对BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=mdk4/mdk5/iar` 命令重新生成工程。

本章节更多详细的介绍请参考 [STM32 系列 BSP 外设驱动使用教程](../docs/STM32系列BSP外设驱动使用教程.md)。



## 注意事项

- 只能用USB转TTL连接PC机 ;



## 感谢 & 维护

- 感谢[obito0](https://github.com/obito0)提供的[原始工程](../stm32f103-mini-system)
- [Meco Man](https://github.com/mysterywolf): jiantingman@foxmail.com