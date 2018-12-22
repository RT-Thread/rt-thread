/**
 * \file
 *
 * \brief SAM Brown Out Detector Driver
 *
 * Copyright (C) 2014-2015 Atmel Corporation. All rights reserved.
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
 * \param[in] conf     Configuration settings to use for the specified BOD33
 *
 * \retval STATUS_OK                  Operation completed successfully
 * \retval STATUS_ERR_INVALID_ARG     An invalid BOD was supplied
 * \retval STATUS_ERR_INVALID_OPTION  The requested BOD level was outside the acceptable range
 */
enum status_code bod33_set_config(
		struct bod33_config *const conf)
{
	/* Sanity check arguments */
	Assert(conf);

	uint32_t temp = 0;

	/* Check if module is enabled. */
	if (SUPC->BOD33.reg & SUPC_BOD33_ENABLE) {
		SUPC->BOD33.reg &= ~SUPC_BOD33_ENABLE;
	}

	/* Convert BOD prescaler, trigger action and mode to a bitmask */
	temp |= (uint32_t)conf->prescaler | (uint32_t)conf->action | (uint32_t)conf->monitor |
			(uint32_t)conf->mode_in_active | (uint32_t)conf->mode_in_standby;

	if (conf->hysteresis == true) {
		temp |= SUPC_BOD33_HYST;
	}

	if (conf->run_in_standby == true) {
		temp |= SUPC_BOD33_RUNSTDBY;
	}

	if (conf->run_in_backup == true) {
		temp |= SUPC_BOD33_RUNBKUP;
	}

	if (conf->level > 0x3F || conf->backuplevel > 0x3F) {
		return STATUS_ERR_INVALID_ARG;
	}

	SUPC->BOD33.reg = SUPC_BOD33_LEVEL(conf->level) |
			SUPC_BOD33_BKUPLEVEL(conf->backuplevel) | temp;

	return STATUS_OK;
}

/**
 * \brief Configure a Brown Out Detector module.
 *
 * Configures a given BOD module with the settings stored in the given
 * configuration structure.
 *
 * \param[in] conf     Configuration settings to use for the specified BOD12
 *
 * \retval STATUS_OK                  Operation completed successfully
 * \retval STATUS_ERR_INVALID_ARG     An invalid BOD was supplied
 * \retval STATUS_ERR_INVALID_OPTION  The requested BOD level was outside the acceptable range
 */
enum status_code bod12_set_config(
		struct bod12_config *const conf)
{
	/* Sanity check arguments */
	Assert(conf);

	uint32_t temp = 0;

	/* Check if module is enabled. */
	if (SUPC->BOD12.reg & SUPC_BOD12_ENABLE) {
		SUPC->BOD12.reg &= ~SUPC_BOD12_ENABLE;
	}

/* Convert BOD prescaler, trigger action and mode to a bitmask */
	temp |= (uint32_t)conf->prescaler | (uint32_t)conf->action |
			(uint32_t)conf->mode_in_active | (uint32_t)conf->mode_in_standby;

	if (conf->hysteresis == true) {
		temp |= SUPC_BOD12_HYST;
	}

	if (conf->run_in_standby == true) {
		temp |= SUPC_BOD12_RUNSTDBY;
	}

	if (conf->level > 0x3F) {
		return STATUS_ERR_INVALID_ARG;
	}

	SUPC->BOD12.reg = SUPC_BOD12_LEVEL(conf->level) | temp;

	return STATUS_OK;
}