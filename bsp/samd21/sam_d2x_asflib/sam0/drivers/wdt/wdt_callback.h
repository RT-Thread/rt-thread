/**
 * \file
 *
 * \brief SAM Watchdog Driver
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
#ifndef WDT_CALLBACK_H_INCLUDED
#define WDT_CALLBACK_H_INCLUDED

#include <compiler.h>
#include "wdt.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup asfdoc_sam0_wdt_group
 *
 * @{
 */

/** \name Callback Configuration and Initialization
 * @{
 */

/** Type definition for a WDT module callback function. */
typedef void (*wdt_callback_t)(void);

/** Enum for the possible callback types for the WDT module. */
enum wdt_callback
{
	/** Callback type for when an early warning callback from the WDT module
	 *  is issued
	 */
	WDT_CALLBACK_EARLY_WARNING,
};

enum status_code wdt_register_callback(
		const wdt_callback_t callback,
		const enum wdt_callback type);

enum status_code wdt_unregister_callback(
		const enum wdt_callback type);

/** @} */

/** \name Callback Enabling and Disabling
 * @{
 */

enum status_code wdt_enable_callback(
		const enum wdt_callback type);

enum status_code wdt_disable_callback(
		const enum wdt_callback type);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif
