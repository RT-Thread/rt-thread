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
#include "wdt.h"
#include <system.h>
#include <system_interrupt.h>

wdt_callback_t wdt_early_warning_callback;

/**
 * \brief Registers an asynchronous callback function with the driver.
 *
 * Registers an asynchronous callback with the WDT driver, fired when a
 * given criteria (such as an Early Warning) is met. Callbacks are fired once
 * for each event.
 *
 * \param[in] callback  Pointer to the callback function to register
 * \param[in] type      Type of callback function to register
 *
 * \return Status of the registration operation.
 * \retval STATUS_OK               The callback was registered successfully
 * \retval STATUS_ERR_INVALID_ARG  If an invalid callback type was supplied
 */
enum status_code wdt_register_callback(
		const wdt_callback_t callback,
		const enum wdt_callback type)
{
	/* Sanity check arguments */
	Assert(callback);

	switch (type)
	{
	case WDT_CALLBACK_EARLY_WARNING:
		wdt_early_warning_callback = callback;
		return STATUS_OK;
	default:
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}
}

/**
 * \brief Unregisters an asynchronous callback function with the driver.
 *
 * Unregisters an asynchronous callback with the WDT driver, removing it
 * from the internal callback registration table.
 *
 * \param[in] type  Type of callback function to unregister
 *
 * \return Status of the de-registration operation.
 * \retval STATUS_OK               The callback was Unregistered successfully
 * \retval STATUS_ERR_INVALID_ARG  If an invalid callback type was supplied
 */
enum status_code wdt_unregister_callback(
		const enum wdt_callback type)
{
	switch (type)
	{
	case WDT_CALLBACK_EARLY_WARNING:
		wdt_early_warning_callback = NULL;
		return STATUS_OK;
	default:
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}
}

/**
 * \brief Enables asynchronous callback generation for a given type.
 *
 * Enables asynchronous callbacks for a given callback type. This must be
 * called before an external interrupt channel will generate callback events.
 *
 * \param[in] type  Type of callback function to enable
 *
 * \return Status of the callback enable operation.
 * \retval STATUS_OK               The callback was enabled successfully
 * \retval STATUS_ERR_INVALID_ARG  If an invalid callback type was supplied
 */
enum status_code wdt_enable_callback(
		const enum wdt_callback type)
{
	Wdt *const WDT_module = WDT;

	switch (type)
	{
	case WDT_CALLBACK_EARLY_WARNING:
		WDT_module->INTENSET.reg = WDT_INTENSET_EW;
		system_interrupt_enable(SYSTEM_INTERRUPT_MODULE_WDT);
		return STATUS_OK;
	default:
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}
}

/**
 * \brief Disables asynchronous callback generation for a given type.
 *
 * Disables asynchronous callbacks for a given callback type.
 *
 * \param[in] type  Type of callback function to disable
 *
 * \return Status of the callback disable operation.
 * \retval STATUS_OK               The callback was disabled successfully
 * \retval STATUS_ERR_INVALID_ARG  If an invalid callback type was supplied
 */
enum status_code wdt_disable_callback(
		const enum wdt_callback type)
{
	Wdt *const WDT_module = WDT;

	switch (type)
	{
	case WDT_CALLBACK_EARLY_WARNING:
		WDT_module->INTENCLR.reg = WDT_INTENCLR_EW;
		return STATUS_OK;
	default:
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}
}

/** Handler for the WDT hardware module interrupt. */
void WDT_Handler(void)
{
	wdt_clear_early_warning();

	if (wdt_early_warning_callback) {
		wdt_early_warning_callback();
	}
}
