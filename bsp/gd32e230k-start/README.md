# GD32E230K-START #

## 1. 简介

[GD32E230K-START](http://gd32mcu.21ic.com/site)是兆易科技提供的开发板，使用 Cortex-M23 内核的 GD32E230K8T6 作为主控制器。提供包括扩展引脚及板载 GD-Link 仿真器等外设资源。除 GD32E230K-START（32引脚）外，GD32E230 系列 START 开发板还有 GD32E230C-START（48引脚）、GD32E230G-START（28引脚）、GD32E230F-START（20引脚），四种开发板程序可以通用，可能需要改变部分引脚定义。

板载主要资源如下：

| 硬件 | 描述 |
| -- | -- |
|CPU| Cortex-M23|
|主频| 72MHz |
|SRAM| 8KB |
|Flash| 64KB |

## 2. 编译说明

GD32E230K-START板级包支持 MDK5，以下是具体版本信息：
注：Cortex-M23 内核只支持 ARM Compiler 6 (Armclang)，并不支持 ARM Compiler 5 (armcc)。

| IDE/编译器 | 已测试版本 |
| -- | -- |
| MDK5(ARM Compiler 6) | MDK5.27 | 

## 3. 烧写及执行

下载程序：使用板载 GD-Link 工具。

### 3.1 配置和仿真

工程已经默认使能了RT-Thread UART驱动、GPIO驱动、SPI驱动、I2C驱动。若想进一步配置工程请
使用ENV工具。

## 4. 驱动支持情况及计划

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | USART0/1 |
| GPIO | 支持 |  |
| SPI | 支持 | SPI0/1 |
| I2C | 支持 | I2C0/1 |

## 5. 联系人信息

维护人：

- [xuzhuoyi](https://github.com/xuzhuoyi)

## 6. 参考

* [GD32E230K-START](http://gd32mcu.21ic.com/site)
