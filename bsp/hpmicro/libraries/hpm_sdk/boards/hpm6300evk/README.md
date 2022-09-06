# HPM6300EVK


::::{important}
:::{note}
Need to supplement the content of each module
:::
::::

## Overview

version
Board overall
Board overall hpm6300evk

- Console serial port parameters:

  - Baud rate: 115200
  - Data bits: 8 bits
  - Check Digit: None
  - Stop bit: 1
  - Flow Control Bits: None
  - Data encoding method: ASCII

## DIP Switch S1

- Bit 1 and 2 controls boot mode

| bit[2:1] | Description                  |
| -------- | ---------------------------- |
| OFF, OFF | Boot from Quad SPI NOR flash |
| OFF, ON  | Serial boot                  |
| ON, OFF  | ISP                          |

(lab_hpm6300_evk_board)=
## Button

(lab_hpm6300_evk_board_buttons)=
| Function | Position |
| ---- | -------- |
|PBUTN (sw3) |Power Button, TinyUF2 Boot Button, GPIO Button |
|WBUTN (sw1) | WAKE UP Button |
|RESET (sw2) | Reset Button |

## Pin Description

- SPI Pin：

| Function | Position |
| ---- | -------- |
| SPI3.CSN    | J28[24] |
| SPI3.SCLK   | J28[23] |
| SPI3.MISO   | J28[21] |
| SPI3.MOSI   | J28[19] |

- I2C Pin：

| Function | Position |
| ---- | -------- |
| I2C0.SCL    | J28[13] |
| I2C0.SDA    | J28[15] |

- ACMP Pin

| Function | Position |
| ---- | -------- |
| CMP.INN5    | J26[7] |
| CMP.COMP_1  | J26[5] |

- GPTMR Pin

| Function | Position |
| ---- | -------- |
| GPTMR2.CAPT_2  | J28[40] |
| GPTMR2.COMP_2  | J28[35] |