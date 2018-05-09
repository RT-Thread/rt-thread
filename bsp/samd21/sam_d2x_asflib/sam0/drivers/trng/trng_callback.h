/**
 * \file
 *
 * \brief SAM True Random Number Generator (TRNG) Driver
 *
 * Copyright (C) 2014-2015 Atmel Corporation. All rights reserved.
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

#ifndef TRNG_CALLBACK_H_INCLUDED
#define TRNG_CALLBACK_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup asfdoc_sam0_trng_group
 *
 * @{
 */

#include <trng.h>

/**
 * Enum for the possible types of TRNG asynchronous jobs that may be issued to
 * the driver.
 */
enum trng_job_type {
	/** Asynchronous TRNG read into a user provided buffer */
	TRNG_JOB_READ_BUFFER,
};

/**
 * \name Callback Management
 * @{
 */
enum status_code trng_register_callback(
		struct trng_module *const module,
		trng_callback_t callback_func,
		enum trng_callback callback_type);

enum status_code trng_unregister_callback(
		struct trng_module *module,
		enum trng_callback callback_type);

/**
 * \brief Enables callback
 *
 * Enables the callback function registered by \ref
 * trng_register_callback. The callback function will be called from the
 * interrupt handler when the conditions for the callback type are met.
 *
 * \param[in]     module        Pointer to TRNG software instance struct
 * \param[in]     callback_type Callback type given by an enum
 */
static inline void trng_enable_callback(
		struct trng_module *const module,
		enum trng_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	/* Enable callback */
	module->enable_callback_mask |= (1 << callback_type);
}

/**
 * \brief Disables callback
 *
 * Disables the callback function registered by the \ref
 * trng_register_callback.
 *
 * \param[in]     module        Pointer to TRNG software instance struct
 * \param[in]     callback_type Callback type given by an enum
 */
static inline void trng_disable_callback(
		struct trng_module *const module,
		enum trng_callback callback_type)
{
	/* Sanity check arguments */
	Assert(module);

	/* Disable callback */
	module->enable_callback_mask &= ~(1UL << callback_type);

	/* Disable data ready interrupt */
	if (callback_type == TRNG_CALLBACK_READ_BUFFER) {
		module->hw->INTENCLR.reg = TRNG_INTENCLR_DATARDY;
	}
}

/** @} */

/**
 * \name Job Management
 * @{
 */
enum status_code trng_read_buffer_job(
		struct trng_module *const module_inst,
		uint32_t *buffer,
		uint32_t number);

enum status_code trng_get_job_status(
		struct trng_module *module_inst,
		enum trng_job_type type);

void trng_abort_job(
		struct trng_module *module_inst,
		enum trng_job_type type);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* TRNG_CALLBACK_H_INCLUDED */

