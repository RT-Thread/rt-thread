/**
 *
 * \file
 *
 * \brief SAM Frequency Meter driver.
 *
 * This file defines a useful set of functions for the FREQM on SAM devices.
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

#ifndef FREQM_CALLBACK_H_INCLUDED
#define FREQM_CALLBACK_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>
#include <system_interrupt.h>
/**
 * \addtogroup asfdoc_sam0_freqm_group
 *
 * @{
 */

/** FREQM callback type. */
enum freqm_callback_type {
	/** Measurement done callback.*/
	FREQM_CALLBACK_MEASURE_DONE = 0,
};
 
/** \name Callback Configuration and Initialization
 * @{
 */
 
enum status_code freqm_register_callback(
		struct freqm_module *const module,
		freqm_callback_t callback_func,
		enum freqm_callback callback_type);

enum status_code freqm_unregister_callback(
		struct freqm_module *module,
		enum freqm_callback callback_type);

/** @} */


/** \name Callback Enabling and Disabling
 * @{
 */

/**
 * \brief Enable an FREQM callback.
 *
 * \param[in,out] module  Pointer to the software instance struct
 * \param[in] type Callback source type
 *
 * \return Status of the callback enable operation.
 * \retval STATUS_OK The callback was enabled successfully
 * \retval STATUS_ERR_INVALID_ARG If an invalid callback type was supplied
 */
static inline enum status_code freqm_enable_callback(struct freqm_module *const module,
		const enum freqm_callback_type type)
{
	/* Sanity check arguments */
	Assert(module);

	if (type == FREQM_CALLBACK_MEASURE_DONE){
		module->hw->INTENSET.reg = FREQM_INTENSET_DONE;
	} else {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	system_interrupt_enable(SYSTEM_INTERRUPT_MODULE_FREQM);
	return STATUS_OK;
}

/**
 * \brief Disable an FREQM callback.
 *
 * \param[in,out] module  Pointer to the software instance struct
 * \param[in]  type Callback source type
 *
 * \return Status of the callback enable operation.
 * \retval STATUS_OK The callback was enabled successfully
 * \retval STATUS_ERR_INVALID_ARG If an invalid callback type was supplied
 */
static inline enum status_code freqm_disable_callback(struct freqm_module *const module,
		 const enum freqm_callback_type type)
{
	/* Sanity check arguments */
	Assert(module);

	if (type == FREQM_CALLBACK_MEASURE_DONE){
		module->hw->INTENCLR.reg = FREQM_INTENCLR_DONE;
	} else {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	system_interrupt_disable(SYSTEM_INTERRUPT_MODULE_FREQM);
	return STATUS_OK;
}

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* FREQM_CALLBACK_H_INCLUDED */
