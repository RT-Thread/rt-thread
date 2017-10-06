/**
 *
 * \file
 *
 * \brief SAM DSU CRC32 driver.
 *
 * This file defines a useful set of functions for DSU CRC32 on SAM devices.
 *
 * Copyright (c) 2016-2017 Atmel Corporation. All rights reserved.
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

#include <system_interrupt.h>
#include <pac.h>
#include <crc32.h>

/**
 * \brief Calculate CRC32 value of the input memory
 *
 * Calculate CRC32 value of the input memory.
 *
 * The read value must be complemented to match standard CRC32 implementations
 * or kept non-inverted if used as starting point for subsequent CRC32 calculations.
 *
 * \param[in] addr    Memory address to calculate CRC32
 * \param[in] len     Memory length to calculate CRC32
 * \param[in,out] pcrc32 Initial value used for the CRC32 calculation, and CRC32 result after calculation
 *
 * \return Status of the configuration procedure.
 *
 * \retval STATUS_OK      If CRC32 calculation OK
 * \retval STATUS_ERR_BAD_ADDRESS  The address was not aligned with 4 bytes.
 
 * \retval STATUS_ERR_IO  A bus error is detected
 */
enum status_code dsu_crc32_cal(const uint32_t addr, const uint32_t len, uint32_t *pcrc32)
{
	if (addr & 0x00000003) {
		return STATUS_ERR_BAD_ADDRESS;
	}

	system_interrupt_disable_global();
	system_peripheral_unlock(SYSTEM_PERIPHERAL_ID(DSU), ~SYSTEM_PERIPHERAL_ID(DSU));

	DSU->DATA.reg = *pcrc32;
	DSU->ADDR.reg = addr;
	DSU->LENGTH.reg = len;

	DSU->CTRL.bit.CRC = 1;
	while ((DSU->STATUSA.reg & DSU_STATUSA_DONE) != 1) {	
	}

	if (DSU->STATUSA.reg & DSU_STATUSA_BERR) {
		system_peripheral_lock(SYSTEM_PERIPHERAL_ID(DSU), ~SYSTEM_PERIPHERAL_ID(DSU));
		system_interrupt_enable_global();
		return STATUS_ERR_IO;
	}

	*pcrc32 = DSU->DATA.reg;
	DSU->STATUSA.reg = DSU_STATUSA_DONE;

	system_peripheral_lock(SYSTEM_PERIPHERAL_ID(DSU), ~SYSTEM_PERIPHERAL_ID(DSU));
	system_interrupt_enable_global();
	return STATUS_OK;
}