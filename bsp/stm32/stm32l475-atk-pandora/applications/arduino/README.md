## 1 潘多拉板载排针的Arduino引脚布局

| STM32引脚编号 | Arduino引脚编号 | 备注     | STM32引脚编号 | Arduino引脚编号 | 备注     |
| ------------- | --------------- | -------- | ------------- | --------------- | -------- |
| PB8           | 11 (D11)        | PWM      | PB9           | 2 (D2)          |          |
| PC7           | A4              | I2C1-SDA | PA8           | 4 (D4)          |          |
| PD15          | 3 (D3)          | PWM      | PC6           | A5              | I2C1-SCL |
| PD13          |                 |          | PD14          | 5 (D5)          |          |
| PC2           | A0              | ADC      | PD12          | 9 (D9)          | PWM      |
| PB14          | 7 (D7)          |          | PB15          | 12 (D12)        |          |
| PB12          | 8 (D8)          |          | PB13          | 13 (D13)        |          |
| PB10          | 10 (D10)        | PWM      | PB11          | 6 (D6)          | PWM      |
| PC4           | A1              | ADC      | PA4           | DAC0            | DAC      |

## 2 潘多拉板载外设的Arduino引脚布局

| 外设名称           | Arduino引脚编号       | STM32引脚编号 |
| ------------------ | --------------------- | ------------- |
| 振动电机-A         | 14 (D14)              | PA1           |
| 振动电机-B         | 15 (D15)              | PA0           |
| 蜂鸣器             | 16 (D16)              | PB2           |
| KEY0               | 17 (D17)              | PD10          |
| KEY1               | 18 (D18)              | PD9           |
| KEY2               | 19 (D19)              | PD8           |
| KEY-WKUP           | 20 (D20)              | PC13          |
| 红LED              | 21 (D21)              | PE7           |
| 绿LED，默认LED     | 22 (D22, LED_BUILTIN) | PE8           |
| 蓝LED，具有PWM能力 | 23 (D23)              | PE9           |

## 3 I2C总线

潘多拉Arduino支持三条I2C总线，分别是：i2c1、i2c3 和 i2c4。你可以通过`pins_arduino.h`文件中的 `ARDUINO_DEFAULT_IIC_BUS_NAME` 宏来设定Arduino的I2C总线，**默认为 i2c4 总线**。其中：

- i2c1 为用户总线，PC7 为 SDA，PC6 为 SCL。用户可以通过杜邦线连接其他 I2C 传感器/芯片。
- i2c3 为板载 I2C 外设总线，连接板载 ICM20608（陀螺仪和加速度传感器） 和 AP3216C（距离和光亮度传感器） 芯片
- i2c4 为板载 I2C 外设总线，连接板载 AHT10（温湿度传感器） 芯片

## 4 特殊功能说明

### 4.1 芯片内部ADC通道

本BSP适配了STM32的两个芯片内部ADC通道，可以通过 analogRead 函数来分别获取如下功能：

| 特殊功能             | Arduino引脚编号 | STM32引脚编号 |
| -------------------- | --------------- | ------------- |
| 芯片内部参考电压 ADC | A2              | --            |
| 芯片内部温度 ADC     | A3              | --            |

### 4.2 真模拟输出功能 (True Analog Output)

Arduino的 analogWrite 函数虽为模拟写，但是实际输出的是PWM数字信号，并非真正的模拟信号。这是由于Arduino早期使用的AVR单片机并不支持DAC的功能，因此这个习惯就被保留了下来。但是随着Arduino支持芯片的丰富，部分高级芯片已经内建了DAC（例如Arduino官方板MKR、Zero等），因此Arduino的 analogWrite 函数后续也支持了真模拟输出功能。

在潘多拉板上，使用PA4来当做真模拟输出功能引脚，使用方法为：

```c
analogWrite(DAC0, 1024); // STM32的DAC分辨率为12位，因此第二个参数范围可以为0-4095
```

