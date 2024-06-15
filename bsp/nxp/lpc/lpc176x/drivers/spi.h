/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __LPC17XX_SPI_H__
#define __LPC17XX_SPI_H__

#include <stdint.h>
#include <stdbool.h>

// if not use FIFO,     R: 600kB/s, W: 500kB/s
// if     use FIFO,     R: 1.2MB/s, W: 800kB/s
#define USE_FIFO        1

/* bit-frequency = PCLK / (CPSDVSR * [SCR+1]), here SCR=0, PCLK=72MHz, must be even */
#define SPI_SPEED_20MHz     4   /* => 18MHz */
#define SPI_SPEED_25MHz     4   /* => 18MHz */
#define SPI_SPEED_400kHz  180   /* => 400kHz */

/* external functions */
void LPC17xx_SPI_Init (void);
void LPC17xx_SPI_DeInit( void );
void LPC17xx_SPI_Release (void);
void LPC17xx_SPI_SetSpeed (uint8_t speed);
void LPC17xx_SPI_Select (void);
void LPC17xx_SPI_DeSelect (void);
void LPC17xx_SPI_SendByte (uint8_t data);
uint8_t LPC17xx_SPI_RecvByte (void);

#if USE_FIFO
void LPC17xx_SPI_RecvBlock_FIFO (uint8_t *buff, uint32_t btr);
void LPC17xx_SPI_SendBlock_FIFO (const uint8_t *buff);
#endif

#endif  // __LPC17XX_SPI_H__
