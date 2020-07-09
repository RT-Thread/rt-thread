/**
 * \file
 *
 * \brief SAM Frequency Meter (FREQM) Driver
 *
 * Copyright (C) 2015-2016 Atmel Corporation. All rights reserved.
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

#include "freqm.h"
#include <gclk.h>

#ifndef FREQM_GCLK_ID_REF
#define FREQM_GCLK_ID_REF (FREQM_GCLK_ID_MSR + 1)
#endif

/**
 * \brief Initializes a hardware FREQM module instance.
 *
 * Enables the clock and initializes the FREQM module, based on the given
 * configuration values.
 *
 * \param[in,out] module_inst  Pointer to the software module instance struct
 * \param[in]     hw           Pointer to the FREQM hardware module
 * \param[in]     config       Pointer to the FREQM configuration options struct
 *
 * \return Status of the initialization procedure.
 *
 * \retval STATUS_OK           The module was initialized successfully
 */
enum status_code freqm_init(
		struct freqm_module *const module_inst,
		Freqm *const hw,
		struct freqm_config *const config)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(hw);
	Assert(config);
	Assert(config->ref_clock_circles);

	/* Initialize device instance */
	module_inst->hw = hw;

	/* Turn on the digital interface clock */
	system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBA, MCLK_APBAMASK_FREQM);

	/* Set up the GCLK for the module */
	struct system_gclk_chan_config gclk_chan_conf;
	system_gclk_chan_get_config_defaults(&gclk_chan_conf);
	gclk_chan_conf.source_generator = config->msr_clock_source;
	system_gclk_chan_set_config(FREQM_GCLK_ID_MSR, &gclk_chan_conf);
	system_gclk_chan_enable(FREQM_GCLK_ID_MSR);

	gclk_chan_conf.source_generator = config->ref_clock_source;
	system_gclk_chan_set_config(FREQM_GCLK_ID_REF, &gclk_chan_conf);
	system_gclk_chan_enable(FREQM_GCLK_ID_REF);
	
	module_inst->ref_clock_freq = system_gclk_gen_get_hz(config->ref_clock_source);

	/* Perform a software reset */
	hw->CTRLA.reg = FREQM_CTRLA_SWRST;

	while (freqm_is_syncing()) {
		/* Wait for all hardware modules to complete synchronization */
	}

	/* Initialize the FREQM with new configurations */
	hw->CFGA.reg = config->ref_clock_circles;

#if FREQM_CALLBACK_MODE == true
	/* Initialize parameters */
	for (uint8_t i = 0; i < FREQM_CALLBACK_N; i++) {
		module_inst->callback[i] = NULL;
	}
	/* Register this instance for callbacks*/
	_freqm_instance = module_inst;
#endif

	return STATUS_OK;
}

/**
 * \brief Read the measurement data result
 *
 * Reads the measurement data result.
 *
 * \param[in]  module_inst  Pointer to the FREQM software instance struct
 * \param[out] result       Pointer to store the result value in
 *
 * \return Status of the FREQM read request.
 * \retval FREQM_STATUS_MEASURE_DONE   Measurement result was retrieved successfully
 * \retval FREQM_STATUS_MEASURE_BUSY   Measurement result was not ready
 * \retval FREQM_STATUS_CNT_OVERFLOW   Measurement result was overflow
 *                              
 * \note If overflow occurred, configure faster reference clock or reduce reference clock cycles.
 */
enum freqm_status freqm_get_result_value(
		struct freqm_module *const module_inst, uint32_t *result)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);
	Assert(result);

	Freqm *const freqm_hw = module_inst->hw;
	uint32_t result_cal;
	*result = result_cal= 0;

	if (freqm_hw->STATUS.reg & FREQM_STATUS_BUSY) {
		/* Result not ready */
		return FREQM_STATUS_MEASURE_BUSY;
	} else {
		if (freqm_hw->STATUS.reg & FREQM_STATUS_OVF) {
			/* Overflow */
			return FREQM_STATUS_CNT_OVERFLOW;
		} else {
			/* Get measurement output data (it will clear data done flag) */
			result_cal = freqm_hw->VALUE.reg;
			freqm_hw->INTFLAG.reg = FREQM_INTFLAG_DONE;

			*result = result_cal * module_inst->ref_clock_freq / freqm_hw->CFGA.reg;
			return FREQM_STATUS_MEASURE_DONE;
		}
	}
}
