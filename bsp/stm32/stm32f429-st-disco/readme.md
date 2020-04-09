# STM32F429-DISCO

## 1. 简介

STM32F429I-DISCOVERY 开发板使用高性能 MCU STM32F429，可以用于实现高级图形用户界面。  
本 BSP 兼容 STM32F429I-DISCO 和 STM32F429I-DISC1 两个版本的 DISCOVERY 开发板。

核心板板载主要资源如下：

| 硬件 | 描述 |
| -- | -- |
|芯片型号| STM32F429ZIT6 |
|CPU| ARM Cortex-M4F |
|主频| 180MHz |
|片内 SRAM| 256KB |
|片外 SDRAM| 64-Mbit SDRAM |
|片内 Flash| 2MB |
|显示设备| 2.4" QVGA TFT LCD|
|‎运动传感器‎| L3GD20 |
|LED| 6 个 |
|按键| 2 个 |

## 2. 编译说明

STM32F429-DISCO 板级包支持 MDK4﹑MDK5﹑IAR 开发环境和 GCC 编译器，以下是具体版本信息：

| IDE/编译器 | 已测试版本                   |
| ---------- | ---------------------------- |
| MDK4       | MDK4.74                      |
| MDK5       | MDK V5.25.2.0                |
| IAR        | 未测试                        |
| GCC        | GCC 5.4.1 20160919 (release) |

## 3. 烧写及执行

供电方式：使用 Mini USB 线连接电脑和板子的 USB ST-LINK 口。

串口连接：STM32F429I-DISC1 版本的开发板的板载调试器为 ST-LINK/V2-B，支持 VCP 虚拟串口，所以可以直接使用虚拟串口输出默认控制台设备 USART1。 

老版本的 STM32F429I-DISCO 开发板需要从板子上的引脚外接串口，并更改控制台设备到相应 USART。 

在PC上使用终端软件以115200-N-8-1的配置方式连接到对应的COM设备上。

STM32F429-DISCO/DISC1 使用板载编程器下载程序。

### 3.1 运行结果

如果编译 & 烧写无误，当复位设备后，会在串口上看到 RT-Thread 的启动 logo 信息：

```bash
 \ | /
- RT -     Thread Operating System
 / | \     3.1.0 build Aug 31 2018
 2006 - 2018 Copyright by rt-thread team
finsh />

```

## 4. 驱动支持情况及计划

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| USART | 支持 | USART1/2/3 |
| GPIO | 支持 |  |
| SPI |  |  |
| IIC |  |  |
| SDRAM |  | |
| LCD |  |  |
| 触摸屏 |  |  |
| USB OTG Host|  |  |
| USB OTG Device|  | |
| L3GD20 |  | |



## 5. 联系人信息

维护人：[xuzhuoyi](https://github.com/xuzhuoyi)

## 6. 参考

* [板子相关资料](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/mcu-eval-tools/stm32-mcu-eval-tools/stm32-mcu-discovery-kits/32f429idiscovery.html)
