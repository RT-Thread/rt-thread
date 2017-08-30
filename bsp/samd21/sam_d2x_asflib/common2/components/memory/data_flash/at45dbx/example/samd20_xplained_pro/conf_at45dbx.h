/**
 * \file
 *
 * \brief Example specific AT45DBX configuration file
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


#ifndef _CONF_AT45DBX_H_
#define _CONF_AT45DBX_H_

#include "at45dbx.h"
#include <board.h>

//! Select the SPI module AT45DBX is connected to
#define AT45DBX_SPI                 EXT2_SPI_MODULE

//! Size of AT45DBX data flash memories to manage.
#define AT45DBX_MEM_SIZE            AT45DBX_8MB

//! Number of AT45DBX components to manage.
#define AT45DBX_MEM_CNT             1

#define AT45DBX_SPI_PINMUX_SETTING  EXT2_SPI_SERCOM_MUX_SETTING
#define AT45DBX_SPI_PINMUX_PAD0     EXT2_SPI_SERCOM_PINMUX_PAD0
#define AT45DBX_SPI_PINMUX_PAD1     EXT2_SPI_SERCOM_PINMUX_PAD1
#define AT45DBX_SPI_PINMUX_PAD2     EXT2_SPI_SERCOM_PINMUX_PAD2
#define AT45DBX_SPI_PINMUX_PAD3     EXT2_SPI_SERCOM_PINMUX_PAD3

#define AT45DBX_CS                  EXT2_PIN_15

//! SPI master speed in Hz.
#define AT45DBX_CLOCK_SPEED         9600

#endif  // _CONF_AT45DBX_H_
