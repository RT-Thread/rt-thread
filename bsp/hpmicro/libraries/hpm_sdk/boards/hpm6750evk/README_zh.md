# HPM6750EVK开发板

## 概述

HPM6750是一款主频达816Mhz的双核微控制器。该芯片拥有最大2M字节的连续片上RAM，并集成了丰富的存储接口，如SDRAM，Quad SPI NOR flash， SD/eMMC卡。同时它也提供多种音视频接口包括LCD显示，像素DMA，摄像头以及I2S音频接口。

 ![hpm6750evk](../../doc/images/boards/hpm6750evk/hpm6750evk.png "hpm6750evk")

## 板上硬件资源

- HPM6750IVM 微控制器 (主频816Mhz, 2MB片上内存)
- 板载存储
  - 256Mb SDRAM
  - 128Mb Quad SPI NOR Flash
- 显示/摄像头
  - LCD接口
  - 摄像头(DVP)接口
- 以太网
  - 1000 Mbits PHY
  - 100 Mbits PHY
- USB
  - USB type C (USB 2.0 OTG) connector x3
- 音频
  - Line in
  - Mic
  - Speaker
  - DAO
- 其他
  - TF卡槽
  - FT2232
  - 蜂鸣器
  - RGB LED
  - CAN
- 扩展口
  - 电机控制

## 拨码开关 S1

- Bit 1，2控制启动模式

| Bit[2:1] | 功能描述                |
| -------- | ----------------------- |
| OFF, OFF | Quad SPI NOR flash 启动 |
| OFF, ON  | 串行启动                |
| ON, OFF  | 在系统编程              |

- Bit 3用于选择PWM或是千兆网口

| Bit3 | 功能描述 |
| ---- | -------- |
| OFF  | 千兆网口 |
| ON   | PWM      |

(lab_hpm6750_evk_board)=
## 按键

(lab_hpm6750_evk_board_buttons)=
| 名称 | 功能 |
| ---- | -------- |
|PBUTN (S2) | 电源按键, TinyUF2 Boot按键, GPIO 按键|
|WBUTN (S3) | WAKE UP 按键|
|RESET (S4) | Reset 按键|

## 引脚描述

- J12端子的 `P-UH 、P-UL`引脚为PWM输出引脚，如下图所示

  ![image-1](../../doc/images/boards/hpm6750evk/hpm6750evk_pwm_output_pin.png "image-1")

- SPI引脚：

| 功能 | 位置 |
| ---- | -------- |
| SPI2.CSN    | J20[6] |
| SPI2.SCLK   | J20[7] |
| SPI2.MISO   | J20[8] |
| SPI2.MOSI   | J20[9] |

- I2C引脚：

| 功能 | 位置 |
| ---- | -------- |
| I2C0.SCL    | J20[3] |
| I2C0.SDA    | J20[4] |

- CORE1调试串口引脚：

| 功能 | 位置 |
| ---- | -------- |
| UART13.TXD    | J20[5] |
| UART13.RXD    | J20[6] |

- ACMP引脚

| 功能 | 位置 |
| ---- | -------- |
| CMP.INN6    | J12[8] |
| CMP.COMP_1  | J12[6] |

- GPTMR引脚

| 功能 | 位置 |
| ---- | -------- |
| GPTMR4.CAPT_1  | J12[6] |
| GPTMR3.COMP_1  | J12[7] |


