/**
 * \file
 *
 * \brief SAM Brown Out Detector Driver
 *
 * Copyright (C) 2015 Atmel Corporation. All rights reserved.
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
#include "bod.h"

/**
 * \brief Configure a Brown Out Detector module.
 *
 * Configures a given BOD module with the settings stored in the given
 * configuration structure.
 *
 * \param[in] conf     Configuration settings to use for the specified BODVDD
 *
 * \retval STATUS_OK                  Operation completed successfully
 * \retval STATUS_ERR_INVALID_ARG     An invalid BOD was supplied
 * \retval STATUS_ERR_INVALID_OPTION  The requested BOD level was outside the acceptable range
 */
enum status_code bodvdd_set_config(
		struct bodvdd_config *const conf)
{
	/* Sanity check arguments */
	Assert(conf);

	uint32_t temp = 0;

	/* Check if module is enabled. */
	if (SUPC->BODVDD.reg & SUPC_BODVDD_ENABLE) {
		SUPC->BODVDD.reg &= ~SUPC_BODVDD_ENABLE;
	}

	/* Convert BOD prescaler, trigger action and mode to a bitmask */
	temp |= (uint32_t)conf->prescaler | (uint32_t)conf->action |
			(uint32_t)conf->mode_in_active | (uint32_t)conf->mode_in_standby;

	if (conf->hysteresis == true) {
		temp |= SUPC_BODVDD_HYST;
	}

	if (conf->run_in_standby == true) {
		temp |= SUPC_BODVDD_RUNSTDBY;
	}

	if (conf->level > 0x3F) {
		return STATUS_ERR_INVALID_ARG;
	}

	SUPC->BODVDD.reg = SUPC_BODVDD_LEVEL(conf->level) | temp;

	return STATUS_OK;
}
