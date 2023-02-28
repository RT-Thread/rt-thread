# 大疆STM32F427 Robomaster A型开发板的Arduino生态兼容说明

## 1 RTduino - RT-Thread的Arduino生态兼容层

大疆STM32F427 Robomaster A型开发板已经完整适配了[RTduino软件包](https://github.com/RTduino/RTduino)，即RT-Thread的Arduino生态兼容层。用户可以按照Arduino的编程习惯来操作该BSP，并且可以使用大量Arduino社区丰富的库，是对RT-Thread生态的极大增强。更多信息，请参见[RTduino软件包说明文档](https://github.com/RTduino/RTduino)。

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
| 0 (D0) | PF14 | 是 | 板载用户LED |
| 1 (D1) | PD9 | 是 | Serial-RX，默认被RT-Thread的UART设备框架uart3接管 |
| 2 (D2) | PD8 | 是 | Serial-TX，默认被RT-Thread的UART设备框架uart3接管 |
| 3 (D3) | PG9 | 是 | Serial-RX，默认被RT-Thread的UART设备框架uart6接管 |
| 4 (D4) | PG14 | 是 | Serial-TX，默认被RT-Thread的UART设备框架uart6接管 |
| 5 (D5) | PE0 | 是 | Serial-RX，默认被RT-Thread的UART设备框架uart8接管 |
| 6 (D6) | PE1 | 是 | Serial-TX，默认被RT-Thread的UART设备框架uart8接管 |
| 7 (D7) | PE7 | 是 | Serial-RX，默认被RT-Thread的UART设备框架uart7接管 |
| 8 (D8) | PE8 | 是 | Serial-TX，默认被RT-Thread的UART设备框架uart7接管 |
| 9 (D9) | PH6 | 是 | 板载蜂鸣器，PWM12-CH1，默认被RT-Thread的PWM设备框架pwm12接管 |
| 10 (D10) | PD12 | 是 | PWM4-CH1，默认被RT-Thread的PWM设备框架pwm4接管 |
| 11 (D11) | PD13 | 是 | PWM4-CH2，默认被RT-Thread的PWM设备框架pwm4接管 |
| 12 (D12) | PD14 | 是 | PWM4-CH3，默认被RT-Thread的PWM设备框架pwm4接管 |
| 13 (D13) | PD15 | 是 | PWM4-CH4，默认被RT-Thread的PWM设备框架pwm4接管 |
| 14 (D14) | PH10 | 是 | PWM5-CH1，默认被RT-Thread的PWM设备框架pwm5接管 |
| 15 (D15) | PH11 | 是 | PWM5-CH2，默认被RT-Thread的PWM设备框架pwm5接管 |
| 16 (D16) | PH12 | 是 | PWM5-CH3，默认被RT-Thread的PWM设备框架pwm5接管 |
| 17 (D17) | PI0 | 是 | PWM5-CH4，默认被RT-Thread的PWM设备框架pwm5接管 |
| 18 (D18) | PA0 | 是 | PWM2-CH1，默认被RT-Thread的PWM设备框架pwm2接管 |
| 19 (D19) | PA1 | 是 | PWM2-CH2，默认被RT-Thread的PWM设备框架pwm2接管 |
| 20 (D20) | PA2 | 是 | PWM2-CH3，默认被RT-Thread的PWM设备框架pwm2接管 |
| 21 (D21) | PA3 | 是 | PWM2-CH4，默认被RT-Thread的PWM设备框架pwm2接管 |
| 22 (D22) | PI5 | 是 | PWM8-CH1，默认被RT-Thread的PWM设备框架pwm8接管 |
| 23 (D23) | PI6 | 是 | PWM8-CH2，默认被RT-Thread的PWM设备框架pwm8接管 |
| 24 (D24) | PI7 | 是 | PWM8-CH3，默认被RT-Thread的PWM设备框架pwm8接管 |
| 25 (D25) | PI2 | 是 | PWM8-CH4，默认被RT-Thread的PWM设备框架pwm8接管 |
| 26 (D26) | PF1 | 是 |  |
| 27 (D27) | PF0 | 是 |  |
| 28 (D28) | PE4 | 是 | I2C1-SCL，默认被RT-Thread的I2C设备框架i2c1接管 |
| 29 (D29) | PE5 | 是 | I2C1-SDA，默认被RT-Thread的I2C设备框架i2c1接管 |
| 30 (D30) | PE6 | 是 |  |
| 31 (D31) | PE12 | 是 |  |
| 32 (D32) | PC2 | 是 |  |
| 33 (D33) | PB0 | 是 |  |
| 34 (D34) | PC3 | 是 |  |
| 35 (D35) | PB1 | 是 |  |
| 36 (D36) | PC4 | 是 |  |
| 37 (D37) | PC0 | 是 |  |
| 38 (D38) | PC5 | 是 |  |
| 39 (D39) | PC1 | 是 |  |
| 40 (D40) | PA5 | 否 |  |
| 41 (D41) | PA4 | 否 |  |
| 42 (D42) | PF10 | 是 |  |
| 43 (D43) | PI9 | 是 |  |
| 44 (A0) | -- |  | 芯片内部温度 ADC，默认被RT-Thread的ADC设备框架adc1接管 |
| 45 (A1) | -- |  | 芯片内部参考电压 ADC，默认被RT-Thread的ADC设备框架adc1接管 |
