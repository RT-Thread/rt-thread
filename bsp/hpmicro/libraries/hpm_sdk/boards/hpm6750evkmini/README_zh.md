# HPM6750EVKMINI开发板

## 概述
HPM6750是一款主频达816Mhz的双核微控制器。该芯片拥有最大2M字节的连续片上RAM，并集成了丰富的存储接口，如SDRAM，Quad SPI NOR flash， SD/eMMC卡。同时它也提供多种音视频接口包括LCD显示，像素DMA，摄像头以及I2S音频接口。

 ![hpm6750evkmini](../../doc/images/boards/hpm6750evkmini/hpm6750evkmini.png "hpm6750evkmini")
## 板上硬件资源
- HPM6750IVM 微控制器 (主频816Mhz, 2MB片上内存)
- 板载存储
  - 128Mb SDRAM
  - 64Mb Quad SPI NOR Flash
- 显示/摄像头
  - LCD接口
  - 摄像头(DVP)接口
- WiFi
  - RW007
- USB
  - USB type C (USB 2.0 OTG) connector x2
- 音频
  - Mic
  - DAO
- 其他
  - TF卡槽
  - FT2232
  - 蜂鸣器
  - RGB LED
- 扩展口
  - ART-PI
## 拨码开关 S1
- Bit 1，2控制启动模式

| Bit[2:1] | 功能描述|
|----------|------------|
|OFF, OFF| Quad SPI NOR flash 启动 |
|OFF, ON| 串行启动 |
|ON, OFF| 在系统编程 |

(lab_hpm6750_evkmini_board)=
## 按键
(lab_hpm6750_evkmini_board_buttons)=
| 名称 | 功能 |
|----------|------------|
|PBUTN (S2) | 电源按键, TinyUF2 Boot按键, GPIO 按键|
|WBUTN (S3) | WAKE UP 按键|
|RESET (S4) | Reset 按键|


## 引脚描述


- SPI引脚：

| 功能 | 位置 |
| ---- | -------- |
| SPI2.CSN    | P1[24] |
| SPI2.SCLK   | P1[23] |
| SPI2.MISO   | P1[21] |
| SPI2.MOSI   | P1[19] |

- I2C引脚：

| 功能 | 位置 |
| ---- | -------- |
| I2C0.SCL    | P1[13] |
| I2C0.SDA    | P1[15] |

- CORE1调试串口引脚：

| 功能 | 位置 |
| ---- | -------- |
| UART13.TXD    | P1[8] |
| UART13.RXD    | P1[10] |

- ACMP引脚

| 功能 | 位置 |
| ---- | -------- |
| CMP.INN6    | P2[11] |
| CMP.COMP_1  | P1[7] |

- GPTMR引脚

| 功能 | 位置 |
| ---- | -------- |
| GPTMR2.CAPT_2  | P2[15] |
| GPTMR2.COMP_2  | P2[19] |