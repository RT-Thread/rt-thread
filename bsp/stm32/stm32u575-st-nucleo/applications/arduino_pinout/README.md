# xxx 开发板的Arduino生态兼容说明

## 1 RTduino - RT-Thread的Arduino生态兼容层

xxx 开发板已经完整适配了[RTduino软件包](https://github.com/RTduino/RTduino)，即RT-Thread的Arduino生态兼容层。用户可以按照Arduino的编程习惯来操作该BSP，并且可以使用大量Arduino社区丰富的库，是对RT-Thread生态的极大增强。更多信息，请参见[RTduino软件包说明文档](https://github.com/RTduino/RTduino)。

### 1.1 如何开启针对本BSP的Arduino生态兼容层

Env 工具下敲入 menuconfig 命令，或者 RT-Thread Studio IDE 下选择 RT-Thread Settings：

```Kconfig
Hardware Drivers Config --->
    Onboard Peripheral Drivers --->
        [*] Compatible with Arduino Ecosystem (RTduino)
```

## 2 Arduino引脚排布

更多引脚布局相关信息参见 [pins_arduino.c](pins_arduino.c) 和 [pins_arduino.h](pins_arduino.h)。

![xxx-pinout](xxx-pinout.jpg)
| Arduino引脚编号  | STM32引脚编号 | 5V容忍 | 备注  |
| ------------------- | --------- | ---- | ------------------------------------------------------------------------- |
| 0 (D0) | PG8 | 是/否 | Serial-RX，默认被RT-Thread的UART设备框架uart1接管 |
| 1 (D1) | PG7 | 是/否 | Serial-TX，默认被RT-Thread的UART设备框架uart1接管 |
| 2 (D2) | PF15 | 是/否 |  |
| 3 (D3) | PE13 | 是/否 | PWM1-CH3，默认被RT-Thread的PWM设备框架pwm1接管 |
| 4 (D4) | PF14 | 是/否 |  |
| 5 (D5) | PE11 | 是/否 | PWM1-CH2，默认被RT-Thread的PWM设备框架pwm1接管 |
| 6 (D6) | PE9 | 是/否 | PWM1-CH1，默认被RT-Thread的PWM设备框架pwm1接管 |
| 7 (D7) | PF13 | 是/否 |  |
| 8 (D8) | PF12 | 是/否 |  |
| 9 (D9) | PD15 | 是/否 | PWM4-CH4，默认被RT-Thread的PWM设备框架pwm4接管 |
| 10 (D10) | PD14 | 是/否 |  |
| 11 (D11) | PA7 | 是/否 | SPI1-MOSI，默认被RT-Thread的SPI设备框架spi1接管 |
| 12 (D12) | PA6 | 是/否 | SPI1-MISO，默认被RT-Thread的SPI设备框架spi1接管 |
| 13 (D13) | PA5 | 是/否 | SPI1-SCK，默认被RT-Thread的SPI设备框架spi1接管 |
| 14 (D14) | PB9 | 是/否 | I2C1-SDA，默认被RT-Thread的I2C设备框架i2c1接管 |
| 15 (D15) | PB8 | 是/否 | I2C1-SCL，默认被RT-Thread的I2C设备框架i2c1接管 |
| 16 (A0) | PA3 |  | 芯片内部参考电压 ADC，默认被RT-Thread的ADC设备框架adc1接管 |
| 17 (A1) | PA2 |  | 芯片内部参考电压 ADC，默认被RT-Thread的ADC设备框架adc1接管 |
| 18 (A2) | PC3 |  | 芯片内部参考电压 ADC，默认被RT-Thread的ADC设备框架adc1接管 |
| 19 (A3) | PB0 |  | 芯片内部参考电压 ADC，默认被RT-Thread的ADC设备框架adc1接管 |
| 20 (A4) | PC1 |  | 芯片内部参考电压 ADC，默认被RT-Thread的ADC设备框架adc1接管 |
| 21 (A5) | PC0 |  | 芯片内部参考电压 ADC，默认被RT-Thread的ADC设备框架adc1接管 |

> 注意：
>
> 1. xxxxxxxxx
> 2. xxxxxxxxx
