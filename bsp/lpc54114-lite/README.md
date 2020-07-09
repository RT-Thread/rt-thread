# LPC54114-Lite 开发板 BSP 说明

## 简介

本文档为 LPC54114-Lite 开发板的 BSP (板级支持包) 说明，LPC54114-Lite 开发板即 NXP LPC54110 Board 开发板。

主要内容如下：

- 开发板资源介绍
- BSP 快速上手
- 进阶使用方法

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。在进阶使用指南章节，将会介绍更多高级功能，帮助开发者利用 RT-Thread 驱动更多板载资源。

## 开发板介绍

LPC54114-Lite 开发板由万利电子提供，双核高性能，专注语音应用的测试开发板卡。

开发板外观如下图所示：

![LPC54114-Lite](figures/LPC54114-Lite(LPC54110).jpg)

该开发板常用**板载资源**如下：

- MCU：LPC54114J256BD64 Cortex-M4/M0+ 双核 MCU ，主频 100MHz，256KB FLASH ，192KB RAM
- 外部 FLASH：型号 MD25D16SIG，16MBIT
- 常用外设
  - LED：8 个，LD4-LD7（绿色，PIO0_30、PIO0_29、PIO0_26、PIO0_25），LD8-LD11（红色，PIO0_22、PIO0_21、PIO0_19、PIO0_15）
  - 按键：4 个，PB2-PB5（PIO1_8、PIO1_9、PIO1_10、PIO1_11）
- 常用接口：USB、TF、音频接口
- 调试接口：SWD

LPC54114-Lite 开发板的更多详细信息请参考万利电子 [开发板用户手册](http://www.manley.com.cn/web/admin_ml32/pic/down/LPC54110%BF%AA%B7%A2%B0%E5%D3%C3%BB%A7%CA%D6%B2%E1.pdf)，[点击此处详见更多资料](http://www.manley.com.cn/web/product_detail.asp?pro=326)。

## 外设支持

本 BSP 目前对外设的支持情况如下：

|**板载外设**     |**支持情况**|**备注**                             |
| ----------------- | :----------: | ------------------------------------- |
| SPI Flash | 支持 |-                                       |
| SPI TF 卡 | 支持 |-                                       |
| I2C 温度传感器 <BR>(PCT2075DP) | 支持 |-      |
| I2S 音频输入 / 输出接口 <BR>(WM8904) | 支持 |仅支持解码      |
| PDM 数字麦克风 <BR>(SPH0641LM4H) | 支持 |-      |
|**片上外设**     |**支持情况**|**备注**                             |
| GPIO              |     支持     | PIO0_0 ... PIO1_31 ---> PIN: 0, 1...63 |
| UART              |     支持     | UART0                            |
| SPI               |   支持   | 暂时只支持SPI2         |
| I2C               |   支持   | 暂时只支持I2C4          |
| ADC          | 暂不支持 | 即将支持 |
| PWM               |   暂不支持   | 即将支持                              |
| USB Device        |   暂不支持   | 即将支持                              |
| IWG               |   暂不支持   | 即将支持                              |
|**板外外设**     |**支持情况**|**备注**                             |
| Arduino 扩展接口 |   暂不支持   |-                                      |

## 使用说明

使用说明分为如下两个章节：

- 快速上手

    本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

- 进阶使用

    本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。


### 快速上手

本 BSP 为开发者提供 MDK5 和 IAR 工程，并且支持 GCC 开发环境。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用 Micro USB 数据线连接开发板 CN1 到 PC（注意：需要下载安装 mbedSerial 驱动，使用 MDK5 需要安装 LPC54114 相关的 pack）。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 CMSIS-DAP 仿真器下载程序，在通过 Micro USB 连接开发板的基础上，点击下载按钮即可下载程序到开发板

#### 运行结果

下载程序成功之后，系统会自动运行，看到编号为 LD4 的这颗绿色 LED 在闪烁。

连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     3.1.1 build Nov 19 2018
 2006 - 2018 Copyright by rt-thread team
msh >
```
## 注意事项

- 需要下载并安装 mbedSerial 驱动
- 若使用 MDK5，则需要下载所使用的 pack
- BSP 仅支持 M4 内核

## 联系人信息

维护人:

- [yangjie](https://github.com/yangjie11)