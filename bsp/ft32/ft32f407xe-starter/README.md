# FT32F407xx-StarterKit-32 #

## 1. 简介

[StarterKit-32](https://www.fremontmicro.com/down/demoboard/index.aspx)是辉芒微提供的开发板，使用 Cortex-M4 内核的 FT32F407xE 作为主控制器。提供包括扩展引脚等外设资源。

板载主要资源如下：

| 硬件 | 描述 |
| -- | -- |
|CPU| Cortex-M4 |
|主频| 210MHz |
|SRAM| 128KB+64KB |
|Flash| 512KB |

- 常用外设
  - LED：3个，（PD13、PD14、PD15）
  - 按键：1个，（PA0或PC13)
- 常用接口：串口（PA2、PA3）

## 2. 编译说明

StarterKit-32板级包支持 MDK5，以下是具体版本信息：

| IDE/编译器 | 已测试版本 |
| -- | -- |
| MDK5(ARM Compiler 5 and 6) | MDK5.38 |

## 3. 烧写及执行

下载程序：使用 CMSIS-DAP或者J-link等工具。

### 3.1 配置和仿真

工程已经默认使能了RT-Thread UART驱动、GPIO驱动。若想进一步配置工程请
使用ENV工具。

## 4. 驱动支持情况及计划

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | USART0/1 |
| GPIO | 支持 |  |

## 5. 联系人信息

维护人：

- [FMD-AE](https://github.com/FmdAE)

## 6. 参考

* [StarterKit-32](https://www.fremontmicro.com/down/demoboard/index.aspx)
