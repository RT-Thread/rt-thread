# STM32F334-Nucleo-64 开发板 BSP 说明

## 简介

本文档为 RT-Thread 开发团队为 STM32F334-Nucleo-64 开发板的 BSP (板级支持包) 说明。

主要内容如下：

- 开发板资源介绍
- BSP 快速上手
- 进阶使用方法

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。在进阶使用指南章节，将会介绍更多高级功能，帮助开发者利用 RT-Thread 驱动更多板载资源。

## 开发板介绍

STM32F334-Nucleo-64 是意法半导体推出的一款基于 ARM Cortex-M4 内核的开发板，最高主频为 72 Mhz，该开发板具有丰富的板载资源，可以充分发挥 STM32F334R8 的芯片性能。

开发板外观如下图所示：

![board](figures/board.png)

该开发板常用 **板载资源** 如下：

- MCU：STM32F334R8T6，主频 72MHz，64KB FLASH ，12KB RAM
- 常用外设
  - LED：1个，LD2（绿色，PA5）
  - 按键：1个，B1
- 调试接口，板载 ST-LINK 调试器。

开发板更多详细信息请参考意法半导体 [STM32F334-Nucleo-64 开发板介绍](https://www.st.com/en/evaluation-tools/nucleo-f334r8.html)。

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设** | **支持情况** |               **备注**                |
| :------------ | :----------: | :-----------------------------------: |
| GPIO         |     支持     | PA0, PA1... ---> PIN: 0, 1...63 |
| UART         |     支持     |              UART2             |

## 使用说明

使用说明分为如下两个章节：

- 快速上手

    本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

- 进阶使用

    本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。


### 快速上手

本 BSP 为开发者提供 MDK4、MDK5 和 IAR 工程，并且支持 GCC 开发环境。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用 Type-A to Mini-B 线连接开发板和 PC 供电。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 ST-LINK 仿真器下载程序，点击下载按钮即可下载程序到开发板

#### 运行结果

下载程序成功之后，系统会自动运行，绿色 LED 会周期性闪烁。

连接开发板对应串口到 PC, 在终端工具里打开相应的串口，复位设备后，可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     5.0.1 build Jun  3 2023 01:29:39
 2006 - 2022 Copyright by RT-Thread team
msh >
```
### 进阶使用

此 BSP 默认只开启了 GPIO 和 串口2 的功能，若需要利用 ENV 工具对BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=mdk4/mdk5/iar` 命令重新生成工程。

本章节更多详细的介绍请参考 [STM32 系列 BSP 外设驱动使用教程](../docs/STM32系列BSP外设驱动使用教程.md)。

## 注意事项

- 暂无

## 联系人信息

维护人:

- [tangzz98](https://github.com/tangzz98), 邮箱：<tangz98@outlook.com>
