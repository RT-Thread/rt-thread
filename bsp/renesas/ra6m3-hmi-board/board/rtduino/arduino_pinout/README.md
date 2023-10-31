# ra6m3-hmi-board Arduino Eco-compatibility Guide

**[中文](README_zh.md)** | **English**

## 1 RTduino - Arduino Eco-compatibility Layer for RT-Thread

The ra6m3-hmi-board development board has been fully adapted to the [RTduino software package](https://github.com/RTduino/RTduino), which is an Arduino eco-compatibility layer for RT-Thread. Users can program this BSP in accordance with Arduino coding conventions and can utilize a wide range of libraries from the Arduino community, significantly enhancing the RT-Thread ecosystem. For more information, please refer to the [RTduino software package documentation](https://github.com/RTduino/RTduino).

### 1.1 Enabling the Arduino Eco-compatibility Layer for this BSP

In the Env tool, enter the "menuconfig" command, or in the RT-Thread Studio IDE, select "RT-Thread Settings":

```Kconfig
Hardware Drivers Config --->
    Onboard Peripheral Drivers --->
        [*] Compatible with Arduino Ecosystem (RTduino)
```

## 2 Arduino Pin Layout

For more information about pin layout, please see [pins_arduino.c](pins_arduino.c) and [pins_arduino.h](pins_arduino.h).

![ra6m3-hmi-board-pinout-figure](ra6m3-hmi-board-pinout-figure.jpg)

| Arduino Pin Number | STM32 Pin Number | 5V Tolerance | Remarks |
| ------------------- | --------- | ---- | ------------------------------------------------------------------------- |
| 0 (D0) | P206 | Yes | Serial4-RX, managed by RT-Thread's UART device framework uart4 by default |
| 1 (D1) | P205 | Yes | Serial4-TX, managed by RT-Thread's UART device framework uart4 by default |
| 2 (D2) | P008 | Yes |  |
| 3 (D3) | P506 | Yes |  |
| 4 (D4) | P603 | Yes |  |
| 5 (D5) | P604 | Yes |  |
| 6 (D6) | P605 | Yes |  |
| 7 (D7) | P208 | Yes |  |
| 8 (D8) | P207 | Yes |  |
| 9 (D9) | P009 | Yes |  |
| 10 (D10) | P712 | Yes | PWM2-CH2, managed by RT-Thread's PWM device framework pwm2's channel2 by default |
| 11 (D11) | P512 | Yes | I2C2-SCL, managed by RT-Thread's I2C device framework i2c2 by default |
| 12 (D12) | P511 | Yes | I2C2-SDA, managed by RT-Thread's I2C device framework i2c2 by default |
| 13 (D13) | P204 | Yes |  |
| 14 (D14) | P203 | Yes |  |
| 15 (D15) | P202 | Yes |  |
| 16 (A0) | P000 | Yes | ADC1-CH0-EXTVOL (external voltage), managed by RT-Thread's ADC device framework adc0's channel0 by default |
| 17 (A1) | P001 | Yes | ADC1-CH1-EXTVOL (external voltage), managed by RT-Thread's ADC device framework adc0's channel1 by default |
| 18 (A2) | P002 | Yes | ADC1-CH2-EXTVOL (external voltage), managed by RT-Thread's ADC device framework adc0's channel2 by default |
| 19 (A3) | P003 | Yes | ADC1-CH7-EXTVOL (external voltage), managed by RT-Thread's ADC device framework adc0's channel7 by default |
| 20 (A4) | P508 | Yes | ADC1-CH19-EXTVOL (external voltage), managed by RT-Thread's ADC device framework adc0's channel20 by default |
| 21 (A5) | P014 | Yes | ADC1-CH5-EXTVOL (external voltage), managed by RT-Thread's ADC device framework adc0's channel5 by default |

> Note: RTduino does not currently support MDK. It is recommended to use the GNU GCC toolchain for compilation.