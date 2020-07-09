/**
 * \file
 *
 * \brief SAM Peripheral Access Controller Driver
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

#include "pac.h"

/**
 * \brief Lock a given peripheral's control registers.
 *
 * Locks a given peripheral's control registers, to deny write access to the
 * peripheral to prevent accidental changes to the module's configuration.
 *
 * \warning Locking an already locked peripheral will cause a CPU
 *          exception, and terminate program execution.
 *
 * \param[in] peripheral_id  ID for the peripheral to be locked, sourced via the
 *                           \ref SYSTEM_PERIPHERAL_ID macro
 * \param[in] key  Bitwise inverse of peripheral ID, used as key to
 *                 reduce the chance of accidental locking. See
 *                 \ref asfdoc_sam0_pac_bitwise_code
 *
 * \return Status of the peripheral lock procedure.
 * \retval STATUS_OK                If the peripheral was successfully locked
 * \retval STATUS_ERR_INVALID_ARG	If invalid argument(s) were supplied
 */
__no_inline enum status_code system_peripheral_lock(
		const uint32_t peripheral_id,
		const uint32_t key)
{
	/* Check if key is correct. */
	if (~peripheral_id != key) {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	PAC->WRCTRL.reg = peripheral_id | PAC_WRCTRL_KEY(PAC_WRCTRL_KEY_SET_Val);

	return STATUS_OK;
}

/**
 * \brief Lock a given peripheral's control registers until hardware reset.
 *
 * Locks a given peripheral's control registers, to deny write access to the
 * peripheral to prevent accidental changes to the module's configuration.
 * After lock, the only way to unlock is hardware reset.
 *
 * \warning Locking an already locked peripheral will cause a CPU
 *          exception, and terminate program execution.
 *
 * \param[in] peripheral_id  ID for the peripheral to be locked, sourced via the
 *                           \ref SYSTEM_PERIPHERAL_ID macro
 * \param[in] key  Bitwise inverse of peripheral ID, used as key to
 *                 reduce the chance of accidental locking. See
 *                 \ref asfdoc_sam0_pac_bitwise_code
 *
 * \return Status of the peripheral lock procedure.
 * \retval STATUS_OK                If the peripheral was successfully locked
 * \retval STATUS_ERR_INVALID_ARG	If invalid argument(s) were supplied
 */
__no_inline enum status_code system_peripheral_lock_always(
		const uint32_t peripheral_id,
		const uint32_t key)
{
	/* Check if key is correct. */
	if (~peripheral_id != key) {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	PAC->WRCTRL.reg = peripheral_id | PAC_WRCTRL_KEY(PAC_WRCTRL_KEY_SETLCK_Val);

	return STATUS_OK;
}

/**
 * \brief Unlock a given peripheral's control registers.
 *
 * Unlocks a given peripheral's control registers, allowing write access to the
 * peripheral so that changes can be made to the module's configuration.
 *
 * \warning Unlocking an already locked peripheral will cause a CUP
 *          exception, and terminate program execution.
 *
 * \param[in] peripheral_id  ID for the peripheral to be unlocked, sourced via the
 *                          \ref SYSTEM_PERIPHERAL_ID macro
 * \param[in] key  Bitwise inverse of peripheral ID, used as key to
 *                 reduce the chance of accidental unlocking. See
 *                 \ref asfdoc_sam0_pac_bitwise_code
 *
 * \return Status of the peripheral unlock procedure.
 * \retval STATUS_OK                If the peripheral was successfully locked
 * \retval STATUS_ERR_INVALID_ARG	If invalid argument(s) were supplied
 */
__no_inline enum status_code system_peripheral_unlock(
		const uint32_t peripheral_id,
		const uint32_t key)
{
	/* Check if key is correct. */
	if (~peripheral_id != key) {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	PAC->WRCTRL.reg = peripheral_id | PAC_WRCTRL_KEY(PAC_WRCTRL_KEY_CLR_Val);

	return STATUS_OK;
}
