# Nano STM32F103C8T6最小系统板(BluePill) BSP 说明

[[English]](README.md)

## 简介

本 BSP 为基于 STM32F103C8T6最小系统板(BluePill) 的最小（nano）配置说明。本 BSP 默认只开启基础的内核功能，关闭了 device 框架，和 msh 组件。

## 开发板介绍

STM32F103C8T6最小系统，采用SWD调试接口，可以用3个接口就能完成调试下载的任务，采用了官方建议的负载RTC晶振方案，小体积高频率的STM32实验板

开发板外观如下图所示：

![board](figures/Bluepill_pinout.png)

该开发板常用 **板载资源** 如下：

- MCU：STM32F103C8T6，主频 72MHz，64KB FLASH ，20KB RAM
- 外部 RAM：无
- 外部 FLASH：无
- 常用外设
  - LED：1个 PC13
- 常用接口：无
- 调试接口：SWD调试接口


## 使用说明

### 快速上手

本 BSP 为开发者提供 MDK4、MDK5 和 IAR 工程，并且支持 GCC 开发环境。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用数据线连接开发板到 PC，打开电源开关。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 J-Link 仿真器下载程序，在通过 J-Link 连接开发板的基础上，点击下载按钮即可下载程序到开发板

#### 运行结果

下载程序成功之后，系统会自动运行，默认没有任何任务运行，系统会在 idle 线程里运行。

### 进阶使用

此 BSP 默认只开启了基础的实时内核功能，如果需使用外设、组件等更多高级功能，再用 ENV 工具对BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=mdk4/mdk5/iar` 命令重新生成工程。

本章节更多详细的介绍请参考 [STM32 系列 BSP 外设驱动使用教程](../docs/STM32系列BSP外设驱动使用教程.md)。

## 注意事项
- 无

## 感谢 & 维护

- 感谢[obito0](https://github.com/obito0)提供的[原始工程](../stm32f103-mini-system)
- [Meco Man](https://github.com/mysterywolf): jiantingman@foxmail.com