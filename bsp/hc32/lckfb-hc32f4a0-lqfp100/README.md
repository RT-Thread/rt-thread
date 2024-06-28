# XHSC EV_F4A0_LQ176 开发板 BSP 说明

## 简介

本文档为小华半导体为 EV_F4A0_LQ176 开发板提供的 BSP (板级支持包) 说明。

主要内容如下：

- 开发板资源介绍
- BSP 快速上手
- 进阶使用方法

通过阅读快速上手章节开发者可以快速地上手该 BSP，将 RT-Thread 运行在开发板上。在进阶使用指南章节，将会介绍更多高级功能，帮助开发者利用 RT-Thread 驱动更多板载资源。

## 开发板介绍

EV_F4A0_LQ176 是 XHSC 官方推出的开发板，搭载 HC32F4A0SITB 芯片，基于 ARM Cortex-M4 内核，最高主频 240 MHz，具有丰富的板载资源，可以充分发挥 HC32F4A0SITB 的芯片性能。

开发板外观如下图所示：

 ![board](figures/board.jpg)

EV_F4A0_LQ176 开发板常用 **板载资源** 如下：

- MCU：HC32F4A0SITB，主频240MHz，2048KB FLASH，512KB RAM
- 外部RAM：IS62WV51216(SRAM, 1MB) IS42S16400J(SDRAM, 8MB)
- 外部FLASH: MT29F2G08AB(Nand, 256MB) W25Q64(SPI NOR, 64MB)
- 常用外设
  - LED：3 个， user LED(LED0,LED1,LED2)。
  - 按键：11 个，矩阵键盘(K1~K9)、WAKEUP(K10)、RESET(K11)。
- 常用接口：USB转串口、SD卡接口、以太网接口、LCD接口、USB HS、USB FS、USB 3300、DVP接口、3.5mm耳机接口、Line in接口、喇叭接口
- 调试接口：板载DAP调试器、标准JTAG/SWD。

开发板更多详细信息请参考小华半导体半导体[EV_F4A0_LQ176](http://www.xhsc.com.cn)

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **板载外设**  | **支持情况** |               **备注**                |
| :------------ | :-----------: | :-----------------------------------: |
| USB 转串口    |      支持     |          使用 UART1                  |
| ETH           |     支持     |              					     |
| LED           |     支持     |           LED                        |
| Nand | 支持 | MT29F2G08AB |
| SDRAM | 支持 | IS42S16400J |

| **片上外设**  | **支持情况** |               **备注**                |
| :------------ | :-----------: | :-----------------------------------: |
| Crypto | 支持 | AES, CRC, HASH, RNG, UID |
| DAC | 支持 |  |
| ADC           |     支持     |                             |
| CAN           |     支持     |                                       |
| GPIO          |     支持     | PA0, PA1... PI13 ---> PIN: 0, 1...141 |
| PM | 支持 |  |
| Lptimer | 支持 |  |
| Hwtimer | 支持 |  |
| Pulse_encoder | 支持 |  |
| PWM | 支持 |  |
| RTC | 支持 | 闹钟精度为1分钟 |
| WDT | 支持 |  |
| I2C           |     支持     |              软件、硬件 I2C                 |
| QSPI | 支持 |  |
| SPI           |     支持     |              SPI1~6                   |
| SDIO | 支持 |  |
| UART V1 & V2         |     支持     |              UART1~10                 |
| USB | 支持 | USBFS/HS Core， device/host模式 |

## 使用说明

使用说明分为如下两个章节：

- 快速上手

    本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

- 进阶使用

    本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。


### 快速上手

本 BSP 为开发者提供 MDK5 和 IAR 工程，并且支持 GCC 开发环境。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用Type-A to MircoUSB线连接开发板和PC供电。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用板载 DAP 下载程序，点击下载按钮即可下载程序到开发板。

#### 运行结果

下载程序成功之后，系统会自动运行，观察开发板上LED的运行效果，绿色LED11会周期性闪烁。

USB虚拟COM端口默认连接串口1，在终端工具里打开相应的串口，复位设备后，可以看到 RT-Thread 的输出信息:

```
 \ | /
- RT -     Thread Operating System
 / | \     4.1.0 build Apr 24 2022 13:32:39
 2006 - 2022 Copyright by RT-Thread team
msh >
```

### 进阶使用

此 BSP 默认只开启了 GPIO 和 串口 1 的功能，更多高级功能需要利用 env 工具对 BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=mdk5/iar` 命令重新生成工程。

## 注意事项

| 板载外设 |  模式  | 注意事项                                                     |
| :------: | :----: | :----------------------------------------------------------- |
|   USB    | device | 由于RTT抽象层的设计，当配置为CDC设备时，打开USB虚拟串口，需使能流控的DTR信号。（如使用SSCOM串口助手打开USB虚拟串口时，勾选DTR选框） |
|   USB    | device | 由于外部PHY管脚复用的原因，当配置使用USBHS Core并且使用外部PHY时，需先通过J14连接到主机（如PC），再复位MCU运行程序；或者将J24跳帽先短接，再复位MCU运行程序。 |
|   USB    |  host  | 由于main()函数中的LED闪烁示例，使用的是USBFS主机口的供电控制管脚，因而当配置为使用USBFS Core的主机模式时，需要将main()函数中的LED示例代码手动屏蔽。 |
|   USB    |  host  | 为确保USB主机对外供电充足，建议通过J35外接5V电源供电，并短接J32的EXT跳帽。 |
|   USB    |  host  | 由于外部PHY管脚复用的原因，当配置使用USBHS Core并且使用外部PHY时，需通过J14先连接好OTG线，再复位MCU运行程序；或者将J24跳帽先短接，再复位MCU运行程序。 |
|   USB    |  host  | 目前仅实现并测试了对U盘的支持。                              |
|   USB    |  host  | 若配置为U盘主机模式，出现部分U盘无法识别或者写入失败时，可以尝试将RTT抽象层中rt_udisk_run()函数的rt_usbh_storage_reset()操作注释掉，测试是否可以获得更好的兼容性。 |
|   USB    |  ALL   | 由于管脚复用的原因，当配置使用USBHS Core时，无法同时使用板载SPI FLASH。 |

## 联系人信息

维护人:

-  [小华半导体MCU](https://www.xhsc.com.cn)，邮箱：<xhsc_mcu@xhsc.com.cn>