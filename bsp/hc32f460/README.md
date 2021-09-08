# HC32F460PETB#

## 1. 简介

[HC32F460](http://www.hdsc.com.cn/Category83-1487)系列是基于 ARM® Cortex®-M4 32-bit RISC CPU，最高工作频率 200MHz 的高性能MCU。 Cortex-M4 内核集成了浮点运算单元（ FPU） 和 DSP，实现单精度浮点算术运算，支持所有 ARM 单精度数据处理指令和数据类型，支持完整 DSP 指令集。HC32F460 系列集成了高速片上存储器，包括最大 512KB 的 Flash，最大 192KB 的 SRAM。
主要资源如下：

| 硬件 | 描述 |
| -- | -- |
|CPU| Cortex-M4|
|主频| 100MHz |
|SRAM| 192KB |
|Flash| 512KB |

## 2. 编译说明

目前仅支持支持 MDK5，以下是具体版本信息：

| IDE/编译器 | 已测试版本 |
| -- | -- |
| MDK5(ARM Compiler 5) | MDK5.31 | 

## 3. 烧写及仿真

下载程序：使用板载 J-Link 工具。

## 4. 驱动支持情况

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | USART1/2/3/4 |
| GPIO | 支持 |  |
##5.运行结果
下载程序成功之后，系统会自动运行，在终端工具里打开相应的串口，复位设备后，可以看到 RT-Thread 的输出信息:

```
 \ | /
- RT -     Thread Operating System
 / | \     4.0.4 build Sep 3 2021
 2006 - 2021 Copyright by rt-thread team
msh >
```
6.进阶使用
默认只开启了 GPIO 输出、中断和 串口4的功能，更多接口需要利用 env 工具对 BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=mdk5` 命令重新生成工程。

## 5. 联系人信息

维护人：

- [lizhengyang](https://github.com/GoldBr1987)

