# TMS320F28379D


## 1. 简介

TMS320F28379D BSP 基于 C2000 Delfino MCU F28379D LaunchPad 开发套件开发。   
TMS320F28379D 是一款功能强大的 32 位浮点微控制器单元 (MCU)，针对高级闭环控制应用而设计，例如工业驱动器和伺服电机控制、太阳能逆变器和转换器、数字电源、电力输送以及电力线通信。包括如下硬件特性：

| 硬件 | 描述 |
| -- | -- |
|芯片型号| TMS320F28379D |
|多核 CPU| 两个 TMS320C28x 32 位 CPU
|| 两个可编程控制律加速器 (CLA) |
|主频| 200MHz |
|CLA 频率| 200MHz |
|总处理能力| 800MIPS |
|片内SRAM| 204kB |
|片内Flash| 1MB |

## 2. 编译说明

编译使用 Code Composer Studio，在 Code Composer Studio 8.1.0 使用 TI v18.1.3.LTS 编译器已测试编译通过。

## 3. 烧写及执行

连接开发板电源后，使用 CCS 中的烧写功能可直接通过板载 XDS100v2 仿真器烧写并执行。

## 4. 驱动支持情况及计划

| 驱动 | 支持情况  |  备注  |
| ------ | ----  | :------:  |
| CPU Timer | 支持 |  |
| GPIO | 支持 | |
| SCI | 开发中 | SCIA/B，预计2018年9月底实现 |
| ePWM | | 预计2019年10月支持 |
| ADC | | 预计2019年10月支持 |
| DAC | | 预计2019/Q4支持|
| I2C | | |
| SPI | | |
| CAN | | |
| eCAP | | |

## 5. 联系人信息

维护人：xuzhuoyi < xzy476386434@vip.qq.com >

## 6. 参考

* [C2000 Delfino MCU F28379D LaunchPad 开发套件][1]
* TMS320F28379D [相关技术文档][2]

  [1]: http://www.ti.com.cn/tool/cn/launchxl-f28379d
  [2]: http://www.ti.com.cn/product/cn/tms320f28379d/technicaldocuments
