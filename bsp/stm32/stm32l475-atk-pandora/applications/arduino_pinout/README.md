# STM32L475潘多拉的Arduino生态兼容说明

## 1 RTduino - RT-Thread的Arduino生态兼容层

STM32L475潘多拉已经完整适配了[RTduino软件包](https://github.com/RTduino/RTduino)，即RT-Thread的Arduino生态兼容层。用户可以按照Arduino的编程习惯来操作该BSP，并且可以使用大量Arduino社区丰富的库，是对RT-Thread生态的极大增强。更多信息，请参见[RTduino软件包说明文档](https://github.com/RTduino/RTduino)。

### 1.1 如何开启针对本BSP的Arduino生态兼容层

Env 工具下敲入 menuconfig 命令，或者 RT-Thread Studio IDE 下选择 RT-Thread Settings：

```Kconfig
Hardware Drivers Config --->
    Onboard Peripheral Drivers --->
        [*] Support Arduino
```

## 2 Arduino引脚排布

该BSP遵照Arduino UNO板的引脚排列方式，并扩展增加了潘多拉自身的板载资源功能引脚。详见 `pins_arduino.c`

### 2.1 Arduino引脚排布统览

| Arduino引脚编号       | STM32引脚编号 | 备注                                                         |
| --------------------- | ------------- | ------------------------------------------------------------ |
| 0 (D0)                | --            | 该引脚在UNO板中为串口RX引脚，不可当做普通IO                  |
| 1 (D1)                | --            | 该引脚在UNO板中为串口TX引脚，不可当做普通IO                  |
| 2 (D2)                | PB9           | 普通IO                                                       |
| 3 (D3)                | PD15          | PWM（定时器4发生）                                           |
| 4 (D4)                | PA8           | 普通IO                                                       |
| 5 (D5)                | PD14          | 普通IO                                                       |
| 6 (D6)                | PB11          | PWM（定时器2发生）                                           |
| 7 (D7)                | PB14          | 普通IO                                                       |
| 8 (D8)                | PB12          | 普通IO                                                       |
| 9 (D9)                | PD12          | PWM（定时器4发生）                                           |
| 10 (D10)              | PB10          | PWM（定时器2发生）                                           |
| 11 (D11)              | PB8           | PWM（定时器4发生）                                           |
| 12 (D12)              | PB15          | 普通IO                                                       |
| 13 (D13)              | PB13          | 普通IO                                                       |
| 14 (D14)              | PA1           | 振动电机-A                                                   |
| 15 (D15)              | PA0           | 振动电机-B                                                   |
| 16 (D16)              | PB2           | 蜂鸣器                                                       |
| 17 (D17)              | PD10          | KEY0                                                         |
| 18 (D18)              | PD9           | KEY1                                                         |
| 19 (D19)              | PD8           | KEY2                                                         |
| 20 (D20)              | PC13          | KEY-WKUP                                                     |
| 21 (D21)              | PE7           | 红色LED                                                      |
| 22 (D22, LED_BUILTIN) | PE8           | 绿色LED，Arduino默认LED                                      |
| 23 (D23)              | PE9           | 蓝色LED，具有PWM功能（定时器1发生）                          |
| 24 (D24)              | PB0           | 红外发送                                                     |
| 25 (D25)              | PB1           | 红外接收                                                     |
| A0                    | PC2           | ADC                                                          |
| A1                    | PC4           | ADC                                                          |
| A2                    | --            | 芯片内部参考电压 ADC                                         |
| A3                    | --            | 芯片内部温度 ADC                                             |
| DAC0                  | PA4           | 真模拟输出 DAC                                               |
| --                    | PC7           | I2C1-SDA，被RT-Thread的I2C设备框架i2c1总线接管，不可当做普通IO |
| --                    | PC6           | I2C1-SCL，被RT-Thread的I2C设备框架i2c1总线接管，不可当做普通IO |

> 注意：
>
> 1. 驱动舵机和analogWrite函数要选择不同定时器发生的PWM信号引脚，由于STM32的定时器4个通道需要保持相同的频率，如果采用相同的定时器发生的PWM分别驱动舵机和analogWrite，可能会导致舵机失效。
> 2. USART1是潘多拉板的默认串口，理论应对接到了Arduino引脚编号的D0和D1，但是其实际用于串口通信，因此不允许当做普通IO来使用和操作。

### 2.2 板载排针的Arduino引脚排布

| STM32引脚编号 | Arduino引脚编号 | 备注     | STM32引脚编号 | Arduino引脚编号 | 备注     |
| ------------- | --------------- | -------- | ------------- | --------------- | -------- |
| PB8           | 11 (D11)        | PWM      | PB9           | 2 (D2)          | 普通IO   |
| PC7           | A4              | I2C1-SDA | PA8           | 4 (D4)          | 普通IO   |
| PD15          | 3 (D3)          | PWM      | PC6           | A5              | I2C1-SCL |
| PD13          | --              | --       | PD14          | 5 (D5)          | 普通IO   |
| PC2           | A0              | ADC      | PD12          | 9 (D9)          | PWM      |
| PB14          | 7 (D7)          | 普通IO   | PB15          | 12 (D12)        | 普通IO   |
| PB12          | 8 (D8)          | 普通IO   | PB13          | 13 (D13)        | 普通IO   |
| PB10          | 10 (D10)        | PWM      | PB11          | 6 (D6)          | PWM      |
| PC4           | A1              | ADC      | PA4           | DAC0            | DAC      |

### 2.3 板载外设的Arduino引脚排布

| 外设名称              | Arduino引脚编号       | STM32引脚编号 |
| --------------------- | --------------------- | ------------- |
| 振动电机-A            | 14 (D14)              | PA1           |
| 振动电机-B            | 15 (D15)              | PA0           |
| 蜂鸣器                | 16 (D16)              | PB2           |
| KEY0                  | 17 (D17)              | PD10          |
| KEY1                  | 18 (D18)              | PD9           |
| KEY2                  | 19 (D19)              | PD8           |
| KEY-WKUP              | 20 (D20)              | PC13          |
| 红LED                 | 21 (D21)              | PE7           |
| 绿LED，Arduino默认LED | 22 (D22, LED_BUILTIN) | PE8           |
| 蓝LED，具有PWM功能    | 23 (D23)              | PE9           |
| 红外发射              | 24 (D24)              | PB0           |
| 红外接收              | 25 (D25)              | PB1           |

## 3 I2C总线

潘多拉Arduino支持三条I2C总线，分别是：i2c1、i2c3 和 i2c4。你可以通过`pins_arduino.h`文件中的 `RTDUINO_DEFAULT_IIC_BUS_NAME` 宏来设定Arduino的I2C总线，**默认为 i2c4 总线**。其中：

- i2c1 为用户总线，PC7 为 SDA，PC6 为 SCL。用户可以通过杜邦线连接其他 I2C 传感器/芯片。
- i2c3 为板载 I2C 外设总线，连接板载 ICM20608（陀螺仪和加速度传感器） 和 AP3216C（距离和光亮度传感器） 芯片
- i2c4 为板载 I2C 外设总线，连接板载 AHT10（温湿度传感器） 芯片

I2C的引脚都是被RT-Thread I2C设备框架接管的，不需要直接操控这两个引脚，直接引用`#include <Wire.h>`（Arduino官方I2C头文件）即可使用。

## 4 SPI总线

潘多拉板的Arduino SPI总线是spi2总线，位置为板上左上角的`WIRELESS`插槽。 `SCK`、`MISO`、`MOSI`引脚是被RT-Thread SPI设备框架接管的，不需要直接操控这3个引脚，直接引用`#include <SPI.h>`（Arduino官方SPI头文件）即可使用。按照Arduino的编程标准，用户需要自行控制片选信号。

## 5 特殊功能说明

### 5.1 芯片内部ADC通道

本BSP适配了STM32的两个芯片内部ADC通道，可以通过 analogRead 函数来分别获取如下功能：

| 特殊功能             | Arduino引脚编号 | STM32引脚编号 |
| -------------------- | --------------- | ------------- |
| 芯片内部参考电压 ADC | A2              | --            |
| 芯片内部温度 ADC     | A3              | --            |

### 5.2 真模拟输出功能 (True Analog Output)

Arduino的 analogWrite 函数虽为模拟写，但是实际输出的是PWM数字信号，并非真正的模拟信号。这是由于Arduino早期使用的AVR单片机并不支持DAC的功能，因此这个习惯就被保留了下来。但是随着Arduino支持芯片的丰富，部分高级芯片已经内建了DAC（例如Arduino官方板MKR、Zero等），因此Arduino的 analogWrite 函数后续也支持了真模拟输出功能。

| 特殊功能                        | Arduino引脚编号 | STM32引脚编号 |
| ------------------------------- | --------------- | ------------- |
| 真模拟输出 (True Analog Output) | DAC0            | PA4           |

在潘多拉板上，使用PA4来当做真模拟输出功能引脚，使用方法为：

```c
analogWrite(DAC0, 1024); // STM32的DAC分辨率为12位，因此第二个参数范围可以为0-4095
```
