# The Arduino Compatible for STM32G474 Nucleo development board

English | [中文](https://github.com/kurisaW/rt-thread/blob/g474_rtdu/bsp/stm32/stm32g474-st-nucleo/applications/arduino_pinout/README_zh.md)

## 1 RTduino - Arduino compatible layer of RT-Thread ecosystem

The STM32G474 Nucleo development board has been fully adapted to the [RTduino package](https://github.com/RTduino/RTduino), which is an Arduino compatible layer of RT-Thread ecosystem. Users can operate the BSP according to the programming habits of Arduino and can use a large number of libraries provided by the Arduino community, which greatly enhances the RT-Thread ecosystem. For more information, please refer to [RTduino package documentation](https://github.com/RTduino/RTduino).

### 1.1 How to enable Arduino compatible layer for this BSP

Enter the `menuconfig` command in Env tool or select RT-Thread Settings in the RT-Thread Studio IDE:

```Kconfig
Hardware Drivers Config --->
    Onboard Peripheral Drivers --->
        [*] Compatible with Arduino Ecosystem (RTduino)
```

## 2 Arduino pin layout

For more information on pin layout, please refer to [pins_arduino.c](pins_arduino.c) and [pins_arduino.h](pins_arduino.h).

![stm32g474-nucleo-pinout.jpg](./stm32g474-nucleo-pinout.jpg)

| Arduino Pin Number | STM32 Pin Number | 5V Tolerant | Note |
| ------------------ | ---------------- | ----------- | --------------------------------------------------- |
| 0 (D0) | PA2 | Yes | Serial-Tx, default used by the RT-Thread UART device framework lpuart1 |
| 1 (D1) | PA3 | Yes | Serial-Rx, default used by the RT-Thread UART device framework lpuart1 |
| 2 (D2) | PA10 | Yes | |
| 3 (D3) | PB3 | Yes | |
| 4 (D4) | PB5 | Yes | |
| 5 (D5) | PB4 | Yes | PWM3-CH1, default used by the RT-Thread PWM device framework pwm3 |
| 6 (D6) | PB10 | Yes | PWM2-CH3, default used by the RT-Thread PWM device framework pwm2 |
| 7 (D7) | PA8 | Yes | |
| 8 (D8) | PA9 | Yes | |
| 9 (D9) | PC7 | Yes | |
| 10 (D10) | PB6 | Yes | |
| 11 (D11) | PA7 | Yes | |
| 12 (D12) | PA6 | Yes | |
| 13 (D13) | PA5 | Yes | |
| 14 (D14) | PB9 | Yes | I2C2-SDA, default used by the RT-Thread I2C device framework i2c2 |
| 15 (D15) | PB8 | Yes | I2C2-SCL, default used by the RT-Thread I2C device framework i2c2 |
| 16 (D16) | PC13 | Yes | |
| 17 (A0) | PA0 | Yes | ADC1-CH1, default used by the RT-Thread ADC device framework adc1 |
| 18 (A1) | PA1 | Yes | ADC1-CH2, default used by the RT-Thread ADC device framework adc1 |
| 19 (A2) | PA4 | Yes | ADC2-CH17, default used by the RT-Thread ADC device framework adc2 |
| 20 (A3) | PB0 | Yes | ADC3-CH12, default used by the RT-Thread ADC device framework adc3 |
| 21 (A4) | PC1 | Yes | ADC2-CH7, default used by the RT-Thread ADC device framework adc2 |
| 22 (A5) | PC0 | Yes | ADC2-CH6, default used by the RT-Thread ADC device framework adc2 |
| 23 (A6) | -- |  | Internal reference voltage ADC of the chip, default used by the RT-Thread ADC device framework adc1 |
| 24 (A7) | -- |  | Internal temperature ADC of the chip, default used by the RT-Thread ADC device framework adc1 |
