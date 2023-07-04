# 第一部分：NUCLEO-U575ZI-Q 开发板 BSP 说明

[English](README.md) | **中文**

## 简介

本文档为 Zheng-Bicheng 为 STM32 B-U585I-IOT02A 开发板提供的 BSP (板级支持包) 说明。

主要内容如下：

- 开发板资源介绍
- BSP 快速上手
- 进阶使用方法

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。在进阶使用指南章节，将会介绍更多高级功能，帮助开发者利用 RT-Thread 驱动更多板载资源。

## 开发板介绍

STM32 B-U585I-IOT02A 是 ST 推出的一款基于 ARM Cortex-M33 内核的开发板，最高主频为 160 Mhz，该开发板具有丰富的板载资源，可以充分发挥 STM32U575 的芯片性能。

开发板外观如下图所示：

![board](https://www.st.com/bin/ecommerce/api/image.PF271412.en.feature-description-include-personalized-no-cpn-large.jpg)

该开发板常用 **板载资源** 如下：

- MCU：STM32U585AIIxQ，主频 160 MHz，2048KB FLASH ，786KB RAM
- 常用接口：USB 转串口、USB 接口、arduino 接口等
- 调试接口，标准 ST-Link

开发板更多详细信息请参考 [STM32 B-U585I-IOT02A](https://www.st.com/zh/evaluation-tools/b-u585i-iot02a.html)。

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **板载外设** | **支持情况** | **备注** |
|:---------|:--------:|:-------|
| USB虚拟串口  |    支持    |        |
| **片上外设** | **支持情况** | **备注** |
| GPIO     |    支持    |        |
| UART     |    支持    | UART1  |


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

> 工程默认配置使用 ST_LINK 仿真器下载程序，在通过 ST_LINK 连接开发板的基础上，点击下载按钮即可下载程序到开发板

#### 运行结果

下载程序成功之后，系统会自动运行，LED闪烁。

连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     4.0.4 build Nov 14 2021 21:15:06
 2006 - 2021 Copyright by rt-thread team
msh >
```
### 进阶使用

此 BSP 暂时只支持了 GPIO 和 UART1 的功能，后续会添加新的功能。

## 注意事项

- 调试串口为 UART1 1 映射说明

  ```c
  PA9     ------> USART1_TX
  PA10     ------> USART1_RX
  ```

- MDK版本最好使用比较新的版本的，本次实验是在MDK5.36版本下进行的。
