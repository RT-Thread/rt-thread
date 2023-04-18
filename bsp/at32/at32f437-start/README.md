# AT32F437 AT-START 开发板 BSP 说明

## 简介

AT32F437 AT-START是雅特力推出的一款AT32F437系列的评估板，其搭载的MCU主要资源参数如下：

| 硬件      | 描述           |
| --------- | ---------------|
| 芯片型号  | AT32F437ZMT7   |
| CPU       | ARM Cortex M4  |
| 主频      | 288M           |
| 片内SRAM  | 384K可扩展512K |
| 片内FLASH | 4032K          |

## 编译说明

AT32F437-START板级包支持MDK4﹑MDK5﹑IAR开发环境和GCC编译器，以下是具体版本信息：

| IDE/编译器 | 已测试版本                   |
| ---------- | ---------------------------- |
| MDK4       | MDK4.74                      |
| MDK5       | MDK531                       |
| IAR        | IAR8.20                      |
| GCC        | GCC 5.4.1 20160919 (release) |

## 板载资源

- MCU：AT32F437ZMT7，主频 288MHz，4032K FLASH ，384K可扩展到512K RAM
- 常用外设
  - LED：3个，（红色PD13、白色PD14、绿色PD15）
  - 按键：1个，KEY_USER（兼具唤醒功能，PA0)
- 常用接口：插针串口J8
- 调试接口，JLINK、板载的 AT-LINK SWD 下载

## 外设支持

本 BSP 目前对外设驱动的支持情况如下：

| 驱动      | 支持情况 |            备注            |
| --------- | -------- | :------------------------: |
| UART      | 支持     | USART1/2/3                 |
| GPIO      | 支持     | PA0...PH7                  |
| IIC       | 支持     | GPIO模拟I2C                |
| SPI       | 支持     | SPI1/2                     |
| ADC       | 支持     | ADC1/2                     |
| DAC       | 支持     | DAC1                       |
| PWM       | 支持     | TMR1/2                     |
| HWTIMER   | 支持     | TMR3/4/5                   |
| SDIO      | 支持     | SDIO1                      |
| CAN       | 支持     | CAN1/2                     |
| QSPI      | 支持     | QSPI1/2                    |
| WDT       | 支持     |                            |
| RTC       | 支持     |                            |
| FLASH     | 支持     |                            |
| EMAC      | 支持     |                            |
| SDRAM     | 支持     |                            |
| USB       | 支持     |                            |

### IO在板级支持包中的映射情况

| IO号 |   板级包中的定义  |
| ---- | ----------------- |
| PD13 | LED2              |
| PD14 | LED3              |
| PD15 | LED4              |
| PA9  | USART1_TX         |
| PA10 | USART1_RX         |
| PD5  | USART2_TX         |
| PD6  | USART2_RX         |
| PB10 | USART3_TX         |
| PB11 | USART3_RX         |
| PA4  | SPI1_NSS          |
| PA5  | SPI1_SCK          |
| PA6  | SPI1_MISO         |
| PA7  | SPI1_MOSI         |
| PB12 | SPI2_NSS          |
| PB13 | SPI2_SCK          |
| PB14 | SPI2_MISO         |
| PB15 | SPI2_MOSI         |
| PB6  | I2C1_SCL          |
| PB7  | I2C1_SDA          |
| PC8  | SDIO1_D0          |
| PC9  | SDIO1_D1          |
| PC10 | SDIO1_D2          |
| PC11 | SDIO1_D3          |
| PC12 | SDIO1_CK          |
| PD2  | SDIO1_CMD         |
| PA8  | PWM_TMR1_CH1      |
| PA11 | PWM_TMR1_CH4      |
| PA0  | PWM_TMR2_CH1      |
| PA1  | PWM_TMR2_CH2      |
| PC0  | ADC1/2_IN10       |
| PC1  | ADC1/2_IN11       |
| PC2  | ADC1/2_IN12       |
| PC3  | ADC1/2_IN13       |
| PC4  | ADC1/2_IN14       |
| PC5  | ADC1/2_IN15       |
| PA4  | DAC_OUT1          |
| PA5  | DAC_OUT2          |
| PB8  | CAN1_RX           |
| PB9  | CAN1_TX           |
| PB5  | CAN2_RX           |
| PB6  | CAN2_TX           |
| PB11 | EMAC_RMII_TX_EN   |
| PB12 | EMAC_RMII_TX0     |
| PB13 | EMAC_RMII_TX1     |
| PD8  | EMAC_RMII_RX_DV   |
| PD9  | EMAC_RMII_RXD0    |
| PD10 | EMAC_RMII_RXD1    |
| PA1  | EMAC_RMII_REF_CLK |
| PF8  | QSPI1_IO0         |
| PF9  | QSPI1_IO1         |
| PF7  | QSPI1_IO2         |
| PF6  | QSPI1_IO3         |
| PF10 | QSPI1_SCK         |
| PG6  | QSPI1_CS          |
| PE7  | QSPI2_IO0         |
| PE8  | QSPI2_IO1         |
| PE9  | QSPI2_IO2         |
| PE10 | QSPI2_IO3         |
| PG13 | QSPI2_SCK         |
| PG8  | QSPI2_CS          |
| PA11 | USB1_DM           |
| PA12 | USB1_DP           |
| PB14 | USB2_DM           |
| PB15 | USB2_DP           |

## 使用说明

    本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

### 快速上手

本 BSP 为开发者提供 MDK4、MDK5 和 IAR 工程，并且支持 GCC 开发环境。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用数据线连接开发板到 PC，打开电源开关。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用AT-LINK SWD下载程序，在通过AT-LINK SWD连接开发板的基础上，点击下载按钮即可下载程序到开发板

#### 运行结果

下载程序成功之后，系统会自动运行，观察开发板上 LED 的运行效果，LED2/3/4 会周期性闪烁。

连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，在串口上可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     4.1.0 build Apr  7 2022
 2006 - 2022 Copyright by RT-Thread team
msh />
```

## 注意事项

AT32F437使用Ethernet且PHY时钟由CLKOUT(PA8)输出提供时，主频最好采用250Mhz。

可在雅特力官方网站进行所需资料下载，如Keil_v5/Keil_v4/IAR等pack安装包和AT-START开发板原理图等（www.arterytek.com）

## 联系人信息

维护人:

- [sheltonyu]