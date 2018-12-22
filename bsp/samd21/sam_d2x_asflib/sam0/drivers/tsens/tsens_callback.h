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
/**
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef TSENS_CALLBACK_H_INCLUDED
#define TSENS_CALLBACK_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>
#include <system_interrupt.h>
#include "tsens.h"

/**
 * \addtogroup asfdoc_sam0_tsens_group
 *
 * @{
 */

/**
 * \brief TSENS Callback Types.
 *
 * Callback types for TSENS callback driver.
 *
 */
enum tsens_callback {
	/** Callback for result ready */
	TSENS_CALLBACK_RESULT_READY,
	/** Callback when result overwritten before read */
	TSENS_CALLBACK_OVERRUN,
	/** Callback when window is hit */
	TSENS_CALLBACK_WINDOW,
	/** Callback when the result overflows */
	TSENS_CALLBACK_OVF,
#  if !defined(__DOXYGEN__)
	/** Number of available callbacks */
	TSENS_CALLBACK_NUM,
#  endif
};

/** Type of the callback functions. */
typedef void (*tsens_callback_t)(enum tsens_callback);

/**
 * \brief TSENS software device instance structure.
 *
 * TSENS software instance structure, used to retain software state information
 * of an associated hardware module instance.
 *
 * \note The fields of this structure should not be altered by the user
 *       application; they are reserved for module-internal use only.
 */
struct tsens_module {
#if !defined(__DOXYGEN__)
	/** Array to store callback functions. */
	tsens_callback_t callback[TSENS_CALLBACK_NUM];
	/** Pointer to used for TSENS results. */
	volatile int32_t *value;
#endif
};

/**
 * \name Callback Management
 * @{
 */
enum status_code tsens_register_callback(
			struct tsens_module *const module,
			tsens_callback_t callback_func,
			enum tsens_callback callback_type);

enum status_code tsens_unregister_callback(
			struct tsens_module *const module,
			enum tsens_callback callback_type);

/**
 * \brief Enables callback.
 *
 * Enables the callback function registered by \ref
 * tsens_register_callback. The callback function will be called from the
 * interrupt handler when the conditions for the callback type are met.
 *
 * \param[in]     callback_type Callback type given by an enum
 *
 */
static inline void tsens_enable_callback(enum tsens_callback callback_type)
{
	uint32_t inenset_temp = 0;

	switch (callback_type) {
		case TSENS_CALLBACK_RESULT_READY:
			inenset_temp |= TSENS_INTFLAG_RESRDY;
			break;
		case TSENS_CALLBACK_OVERRUN:
			inenset_temp |= TSENS_INTENSET_OVERRUN;
			break;
		case TSENS_CALLBACK_WINDOW:
			inenset_temp |= TSENS_INTENSET_WINMON;
			break;
		case TSENS_CALLBACK_OVF:
			inenset_temp |= TSENS_INTENSET_OVF;
			break;

		default:
			break;
	}

	/* Enable the interrupt for the callback */
	TSENS->INTENSET.reg = inenset_temp;
}

/**
 * \brief Disables callback.
 *
 * Disables the callback function registered by the \ref
 * tsens_register_callback.
 *
 * \param[in]     callback_type Callback type given by an enum
 *
 */
static inline void tsens_disable_callback(enum tsens_callback callback_type)
{
	uint32_t inenclr_temp = 0;

	switch (callback_type) {
		case TSENS_CALLBACK_RESULT_READY:
			inenclr_temp |= TSENS_INTENCLR_OVERRUN;
			break;
		case TSENS_CALLBACK_OVERRUN:
			inenclr_temp |= TSENS_INTENSET_OVERRUN;
			break;
		case TSENS_CALLBACK_WINDOW:
			inenclr_temp |= TSENS_INTENSET_WINMON;
			break;
		case TSENS_CALLBACK_OVF:
			inenclr_temp |= TSENS_INTENSET_OVF;
			break;

		default:
			break;
	}

	/* Disable the interrupt for the callback */
	TSENS->INTENCLR.reg = inenclr_temp;
}

void tsens_read_job(struct tsens_module *const module_inst, int32_t *result);
/** @} */

/** @} */
#ifdef __cplusplus
}
#endif

#endif /* TSENS_CALLBACK_H_INCLUDED */
