# 大疆STM32F407 Robomaster C型开发板的Arduino生态兼容说明

## 1 RTduino - RT-Thread的Arduino生态兼容层

大疆STM32F407 Robomaster C型开发板已经完整适配了[RTduino软件包](https://github.com/RTduino/RTduino)，即RT-Thread的Arduino生态兼容层。用户可以按照Arduino的编程习惯来操作该BSP，并且可以使用大量Arduino社区丰富的库，是对RT-Thread生态的极大增强。更多信息，请参见[RTduino软件包说明文档](https://github.com/RTduino/RTduino)。

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
| 0 (D0) | PH11 | 是 | 板载用户LED |
| 1 (D1) | PB7 | 是 | Serial-RX，默认被RT-Thread的UART设备框架uart1接管 |
| 2 (D2) | PA9 | 是 | Serial-TX，默认被RT-Thread的UART设备框架uart1接管 |
| 3 (D3) | PG9 | 是 | Serial-RX，默认被RT-Thread的UART设备框架uart6接管 |
| 4 (D4) | PG14 | 是 | Serial-TX，默认被RT-Thread的UART设备框架uart6接管 |
| 5 (D5) | PF1 | 否 | I2C1-SCL，默认被RT-Thread的I2C设备框架i2c1接管 |
| 6 (D6) | PF0 | 否 | I2C1-SDA，默认被RT-Thread的I2C设备框架i2c1接管 |
| 7 (D7) | PE9 | 是 | PWM1-CH1，默认被RT-Thread的PWM设备框架pwm1接管 |
| 8 (D8) | PE11 | 是 | PWM1-CH2，默认被RT-Thread的PWM设备框架pwm1接管 |
| 9 (D9) | PE13 | 是 | PWM1-CH3，默认被RT-Thread的PWM设备框架pwm1接管 |
| 10 (D10) | PE14 | 是 | PWM1-CH4，默认被RT-Thread的PWM设备框架pwm1接管 |
| 11 (D11) | PC6 | 是 | PWM8-CH1，默认被RT-Thread的PWM设备框架pwm8接管 |
| 12 (D12) | PI6 | 是 | PWM8-CH2，默认被RT-Thread的PWM设备框架pwm8接管 |
| 13 (D13) | PI7 | 是 | PWM8-CH3，默认被RT-Thread的PWM设备框架pwm8接管 |
| 14 (A0) | -- |  | 芯片内部温度 ADC，默认被RT-Thread的ADC设备框架adc1接管 |
| 15 (A1) | -- |  | 芯片内部参考电压 ADC，默认被RT-Thread的ADC设备框架adc1接管 |

