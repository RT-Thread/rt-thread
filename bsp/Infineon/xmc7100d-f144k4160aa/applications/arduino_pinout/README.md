# board_default 开发板的Arduino生态兼容说明

## 1 RTduino - RT-Thread的Arduino生态兼容层

board_default 开发板已经完整适配了[RTduino软件包](https://github.com/RTduino/RTduino)，即RT-Thread的Arduino生态兼容层。用户可以按照Arduino的编程习惯来操作该BSP，并且可以使用大量Arduino社区丰富的库，是对RT-Thread生态的极大增强。更多信息，请参见[RTduino软件包说明文档](https://github.com/RTduino/RTduino)。

### 1.1 如何开启针对本BSP的Arduino生态兼容层

Env 工具下敲入 menuconfig 命令，或者 RT-Thread Studio IDE 下选择 RT-Thread Settings：

```Kconfig
Hardware Drivers Config --->
    Onboard Peripheral Drivers --->
        [*] Compatible with Arduino Ecosystem (RTduino)
```

## 2 Arduino引脚排布

更多引脚布局相关信息参见 [pins_arduino.c](pins_arduino.c) 和 [pins_arduino.h](pins_arduino.h)。

| Arduino引脚编号  | STM32引脚编号 | 5V容忍 | 备注  |
| ------------------- | --------- | ---- | ------------------------------------------------------------------------- |
| 0 (D0) | BSP_IO_PORT_06_PIN_04 | 否 | Serial-RX,默认被RT-Thread的UART设备框架uart6接管 |
| 1 (D1) | BSP_IO_PORT_06_PIN_05 | 否 | Serial-TX,默认被RT-Thread的UART设备框架uart6接管 |
| 2 (D2) | BSP_IO_PORT_05_PIN_00 | 否 |  |
| 3 (D3) | BSP_IO_PORT_05_PIN_01 | 否 | PWM0-CH0,默认被RT-Thread的PWM设备框架pwm0接管 |
| 4 (D4) | BSP_IO_PORT_11_PIN_02 | 否 |  |
| 5 (D5) | BSP_IO_PORT_11_PIN_03 | 否 | PWM0-CH0,默认被RT-Thread的PWM设备框架pwm0接管 |
| 6 (D6) | BSP_IO_PORT_11_PIN_04 | 否 | PWM0-CH0,默认被RT-Thread的PWM设备框架pwm0接管 |
| 7 (D7) | BSP_IO_PORT_11_PIN_05 | 否 |  |
| 8 (D8) | BSP_IO_PORT_11_PIN_06 | 否 |  |
| 9 (D9) | BSP_IO_PORT_05_PIN_07 | 否 | PWM0-CH0,默认被RT-Thread的PWM设备框架pwm0接管 |
| 10 (D10) | BSP_IO_PORT_00_PIN_05 | 否 |  |
| 11 (D11) | BSP_IO_PORT_00_PIN_02 | 否 | SPI0-MOSI,默认被RT-Thread的SPI设备框架spi0接管 |
| 12 (D12) | BSP_IO_PORT_00_PIN_03 | 否 | SPI0-MISO,默认被RT-Thread的SPI设备框架spi0接管 |
| 13 (D13) | BSP_IO_PORT_00_PIN_04 | 否 | SPI0-SCK,默认被RT-Thread的SPI设备框架spi0接管 |
| 14 (D14) | BSP_IO_PORT_08_PIN_01 | 否 | I2C0-SDA,默认被RT-Thread的I2C设备框架i2c0接管 |
| 15 (D15) | BSP_IO_PORT_08_PIN_00 | 否 | I2C0-SCL,默认被RT-Thread的I2C设备框架i2c0接管 |

> 注意：
>
> 1. xxxxxxxxx
> 2. xxxxxxxxx
