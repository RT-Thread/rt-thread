# stm32h503-st-nucleo 开发板的Arduino生态兼容说明

## 1 RTduino - RT-Thread的Arduino生态兼容层

stm32h503-st-nucleo 开发板已经完整适配了[RTduino软件包](https://github.com/RTduino/RTduino)，即RT-Thread的Arduino生态兼容层。用户可以按照Arduino的编程习惯来操作该BSP，并且可以使用大量Arduino社区丰富的库，是对RT-Thread生态的极大增强。更多信息，请参见[RTduino软件包说明文档](https://github.com/RTduino/RTduino)。

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
| 0 (D0) | GET_PIN(B, 15) | 是 | Serial2-RX,默认被RT-Thread的UART设备框架uart1接管 |
| 1 (D1) | GET_PIN(B, 14) | 是 | Serial2-TX,默认被RT-Thread的UART设备框架uart1接管 |
| 2 (D2) | GET_PIN(A, 10) | 是 |  |
| 3 (D3) | GET_PIN(B, 3) | 是 |  |
| 4 (D4) | GET_PIN(B, 5) | 是 |  |
| 5 (D5) | GET_PIN(B, 4) | 是 | PWM1-CH2,默认被RT-Thread的PWM设备框架pwm1接管 |
| 6 (D6) | GET_PIN(B, 10) | 是 | PWM2-CH3,默认被RT-Thread的PWM设备框架pwm2接管 |
| 7 (D7) | GET_PIN(A, 8) | 是 |  |
| 8 (D8) | GET_PIN(C, 7) | 是 |  |
| 9 (D9) | GET_PIN(C, 6) | 是 | PWM3-CH1,默认被RT-Thread的PWM设备框架pwm3接管 |
| 10 (D10) | GET_PIN(C, 9) | 是 | PWM3-CH4,默认被RT-Thread的PWM设备框架pwm3接管 |
| 11 (D11) | GET_PIN(A, 7) | 是 | PWM3-CH2,默认被RT-Thread的PWM设备框架pwm3接管 |
| 12 (D12) | GET_PIN(A, 6) | 是 |  |
| 13 (D13) | GET_PIN(A, 5) | 是 | 板载用户LED |
| 14 (D14) | GET_PIN(B, 7) | 是 | I2C1-SDA,默认被RT-Thread的I2C设备框架i2c1接管 |
| 15 (D15) | GET_PIN(B, 6) | 是 | I2C1-SCL,默认被RT-Thread的I2C设备框架i2c1接管 |
| 16 (A0) | GET_PIN(A, 0) | 是 | ADC1-CH0,默认被RT-Thread的ADC设备框架adc1接管 |
| 17 (A1) | GET_PIN(A, 1) | 是 | ADC1-CH1,默认被RT-Thread的ADC设备框架adc1接管 |
| 18 (A2) | GET_PIN(A, 2) | 是 | ADC1-CH14,默认被RT-Thread的ADC设备框架adc1接管 |
| 19 (A3) | GET_PIN(B, 0) | 是 | ADC1-CH9,默认被RT-Thread的ADC设备框架adc1接管 |
| 20 (A4) | GET_PIN(C, 1) | 是 | ADC1-CH11,默认被RT-Thread的ADC设备框架adc1接管 |
| 21 (A5) | GET_PIN(C, 0) | 是 | ADC1-CH10,默认被RT-Thread的ADC设备框架adc1接管 |

> 注意：
>
> 1. xxxxxxxxx
> 2. xxxxxxxxx
