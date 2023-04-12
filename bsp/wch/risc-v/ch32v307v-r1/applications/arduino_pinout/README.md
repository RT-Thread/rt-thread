# The Arduino Compatible for CH32V307V-R1

**English** | [中文](README_zh.md)

## 1 RTduino - Arduino Ecosystem Compatibility Layer for RT-Thread

CH32V307V-R1 board has support [RTduino](https://github.com/RTduino/RTduino). Users can use Arduino APIs, third party libraries and programming method to program on the board.

### 1.1 How to Enable RTduino

This board complies with Arduino UNO pins layout. For more details, Please go to the [RTduino repository](https://github.com/RTduino/RTduino).

```Kconfig
Hardware Drivers Config --->
    Onboard Peripheral Drivers --->
        [*] Compatible with Arduino Ecosystem (RTduino)
```

## 2 Arduino Pinout

For more information, please see [pins_arduino.c](pins_arduino.c) and [pins_arduino.h](pins_arduino.h).

| Arduino Pin | CH32 Pin | 5V Tolerate | Note                                                      |
| ----------- | -------- | ----------- | --------------------------------------------------------- |
| 0 (D0)      | PA10     | Yes         | Serial-Rx. Token over by RT-Thread UART device by default |
| 1 (D1)      | PA9      | Yes         | Serial-Tx. Token over by RT-Thread UART device by default |
| 2 (D2)      | PA8      | Yes         | PWM1-CH1. Token over by RT-Thread PWM device by default   |
| 3 (D3)      | PA7      | No          | PWM3-CH2. Token over by RT-Thread PWM device by default   |
| 4 (D4)      | PA6      | No          | PWM3-CH1. Token over by RT-Thread PWM device by default   |
| 5 (D5)      | PB5      | Yes         |                                                           |
| 6 (D6)      | PB8      | Yes         | PWM4-CH3. Token over by RT-Thread PWM device by default   |
| 7 (D7)      | PB9      | Yes         | PWM4-CH4. Token over by RT-Thread PWM device by default   |
| 8 (D8)      | PB1      | No          | PWM3-CH4. Token over by RT-Thread PWM device by default   |
| 9 (D9)      | PB0      | No          | PWM3-CH3. Token over by RT-Thread PWM device by default   |
| 10 (D10)    | PB12     | Yes         |                                                           |
| 11 (D11)    | PB15     | Yes         |                                                           |
| 12 (D12)    | PB14     | Yes         |                                                           |
| 13 (D13)    | PB13     | Yes         |                                                           |
| 14 (D14)    | PB11     | Yes         | I2C-SDA. Token over by RT-Thread I2C device by default    |
| 15 (D15)    | PB10     | No          | I2C-SCL. Token over by RT-Thread I2C device by default    |
| A0          | PA0      | No          | ADC1-CH0. Token over by RT-Thread ADC device by default   |
| A1          | PA1      | No          | ADC1-CH1. Token over by RT-Thread ADC device by default   |
| A2          | PA2      | No          | ADC1-CH2. Token over by RT-Thread ADC device by default   |
| A3          | PA3      | No          | ADC1-CH3. Token over by RT-Thread ADC device by default   |
| A4          | PA4      | No          | ADC1-CH4. Token over by RT-Thread ADC device by default   |
| A5          | PA5      | No          | ADC1-CH5. Token over by RT-Thread ADC device by default   |

> Notice:
> 
> 1. Don't use a same hardware timer to drive PWM (analogRead) and servos at same time, because hardware timers can only generate a same frequency for 4 PWM channels. Otherwise, it could cause a failure when drive servos.

## 3 Communication

### 3.1 I2C Bus

I2C bus is `SCL/D15` and `SDA/D14` pins. Users can directly include the `#include <Wire.h>`, which is the Arduino official I2C header file, to use the I2C bus.

### 3.2 SPI Bus

This board doesn't support Arduino SPI header file and functions.

### 3.3 Serial

This board supports to use `Serial.` method to operate `uart1` device. See [example](https://github.com/RTduino/RTduino/blob/master/examples/Basic/helloworld.cpp).
