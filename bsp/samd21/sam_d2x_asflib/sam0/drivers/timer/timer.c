/**
 * \file
 *
 * \brief SAM TIMER Driver for SAMB11
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
#include "timer.h"

static timer_callback_t timer_callback;
/**
 * \brief Initializes config with predefined default values.
 *
 * This function will initialize a given TIMER configuration structure to
 * a set of known default values. This function should be called on
 * any new instance of the configuration structures before being
 * modified by the user application.
 *
 * The default configuration is as follows:
 *  \li Timer interrupt set as disable
 *  \li Set relaod value as 0
 *
 * \param[out]  config  Pointer to a TIMER module configuration structure to set
 */
void timer_get_config_defaults(struct timer_config *config)
{
	config->reload_value = 0;
	config->interrupt_enable = true;
}


/**
 * \brief Get TIMER0 module current value.
 *
 * \retval Current value
 */
uint32_t timer_get_value(void)
{
	return TIMER0->VALUE.reg;
}

/**
 * \brief Set TIMER0 module value.
 *
 * \param[in]     value        Reload value
 */
void timer_set_value(uint32_t value)
{
	TIMER0->RELOAD.reg = value;
}

/**
 * \brief Get TIMER0 module interrupt status
 *
 * \retval The status of module
 */
uint32_t timer_get_interrupt_status(void)
{
	return TIMER0->INTSTATUSCLEAR.reg;
}

/**
 * \brief Clear TIMER0 module interrupt status
 *
 * Clear the TIMER0 module interrupt status
 */
void timer_clear_interrupt_status(void)
{
	TIMER0->INTSTATUSCLEAR.reg = 1;
	/* Wait for operation finish */
	while (TIMER0->INTSTATUSCLEAR.reg);
}

/**
 * \brief Set TIMER0 module enable
 *
 * Enable the TIMER0 module
 */
void timer_enable(void)
{
	TIMER0->CTRL.reg |= TIMER_CTRL_ENABLE;
}

/**
 * \brief Set TIMER0 disable
 *
 * Disable the TIMER0 module
 */
void timer_disable(void)
{
	TIMER0->CTRL.reg &= (~TIMER_CTRL_ENABLE);
}

/**
 * \brief Registers a callback.
 *
 * Registers and enable a callback function which is implemented by the user.
 *
 * \param[in]     callback_func Pointer to callback function
 */
void timer_register_callback(timer_callback_t fun)
{
	timer_callback = fun; 
}

/**
 * \brief Unregisters a callback.
 *
 * Unregisters and disable a callback function implemented by the user.
 *
 */
void timer_unregister_callback(void)
{
	timer_callback = NULL; 
}

/**
 * \brief Timer ISR handler.
 *
 * Timer ISR handler.
 *
 */
static void timer_isr_handler(void)
{
	if (timer_get_interrupt_status()) {
		timer_clear_interrupt_status();
		
		if (timer_callback) {
			timer_callback();
		}
	}
}

/**
 * \brief Initializes TIMER0 module instance.
 *
 * Initializes the TIMER0 module, based on the given
 * configuration values.
 *
 * \param[in]     config       Pointer to the TIMER configuration options struct
 *
 * \return Status of the initialization procedure.
 */
void timer_init(const struct timer_config *config)
{
	/* Global reset */
	system_peripheral_reset(PERIPHERAL_TIMER);

	TIMER0->CTRL.reg = config->interrupt_enable << TIMER_CTRL_INTERRUPT_ENABLE_Pos;
	TIMER0->RELOAD.reg = config->reload_value;
	
	timer_callback = NULL;
	system_register_isr(RAM_ISR_TABLE_TIMER0_INDEX, (uint32_t)timer_isr_handler);
}