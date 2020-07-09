/**
 * \file
 *
 * \brief SAM Peripheral Digital-to-Analog Converter Driver
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
#include "dac.h"
#include <system.h>
#include <pinmux.h>

/**
 * \internal Writes a DAC configuration to the hardware module.
 *
 * Writes out a given configuration to the hardware module.
 *
 * \param[out] module_inst  Pointer to the DAC software instance struct
 * \param[in]  config       Pointer to the configuration struct
 *
 */
static void _dac_set_config(
		struct dac_module *const module_inst,
		struct dac_config *const config)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(config);
	Assert(module_inst->hw);

	Dac *const dac_module = module_inst->hw;

	/* Set selected DAC start on event to be disable when enabling the module */
	module_inst->start_on_event[DAC_CHANNEL_0] = false;
	module_inst->start_on_event[DAC_CHANNEL_1] = false;

	uint32_t new_ctrlb = 0;

	/* Enable DAC in differential mode if configured */
	if (config->differential_mode) {
		new_ctrlb |= DAC_CTRLB_DIFF;
	}

	/* Set reference voltage */
	new_ctrlb |= config->reference;

	/* Apply the new configuration to the hardware module */
	dac_module->CTRLB.reg = new_ctrlb;
}

/**
 * \brief Determines if the hardware module(s) are currently synchronizing to the bus.
 *
 * Checks to see if the underlying hardware peripheral module(s) are currently
 * synchronizing across multiple clock domains to the hardware bus. This
 * function can be used to delay further operations on a module until such time
 * that it is ready, to prevent blocking delays for synchronization in the
 * user application.
 *
 * \param[in] dev_inst  Pointer to the DAC software instance struct
 *
 * \return Synchronization status of the underlying hardware module(s).
 *
 * \retval true If the module synchronization is ongoing
 * \retval false If the module has completed synchronization
 */
bool dac_is_syncing(
		struct dac_module *const dev_inst)
{
	/* Sanity check arguments */
	Assert(dev_inst);

	Dac *const dac_module = dev_inst->hw;

	if (dac_module->SYNCBUSY.reg) {
		return true;
	}

	return false;
}

/**
 * \brief Initializes a DAC configuration structure to defaults.
 *
 *  Initializes a given DAC configuration structure to a set of
 *  known default values. This function should be called on any new
 *  instance of the configuration structures before being modified by the
 *  user application.
 *
 *  The default configuration is as follows:
 *   \li 1V from internal bandgap reference
 *   \li Drive the DAC output to the VOUT pin
 *   \li Right adjust data
 *   \li GCLK generator 0 (GCLK main) clock source
 *   \li The output buffer is disabled when the chip enters STANDBY sleep
 *       mode
 *
 * \param[out] config  Configuration structure to initialize to default values
 */
void dac_get_config_defaults(
		struct dac_config *const config)
{
	/* Sanity check arguments */
	Assert(config);

	/* Default configuration values */
	config->differential_mode = false;
    config->reference      = DAC_REFERENCE_INTREF;
	config->clock_source   = GCLK_GENERATOR_0;
}

/**
 * \brief Initialize the DAC device struct.
 *
 * Use this function to initialize the Digital to Analog Converter. Resets the
 * underlying hardware module and configures it.
 *
 * \note The DAC channel must be configured separately.
 *
 * \param[out] module_inst  Pointer to the DAC software instance struct
 * \param[in]  module       Pointer to the DAC module instance
 * \param[in]  config       Pointer to the config struct, created by the user
 *                          application
 *
 * \return Status of initialization.
 * \retval STATUS_OK          Module initiated correctly
 * \retval STATUS_ERR_DENIED  If module is enabled
 * \retval STATUS_BUSY        If module is busy resetting
 */
enum status_code dac_init(
		struct dac_module *const module_inst,
		Dac *const module,
		struct dac_config *const config)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module);
	Assert(config);

	/* Initialize device instance */
	module_inst->hw = module;

	/* Turn on the digital interface clock */
	system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBC, MCLK_APBCMASK_DAC);

	/* Check if module is enabled. */
	if (module->CTRLA.reg & DAC_CTRLA_ENABLE) {
		return STATUS_ERR_DENIED;
	}

	/* Check if reset is in progress. */
	if (module->CTRLA.reg & DAC_CTRLA_SWRST) {
		return STATUS_BUSY;
	}

	/* Configure GCLK channel and enable clock */
	struct system_gclk_chan_config gclk_chan_conf;
	system_gclk_chan_get_config_defaults(&gclk_chan_conf);
	gclk_chan_conf.source_generator = config->clock_source;
	system_gclk_chan_set_config(DAC_GCLK_ID, &gclk_chan_conf);
	system_gclk_chan_enable(DAC_GCLK_ID);

	/* Write configuration to module */
	_dac_set_config(module_inst, config);

	/* Store reference selection for later use */
	module_inst->reference = config->reference;

#if DAC_CALLBACK_MODE == true
	for (uint8_t i = 0; i < DAC_CHANNEL_N; i++) {
		for (uint8_t j = 0; j < DAC_CALLBACK_N; j++) {
			module_inst->callback[i][j] = NULL;
		}
	};

	_dac_instances[0] = module_inst;
#endif

	return STATUS_OK;
}

/**
 * \brief Resets the DAC module.
 *
 * This function will reset the DAC module to its power on default values and
 * disable it.
 *
 * \param[in] module_inst  Pointer to the DAC software instance struct
 */
void dac_reset(
		struct dac_module *const module_inst)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Dac *const dac_module = module_inst->hw;

	while (dac_is_syncing(module_inst)) {
		/* Wait until the synchronization is complete */
	}

	/* Software reset the module */
	dac_module->CTRLA.reg |= DAC_CTRLA_SWRST;
}

/**
 * \brief Enable the DAC module.
 *
 * Enables the DAC interface and the selected output. If any internal reference
 * is selected it will be enabled.
 *
 * \param[in] module_inst  Pointer to the DAC software instance struct
 *
 */
void dac_enable(
		struct dac_module *const module_inst)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Dac *const dac_module = module_inst->hw;

	while (dac_is_syncing(module_inst)) {
		/* Wait until the synchronization is complete */
	}

	/* Enable the module */
	dac_module->CTRLA.reg |= DAC_CTRLA_ENABLE;

	/* Enable internal bandgap reference if selected in the configuration */
	if (module_inst->reference == DAC_REFERENCE_INTREF) {
		system_voltage_reference_enable(SYSTEM_VOLTAGE_REFERENCE_OUTPUT);
	}

	if(dac_module->DACCTRL[DAC_CHANNEL_0].reg & DAC_DACCTRL_ENABLE) {
		while(! (dac_module->STATUS.reg & DAC_STATUS_READY(DAC_CHANNEL_0 + 1))) {
		};
	} else if(dac_module->DACCTRL[DAC_CHANNEL_1].reg & DAC_DACCTRL_ENABLE) {
		while(! (dac_module->STATUS.reg & DAC_STATUS_READY(DAC_CHANNEL_1 + 1))) {
		};
	}
}

/**
 * \brief Disable the DAC module.
 *
 * Disables the DAC interface and the output buffer.
 *
 * \param[in] module_inst  Pointer to the DAC software instance struct
 *
 */
void dac_disable(
		struct dac_module *const module_inst)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Dac *const dac_module = module_inst->hw;

	while (dac_is_syncing(module_inst)) {
		/* Wait until the synchronization is complete */
	}

	/* Disbale interrupt */
	dac_module->INTENCLR.reg = DAC_INTENCLR_MASK;
	/* Clear interrupt flag */
	dac_module->INTFLAG.reg = DAC_INTFLAG_MASK;

	/* Disable DAC */
	dac_module->CTRLA.reg &= ~DAC_CTRLA_ENABLE;
}

/**
 * \brief Enables a DAC event input or output.
 *
 *  Enables one or more input or output events to or from the DAC module. See
 *  \ref dac_events "Struct dac_events" for a list of events this module supports.
 *
 *  \note Events cannot be altered while the module is enabled.
 *
 *  \param[in] module_inst  Software instance for the DAC peripheral
 *  \param[in] events       Struct containing flags of events to enable
 */
void dac_enable_events(
		struct dac_module *const module_inst,
		struct dac_events *const events)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);
	Assert(events);

	Dac *const dac_module = module_inst->hw;

	uint32_t event_mask = 0;

	/* Configure Enable Inversion of input event */
	if (events->generate_event_on_chan0_falling_edge) {
		event_mask |= DAC_EVCTRL_INVEI0;
	}

	/* Configure Enable Inversion of input event */
	if (events->generate_event_on_chan1_falling_edge) {
		event_mask |= DAC_EVCTRL_INVEI1;
	}

	/* Configure Buffer Empty event */
	if (events->generate_event_on_chan0_buffer_empty) {
		event_mask |= DAC_EVCTRL_EMPTYEO0;
	}

	/* Configure Buffer Empty event */
	if (events->generate_event_on_chan1_buffer_empty) {
		event_mask |= DAC_EVCTRL_EMPTYEO1;
	}

	/* Configure Conversion Start event */
	if (events->on_event_chan0_start_conversion) {
		event_mask |= DAC_EVCTRL_STARTEI0;
		module_inst->start_on_event[DAC_CHANNEL_0] = true;
	}

	/* Configure Conversion Start event */
	if (events->on_event_chan1_start_conversion) {
		event_mask |= DAC_EVCTRL_STARTEI1;
		module_inst->start_on_event[DAC_CHANNEL_1] = true;
	}

	dac_module->EVCTRL.reg |= event_mask;
}

/**
 * \brief Disables a DAC event input or output.
 *
 *  Disables one or more input or output events to or from the DAC module. See
 *  \ref dac_events "Struct dac_events" for a list of events this module supports.
 *
 *  \note Events cannot be altered while the module is enabled.
 *
 *  \param[in] module_inst  Software instance for the DAC peripheral
 *  \param[in] events       Struct containing flags of events to disable
 */
void dac_disable_events(
		struct dac_module *const module_inst,
		struct dac_events *const events)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);
	Assert(events);

	Dac *const dac_module = module_inst->hw;

	uint32_t event_mask = 0;

	/* Configure Buffer Empty event */
	if (events->on_event_chan0_start_conversion) {
		event_mask |= DAC_EVCTRL_EMPTYEO0;
	}

	/* Configure Buffer Empty event */
	if (events->on_event_chan1_start_conversion) {
		event_mask |= DAC_EVCTRL_EMPTYEO1;
	}

	/* Configure Conversion Start event */
	if (events->generate_event_on_chan0_buffer_empty) {
		event_mask |= DAC_EVCTRL_STARTEI0;
		module_inst->start_on_event[DAC_CHANNEL_0] = false;
	}

	/* Configure Conversion Start event */
	if (events->generate_event_on_chan0_buffer_empty) {
		event_mask |= DAC_EVCTRL_STARTEI1;
		module_inst->start_on_event[DAC_CHANNEL_1] = false;
	}

	dac_module->EVCTRL.reg &= ~event_mask;
}

void dac_chan_get_config_defaults(
		struct dac_chan_config *const config)
{
	/* Sanity check arguments */
	Assert(config);

	/* Dac channel default configuration values */
	config->left_adjust    = false;
	config->current        = DAC_CURRENT_12M;
	config->run_in_standby = false;
	config->dither_mode    = false;
	config->refresh_period = 2;
}


/**
 * \brief Writes a DAC channel configuration to the hardware module.
 *
 * Writes out a given channel configuration to the hardware module.
 *
 * \note The DAC device instance structure must be initialized before calling
 *       this function.
 *
 * \param[in] module_inst  Pointer to the DAC software instance struct
 * \param[in] channel      Channel to configure
 * \param[in] config       Pointer to the configuration struct
 *
 */
void dac_chan_set_config(
		struct dac_module *const module_inst,
		const enum dac_channel channel,
		struct dac_chan_config *const config)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);
	Assert(config);

	/* MUX the DAC VOUT pin */
	struct system_pinmux_config pin_conf;
	system_pinmux_get_config_defaults(&pin_conf);

	pin_conf.direction    = SYSTEM_PINMUX_PIN_DIR_INPUT;
	pin_conf.input_pull   = SYSTEM_PINMUX_PIN_PULL_NONE;

	if(channel == DAC_CHANNEL_0) {
		/* Set up the DAC VOUT0 pin */
		pin_conf.mux_position = MUX_PA02B_DAC_VOUT0;
		system_pinmux_pin_set_config(PIN_PA02B_DAC_VOUT0, &pin_conf);
	}
	else if(channel == DAC_CHANNEL_1) {
		/* Set up the DAC VOUT1 pin */
		pin_conf.mux_position = MUX_PA05B_DAC_VOUT1;
		system_pinmux_pin_set_config(PIN_PA05B_DAC_VOUT1, &pin_conf);
	}

	Dac *const dac_module = module_inst->hw;

	uint32_t new_dacctrl = 0;

	/* Left adjust data if configured */
	if (config->left_adjust) {
		new_dacctrl |= DAC_DACCTRL_LEFTADJ;
	}

	/* Set current control */
	new_dacctrl |= config->current;

	/* Enable DAC in standby sleep mode if configured */
	if (config->run_in_standby) {
		new_dacctrl |= DAC_DACCTRL_RUNSTDBY;
	}

	/* Voltage pump disable if configured */
	if (config->dither_mode) {
		new_dacctrl |= DAC_DACCTRL_DITHER;
	}

	new_dacctrl |= DAC_DACCTRL_REFRESH(config->refresh_period);

	/* Apply the new configuration to the hardware module */
	dac_module->DACCTRL[channel].reg = new_dacctrl;
}

/**
 * \brief Enable a DAC channel.
 *
 * Enables the selected DAC channel.
 *
 * \param[in] module_inst  Pointer to the DAC software instance struct
 * \param[in] channel      Channel to enable
 *
 */
void dac_chan_enable(
		struct dac_module *const module_inst,
		enum dac_channel channel)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Dac *const dac_module = module_inst->hw;

	/* Enable the module */
	dac_module->DACCTRL[channel].reg |= DAC_DACCTRL_ENABLE;
}

/**
 * \brief Disable a DAC channel.
 *
 * Disables the selected DAC channel.
 *
 * \param[in] module_inst  Pointer to the DAC software instance struct
 * \param[in] channel      Channel to disable
 *
 */
void dac_chan_disable(
		struct dac_module *const module_inst,
		enum dac_channel channel)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Dac *const dac_module = module_inst->hw;

	/* Enable the module */
	dac_module->DACCTRL[channel].reg &= ~DAC_DACCTRL_ENABLE;

}

/**
 * \brief Write to the DAC.
 *
 * This function writes to the DATA or DATABUF register.
 * If the conversion is not event-triggered, the data will be written to
 * the DATA register and the conversion will start.
 * If the conversion is event-triggered, the data will be written to DATABUF
 * and transferred to the DATA register and converted when a Start Conversion
 * Event is issued.
 * Conversion data must be right or left adjusted according to configuration
 * settings.
 * \note To be event triggered, the enable_start_on_event must be
 * enabled in the configuration.
 *
 * \param[in] module_inst      Pointer to the DAC software device struct
 * \param[in] channel          DAC channel to write to
 * \param[in] data             Conversion data
 *
 * \return Status of the operation.
 * \retval STATUS_OK           If the data was written
 */
enum status_code dac_chan_write(
		struct dac_module *const module_inst,
		enum dac_channel channel,
		const uint16_t data)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Dac *const dac_module = module_inst->hw;

	while (dac_is_syncing(module_inst)) {
		/* Wait until the synchronization is complete */
	}

	if (module_inst->start_on_event[channel]) {
		/* Write the new value to the buffered DAC data register */
		dac_module->DATABUF[channel].reg = data;
	} else {
		/* Write the new value to the DAC data register */
		dac_module->DATA[channel].reg = data;
	}

	return STATUS_OK;
}

/**
 * \brief Write to the DAC.
 *
 * This function converts a specific number of digital data.
 * The conversion should be event-triggered, the data will be written to DATABUF
 * and transferred to the DATA register and converted when a Start Conversion
 * Event is issued.
 * Conversion data must be right or left adjusted according to configuration
 * settings.
 * \note To be event triggered, the enable_start_on_event must be
 * enabled in the configuration.
 *
 * \param[in] module_inst      Pointer to the DAC software device struct
 * \param[in] channel          DAC channel to write to
 * \param[in] buffer           Pointer to the digital data write buffer to be converted
 * \param[in] length           Length of the write buffer
 *
 * \return Status of the operation.
 * \retval STATUS_OK           If the data was written or no data conversion required
 * \retval STATUS_ERR_UNSUPPORTED_DEV  The DAC is not configured as using event trigger
 * \retval STATUS_BUSY                 The DAC is busy and can not do the conversion
 */
enum status_code dac_chan_write_buffer_wait(
		struct dac_module *const module_inst,
		enum dac_channel channel,
		uint16_t *buffer,
		uint32_t length)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Dac *const dac_module = module_inst->hw;

	while (dac_is_syncing(module_inst)) {
		/* Wait until the synchronization is complete */
	}

	/* Zero length request */
	if (length == 0) {
		/* No data to be converted */
		return STATUS_OK;
	}

#if DAC_CALLBACK_MODE == true
	/* Check if busy */
	if (module_inst->job_status[channel] == STATUS_BUSY) {
		return STATUS_BUSY;
	}
#endif

	/* Only support event triggered conversion */
	if (module_inst->start_on_event[channel] == false) {
		return STATUS_ERR_UNSUPPORTED_DEV;
	}

	/* Blocks while buffer is being transferred */
	while (length--) {
		/* Convert one data */
		dac_chan_write(module_inst, channel, buffer[length]);

		/* Wait until Transmit is complete or timeout */
		for (uint32_t i = 0; i <= DAC_TIMEOUT; i++) {
			if(channel == DAC_CHANNEL_0) {
				if (dac_module->INTFLAG.reg & DAC_INTFLAG_EMPTY0) {
					break;
				} else if (i == DAC_TIMEOUT) {
					return STATUS_ERR_TIMEOUT;
				}
			} else if(channel == DAC_CHANNEL_1) {
				if (dac_module->INTFLAG.reg & DAC_INTFLAG_EMPTY1) {
					break;
				} else if (i == DAC_TIMEOUT) {
					return STATUS_ERR_TIMEOUT;
				}
			}
		}
	}

	return STATUS_OK;
}

/**
 * \brief Retrieves the status of DAC channel end of conversion.
 *
 * Checks if the conversion is completed or not and returns boolean flag
 * of status.
 *
 * \param[in] module_inst  Pointer to the DAC software instance struct
 * \param[in] channel      Channel to disable
 *
 * \retval true     Conversion is complete, VOUT is stable
 * \retval false    No conversion completed since last load of DATA
 */
bool dac_chan_is_end_of_conversion(
		struct dac_module *const module_inst,
		enum dac_channel channel)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Dac *const dac_module = module_inst->hw;

	if(dac_module->STATUS.reg & DAC_STATUS_EOC(channel + 1)) {
		return true;
	} else {
		return false;
	}
}

/**
 * \brief Retrieves the current module status.
 *
 * Checks the status of the module and returns it as a bitmask of status
 * flags.
 *
 * \param[in] module_inst      Pointer to the DAC software device struct
 *
 * \return Bitmask of status flags.
 *
 * \retval DAC_STATUS_CHANNEL_0_EMPTY    Data has been transferred from DATABUF
 *                                       to DATA by a start conversion event
 *                                       and DATABUF is ready for new data
 * \retval DAC_STATUS_CHANNEL_0_UNDERRUN A start conversion event has occurred
 *                                       when DATABUF is empty
 *
 */
uint32_t dac_get_status(
		struct dac_module *const module_inst)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Dac *const dac_module = module_inst->hw;

	uint8_t intflags = dac_module->INTFLAG.reg;
	uint32_t status_flags = 0;

	if (intflags & DAC_INTFLAG_EMPTY0) {
		status_flags |= DAC_STATUS_CHANNEL_0_EMPTY;
	}

	if (intflags & DAC_INTFLAG_EMPTY1) {
		status_flags |= DAC_STATUS_CHANNEL_1_EMPTY;
	}

	if (intflags & DAC_INTFLAG_UNDERRUN0) {
		status_flags |= DAC_STATUS_CHANNEL_0_UNDERRUN;
	}

	if (intflags & DAC_INTFLAG_UNDERRUN1) {
		status_flags |= DAC_STATUS_CHANNEL_1_UNDERRUN;
	}

	return status_flags;
}

/**
 * \brief Clears a module status flag.
 *
 * Clears the given status flag of the module.
 *
 * \param[in] module_inst      Pointer to the DAC software device struct
 * \param[in] status_flags     Bit mask of status flags to clear
 *
 */
void dac_clear_status(
		struct dac_module *const module_inst,
		uint32_t status_flags)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Dac *const dac_module = module_inst->hw;

	uint32_t intflags = 0;

	if (status_flags & DAC_STATUS_CHANNEL_0_EMPTY) {
		intflags |= DAC_INTFLAG_EMPTY0;
	}

	if (status_flags & DAC_STATUS_CHANNEL_1_EMPTY) {
		intflags |= DAC_INTFLAG_EMPTY1;
	}

	if (status_flags & DAC_STATUS_CHANNEL_0_UNDERRUN) {
		intflags |= DAC_INTFLAG_UNDERRUN0;
	}

	if (status_flags & DAC_STATUS_CHANNEL_1_UNDERRUN) {
		intflags |= DAC_INTFLAG_UNDERRUN1;
	}

	dac_module->INTFLAG.reg = intflags;
}
