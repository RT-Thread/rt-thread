# TM4C129X-Development Board
http://www.ti.com/tool/dk-tm4c129x

## 1. 简介

TM4C129X-DK是TI官方的开发板，此为其中一款开发板，带屏幕，配置更高。
TI官方提供了详细的SDK支持，含USB，LWIP，甚至图形库。

核心板板载主要资源如下：

| 硬件 | 描述 |
| -- | -- |
|芯片型号| TM4C129XNCZAD |
|CPU| ARM Cortex-M4F |
|主频| 120MHz |
|片内Flash| 1024B |
|片内SRAM| 256KB |


## 2. 编译说明

TM4C129X-DK板级包目前仅支持MDK5编译器，以下是具体版本信息：

| IDE/编译器 | 已测试版本                   |
| ---------- | ---------------------------- |
| MDK5       | MDK521a                      |


## 3. 烧写及执行

TM4C129X-DK本身提供了一个烧录接口，是Stellaris ICDI，keil本身不提供该驱动，需自行下载。
http://www.ti.com.cn/tool/cn/stellaris_icdi_drivers

供电方式：使用ICDI接口即可供电

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

### 4.1 IO在板级支持包中的映射情况

| IO号 | 板级包中的定义 |
| -- | -- |

## 5. 联系人信息

维护人：[zero](https://github.com/Zero-Sky)

## 6. 参考


