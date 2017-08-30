/**
 * \file
 *
 * \brief AT25DFx configuration.
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

#ifndef CONF_AT25DFX_H_INCLUDED
#define CONF_AT25DFX_H_INCLUDED

#include <board.h>
#include "at25dfx.h"

//! Select the SPI module AT25DFx is connected to
#define AT25DFX_SPI                 SERIALFLASH_SPI_MODULE

/** AT25DFx device type */
#define AT25DFX_MEM_TYPE            AT25DFX_081A

#define AT25DFX_SPI_PINMUX_SETTING  SERIALFLASH_SPI_MUX_SETTING
#define AT25DFX_SPI_PINMUX_PAD0     SERIALFLASH_SPI_PINMUX_PAD0
#define AT25DFX_SPI_PINMUX_PAD1     SERIALFLASH_SPI_PINMUX_PAD1
#define AT25DFX_SPI_PINMUX_PAD2     SERIALFLASH_SPI_PINMUX_PAD2
#define AT25DFX_SPI_PINMUX_PAD3     SERIALFLASH_SPI_PINMUX_PAD3

#define AT25DFX_CS                  SERIALFLASH_SPI_CS 

//! SPI master speed in Hz.
#define AT25DFX_CLOCK_SPEED         1000000

#endif  /* CONF_AT25DFX_H_INCLUDED */
