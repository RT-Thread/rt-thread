# nRF5340-PCA10095 BSP说明

## 简介

该文件夹主要存放所有主芯片为nRF5340的板级支持包。

目前支持的开发板如下

| 支持开发板型号                                               | 开发板上外设                | 备注  |
| ------------------------------------------------------------ | --------------------------- | ----- |
| [NRF5340-DK-PCA10095](https://www.nordicsemi.com/Products/Development-hardware/nRF5340-DK) | QSPI FLASH, 4 button，4 LED | UART0 |
| [NRF7002-DK-PCA10143](https://www.nordicsemi.com/Products/Development-hardware/nRF7002-DK) | QSPI FLASH, 2LED, 2BUTTON   | UART0 |




选择开发板请使用`menuconfig` -> `Hardware Driver Config` -> `Select Bsp board`

选择对应的开发板

本文主要内容如下：

- 开发板资源介绍

PCA10095-nrf5340 开发板常用 **板载资源** 如下：

- MCU：NRF5340，双核， Arm® Cortex®-M33，DSP, ARMV8,应用核128M Hz， 网络核64MHz
- MCU 外设: GPIO, UART, SPI, I2C(TWI), RTC,TIMER,NFC,QSPI,PWM,ADC,USB
- 板载外设
  - LED：4个，P0.28(LED1), P0.29(LED2), P0.30 (LED3), P0.31(LED4) 。
  - 按键：5个，P0.23(SW1), P0.24(SW2), P0.08(SW3), P0.09(SW4)。BOOT/RESET(SW5)
  - FLASH: P0.13(QSPI0), P0.14(QSPI1), P0.15(QSPI2), P0.16(QSPI3), P0.17(QSPI_CLK), P0.18(QSPI_CS)  =》QSPI flash
  - USB:   1个
  - UART1: RXD(P1.00), TXD(P1.01), CTS(P0.10), RTS(P0.11)   => 连接的JLINK中的VCOM0
  - UART2: RXD(P0.22), TXD(P0.20), CTS(P0.21), RTS(P0.19)  => 连接的JLINK中的VCOM1
  - Segger RTT (RTT Console)
  - NFC: NFC1(P0.02), NFC2(P0.03)
- 常用接口：USB device、Arduino Uno 接口
- 调试接口：板载 J-LINK 调试器。

PCA10143-nrf7002 开发板常用 **板载资源** 如下：

- 板载设
  - LED：2个，LED1(P1.06), LED2(P1.07).

  - BUTTON: 2个， SW1(P1.08), SW2(P1.09)

  - UART1: RXD(P1.00), TXD(P1.01), CTS(P0.10), RTS(P0.11)   => 连接的JLINK中的VCOM0

  - UART2: RXD(P0.22), TXD(P0.20), CTS(P0.21), RTS(P0.19)  => 连接的JLINK中的VCOM1

  - SPI_HS: SCK(P0.08), MOSI(P0.09), MISO(P0.10), CS(P0.11)  => 连接MX25 QSPI FLASH

  - I2C: SDA(P1.02)   SCL(P1.03)

  - NRF7002 CTRL: BUCKEN(P0.12), IRQ(P0.23), GRANT(P0.24), REQ(P0.28), STATUS1(P0.29), STATUS0(P0.30)

  - NRF7002(QSPI): CS(P0.18), CLK(P0.17), QSPI0(P0.13), QSPI1(P0.14), QSPI2(P0.15), QSPI3(P0.16)

    

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
|  |              |                        |
| Segger_rtt | 支持 | 在Hardware Drivers Config → Onboard Peripheral Drirs中选中即可 |
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