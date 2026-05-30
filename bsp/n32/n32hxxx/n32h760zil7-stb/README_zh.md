# N32H760ZIL7-STB 开发板 BSP 说明

## 简介

本文档为 [OnlyoutzZ](https://github.com/OnlyoutzZ) 为 N32H760ZIL7-STB 开发板提供的 BSP (板级支持包) 说明。

主要内容如下：

- 开发板资源介绍
- BSP 快速上手
- 进阶使用方法

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。在进阶使用指南章节，将会介绍更多高级功能，帮助开发者利用 RT-Thread 驱动更多板载资源。

## 开发板介绍

N32H760ZIL7-STB 是 NSING 推出的一款基于 ARM Cortex-M7 内核的开发板，最高主频为 600Mhz，该开发板具有丰富的板载资源，可以充分发挥 N32H760 的芯片性能。

开发板外观如下图所示：

![board](figures/board.png)

该开发板常用 **板载资源** 如下：

- MCU：N32H760，主频 600MHz，1920KB FLASH ，128KB AXI-SRAM
- 常用接口：USB 转串口(J1)、USB 接口(J2/J3)等
- 调试接口：板载的 CMSIS-DAP SWD 下载(J1)

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **板载外设** | **支持情况** | **备注**          |
| :----------- | :----------: | :---------------- |
| **片上外设** | **支持情况** | **备注**          |
| GPIO         |     支持     |                   |
| UART         |     支持     | UART1/2/3         |
| IIC          |     支持     | 硬件I2C1, 软件IIC |
| SPI          |     支持     | SPI1              |
| RTC          |     支持     | RTC               |
| ADC          |     支持     | ADC1/2/3          |

## 使用说明

使用说明分为如下两个章节：

- 快速上手

  本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

- 进阶使用

  本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。

### 快速上手

本 BSP 为开发者提供 MDK5 工程。下面介绍如何在 MDK5 环境下将系统运行起来。

#### 硬件连接

使用 USB 数据线插入开发板 J1 接口并连接到 PC。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 CMSIS-DAP SWD 下载程序，点击下载按钮即可下载程序到开发板

#### 运行结果

下载程序成功之后，系统会自动运行，LED 闪烁。

连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     5.3.0 build Jan 27 2026 16:53:58
 2006 - 2024 Copyright by RT-Thread team
msh >
```

### 进阶使用

此 BSP 默认只开启了 GPIO 和 串口 1 的功能，如果需使用更多高级功能，需要利用 ENV 工具对 BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=mdk5` 命令重新生成工程。

## 注意事项

- 调试串口为串口 1 映射说明

  PA9 ------> USART1_TX

  PA10 ------> USART1_RX

## 联系人信息

维护人:

- [OnlyoutzZ](https://github.com/OnlyoutzZ)
