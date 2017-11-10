/**
 * \file
 *
 * \brief SAM Temperature Sensor Driver
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

#include "tsens_callback.h"

struct tsens_module *_tsens_instances;

/** Interrupt handler for the TSENS module. */
void TSENS_Handler(void)
{
	struct tsens_module *module = _tsens_instances;
	Assert(module);

	/* get interrupt flags and mask out enabled callbacks */
	uint32_t flags = TSENS->INTFLAG.reg;

	/* store TSENS result in job buffer */
	uint32_t temp = TSENS->VALUE.reg;
	if(temp & 0x00800000) {
		temp |= ~TSENS_VALUE_MASK;
	}
#if (ERRATA_14476)
	*(module->value) = temp * (-1);
#endif

	for(uint8_t i = 0; i < TSENS_CALLBACK_NUM; i++)
	{
		if (flags & ((uint32_t)0x01 << i)) {
			/* Clear the INTFLAG anyway */
			TSENS->INTFLAG.reg = (uint32_t)0x01 << i;

			if(module->callback[i] != NULL) {
				module->callback[i]((enum tsens_callback)i);
			}
		}
	}
}

/**
 * \brief Registers a callback.
 *
 * Registers a callback function which is implemented by the user.
 *
 * \note The callback must be enabled by for the interrupt handler to call it
 * when the condition for the callback is met.
 *
 * \param[in] module         Pointer to TSENS software instance struct
 * \param[in] callback_func  Pointer to callback function
 * \param[in] callback_type  Callback type given by an enum
 *
 */
enum status_code tsens_register_callback(
		struct tsens_module *const module,
		tsens_callback_t callback_func,
		enum tsens_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(callback_func);

	if(callback_type > TSENS_CALLBACK_NUM) {
		return STATUS_ERR_INVALID_ARG;
	}

	/* Register callback function */
	module->callback[callback_type] = callback_func;
	_tsens_instances = module;

	return STATUS_OK;
}

/**
 * \brief Unregisters a callback.
 *
 * Unregisters a callback function which is implemented by the user.
 *
 * \param[in] module         Pointer to TSENS software instance struct
 * \param[in] callback_type  Callback type given by an enum
 *
 */
enum status_code tsens_unregister_callback(
		struct tsens_module *const module,
		enum tsens_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	if(callback_type > TSENS_CALLBACK_NUM) {
		return STATUS_ERR_INVALID_ARG;
	}

	/* Register callback function */
	module->callback[callback_type] = NULL;

	return STATUS_OK;
}

/**
 * \brief Read result from TSENS.
 *
 * \param[in]  module_inst  Pointer to the TSENS software instance struct
 * \param[out] result       Pointer to store the TSENS result
 *
 */
void tsens_read_job(
		struct tsens_module *const module_inst,
		int32_t *result)
{
	Assert(module_inst);
	Assert(result);

	module_inst->value = result;

	if(!(TSENS->CTRLC.reg & TSENS_CTRLC_FREERUN)) {
		tsens_start_conversion();
	}
}
