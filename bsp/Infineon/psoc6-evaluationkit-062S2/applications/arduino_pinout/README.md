# psoc6-evaluationkit-062S2 开发板的Arduino生态兼容说明

## 1 RTduino - RT-Thread的Arduino生态兼容层

psoc6-evaluationkit-062S2 开发板已经完整适配了[RTduino软件包](https://github.com/RTduino/RTduino)，即RT-Thread的Arduino生态兼容层。用户可以按照Arduino的编程习惯来操作该BSP，并且可以使用大量Arduino社区丰富的库，是对RT-Thread生态的极大增强。更多信息，请参见[RTduino软件包说明文档](https://github.com/RTduino/RTduino)。

### 1.1 如何开启针对本BSP的Arduino生态兼容层

Env 工具下敲入 menuconfig 命令，或者 RT-Thread Studio IDE 下选择 RT-Thread Settings：

```Kconfig
Hardware Drivers Config --->
    Onboard Peripheral Drivers --->
        [*] Compatible with Arduino Ecosystem (RTduino)
```

## 2 Arduino引脚排布

更多引脚布局相关信息参见 [pins_arduino.c](pins_arduino.c) 和 [pins_arduino.h](pins_arduino.h)。

| Arduino引脚编号  | 引脚编号 | 5V容忍 | 备注  |
| ------------------- | --------- | ---- | ------------------------------------------------------------------------- |
| 0 (D0) | P80 | 是/否 | I2C4-SCL，默认被RT-Thread的I2C设备框架i2c4接管 |
| 1 (D1) | P81 | 是/否 | I2C4-SDA，默认被RT-Thread的I2C设备框架i2c4接管 |
| 2 (D2) | P04 | 是/否 | SPI0-SCK，默认被RT-Thread的SPI设备框架spi0接管 |
| 3 (D3) | P03 | 是/否 | SPI0-MISO，默认被RT-Thread的SPI设备框架spi0接管 |
| 4 (D4) | P02 | 是/否 | SPI0-MOSI，默认被RT-Thread的SPI设备框架spi0接管 |
| 5 (D5) | P05 | 是/否 | SPI片选默认引脚 |
| 6 (D6) | P57 | 是/否 | PWM0-CH7，默认被RT-Thread的PWM设备框架pwm0接管 |
| 7 (D7) | P56 | 是/否 | PWM1-CH7，默认被RT-Thread的PWM设备框架pwm1接管 |
| 8 (D8) | P1,5 | 是/否 | PWM1-CH3，默认被RT-Thread的PWM设备框架pwm1接管 |
| 9 (D9) | P1,4 | 是/否 | PWM1-CH1，默认被RT-Thread的PWM设备框架pwm1接管 |
| 10 (D10) | P1,3 | 是/否 | PWM1-CH2，默认被RT-Thread的PWM设备框架pwm1接管 |
| 11 (D11) | P1,2 | 是/否 | PWM0-CH2，默认被RT-Thread的PWM设备框架pwm0接管 |
| 12 (D12) | P51 | 是/否 | PWM1-CH4，默认被RT-Thread的PWM设备框架pwm1接管 |
| 13 (D13) | P50 | 是/否 | PWM0-CH4，默认被RT-Thread的PWM设备框架pwm0接管 |
| 14 (D14) | P1,1 | 是/否 | Serial2-TX，默认被RT-Thread的UART设备框架uart5接管 |
| 15 (D15) | P1,0 | 是/否 | Serial2-RX，默认被RT-Thread的UART设备框架uart5接管 |
