# STM32L475潘多拉的Arduino生态兼容说明

## 1 RTduino - RT-Thread的Arduino生态兼容层

STM32L475潘多拉已经完整适配了[RTduino软件包](https://github.com/RTduino/RTduino)，即RT-Thread的Arduino生态兼容层。用户可以按照Arduino的编程习惯来操作该BSP，并且可以使用大量Arduino社区丰富的库，是对RT-Thread生态的极大增强。更多信息，请参见[RTduino软件包说明文档](https://github.com/RTduino/RTduino)。

### 1.1 如何开启针对本BSP的Arduino生态兼容层

Env 工具下敲入 menuconfig 命令，或者 RT-Thread Studio IDE 下选择 RT-Thread Settings：

```Kconfig
Hardware Drivers Config --->
    Onboard Peripheral Drivers --->
        [*] Compatible with Arduino Ecosystem (RTduino)
```

## 2 Arduino引脚排布

该BSP遵照Arduino UNO板的引脚排列方式，并扩展增加了潘多拉自身的板载资源功能引脚。详见 `pins_arduino.c`

### 2.1 Arduino引脚排布统览

更多引脚布局相关信息参见 [pins_arduino.c](pins_arduino.c) 和 [pins_arduino.h](pins_arduino.h)。

| Arduino引脚编号           | STM32引脚编号 | 5V容忍    | 备注                                           |
| --------------------- | --------- | ------- | -------------------------------------------- |
| 0 (D0)                | PA10      | 是       | Serial-Rx，被RT-Thread的UART设备框架uart1接管         |
| 1 (D1)                | PA9       | 是       | Serial-Tx，被RT-Thread的UART设备框架uart1接管         |
| 2 (D2)                | PB9       | 是       | 普通IO                                         |
| 3 (D3)                | PD15      | 是       | PWM4-CH4，默认被RT-Thread的PWM设备框架pwm4接管          |
| 4 (D4)                | PA8       | 是       | 普通IO                                         |
| 5 (D5)                | PD14      | 是       | 普通IO                                         |
| 6 (D6)                | PB11      | 是       | PWM2-CH4，默认被RT-Thread的PWM设备框架pwm2接管          |
| 7 (D7)                | PB14      | 是       | 普通IO                                         |
| 8 (D8)                | PB12      | 是       | 普通IO                                         |
| 9 (D9)                | PD12      | 是       | PWM4-CH1，默认被RT-Thread的PWM设备框架pwm4接管          |
| 10 (D10)              | PB10      | 是       | PWM2-CH3，默认被RT-Thread的PWM设备框架pwm2接管          |
| 11 (D11)              | PB8       | 是       | PWM4-CH3，默认被RT-Thread的PWM设备框架pwm4接管          |
| 12 (D12)              | PB15      | 是       | 普通IO                                         |
| 13 (D13)              | PB13      | 是       | 普通IO                                         |
| 14 (D14)              | PA1       | 是       | 振动电机-A                                       |
| 15 (D15)              | PA0       | 是       | 振动电机-B                                       |
| 16 (D16)              | PB2       | 是       | 蜂鸣器                                          |
| 17 (D17)              | PD10      | 是       | KEY0                                         |
| 18 (D18)              | PD9       | 是       | KEY1                                         |
| 19 (D19)              | PD8       | 是       | KEY2                                         |
| 20 (D20)              | PC13      | 是       | KEY-WKUP                                     |
| 21 (D21)              | PE7       | 是       | 用户红色LED                                      |
| 22 (D22, LED_BUILTIN) | PE8       | 是       | 用户绿色LED                                      |
| 23 (D23)              | PE9       | 是       | 用户蓝色LED，PWM1-CH1，默认被RT-Thread的PWM设备框架pwm1接管  |
| 24 (D24)              | PB0       | 3.6V容忍  | 红外发送                                         |
| 25 (D25)              | PB1       | 是       | 红外接收                                         |
| 26 (D26)              | PD4       | 是       | 无线模块 CE                                      |
| 27 (D27)              | PD3       | 是       | 无线模块 中断                                      |
| 28 (D28, SS)          | PD5       | 是       | 无线模块 片选 CS                                   |
| 29 (D29)              | PB13      |         | SPI2-SCK，默认被RT-Thread的SPI设备框架spi2总线接管        |
| 30 (D30)              | PB14      |         | SPI2-MISO，默认被RT-Thread的SPI设备框架spi2总线接管       |
| 31 (D31)              | PB15      |         | SPI2-MOSI，默认被RT-Thread的SPI设备框架spi2总线接管       |
| 32 (D32)              | PC7       | 是       | I2C1-SDA，默认被RT-Thread的I2C设备框架i2c1总线接管        |
| 33 (D33)              | PC6       | 是       | I2C1-SCL，默认被RT-Thread的I2C设备框架i2c1总线接管        |
| 34 (D34)              | PA2       |         | Serial2-Tx，默认被RT-Thread的UART设备框架uart2接管      |
| 35 (D35)              | PA3       |         | Serial2-Rx，默认被RT-Thread的UART设备框架uart2接管      |
| 36 (D36)              | PD7       | 是       | LCD 片选 CS                                    |
| 37 (D37)              | PB6       | 是       | LCD 复位 RESET                                 |
| 38 (D38)              | PB4       | 是       | LCD D/C 数据命令选择 即RW读写选择                       |
| 39 (D39)              | PB7       | 是       | LCD 背光电源，PWM4-CH2，默认被RT-Thread的PWM设备框架pwm4接管 |
| A0                    | PC2       | 是（但不建议） | ADC1-CH3，默认被RT-Thread的ADC设备框架adc1接管          |
| A1                    | PC4       | 是（但不建议） | ADC1-CH13，默认被RT-Thread的ADC设备框架adc1接管         |
| A2                    | --        |         | 芯片内部参考电压 ADC1-CH0，默认被RT-Thread的ADC设备框架adc1接管 |
| A3                    | --        |         | 芯片内部温度 ADC1-CH17，默认被RT-Thread的ADC设备框架adc1接管  |
| DAC0                  | PA4       | 3.6V容忍  | 真模拟输出 DAC1-CH1，默认被RT-Thread的DAC设备框架dac1接管    |

> 注意：
> 
> 1. 驱动舵机和analogWrite函数要选择不同定时器发生的PWM信号引脚，由于STM32的定时器4个通道需要保持相同的频率，如果采用相同的定时器发生的PWM分别驱动舵机和analogWrite，可能会导致舵机失效。

### 2.2 板载排针的Arduino引脚排布

| STM32引脚编号 | Arduino引脚编号 | 备注       | STM32引脚编号 | Arduino引脚编号 | 备注       |
| --------- | ----------- | -------- | --------- | ----------- | -------- |
| PB8       | 11 (D11)    | PWM      | PB9       | 2 (D2)      | 普通IO     |
| PC7       | A4          | I2C1-SDA | PA8       | 4 (D4)      | 普通IO     |
| PD15      | 3 (D3)      | PWM      | PC6       | A5          | I2C1-SCL |
| PD13      | --          | --       | PD14      | 5 (D5)      | 普通IO     |
| PC2       | A0          | ADC      | PD12      | 9 (D9)      | PWM      |
| PB14      | 7 (D7)      | 普通IO     | PB15      | 12 (D12)    | 普通IO     |
| PB12      | 8 (D8)      | 普通IO     | PB13      | 13 (D13)    | 普通IO     |
| PB10      | 10 (D10)    | PWM      | PB11      | 6 (D6)      | PWM      |
| PC4       | A1          | ADC      | PA4       | DAC0        | DAC      |

### 2.3 板载外设的Arduino引脚排布

| 外设名称              | Arduino引脚编号           | STM32引脚编号 |
| ----------------- | --------------------- | --------- |
| 振动电机-A            | 14 (D14)              | PA1       |
| 振动电机-B            | 15 (D15)              | PA0       |
| 蜂鸣器               | 16 (D16)              | PB2       |
| KEY0              | 17 (D17)              | PD10      |
| KEY1              | 18 (D18)              | PD9       |
| KEY2              | 19 (D19)              | PD8       |
| KEY-WKUP          | 20 (D20)              | PC13      |
| 红LED              | 21 (D21)              | PE7       |
| 绿LED，Arduino默认LED | 22 (D22, LED_BUILTIN) | PE8       |
| 蓝LED，具有PWM功能      | 23 (D23)              | PE9       |
| 红外发射              | 24 (D24)              | PB0       |
| 红外接收              | 25 (D25)              | PB1       |

## 3 通信

### 3.1 I2C总线

潘多拉Arduino支持三条I2C总线，分别是：i2c1、i2c3 和 i2c4。你可以通过`pins_arduino.h`文件中的 `RTDUINO_DEFAULT_IIC_BUS_NAME` 宏来设定Arduino的I2C总线，**默认为 i2c4 总线**。其中：

- i2c1 为用户总线，PC7 为 SDA，PC6 为 SCL。用户可以通过杜邦线连接其他 I2C 传感器/芯片。
- i2c3 为板载 I2C 外设总线，连接板载 ICM20608（陀螺仪和加速度传感器） 和 AP3216C（距离和光亮度传感器） 芯片
- i2c4 为板载 I2C 外设总线，连接板载 AHT10（温湿度传感器） 芯片

I2C的引脚都是被RT-Thread I2C设备框架接管的，不需要直接操控这两个引脚，直接引用`#include <Wire.h>`（Arduino官方I2C头文件）即可使用。

### 3.2 SPI总线

潘多拉板的Arduino SPI总线是spi2总线，位置为板上左上角的`WIRELESS`插槽。 `SCK`、`MISO`、`MOSI`引脚是被RT-Thread SPI设备框架接管的，不需要直接操控这3个引脚，直接引用`#include <SPI.h>`（Arduino官方SPI头文件）即可使用。按照Arduino的编程标准，用户需要自行控制片选信号，默认为 `SS`, 即 `D28`。

### 3.3 串口

默认支持通过 `Serial.` 方法调用 `uart1` 串口设备；通过 `Serial2.` 方法调用 `uart2` 串口设备。详见[例程](https://github.com/RTduino/RTduino/blob/master/examples/Basic/helloworld.cpp)。

### 3.4 USB虚拟串口

支持USB虚拟串口，如果需要使用，可以手动使能。详见[例程](https://github.com/RTduino/RTduino/tree/master/examples/USBSerial)。

```Kconfig
RT-Thread online packages --->
    Arduino libraries --->
        [*] RTduino: Arduino Ecological Compatibility Layer
            [*] Enable USB Serial
```

## 4 特殊功能说明

### 4.1 芯片内部ADC通道

本BSP适配了STM32的两个芯片内部ADC通道，可以通过 analogRead 函数来分别获取如下功能：

| 特殊功能         | Arduino引脚编号 | STM32引脚编号 |
| ------------ | ----------- | --------- |
| 芯片内部参考电压 ADC | A2          | --        |
| 芯片内部温度 ADC   | A3          | --        |

### 4.2 真模拟输出功能 (True Analog Output)

Arduino的 analogWrite 函数虽为模拟写，但是实际输出的是PWM数字信号，并非真正的模拟信号。这是由于Arduino早期使用的AVR单片机并不支持DAC的功能，因此这个习惯就被保留了下来。但是随着Arduino支持芯片的丰富，部分高级芯片已经内建了DAC（例如Arduino官方板MKR、Zero等），因此Arduino的 analogWrite 函数后续也支持了真模拟输出功能。

| 特殊功能                       | Arduino引脚编号 | STM32引脚编号 |
| -------------------------- | ----------- | --------- |
| 真模拟输出 (True Analog Output) | DAC0        | PA4       |

在潘多拉板上，使用PA4来当做真模拟输出功能引脚，使用方法为：

```c
analogWrite(DAC0, 128);
```
