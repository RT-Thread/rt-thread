/**
 *
 * \file
 *
 * \brief SAM Frequency Meter driver.
 *
 * This file defines a useful set of functions for the FREQM on SAM devices.
 *
 * Copyright (c) 2015-2016 Atmel Corporation. All rights reserved.
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

#include "freqm.h"
#include "freqm_callback.h"

/** \internal Max number of callback type. */
#define FREQM_CALLBACK_TYPE_NUM 1

struct freqm_module *_freqm_instance;


/**
 * \brief Registers a callback
 *
 * Registers a callback function which is implemented by the user.
 *
 * \note The callback must be enabled by \ref freqm_enable_callback,
 * in order for the interrupt handler to call it when the conditions for the
 * callback type is met.
 *
 * \param[in]     module        Pointer to FREQM software instance struct
 * \param[in]     callback_func Pointer to callback function
 * \param[in]     callback_type Callback type given by an enum
 *
 * \retval STATUS_OK  The function exited successfully
 */
enum status_code freqm_register_callback(
		struct freqm_module *const module,
		freqm_callback_t callback_func,
		enum freqm_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);
	Assert(callback_func);

	if (callback_type >= FREQM_CALLBACK_TYPE_NUM) {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}
	/* Register callback function */
	module->callback[callback_type] = callback_func;

	return STATUS_OK;
}

/**
 * \brief Unregisters a callback
 *
 * Unregisters a callback function implemented by the user. The callback should be
 * disabled before it is unregistered.
 *
 * \param[in]     module        Pointer to FREQM software instance struct
 * \param[in]     callback_type Callback type given by an enum
 *
 * \retval STATUS_OK  The function exited successfully
 */
enum status_code freqm_unregister_callback(
		struct freqm_module *module,
		enum freqm_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	if (callback_type >= FREQM_CALLBACK_TYPE_NUM) {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}
	/* Unregister callback function */
	module->callback[callback_type] = NULL;

	return STATUS_OK;
}



/**
* \internal The FREQM interrupt handler.
*/
void FREQM_Handler(void)
{
	/* Get device instance from the look-up table */
	struct freqm_module *module = _freqm_instance;

	/* Read and mask interrupt flag register */
	uint32_t status = FREQM->INTFLAG.reg;

	/* Check if data ready needs to be serviced */
	if (status & FREQM_INTFLAG_DONE) {
		if (module->callback[FREQM_CALLBACK_MEASURE_DONE]) {
			FREQM->INTFLAG.reg = FREQM_INTFLAG_DONE;
			module->callback[FREQM_CALLBACK_MEASURE_DONE]();
		}
	}

}
