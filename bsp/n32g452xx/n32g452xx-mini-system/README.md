# N32G452XX MINI-SYSTEM BSP 说明

## 简介

N32G452 MINI-SYSTEM 是国民技术推出的一款N32G452系列的评估板(目前市面还没有，以后也可能不会有)，其搭载的MCU主要资源参数如下：

| 硬件      | 描述          |
| --------- | ------------- |
| 芯片型号  | N32G452RCL7  |
| CPU       | ARM Cortex M4 |
| 主频      | 144M          |
| 片内SRAM  | 80K可扩展144K |
| 片内FLASH | 256K         |

## 编译说明

N32G452 MINI-SYSTEM 板级包支持MDK5开发环境和GCC编译器，以下是具体版本信息：

| IDE/编译器 | 已测试版本                   |
| ---------- | ---------------------------- |
| MDK5       | MDK533                       |
| GCC        | GCC 6.2.1 20161205 (release) |

## 板载资源

- MCU：N32G452RCL7，主频 144MHz，256KB FLASH ，80KB可扩展到144KB RAM
- 常用接口：插针串口J8
- 调试接口，JLINK、板载的 NS-LINK SWD 下载

## 外设支持

本 BSP 目前对外设驱动的支持情况如下：

| 驱动      | 支持情况 |            备注            |
| --------- | -------- | :------------------------: |
| UART      | 支持(已移植，已测试)     | USART1/2/3                 |
| GPIO      | 支持(已移植，已测试)     | PA0...PF7                  |
| ADC       | 支持(已移植，已测试)     | ADC1/2                     |
| PWM       | 支持(已移植，已测试)     | TMR1/2                     |
| HWTIMER   | 支持(已移植，已测试)     | TMR6/7                     |

### IO在板级支持包中的映射情况

| IO号 | 板级包中的定义 |
| ---- | -------------- |
| PA9  | USART1_TX      |
| PA10 | USART1_RX      |
| PA2  | USART2_TX      |
| PA3  | USART2_RX      |
| PB10 | USART3_TX      |
| PB11 | USART3_RX      |
| PA4  | SPI1_NSS       |
| PA5  | SPI1_SCK       |
| PA6  | SPI1_MISO      |
| PA7  | SPI1_MOSI      |
| PB12 | SPI2_NSS       |
| PB13 | SPI2_SCK       |
| PB14 | SPI2_MISO      |
| PB15 | SPI2_MOSI      |
| PB6  | I2C1_SCL       |
| PB7  | I2C1_SDA       |
| PC8  | SDIO1_D0       |
| PC9  | SDIO1_D1       |
| PC10 | SDIO1_D2       |
| PC11 | SDIO1_D3       |
| PC12 | SDIO1_CK       |
| PD2  | SDIO1_CMD      |
| PA8  | PWM_TMR1_CH1   |
| PA11 | PWM_TMR1_CH4   |
| PA0  | PWM_TMR2_CH1   |
| PA1  | PWM_TMR2_CH2   |
| PC0  | ADC1/2_IN10    |
| PC1  | ADC1/2_IN11    |
| PC2  | ADC1/2_IN12    |
| PC3  | ADC1/2_IN13    |

## 使用说明

    本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

### 快速上手

本 BSP 为开发者提供 MDK5工程，并且支持 GCC 开发环境。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用数据线连接开发板到 PC，打开电源开关。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

#### 运行结果

下载程序成功之后，系统会自动运行，观察开发板上 LED 的运行效果，LED1 会周期性闪烁。

连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，在串口上可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     4.0.4 build Aug 19 2021
 2006 - 2021 Copyright by rt-thread team
msh />
```

## 注意事项

1. 使用 J-LINK 下载时，请设置下载完成自动复位（J-Flash设置步骤：`Options->Project settings->production->Start application`），否则下载完成后手动按键复位无法启动，初步定位问题原因为：芯片下电缓慢，参考《N32G43x系列芯片电源系统设计指南》或联系FAE了解情况。

## 联系人信息

维护人:

- [LinYuanbo](https://github.com/Lim-LinYuanbo)
- [breo.com](https://github.com/breo-shenzhen)
