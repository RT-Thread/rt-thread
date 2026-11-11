# GD32470I-EVAL评估板BSP说明

## 简介

GD32470I-EVAL评估板使用GD32F470IKH6作为主控制器。评估板使用Mini USB接口或者DC-005连接器提供5V电源。该评估板具有丰富的板载资源，提供包括扩展引脚在内的及SWD, Reset, Boot, User button key, LED, CAN, I2C, I2S, USART, RTC, LCD, SPI, ADC, DAC, EXMC, CTC, SDIO, DCI, ENET, USBFS, USBHS, GD-Link等外设资源，图片如下：

![board](figures/board.jpg)

> 更多关于开发板的资料可以查看GD32470I-EVAL-V1.0原理图。

该开发板常用 **板载资源** 如下：

- GD32F470IKH6，主频 240MHz，CPU内核：ARM Cortex-M4，3072KB FLASH ，512KB RAM 
- 常用外设
  
  - 用户LED ：3个，LED1（PE2），LED2（PE3），LED3（PF10）
  - 电源指示灯：一个红色LED
  - 按键：4个，K1-Reset(NRST)，K2-Wakeup（PA0），K3-Tamper（PC13），K4-User key（PB14）
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
  - EXMC/NAND Flash * 1
  - ADC * 3
  - DAC * 2
  - DCI摄像头接口 * 1
  - 最多支持176GPIOs
- 调试接口：GD-Link
- 支持RGB接口和MCU屏幕接口
- 一路SDIO-TF卡
- SPI Flash：板载Flash
- SDRAM：外扩SDRAM
- 一路Mini USB
- 调试接口引出了SWD和UART
- 丰富的扩展引脚
- 开发板更多信息请查看GD32470I-EVAL原理图

## 外设支持

| **片上外设** | **支持情况** | **备注**                           |
|:------------|:------------:|:----------------------------------|
| GPIO        | 支持         | PA0, PA1... ---> PIN: 0, 1...175 |
| UART        | 支持         | UART0 - UART7                    |
| SPI         | 支持         | 支持 SPI0 ~ SPI5，可配置多个总线 |
| I2C         | 支持         | 支持 I2C0 ~ I2C2                 |


## 使用说明

使用说明分为如下两个章节：

- 快速上手
  
  本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

- 进阶使用
  
  本章节是为需要在 RT-Thread 操作系统上使用更多开发板资源的开发者准备的。通过使用 ENV 工具对 BSP 进行配置，可以开启更多板载资源，实现更多高级功能。

### 快速上手

本 BSP 为开发者提供 MDK5工程，支持 GCC 开发环境，也可使用RT-Thread Studio开发。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用GD-Link调试器连接开发板到 PC，使用USB2TTL连接USART0，并给开发板供电（可使用Mini USB接口或DC-005连接器提供5V电源）。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 GD-Link 仿真器下载程序，在通过 GD-Link 连接开发板的基础上，点击下载按钮即可下载程序到开发板

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

此 BSP 默认只开启了 GPIO 和 串口0的功能，如果需使用高级功能，需要利用 ENV 工具对BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=mdk4/mdk5/iar` 命令重新生成工程。

## 注意事项

- 若需使用板载 SPI Flash，请在 `menuconfig` 中启用以下配置：

```
RT-Thread Components  --->
  Device Drivers  --->
    [*] Enable SPI BUS support (RT_USING_SPI)
        [*] Enable SFUD for SPI Flash (RT_USING_SFUD)

Hardware Drivers Config  --->
  On-chip Peripheral Drivers  --->
    [*] Enable SPI BUS (BSP_USING_SPI)
        [*] Enable SPI5 BUS (BSP_USING_SPI5)
```

- 若需使用SDRAM功能，请在 `menuconfig` 中启用EXMC配置
- 若需使用DCI摄像头功能，请在 `menuconfig` 中启用相应的DCI配置
- 若需使用LCD显示功能，请在 `menuconfig` 中启用LCD相关配置


## 联系人信息

维护人:

- [godmial](https://github.com/godmial), 邮箱：<2633967641@qq.com>
- [yuanzihao](https://github.com/zihao-yuan/), 邮箱：<y@yzh.email>
