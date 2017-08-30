/**
 * \file
 *
 * \brief AT25DFx SerialFlash driver public SPI HAL interface.
 *
 * Copyright (C) 2013-2015 Atmel Corporation. All rights reserved.
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

#ifndef AT25DFX_HAL_H
#define AT25DFX_HAL_H

#include <spi.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup asfdoc_common2_at25dfx_group
 *
 * @{
 */

/** Typedef for SPI HAL */
typedef struct spi_module at25dfx_spi_module_t;

/**
 * \brief Initialize SPI configuration
 *
 * This function initializes the SPI configuration struct with default settings
 * that should work with SerialFlash devices.
 *
 * The user can change the baud rate and the MUX settings for SERCOM and GPIO
 * pads, but should leave all other settings intact.
 *
 * \param[out] config Address of config struct to initialize.
 */
static inline void at25dfx_spi_get_config_defaults(
		struct spi_config *const config)
{
	spi_get_config_defaults(config);
}

/** @ */

#ifdef __cplusplus
}
#endif

#endif // AT25DFX_HAL_H