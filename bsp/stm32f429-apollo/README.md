# STM32F429-APOLLO

## 1. 简介

STM32F429-APOLLO是广州市星翼电子科技有限公司推出的一款开发板。

核心板板载主要资源如下：

| 硬件 | 描述 |
| -- | -- |
|芯片型号| STM32F429IGT6 |
|CPU| ARM Cortex-M4 |
|主频| 180MHz |
|片内SRAM| 256KB |
|片外SRAM| 32MB |
|片内Flash| 1MB |

## 2. 编译说明

STM32F429-APOLLO板级包支持MDK4﹑MDK5﹑IAR开发环境和GCC编译器，以下是具体版本信息：

| IDE/编译器 | 已测试版本                   |
| ---------- | ---------------------------- |
| MDK4       | MDK4.74                      |
| MDK5       | MDK524a                      |
| IAR        | IAR 7.60~IAR8.20             |
| GCC        | GCC 5.4.1 20160919 (release) |

## 3. 烧写及执行

供电方式：使用USB线连接电脑和板子的USB_232 USB口。在使用比较大负载的外设（例如4.3寸或更大的屏），建议使用独立电源接在DC_IN供电。

串口连接：短接RXD和PA9，短接TXD和PA10，在PC上使用终端软件以115200-N-8-1的配置方式连接到对应的COM设备上。

STM32F429-APOLLO有JTAG/SWD接口，可以使用JLink/STLINK/ULINK等仿真器下载程序。

### 3.1 运行结果

如果编译 & 烧写无误，当复位设备后，会在串口上看到RT-Thread的启动logo信息：

```bash
 \ | /
- RT -     Thread Operating System
 / | \     3.0.3 build Feb 28 2018
 2006 - 2018 Copyright by rt-thread team
finsh />

```

## 4. 驱动支持情况及计划

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | UART0/1 |
| GPIO | 未支持 |  |
| IIC | 支持 | 仅仅支持GPIO模拟方式 |
| SPI | 支持 |  |
| ETH | 支持 |  |
| LCD | 支持 | 支持FrameBuffer模式LCD显示 |
| RTC | 支持 |  |
| SDIO | 支持 |  |
| SDRAM | 支持 | |
| SPI FLASH | 支持 | |

### 4.1 IO在板级支持包中的映射情况

| IO号 | 板级包中的定义 |
| -- | -- |
| PB1 | LED0 |
| PB0 | LED1 |
| PH3 | KEY0 |
| PH2 | KEY1 |
| PC13 | KEY2 |

## 5. 联系人信息

维护人：[tanek](https://github.com/TanekLiang)

## 6. 参考

* [板子相关资料](http://www.openedv.com/thread-13912-1-1.html)：
  * STM32F429开发指南-HAL库版本_V1.1.pdf 
  * STM32F429开发指南-寄存器版本_V1.1
* [芯片相关文档](http://www.st.com/content/st_com/en/products/microcontrollers/stm32-32-bit-arm-cortex-mcus/stm32-high-performance-mcus/stm32f4-series/stm32f429-439/stm32f429ig.html)

