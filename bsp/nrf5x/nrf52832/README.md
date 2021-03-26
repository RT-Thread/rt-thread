# nRF52832-PCA10040 BSP说明

## 简介

该文件夹主要存放所有主芯片为nRF52832的板级支持包。目前默认支持的开发板是官方[PCA10040](https://www.nordicsemi.com/Software-and-tools/Development-Kits/nRF52-DK)
主要内容如下：

- 开发板资源介绍
- 进阶使用方法

## 开发板介绍

PCA10040-nRF52832是Nordic 官方的开发板，搭载nRF52832 芯片，基于ARM Cortex-M4内核，最高主频64 MHz，具有丰富的资源。

开发板外观如下图所示

![](../docs/images/nrf52832.jpg)

PCA10040-nrf52832开发板常用 **板载资源** 如下：

- MCU：NRF52832，主频 64MHz，512kB FLASH ，64kB RAM
- MCU 外设: GPIO, UART, SPI, I2C(TWI), RTC,TIMER,NFC,PWM,ADC
- 板载设
  - LED：4个 。
  - 按键：5个，4个USER and 1个RESET 。
- 常用接口：Arduino Uno 接口
- 调试接口：板载 J-LINK 调试器。

开发板更多详细信息请参考NORDIC官方[PCA10040](https://www.nordicsemi.com/Software-and-tools/Development-Kits/nRF52-DK)



## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设** | **支持情况** | **备注** |
| :----------- | :----------: | :------: |
| GPIO         |     支持     |  GPION   |
| UART         |     支持     |  UART0   |
| PWM          |     支持     |   支持   |
| SPI          |     支持     |   支持   |
| RTC          |     支持     |          |
| ADC          |     支持     |          |
|              |              |          |
|              |              |          |
|              |              |          |



### 进阶使用

此 BSP 默认只开启了 GPIO 和 串口 0 的功能，更多高级功能需要利用 env 工具对 BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=mdk4/mdk5/iar` 命令重新生成工程。


### VS Code开发支持

配置步骤：

1. 在命令行设置以下两个环境变量：

    ```bash
    export RTT_CC=gcc
    export RTT_EXEC_PATH=<工具链路径/bin>
    ```

2. 搜索插件`Cortex-debug`并安装。
3. 安装[nRF Command Line Tools](https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Command-Line-Tools)以支持`nrfjprog`命令。
4. 在.vscode/settings.json内配置工具链和`JlinkGDBServer`，sample：

    ```json
    {
        "cortex-debug.armToolchainPath": "/usr/local/gcc-arm-none-eabi-9-2019-q4-major/bin/",
        "cortex-debug.armToolchainPrefix": "arm-none-eabi",
        "cortex-debug.JLinkGDBServerPath": "/Applications/SEGGER/JLink/JLinkGDBServer"
    }
    ```

5. 点击`终端`->`运行任务`->`build`编译，点击`终端`->`运行任务`->`flash`烧录，点击左侧`debug`->`run`使用VS Code进行debug。

## 支持其他开发板

客户可以将自己的开发板的.config文件和board/Kconfig文件到board/$(board_name)下面添加README.md即可

## 注意事项

## 联系人信息

维护人:

-  