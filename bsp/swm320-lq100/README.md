# SWXT-LQ100-32102 V1.1 板级支持包 说明

标签： SYNWIT、Cortex-M4、SWM320VET7、国产MCU

---

## 1. 简介

本文档为 SWXT-LQ100-32102 V1.1 的 BSP(板级支持包) 说明。

通过阅读本文档，开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。

### 1.1  开发板介绍

SWXT-LQ100-32102 V1.1 开发板由华芯微特提供，可满足基础测试及高端开发需求。

开发板外观如下图所示：

SWXT_LQ100-32102 V1.1

![SWXT-LQ100-32102](figures/SWXT-LQ100-32102.jpg "SWXT-LQ100-32102 V1.1")

SWXT-LQ100-32102 V1.1 开发板板载资源如下：

- MCU：SWM320VET7-50  ARM 32-bit Cortex-M4，主频 120MHz，512KB FLASH ，128KB SRAM，2.2～3.6V
- 常用外设
  - LED：1 个，D2 红绿蓝三色LED
  - 按键：3 个，K1、K2、K3
  - Nor Flash S29GL128M
  - SRAM IS62WV51216BLL
- 常用接口：USB打印接口，TFT LCD接口，SD卡接口
- 调试接口：SWD

更多详细信息请咨询[华芯微特技术支持][http://www.synwit.cn/support.html]

### 1.2  MCU 简介

SWM320VET7 是 SYNWIT 公司的一款面向工业控制、白色家电、电机驱动等领域的芯片。包括如下硬件特性：

| 硬件 | 描述 |
| -- | -- |
|芯片型号| SWM320VET7 |
|CPU| ARM Cortex-M4 |
|主频| 120MHz |
|片内SRAM| 128KB |
|片内Flash|  512KB |

## 2. 编译说明

本 BSP 为开发者提供 MDK5 工程。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 Jlink 仿真器下载程序，在通过 Jlink 连接开发板到 PC 的基础上，点击下载按钮即可下载程序到开发板

推荐熟悉 RT_Thread 的用户使用[env工具](https://www.rt-thread.org/page/download.html)，可以在console下进入到 `bsp/swm320-lq100` 目录中，运行以下命令：

`scons`

来编译这个板级支持包。如果编译正确无误，会产生rtthread.elf、rtthread.bin文件。其中 rtthread.bin 可以烧写到设备中运行。

## 3. 烧写及执行

### 3.1 硬件连接

- 使用 USB B-Type 数据线连接开发板到 PC（注意：需要下载安装串口驱动支持 CH340 芯片，使用 MDK5 需要安装 SWM320 相关的 pack）。

  >  USB B-Type 数据线用于串口通讯，同时供电

- 使用 Jlink 连接开发板到 PC （需要 Jlink 驱动）

将串口 0 引脚为：`[PA2/PA3]`和 USB 转串口模块 P2 相连，串口配置方式为115200-N-8-1。

当使用 [env工具](https://www.rt-thread.org/page/download.html) 正确编译产生出rtthread.bin映像文件后，可以使用 ISP 的方式来烧写到设备中。

**建议使用 keil 软件直接下载**。ISP 下载较复杂。

### 3.2 运行结果

如果编译 & 烧写无误，当复位设备后，会在串口上看到板子上的蓝色LED闪烁。串口打印RT-Thread的启动logo信息：

```
 \ | /
- RT -     Thread Operating System
 / | \     4.0.0 build Dec 11 2018
 2006 - 2018 Copyright by rt-thread team
msh />
```

## 4. 驱动支持情况及计划

|**板载外设**     |**支持情况**|**备注**                    |
| ----------------- | :----------: | ----------------------- |
| Nor Flash         | 支持          |                        |
| SDIO TF 卡        | 暂不支持      |                        |
| SRAM              | 支持          |      |
| TFT-LCD           |   暂不支持    |   即将支持             |
|**片上外设**     |**支持情况** |**备注**                  |
| GPIO              |     支持     | PIN：1...100 |
| UART              |     支持     | UART0 / UART1 / UART2 / UART3  |
| SPI               |     支持     | SPI0 / SPI1        |
| I2C               |   支持   |    I2C0 IO模拟   |
| ADC               | 暂不支持 | 即将支持 |
| PWM               |   支持   |  PWM0 / PWM1 /PWM2 /PWM3 其余两个后续补充|
| IWG               |   支持   |                            |
| TIMER             |   支持   |                       |
| RTC               |   支持   |                             |
| CAN               |   暂不支持   |                |

## 5. 联系人信息

维护人：

-[Zohar_Lee](https://github.com/zohar123) email: lizhh@synwit.cn

## 6. 参考

- 芯片[SWM320系列数据手册][http://www.synwit.cn/Public/Uploads/2018-11-05/5bdff49b396d1.pdf]

- [ SWM320_LQFP100原理图](http://www.synwit.cn/Public/Uploads/2018-11-01/5bdab8ad2e5b9.pdf)

- [ SWM320_LQFP64原理图](http://www.synwit.cn/Public/Uploads/2018-11-05/5bdfea74d5712.pdf)

- [ keil pack及其他资料](http://www.synwit.cn/support-1/2.html)
