# BL706 IOT 开发板 BSP 说明

## 简介

BL706 是一款 BLE + Zigbee 组合的芯片组，用于低功耗物联网应用开发。无线子系统包含 2.4G 无线电，BLE5.0 和 802.15.4 基带/MAC 设计。微控制器子系统包含一个低功耗的 32 位 RISC CPU，高速缓存和存储器。电源管理单元控制低功耗模式。此外，还支持各种安全性能。外围接口包括 USB2.0，以太网，红外遥控器，SPI，UART，ISO 17987，I2C，I2S，PWM，QDEC，KeyScan，ADC，DAC，PIR 和 GPIO。

板载主要资源如下：

| 硬件      | 描述          |
| --------- | -------------|
| 芯片型号  | BL706         |
| CPU       | rv32imafc    |
| 主频      | 144M          |
| 片内SRAM  | 132K          |
| 片内FLASH | 1024K         |

## 编译说明

BL706 IOT 开发板支持CDK、 GCC编译器，以下是具体版本信息：

| IDE/编译器 | 已测试版本                   |
| ---------- | ---------------------------- |
| GCC        | GCC 10.2.0 20210819 (release) |

## 外设支持

## 使用说明

编译BL706，需要有 RT-Thread 的代码，因为 BL706 的 sdk 是以软件包方式，所以需要在 bsp/bouffalolab 下做软件包更新。Windows 下推荐使用 env 工具，然后在 console 下进入 bsp/bouffalolab 目录中，运行：

    cd bsp/bouffalolab
    pkgs --update

下载risc-v的工具链，[下载地址](https://gitee.com/bouffalolab/toolchain_gcc_sifive_windows)

更新完软件包后，在`rtconfig.py`中将risc-v工具链的本地路径加入到 **EXEC_PATH** 参数。

### 代码烧录

- 见 [bl_dev_cube](http://bouffalolab.gitee.io/bl_mcu_sdk/get_started/bl_dev_cube.html)

### 实验现象

连接开发板对应串口到 PC , 在终端工具里打开相应的串口（115200-8-1-N），复位设备后，在串口上可以看到 RT-Thread 的输出信息:

```
 \ | /
- RT -     Thread Operating System
 / | \     4.0.4 build Sep 28 2021
 2006 - 2021 Copyright by rt-thread team
Hello, world
```

## 联系人信息

维护人：

- [sakumisu](https://github.com/sakumisu)

## 参考

* [BL_MCU_SDK](https://gitee.com/bouffalolab/bl_mcu_sdk)
