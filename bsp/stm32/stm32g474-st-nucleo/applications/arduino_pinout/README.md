# STM32G474 Nucleo开发板的Arduino生态兼容说明

## 1 RTduino - RT-Thread的Arduino生态兼容层

STM32G474 Nucleo开发板已经完整适配了[RTduino软件包](https://github.com/RTduino/RTduino)，即RT-Thread的Arduino生态兼容层。用户可以按照Arduino的编程习惯来操作该BSP，并且可以使用大量Arduino社区丰富的库，是对RT-Thread生态的极大增强。更多信息，请参见[RTduino软件包说明文档](https://github.com/RTduino/RTduino)。

### 1.1 如何开启针对本BSP的Arduino生态兼容层

Env 工具下敲入 menuconfig 命令，或者 RT-Thread Studio IDE 下选择 RT-Thread Settings：

```Kconfig
Hardware Drivers Config --->
    Onboard Peripheral Drivers --->
        [*] Compatible with Arduino Ecosystem (RTduino)
```

## 2 Arduino引脚排布

更多引脚布局相关信息参见 [pins_arduino.c](pins_arduino.c) 和 [pins_arduino.h](pins_arduino.h)。

![stm32g474-nucleo-pinout.jpg](./stm32g474-nucleo-pinout.jpg)
| Arduino引脚编号  | STM32引脚编号 | 5V容忍 | 备注  |
| ------------------- | --------- | ---- | ------------------------------------------------------------------------- |
| 0 (D0) | PA2 | 是 | Serial-Tx，默认被RT-Thread的UART设备框架lpuart1接管 |
| 1 (D1) | PA3 | 是 | Serial-Rx，默认被RT-Thread的UART设备框架lpuart1接管 |
| 2 (D2) | PA10 | 是 |  |
| 3 (D3) | PB3 | 是 |  |
| 4 (D4) | PB5 | 是 |  |
| 5 (D5) | PB4 | 是 | PWM3-CH1，默认被RT-Thread的PWM设备框架pwm3接管 |
| 6 (D6) | PB10 | 是 | PWM2-CH3，默认被RT-Thread的PWM设备框架pwm2接管 |
| 7 (D7) | PA8 | 是 |  |
| 8 (D8) | PA9 | 是 |  |
| 9 (D9) | PC7 | 是 |  |
| 10 (D10) | PB6 | 是 |  |
| 11 (D11) | PA7 | 是 |  |
| 12 (D12) | PA6 | 是 |  |
| 13 (D13) | PA5 | 是 |  |
| 14 (D14) | PB9 | 是 | I2C2-SDA，默认被RT-Thread的I2C设备框架i2c2接管 |
| 15 (D15) | PB8 | 是 | I2C2-SCL，默认被RT-Thread的I2C设备框架i2c2接管 |
| 16 (D16) | PC13 | 是 |  |
| 17 (A0) | PA0 | 是 | ADC1-CH1，默认被RT-Thread的ADC设备框架adc1接管 |
| 18 (A1) | PA1 | 是 | ADC1-CH2，默认被RT-Thread的ADC设备框架adc1接管 |
| 19 (A2) | PA4 | 是 | ADC2-CH17，默认被RT-Thread的ADC设备框架adc2接管 |
| 20 (A3) | PB0 | 是 | ADC3-CH12，默认被RT-Thread的ADC设备框架adc3接管 |
| 21 (A4) | PC1 | 是 | ADC2-CH7，默认被RT-Thread的ADC设备框架adc2接管 |
| 22 (A5) | PC0 | 是 | ADC2-CH6，默认被RT-Thread的ADC设备框架adc2接管 |
| 23 (A6) | -- |  | 芯片内部参考电压 ADC，默认被RT-Thread的ADC设备框架adc1接管 |
| 24 (A7) | -- |  | 芯片内部温度 ADC，默认被RT-Thread的ADC设备框架adc1接管 |

> 注意：
>
> 1. xxxxxxxxx
> 2. xxxxxxxxx
