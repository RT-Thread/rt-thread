# PHYTIUM BSP 说明

## 1. 简介

本文档为基于 RT-Thread 的 Phytium 系列 CPU 相关 BSP 说明。

本文的主要内容如下:

- BSP 简介
- 移植支持情况
- 如何在 Ubuntu/RT-Thread Env/RT-Thread Studio 环境下使用此 BSP
- 如何进行编译与实验
- 其他技术文档
- 维护人信息

### BSP简介

- 飞腾芯片产品具有谱系全、性能高、生态完善、自主化程度高等特点，目前主要包括高性能服务器 CPU（飞腾腾云S系列）、高效能桌面 CPU（飞腾腾锐D系列）、高端嵌入式 CPU（飞腾腾珑E系列）和飞腾套片四大系列，为从端到云的各型设备提供核心算力支撑。

- 本 BSP 目前支持飞腾派、飞腾腾珑E系列相关 CPU， 基于 Phytium-Standalone-SDK 进行开发。

- 本 BSP 支持 Phytium 系列 CPU 工作在 aarch32/aarch64 两种执行状态，开发者能够根据自己的应用场景灵活选择CPU工作状态。

## 2. 移植支持情况

| **片上外设**      | **支持情况** | **备注**                              |
| :-----------------| :----------: | :------------------------------------- |
| UART              |     支持     | UART1 打印输出 |
| [GPIO](./doc/drivers/gpio.md)              |     支持     | GPIO 引脚电平输入输出，中断 |
| XMAC              |     支持     | XMAC 网卡初始化和运行 |
| SDMMC             |     支持     | SD0/SD1 读写 SD 卡或 eMMC 颗粒 |
| PWM               |     支持     | PWM 脉宽调制电压输出        |
| CAN               |     支持     | CAN/CANFD设备通信 |
| I2C               |     支持     | I2C设备通信 |
| SPI               |     支持     | SPI设备通信 |
| DC                |     支持     | DC显示设备 |
| USB3(XHCI)        |     支持     | USB3(XHCI)设备支持|
| USB2(Host/Device) |     支持     | USB2(Host/Device)设备支持|

| **芯片**      | **支持情况** | **备注**                              |
| :----------------- | :----------: | :------------------------------------- |
| Phytium PI          |     支持     | 支持SMP |
| E2000D              |     支持     | 支持SMP |
| E2000Q              |     支持     | 支持SMP |

##  3. 如何在 Ubuntu, RT-Thread env, RT-Thread Studio 环境下使用此BSP

### Ubuntu 环境

1. 参考[RT-Thread/env](https://github.com/RT-Thread/env) 中 Tutorial 在ubuntu环境下安装env环境
2. 进入`aarch32`或`aarch64`目录
3. 按照指导安装 [aarch32](./aarch32/README.md)或[aarch64](./aarch64/README.md)编译链，并进行相关配置
4. 按照指导[启动镜像程序](./doc/how_to_flashed_binary.md)

### RT-Thread env 环境

1. 进入RT-Thread官网，[下载RT-Thread env工具](https://www.rt-thread.org/download.html)，在开发路径下解压缩即可
2. 启动 RT-Thread env 应用程序，在交互界面可以使用`cd`指令进入`aarch32`或`aarch64`目录
3. 按照指导安装 [aarch32](./aarch32/README.md)或[aarch64](./aarch64/README.md)编译链，并进行相关配置
4. 按照指导[启动镜像程序](./doc/how_to_flashed_binary.md)
5. 参考[使用文件系统](./doc/how_to_use_file_system.md)制作和使用文件系统

### RT-Thread Studio 环境

1. 请阅读[Phytium Rt-thread Studio指导手册](./doc/how_to_use_rtthread_studio.md)，进行环境搭建

## 4. 如何添加开发板

>注:BSP已适配E2000Q_DEMO，E2000D_DEMO，PHYTIUMPI开发板，若需填加系列其他开发板，请按以下步骤进行

- 请[阅读文档](./doc/how_to_add_cus_board.md)，按照指导添加自定义开发板

## 5. 其他技术文档

- [如何使用Cherryusb](./doc/use_cherryusb.md)

- [基于飞腾BSP开发lvgl应用程序](./doc/use_phytium_dc_with_lvgl.md)

- [Phytium_PI上开发和固化RT-Thread程序](./doc/use_phytium_pi_sd_image.md)，解决Phytium PI上使用RT-Thread读写操作影响 SD 卡的固件问题

- [C++支持](./doc/cpp_support.md)

## 6. 维护人信息

- huanghe:  huanghe@phytium.com.cn
- zhugengyu:  zhugengyu@phytium.com.cn
