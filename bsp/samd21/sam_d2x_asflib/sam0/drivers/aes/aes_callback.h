/**
 *
 * \file
 *
 * \brief SAM Advanced Encryption Standard driver.
 *
 * This file defines a useful set of functions for the AES on SAM devices.
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
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

#ifndef AES_CALLBACK_H_INCLUDED
#define AES_CALLBACK_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>
#include <system_interrupt.h>
/**
 * \addtogroup asfdoc_sam0_drivers_aes_group
 *
 * @{
 */

/** AES interrupt callback function type. */
typedef void (*aes_callback_t)(void); 

/** AES callback type. */
enum aes_callback_type {
	/** Encryption complete callback */
	AES_CALLBACK_ENCRYPTION_COMPLETE = 0,
	/** GF Multiplication Complete callback */
	AES_CALLBACK_GF_MULTI_COMPLETE = 1,
};
 
/** \name Callback Configuration and Initialization
 * @{
 */
 
enum status_code aes_register_callback(
	const aes_callback_t callback,
	const enum aes_callback_type type);

enum status_code aes_unregister_callback(
	const aes_callback_t callback,
	const enum aes_callback_type type);

/** @} */


/** \name Callback Enabling and Disabling
 * @{
 */

/**
 * \brief Enable an AES callback.
 *
 * \param[in,out] module  Pointer to the software instance struct
 * \param[in] type Callback source type
 *
 * \return Status of the callback enable operation.
 * \retval STATUS_OK The callback was enabled successfully
 * \retval STATUS_ERR_INVALID_ARG If an invalid callback type was supplied
 */
static inline enum status_code aes_enable_callback(struct aes_module *const module,
		const enum aes_callback_type type)
{
	system_interrupt_enable(SYSTEM_INTERRUPT_MODULE_AES);
	if (type == AES_CALLBACK_ENCRYPTION_COMPLETE){
		module->hw->INTENSET.reg = AES_INTENSET_ENCCMP;
	} else if (type == AES_CALLBACK_GF_MULTI_COMPLETE){
		module->hw->INTENSET.reg = AES_INTENSET_GFMCMP;
	} else {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

/**
 * \brief Disable an AES callback.
 *
 * \param[in,out] module  Pointer to the software instance struct
 * \param[in]  type Callback source type
 *
 * \return Status of the callback enable operation.
 * \retval STATUS_OK The callback was enabled successfully
 * \retval STATUS_ERR_INVALID_ARG If an invalid callback type was supplied
 */
static inline enum status_code aes_disable_callback(struct aes_module *const module,
		 const enum aes_callback_type type)
{
	system_interrupt_disable(SYSTEM_INTERRUPT_MODULE_AES);
	if (type == AES_CALLBACK_ENCRYPTION_COMPLETE){
		module->hw->INTENCLR.reg = AES_INTENCLR_ENCCMP;
	} else if (type == AES_CALLBACK_GF_MULTI_COMPLETE){
		module->hw->INTENCLR.reg = AES_INTENCLR_GFMCMP;
	} else {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* AES_CALLBACK_H_INCLUDED */
