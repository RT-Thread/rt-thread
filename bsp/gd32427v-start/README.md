# GD32F427V-START

## 简介

GD32427V-START是-兆易创新推出的一款GD32F427系列的评估板，板载资源主要如下：

| 硬件      | 描述          |
| --------- | ------------- |
| 芯片型号  | GD32F427VKT6  |
| CPU       | ARM Cortex M4 |
| 主频      | 240M          |
| 片内SRAM  | 256K          |
| 片内FLASH | 3072K         |


## 烧写及执行

供电方式：开发板使用 Mini USB 接口提供 5V 电源。

下载程序：开发板自带 GD-Link 。

串口连接：使用USB转TTL模块连接PB6(MCU TX)和PB7(MCU RX)。

### 运行结果

如果编译 & 烧写无误，当复位设备后，会在串口上看到RT-Thread的启动logo信息：

```bash
 \ | /
- RT -     Thread Operating System
 / | \     5.0.0 build Nov 20 2022 18:09:16
 2006 - 2022 Copyright by RT-Thread team
msh >

```
## 驱动支持情况及计划

| 驱动      | 支持情况 |            备注            |
| --------- | -------- | :------------------------: |
| UART      | 支持     |          UART0~7           |
| GPIO      | 未支持   |                            |
| IIC       | 未支持   |                            |
| SPI       | 支持     |           SPI0~5           |


### IO在板级支持包中的映射情况

| IO号 | 板级包中的定义 |
| ---- | -------------- |
| PC6  | LED2           |


## 联系人信息

维护人：[dozingfiretruck](https://github.com/dozingfiretruck)
