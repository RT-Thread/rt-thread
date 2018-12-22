/**
 * \file
 *
 * \brief SAM Peripheral Access Controller Driver
 *
 * Copyright (C) 2012-2016 Atmel Corporation. All rights reserved.
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
 * \warning Locking an already locked peripheral will cause a hard fault
 *          exception, and terminate program execution.
 *
 * \param[in] peripheral_id  ID for the peripheral to be locked, sourced via the
 *                           \ref SYSTEM_PERIPHERAL_ID macro.
 * \param[in] key  Bitwise inverse of peripheral ID, used as key to
 *                 reduce the chance of accidental locking. See
 *                 \ref asfdoc_sam0_pac_bitwise_code.
 *
 * \return Status of the peripheral lock procedure.
 * \retval STATUS_OK                If the peripheral was successfully locked.
 * \retval STATUS_ERR_INVALID_ARG	If invalid argument(s) were supplied.
 */
__no_inline enum status_code system_peripheral_lock(
		const uint32_t peripheral_id,
		const uint32_t key)
{
	/* Bit to be set in desired register is given by bit 5:0 */
	uint8_t register_bit_pos = peripheral_id % 32;
	UNUSED(register_bit_pos);

	/* Value of which PAC register to use is given by bit 31:6 */
	uint8_t register_pos = peripheral_id / 32;

	/* Check if key is correct. */
	if (~peripheral_id != key) {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	switch (register_pos) {
#ifdef PAC0
		case 0:
			PAC0->WPSET.reg = (1 << register_bit_pos);
			break;
#endif
#ifdef PAC1
		case 1:
			PAC1->WPSET.reg = (1 << register_bit_pos);
			break;
#endif
#ifdef PAC2
		case 2:
			/* Turn on the digital interface clock */
			system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBC, PM_APBCMASK_PAC2);
			PAC2->WPSET.reg = (1 << register_bit_pos);
			break;
#endif
		default:
			Assert(false);
			return STATUS_ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

/**
 * \brief Unlock a given peripheral's control registers.
 *
 * Unlocks a given peripheral's control registers, allowing write access to the
 * peripheral so that changes can be made to the module's configuration.
 *
 * \warning Unlocking an already locked peripheral will cause a hard fault
 *          exception, and terminate program execution.
 *
 * \param[in] peripheral_id  ID for the peripheral to be unlocked, sourced via the
 *                          \ref SYSTEM_PERIPHERAL_ID macro.
 * \param[in] key  Bitwise inverse of peripheral ID, used as key to
 *                 reduce the chance of accidental unlocking. See
 *                 \ref asfdoc_sam0_pac_bitwise_code.
 *
 * \return Status of the peripheral unlock procedure.
 * \retval STATUS_OK                If the peripheral was successfully locked.
 * \retval STATUS_ERR_INVALID_ARG	If invalid argument(s) were supplied.
 */
__no_inline enum status_code system_peripheral_unlock(
		const uint32_t peripheral_id,
		const uint32_t key)
{
	/* Bit to be set in desired register is given by bit 5:0 */
	uint8_t register_bit_pos = peripheral_id % 32;
	UNUSED(register_bit_pos);

	/* Value of which PAC register to use is given by bit 31:6 */
	uint8_t register_pos = peripheral_id / 32;

	/* Check if key is correct. */
	if (~peripheral_id != key) {
		Assert(false);
		return STATUS_ERR_INVALID_ARG;
	}

	switch (register_pos) {
#ifdef PAC0
		case 0:
			PAC0->WPCLR.reg = (1 << register_bit_pos);
			break;
#endif
#ifdef PAC1
		case 1:
			PAC1->WPCLR.reg = (1 << register_bit_pos);
			break;
#endif
#ifdef PAC2
		case 2:
			/* Turn on the digital interface clock */
			system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBC, PM_APBCMASK_PAC2);
			PAC2->WPCLR.reg = (1 << register_bit_pos);
			break;
#endif
		default:
			Assert(false);
			return STATUS_ERR_INVALID_ARG;
	}

	return STATUS_OK;
}
