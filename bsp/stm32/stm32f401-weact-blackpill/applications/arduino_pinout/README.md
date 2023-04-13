# STM32F401-weact-blackpill 开发板的Arduino生态兼容说明

## 1 RTduino - RT-Thread的Arduino生态兼容层

STM32F411-weact-blackpill 开发板已经完整适配了[RTduino软件包](https://github.com/RTduino/RTduino)，即RT-Thread的Arduino生态兼容层。用户可以按照Arduino的编程习惯来操作该BSP，并且可以使用大量Arduino社区丰富的库，是对RT-Thread生态的极大增强。更多信息，请参见[RTduino软件包说明文档](https://github.com/RTduino/RTduino)。

### 1.1 如何开启针对本BSP的Arduino生态兼容层

Env 工具下敲入 menuconfig 命令，或者 RT-Thread Studio IDE 下选择 RT-Thread Settings：

```Kconfig
Hardware Drivers Config --->
    Onboard Peripheral Drivers --->
        [*] Compatible with Arduino Ecosystem (RTduino)
```

## 2 Arduino引脚排布

更多引脚布局相关信息参见 [pins_arduino.c](pins_arduino.c) 和 [pins_arduino.h](pins_arduino.h)。

![weact-blackpill-f401-pinout](images/weact-blackpill-f401-pinout.png)

| Arduino引脚编号  | STM32引脚编号 | 5V容忍 | 备注  |
| ------------------- | --------- | ---- | ------------------------------------------------------------------------- |
| 0 (D0) | PC13 | 是 | 板载用户LED |
| 1 (D1) | PC14 | 是 | I2C1-SDA，默认被RT-Thread的I2C设备框架i2c1接管 |
| 2 (D2) | PC15 | 是 | I2C1-SCL，默认被RT-Thread的I2C设备框架i2c1接管 |
| 3 (D3) | PA2 | 是 | Serial2-TX，默认被RT-Thread的UART设备框架uart2接管 |
| 4 (D4) | PA3 | 是 | Serial2-RX，默认被RT-Thread的UART设备框架uart2接管 |
| 5 (D5) | PB2 | 是 |  |
| 6 (D6) | PB10 | 是 |  |
| 7 (D7) | PB9 | 是 | PWM4-CH4，默认被RT-Thread的PWM设备框架pwm4接管 |
| 8 (D8) | PB8 | 是 | PWM4-CH3，默认被RT-Thread的PWM设备框架pwm4接管 |
| 9 (D9) | PB7 | 是 | PWM4-CH2，默认被RT-Thread的PWM设备框架pwm4接管 |
| 10 (D10) | PB6 | 是 | PWM4-CH1，默认被RT-Thread的PWM设备框架pwm4接管 |
| 11 (D11) | PB5 | 是 | SPI1-MOSI，默认被RT-Thread的SPI设备框架spi1接管 |
| 12 (D12) | PB4 | 是 | SPI1-MISO，默认被RT-Thread的SPI设备框架spi1接管 |
| 13 (D13) | PB3 | 是 | SPI1-SCK，默认被RT-Thread的SPI设备框架spi1接管 |
| 14 (D14) | PA15 | 是 | SPI1-，默认被RT-Thread的SPI设备框架spi1接管 |
| 15 (D15) | PA12 | 是 |  |
| 16 (D16) | PA11 | 是 |  |
| 17 (D17) | PA10 | 是 | Serial-RX，默认被RT-Thread的UART设备框架uart1接管 |
| 18 (D18) | PA9 | 是 | Serial-TX，默认被RT-Thread的UART设备框架uart1接管 |
| 19 (D19) | PA8 | 是 |  |
| 20 (D20) | PB15 | 是 | PWM1-CH3，默认被RT-Thread的PWM设备框架pwm1接管 |
| 21 (D21) | PB14 | 是 | PWM1-CH2，默认被RT-Thread的PWM设备框架pwm1接管 |
| 22 (D22) | PB13 | 是 | PWM1-CH1，默认被RT-Thread的PWM设备框架pwm1接管 |
| 23 (D23) | PB12 | 是 |  |
| 24 (A0) | PA0 | 是 | ADC1-CH0，默认被RT-Thread的ADC设备框架adc1接管 |
| 25 (A1) | PA1 | 是 | ADC1-CH1，默认被RT-Thread的ADC设备框架adc1接管 |
| 26 (A2) | PA4 | 是 | ADC1-CH4，默认被RT-Thread的ADC设备框架adc1接管 |
| 27 (A3) | PA5 | 是 | ADC1-CH5，默认被RT-Thread的ADC设备框架adc1接管 |
| 28 (A4) | PA6 | 是 | ADC1-CH6，默认被RT-Thread的ADC设备框架adc1接管 |
| 29 (A5) | PA7 | 是 | ADC1-CH7，默认被RT-Thread的ADC设备框架adc1接管 |
| 30 (A6) | PB0 | 是 | ADC1-CH8，默认被RT-Thread的ADC设备框架adc1接管 |
| 31 (A7) | PB1 | 是 | ADC1-CH9，默认被RT-Thread的ADC设备框架adc1接管 |
| 32 (A8) | -- |  | 芯片内部参考电压 ADC，默认被RT-Thread的ADC设备框架adc1接管 |
| 33 (A9) | -- |  | 芯片内部温度 ADC，默认被RT-Thread的ADC设备框架adc1接管 |
