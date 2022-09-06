# STM32F69 Discovery开发板的Arduino生态兼容说明

## 1 RTduino - RT-Thread的Arduino生态兼容层

STM32F469 Discovery开发板已经完整适配了[RTduino软件包](https://github.com/RTduino/RTduino)，即RT-Thread的Arduino生态兼容层。用户可以按照Arduino的编程习惯来操作该BSP，并且可以使用大量Arduino社区丰富的库，是对RT-Thread生态的极大增强。更多信息，请参见[RTduino软件包说明文档](https://github.com/RTduino/RTduino)。

### 1.1 如何开启针对本BSP的Arduino生态兼容层

Env 工具下敲入 menuconfig 命令，或者 RT-Thread Studio IDE 下选择 RT-Thread Settings：

```Kconfig
Hardware Drivers Config --->
    Onboard Peripheral Drivers --->
        [*] Support Arduino
```

## 2 Arduino引脚排布

![disco-f469-pinout](disco-f469-pinout.png)

该BSP遵照Arduino UNO板的引脚排列方式。详见 `pins_arduino.c`

| Arduino引脚编号 | STM32引脚编号 | 5V容忍 | 备注                                                         |
| --------------- | ------------- | ------ | ------------------------------------------------------------ |
| 0 (D0)          | --            |        | 该引脚在UNO板中为串口RX引脚，不可当做普通IO                  |
| 1 (D1)          | --            |        | 该引脚在UNO板中为串口TX引脚，不可当做普通IO                  |
| 2 (D2)          | PG13          | 是     |                                                              |
| 3 (D3)          | PA1           | 是     | PWM（定时器2发生）                                           |
| 4 (D4)          | PG12          | 是     |                                                              |
| 5 (D5)          | PA2           | 是     | PWM（定时器2发生）                                           |
| 6 (D6)          | PA6           | 是     | PWM（定时器3发生）                                           |
| 7 (D7)          | PG11          | 是     |                                                              |
| 8 (D8)          | PG10          | 是     |                                                              |
| 9 (D9)          | PA7           | 是     | PWM（定时器3发生）                                           |
| 10 (D10)        | PH6           | 是     | PWM（定时器12发生）                                          |
| 11 (D11)        | PB15          | 是     | PWM（定时器12发生）                                          |
| 12 (D12)        | PB14          | 是     |                                                              |
| 13 (D13)        | PD3           | 是     | LED_BUILTIN                                                  |
| 14 (D14)        | PB9           | 是     | I2C1-SDA，被RT-Thread的I2C设备框架i2c1总线接管，不可当做普通IO |
| 15 (D15)        | PB8           | 是     | I2C1_SCL，被RT-Thread的I2C设备框架i2c1总线接管，不可当做普通IO |
| 16 (D16)        | PA0           | 是     | Discovery板载用户按键（蓝色）                                |
| 17（D17）       | PG6           | 是     | user LED1(用户LED)                                           |
| 18（D18）       | PD4           | 是     | user LED2(用户LED)                                           |
| 19（D19）       | PD5           | 是     | user LED3(用户LED)                                           |
| 20（D20）       | PK3           | 是     | user LED4(用户LED)                                           |
| A0              | PB1           | 是     | ADC Channel_9                                                |
| A1              | PC2           | 是     | ADC Channel_12                                               |
| A2              | PC3           | 是     | ADC Channel_13                                               |
| A3              | PC4           | 是     | ADC Channel_14                                               |
| A4              | PC5           | 是     | ADC Channel_15                                               |
| A5              | PA4           | 是     | ADC Channel_4                                                |
| A6              | --            |        | 芯片内部参考电压 ADC                                         |
| A7              | --            |        | 芯片内部温度 ADC                                             |

> 注意：
>
> - 暂无

> 参考资料
>
> 【1】[STM32F469 Discovery官方资料](https://www.st.com/en/evaluation-tools/32f469idiscovery.html#documentation)

## 3 I2C总线

STM32F469 Discovery板的I2C总线是板上丝印的 `SCL/D15` 和 `SDA/D14` 引脚，这两个引脚是被RT-Thread I2C设备框架接管的，不需要直接操控这两个引脚，直接引用`#include <Wire.h>`（Arduino官方I2C头文件）即可使用。
