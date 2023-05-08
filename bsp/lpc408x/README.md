# LPC408x BSP 使用说明

## 简介

LPC408x 是 RT-Thread 推出的一款基于 LPC408x 系列的评估板，板载资源主要如下：

| 硬件      | 描述          |
| --------- | ------------- |
| 芯片型号  | LPC4088FET208 |
| CPU       | ARM Cortex M4 |
| 主频      | 120M          |
| 片内 SRAM  | 64K           |
| 片外 SDRAM | 32M          |
| 片内 FLASH | 512K         |

## 编译说明

LPC408x 板级包支持 MDK4﹑MDK5 开发环境和 GCC 编译器，以下是具体版本信息：

| IDE / 编译器 | 已测试版本                   |
| ---------- | ---------------------------- |
| MDK4       | MDK4.74                      |
| MDK5       | MDK524a                      |
| GCC        | GCC 5.4.1 20160919 (release) |

## 烧写及执行

供电方式：使用方口 USB 连接电脑和开发板。

下载程序：使用 JLink/ULink 等等仿真器连接到板子上的 20Pin 仿真口。

串口连接：板载 CP2102，连接了 USB 后打开相应的串口即可。

### 运行结果

如果编译 & 烧写无误，当复位设备后，会在串口上看到 RT-Thread 的启动 logo 信息：

```bash
 \ | /
- RT -     Thread Operating System
 / | \     3.0.4 build May 22 2018
 2006 - 2018 Copyright by rt-thread team
finsh />

```
## 驱动支持情况及计划

| 驱动  | 支持情况 |      备注      |
| ----- | -------- | :------------: |
| UART  | 支持     |     UART0/2    |
| ETH   | 支持     |                |
| LCD   | 支持     |                |
| SDRAM | 支持     |                |
| ADC   | 支持     |                |

### IO 在板级支持包中的映射情况

| IO 号  | 板级包中的定义 |
| ----- | -------------- |
| P3_14 | LED1           |
| P3_3  | LED2           |
| P2_2  | LED3           |
| P0_6  | SW2            |
| P0_5  | SW3            |
| P1_1  | SW4            |

## 联系人信息

维护人：[tanek](https://github.com/liangyongxiang)
