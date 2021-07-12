# GD32350R-EVAL

## 简介

GD32350R-EVAL是-兆易创新推出的一款GD32F350系列的评估板，板载资源主要如下：

| 硬件      | 描述          |
| --------- | ------------- |
| 芯片型号  | GD32F350R8T6  |
| CPU       | ARM Cortex M4 |
| 主频      | 108M          |
| 片内SRAM  | 16K           |
| 片内FLASH | 64K           |

## 编译说明

GD32450Z-EVAL板级包支持MDK5开发环境以下是具体版本信息：

| IDE/编译器 | 已测试版本 |
| ---------- | ---------- |
| MDK5       | MDK524a    |

## 烧写及执行

供电方式：开发板使用 Mini USB 接口或者 DC-005 连接器提供 5V 电源。

下载程序：下载程序到开发板需要一套 JLink 或者使用 GD-Link 工具。

串口连接：使用串口线连接到COM1(UART0)，或者使用USB转TTL模块连接PA9(MCU TX)和PA10(MCU RX)。

### 运行结果

如果编译 & 烧写无误，当复位设备后，会在串口上看到RT-Thread的启动logo信息：

```bash
 \ | /
- RT -     Thread Operating System
 / | \     4.0.4 build Jun 21 2021
 2006 - 2021 Copyright by rt-thread team

<RT-Thread -- GD32F350R8T6>

msh >
```
## 驱动支持情况及计划

| 驱动      | 支持情况 |            备注            |
| --------- | -------- | :------------------------: |
| UART      | 支持     |          UART0~1           |
| GPIO      | 支持     |           ALL              |

## 联系人信息

维护人：[RiceChen](https://gitee.com/RiceChen0)
邮箱：980307037@qq.com
