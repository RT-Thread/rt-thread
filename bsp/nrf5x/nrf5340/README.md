# nRF5340-PCA10095 BSP说明

## 简介

该文件夹主要存放所有主芯片为nRF5340的板级支持包。

目前支持的开发板如下

| 支持开发板型号                                               | 开发板上外设                | 备注                                |
| ------------------------------------------------------------ | --------------------------- | ----------------------------------- |
| [PCA10095](https://www.nordicsemi.com/Products/Development-hardware/nRF5340-DK) | QSPI FLASH, 4 button，4 LED | UART0                               |

|                                                              |                             |                                     |


选择开发板请使用`menuconfig` -> `Hardware Driver Config` -> `Select Bsp board`

选择对应的开发板

本文主要内容如下：

- 开发板资源介绍
- 进阶使用方法

## 开发板介绍

## 外设支持

本 BSP 目前对外设的支持情况如下：

| **片上外设** | **支持情况** |        **备注**        |
| :----------- | :----------: | :--------------------: |
| GPIO         |     支持     |         GPION          |
| UART         |     支持     |         UART0 请暂时使用1000000波特率|
| PWM          |     支持     |          支持          |
| SPI          |     支持     |          支持          |
| QSPI         |     支持     | 支持开发板上QSPI FLASH |
| RTC          |     支持     |                        |
| ADC          |     支持     |                        |
|              |              |                        |
|              |              |                        |
|              |              |                        |



### 进阶使用

此 BSP 默认只开启了 GPIO 和 串口 0 的功能，更多高级功能需要利用 env 工具对 BSP 进行配置，步骤如下：

1. 在 bsp 下打开 env 工具。

2. 输入`menuconfig`命令配置工程，配置好之后保存退出。

3. 输入`pkgs --update`命令更新软件包。

4. 输入`scons --target=mdk5` 命令重新生成工程。



## 支持其他开发板

客户可以将自己的开发板的.config文件和board/Kconfig文件到board/$(board_name)下面添加README.md即可，使用的时候替换.config文件

## 注意事项

## 联系人信息

维护人:

-  [Andrew], 邮箱：<andrew.li@nordicsemi.no>