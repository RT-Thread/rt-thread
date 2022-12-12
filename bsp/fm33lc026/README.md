# FM33LC026 #

## 1. 简介

[FM33LC026](开发者论坛：http://www.fmdevelopers.com.cn/forum.php)是复旦微的MCU，使用 Cortex-M0 内核。该BSP基于FM026开发调试，LC0XX系列通用，重新选择型号即可，可能需要改变部分引脚定义。
FM33LC0xxx系列低功耗MCU，基于ARM Cortex-M0内核，集成大容量嵌入式闪存，具备丰富的模拟和数字外设，并具有优异的低功耗特性。FM33LC0xxx系列包含三个子系列，分别为支持无晶振USB FS device的FM33LC0xxU系列，和不支持USB的FM33LC0xxN系列，以及FM33LC0x4NR系列。
主要资源如下：

| 硬件 | 描述 |
| -- | -- |
|CPU| Cortex-M0|
|主频| 64MHz |
|SRAM| 24KB |
|Flash| 128KB |

## 2. 编译说明

只适配了MDK5，使用MDK5编译。

| IDE/编译器 | 已测试版本 |
| -- | -- |
| MDK5 | MDK5.27 | 

## 3. 烧写及执行

下载程序：使用 J-Link 工具。

### 3.1 配置和仿真

工程已经默认使能了RT-Thread UART驱动。若想进一步配置工程请
使用ENV工具。

## 4. 驱动支持情况及计划

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | USART0/1/4/5 |

## 5. 联系人信息

维护人：

- [jqj96](https://github.com/jqj96)

## 6. 参考

