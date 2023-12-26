# xxx 开发板的Arduino生态兼容说明

## 1 RTduino - RT-Thread的Arduino生态兼容层

xxx 开发板已经完整适配了[RTduino软件包](https://github.com/RTduino/RTduino)，即RT-Thread的Arduino生态兼容层。用户可以按照Arduino的编程习惯来操作该BSP，并且可以使用大量Arduino社区丰富的库，是对RT-Thread生态的极大增强。更多信息，请参见[RTduino软件包说明文档](https://github.com/RTduino/RTduino)。

### 1.1 如何开启针对本BSP的Arduino生态兼容层

Env 工具下敲入 menuconfig 命令，或者 RT-Thread Studio IDE 下选择 RT-Thread Settings：

```Kconfig
Hardware Drivers Config --->
    Onboard Peripheral Drivers --->
        [*] Compatible with Arduino Ecosystem (RTduino)
```

## 2 Arduino引脚排布

更多引脚布局相关信息参见 [pins_arduino.c](pins_arduino.c) 和 [pins_arduino.h](pins_arduino.h)。

![xxx-pinout](xxx-pinout.jpg)
| Arduino引脚编号  | STM32引脚编号 | 5V容忍 | 备注  |
| ------------------- | --------- | ---- | ------------------------------------------------------------------------- |
| 0 (D0) | P | 是/否 | Serial-TX，默认被RT-Thread的UART设备框架uart1接管 |
| 1 (D1) | P | 是/否 | Serial-RX，默认被RT-Thread的UART设备框架uart1接管 |
| 2 (D2) | P | 是/否 |  |
| 3 (D3) | P | 是/否 |  |
| 4 (D4) | P | 是/否 |  |
| 5 (D5) | P | 是/否 |  |
| 6 (D6) | P | 是/否 |  |
| 7 (D7) | P | 是/否 |  |
| 8 (D8) | P | 是/否 | Serial2-TX，默认被RT-Thread的UART设备框架uart2接管 |
| 9 (D9) | P | 是/否 | Serial2-RX，默认被RT-Thread的UART设备框架uart2接管 |
| 10 (D10) | P | 是/否 |  |
| 11 (D11) | P | 是/否 |  |
| 12 (D12) | P | 是/否 |  |
| 13 (D13) | P | 是/否 |  |
| 14 (D14) | P | 是/否 |  |
| 15 (D15) | P | 是/否 |  |
| 16 (D16) | P | 是/否 |  |
| 17 (D17) | P | 是/否 |  |
| 18 (D18) | P | 是/否 |  |
| 19 (D19) | P | 是/否 |  |
| 20 (D20) | P | 是/否 |  |
| 21 (D21) | P | 是/否 |  |
| 22 (D22) | P | 是/否 |  |
| 23 (D23) | P | 是/否 | 板载用户LED |
| 24 (D24) | P | 是/否 |  |
| 25 (D25) | P | 是/否 |  |

> 注意：
>
> 1. xxxxxxxxx
> 2. xxxxxxxxx
