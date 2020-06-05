# N32G45X-STB

## 1. 简介

N32G45X-STB 系列开发板是国民技术提供的开发板，使用 N32G45X 系列芯片（包括 N32G452 / 455 / 457 / FR 指纹/ WB 蓝牙）作为主控制器。提供包括扩展引脚在内的及 SWD、Reset、Boot、User button key、LED、CAN、I2C、I2S、USART、RTC、LCD、SPI、ADC、DAC、XFMC、SDIO、USB、ETH、硬件加密、运放等外设资源。

板载主要资源如下：

| 硬件 | 描述 |
| -- | -- |
|CPU| Cortex-M4|
|主频| 144MHz |
|SRAM| 144KB |
|Flash| 512KB |

## 2. 编译说明

N32G45X-STB 板级包支持 MDK5 编译环境，以下是具体版本信息： 

| IDE/编译器 | 已测试版本 |
| -- | -- |
| MDK5 | MDK5.25 |

## 3. 烧写及执行

供电方式：开发板使用 Mini USB 接口。

下载程序：下载程序到开发板需要一套 JLink 或者使用板载 NS-Link 工具。

### 3.1 配置和仿真

工程已经默认使能了 RT-Thread UART 驱动、GPIO 驱动。

### 3.2 运行结果

打开 MDK 或者 IAR 工程，进入仿真后全速运行，将会在串口 0 上看到 RT-Thread 的启动 logo 信息：

```
 \ | /
- RT -     Thread Operating System
 / | \     4.0.3 build Jun  5 2020
 2006 - 2020 C
opyright by rt-thread team
msh />
```
## 4. 驱动支持情况及计划

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| UART | 支持 | UART0/1/2/3/4 |
| GPIO | 支持 |  |


### 4.1 IO在板级支持包中的映射情况

| IO 号 | 板级包中的定义 |
| -- | -- |
| PA9 | USART0 TX |
| PA10 | USART0 RX |
| PA2 | USART1 TX |
| PA3 | USART1 RX |

## 5. 联系人信息

维护人：

- [fengyeyu123](https://github.com/fengyeyu123)

## 6. 参考
