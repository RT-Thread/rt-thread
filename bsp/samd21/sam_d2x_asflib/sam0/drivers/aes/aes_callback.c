/**
 *
 * \file
 *
 * \brief SAM Advanced Encryption Standard driver.
 *
 * This file defines a useful set of functions for the AES on SAM devices.
 *
 * Copyright (c) 2014-2016 Atmel Corporation. All rights reserved.
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

#include "aes.h"
#include "aes_callback.h"

/** \internal Max number of callback type. */
#define AES_CALLBACK_TYPE_NUM 2

/**
* \internal
* \brief AES callback function pointer
*/
aes_callback_t aes_callback_pointer[AES_CALLBACK_TYPE_NUM]={NULL,NULL};


enum status_code aes_register_callback(
	const aes_callback_t callback,
	const enum aes_callback_type type)
{
	if (type >= AES_CALLBACK_TYPE_NUM){
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	aes_callback_pointer[type] = callback;
	return STATUS_OK;
}

enum status_code aes_unregister_callback(
	const aes_callback_t callback,
	const enum aes_callback_type type)
{
	if (type >= AES_CALLBACK_TYPE_NUM){
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	aes_callback_pointer[type] = NULL;
	return STATUS_OK;
}



/**
* \internal The AES interrupt handler.
*/
void AES_Handler(void)
{
	uint32_t status = AES->INTFLAG.reg;

	if (status & AES_INTFLAG_ENCCMP) {
		if (aes_callback_pointer[AES_CALLBACK_ENCRYPTION_COMPLETE]) {
			AES->INTFLAG.reg = AES_INTFLAG_ENCCMP;
			aes_callback_pointer[AES_CALLBACK_ENCRYPTION_COMPLETE]();
		}
	}

	if (status & AES_INTFLAG_GFMCMP) {
		if (aes_callback_pointer[AES_CALLBACK_ENCRYPTION_COMPLETE]) {
			AES->INTFLAG.reg = AES_INTFLAG_GFMCMP;
			aes_callback_pointer[AES_CALLBACK_ENCRYPTION_COMPLETE]();
		}
	}
}
