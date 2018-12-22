/**
 * \file
 *
 * \brief SAM PWM Driver for SAMB11
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
#include "pwm.h"
#include "system_sam_b.h"

/**
 * \internal Get the register configuration values by PWM device
 */
static uint32_t _pwm_reg_output_polarity(enum pwm_device_select device_select)
{
	switch (device_select) {
		case PWM0:
			return LPMCU_MISC_REGS_PWM0_CTRL_OUTPUT_POLARITY;
		case PWM1:
			return LPMCU_MISC_REGS_PWM1_CTRL_OUTPUT_POLARITY;
		case PWM2:
			return LPMCU_MISC_REGS_PWM2_CTRL_OUTPUT_POLARITY;
		case PWM3:
			return LPMCU_MISC_REGS_PWM3_CTRL_OUTPUT_POLARITY;

		default:
			return 0;
	}
}

/**
 * \internal Get the register configuration values by PWM device
 */
static uint32_t _pwm_reg_agcdata_fmt(enum pwm_device_select device_select)
{
	switch (device_select) {
		case PWM0:
			return LPMCU_MISC_REGS_PWM0_CTRL_AGCDATA_FMT;
		case PWM1:
			return LPMCU_MISC_REGS_PWM1_CTRL_AGCDATA_FMT;
		case PWM2:
			return LPMCU_MISC_REGS_PWM2_CTRL_AGCDATA_FMT;
		case PWM3:
			return LPMCU_MISC_REGS_PWM3_CTRL_AGCDATA_FMT;

		default:
			return 0;
	}
}

/**
 * \internal Get the register configuration values by PWM device
 */
static uint32_t _pwm_reg_sample_method(enum pwm_device_select device_select, bool value)
{
	switch (device_select) {
		case PWM0:
			return (LPMCU_MISC_REGS_PWM0_CTRL_SAMPLE_METHOD &
					((value) << LPMCU_MISC_REGS_PWM0_CTRL_SAMPLE_METHOD_Pos));
		case PWM1:
			return (LPMCU_MISC_REGS_PWM1_CTRL_SAMPLE_METHOD &
					((value) << LPMCU_MISC_REGS_PWM1_CTRL_SAMPLE_METHOD_Pos));
		case PWM2:
			return (LPMCU_MISC_REGS_PWM2_CTRL_SAMPLE_METHOD &
					((value) << LPMCU_MISC_REGS_PWM2_CTRL_SAMPLE_METHOD_Pos));
		case PWM3:
			return (LPMCU_MISC_REGS_PWM3_CTRL_SAMPLE_METHOD & 
					((value) << LPMCU_MISC_REGS_PWM3_CTRL_SAMPLE_METHOD_Pos));

		default:
			return 0;
	}
}

/**
 * \internal Get the register configuration values by PWM device
 */
static uint32_t _pwm_reg_period(enum pwm_device_select device_select, enum pwm_period value)
{
	switch (device_select) {
		case PWM0:
			return LPMCU_MISC_REGS_PWM0_CTRL_PWM_PERIOD(value);
		case PWM1:
			return LPMCU_MISC_REGS_PWM1_CTRL_PWM_PERIOD(value);
		case PWM2:
			return LPMCU_MISC_REGS_PWM2_CTRL_PWM_PERIOD(value);
		case PWM3:
			return LPMCU_MISC_REGS_PWM3_CTRL_PWM_PERIOD(value);

		default:
			return 0;
	}
}

/**
 * \internal Get the register configuration values by PWM device
 */
static uint32_t _pwm_reg_agcdata_in(
				enum pwm_device_select device_select, \
				bool agcdata_format, \
				uint8_t duty_cycle)
{
	int32_t agcdata_in;

	if (agcdata_format) {
		agcdata_in = (uint16_t)((1024 * duty_cycle) / 100);
	} else {
		agcdata_in = (int16_t)((1024 * duty_cycle) / 100 - 512);
	}
	switch (device_select) {
		case PWM0:
			return LPMCU_MISC_REGS_PWM0_CTRL_AGCDATA_IN(agcdata_in);
		case PWM1:
			return LPMCU_MISC_REGS_PWM1_CTRL_AGCDATA_IN(agcdata_in);
		case PWM2:
			return LPMCU_MISC_REGS_PWM2_CTRL_AGCDATA_IN(agcdata_in);
		case PWM3:
			return LPMCU_MISC_REGS_PWM3_CTRL_AGCDATA_IN(agcdata_in);

		default:
			return 0;
	}
}

/**
 * \internal Get the register configuration values by PWM device
 */
static uint32_t _pwm_reg_clock_sel(enum pwm_device_select device_select, enum pwm_clock_select value)
{
	switch (device_select) {
		case PWM0:
			return LPMCU_MISC_REGS_PWM0_CTRL_CLOCK_SEL(value);
		case PWM1:
			return LPMCU_MISC_REGS_PWM1_CTRL_CLOCK_SEL(value);
		case PWM2:
			return LPMCU_MISC_REGS_PWM2_CTRL_CLOCK_SEL(value);
		case PWM3:
			return LPMCU_MISC_REGS_PWM3_CTRL_CLOCK_SEL(value);

		default:
			return 0;
	}
}

/**
 *  \brief Initializes a pwm configuration structure to defaults.
 *
 *  Initializes a given pwm configuration structure to a set of
 *  known default values. This function should be called on all new
 *  instances of these configuration structures before being modified by the
 *  user application.
 *
 *  The default configuration is as follows:
 *   \li Not to inverse the polarity
 *   \li Sample method 0
 *   \li PWM period is 4
 *   \li Duty cycle is 50%
 *   \li Clock is 26MHz
 *   \li Output frequency is 25.4KHz
 *   \li Pinmux pad
 *
 *  \param[out] config  Configuration structure to initialize to default values
 */
void pwm_get_config_defaults(struct pwm_config *const config)
{
	config->output_polarity = false;
	config->agcdata_format = false;
	config->sample_method = PWM_SAMPLE_METHOD_0;
	config->period = PWM_PERIOD_4;
	config->duty_cycle = 50;
	config->clock_select = PWM_CLOCK_SELECT_26_0;
	config->pin_number_pad = 0;
	config->pinmux_sel_pad = 0;
}

/**
 * \brief Set the duty cycle of the PWM module.
 *
 * This function will set the duty cycle of the PWM module, based on the values
 * of setting.
 *
 * \param[in]   device_select   PWM device
 * \param[in]   duty_cycle      This value specifies the duty cycle(%)
 */
void pwm_set_duty_cycle(enum pwm_device_select device_select, \
					uint8_t duty_cycle)
{
	bool agcdata_format;
	uint32_t temp;

	switch(device_select) {
		case PWM0:
			agcdata_format = LPMCU_MISC_REGS0->PWM0_CTRL.bit.AGCDATA_FMT;
			temp = LPMCU_MISC_REGS0->PWM0_CTRL.reg;
			temp &= ~LPMCU_MISC_REGS_PWM0_CTRL_AGCDATA_IN_Msk;
			temp |= _pwm_reg_agcdata_in(device_select, agcdata_format, duty_cycle);
			LPMCU_MISC_REGS0->PWM0_CTRL.reg = temp;
			break;

		case PWM1:
			agcdata_format = LPMCU_MISC_REGS0->PWM1_CTRL.bit.AGCDATA_FMT;
			temp = LPMCU_MISC_REGS0->PWM1_CTRL.reg;
			temp &= ~LPMCU_MISC_REGS_PWM1_CTRL_AGCDATA_IN_Msk;
			temp |= _pwm_reg_agcdata_in(device_select, agcdata_format, duty_cycle);
			LPMCU_MISC_REGS0->PWM1_CTRL.reg = temp;
			break;

		case PWM2:
			agcdata_format = LPMCU_MISC_REGS0->PWM2_CTRL.bit.AGCDATA_FMT;
			temp = LPMCU_MISC_REGS0->PWM2_CTRL.reg;
			temp &= ~LPMCU_MISC_REGS_PWM2_CTRL_AGCDATA_IN_Msk;
			temp |= _pwm_reg_agcdata_in(device_select, agcdata_format, duty_cycle);
			LPMCU_MISC_REGS0->PWM2_CTRL.reg = temp;
			break;

		case PWM3:
			agcdata_format = LPMCU_MISC_REGS0->PWM3_CTRL.bit.AGCDATA_FMT;
			temp = LPMCU_MISC_REGS0->PWM3_CTRL.reg;
			temp &= ~LPMCU_MISC_REGS_PWM3_CTRL_AGCDATA_IN_Msk;
			temp |= _pwm_reg_agcdata_in(device_select, agcdata_format, duty_cycle);
			LPMCU_MISC_REGS0->PWM3_CTRL.reg = temp;
			break;
	}
}

/**
 * \brief Set the period of the PWM module.
 *
 * This function will set the frequence of the PWM module, based on the values
 * of setting period.
 *
 * \param[in]   device_select   PWM device
 * \param[in]   period          Programmable PWM update period
 */
void pwm_set_period(enum pwm_device_select device_select, \
					enum pwm_period period)
{
	uint32_t reg_value;
	uint32_t temp;

	if (period > PWM_PERIOD_8) {
		reg_value = PWM_PERIOD_4;
	}
	reg_value = _pwm_reg_period(device_select, period);

	switch(device_select) {
		case PWM0:
			temp = LPMCU_MISC_REGS0->PWM0_CTRL.reg;
			temp &= ~LPMCU_MISC_REGS_PWM0_CTRL_PWM_PERIOD_Msk;
			temp |= reg_value;
			LPMCU_MISC_REGS0->PWM0_CTRL.reg = temp;
			break;

		case PWM1:
			temp = LPMCU_MISC_REGS0->PWM1_CTRL.reg;
			temp &= ~LPMCU_MISC_REGS_PWM1_CTRL_PWM_PERIOD_Msk;
			temp |= reg_value;
			LPMCU_MISC_REGS0->PWM1_CTRL.reg = temp;
			break;

		case PWM2:
			temp = LPMCU_MISC_REGS0->PWM2_CTRL.reg;
			temp &= ~LPMCU_MISC_REGS_PWM2_CTRL_PWM_PERIOD_Msk;
			temp |= reg_value;
			LPMCU_MISC_REGS0->PWM2_CTRL.reg = temp;
			break;

		case PWM3:
			temp = LPMCU_MISC_REGS0->PWM3_CTRL.reg;
			temp &= ~LPMCU_MISC_REGS_PWM3_CTRL_PWM_PERIOD_Msk;
			temp |= reg_value;
			LPMCU_MISC_REGS0->PWM3_CTRL.reg = temp;
			break;
	}
}

/**
 * \brief Initializes the PWM module
 *
 * This function will initialize the PWM module, based on the values
 * of the config struct.
 *
 * \param[in]   device_select   PWM device
 * \param[in]   config          Pointer to the config struct
 *
 * \return The status of the configuration.
 * \retval STATUS_ERR_UNSUPPORTED_DEV  If unsupported device were provided
 * \retval STATUS_OK                   If the configuration was written
 */
enum status_code pwm_init(enum pwm_device_select device_select, \
		const struct pwm_config *const config)
{
	uint32_t reg_value = 0;

	if (device_select > PWM3) {
		return STATUS_ERR_UNSUPPORTED_DEV;
	}

	if (config->output_polarity) {
		reg_value |= _pwm_reg_output_polarity(device_select);
	}

	if (config->agcdata_format) {
		reg_value |= _pwm_reg_agcdata_fmt(device_select);
	}

	reg_value |= _pwm_reg_sample_method(device_select, config->sample_method);

	/* If period > 8 will be set to 4 as default. */
	if (config->period > PWM_PERIOD_8) {
		reg_value |= _pwm_reg_period(device_select, PWM_PERIOD_4);
	} else {
		reg_value |= _pwm_reg_period(device_select, config->period);
	}
	reg_value |= _pwm_reg_agcdata_in(device_select, config->agcdata_format, \
									config->duty_cycle);

	reg_value |= _pwm_reg_clock_sel(device_select, config->clock_select);

	switch(device_select) {
		case PWM0:
			LPMCU_MISC_REGS0->PWM0_CTRL.reg = reg_value;
			break;

		case PWM1:
			LPMCU_MISC_REGS0->PWM1_CTRL.reg = reg_value;
			break;

		case PWM2:
			LPMCU_MISC_REGS0->PWM2_CTRL.reg = reg_value;
			break;

		case PWM3:
			LPMCU_MISC_REGS0->PWM3_CTRL.reg = reg_value;
			break;
	}

	struct gpio_config config_gpio;
	gpio_get_config_defaults(&config_gpio);
	config_gpio.direction = GPIO_PIN_DIR_OUTPUT;
	gpio_pin_set_config(config->pin_number_pad, &config_gpio);
	gpio_pinmux_cofiguration(config->pin_number_pad, \
							(uint16_t)(config->pinmux_sel_pad));

	return STATUS_OK;
}

/**
 * \brief Enables the PWM module
 *
 * This function will enable the PWM module.
 *
 * \param[in] device_select  PWM device
 */
void pwm_enable(enum pwm_device_select device_select)
{
	switch (device_select) {
		case PWM0:
			system_clock_peripheral_enable(PERIPHERAL_PWM0);
			LPMCU_MISC_REGS0->PWM0_CTRL.reg |= LPMCU_MISC_REGS_PWM0_CTRL_PWM_EN;
			break;

		case PWM1:
			system_clock_peripheral_enable(PERIPHERAL_PWM1);
			LPMCU_MISC_REGS0->PWM1_CTRL.reg |= LPMCU_MISC_REGS_PWM1_CTRL_PWM_EN;
			break;

		case PWM2:
			system_clock_peripheral_enable(PERIPHERAL_PWM2);
			LPMCU_MISC_REGS0->PWM2_CTRL.reg |= LPMCU_MISC_REGS_PWM2_CTRL_PWM_EN;
			break;

		case PWM3:
			system_clock_peripheral_enable(PERIPHERAL_PWM3);
			LPMCU_MISC_REGS0->PWM3_CTRL.reg |= LPMCU_MISC_REGS_PWM3_CTRL_PWM_EN;
			break;
	}
}

/**
 * \brief Disable the PWM module
 *
 * This function will disable the PWM module.
 *
 * \param[in] device_select  PWM device
 */
void pwm_disable(enum pwm_device_select device_select)
{
	switch (device_select) {
		case PWM0:
			system_clock_peripheral_disable(PERIPHERAL_PWM0);
			LPMCU_MISC_REGS0->PWM0_CTRL.reg &= ~LPMCU_MISC_REGS_PWM0_CTRL_PWM_EN;
			break;

		case PWM1:
			system_clock_peripheral_disable(PERIPHERAL_PWM1);
			LPMCU_MISC_REGS0->PWM1_CTRL.reg &= ~LPMCU_MISC_REGS_PWM1_CTRL_PWM_EN;
			break;

		case PWM2:
			system_clock_peripheral_disable(PERIPHERAL_PWM2);
			LPMCU_MISC_REGS0->PWM2_CTRL.reg &= ~LPMCU_MISC_REGS_PWM2_CTRL_PWM_EN;
			break;

		case PWM3:
			system_clock_peripheral_disable(PERIPHERAL_PWM3);
			LPMCU_MISC_REGS0->PWM3_CTRL.reg &= ~LPMCU_MISC_REGS_PWM3_CTRL_PWM_EN;
			break;
	}
}

/**
 * \brief Reset the PWM module
 *
 * This function will reset the PWM module.
 *
 * \param[in] device_select  PWM device
 */
void pwm_reset(enum pwm_device_select device_select)
{
	switch (device_select) {
		case PWM0:
			system_peripheral_reset(PERIPHERAL_PWM0);
			break;

		case PWM1:
			system_peripheral_reset(PERIPHERAL_PWM1);
			break;

		case PWM2:
			system_peripheral_reset(PERIPHERAL_PWM2);
			break;

		case PWM3:
			system_peripheral_reset(PERIPHERAL_PWM3);
			break;
	}
}