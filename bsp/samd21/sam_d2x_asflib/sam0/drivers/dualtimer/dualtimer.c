/**
 * \file
 *
 * \brief SAM DUALTIMER Driver for SAMB11
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
#include "dualtimer.h"

static dualtimer_callback_t dualtimer_callback_timer1 = NULL;
static dualtimer_callback_t dualtimer_callback_timer2 = NULL;
/**
 * \brief Initializes config with predefined default values.
 *
 * This function will initialize a given Dualtimer configuration structure to
 * a set of known default values. This function should be called on
 * any new instance of the configuration structures before being
 * modified by the user application.
 *
 * \param[out]  config  Pointer to a DUALTIMER module configuration structure to set
 */
void dualtimer_get_config_defaults(struct dualtimer_config *config)
{
	config->timer1.timer_enable = true;
	config->timer2.timer_enable = true;

	config->timer1.counter_mode = DUALTIMER_PERIODIC_MODE;
	config->timer2.counter_mode = DUALTIMER_PERIODIC_MODE;

	config->timer1.counter_size = DUALTIMER_COUNTER_SIZE_32BIT;
	config->timer2.counter_size = DUALTIMER_COUNTER_SIZE_32BIT;

	config->timer1.clock_prescaler = DUALTIMER_CLOCK_PRESCALER_DIV1;
	config->timer2.clock_prescaler = DUALTIMER_CLOCK_PRESCALER_DIV1;

	config->timer1.interrup_enable = true;
	config->timer2.interrup_enable = true;

	config->timer1.load_value = 0;
	config->timer2.load_value = 0;

	config->clock_source = DUALTIMER_CLK_INPUT_0;
}


/**
 * \brief Get Dualtimer module timer1/timer2 current value.
 *
 * \param[in]     timer        Timer1/Timer2
 *
 * \retval Timer1/Timer2 current value
 */
uint32_t dualtimer_get_value(enum dualtimer_timer timer)
{
	if (timer == DUALTIMER_TIMER1) {
		return DUALTIMER0->TIMER1VALUE.reg;
	} else {
		return DUALTIMER0->TIMER2VALUE.reg;
	}
}

/**
 * \brief Set Dualtimer module timer1/timer2 load value.
 *
 * \param[in]     timer        Timer1/Timer2
 * \param[in]     cur_bg       Current/Background
 * \param[in]     value        Load value
 */
void dualtimer_set_counter(enum dualtimer_timer timer,
		enum dualtimer_set_register cur_bg, uint32_t value)
{
	if (timer == DUALTIMER_TIMER1) {
		if (cur_bg == DUALTIMER_SET_CURRUNT_REG) {
			DUALTIMER0->TIMER1LOAD.reg = value;
		} else {
			DUALTIMER0->TIMER1BGLOAD.reg = value;
		}
	} else {
		if (cur_bg == DUALTIMER_SET_CURRUNT_REG) {
			DUALTIMER0->TIMER2LOAD.reg = value;
			} else {
			DUALTIMER0->TIMER2BGLOAD.reg = value;
		}
	}
}

/**
 * \brief Get Dualtimer module timer1/timer2 raw interrupt status
 *
 * \param[in]     timer        Timer1/Timer2
 *
 * \retval The raw interrupt status of timer1/timer2
 */
uint8_t dualtimer_get_status(enum dualtimer_timer timer)
{
	if (timer == DUALTIMER_TIMER1) {
		return DUALTIMER0->TIMER1RIS.reg;
	} else {
		return DUALTIMER0->TIMER2RIS.reg;
	}
}

/**
 * \brief Get Dualtimer module timer1/timer2 interrupt status
 *
 * \param[in]     timer        Timer1/Timer2
 *
 * \retval The interrupt status of timer1/timer2
 */
uint8_t dualtimer_get_interrupt_status(enum dualtimer_timer timer)
{
	if (timer == DUALTIMER_TIMER1) {
		return DUALTIMER0->TIMER1MIS.reg;
	} else {
		return DUALTIMER0->TIMER2MIS.reg;
	}
}

/**
 * \brief Clear Dualtimer module timer1/timer2 interrupt status
 *
 * Clear the Dualtimer module timer1/timer2 interrupt status
 *
 * \param[in]     timer        Timer1/Timer2
 */
void dualtimer_clear_interrupt_status(enum dualtimer_timer timer)
{
	if (timer == DUALTIMER_TIMER1) {
		DUALTIMER0->TIMER1INTCLR.reg = 1;
	} else {
		DUALTIMER0->TIMER2INTCLR.reg = 1;
	}
}

/**
 * \brief Set Dualtimer module timer1/timer2 enable
 *
 * Enable the Dualtimer module timer1/timer2
 *
 * \param[in]     timer        Timer1/Timer2
 */
void dualtimer_enable(enum dualtimer_timer timer)
{
	if (timer == DUALTIMER_TIMER1) {
		DUALTIMER0->TIMER1CONTROL.reg |= DUALTIMER_TIMER1CONTROL_TIMER_ENABLE;
	} else {
		DUALTIMER0->TIMER2CONTROL.reg |= DUALTIMER_TIMER2CONTROL_TIMER_ENABLE;
	}
}

/**
 * \brief Set Dualtimer module timer1/timer2 disable
 *
 * Disable the Dualtimer module timer1/timer2
 *
 * \param[in]     timer        Timer1/Timer2
 */
void dualtimer_disable(enum dualtimer_timer timer)
{
	if (timer == DUALTIMER_TIMER1) {
		DUALTIMER0->TIMER1CONTROL.reg &= ~DUALTIMER_TIMER1CONTROL_TIMER_ENABLE;
	} else {
		DUALTIMER0->TIMER2CONTROL.reg &= ~DUALTIMER_TIMER2CONTROL_TIMER_ENABLE;
	}
}

/**
 * \brief Dualtimer ISR handler.
 *
 * Dualtimer ISR handler.
 *
 */
static void dualtimer_isr_handler(void)
{
	if (dualtimer_get_interrupt_status(DUALTIMER_TIMER1)) {
		dualtimer_clear_interrupt_status(DUALTIMER_TIMER1);
		if (dualtimer_callback_timer1)
			dualtimer_callback_timer1();
	}
	if (dualtimer_get_interrupt_status(DUALTIMER_TIMER2)) {
		dualtimer_clear_interrupt_status(DUALTIMER_TIMER2);
		if (dualtimer_callback_timer2)
			dualtimer_callback_timer2();
	}
}

/**
 * \brief Initializes Dualtimer module instance.
 *
 * Initializes the Dualtimer module, based on the given
 * configuration values.
 *
 * \param[in]     config       Pointer to the Dualtimer configuration options struct
 *
 * \return Status of the initialization procedure.
 */
void dualtimer_init(const struct dualtimer_config *config)
{
	uint8_t regval = 0;

	/* Global reset */
	system_peripheral_reset(PERIPHERAL_DUALT_TIMER);

	/* Common config */
	if (config->timer1.timer_enable || config->timer2.timer_enable) {
		LPMCU_MISC_REGS0->LPMCU_CLOCK_ENABLES_0.reg |=
		LPMCU_MISC_REGS_LPMCU_CLOCK_ENABLES_0_DUALTIMER0_CLK_EN;
		LPMCU_MISC_REGS0->LPMCU_CTRL.bit.DUALTIMER0_CLK_SEL = config->clock_source;
	}
	
	/* Timer1 config */
	if (config->timer1.timer_enable) {
		if (config->timer1.counter_mode == DUALTIMER_ONE_SHOT_MODE) {
			regval = DUALTIMER_TIMER1CONTROL_ONE_SHOT_COUNT_1;
		} else if (config->timer1.counter_mode == DUALTIMER_FREE_RUNNING_MODE) {
			regval = DUALTIMER_TIMER1CONTROL_TIMER_MODE_0;
		} else if (config->timer1.counter_mode == DUALTIMER_PERIODIC_MODE) {
			regval = DUALTIMER_TIMER1CONTROL_TIMER_MODE_1;
		}
		regval |= (DUALTIMER_TIMER1CONTROL_TIMER_SIZE &
				((config->timer1.counter_size) << DUALTIMER_TIMER1CONTROL_TIMER_SIZE_Pos)) |
				DUALTIMER_TIMER1CONTROL_TIMERPRE(config->timer1.clock_prescaler);
		if (config->timer1.interrup_enable) {
			regval |= DUALTIMER_TIMER1CONTROL_INTERRUPT_ENABLE;
		}
		DUALTIMER0->TIMER1LOAD.reg = config->timer1.load_value;
		DUALTIMER0->TIMER1CONTROL.reg = regval;
		LPMCU_MISC_REGS0->DUALTIMER0_CTRL.reg |= LPMCU_MISC_REGS_DUALTIMER0_CTRL_CNTR_1_ENABLE;
		dualtimer_enable(DUALTIMER_TIMER1);
	}

	/* Timer2 config */
	if (config->timer2.timer_enable) {
		if (config->timer2.counter_mode == DUALTIMER_ONE_SHOT_MODE) {
			regval = DUALTIMER_TIMER2CONTROL_ONE_SHOT_COUNT_1;
		} else if (config->timer2.counter_mode == DUALTIMER_FREE_RUNNING_MODE) {
			regval = DUALTIMER_TIMER2CONTROL_TIMER_MODE_0;
		} else if (config->timer2.counter_mode == DUALTIMER_PERIODIC_MODE) {
			regval = DUALTIMER_TIMER2CONTROL_TIMER_MODE_1;
		}
		regval |= (DUALTIMER_TIMER2CONTROL_TIMER_SIZE &
				((config->timer2.counter_size) << DUALTIMER_TIMER2CONTROL_TIMER_SIZE_Pos)) |
				DUALTIMER_TIMER2CONTROL_TIMERPRE(config->timer2.clock_prescaler);
		if (config->timer2.interrup_enable) {
			regval |= DUALTIMER_TIMER2CONTROL_INTERRUPT_ENABLE;
		}
		DUALTIMER0->TIMER2LOAD.reg = config->timer2.load_value;
		DUALTIMER0->TIMER2CONTROL.reg = regval;
		LPMCU_MISC_REGS0->DUALTIMER0_CTRL.reg |= LPMCU_MISC_REGS_DUALTIMER0_CTRL_CNTR_2_ENABLE;
		dualtimer_enable(DUALTIMER_TIMER2);
	}

	system_register_isr(RAM_ISR_TABLE_DUALTIMER_INDEX, (uint32_t)dualtimer_isr_handler);
}

/**
 * \brief Registers a callback.
 *
 * Registers and enable a callback function which is implemented by the user.
 *
 * \param[in]     callback_func Pointer to callback function
 */
void dualtimer_register_callback(enum dualtimer_timer timer, dualtimer_callback_t fun)
{
	if (timer == DUALTIMER_TIMER1) {
		dualtimer_callback_timer1 = fun;
	} else {
		dualtimer_callback_timer2 = fun;
	}
}

/**
 * \brief Unregisters a callback.
 *
 * Unregisters and disable a callback function implemented by the user.
 *
 */
void dualtimer_unregister_callback(enum dualtimer_timer timer)
{
	if (timer == DUALTIMER_TIMER1) {
		dualtimer_callback_timer1 = NULL;
	} else {
		dualtimer_callback_timer2 = NULL;
	}
}