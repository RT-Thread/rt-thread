/**
 * \file
 *
 * \brief SAM Temperature Sensor (TSENS) Driver
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

#include "tsens.h"

#define WINDOW_MIN_VALUE    -40
#define WINDOW_MAX_VALUE    105

/**
 * \internal Writes an TSENS configuration to the hardware module
 *
 * Writes out a given TSENS module configuration to the hardware module.
 *
 * \param[in]  config       Pointer to configuration struct
 *
 * \return Status of the configuration procedure.
 * \retval STATUS_OK               The configuration was successful
 * \retval STATUS_ERR_INVALID_ARG  Invalid argument(s) were provided
 */
static enum status_code _tsens_set_config(struct tsens_config *const config)
{
	/* Configure GCLK channel and enable clock */
	struct system_gclk_chan_config gclk_chan_conf;
	system_gclk_chan_get_config_defaults(&gclk_chan_conf);
	gclk_chan_conf.source_generator = config->clock_source;
	system_gclk_chan_set_config(TSENS_GCLK_ID, &gclk_chan_conf);
	system_gclk_chan_enable(TSENS_GCLK_ID);

	/* Configure run in standby */
	TSENS->CTRLA.reg = (config->run_in_standby << TSENS_CTRLA_RUNSTDBY_Pos);

	/* Check validity of window thresholds */
	if (config->window.window_mode != TSENS_WINDOW_MODE_DISABLE) {
		if((config->window.window_lower_value < WINDOW_MIN_VALUE) || \
			(config->window.window_upper_value > WINDOW_MAX_VALUE)) {
				return STATUS_ERR_INVALID_ARG;
			}
	}

	/* Configure CTRLC */
	TSENS->CTRLC.reg =
			(config->free_running << TSENS_CTRLC_FREERUN_Pos) | \
			(config->window.window_mode);

#if ERRATA_14476
	/* Configure lower threshold */
	TSENS->WINLT.reg = TSENS_WINLT_WINLT(config->window.window_upper_value);

	/* Configure upper threshold */
	TSENS->WINUT.reg = TSENS_WINLT_WINLT(config->window.window_lower_value);
#else
	/* Configure lower threshold */
	TSENS->WINLT.reg = TSENS_WINLT_WINLT(config->window.window_lower_value);

	/* Configure upper threshold */
	TSENS->WINUT.reg = TSENS_WINLT_WINLT(config->window.window_upper_value);
#endif

	/* Configure events */
	TSENS->EVCTRL.reg = config->event_action;

	/* Disable all interrupts */
	TSENS->INTENCLR.reg =
			(1 << TSENS_INTENCLR_OVF_Pos) | (1 << TSENS_INTENCLR_WINMON_Pos) | \
			(1 << TSENS_INTENCLR_OVERRUN_Pos) | (1 << TSENS_INTENCLR_RESRDY_Pos);

	/* Read calibration from NVM */
	uint32_t tsens_bits = *((uint32_t *)NVMCTRL_TEMP_LOG);
	uint32_t tsens_tcal = \
				((tsens_bits & TSENS_FUSES_TCAL_Msk) >> TSENS_FUSES_TCAL_Pos);
	uint32_t tsens_fcal = \
				((tsens_bits & TSENS_FUSES_FCAL_Msk) >> TSENS_FUSES_FCAL_Pos);

	TSENS->CAL.reg = TSENS_CAL_TCAL(tsens_tcal) | TSENS_CAL_FCAL(tsens_fcal);
	TSENS->GAIN.reg = TSENS_GAIN_GAIN(config->calibration.gain);
	TSENS->OFFSET.reg = TSENS_OFFSET_OFFSETC(config->calibration.offset);

	return STATUS_OK;
}

/**
 * \brief Initializes the TSENS.
 *
 * Initializes the TSENS device struct and the hardware module based on the
 * given configuration struct values.
 *
 * \param[in]  config      Pointer to the configuration struct
 *
 * \return Status of the initialization procedure.
 * \retval STATUS_OK                The initialization was successful
 * \retval STATUS_ERR_INVALID_ARG   Invalid argument(s) were provided
 * \retval STATUS_BUSY              The module is busy with a reset operation
 * \retval STATUS_ERR_DENIED        The module is enabled
 */
enum status_code tsens_init(struct tsens_config *config)
{
	/* Sanity check arguments */
	Assert(config);

	/* Turn on the digital interface clock */
	system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBA, MCLK_APBAMASK_TSENS);

	if (TSENS->CTRLA.reg & TSENS_CTRLA_SWRST) {
		/* We are in the middle of a reset. Abort. */
		return STATUS_BUSY;
	}

	if (TSENS->CTRLA.reg & TSENS_CTRLA_ENABLE) {
		/* Module must be disabled before initialization. Abort. */
		return STATUS_ERR_DENIED;
	}

	/* Write configuration to module */
	return _tsens_set_config(config);
}

/**
 * \brief Initializes an TSENS configuration structure to defaults.
 *
 * Initializes a given TSENS configuration struct to a set of known default
 * values. This function should be called on any new instance of the
 * configuration struct before being modified by the user application.
 *
 * The default configuration is as follows:
 *  \li GCLK generator 0 (GCLK main) clock source
 *  \li All events (input and generation) disabled
 *  \li Free running disabled
 *  \li Run in standby disabled
 *  \li Window monitor disabled
 *  \li Register GAIN value
 *  \li Register OFFSET value
 *
 * \note Register GAIN and OFFSET is loaded from NVM, or can also be fixed.
 * If this bitfield is to be fixed, pay attention to the relationship between GCLK
 * frequency, GAIN, and resolution. See \ref asfdoc_sam0_tsens_module_overview
 * "Chapter Module Overview".
 *
 * \param[out] config  Pointer to configuration struct to initialize to
 *                     default values
 */
void tsens_get_config_defaults(struct tsens_config *const config)
{
	Assert(config);
	config->clock_source                  = GCLK_GENERATOR_0;
	config->free_running                  = false;
	config->run_in_standby                = false;
	config->window.window_mode            = TSENS_WINDOW_MODE_DISABLE;
	config->window.window_upper_value     = 0;
	config->window.window_lower_value     = 0;
	config->event_action                  = TSENS_EVENT_ACTION_DISABLED;

	uint32_t tsens_bits[2];
	tsens_bits[0] = *((uint32_t *)NVMCTRL_TEMP_LOG);
	tsens_bits[1] = *(((uint32_t *)NVMCTRL_TEMP_LOG) + 1);
	config->calibration.offset   = \
		((tsens_bits[0] & TSENS_FUSES_OFFSET_Msk) >> TSENS_FUSES_OFFSET_Pos);
	config->calibration.gain     = \
		((tsens_bits[0] & TSENS_FUSES_GAIN_0_Msk) >> TSENS_FUSES_GAIN_0_Pos) | \
		((tsens_bits[1] & TSENS_FUSES_GAIN_1_Msk) >> TSENS_FUSES_GAIN_1_Pos);
}

/**
 * \brief Reads the TSENS result.
 *
 * Reads the result from a TSENS conversion that was previously started.
 *
 * \param[out] result       Pointer to store the result value in
 *
 * \return Status of the TSENS read request.
 * \retval STATUS_OK           The result was retrieved successfully
 * \retval STATUS_BUSY         A conversion result was not ready
 * \retval STATUS_ERR_OVERFLOW The result register has been overwritten by the
 *                             TSENS module before the result was read by the software
 */
enum status_code tsens_read(int32_t *result)
{
	Assert(result);

	if (!(tsens_get_status() & TSENS_STATUS_RESULT_READY)) {
		/* Result not ready */
		return STATUS_BUSY;
	}

	if (TSENS->STATUS.reg & TSENS_STATUS_OVF) {
		/* The result is not valid */
		return STATUS_ERR_BAD_DATA;
	}

	/* Get TSENS result */
	uint32_t temp = TSENS->VALUE.reg;
	if(temp & 0x00800000) {
		temp |= ~TSENS_VALUE_MASK;
	}
#if (ERRATA_14476)
	*result = temp * (-1);
#endif

	/* Reset ready flag */
	tsens_clear_status(TSENS_STATUS_RESULT_READY);

	if (tsens_get_status() & TSENS_STATUS_OVERRUN) {
		tsens_clear_status(TSENS_STATUS_OVERRUN);
		return STATUS_ERR_OVERFLOW;
	}

	return STATUS_OK;
}
