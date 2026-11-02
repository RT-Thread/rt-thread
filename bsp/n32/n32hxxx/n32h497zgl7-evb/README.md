# N32H497ZGL7 开发板 BSP 说明

## 简介

本文档为 RT-Thread 开发团队为 N32H497ZGL7 开发板提供的 BSP (板级支持包) 说明。

主要内容如下：

- 开发板资源介绍
- BSP 快速上手
- 进阶使用方法

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。在进阶使用指南章节，将会介绍更多高级功能，帮助开发者利用 RT-Thread 驱动更多板载资源。

## 开发板介绍

N32H497ZGL7_EVB V1.0 是 Nsing 推出的一款基于 ARM Cortex-M4 内核的开发板，最高主频为 240Mhz，该开发板具有丰富的板载资源，可以充分发挥 N32H497 的芯片性能。

开发板外观如下图所示：

![board](figures/board.jpg)

该开发板常用 **板载资源** 如下：

- MCU：N32H497ZGL7，主频 240MHz，1024KB FLASH ，448KB RAM
- 外部 PSRAM：APS1604M-3SQR-SN（XSPI-PSRAM）
- 外部 SDRAM：M12L64164A-5TG2C
- 外部 EEROM：AT24C02
- 外部 FLASH：W25Q128JVSIQTR（SPI）、P25Q40HA-SSH-IT（XSPI）
- 常用外设
  - LED：3个，LED1（PA3），LED2（PB3），LED3（PA8）
  - 按键：4个，WKUP（兼具唤醒功能，PA0），KEY1（PC13），KEY2（PA15），KEY3
- 常用接口：USB 转串口、CAN 接口、RS485 接口、LIN 接口、以太网接口
- 调试接口，标准 JTAG/SWD

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设**      | **支持情况** | **备注**                                                               |
| GPIO              |     支持     | PA0, PA1... PH5 ---> PIN: 0, 1...117                                   |
| UART              |     支持     | UART1/2/3, 如需使用该外设，请使用 Cube 重新配                             |


## 使用说明

使用说明分为如下两个章节：

- 快速上手

    本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

- 进阶使用

    本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。


### 快速上手

本 BSP 为开发者提供 MDK5 和 IAR 工程，并且支持 GCC 开发环境。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

**请注意！！！**

在执行编译工作前请先打开ENV执行以下指令（该指令用于拉取必要的 STD 库及 CMSIS 库，否则无法通过编译）：

```bash
pkgs --update
```

#### 硬件连接

使用数据线连接开发板到 PC，打开电源开关。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 CMSIS-DAP 下载程序，在通过 USB 线连接开发板的基础上，点击下载按钮即可下载程序到开发板

#### 运行结果

下载程序成功之后，系统会自动运行，观察开发板上 LED1 的运行效果，LED1 会周期性闪烁。

连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     5.3.0 build Jul 16 2026 11:18:41
 2006 - 2024 Copyright by RT-Thread team
msh >
```
### 进阶使用

此 BSP 默认只开启了 GPIO 和 串口1 的功能，如果需使用更多高级功能，需要利用 ENV 工具对BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=mdk5/iar` 命令重新生成工程。

## 注意事项

- 调试串口为串口 1 映射说明

  PA9 ------> USART1_TX

  PA10 ------> USART1_RX

- 按键 KEY3 说明

  若需要使用按键 KEY3，需要拔了 J43 跳线帽，使用杜邦线连接到 PB4

## 联系人信息

维护人:

- [OnlyoutzZ](https://github.com/OnlyoutzZ)