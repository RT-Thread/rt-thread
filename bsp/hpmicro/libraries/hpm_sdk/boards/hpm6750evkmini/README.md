# HPM6750EVKMINI

## Overview

The HPM6750 is a dual-core flashless MCU running 816Mhz. It has a 2MB continuous on-chip ram. Also, it provides various memory interfaces, including SDRAM, Quad SPI NOR Flash, SD/eMMC. It integrates rich audio and video interfaces, including LCD, pixel DMA, camera， and I2S audio interfaces.

 ![hpm6750evkmini](../../doc/images/boards/hpm6750evkmini/hpm6750evkmini.png "hpm6750evkmini")
## Hardware
- HPM6750IVM MCU (816Mhz, 2MB OCRAM)
- Onboard Memory
  - 128Mb SDRAM
  - 64Mb Quad SPI NOR Flash
- Display & Camera
  - LCD connector
  - Camera (DVP)
- WiFi
  - RW007 over SPI
- USB
  - USB type C (USB 2.0 OTG) connector x2
- Audio
  - Mic
  - DAO
- Others
  - TF Slot
  - FT2232
  - Beeper
  - RGB LED
- Expansion port
  - ART-PI extension port
## DIP Switch S1
- Bit 1 and 2 controls boot mode

| bit[2:1] | Description|
|----------|------------|
|OFF, OFF| Boot from Quad SPI NOR flash |
|OFF, ON| Serial boot |
|ON, OFF| ISP |

(lab_hpm6750_evkmini_board)=
## Button
(lab_hpm6750_evkmini_board_buttons)=
| Name | FUNCTIONS |
|----------|------------|
|PBUTN (S2) | Power Button, TinyUF2 Boot Button, GPIO Button |
|WBUTN (S3) | WAKE UP Button |
|RESET (S4) | Reset Button |

## Pin Description


- SPI Pin

| Function | Position |
| ---- | -------- |
| SPI2.CSN    | P1[24] |
| SPI2.SCLK   | P1[23] |
| SPI2.MISO   | P1[21] |
| SPI2.MOSI   | P1[19] |

- I2C Pin：

| Function | Position |
| ---- | -------- |
| I2C0.SCL    | P1[13] |
| I2C0.SDA    | P1[15] |

- UART for core1 debug console：

| Function | Position |
| ---- | -------- |
| UART13.TXD    | P1[8] |
| UART13.RXD    | P1[10] |

- ACMP Pin

| Function | Position |
| ---- | -------- |
| CMP.INN6    | P2[11] |
| CMP.COMP_1  | P1[7] |

- GPTMR Pin

| Function | Position |
| ---- | -------- |
| GPTMR2.CAPT_2  | P2[15] |
| GPTMR2.COMP_2  | P2[19] |