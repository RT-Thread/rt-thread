# xmc7100d-f144k4160aa 开发板的Arduino生态兼容说明

## 1 RTduino - RT-Thread的Arduino生态兼容层

xmc7100d-f144k4160aa 开发板已经完整适配了[RTduino软件包](https://github.com/RTduino/RTduino)，即RT-Thread的Arduino生态兼容层。用户可以按照Arduino的编程习惯来操作该BSP，并且可以使用大量Arduino社区丰富的库，是对RT-Thread生态的极大增强。更多信息，请参见[RTduino软件包说明文档](https://github.com/RTduino/RTduino)。

### 1.1 如何开启针对本BSP的Arduino生态兼容层

Env 工具下敲入 menuconfig 命令，或者 RT-Thread Studio IDE 下选择 RT-Thread Settings：

```Kconfig
Hardware Drivers Config --->
    Onboard Peripheral Drivers --->
        [*] Compatible with Arduino Ecosystem (RTduino)
```

## 2 Arduino引脚排布

更多引脚布局相关信息参见 [pins_arduino.c](pins_arduino.c) 和 [pins_arduino.h](pins_arduino.h)。

| Arduino引脚编号  | XMC7100引脚编号 | 5V容忍 | 备注  |
| ------------------- | --------- | ---- | ------------------------------------------------------------------------- |
| 0 (D0) | BSP_IO_PORT_19_PIN_00 | 否 | Serial2-RX,默认被RT-Thread的UART设备框架uart2接管 |
| 1 (D1) | BSP_IO_PORT_19_PIN_01 | 否 | Serial2-TX,默认被RT-Thread的UART设备框架uart2接管 |
| 2 (D2) | BSP_IO_PORT_00_PIN_03 | 否 | SPI0-CS |
| 3 (D3) | BSP_IO_PORT_01_PIN_01 | 否 | SPI0-MOSI,默认被RT-Thread的SPI设备框架spi0接管 |
| 4 (D4) | BSP_IO_PORT_01_PIN_00 | 否 | SPI0-MISO,默认被RT-Thread的SPI设备框架spi0接管 |
| 5 (D5) | BSP_IO_PORT_00_PIN_02 | 否 | SPI0-SCK,默认被RT-Thread的SPI设备框架spi0接管 |
| 6 (D6) | BSP_IO_PORT_00_PIN_00 | 否 | I2C2-SDA,默认被RT-Thread的I2C设备框架i2c2接管 |
| 7 (D7) | BSP_IO_PORT_00_PIN_01 | 否 | I2C2-SCL,默认被RT-Thread的I2C设备框架i2c2接管 |

> 注意：
>
> 1. BMP280和SSD1306不能同时开启，会导致BMP280无法获取数据
> 2. SSD1306的地址需要改成0x3D
> 3. 需要去掉HardwareSerial::begin(uint32_t baud, uint8_t config) 和HardwareSerial::begin(uint32_t baud)函数内的代码
> 4. 部分引脚默认被RT-Thread的设备框架（如UART、SPI、I2C）接管，使用时请注意资源冲突。
