/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// -----------------------------------------------------
// NOTE: THIS HEADER IS ALSO INCLUDED BY ASSEMBLER SO
//       SHOULD ONLY CONSIST OF PREPROCESSOR DIRECTIVES
// -----------------------------------------------------

#ifndef _BOARDS_VGABOARD_H
#define _BOARDS_VGABOARD_H

#ifndef PICO_DEFAULT_UART
#define PICO_DEFAULT_UART 1
#endif

#ifndef PICO_DEFAULT_UART_TX_PIN
#define PICO_DEFAULT_UART_TX_PIN 20
#endif

#ifndef PICO_DEFAULT_UART_RX_PIN
#define PICO_DEFAULT_UART_RX_PIN 21
#endif

#ifndef PICO_DEFAULT_LED_PIN
#define PICO_DEFAULT_LED_PIN 25 // same as Pico
#endif

// Audio pins. I2S BCK, LRCK are on the same pins as PWM L/R.
// - When outputting I2S, PWM sees BCK and LRCK, which should sound silent as
//   they are constant duty cycle, and above the filter cutoff
// - When outputting PWM, I2S DIN should be low, so I2S should remain silent.
#define VGABOARD_I2S_DIN_PIN 26
#define VGABOARD_I2S_BCK_PIN 27
#define VGABOARD_I2S_LRCK_PIN 28

#define VGABOARD_PWM_L_PIN 28
#define VGABOARD_PWM_R_PIN 27

#define VGABOARD_VGA_COLOR_PIN_BASE 0
#define VGABOARD_VGA_SYNC_PIN_BASE 16

// Note DAT2/3 are shared with UART TX/RX (pull jumpers off header to access
// UART pins and disconnect SD DAT2/3)
#define VGABOARD_SD_CLK_PIN 5
#define VGABOARD_SD_CMD_PIN 18
#define VGABOARD_SD_DAT0_PIN 19

// Note buttons are shared with VGA colour LSBs -- if using VGA, you can float
// the pin on VSYNC assertion and sample on VSYNC deassertion
#define VGABOARD_BUTTON_A_PIN 0
#define VGABOARD_BUTTON_B_PIN 6
#define VGABOARD_BUTTON_C_PIN 11

#ifndef PICO_SCANVIDEO_COLOR_PIN_BASE
#define PICO_SCANVIDEO_COLOR_PIN_BASE VGABOARD_VGA_COLOR_PIN_BASE
#endif

#ifndef PICO_SCANVIDEO_SYMC_PIN_BASE
#define PICO_SCANVIDEO_SYNC_PIN_BASE VGABOARD_VGA_SYNC_PIN_BASE
#endif

#ifndef PICO_SD_CLK_PIN
#define PICO_SD_CLK_PIN VGABOARD_SD_CLK_PIN
#endif

#ifndef PICO_SD_CMD_PIN
#define PICO_SD_CMD_PIN VGABOARD_SD_CMD_PIN
#endif

#ifndef PICO_SD_DAT0_PIN
#define PICO_SD_DAT0_PIN VGABOARD_SD_DAT0_PIN
#endif

#define PICO_AUDIO_I2S_DATA_PIN VGABOARD_I2S_DIN_PIN
#define PICO_AUDIO_I2S_CLOCK_PIN_BASE VGABOARD_I2S_BCK_PIN

#define PICO_AUDIO_PWM_L_PIN VGABOARD_PWM_L_PIN
#define PICO_AUDIO_PWM_R_PIN VGABOARD_PWM_R_PIN

#ifndef PICO_FLASH_SPI_CLKDIV
#define PICO_FLASH_SPI_CLKDIV 2
#endif

#ifndef PICO_FLASH_SIZE_BYTES
#define PICO_FLASH_SIZE_BYTES (2 * 1024 * 1024)
#endif

// Drive high to force power supply into PWM mode (lower ripple on 3V3 at light loads)
#define PICO_SMPS_MODE_PIN 23

#ifndef PICO_FLOAT_SUPPORT_ROM_V1
#define PICO_FLOAT_SUPPORT_ROM_V1 1
#endif

#ifndef PICO_DOUBLE_SUPPORT_ROM_V1
#define PICO_DOUBLE_SUPPORT_ROM_V1 1
#endif

#define PICO_VGA_BOARD

#endif
