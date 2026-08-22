# FM33LG026 #

## 1. 简介

[FM33LG026](开发者论坛：http://www.fmdevelopers.com.cn/forum.php)是复旦微的MCU，使用 Cortex-M0 内核。该BSP由 RT-Thread 官方 bsp/fm33lc026（FM33LC0xx 系列）BSP 移植改造而来（目录名改为 fm33lg026），底层驱动替换为官方 FM33LG0XX_FL_Library_v2.3.5，LG0XX系列通用，重新选择型号即可，可能需要改变部分引脚定义。

FM33LG0xxx系列低功耗MCU，基于ARM Cortex-M0内核，集成大容量嵌入式闪存，具备丰富的模拟和数字外设，并具有优异的低功耗特性。主要资源如下：

| 硬件 | 描述 |
| -- | -- |
|CPU| Cortex-M0|
|主频| 64MHz（PLL，RCHF 8M -> PLL x8） |
|SRAM| 32KB |
|Flash| 128KB（LG026）/ 256KB（LG048）|

## 2. 编译说明

只适配了MDK5，使用MDK5编译。

| IDE/编译器 | 已测试版本 |
| -- | -- |
| MDK5 | MDK5.27 | 

## 3. 烧写及执行

下载程序：使用 J-Link 工具（需安装 FM33LG0XX 的 Keil DFP pack）。

### 3.1 配置和仿真

工程已经默认使能了RT-Thread UART驱动（console 为 uart0，PA13/PA14）和 GPIO 驱动。若想进一步配置工程请使用ENV工具。

## 4. 驱动支持情况及计划

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | uart0（console，PA13/PA14）/1/4 |
| GPIO | 支持 | PA/PB/PC/PD，含中断 |

## 5. 移植说明

本 BSP 由 RT-Thread 官方 bsp/fm33lc026（FM33LC0xx 系列）BSP 移植到 FM33LG0xx，要点：

1. **库替换**：`libraries/FM33LG0xx_FL_Driver/` 为官方 FM33LG0XX_FL_Library_v2.3.5 全套
2. **时钟差异**：LC 用 RCC API，LG 用 CMU API（`FL_CMU_*`）；RTC 由 rtc.c 拆为 rtca.c + rtcb.c
3. **RAM 差异**：LC04X 24KB → LG 32KB（heap 上限、link.sct、uvprojx IRAM 均同步为 0x8000）
4. **system 文件**：必须使用官方 V2.0.0 完整版（BSP 自带的 V1.02 是占位模板）
5. **已知修复**：
   - drv_gpio.c 补 `INIT_BOARD_EXPORT(rt_hw_pin_init)`（原 BSP 缺失导致 pin 设备不注册）
   - drv_gpio.h 的 GET_PIN 宏端口步长修正为 0x0040（原 BSP 为 0x0400，会导致引脚错映射到 PA 口）

## 6. 联系人信息

维护人：

- [jqj96](https://github.com/jqj96)（原 BSP）
- 移植：王成雷

## 7. 参考

- FM33LG0XX_FL_Library_v2.3.5（官方库）
