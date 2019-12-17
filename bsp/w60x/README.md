# Winner Micro W60X 板级支持包

## 简介

W60X 芯片是[联盛德微电子](http://www.winnermicro.com)推出的一款嵌入式 Wi-Fi SoC 芯片。该芯片集成度高，所需外围器件少，性价比高。适用于 IoT（智能家庭）领域各种智能产品。高度集成的 Wi-Fi 功能是其主要功能；另外，该芯片集成 Cortex-M3 内核，内置 QFlash，SDIO、SPI、UART、GPIO、I²C、PWM、I²S、7816 等接口, 支持多种硬件加解密算法。

更多信息请查看`packages/wm_libraries/DOC 中的寄存器手册`。

## 外设支持

| 驱动       | 支持情况 | 备注                                            |
| ---------- | :------: | :---------------------------------------------: |
| UART       | 支持     | UART0/UART1/UART2                               |
| GPIO       | 支持     | 自动根据芯片型号选择引脚布局                    |
| SPI        | 支持     | 低速 SPI，支持 SPI BUS，8/32bit 主机模式        |
| WDT        | 支持     | 支持                                            |
| I2C        | 支持     | 硬件 I2C 和 软件 I2C                            |
| RTC        | 支持     | 支持 ntp 同步、支持 Alarm                       |
| ADC        | 支持     | 8 channel ADC 采集 CPU 温度采集（W601 支持）    |
| PWM        | 支持     | 5 channel PWM 输出                              |
| Timer      | 支持     | 5个Timers 独立工作                              |
| Crypto     | 支持     | 支持硬件 AES/DES/3DES/RC/SHA1/MD3/CRC 加解密算法|
| WiFi       | 支持     | 支持 IEEE802.11b/g/n，支持 sta、ap、ap+sta 模式 |
| 低功耗     | 支持     | 支持 WiFi 协议节电，支持 standby 深度节电       |

## 使用说明

使用说明分为如下两个章节：

- 快速上手

    本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

- 进阶使用

    本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。

### 快速上手

本 BSP 为开发者提供 MDK5 和 IAR 工程，并且支持 GCC 开发环境。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 编译

1. env 工具中使用 `pkgs --update` 命令下载必要的软件包。

2. env 工具中使用 `scons --target=mdk5` 命令生成工程

2. 双击 project.uvprojx 文件，打开 MDK5 工程，完成程序的编译工作。

#### 下载

目前支持两种下载方式，下面将分别说明：

- JLink下载

    将 JLink 连接到开发板，然后点击 MDK5 中的下载按钮即可下载程序到开发板。JLink 下载之前 **务必参考**  `packages/wm_libraries/DOC` 目录下的 `《WM_W60X_SWD调试配置指南》`。

- 串口下载

    程序编译正确无误后，会在 `Bin` 文件夹中生成 `.img` 固件，使用带有 Xmodem 协议的串口工具对固件进行下载（默认 UART0-115200）。串口下载参考 `packages/wm_libraries/DOC` 目录下的 `《WM_W60X_固件升级指导》`。

#### 运行结果

下载程序成功之后，系统会自动运行，会在`UART0`上看到 RT-Thread 的启动 logo 信息：

```bash
 \ | /
- RT -     Thread Operating System
 / | \     4.0.1 build Mar 21 2019
 2006 - 2019 Copyright by rt-thread team
```

- 默认串口`UART0` 波特率`115200`

### 进阶使用

此 BSP 默认只开启了 GPIO 和 UART0 的功能，如果需使用其他外设，需要利用 ENV 工具对 BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=mdk5` 或 `scons --target=iar` 命令重新生成工程。

## 注意事项

> 使用 W600 芯片时,请注意芯片 Flash 的大小，区分 2M Flash 和 1M Flash。更多信息请查看 `packages/wm_libraries/DOC` 的文档：

- 《WM_W60X_2M_Flash布局说明》
- 《WM_W60X_2M_Flash参数区使用说明》
- 《WM_W60X_2M_Flash固件生成说明》

## 联系人信息

[RT_Thread](https://github.com/RT-Thread/rt-thread)

[WinnerMicro](https://github.com/WinnerMicro)

## 感谢

[flyingcys](https://github.com/flyingcys) < [294102238@qq.com](mailto:294102238@qq.com) >