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

#ifndef SLCD_CALLBACK_H_INCLUDED
#define SLCD_CALLBACK_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>
#include <system_interrupt.h>
/**
 * \addtogroup asfdoc_sam0_drivers_slcd_group
 *
 * @{
 */

/**
 * \brief SLCD callback type
 *
 * Enum SLCD callback type. 
 */
enum slcd_callback_type {
	/** Frame Counter 0 Overflow callback */
	SLCD_CALLBACK_FC0_OVERFLOW = 0,
	/** Frame Counter 1 Overflow callback */
	SLCD_CALLBACK_FC1_OVERFLOW,
	/** Frame Counter 2 Overflow callback */
	SLCD_CALLBACK_FC2_OVERFLOW,
	/** VLCD Ready Toggle callback */
	SLCD_CALLBACK_VLCD_READY,
	/** VLCD Status Toggle callback */
	SLCD_CALLBACK_VLCD_TOGGLE,
	/** Pump Run Status Toggle callback */
	SLCD_CALLBACK_PUMP_TOGGLE,
};

/** SLCD interrupt callback function type. */
typedef void (*slcd_callback_t)(enum slcd_callback_type type);

/** \internal Max number of callback type. */
#define SLCD_CALLBACK_TYPE_NUM 6

/** \name Callback Function
 * @{
 */

enum status_code slcd_register_callback(
	const slcd_callback_t callback,
	const enum slcd_callback_type type);

enum status_code slcd_unregister_callback(
	const slcd_callback_t callback,
	const enum slcd_callback_type type);

/**
 * \brief Enable an SLCD callback
 *
 * \param[in] type Callback source type
 *
 * \retval STATUS_OK  The function exited successfully
 * \retval STATUS_ERR_INVALID_ARG  If an invalid callback type was supplied
 */
static inline void slcd_enable_callback(const enum slcd_callback_type type)
{
	if (type < SLCD_CALLBACK_TYPE_NUM){
		SLCD->INTENSET.reg = 1 << type;
	}
}

/**
 * \brief Disable an SLCD callback
 *
 * \param[in]  type Callback source type
 *
 * \retval STATUS_OK  The function exited successfully
 * \retval STATUS_ERR_INVALID_ARG  If an invalid callback type was supplied
 */
static inline void slcd_disable_callback(const enum slcd_callback_type type)
{
	if (type < SLCD_CALLBACK_TYPE_NUM){
		SLCD->INTENCLR.reg = 1 << type;
	}
}

/** @} */

/** @} */
#ifdef __cplusplus
}
#endif

#endif  /* SLCD_CALLBACK_H_INCLUDED */
