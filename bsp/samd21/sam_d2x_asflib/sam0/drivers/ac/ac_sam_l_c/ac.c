/**
 * \file
 *
 * \brief SAM Analog Comparator Driver
 *
 * Copyright (C) 2014-2016 Atmel Corporation. All rights reserved.
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
#include "ac.h"

static enum status_code _ac_set_config(
		struct ac_module *const module_inst,
		struct ac_config *const config)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);
	Assert(config);

	UNUSED(module_inst);

	/* Set up GCLK */
	struct system_gclk_chan_config gclk_chan_conf;
	system_gclk_chan_get_config_defaults(&gclk_chan_conf);
	gclk_chan_conf.source_generator = config->source_generator;
#if (SAMC21) || (SAMC20)
	/* The Analog Comparators and ADC1 use the same generic clock configuration.
 	 * GCLK_ADC1 must be used to configure the clock for AC as GCLK_AC is not 
 	 * functional. Errata reference: 13404 
 	 */
	system_gclk_chan_set_config(34, &gclk_chan_conf);
	system_gclk_chan_enable(34);
#else
	system_gclk_chan_set_config(AC_GCLK_ID, &gclk_chan_conf);
	system_gclk_chan_enable(AC_GCLK_ID);
#endif

	return STATUS_OK;
}

/** \brief Resets and disables the Analog Comparator driver.
 *
 *  Resets and disables the Analog Comparator driver, resets the internal
 *  states and registers of the hardware module to their power-on defaults.
 *
 * \param[out] module_inst  Pointer to the AC software instance struct
 */
enum status_code ac_reset(
		struct ac_module *const module_inst)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Ac *const ac_module = module_inst->hw;

	/* Disable the hardware module */
	ac_disable(module_inst);

	while (ac_is_syncing(module_inst)) {
		/* Wait until synchronization is complete */
	}

	/* Software reset the module */
	ac_module->CTRLA.reg |= AC_CTRLA_SWRST;

	return STATUS_OK;
}

/** \brief Initializes and configures the Analog Comparator driver.
 *
 *  Initializes the Analog Comparator driver, configuring it to the user
 *  supplied configuration parameters, ready for use. This function should be
 *  called before enabling the Analog Comparator.
 *
 *  \note Once called the Analog Comparator will not be running; to start the
 *        Analog Comparator call \ref ac_enable() after configuring the module.
 *
 * \param[out] module_inst  Pointer to the AC software instance struct
 * \param[in]  hw           Pointer to the AC module instance
 * \param[in]  config       Pointer to the config struct, created by the user
 *                          application
 */
enum status_code ac_init(
		struct ac_module *const module_inst,
		Ac *const hw,
		struct ac_config *const config)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(hw);
	Assert(config);

	/* Initialize device instance */
	module_inst->hw = hw;

#if (SAML21) || (SAMR30)
	/* Turn on the digital interface clock */
	system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBD, MCLK_APBDMASK_AC);
#else
	/* Turn on the digital interface clock */
	system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBC, MCLK_APBCMASK_AC);
#endif

#if AC_CALLBACK_MODE == true
	/* Initialize parameters */
	for (uint8_t i = 0; i < AC_CALLBACK_N; i++) {
		module_inst->callback[i]        = NULL;
	}

	/* Initialize software flags*/
	module_inst->register_callback_mask = 0x00;
	module_inst->enable_callback_mask   = 0x00;

#  if (AC_INST_NUM == 1)
	_ac_instance[0] = module_inst;
#  else
	/* Register this instance for callbacks*/
	_ac_instance[_ac_get_inst_index(hw)] = module_inst;
#  endif
#endif

	/* Write configuration to module */
	return _ac_set_config(module_inst, config);
}

/** \brief Writes an Analog Comparator channel configuration to the hardware module.
 *
 *  Writes a given Analog Comparator channel configuration to the hardware
 *  module.
 *
 *  \param[in] module_inst  Software instance for the Analog Comparator peripheral
 *  \param[in] channel      Analog Comparator channel to configure
 *  \param[in] config       Pointer to the channel configuration struct
 */
enum status_code ac_chan_set_config(
		struct ac_module *const module_inst,
		const enum ac_chan_channel channel,
		struct ac_chan_config *const config)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);
	Assert(config);

	Ac *const ac_module = module_inst->hw;

	/* Use a temporary variable to compute the comparator configuration */
	uint32_t compctrl_temp = 0;

	/* Enable output filter mode */
	compctrl_temp |= config->filter;

	/* Comparators should be enabled during sleep */
	if (config->run_in_standby == true) {
		compctrl_temp |= AC_COMPCTRL_RUNSTDBY;
	}

	/* Set output signal routing mode */
	compctrl_temp |= config->output_mode;

	/* Configure comparator positive and negative pin MUX configurations */
	compctrl_temp |=
			(uint32_t)config->positive_input |
			(uint32_t)config->negative_input;

	/* Set sampling mode (single shot or continuous) */
	compctrl_temp |= config->sample_mode;

	/* Set channel interrupt selection */
	compctrl_temp |= config->interrupt_selection;

	while (ac_is_syncing(module_inst)) {
		/* Wait until synchronization is complete */
	}

	/* Write the final configuration to the module's control register */
	ac_module->COMPCTRL[(uint8_t)channel].reg = compctrl_temp;

	/* Configure VCC voltage scaling for the comparator */
	ac_module->SCALER[(uint8_t)channel].reg   = config->vcc_scale_factor - 1;

	return STATUS_OK;
}

/**
 * \brief Function used to setup interrupt selection of a window.
 *
 * This function is used to setup when an interrupt should occur
 * for a given window.
 *
 * \note This must be done before enabling the channel.
 *
 * \param[in]  module_inst  Pointer to software instance struct
 * \param[in]  win_channel  Window channel to setup
 * \param[in]  config       Configuration for the given window channel
 *
 * \retval  STATUS_OK               Function exited successful
 * \retval  STATUS_ERR_INVALID_ARG  win_channel argument incorrect
 */
enum status_code ac_win_set_config(
		struct ac_module *const module_inst,
		enum ac_win_channel const win_channel,
		struct ac_win_config *const config)
{
	Assert(module_inst);
	Assert(module_inst->hw);
	Assert(config);

	uint8_t winctrl_mask;

	winctrl_mask = module_inst->hw->WINCTRL.reg;

	if (win_channel == AC_WIN_CHANNEL_0) {
		winctrl_mask &= ~AC_WINCTRL_WINTSEL0_Msk;
		winctrl_mask |= config->interrupt_selection;
	}
#if (AC_PAIRS > 1)
	else if (win_channel == AC_WIN_CHANNEL_1) {
		winctrl_mask &= ~AC_WINCTRL_WINTSEL1_Msk;
		winctrl_mask = (config->interrupt_selection << (AC_WINCTRL_WINTSEL1_Pos -
		AC_WINCTRL_WINTSEL0_Pos));
	}
#endif /* (AC_PAIRS > 1) */
	else {
		return STATUS_ERR_INVALID_ARG ;
	}

	module_inst->hw->WINCTRL.reg = winctrl_mask;

	return STATUS_OK;
}

/** \brief Enables an Analog Comparator window channel that was previously configured.
 *
 *  Enables and starts an Analog Comparator window channel.
 *
 *  \note The comparator channels used by the window channel must be configured
 *        and enabled before calling this function. The two comparator channels
 *        forming each window comparator pair must have identical configurations
 *        other than the negative pin multiplexer setting.
 *
 *  \param[in] module_inst  Software instance for the Analog Comparator peripheral
 *  \param[in] win_channel  Comparator window channel to enable
 *
 *  \return Status of the window enable procedure.
 *
 *  \retval STATUS_OK              The window comparator was enabled
 *  \retval STATUS_ERR_IO          One or both comparators in the window
 *                                 comparator pair is disabled
 *  \retval STATUS_ERR_BAD_FORMAT  The comparator channels in the window pair
 *                                 were not configured correctly
 */
enum status_code ac_win_enable(
		struct ac_module *const module_inst,
		const enum ac_win_channel win_channel)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Ac *const ac_module = module_inst->hw;

	/* Load the configurations of the two comparators used in the window */
	uint32_t win_pair_comp0_conf = ac_module->COMPCTRL[win_channel * 2].reg;
	uint32_t win_pair_comp1_conf = ac_module->COMPCTRL[win_channel * 2 + 1].reg;

	/* Make sure both comparators in the window comparator pair are enabled */
	if (!(win_pair_comp0_conf & AC_COMPCTRL_ENABLE) ||
			!(win_pair_comp1_conf & AC_COMPCTRL_ENABLE)) {
		return STATUS_ERR_IO;
	}

	/* Make sure the comparators are configured in the same way, other than the
	 * negative pin multiplexers */
	if ((win_pair_comp0_conf & ~AC_COMPCTRL_MUXNEG_Msk) !=
			(win_pair_comp1_conf & ~AC_COMPCTRL_MUXNEG_Msk)) {
		return STATUS_ERR_BAD_FORMAT;
	}

	while (ac_is_syncing(module_inst)) {
		/* Wait until synchronization is complete */
	}

	/* Enable the requested window comparator */
	switch (win_channel)
	{
		case AC_WIN_CHANNEL_0:
			ac_module->WINCTRL.reg |= AC_WINCTRL_WEN0;
			break;

#if (AC_PAIRS > 1)
		case AC_WIN_CHANNEL_1:
			ac_module->WINCTRL.reg |= AC_WINCTRL_WEN1;
			break;
#endif
	}

	return STATUS_OK;
}

/** \brief Disables an Analog Comparator window channel that was previously enabled.
 *
 *  Stops an Analog Comparator window channel that was previously started via a
 *  call to \ref ac_win_enable().
 *
 *  \param[in] module_inst  Software instance for the Analog Comparator peripheral
 *  \param[in] win_channel  Comparator window channel to disable
 */
void ac_win_disable(
		struct ac_module *const module_inst,
		const enum ac_win_channel win_channel)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Ac *const ac_module = module_inst->hw;

	while (ac_is_syncing(module_inst)) {
		/* Wait until synchronization is complete */
	}

	/* Disable the requested window comparator */
	switch (win_channel)
	{
		case AC_WIN_CHANNEL_0:
			ac_module->WINCTRL.reg &= ~AC_WINCTRL_WEN0;
			break;

#if (AC_PAIRS > 1)
		case AC_WIN_CHANNEL_1:
			ac_module->WINCTRL.reg &= ~AC_WINCTRL_WEN1;
			break;
#endif
	}
}

/** \brief Determines the state of a specified Window Comparator.
 *
 *  Retrieves the current window detection state, indicating what the input
 *  signal is currently comparing to relative to the window boundaries.
 *
 *  \param[in] module_inst  Software instance for the Analog Comparator peripheral
 *  \param[in] win_channel  Comparator Window channel to test
 *
 *  \return Bit mask of Analog Comparator window channel status flags.
 */
uint8_t ac_win_get_status(
		struct ac_module *const module_inst,
		const enum ac_win_channel win_channel)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Ac *const ac_module = module_inst->hw;

	uint32_t win_status = 0;

	/* Check if interrupt flag is set */
	if (ac_module->INTFLAG.reg & (AC_INTFLAG_WIN0 << win_channel)) {
		win_status |= AC_WIN_STATUS_INTERRUPT_SET;
	}

	/* If one or both window comparators not ready, return unknown result */
	if (ac_win_is_ready(module_inst, win_channel) == false) {
		win_status |= AC_WIN_STATUS_UNKNOWN;
		return win_status;
	}

	uint8_t statusa_tmp = ac_module->STATUSA.reg;

	/* Map hardware comparison states to logical window states */
	if (statusa_tmp & (AC_STATUSA_WSTATE0_BELOW << win_channel)) {
		return win_status | AC_WIN_STATUS_BELOW;
	} else if (statusa_tmp & (AC_STATUSA_WSTATE0_INSIDE << win_channel)) {
		return win_status | AC_WIN_STATUS_INSIDE;
	} else {
		return win_status | AC_WIN_STATUS_ABOVE;
	}

}
