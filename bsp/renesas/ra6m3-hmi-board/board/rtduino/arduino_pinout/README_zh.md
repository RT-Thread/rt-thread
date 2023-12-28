# ra6m3-hmi-board 开发板的Arduino生态兼容说明

**[English](README.md)** | **中文**

## 1 RTduino - RT-Thread的Arduino生态兼容层

ra6m3-hmi-board 开发板已经完整适配了[RTduino软件包](https://github.com/RTduino/RTduino)，即RT-Thread的Arduino生态兼容层。用户可以按照Arduino的编程习惯来操作该BSP，并且可以使用大量Arduino社区丰富的库，是对RT-Thread生态的极大增强。更多信息，请参见[RTduino软件包说明文档](https://github.com/RTduino/RTduino)。

### 1.1 如何开启针对本BSP的Arduino生态兼容层

Env 工具下敲入 menuconfig 命令，或者 RT-Thread Studio IDE 下选择 RT-Thread Settings：

```Kconfig
Hardware Drivers Config --->
    Onboard Peripheral Drivers --->
        [*] Compatible with Arduino Ecosystem (RTduino)
```

## 2 Arduino引脚排布

更多引脚布局相关信息参见 [pins_arduino.c](pins_arduino.c) 和 [pins_arduino.h](pins_arduino.h)。

![ra6m3-hmi-board-pinout-figure](ra6m3-hmi-board-pinout-figure.jpg)

| Arduino引脚编号  | STM32引脚编号 | 5V容忍 | 备注  |
| ------------------- | --------- | ---- | ------------------------------------------------------------------------- |
| 0 (D0) | P206 | 是 | Serial4-RX,默认被RT-Thread的UART设备框架uart4接管 |
| 1 (D1) | P205 | 是 | Serial4-TX,默认被RT-Thread的UART设备框架uart4接管 |
| 2 (D2) | P008 | 是 |  |
| 3 (D3) | P506 | 是 |  |
| 4 (D4) | P603 | 是 |  |
| 5 (D5) | P604 | 是 | PWM8-CH0,默认被RT-Thread的PWM设备框架pwm8的channel0接管 |
| 6 (D6) | P605 | 是 | PWM8-CH0,默认被RT-Thread的PWM设备框架pwm8的channel0接管 |
| 7 (D7) | P208 | 是 |  |
| 8 (D8) | P207 | 是 |  |
| 9 (D9) | P009 | 是 |  |
| 10 (D10) | P712 | 是 | PWM2-CH0,默认被RT-Thread的PWM设备框架pwm2的channel0接管 |
| 11 (D11) | P512 | 是 | PWM0-CH0,默认被RT-Thread的PWM设备框架pwm0的channel0接管 |
| 12 (D12) | P511 | 是 |  |
| 13 (D13) | P204 | 是 |  |
| 14 (D14) | P203 | 是 |  |
| 15 (D15) | P202 | 是 |  |
| 16 (A0) | P000 | 是 | ADC1-CH0-EXTVOL(外部电压),默认被RT-Thread的ADC设备框架adc0的channel0接管 |
| 17 (A1) | P001 | 是 | ADC1-CH1-EXTVOL(外部电压),默认被RT-Thread的ADC设备框架adc0的channel1接管 |
| 18 (A2) | P002 | 是 | ADC1-CH2-EXTVOL(外部电压),默认被RT-Thread的ADC设备框架adc0的channel2接管 |
| 19 (A3) | P003 | 是 | ADC1-CH7-EXTVOL(外部电压),默认被RT-Thread的ADC设备框架adc0的channel7接管 |
| 20 (A4) | P508 | 是 | ADC1-CH19-EXTVOL(外部电压),默认被RT-Thread的ADC设备框架adc0的channel20接管 |
| 21 (A5) | P014 | 是 | ADC1-CH5-EXTVOL(外部电压),默认被RT-Thread的ADC设备框架adc0的channel5接管 |

> 注意：
> 1.RTduino暂时不对MDK支持，建议使用GNU GCC工具链编译
> 2.renesas的pwm通道默认使用channel0，详细驱动细节请查阅`bsp\renesas\libraries\HAL_Drivers\drv_pwm.c`文件