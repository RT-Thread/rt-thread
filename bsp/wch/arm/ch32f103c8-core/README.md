# ch32f103c8 BSP 说明
## 简介
| 硬件      | 描述          |
| --------- | ------------- |
| 芯片型号  | ch32f103c8    |
| CPU       | ARM Cortex M3 |
| 主频      | 72M           |
| 片内SRAM  | 20K           |
| 片内FLASH | 64K           |

## 编译说明

板级包支持MDK5开发环境，以下是具体版本信息：

| IDE/编译器 | 已测试版本                   |
| ---------- | ---------------------------- |
| MDK5       | MDK534                       |




## 外设支持

本 BSP 目前对外设驱动的支持情况如下：

| 驱动      | 支持情况 |            备注            |
| --------- | -------- | :------------------------:|
| UART      | 支持     | USART1/2/3                 |
| GPIO      | 支持     | PA0...PD2                  |
| IIC       | 支持     | 硬件I2C(7位)                |
| SPI       | 支持     | SPI1/2                     |
| WDT       | 支持     | IWDG                       |
| RTC       | 支持     | 外部或内部低速晶振           |


### IO在板级支持包中的映射情况

| IO号 | 板级包中的定义 |
| ---- | -------------- |
| PA9  | USART1_TX      |
| PA10 | USART1_RX      |
| PA2  | USART2_TX      |
| PA3  | USART2_RX      |
| PC10 | USART3_TX      |
| PC11 | USART3_RX      |
| PA4  | SPI1_CS        |
| PA5  | SPI1_SCK       |
| PA6  | SPI1_MISO      |
| PA7  | SPI1_MOSI      |
| PB12 | SPI2_CS        |
| PB13 | SPI2_SCK       |
| PB14 | SPI2_MISO      |
| PB15 | SPI2_MOSI      |
| PB8  | I2C1_SCL       |
| PB9  | I2C1_SDA       |
| PB10  | I2C2_SCL      |
| PB11  | I2C2_SDA      |


## 使用说明

    本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

### 快速上手

本 BSP 为开发者提供 MDK5 工程。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用数据线连接开发板到 PC，打开电源开关。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 SWD 下载程序，在通过 wch-link或公版daplink 连接开发板的基础上，点击下载按钮即可下载程序到开发板

#### 运行结果


连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，在串口上可以看到 RT-Thread 的输出信息:

```bash
 \ | /
- RT -     Thread Operating System
 / | \     4.0.4 build Aug 30 2021
 2006 - 2021 Copyright by rt-thread team
msh >
```

## 联系人信息

维护人:

- [charlown](https://github.com/charlown) 