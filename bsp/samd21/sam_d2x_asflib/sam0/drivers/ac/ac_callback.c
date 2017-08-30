/**
 * \file
 *
 * \brief SAM AC - Analog Comparator Callback Driver
 *
 * Copyright (C) 2013-2015 Atmel Corporation. All rights reserved.
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

#include "ac_callback.h"

struct ac_module *_ac_instance[AC_INST_NUM];

void _ac_interrupt_handler(const uint32_t instance_index);

/**
 * \brief Registers a callback.
 *
 * Registers a callback function which is implemented by the user.
 *
 * \note The callback must be enabled by \ref ac_enable_callback,
 * in order for the interrupt handler to call it when the conditions for the
 * callback type is met.
 *
 * \param[in]     module      Pointer to software instance struct
 * \param[in]     callback_func Pointer to callback function
 * \param[in]     callback_type Callback type given by an enum
 *
 * \retval STATUS_OK  The function exited successfully
 */
enum status_code ac_register_callback(
		struct ac_module *const module,
		ac_callback_t callback_func,
		const enum ac_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(callback_func);

	/* Register callback function */
	module->callback[callback_type] = callback_func;

	/* Set software flag for callback */
	module->register_callback_mask |= (1 << callback_type);

	return STATUS_OK;
}

/**
 * \brief Unregisters a callback.
 *
 * Unregisters a callback function implemented by the user.
 *
 * \param[in]     module Pointer to AC software instance struct
 * \param[in]     callback_type Callback type given by an enum
 *
 * \retval STATUS_OK  The function exited successfully
 */
enum status_code ac_unregister_callback(
		struct ac_module *const module,
		const enum ac_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);
	/* Unregister callback function */
	module->callback[callback_type] = NULL;

	/* Clear software flag for callback */
	module->register_callback_mask &= ~(1 << callback_type);

	return STATUS_OK;
}

/**
 * \internal ISR handler for AC
 */
#if (AC_INST_NUM == 1)
void AC_Handler(void)
{
	_ac_interrupt_handler(0);
}
#elif (AC_INST_NUM == 2)
void AC_Handler(void)
{
	_ac_interrupt_handler(0);
}

void AC1_Handler(void)
{
	_ac_interrupt_handler(1);
}
#else
#  error This driver is not support more than three AC instances.
#endif

/**
 * \brief Interrupt Handler for AC module.
 *
 * Handles interrupts as they occur, it will run the callback functions
 * that are registered and enabled.
 *
 * \param [in] instance_index  Default value 0
 */
void _ac_interrupt_handler(const uint32_t instance_index)
{
	/* Temporary variable */
	uint8_t interrupt_and_callback_status_mask;

	/* Get device instance from the look-up table */

	struct ac_module *module = _ac_instance[instance_index];

	/* Read and mask interrupt flag register */
	interrupt_and_callback_status_mask =
			_ac_instance[instance_index]->hw->INTFLAG.reg &
			(module->register_callback_mask & module->enable_callback_mask);

	/* Check if comparator channel 0 needs to be serviced */
	if (interrupt_and_callback_status_mask & AC_INTFLAG_COMP0) {
		/* Invoke registered and enabled callback function */
		(module->callback[AC_CALLBACK_COMPARATOR_0])(module);
		/* Clear interrupt flag */
		module->hw->INTFLAG.reg = AC_INTFLAG_COMP0;
	}

	/* Check if comparator channel 1 needs to be serviced */
	if (interrupt_and_callback_status_mask & AC_INTFLAG_COMP1) {
		/* Invoke registered and enabled callback function */
		(module->callback[AC_CALLBACK_COMPARATOR_1])(module);
		/* Clear interrupt flag */
		module->hw->INTFLAG.reg = AC_INTFLAG_COMP1;
	}

	/* Check if window 0 needs to be serviced */
	if (interrupt_and_callback_status_mask & AC_INTFLAG_WIN0) {
		/* Invoke registered and enabled callback function */
		(module->callback[AC_CALLBACK_WINDOW_0])(module);
		/* Clear interrupt flag */
		module->hw->INTFLAG.reg = AC_INTFLAG_WIN0;
	}

#if (AC_NUM_CMP > 2)
		/* Check if comparator channel 2 needs to be serviced */
	if (interrupt_and_callback_status_mask & AC_INTFLAG_COMP2) {
		/* Invoke registered and enabled callback function */
		(module->callback[AC_CALLBACK_COMPARATOR_2])(module);
		/* Clear interrupt flag */
		module->hw->INTFLAG.reg = AC_INTFLAG_COMP2;
	}

	/* Check if comparator channel 3 needs to be serviced */
	if (interrupt_and_callback_status_mask & AC_INTFLAG_COMP3) {
		/* Invoke registered and enabled callback function */
		(module->callback[AC_CALLBACK_COMPARATOR_3])(module);
		/* Clear interrupt flag */
		module->hw->INTFLAG.reg = AC_INTFLAG_COMP3;
	}

#  if !(SAMC20)
		/* Check if window 1 needs to be serviced */
	if (interrupt_and_callback_status_mask & AC_INTFLAG_WIN1) {
		/* Invoke registered and enabled callback function */
		(module->callback[AC_CALLBACK_WINDOW_1])(module);
		/* Clear interrupt flag */
		module->hw->INTFLAG.reg = AC_INTFLAG_WIN1;
	}
#  endif
#endif /* (AC_NUM_CMP > 2) */
}
