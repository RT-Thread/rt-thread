/**
 * \file
 *
 * \brief SD/MMC stack configuration file.
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef CONF_SD_MMC_H_INCLUDED
#define CONF_SD_MMC_H_INCLUDED

/* Define to enable the SPI mode instead of Multimedia Card interface mode */
#define SD_MMC_SPI_MODE

/* Define to enable the SDIO support */
//#define SDIO_SUPPORT_ENABLE

/* Define to enable the debug trace to the current standard output (stdio) */
//#define SD_MMC_DEBUG

/* Define to memory count */
#define SD_MMC_SPI_MEM_CNT          1

/* Select the SPI module SD/MMC is connected to */
#ifdef EXT1_SPI_MODULE /* Default configuration for Xplained Pro kit */
#  define SD_MMC_SPI                 EXT1_SPI_MODULE
#  define SD_MMC_SPI_PINMUX_SETTING  EXT1_SPI_SERCOM_MUX_SETTING
#  define SD_MMC_SPI_PINMUX_PAD0     EXT1_SPI_SERCOM_PINMUX_PAD0
#  define SD_MMC_SPI_PINMUX_PAD1     EXT1_SPI_SERCOM_PINMUX_PAD1
#  define SD_MMC_SPI_PINMUX_PAD2     EXT1_SPI_SERCOM_PINMUX_PAD2
#  define SD_MMC_SPI_PINMUX_PAD3     EXT1_SPI_SERCOM_PINMUX_PAD3

#  define SD_MMC_CS                  EXT1_PIN_15

#  define SD_MMC_0_CD_GPIO           (EXT1_PIN_10)
#  define SD_MMC_0_CD_DETECT_VALUE   0
#else /* Dummy configuration */
#  define SD_MMC_SPI                 0
#  define SD_MMC_SPI_PINMUX_SETTING  0
#  define SD_MMC_SPI_PINMUX_PAD0     0
#  define SD_MMC_SPI_PINMUX_PAD1     0
#  define SD_MMC_SPI_PINMUX_PAD2     0
#  define SD_MMC_SPI_PINMUX_PAD3     0

#  define SD_MMC_CS                  0

#  define SD_MMC_0_CD_GPIO           0
#  define SD_MMC_0_CD_DETECT_VALUE   0
#endif

/* Define the SPI clock source */
#define SD_MMC_SPI_SOURCE_CLOCK    GCLK_GENERATOR_0

/* Define the SPI max clock */
#define SD_MMC_SPI_MAX_CLOCK       4000000

#endif /* CONF_SD_MMC_H_INCLUDED */

