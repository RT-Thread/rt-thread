# GD32F205RKT6

## 简介

GD32F205RKT6 是-兆易创新推出的一颗 Cortex-M3 的处理器，芯片资源主要如下：

| 硬件      | 描述          |
| --------- | ------------- |
| 芯片型号  | GD32F205RKT6  |
| CPU       | ARM Cortex M3 |
| 主频      | 120M          |
| 片内SRAM  | 256K           |
| 片内FLASH | 3072K           |

## 编译说明

GD32450Z-EVAL板级包支持MDK5开发环境以下是具体版本信息：

| IDE/编译器 | 已测试版本 |
| ---------- | ---------- |
| GCC        | gcc version 6.2.1 20161205 |

## 烧写及执行

下载程序：下载程序到开发板需要一套 JLink 或者使用 GD-Link 工具。

串口连接：使用串口线连接到COM1(UART0)，或者使用USB转TTL模块连接PA9(MCU TX)和PA10(MCU RX)。

### 运行结果

如果编译 & 烧写无误，当复位设备后，会在串口上看到RT-Thread的启动logo信息：

```bash
 \ | /
- RT -     Thread Operating System
 / | \     4.0.4 build Sep 20 2021
 2006 - 2021 Copyright by rt-thread team
msh >
```
## 驱动支持情况及计划

| 驱动      | 支持情况 |            备注            |
| --------- | -------- | :------------------------: |
| UART      | 支持     |          UART0~1           |
| GPIO      | 支持     |           ALL              |

## 联系人信息

维护人：[iysheng](https://gitee.com/iysheng)
邮箱：iysheng@163.com
