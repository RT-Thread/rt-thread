/**
 *
 * \file
 *
 * \brief SAM Segment Liquid Crystal Display(SLCD) Controller.
 *
 * Copyright (c) 2015 Atmel Corporation. All rights reserved.
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

#include "slcd.h"
#include "slcd_callback.h"

/**
* \internal
* \brief slcd callback function pointer
*/
slcd_callback_t slcd_callback_pointer[SLCD_CALLBACK_TYPE_NUM];


/**
 * \brief Registers a callback
 *
 * Registers a callback function which is implemented by the user.
 *
 * \note The callback must be enabled by \ref slcd_enable_callback,
 * in order for the interrupt handler to call it when the conditions for the
 * callback type is met.
 *
 * \param[in]     callback_func Pointer to callback function
 * \param[in]     callback_type Callback type given by an enum
 *
 * \retval STATUS_OK  The function exited successfully
 * \retval STATUS_ERR_INVALID_ARG  If an invalid callback type was supplied
 */

enum status_code slcd_register_callback(
	const slcd_callback_t callback,
	const enum slcd_callback_type type)
{
	if (type >= SLCD_CALLBACK_TYPE_NUM){
		return STATUS_ERR_INVALID_ARG;
	}

	slcd_callback_pointer[type] = callback;
	return STATUS_OK;
}

/**
 * \brief Unregisters a callback
 *
 * Unregisters a callback function implemented by the user.
 *
 * \param[in]  callback_type Callback type given by an enum
 *
 * \retval STATUS_OK  The function exited successfully
 * \retval STATUS_ERR_INVALID_ARG  If an invalid callback type was supplied
 */

enum status_code slcd_unregister_callback(
	const slcd_callback_t callback,
	const enum slcd_callback_type type)
{
	if (type >= SLCD_CALLBACK_TYPE_NUM){
		return STATUS_ERR_INVALID_ARG;
	}

	slcd_callback_pointer[type] = NULL;
	return STATUS_OK;
}

/**
* \internal The SLCD interrupt handler.
*/
void SLCD_Handler(void)
{
	uint32_t status = SLCD->INTFLAG.reg;
	for (uint8_t i = 0; i < SLCD_CALLBACK_TYPE_NUM; i++) {
		if (status & (1 << i)) {
			/* Clear the INTFLAG anyway */
			SLCD->INTFLAG.reg = 1 << i;

			if (slcd_callback_pointer[i]) {
				slcd_callback_pointer[i]((enum slcd_callback_type)i);
			}
		}
	}
}
