# GD32E503V-EVAL 开发板 BSP 说明

## 简介

GD32E503V-EVAL 评估板使用 GD32E503VET6 作为主控制器。评估板使用 GD-Link Mini
USB 接口提供 5V 电源。提供包括扩展引脚在内的及 Reset， Boot， K2， LED， I2S， I2CEEPROM， LCD， NAND Flash， SPI-Flash， SDIO， USB， USART 转 USB 接口等外设资源。

该开发板常用 ** 板载资源 ** 如下：

- GD32E503VET6，主频 180MHz，512KB FLASH ，128KB RAM
- 常用外设

  - LED ：5 个，LEDPWR (电源指示灯），LED1（PC0），LED2（PC2），LED3（PE0），LED4（PE1）
  - 按键：5 个，KEY_A（用户按键，PA0），KEY_B（用户按键，PC13），KEY_C（用户按键，PB14），KEY_D（用户按键，PC5），KEY_Cet（用户按键，PC4）
  - General TM * 10、Advanced TM * 2、Basic TM * 2
  - 系统时钟 * 1
  - 看门狗 * 2
  - RTC * 1
  - USART * 4、UART * 2
  - I2C * 2、I2S * 2
  - SPI * 3
  - CAN2.0B * 1
  - USB2.0 OTG FS * 1
  - TFT-LCD
  - EXMC/SDRAM * 1
  - ADC * 3
  - DAC * 2
  - 最多支持 100GPIOs
- 常用接口：USB 接口
- 调试接口：GD-LINK

## 外设支持

本 BSP 目前对外设的支持情况如下：

| ** 片上外设 ** | ** 支持情况 ** | ** 备注 **                   |
| :----------- | :----------: | :------------------------------- |
| GPIO         |     支持     | PA0, PA1... ---> PIN: 0, 1...111 |
| UART         |     支持     | UART0 - UART5                    |
| ** 扩展模块 ** | ** 支持情况 ** | ** 备注 **                   |
| 暂无         |   暂不支持   | 暂不支持                         |

## 使用说明

使用说明分为如下两个章节：

- 快速上手

  本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

- 进阶使用

  本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。

### 快速上手

本 BSP 为开发者提供 MDK4、MDK5 和 IAR 工程，并且支持 GCC 开发环境，也可使用 RT-Thread Studio 开发。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用数据线连接开发板到 PC，使用 USB 转 232 连接 USART1，打开电源开关。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 GD-Link  仿真器下载程序，在通过 GD-Link  连接开发板的基础上，点击下载按钮即可下载程序到开发板

#### 运行结果

下载程序成功之后，系统会自动运行，LED 闪烁。

连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     4.0.4 build Jan  9 2021
 2006 - 2021 Copyright by rt-thread team
msh >
```

### 进阶使用

此 BSP 默认只开启了 GPIO 和 串口 1 的功能，如果需使用高级功能，需要利用 ENV 工具对 BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入 `menuconfig` 命令配置工程，配置好之后保存退出。

3. 输入 `pkgs --update` 命令更新软件包。

4. 输入 `scons --target=mdk4/mdk5/iar` 命令重新生成工程。

## 注意事项

暂无

## 联系人信息

维护人:

- [drifting1024](https://github.com/drifting1024), 邮箱：<drifting1024@163.com>