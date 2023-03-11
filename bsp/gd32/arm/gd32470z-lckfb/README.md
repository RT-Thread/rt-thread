# GD32470-LCKFB梁山派开发板BSP说明

## 简介

GD32470Z-LCKFB梁山派是立创开发板推出的一款GD32F470系列的开发板，最高主频高达240M，该开发板具有丰富的板载资源，是基于GD32F470ZGT6的全国产化开源开发板，图片如下：

![board](figures/board.png)

> 2022年12月05号后立创·梁山派开发板主控从GD32F450ZGT6升级到了GD32F470ZGT6 两款芯片兼容主要差别GD32F450ZGT6主频200、SDRAM 256K，GD32F470ZGT6主频240、SDRAM 512K。

该开发板常用 **板载资源** 如下：

- GD32F470ZGT6，主频 240MHz，CPU内核：ARM Cortex-M4，1024KB FLASH ，512KB RAM 
- 常用外设
  
  - 用户LED ：4个，LED1 (PE3），LED2（PD7），LED3（PG3），LED4（PA5）
  - 电源指示灯：一个红色LED
  - 按键：3个，KEY_UP（PA0），RESET(NRST)，BOOT0（PB2）
  - General TM * 10、Advanced TM * 2、Basic TM * 2
  - SysTick * 1
  - 看门狗 * 2
  - RTC * 1
  - USART * 4、UART * 4
  - I2C * 3、I2S * 2
  - SPI * 6
  - SDIO * 1
  - CAN * 2
  - USBFS+HS
  - 以太网 * 1
  - TFT-LCD
  - EXMC/SDRAM * 1
  - ADC * 3
  - DAC * 2
  - 最多支持114GPIOs
- 调试接口：CMSIS-DAP
- 支持RGB接口和MCU屏幕接口
- 一路SDIO-TF卡
- SPI Flash：W25Q64
- SDRAM：W9825G6KH-6I
- 一路Type-C USB
- 调试接口引出了SWD和UART
- 双2*20PIN 2.54排针引出了68个可编程IO
- 开发板更多信息请查看[立创开发板官网](https://lckfb.com/)

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设** | **支持情况** | **备注**                           |
|:-------- |:--------:|:-------------------------------- |
| GPIO     | 支持       | PA0, PA1... ---> PIN: 0, 1...113 |
| UART     | 支持       | UART0 - UART7                    |
| **扩展模块** | **支持情况** | **备注**                           |
| 暂无       | 暂不支持     | 暂不支持                             |

## 使用说明

使用说明分为如下两个章节：

- 快速上手
  
  本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

- 进阶使用
  
  本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。

### 快速上手

本 BSP 为开发者提供 MDK5工程，支持 GCC 开发环境，也可使用RT-Thread Studio开发。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用调试器连接开发板到 PC，使用USB2TTL连接USART0，并给开发板供电。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 CMSIS-DAP 仿真器下载程序，在通过 CMSIS-DAP  连接开发板的基础上，点击下载按钮即可下载程序到开发板

#### 运行结果

下载程序成功之后，系统会自动运行，LED 闪烁。

连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     5.0.0 build Mar  3 2023 00:43:44
 2006 - 2022 Copyright by RT-Thread team
msh />
```

### 进阶使用

此 BSP 默认只开启了 GPIO 和 串口1的功能，如果需使用高级功能，需要利用 ENV 工具对BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=mdk4/mdk5/iar` 命令重新生成工程。

## 注意事项

暂无

## 联系人信息

维护人:

- [yuanzihao](https://github.com/zihao-yuan/), 邮箱：<y@yzh.email>
