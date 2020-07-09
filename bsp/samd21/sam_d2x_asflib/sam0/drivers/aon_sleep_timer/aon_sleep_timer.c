/**
 * \file
 *
 * \brief SAM AON Sleep Timer Driver for SAMB11
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
#include "aon_sleep_timer.h"

static aon_sleep_timer_callback_t aon_sleep_timer_callback = NULL;

static void delay_cycle(uint32_t cycles)
{
	volatile uint32_t i = 0;

	for (i = 0; i < cycles*100; i++) {
		asm volatile ("nop");
	}
}

/**
 * \brief Initializes config with predefined default values.
 *
 * This function will initialize a given AON Sleep Timer configuration structure to
 * a set of known default values. This function should be called on
 * any new instance of the configuration structures before being
 * modified by the user application.
 *
 * \param[out]  config  Pointer to a AON Sleep Timer module configuration structure to set
 */
void aon_sleep_timer_get_config_defaults(struct aon_sleep_timer_config *config)
{
	/* Default configuration values */
	config->wakeup = AON_SLEEP_TIMER_WAKEUP_ARM;
	config->mode = AON_SLEEP_TIMER_SINGLE_MODE;
	config->counter = 32000;
}

/**
 * \brief Disable AON Sleep Timer module instance.
 *
 * AON Sleep Timer module instance disable.
 */
void aon_sleep_timer_disable(void)
{
	uint32_t regval;

	AON_SLEEP_TIMER0->SINGLE_COUNT_DURATION.reg = 0;
	regval = AON_SLEEP_TIMER0->CONTROL.reg;
	regval &= ~AON_SLEEP_TIMER_CONTROL_RELOAD_ENABLE;
	regval &= ~AON_SLEEP_TIMER_CONTROL_SINGLE_COUNT_ENABLE;
	AON_SLEEP_TIMER0->CONTROL.reg = regval;

	while (AON_SLEEP_TIMER0->CONTROL.reg & (1 << 14)) {
	}
}

/**
 * \brief Get AON Sleep Timer module instance current value.
 *
 * \retval Current value
 */
uint32_t aon_sleep_timer_get_current_value(void)
{
	return AON_SLEEP_TIMER0->CURRENT_COUNT_VALUE.reg;
}

/**
 * \brief If AON Sleep Timer is active
 *
 * \return Active status of the AON Sleep Timer.
 */
bool aon_sleep_timer_sleep_timer_active(void)
{
	return AON_SLEEP_TIMER0->CONTROL.bit.SLEEP_TIMER_ACTIVE;
}

/**
 * \brief Clear AON Sleep Timer module instance interrupt.
 *
 * This flag will be cleared automatically once the IRQ
 * has been seen on the sleep clock.
 */
void aon_sleep_timer_clear_interrup(void)
{
	AON_SLEEP_TIMER0->CONTROL.reg |= AON_SLEEP_TIMER_CONTROL_IRQ_CLEAR;
}

/**
 * \brief Registers a callback.
 *
 * Registers and enable a callback function which is implemented by the user.
 *
 * \param[in]     callback_func Pointer to callback function
 */
void aon_sleep_timer_register_callback(aon_sleep_timer_callback_t fun)
{
	aon_sleep_timer_callback = fun;
}

/**
 * \brief Unregisters a callback.
 *
 * Unregisters and disable a callback function implemented by the user.
 *
 */
void aon_sleep_timer_unregister_callback(void)
{
	aon_sleep_timer_callback = NULL;
}

/**
 * \brief Timer ISR handler.
 *
 * Timer ISR handler.
 *
 */
static void aon_sleep_timer_isr_handler(void)
{
	aon_sleep_timer_clear_interrup();

	if (aon_sleep_timer_callback) {
		aon_sleep_timer_callback();
	}
}

/**
 * \brief Initializes AON Sleep Timer module instance.
 *
 * Initializes the AON Sleep Timer module, based on the parameters,
 * and start timer.
 *
 * \param[in]     config       Pointer to the AON Sleep Timer configuration options struct
 *
 */
void aon_sleep_timer_init(const struct aon_sleep_timer_config *config)
{
	uint32_t aon_st_ctrl = 0;

	AON_PWR_SEQ0->AON_ST_WAKEUP_CTRL.reg = AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_RESETVALUE;
	if (config->wakeup == AON_SLEEP_TIMER_WAKEUP_ARM_BLE) {
		AON_PWR_SEQ0->AON_ST_WAKEUP_CTRL.reg |=
				AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_ARM_ENABLE |
				AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_BLE_ENABLE;
	} else if (config->wakeup == AON_SLEEP_TIMER_WAKEUP_ARM) {
		AON_PWR_SEQ0->AON_ST_WAKEUP_CTRL.reg |=
				AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_ARM_ENABLE;
	}

	aon_st_ctrl = AON_SLEEP_TIMER0->CONTROL.reg;
	while (aon_st_ctrl & ((1UL << 31) - 1)) {
		AON_SLEEP_TIMER0->CONTROL.reg = 0;
		delay_cycle(3);
		while (aon_st_ctrl & ((config->mode == AON_SLEEP_TIMER_RELOAD_MODE) ?
				(1 << 9) : (1 << 14))) {
			aon_st_ctrl = AON_SLEEP_TIMER0->CONTROL.reg;
		}
		aon_st_ctrl = AON_SLEEP_TIMER0->CONTROL.reg;
	}

	if (config->mode == AON_SLEEP_TIMER_RELOAD_MODE) {
		/* Reload counter will start here */
		AON_SLEEP_TIMER0->SINGLE_COUNT_DURATION.reg = config->counter;
		AON_SLEEP_TIMER0->CONTROL.reg = AON_SLEEP_TIMER_CONTROL_RELOAD_ENABLE;
	} else {
		/* Single counter will start here */
		AON_SLEEP_TIMER0->SINGLE_COUNT_DURATION.reg = config->counter;
		AON_SLEEP_TIMER0->CONTROL.reg = AON_SLEEP_TIMER_CONTROL_SINGLE_COUNT_ENABLE;
	}

	if (config->mode == AON_SLEEP_TIMER_SINGLE_MODE) {
		while ((AON_SLEEP_TIMER0->CONTROL.reg &
				AON_SLEEP_TIMER_CONTROL_SLP_TIMER_SINGLE_COUNT_ENABLE_DLY_Msk)
				!= AON_SLEEP_TIMER_CONTROL_SLP_TIMER_SINGLE_COUNT_ENABLE_DLY_Msk) {
		}
	}

	system_register_isr(RAM_ISR_TABLE_AON_SLEEP_TIMER_INDEX, (uint32_t)aon_sleep_timer_isr_handler);
}
