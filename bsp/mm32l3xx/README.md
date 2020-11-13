# MM32 MiniBoard Rev.D2 开发板BSP 说明

标签： MM32、Cortex-M3、MM32L373PF、国产MCU

---

## 1. 简介

本文档为上海灵动微电子AE团队为MM32 MiniBoard开发板提供的BSP(板级支持包) 说明。通过阅读本文档，开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。

### 1.1  开发板介绍

MM32 MiniBoard Rev.D2 是为了用户快速上手、了解学习MM32系列MCU的一块入门级开发板，可满足基础测试及高端开发需求。

开发板外观如下图所示：

MM32 MiniBoard Rev.D2 

![MM32 MiniBoard Rev.D2](figures/MM32%20MiniBoard%20Rev.D2_1.jpg)

MM32 MiniBoard Rev.D2 开发板板载资源如下：

- MCU：MM32L373PF  ARM 32-bit Cortex-M3，主频 96MHz，128KB FLASH ，20KB SRAM
- 常用外设
  - LED：4个4色LED，可用于测试GPIO功能
  - 按键：1个复位按键、 1个WakeUp按键、两个普通按键
  - SPI Flash W25P80，容量8M bit，速度50MHz
  - I2C接口EEPROM芯片，AT24C02，容量256字节
  - 1个旋转式电位计（变阻器），用于ADC测试
  - 能耗测试开关：待机模式和运行模式
- 常用接口：Micro-USB接口，RS-232接口，UART接口
- 调试接口：SWD，支持J-Link、U-LINK2、MM32-LINK调试器

更多详细信息请咨询[灵动微电子技术支持][http://www.mm32.com.cn]

### 1.2  MCU 简介

MM32L373PF 是上海灵动微电子股份有限公司的一款面向电机驱动、工业应用、消费电子、白色家电等领域的低功耗芯片。包括如下硬件特性：

| 硬件 | 描述 |
| -- | -- |
|芯片型号| MM32L373PF |
|CPU| ARM Cortex-M3 |
|主频| 96MHz |
|片内SRAM| 20KB |
|片内Flash|  128KB |

## 2. 编译说明

本 BSP 为开发者提供 MDK5 工程。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 Jlink 仿真器下载程序，在通过 Jlink 连接开发板到 PC 的基础上，点击下载按钮即可下载程序到开发板

推荐熟悉 RT_Thread 的用户使用[env工具](https://www.rt-thread.org/page/download.html)，可以在console下进入到 `bsp/mm32l37x` 目录中，运行以下命令：

`scons`

来编译这个板级支持包。如果编译正确无误，会产生rtthread.elf、rtthread.bin文件。其中 rtthread.bin 可以烧写到设备中运行。

## 3. 烧写及执行

### 3.1 硬件连接

使用MM32-LINK或Jlink等调试工具连接开发板到PC，通过调试调试工具供电或使用Micro-USB供电。若使用Jlink等调试工具，还需要将UART1_TX(PA9)、UART1_RX(PA10)、GND接到串口工具上。

使用MM32-LINK连接开发板如下图所示：

MM32-LINK+MiniBoard Rev.D2

![MM32-LINK+MiniBoard Rev.D2](figures/MM32%20MiniBoard%20Rev.D2_2.jpg)

### 3.2 运行结果

如果编译 & 烧写无误，当复位设备后，会看到板子上的4个LED闪烁。串口打印RT-Thread的启动logo信息：

```
 \ | /
- RT -     Thread Operating System
 / | \     4.0.0 build Dec 11 2018
 2006 - 2018 Copyright by rt-thread team
msh />
```

## 4. 驱动支持情况及计划

| 驱动       | 支持情况 | 备注                         |
| ---------- | :------: | :--------------------------: |
| UART       | 支持     | UART1/2                   |
| GPIO       | 支持     | / |

## 5. 联系人信息

维护人：

-[Henryhuang](https://github.com/huangzushui) email: huangzushui@mindmotion.com.cn

## 6. 参考

- [MM32L3xx_n系列数据手册](http://www.mm32.com.cn/getfile.aspx?id=1062)

- [MM32L3xx_n系列用户手册](http://www.mm32.com.cn/getfile.aspx?id=578)

- [MiniBoardStartKit资料包](http://www.mm32.com.cn/download.aspx?cid=2545)

- [keil pack安装包](http://www.mm32.com.cn/download.aspx?cid=2546)

- [MM32 支持工具包](http://www.mm32.com.cn/download.aspx?cid=2547)
