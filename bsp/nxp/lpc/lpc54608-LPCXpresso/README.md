# LPCXpresso54608

## 简介

LPCXpresso54608是NXP推出的一款基于LPC54608系列的评估板，板载资源主要如下：

| 硬件      | 描述          |
| --------- | ------------- |
| 芯片型号  | LPC54608J512  |
| CPU       | ARM Cortex M4 |
| 主频      | 180M          |
| 片内SRAM  | 200K(160KSRAM + 32K I-code/D-code SRAM + 8K USB SRM)          |
| 片外SDRAM | 8M           |
| 片内FLASH | 512K         |

## 编译说明

LPCXpresso54608板级包支持MDK4﹑MDK5﹑IAR开发环境和GCC编译器，以下是具体版本信息：

| IDE/编译器 | 已测试版本                   |
| ---------- | ---------------------------- |
| MDK4       | MDK4.74                      |
| MDK5       | MDK524a                      |
| IAR        | IAR 7.60~IAR8.20             |
| GCC        | GCC 5.4.1 20160919 (release) |

## 烧写及执行

供电方式：使用 Micro USB 连接电脑和板子上的J8(Debug Link)。

下载程序：开发板自带了板载CMSIS-DAP仿真器，在IDE里选择CMSIS-DAP即可。

串口连接：板载CMSIS-DAP仿真器连接到LPC54608J512的UART0，在PC上打开CMSIS-DAP对应的UART即可。

### 运行结果

如果编译 & 烧写无误，当复位设备后，会在串口上看到RT-Thread的启动logo信息：

```bash
 \ | /
- RT -     Thread Operating System
 / | \     3.0.4 build May 22 2018
 2006 - 2018 Copyright by rt-thread team
finsh />

```
## 驱动支持情况及计划

| 驱动  | 支持情况 |            备注            |
| ----- | -------- | :------------------------: |
| UART  | 支持     |        只支持UART0         |
| GPIO  | 未支持   |                            |
| IIC   | 支持     |         只支持IIC1         |
| SPI   | 未支持   |           SPI0~5           |
| ETH   | 支持     |                            |
| LCD   | 支持     | 支持FrameBuffer模式LCD显示 |
| TOUCH | 支持     |       ft5406触摸芯片       |
| SDRAM | 支持     |                            |

### IO在板级支持包中的映射情况

| IO号  | 板级包中的定义 |
| ----- | -------------- |
| P3_14 | LED1           |
| P3_3  | LED2           |
| P2_2  | LED3           |
| P0_6  | SW2            |
| P0_5  | SW3            |
| P1_1  | SW4            |

## 联系人信息

维护人：[tanek](https://github.com/liangyongxiang)
