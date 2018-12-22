/**
 * \file
 *
 * \brief SAMB Peripheral Analog-to-Digital Converter Driver
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

#include "adc_sam_b.h"

static enum status_code _adc_gpio_ms_enable(enum adc_input_channel channel)
{
	switch (channel) {
		case ADC_INPUT_CH_GPIO_MS1:
			AON_GP_REGS0->MS_GPIO_MODE.reg |= \
				AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_44;
			break;
		case ADC_INPUT_CH_GPIO_MS2:
			AON_GP_REGS0->MS_GPIO_MODE.reg |= \
				AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_45;
		break;
		case ADC_INPUT_CH_GPIO_MS3:
			AON_GP_REGS0->MS_GPIO_MODE.reg |= \
				AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_46;
		break;
		case ADC_INPUT_CH_GPIO_MS4:
			AON_GP_REGS0->MS_GPIO_MODE.reg |= \
				AON_GP_REGS_MS_GPIO_MODE_ANALOG_ENABLE_47;
		break;

		default:
			return STATUS_ERR_INVALID_ARG;
	}
	return STATUS_OK;
}

/**
 * \brief Initializes an ADC configuration structure to defaults
 *
 * Initializes a given ADC configuration struct to a set of known default
 * values. This function should be called on any new instance of the
 * configuration struct before being modified by the user application.
 *
 * The default configuration is as follows:
 *  \li VBATT/2 as voltage reference
 *  \li Internal reference voltage level 0.7V
 *  \li On GPIO_MS1 input channel
 *  \li Select one external input channels
 *  \li Input channel time multiplexing selection mode
 *  \li Comparator biasing current selection
 *  \li No invert ADC clock
 *  \li Fractional part for the clock divider is 0
 *  \li Integer part for the clock divider is 0x12
 *
 * \param[out] config  Pointer to configuration struct to initialize to
 *                     default values
 */
void adc_get_config_defaults(struct adc_config *const config)
{
	Assert(config);
	config->reference = ADC_REFERENCE_VBATT_2;
	config->internal_vref = ADC_INTERNAL_BUF_1_5;
	config->input_channel = ADC_INPUT_CH_GPIO_MS1;
	config->channel_mode = ADC_CH_MODE_ASSIGN;
	config->input_dynamic_range = ADC_INPUT_DYNAMIC_RANGE_3;
	config->bias_current = ADC_BIAS_CURRENT_3;
	config->invert_clock = false;
	config->frac_part = 0;
	config->int_part = 0x12;
}

/**
 * \brief Initializes the ADC
 *
 * Initializes the ADC device struct and the hardware module based on the
 * given configuration struct values.
 *
 * \param[in]  config      Pointer to the configuration struct
 *
 */
void adc_init(struct adc_config *config)
{
	/* Sanity check arguments */
	Assert(config);

	if (config->invert_clock) {
		LPMCU_MISC_REGS0->SENS_ADC_CLK_CTRL.reg = LPMCU_MISC_REGS_SENS_ADC_CLK_CTRL_INVERT;
	} else {
		LPMCU_MISC_REGS0->SENS_ADC_CLK_CTRL.reg &= ~LPMCU_MISC_REGS_SENS_ADC_CLK_CTRL_MASK;
	}

	/* Setting ADC clock */
	LPMCU_MISC_REGS0->SENS_ADC_CLK_CTRL.reg |= \
			LPMCU_MISC_REGS_SENS_ADC_CLK_CTRL_FRAC_PART(config->frac_part) | \
			LPMCU_MISC_REGS_SENS_ADC_CLK_CTRL_INT_PART(config->int_part);

	if ((config->reference == ADC_REFERENCE_GPIO_MS1) || \
		(config->reference == ADC_REFERENCE_GPIO_MS2) || \
		(config->reference == ADC_REFERENCE_GPIO_MS3) || \
		(config->reference == ADC_REFERENCE_GPIO_MS4)) {
		_adc_gpio_ms_enable(config->reference - ADC_REFERENCE_GPIO_MS1);
	}

	AON_GP_REGS0->RF_PMU_REGS_1.bit.SADC_REF_SEL = config->reference;
	AON_GP_REGS0->RF_PMU_REGS_1.bit.SADC_BIAS_RES_CTRL = config->internal_vref;

	if (config->channel_mode == ADC_CH_MODE_ASSIGN) {
		AON_GP_REGS0->RF_PMU_REGS_1.bit.SADC_CHN_CTRL = \
				AON_GP_REGS_RF_PMU_REGS_1_SADC_CHN_CTRL_1_Val;
		AON_GP_REGS0->RF_PMU_REGS_1.bit.SADC_CHN_SEL = config->input_channel;
		
		if (config->input_channel <= ADC_INPUT_CH_GPIO_MS4) {
			/* Enable GPIO_MS pin */
			_adc_gpio_ms_enable(config->input_channel);
		}
	} else if (config->channel_mode == ADC_CH_MODE_CH0_TO_CH3) {
		/* Input channels time multiplexing is between channel 0 to channel 3 */
		/* Config GPIO_MS1 ~ GPIO_MS4 pin */
		AON_GP_REGS0->MS_GPIO_MODE.reg = AON_GP_REGS_MS_GPIO_MODE_MASK;
	} else if (config->channel_mode == ADC_CH_MODE_CH4_TO_CH7) {
		/* Input channels time multiplexing is between channel 4 to channel 7 */
		AON_GP_REGS0->RF_PMU_REGS_1.bit.SADC_CHN_SEL = 0x4;
	}

	AON_GP_REGS0->RF_PMU_REGS_1.bit.CODE_IN = config->input_dynamic_range;
	AON_GP_REGS0->RF_PMU_REGS_1.bit.SADC_LP_CTRL = config->bias_current;
}

/**
 * \brief Retrieves the current module status.
 *
 * Retrieves the status of the module, giving overall state information.
 *
 * \return ADC status.
 */
uint32_t adc_get_status(void)
{
	return (LPMCU_MISC_REGS0->SENS_ADC_RAW_STATUS.reg);
}

/**
 * \brief Enables the ADC module.
 *
 * Enables an ADC module that has previously been configured.
 *
 */
void adc_enable(void)
{
	///* Enable ADC clock */
	system_clock_peripheral_enable(PERIPHERAL_ADC);

	/* Enable ADC module */
	AON_GP_REGS0->AON_PMU_CTRL.reg &= \
		~AON_GP_REGS_AON_PMU_CTRL_PMU_SENS_ADC_RST;
	AON_GP_REGS0->AON_PMU_CTRL.reg |= \
			AON_GP_REGS_AON_PMU_CTRL_PMU_SENS_ADC_EN | \
			AON_GP_REGS_AON_PMU_CTRL_PMU_BGR_EN;
	for (uint16_t i = 0; i < 0xFF; i++) {
		/* Waiting... */
	}
}

/**
 * \brief Disable the ADC module.
 *
 * Disable an ADC module that has previously been configured.
 *
 */
void adc_disable(void)
{
	/* Disable ADC clock */
	system_clock_peripheral_disable(PERIPHERAL_ADC);

	/* Disable ADC module */
	AON_GP_REGS0->AON_PMU_CTRL.reg &= \
			~(AON_GP_REGS_AON_PMU_CTRL_PMU_SENS_ADC_EN | \
			AON_GP_REGS_AON_PMU_CTRL_PMU_BGR_EN);
}

/**
 * \brief Reset the ADC module.
 *
 * Reset an ADC module that has previously been configured.
 *
 */
void adc_reset(void)
{
	/* Reset ADC module */
	system_peripheral_reset(PERIPHERAL_ADC);
}

/**
 * \brief Reads the ADC result.
 *
 * Reads the result from an ADC conversion that was previously started.
 *
 * \param[in]  input_channel  Input channel which need to read the result
 * \param[out] result         Pointer to store the result value in
 *
 * \return Status of the ADC read request.
 * \retval STATUS_OK           The result was retrieved successfully
 * \retval STATUS_BUSY         A conversion result was not ready
 */
enum status_code adc_read(enum adc_input_channel input_channel, uint16_t *result)

{
	Assert(result);

	/* The transition of the ADC_DONE signal from LO to HI indicates that the
	 * ADC conversion is done. */
	while (adc_get_status() & LPMCU_MISC_REGS_SENS_ADC_RAW_STATUS_ADC_DONE) {
		/* Waiting... */
	}

	while(!(adc_get_status() & LPMCU_MISC_REGS_SENS_ADC_RAW_STATUS_ADC_DONE)) {
		/* Waiting... */
	}

	switch (input_channel) {
		case ADC_INPUT_CH_GPIO_MS1:
		case ADC_INPUT_CH_TEMPERATURE:
			*result = LPMCU_MISC_REGS0->SENS_ADC_CH0_DATA.reg;
			break;

		case ADC_INPUT_CH_GPIO_MS2:
		case ADC_INPUT_CH_VBATT_4:
			*result = LPMCU_MISC_REGS0->SENS_ADC_CH1_DATA.reg;
			break;

		case ADC_INPUT_CH_GPIO_MS3:
		case ADC_INPUT_CH_LPD0_LDO:
			*result = LPMCU_MISC_REGS0->SENS_ADC_CH2_DATA.reg;
			break;

		case ADC_INPUT_CH_GPIO_MS4:
		case ADC_INPUT_CH_VREF:
			*result = LPMCU_MISC_REGS0->SENS_ADC_CH3_DATA.reg;
			break;
	}

	return STATUS_OK;
}