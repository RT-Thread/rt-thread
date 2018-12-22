/**
 * \file
 *
 * \brief SAM Peripheral Analog-to-Digital Converter Driver
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

#include "adc.h"
#if (ADC_INST_NUM > 1) || (SAMC20)

#  define _ADC_GCLK_ID(n,unused)           TPASTE3(ADC,n,_GCLK_ID),
#  define _ADC_APBCMASK(n,unused)          TPASTE2(MCLK_APBCMASK_ADC,n),

#  define _ADC_FUSES_BIASCOMP_ADDR(n,unused)        TPASTE3(ADC,n,_FUSES_BIASCOMP_ADDR),
#  define _ADC_FUSES_BIASCOMP_Pos(n,unused)         TPASTE3(ADC,n,_FUSES_BIASCOMP_Pos),
#  define _ADC_FUSES_BIASREFBUF_ADDR(n,unused)      TPASTE3(ADC,n,_FUSES_BIASREFBUF_ADDR),
#  define _ADC_FUSES_BIASREFBUF_Pos(n,unused)       TPASTE3(ADC,n,_FUSES_BIASREFBUF_Pos),
#  define _ADC_EXTCHANNEL_MSB(n,unused)             TPASTE3(ADC,n,_EXTCHANNEL_MSB),

#  define ADC_GCLK_ID       MREPEAT(ADC_INST_NUM, _ADC_GCLK_ID, 0)
#  define ADC_APBCMASKS     MREPEAT(ADC_INST_NUM, _ADC_APBCMASK, 0)

#  define ADC_FUSES_BIASCOMP_ADDR     MREPEAT(ADC_INST_NUM, _ADC_FUSES_BIASCOMP_ADDR, 0)
#  define ADC_FUSES_BIASCOMP_Pos      MREPEAT(ADC_INST_NUM, _ADC_FUSES_BIASCOMP_Pos, 0)
#  define ADC_FUSES_BIASREFBUF_ADDR   MREPEAT(ADC_INST_NUM, _ADC_FUSES_BIASREFBUF_ADDR, 0)
#  define ADC_FUSES_BIASREFBUF_Pos    MREPEAT(ADC_INST_NUM, _ADC_FUSES_BIASREFBUF_Pos, 0)
#  define ADC_EXTCHANNEL_MSB          MREPEAT(ADC_INST_NUM, _ADC_EXTCHANNEL_MSB, 0)

#endif

/* List of ADC GCLK IDs */
const uint8_t _adc_gclk_ids[ADC_INST_NUM] = { ADC_GCLK_ID };

/* List of ADC APB Masks */
#if (ADC_INST_NUM > 1) || (SAMC20)
const uint32_t _adc_apbcmasks[ADC_INST_NUM] = { ADC_APBCMASKS };
#endif

/* List of Number of external channels of ADC modules. */
const uint32_t _adc_extchannel_msb[ADC_INST_NUM] = { ADC_EXTCHANNEL_MSB };

/* List of address of comparator scaling of ADC modules. */
const uint32_t _adc_biascomp_addr[ADC_INST_NUM] = { ADC_FUSES_BIASCOMP_ADDR };

/* List of address of bias reference buffer scaling of ADC modules. */
const uint32_t _adc_biasrefbuf_addr[ADC_INST_NUM] = { ADC_FUSES_BIASREFBUF_ADDR };

/* List of offset of comparator scaling of ADC modules. */
const uint8_t _adc_biascomp_pos[ADC_INST_NUM] = { ADC_FUSES_BIASCOMP_Pos };

/* List of offset of bias reference buffer scaling of ADC modules. */
const uint8_t _adc_biasrefbuf_pos[ADC_INST_NUM] = { ADC_FUSES_BIASREFBUF_Pos };


/**
 * \internal Find the index of given ADC module instance.
 *
 * \param[in] ADC module instance pointer.
 *
 * \return Index of the given ADC module instance.
 */
uint8_t _adc_get_inst_index(
		Adc *const hw)
{
	/* List of available ADC modules. */
	Adc *const adc_modules[ADC_INST_NUM] = ADC_INSTS;

	/* Find index for ADC instance. */
	for (uint32_t i = 0; i < ADC_INST_NUM; i++) {
		if (hw == adc_modules[i]) {
			return i;
		}
	}

	/* Invalid data given. */
	Assert(false);
	return 0;
}

/**
 * \brief Initializes an ADC configuration structure to defaults.
 *
 * Initializes a given ADC configuration struct to a set of known default
 * values. This function should be called on any new instance of the
 * configuration struct before being modified by the user application.
 *
 * The default configuration is as follows:
 *  \li GCLK generator 0 (GCLK main) clock source
 *  \li Internal bandgap reference
 *  \li Div 2 clock prescaler
 *  \li 12-bit resolution
 *  \li Window monitor disabled
 *  \li Positive input on ADC PIN 1
 *  \li Negative input on Internal ground
 *  \li Averaging disabled
 *  \li Oversampling disabled
 *  \li Right adjust data
 *  \li Single-ended mode
 *  \li Free running disabled
 *  \li All events (input and generation) disabled
 *  \li ADC run in standby disabled
 *  \li ADC On demand disabled
 *  \li No sampling time compensation
 *  \li Disable the positive input sequense
 *  \li No reference compensation
 *  \li No gain/offset correction
 *  \li No added sampling time
 *
 * \param[out] config  Pointer to configuration struct to initialize to
 *                     default values
 */
void adc_get_config_defaults(struct adc_config *const config)
{
	Assert(config);
	config->clock_source                  = GCLK_GENERATOR_0;
	config->reference                     = ADC_REFERENCE_INTREF;
	config->clock_prescaler               = ADC_CLOCK_PRESCALER_DIV2;
	config->resolution                    = ADC_RESOLUTION_12BIT;
	config->window.window_mode            = ADC_WINDOW_MODE_DISABLE;
	config->window.window_upper_value     = 0;
	config->window.window_lower_value     = 0;
#if SAMR30
	config->positive_input                = ADC_POSITIVE_INPUT_PIN6;
#else
	config->positive_input                = ADC_POSITIVE_INPUT_PIN1;
#endif
	config->negative_input                = ADC_NEGATIVE_INPUT_GND;
	config->accumulate_samples            = ADC_ACCUMULATE_DISABLE;
	config->divide_result                 = ADC_DIVIDE_RESULT_DISABLE;
	config->left_adjust                   = false;
	config->differential_mode             = false;
	config->freerunning                   = false;
	config->event_action                  = ADC_EVENT_ACTION_DISABLED;
	config->run_in_standby                = false;
	config->on_demand                     = false;
	config->sampling_time_compensation_enable  = false;
	config->positive_input_sequence_mask_enable = 0;
	config->reference_compensation_enable = false;
	config->correction.correction_enable  = false;
	config->correction.gain_correction    = ADC_GAINCORR_RESETVALUE;
	config->correction.offset_correction  = ADC_OFFSETCORR_RESETVALUE;
	config->sample_length                 = 0;
}

/**
 * \brief Sets the ADC window mode.
 *
 * Sets the ADC window mode to a given mode and value range.
 *
 * \param[in] module_inst         Pointer to the ADC software instance struct
 * \param[in] window_mode         Window monitor mode to set
 * \param[in] window_lower_value  Lower window monitor threshold value
 * \param[in] window_upper_value  Upper window monitor threshold value
  */
void adc_set_window_mode(
		struct adc_module *const module_inst,
		const enum adc_window_mode window_mode,
		const int16_t window_lower_value,
		const int16_t window_upper_value)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);

	Adc *const adc_module = module_inst->hw;

	while (adc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Set window mode */
	adc_module->CTRLC.reg = window_mode;

	while (adc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Set lower window monitor threshold value */
	adc_module->WINLT.reg = window_lower_value;

	while (adc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Set upper window monitor threshold value */
	adc_module->WINUT.reg = window_upper_value;

	while (adc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}
}

/**
* \internal Configure MUX settings for the analog pins.
*
* This function will set the given ADC input pins
* to the analog function in the pin mux, giving
* the ADC access to the analog signal.
*
* \param [in] index   Index of the ADC module instance.
* \param [in] pin     AINxx pin to configure
*/
static inline void _adc_configure_ain_pin(uint8_t index, uint32_t pin)
{
#define PIN_INVALID_ADC_AIN    0xFFFFUL

	/* Pinmapping table for AINxx -> GPIO pin number */
#if (SAML21) || (SAML22) || (SAMR30)
	const uint32_t pinmapping[] = {
#if (SAML21E) || (SAMR30E)
#if !(SAMR30)
			PIN_PA02B_ADC_AIN0,  PIN_PA03B_ADC_AIN1,
#endif
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_PA04B_ADC_AIN4,  PIN_PA05B_ADC_AIN5,
			PIN_PA06B_ADC_AIN6,  PIN_PA07B_ADC_AIN7,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_PA08B_ADC_AIN16, PIN_PA09B_ADC_AIN17,
			PIN_PA10B_ADC_AIN18, PIN_PA11B_ADC_AIN19,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
#elif (SAML21G) || (SAMR30G)
#if !(SAMR30)
			PIN_PA02B_ADC_AIN0,  PIN_PA03B_ADC_AIN1,
#endif
			PIN_PB08B_ADC_AIN2,  PIN_PB09B_ADC_AIN3,
			PIN_PA04B_ADC_AIN4,  PIN_PA05B_ADC_AIN5,
			PIN_PA06B_ADC_AIN6,  PIN_PA07B_ADC_AIN7,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_PB02B_ADC_AIN10, PIN_PB03B_ADC_AIN11,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_PA08B_ADC_AIN16, PIN_PA09B_ADC_AIN17,
			PIN_PA10B_ADC_AIN18, PIN_PA11B_ADC_AIN19,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
#elif (SAML21J)
			PIN_PA02B_ADC_AIN0,  PIN_PA03B_ADC_AIN1,
			PIN_PB08B_ADC_AIN2,  PIN_PB09B_ADC_AIN3,
			PIN_PA04B_ADC_AIN4,  PIN_PA05B_ADC_AIN5,
			PIN_PA06B_ADC_AIN6,  PIN_PA07B_ADC_AIN7,
			PIN_PB00B_ADC_AIN8,  PIN_PB01B_ADC_AIN9,
			PIN_PB02B_ADC_AIN10, PIN_PB03B_ADC_AIN11,
			PIN_PB04B_ADC_AIN12, PIN_PB05B_ADC_AIN13,
			PIN_PB06B_ADC_AIN14, PIN_PB07B_ADC_AIN15,
			PIN_PA08B_ADC_AIN16, PIN_PA09B_ADC_AIN17,
			PIN_PA10B_ADC_AIN18, PIN_PA11B_ADC_AIN19,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
#elif (SAML22G)
			PIN_PA02B_ADC_AIN0,  PIN_PA03B_ADC_AIN1,
			PIN_PB08B_ADC_AIN2,  PIN_PB09B_ADC_AIN3,
			PIN_PA04B_ADC_AIN4,  PIN_PA05B_ADC_AIN5,
			PIN_PA06B_ADC_AIN6,  PIN_PA07B_ADC_AIN7,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_PB02B_ADC_AIN10, PIN_PB03B_ADC_AIN11,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
#elif (SAML22J)
			PIN_PA02B_ADC_AIN0,  PIN_PA03B_ADC_AIN1,
			PIN_PB08B_ADC_AIN2,  PIN_PB09B_ADC_AIN3,
			PIN_PA04B_ADC_AIN4,  PIN_PA05B_ADC_AIN5,
			PIN_PA06B_ADC_AIN6,  PIN_PA07B_ADC_AIN7,
			PIN_PB00B_ADC_AIN8,  PIN_PB01B_ADC_AIN9,
			PIN_PB02B_ADC_AIN10, PIN_PB03B_ADC_AIN11,
			PIN_PB04B_ADC_AIN12, PIN_PB05B_ADC_AIN13,
			PIN_PB06B_ADC_AIN14, PIN_PB07B_ADC_AIN15,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
#elif (SAML22N)
			PIN_PA02B_ADC_AIN0,  PIN_PA03B_ADC_AIN1,
			PIN_PB08B_ADC_AIN2,  PIN_PB09B_ADC_AIN3,
			PIN_PA04B_ADC_AIN4,  PIN_PA05B_ADC_AIN5,
			PIN_PA06B_ADC_AIN6,  PIN_PA07B_ADC_AIN7,
			PIN_PB00B_ADC_AIN8,  PIN_PB01B_ADC_AIN9,
			PIN_PB02B_ADC_AIN10, PIN_PB03B_ADC_AIN11,
			PIN_PB04B_ADC_AIN12, PIN_PB05B_ADC_AIN13,
			PIN_PB06B_ADC_AIN14, PIN_PB07B_ADC_AIN15,
			PIN_PC00B_ADC_AIN16, PIN_PC01B_ADC_AIN17,
			PIN_PC02B_ADC_AIN18, PIN_PC03B_ADC_AIN19,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
			PIN_INVALID_ADC_AIN, PIN_INVALID_ADC_AIN,
#   else
#       error ADC pin mappings are not defined for this device.
#   endif
	};
#elif (SAMC20)
	const uint32_t pinmapping[] = {
#   if (SAMC20E)
			PIN_PA02B_ADC0_AIN0,  PIN_PA03B_ADC0_AIN1,
			PIN_INVALID_ADC_AIN,  PIN_INVALID_ADC_AIN,
			PIN_PA04B_ADC0_AIN4,  PIN_PA05B_ADC0_AIN5,
			PIN_PA06B_ADC0_AIN6,  PIN_PA07B_ADC0_AIN7,
			PIN_PA08B_ADC0_AIN8,  PIN_PA09B_ADC0_AIN9,
			PIN_PA10B_ADC0_AIN10, PIN_PA11B_ADC0_AIN11,
#   elif (SAMC20G)
			PIN_PA02B_ADC0_AIN0,  PIN_PA03B_ADC0_AIN1,
			PIN_PB08B_ADC0_AIN2,  PIN_PB09B_ADC0_AIN3,
			PIN_PA04B_ADC0_AIN4,  PIN_PA05B_ADC0_AIN5,
			PIN_PA06B_ADC0_AIN6,  PIN_PA07B_ADC0_AIN7,
			PIN_PA08B_ADC0_AIN8,  PIN_PA09B_ADC0_AIN9,
			PIN_PA10B_ADC0_AIN10, PIN_PA11B_ADC0_AIN11,
#   elif (SAMC20J)
			PIN_PA02B_ADC0_AIN0,  PIN_PA03B_ADC0_AIN1,
			PIN_PB08B_ADC0_AIN2,  PIN_PB09B_ADC0_AIN3,
			PIN_PA04B_ADC0_AIN4,  PIN_PA05B_ADC0_AIN5,
			PIN_PA06B_ADC0_AIN6,  PIN_PA07B_ADC0_AIN7,
			PIN_PA08B_ADC0_AIN8,  PIN_PA09B_ADC0_AIN9,
			PIN_PA10B_ADC0_AIN10, PIN_PA11B_ADC0_AIN11,
#   else
#       error ADC pin mappings are not defined for this device.
#   endif
	};
#elif (SAMC21)
	const uint32_t *pinmapping = NULL;;
	const uint32_t pinmapping0[] = {
#   if (SAMC21E)
			PIN_PA02B_ADC0_AIN0,  PIN_PA03B_ADC0_AIN1,
			PIN_INVALID_ADC_AIN,  PIN_INVALID_ADC_AIN,
			PIN_PA04B_ADC0_AIN4,  PIN_PA05B_ADC0_AIN5,
			PIN_PA06B_ADC0_AIN6,  PIN_PA07B_ADC0_AIN7,
			PIN_PA08B_ADC0_AIN8,  PIN_PA09B_ADC0_AIN9,
			PIN_PA10B_ADC0_AIN10, PIN_PA11B_ADC0_AIN11,
#   elif (SAMC21G)
			PIN_PA02B_ADC0_AIN0,  PIN_PA03B_ADC0_AIN1,
			PIN_PB08B_ADC0_AIN2,  PIN_PB09B_ADC0_AIN3,
			PIN_PA04B_ADC0_AIN4,  PIN_PA05B_ADC0_AIN5,
			PIN_PA06B_ADC0_AIN6,  PIN_PA07B_ADC0_AIN7,
			PIN_PA08B_ADC0_AIN8,  PIN_PA09B_ADC0_AIN9,
			PIN_PA10B_ADC0_AIN10, PIN_PA11B_ADC0_AIN11,
#   elif (SAMC21J)
			PIN_PA02B_ADC0_AIN0,  PIN_PA03B_ADC0_AIN1,
			PIN_PB08B_ADC0_AIN2,  PIN_PB09B_ADC0_AIN3,
			PIN_PA04B_ADC0_AIN4,  PIN_PA05B_ADC0_AIN5,
			PIN_PA06B_ADC0_AIN6,  PIN_PA07B_ADC0_AIN7,
			PIN_PA08B_ADC0_AIN8,  PIN_PA09B_ADC0_AIN9,
			PIN_PA10B_ADC0_AIN10, PIN_PA11B_ADC0_AIN11,
#   else
#       error ADC pin mappings are not defined for this device.
#   endif
		};
	const uint32_t pinmapping1[] = {
#   if (SAMC21E)
		PIN_INVALID_ADC_AIN,  PIN_INVALID_ADC_AIN,
		PIN_INVALID_ADC_AIN,  PIN_INVALID_ADC_AIN,
		PIN_INVALID_ADC_AIN,  PIN_INVALID_ADC_AIN,
		PIN_INVALID_ADC_AIN,  PIN_INVALID_ADC_AIN,
		PIN_INVALID_ADC_AIN,  PIN_INVALID_ADC_AIN,
		PIN_PA08B_ADC1_AIN10, PIN_PA09B_ADC1_AIN11,
#   elif (SAMC21G)
		PIN_INVALID_ADC_AIN,  PIN_INVALID_ADC_AIN,
		PIN_PB02B_ADC1_AIN2,  PIN_PB03B_ADC1_AIN3,
		PIN_PB08B_ADC1_AIN4,  PIN_PB09B_ADC1_AIN5,
		PIN_INVALID_ADC_AIN,  PIN_INVALID_ADC_AIN,
		PIN_INVALID_ADC_AIN,  PIN_INVALID_ADC_AIN,
		PIN_PA08B_ADC1_AIN10, PIN_PA09B_ADC1_AIN11,
#   elif (SAMC21J)
		PIN_PB00B_ADC1_AIN0,  PIN_PB01B_ADC1_AIN1,
		PIN_PB02B_ADC1_AIN2,  PIN_PB03B_ADC1_AIN3,
		PIN_PB08B_ADC1_AIN4,  PIN_PB09B_ADC1_AIN5,
		PIN_PB04B_ADC1_AIN6,  PIN_PB05B_ADC1_AIN7,
		PIN_PB06B_ADC1_AIN8,  PIN_PB07B_ADC1_AIN9,
		PIN_PA08B_ADC1_AIN10, PIN_PA09B_ADC1_AIN11,
#   else
#       error ADC pin mappings are not defined for this device.
#   endif
	};

	switch(index) {
	case 0:
		pinmapping = pinmapping0;
		break;
	case 1:
		pinmapping = pinmapping1;
		break;
	default:
		break;
	}
	Assert(pinmapping);
#endif

	uint32_t pin_map_result = PIN_INVALID_ADC_AIN;

	if (pin <= _adc_extchannel_msb[index]) {
		pin_map_result = pinmapping[pin >> ADC_INPUTCTRL_MUXPOS_Pos];

		Assert(pin_map_result != PIN_INVALID_ADC_AIN);

		struct system_pinmux_config config;
		system_pinmux_get_config_defaults(&config);

		/* Analog functions are all on MUX setting B */
		config.input_pull   = SYSTEM_PINMUX_PIN_PULL_NONE;
		config.mux_position = 1;

		system_pinmux_pin_set_config(pin_map_result, &config);
	}
}

/**
 * \internal Writes an ADC configuration to the hardware module.
 *
 * Writes out a given ADC module configuration to the hardware module.
 *
 * \param[in]  index        Index of the ADC module instance
 * \param[out] module_inst  Pointer to the ADC software instance struct
 * \param[in]  config       Pointer to configuration struct
 *
 * \return Status of the configuration procedure.
 * \retval STATUS_OK               The configuration was successful
 * \retval STATUS_ERR_INVALID_ARG  Invalid argument(s) were provided
 */
static enum status_code _adc_set_config(
		uint8_t index,
		struct adc_module *const module_inst,
		struct adc_config *const config)
{
	uint8_t adjres = 0;
	uint32_t resolution = ADC_RESOLUTION_16BIT;
	enum adc_accumulate_samples accumulate = ADC_ACCUMULATE_DISABLE;

	/* Get the hardware module pointer */
	Adc *const adc_module = module_inst->hw;

	/* Configure GCLK channel and enable clock */
	struct system_gclk_chan_config gclk_chan_conf;
	system_gclk_chan_get_config_defaults(&gclk_chan_conf);
	gclk_chan_conf.source_generator = config->clock_source;
	system_gclk_chan_set_config(_adc_gclk_ids[index], &gclk_chan_conf);
	system_gclk_chan_enable(_adc_gclk_ids[index]);

	/* Setup pinmuxing for analog inputs */
	_adc_configure_ain_pin(index, config->positive_input);
	_adc_configure_ain_pin(index, config->negative_input);

	/* Set pinmux for positive input sequence*/
	for(uint8_t i=0;i <= _adc_extchannel_msb[index];i++){
		if(config->positive_input_sequence_mask_enable & (1 << i)){
			_adc_configure_ain_pin(index, i);
		}
	}

	/* Configure run in standby and on demand */
	adc_module->CTRLA.reg = ((config->run_in_standby << ADC_CTRLA_RUNSTDBY_Pos)
						    | (config->on_demand << ADC_CTRLA_ONDEMAND_Pos)) ;

	/* Configure reference */
	adc_module->REFCTRL.reg =
			(config->reference_compensation_enable << ADC_REFCTRL_REFCOMP_Pos)
			| (config->reference);

	/* Set adjusting result and number of samples */
	switch (config->resolution) {

	case ADC_RESOLUTION_CUSTOM:
		adjres = config->divide_result;
		accumulate = config->accumulate_samples;
		/* 16-bit result register */
		resolution = ADC_RESOLUTION_16BIT;
		break;

	case ADC_RESOLUTION_13BIT:
		/* Increase resolution by 1 bit */
		adjres = ADC_DIVIDE_RESULT_2;
		accumulate = ADC_ACCUMULATE_SAMPLES_4;
		/* 16-bit result register */
		resolution = ADC_RESOLUTION_16BIT;
		break;

	case ADC_RESOLUTION_14BIT:
		/* Increase resolution by 2 bit */
		adjres = ADC_DIVIDE_RESULT_4;
		accumulate = ADC_ACCUMULATE_SAMPLES_16;
		/* 16-bit result register */
		resolution = ADC_RESOLUTION_16BIT;
		break;
	case ADC_RESOLUTION_15BIT:
		/* Increase resolution by 3 bit */
		adjres = ADC_DIVIDE_RESULT_2;
		accumulate = ADC_ACCUMULATE_SAMPLES_64;
		/* 16-bit result register */
		resolution = ADC_RESOLUTION_16BIT;
		break;

	case ADC_RESOLUTION_16BIT:
		/* Increase resolution by 4 bit */
		adjres = ADC_DIVIDE_RESULT_DISABLE;
		accumulate = ADC_ACCUMULATE_SAMPLES_256;
		/* 16-bit result register */
		resolution = ADC_RESOLUTION_16BIT;
		break;
	case ADC_RESOLUTION_8BIT:
		/* 8-bit result register */
		resolution = ADC_RESOLUTION_8BIT;
		break;
	case ADC_RESOLUTION_10BIT:
		/* 10-bit result register */
		resolution = ADC_RESOLUTION_10BIT;
		break;
	case ADC_RESOLUTION_12BIT:
		/* 12-bit result register */
		resolution = ADC_RESOLUTION_12BIT;
		break;

	default:
		/* Unknown. Abort. */
		return STATUS_ERR_INVALID_ARG;
	}

	adc_module->AVGCTRL.reg = ADC_AVGCTRL_ADJRES(adjres) | accumulate;

	while (adc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Check validity of sample length value */
	if (config->sample_length > 63) {
		return STATUS_ERR_INVALID_ARG;
	} else {
		/* Configure sample length */
		adc_module->SAMPCTRL.reg =
				(config->sample_length << ADC_SAMPCTRL_SAMPLEN_Pos)
				| (config->sampling_time_compensation_enable << ADC_SAMPCTRL_OFFCOMP_Pos);
	}

	while (adc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Configure CTRLB */
	adc_module->CTRLB.reg =
			config->clock_prescaler;
	adc_module->CTRLC.reg =
			resolution |
			(config->correction.correction_enable << ADC_CTRLC_CORREN_Pos) |
			(config->freerunning << ADC_CTRLC_FREERUN_Pos) |
			(config->left_adjust << ADC_CTRLC_LEFTADJ_Pos) |
			(config->differential_mode << ADC_CTRLC_DIFFMODE_Pos);

	while (adc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Check validity of window thresholds */
	if (config->window.window_mode != ADC_WINDOW_MODE_DISABLE) {
		switch (resolution) {
		case ADC_RESOLUTION_8BIT:
			if (config->differential_mode &&
					(config->window.window_lower_value > 127 ||
					config->window.window_lower_value < -128 ||
					config->window.window_upper_value > 127 ||
					config->window.window_upper_value < -128)) {
				/* Invalid value */
				return STATUS_ERR_INVALID_ARG;
			} else if (config->window.window_lower_value > 255 ||
					config->window.window_upper_value > 255){
				/* Invalid value */
				return STATUS_ERR_INVALID_ARG;
			}
			break;
		case ADC_RESOLUTION_10BIT:
			if (config->differential_mode &&
					(config->window.window_lower_value > 511 ||
					config->window.window_lower_value < -512 ||
					config->window.window_upper_value > 511 ||
					config->window.window_upper_value < -512)) {
				/* Invalid value */
				return STATUS_ERR_INVALID_ARG;
			} else if (config->window.window_lower_value > 1023 ||
					config->window.window_upper_value > 1023){
				/* Invalid value */
				return STATUS_ERR_INVALID_ARG;
			}
			break;
		case ADC_RESOLUTION_12BIT:
			if (config->differential_mode &&
					(config->window.window_lower_value > 2047 ||
					config->window.window_lower_value < -2048 ||
					config->window.window_upper_value > 2047 ||
					config->window.window_upper_value < -2048)) {
				/* Invalid value */
				return STATUS_ERR_INVALID_ARG;
			} else if (config->window.window_lower_value > 4095 ||
					config->window.window_upper_value > 4095){
				/* Invalid value */
				return STATUS_ERR_INVALID_ARG;
			}
			break;
		case ADC_RESOLUTION_16BIT:
			if (config->differential_mode &&
					(config->window.window_lower_value > 32767 ||
					config->window.window_lower_value < -32768 ||
					config->window.window_upper_value > 32767 ||
					config->window.window_upper_value < -32768)) {
				/* Invalid value */
				return STATUS_ERR_INVALID_ARG;
			} else if (config->window.window_lower_value > 65535 ||
					config->window.window_upper_value > 65535){
				/* Invalid value */
				return STATUS_ERR_INVALID_ARG;
			}
			break;
		}
	}

	/* Configure window mode */
	adc_module->CTRLC.reg |= config->window.window_mode;

	while (adc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Configure lower threshold */
	adc_module->WINLT.reg =
			config->window.window_lower_value << ADC_WINLT_WINLT_Pos;

	while (adc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Configure lower threshold */
	adc_module->WINUT.reg = config->window.window_upper_value <<
			ADC_WINUT_WINUT_Pos;

	while (adc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Configure pin scan mode and positive and negative input pins */
	adc_module->INPUTCTRL.reg =
			config->negative_input |
			config->positive_input;

	while (adc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	/* Configure events */
	adc_module->EVCTRL.reg = config->event_action;

	/* Disable all interrupts */
	adc_module->INTENCLR.reg =
			(1 << ADC_INTENCLR_WINMON_Pos) |(1 << ADC_INTENCLR_OVERRUN_Pos)
			| (1 << ADC_INTENCLR_RESRDY_Pos);

	if (config->correction.correction_enable){
		/* Make sure gain_correction value is valid */
		if (config->correction.gain_correction > ADC_GAINCORR_GAINCORR_Msk) {
			return STATUS_ERR_INVALID_ARG;
		} else {
			/* Set gain correction value */
			adc_module->GAINCORR.reg = config->correction.gain_correction <<
					ADC_GAINCORR_GAINCORR_Pos;
		}

		while (adc_is_syncing(module_inst)) {
			/* Wait for synchronization */
		}

		/* Make sure offset correction value is valid */
		if (config->correction.offset_correction > 2047 ||
				config->correction.offset_correction < -2048) {
			return STATUS_ERR_INVALID_ARG;
		} else {
			/* Set offset correction value */
			adc_module->OFFSETCORR.reg = config->correction.offset_correction <<
					ADC_OFFSETCORR_OFFSETCORR_Pos;
		}

		while (adc_is_syncing(module_inst)) {
			/* Wait for synchronization */
		}
	}

	/* Load in the fixed device ADC calibration constants */
	adc_module->CALIB.reg =
			ADC_CALIB_BIASREFBUF(
				(*(uint32_t *)_adc_biasrefbuf_addr[index] >> _adc_biasrefbuf_pos[index])
			) |
			ADC_CALIB_BIASCOMP(
				(*(uint32_t *)_adc_biascomp_addr[index] >> _adc_biascomp_pos[index])
			);

	return STATUS_OK;
}

/**
 * \brief Initializes the ADC.
 *
 * Initializes the ADC device struct and the hardware module based on the
 * given configuration struct values.
 *
 * \param[out] module_inst Pointer to the ADC software instance struct
 * \param[in]  hw          Pointer to the ADC module instance
 * \param[in]  config      Pointer to the configuration struct
 *
 * \return Status of the initialization procedure.
 * \retval STATUS_OK                The initialization was successful
 * \retval STATUS_ERR_INVALID_ARG   Invalid argument(s) were provided
 * \retval STATUS_BUSY          The module is busy with a reset operation
 * \retval STATUS_ERR_DENIED        The module is enabled
 */
enum status_code adc_init(
		struct adc_module *const module_inst,
		Adc *hw,
		struct adc_config *config)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(hw);
	Assert(config);

	/* Temporary variable to hold ADC instance number */
	uint8_t instance = _adc_get_inst_index(hw);

	/* Associate the software module instance with the hardware module */
	module_inst->hw = hw;
#if (SAML22)
	/* Turn on the digital interface clock */
	system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBC, MCLK_APBCMASK_ADC);
#elif (SAML21) || (SAMR30)
	/* Turn on the digital interface clock */
	system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBD, MCLK_APBDMASK_ADC);
#else
	system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBC, _adc_apbcmasks[instance]);
#endif

	if (hw->CTRLA.reg & ADC_CTRLA_SWRST) {
		/* We are in the middle of a reset. Abort. */
		return STATUS_BUSY;
	}

	while (adc_is_syncing(module_inst)) {
		/* Wait for synchronization */
	}

	if (hw->CTRLA.reg & ADC_CTRLA_ENABLE) {
		/* Module must be disabled before initialization. Abort. */
		return STATUS_ERR_DENIED;
	}

	/* Store the selected reference for later use */
	module_inst->reference = config->reference;

	/* Make sure the voltage reference is enabled if requested by the config */
	if (module_inst->reference == ADC_REFERENCE_INTREF) {
		system_voltage_reference_enable(SYSTEM_VOLTAGE_REFERENCE_OUTPUT);
	}

#if ADC_CALLBACK_MODE == true
	for (uint8_t i = 0; i < ADC_CALLBACK_N; i++) {
		module_inst->callback[i] = NULL;
	};

	module_inst->registered_callback_mask = 0;
	module_inst->enabled_callback_mask = 0;
	module_inst->remaining_conversions = 0;
	module_inst->job_status = STATUS_OK;

	_adc_instances[instance] = module_inst;

	if (config->event_action == ADC_EVENT_ACTION_DISABLED &&
			!config->freerunning) {
		module_inst->software_trigger = true;
	} else {
		module_inst->software_trigger = false;
	}
#endif

	/* Write configuration to module */
	return _adc_set_config(instance, module_inst, config);
}
