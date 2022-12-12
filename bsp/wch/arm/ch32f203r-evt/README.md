# ch32f203r-evt BSP 说明
## 简介
| 硬件      | 描述          |
| --------- | ------------- |
| 芯片型号  | ch32f203rc    |
| CPU       | ARM Cortex M3 |
| 主频      | 144M           |
| 片内SRAM  | 64K           |
| 片内FLASH | 256K           |

## 编译说明

板级包支持MDK5开发环境，以下是具体版本信息：

| IDE/编译器 | 已测试版本                   |
| ---------- | ---------------------------- |
| MDK5       | MDK534                       |




## 外设支持

本 BSP 目前对外设驱动的支持情况如下：

| 驱动      | 支持情况 |            备注            |
| --------- | -------- | :------------------------:|
| UART      | 支持     | USART 1~8       |
| GPIO      | 支持     | PA0...PE15                  |
| IIC       | 支持     | 硬件I2C(7位)                |
| SPI       | 支持     | SPI 1~3                    |
| WDT       | 支持     | IWDG                       |
| RTC       | 支持     | 外部或内部低速晶振           |
| HWTIMER   | 支持     |定时器 1~10                   |
| PWM       | 支持     |定时器 1~5, 8~10(每个定时器包括4个通道)      |


### IO在板级支持包中的映射情况

| IO号 | 板级包中的定义 |
| ---- | -------------- |
| PA9(默认与板载wch-link串口相连)  | USART1_TX      |
| PA10(默认与板载wch-link串口相连) | USART1_RX      |



## 使用说明

    本章节是为刚接触 RT-Thread 的新手准备的使用说明，遵循简单的步骤即可将 RT-Thread 操作系统运行在该开发板上，看到实验效果 。

### 快速上手

本 BSP 为开发者提供 MDK5 工程。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用数据线连接板载wch-link到 PC，打开电源开关。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 SWD （板载wch-link, CMSIS-DAP Debugger）下载程序，下载算法修改为start:0x20000000，size:0x00002800，
点击下载按钮即可下载程序到开发板

#### 运行结果


在终端工具里打开板载wch-link串口（WCHDapLink SERIAL，默认115200-8-1-N），复位设备后，在串口上可以看到 RT-Thread 的输出信息:

```bash

 \ | /
- RT -     Thread Operating System
 / | \     4.0.4 build Jan 21 2022
 2006 - 2021 Copyright by rt-thread team
msh >
```

## 联系人信息

维护人:

- [charlown](https://github.com/charlown)
