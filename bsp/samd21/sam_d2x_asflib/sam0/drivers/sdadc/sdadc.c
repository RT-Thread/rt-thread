/**
 * \file
 *
 * \brief SAM Sigma-Delta Analog-to-Digital Converter (SDADC) Driver
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

#include "sdadc.h"

/**
* \internal Configure MUX settings for the analog pins
*
* This function will set the given SDADC input pins
* to the analog function in the pinmux, giving
* the SDADC access to the analog signal
*
* \param [in] pin AINxx pin to configure
*/
static inline void _sdadc_configure_ain_pin(uint32_t pin)
{
	/* Pinmapping table for AINxx -> GPIO pin number */
	const uint32_t pinmapping[] = {
#if (SAMC21E)
			PIN_PA06B_SDADC_INN0, PIN_PA07B_SDADC_INP0,
#elif (SAMC21G)
			PIN_PA06B_SDADC_INN0, PIN_PA07B_SDADC_INP0,
			PIN_PB08B_SDADC_INN1, PIN_PB09B_SDADC_INP1,
#elif (SAMC21J)
			PIN_PA06B_SDADC_INN0, PIN_PA07B_SDADC_INP0,
			PIN_PB08B_SDADC_INN1, PIN_PB09B_SDADC_INP1,
			PIN_PB06B_SDADC_INN2, PIN_PB07B_SDADC_INP2,
#else
#  error SDADC pin mappings are not defined for this device.
#endif
	};

	uint32_t pin_map_result;

	struct system_pinmux_config config;
	system_pinmux_get_config_defaults(&config);

	config.input_pull   = SYSTEM_PINMUX_PIN_PULL_NONE;
	config.mux_position = 1;

	pin_map_result = pinmapping[pin * 2];
	system_pinmux_pin_set_config(pin_map_result, &config);

	pin_map_result = pinmapping[pin * 2 + 1];
	system_pinmux_pin_set_config(pin_map_result, &config);
}

/**
 * \internal Writes an SDADC configuration to the hardware module
 *
 * Writes out a given SDADC module configuration to the hardware module.
 *
 * \param[out] module_inst  Pointer to the SDADC software instance struct
 * \param[in]  config       Pointer to configuration struct
 *
 * \return Status of the configuration procedure.
 * \retval STATUS_OK               The configuration was successful
 * \retval STATUS_ERR_INVALID_ARG  Invalid argument(s) were provided
 */
static enum status_code _sdadc_set_config(
		struct sdadc_module *const module_inst,
		struct sdadc_config *const config)
{
	/* Get the hardware module pointer */
	Sdadc *const sdadc_module = module_inst->hw;

	/* Configure GCLK channel and enable clock */
	struct system_gclk_chan_config gclk_chan_conf;
	system_gclk_chan_get_config_defaults(&gclk_chan_conf);
	gclk_chan_conf.source_generator = config->clock_source;
	system_gclk_chan_set_config(SDADC_GCLK_ID, &gclk_chan_conf);
	system_gclk_chan_enable(SDADC_GCLK_ID);

	/* Setup pinmuxing for analog inputs */
	_sdadc_configure_ain_pin(config->mux_input);

	/* Configure run in standby */
	sdadc_module->CTRLA.reg = (config->run_in_standby << SDADC_CTRLA_RUNSTDBY_Pos)
			| (config->on_command << SDADC_CTRLA_ONDEMAND_Pos);

	while (sdadc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Configure reference */
	sdadc_module->REFCTRL.reg = (config->reference.ref_sel) | (config->reference.ref_range) |
						(config->reference.on_ref_buffer << SDADC_REFCTRL_ONREFBUF_Pos);

	/* Configure CTRLB */
	sdadc_module->CTRLB.reg =
			(config->skip_count << SDADC_CTRLB_SKPCNT_Pos) |
			(config->clock_prescaler / 2 - 1) | config->osr;

	while (sdadc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Configure CTRLC */
	sdadc_module->CTRLC.reg =
			(config->freerunning << SDADC_CTRLC_FREERUN_Pos);

	/* Configure SEQCTRL */
	sdadc_module->SEQCTRL.reg =
			(config->seq_enable[0]) | (config->seq_enable[1] << 1) | (config->seq_enable[2] << 2);

	/* Check validity of window thresholds */
	if (config->window.window_mode != SDADC_WINDOW_MODE_DISABLE) {
		if (config->window.window_lower_value > (int32_t)(SDADC_RESULT_RESULT_Msk / 2) ||
			config->window.window_lower_value < -(int32_t)(SDADC_RESULT_RESULT_Msk / 2 + 1) ||
			config->window.window_upper_value > (int32_t)(SDADC_RESULT_RESULT_Msk / 2) ||
			config->window.window_upper_value < -(int32_t)(SDADC_RESULT_RESULT_Msk / 2 + 1)) {
			/* Invalid value */
			return STATUS_ERR_INVALID_ARG;
		} else if (config->window.window_lower_value > (int32_t)SDADC_RESULT_RESULT_Msk ||
				config->window.window_upper_value > (int32_t)SDADC_RESULT_RESULT_Msk){
			/* Invalid value */
			return STATUS_ERR_INVALID_ARG;
		}
	}

	while (sdadc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Configure window mode */
	sdadc_module->WINCTRL.reg = config->window.window_mode;

	while (sdadc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Configure lower threshold */
	sdadc_module->WINLT.reg =
			config->window.window_lower_value << SDADC_WINLT_WINLT_Pos;

	while (sdadc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Configure lower threshold */
	sdadc_module->WINUT.reg = config->window.window_upper_value <<
			SDADC_WINUT_WINUT_Pos;

	while (sdadc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Configure pin scan mode and positive and negative input pins */
	sdadc_module->INPUTCTRL.reg = config->mux_input;

	/* Configure events */
	sdadc_module->EVCTRL.reg = config->event_action;

	/* Disable all interrupts */
	sdadc_module->INTENCLR.reg = (1 << SDADC_INTENCLR_WINMON_Pos) |
			(1 << SDADC_INTENCLR_OVERRUN_Pos) | (1 << SDADC_INTENCLR_RESRDY_Pos);

	/* Make sure offset correction value is valid */
	if (config->correction.offset_correction > (int32_t)(SDADC_OFFSETCORR_MASK / 2) ||
		config->correction.offset_correction < - (int32_t)(SDADC_OFFSETCORR_MASK / 2 + 1)) {
		return STATUS_ERR_INVALID_ARG;
	} else {
		while (sdadc_is_syncing(module_inst)) {
			/* Wait for synchronization */
		}

		/* Set offset correction value */
		sdadc_module->OFFSETCORR.reg = config->correction.offset_correction <<
				SDADC_OFFSETCORR_OFFSETCORR_Pos;
	}

	/* Make sure gain_correction value is valid */
	if (config->correction.gain_correction > SDADC_GAINCORR_MASK) {
		return STATUS_ERR_INVALID_ARG;
	} else {
		while (sdadc_is_syncing(module_inst)) {
			/* Wait for synchronization */
		}

		/* Set gain correction value */
		sdadc_module->GAINCORR.reg = config->correction.gain_correction <<
				SDADC_GAINCORR_GAINCORR_Pos;
	}

	/* Make sure shift_correction value is valid */
	if (config->correction.shift_correction > SDADC_SHIFTCORR_MASK) {
		return STATUS_ERR_INVALID_ARG;
	} else {
		while (sdadc_is_syncing(module_inst)) {
			/* Wait for synchronization */
		}

		/* Set shift correction value */
		sdadc_module->SHIFTCORR.reg = config->correction.shift_correction <<
				SDADC_SHIFTCORR_SHIFTCORR_Pos;
	}

	return STATUS_OK;
}

/**
 * \brief Initializes the SDADC.
 *
 * Initializes the SDADC device struct and the hardware module based on the
 * given configuration struct values.
 *
 * \param[out] module_inst Pointer to the SDADC software instance struct
 * \param[in]  hw          Pointer to the SDADC module instance
 * \param[in]  config      Pointer to the configuration struct
 *
 * \return Status of the initialization procedure.
 * \retval STATUS_OK                The initialization was successful
 * \retval STATUS_ERR_INVALID_ARG   Invalid argument(s) were provided
 * \retval STATUS_BUSY          The module is busy with a reset operation
 * \retval STATUS_ERR_DENIED        The module is enabled
 */
enum status_code sdadc_init(
		struct sdadc_module *const module_inst,
		Sdadc *hw,
		struct sdadc_config *config)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(hw);
	Assert(config);

	/* Associate the software module instance with the hardware module */
	module_inst->hw = hw;

	/* Turn on the digital interface clock */
	system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBC, MCLK_APBCMASK_SDADC);

	if (hw->CTRLA.reg & SDADC_CTRLA_SWRST) {
		/* We are in the middle of a reset. Abort. */
		return STATUS_BUSY;
	}

	if (hw->CTRLA.reg & SDADC_CTRLA_ENABLE) {
		/* Module must be disabled before initialization. Abort. */
		return STATUS_ERR_DENIED;
	}

	/* Store the selected reference for later use */
	module_inst->reference = config->reference;

#if SDADC_CALLBACK_MODE == true
	for (uint8_t i = 0; i < SDADC_CALLBACK_N; i++) {
		module_inst->callback[i] = NULL;
	};

	module_inst->registered_callback_mask = 0;
	module_inst->enabled_callback_mask = 0;
	module_inst->remaining_conversions = 0;
	module_inst->job_status = STATUS_OK;

	_sdadc_instances[0] = module_inst;

	if (config->event_action == SDADC_EVENT_ACTION_DISABLED &&
			!config->freerunning) {
		module_inst->software_trigger = true;
	} else {
		module_inst->software_trigger = false;
	}
#endif

	/* Write configuration to module */
	return _sdadc_set_config(module_inst, config);
}
