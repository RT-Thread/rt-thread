# STM32F407 -develop说明

## 简介

用于搭建stm32F407vet6系统，学习STM32及相关功能接口开放。

## 调试

    #define DBG_TAG     "MAIN"
    #define DBG_LVL     DBG_
    DBG_ERROR
    DBG_WARNING
    DBG_INFO
    DBG_LOG
    #include <rtdbg.h>
    // LOG_D("LOG_D(%d): RT-Thread is an open source IoT operating system from China.", count);
    // LOG_I("LOG_I(%d): RT-Thread is an open source IoT operating system from China.", count);
    // LOG_W("LOG_W(%d): RT-Thread is an open source IoT operating system from China.", count);
    // LOG_E("LOG_E(%d): RT-Thread is an open source IoT operating system from China.", count);
    // ulog_d("test", "ulog_d(%d): RT-Thread is an open source IoT operating system from China.", count);
    // ulog_i("test", "ulog_i(%d): RT-Thread is an open source IoT operating system from China.", count);
    // ulog_w("test", "ulog_w(%d): RT-Thread is an open source IoT operating system from China.", count);
    // ulog_e("test", "ulog_e(%d): RT-Thread is an open source IoT operating system from China.", count);
    

## 功能

* 输出编译版本号



## 开发板介绍



该开发板常用 **板载资源** 如下：

- MCU：STM32F407ZGT6，主频 168MHz，512KB FLASH ，192KB RAM
- 外部 RAM：IS62WV51216（1MB）
- 外部 FLASH：W25Q128（SPI，16MB）
- 常用外设
  - LED：2个，DS0（红色，PB1），DS1（绿色，PB0）
  - 按键，4个，KEY_UP（兼具唤醒功能，PIN：0），K0（PIN：68），K1（PIN：67），K2（PIN：66）
- 常用接口：USB 转串口、SD 卡接口、以太网接口、LCD 接口、USB SLAVE、USB HOST
- 调试接口，标准 JTAG/SWD

开发板更多详细信息请参考正点原子 [STM32 探索者开发板介绍](https://eboard.taobao.com/index.htm)。

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **板载外设** | **支持情况** |               **备注**                |
| :------------ | :----------: | :-----------------------------------: |
| USB 转串口     |     支持     |                                    |
| COM2         |   支持  | 和以太网、PWM 冲突，如需使用该外设，请使用 CubeMX 重新配置 UART2 管脚 |
| COM3         |  支持   |                                           |
| MPU6050      |     支持     |                                       |
| Flash        |   支持   |                               |
| SRAM         |   支持   |                               |
| SD卡         |   支持   |                               |
| 以太网       |   支持   |                               |
| WM8978       |   暂不支持   |                                       |
| **片上外设** | **支持情况** |               **备注**                |
| GPIO         |     支持     | PA0, PA1... PH1 ---> PIN: 0, 1...144 |
| UART         |     支持     |              UART1/2/3              |
| SPI          |     支持     |               SPI1/2/3                |
| I2C          |     支持     |               软件 I2C                |
| ADC          |     支持     |                                       |
| RTC          |     支持     | 支持外部晶振和内部低速时钟 |
| WDT          |     支持     |                                       |
| FLASH | 支持 | 已适配 [FAL](https://github.com/RT-Thread-packages/fal) |
| PWM          |   支持   |                               |
| USB Device   |   支持   |                               |
| USB Host     |   支持   |                               |
| **扩展模块** | **支持情况** |               **备注**                |
| ATK-ESP8266 模块 | 暂不支持 | 即将支持 |


## 使用说明

- 


### 快速上手

本 BSP 为开发者提供 MDK4、MDK5 和 IAR 工程，并且支持 GCC 开发环境。下面以 MDK5 开发环境为例，介绍如何将系统运行起来。

#### 硬件连接

使用数据线连接开发板到 PC，打开电源开关。

#### 编译下载

双击 project.uvprojx 文件，打开 MDK5 工程，编译并下载程序到开发板。

> 工程默认配置使用 JLink 下载程序，在通过 JLink 连接开发板的基础上，点击下载按钮即可下载程序到开发板

#### 运行结果

> 

```bash

```
### 进阶使用



## 注意事项



## 联系人信息

维护人:

- ericyinwork@163.com