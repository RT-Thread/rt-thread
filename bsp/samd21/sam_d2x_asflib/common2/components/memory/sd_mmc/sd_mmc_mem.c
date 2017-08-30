/**
 * \file
 *
 * \brief CTRL_ACCESS interface for common SD/MMC stack
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

#include "conf_access.h"

#if (SD_MMC_0_MEM == ENABLE) || (SD_MMC_1_MEM == ENABLE)

#include "conf_sd_mmc.h"
#include "sd_mmc.h"
#include "sd_mmc_mem.h"

/**
 * \ingroup sd_mmc_stack_mem
 * \defgroup sd_mmc_stack_mem_internal Implementation of SD/MMC Memory
 * @{
 */

/**
 * \name Control Interface
 * @{
 */

static bool sd_mmc_ejected[2] = {false, false};

Ctrl_status sd_mmc_test_unit_ready(uint8_t slot)
{
	switch (sd_mmc_check(slot))
	{
	case SD_MMC_OK:
		if (sd_mmc_ejected[slot]) {
			return CTRL_NO_PRESENT;
		}
		if (sd_mmc_get_type(slot) & (CARD_TYPE_SD | CARD_TYPE_MMC)) {
			return CTRL_GOOD;
		}
		// It is not a memory card
		return CTRL_NO_PRESENT;

	case SD_MMC_INIT_ONGOING:
		return CTRL_BUSY;

	case SD_MMC_ERR_NO_CARD:
		sd_mmc_ejected[slot] = false;
		return CTRL_NO_PRESENT;

	default:
		return CTRL_FAIL;
	}
}

Ctrl_status sd_mmc_test_unit_ready_0(void)
{
	return sd_mmc_test_unit_ready(0);
}


Ctrl_status sd_mmc_test_unit_ready_1(void)
{
	return sd_mmc_test_unit_ready(1);
}

Ctrl_status sd_mmc_read_capacity(uint8_t slot, uint32_t *nb_sector)
{
	// Return last sector address (-1)
	*nb_sector = (sd_mmc_get_capacity(slot) * 2) - 1;
	return sd_mmc_test_unit_ready(slot);
}

Ctrl_status sd_mmc_read_capacity_0(uint32_t *nb_sector)
{
	return sd_mmc_read_capacity(0, nb_sector);
}

Ctrl_status sd_mmc_read_capacity_1(uint32_t *nb_sector)
{
	return sd_mmc_read_capacity(1, nb_sector);
}

bool sd_mmc_unload(uint8_t slot, bool unload)
{
	sd_mmc_ejected[slot] = unload;
	return true;
}

bool sd_mmc_unload_0(bool unload)
{
	return sd_mmc_unload(0, unload);
}

bool sd_mmc_unload_1(bool unload)
{
	return sd_mmc_unload(1, unload);
}

bool sd_mmc_wr_protect(uint8_t slot)
{
	return sd_mmc_is_write_protected(slot);
}

bool sd_mmc_wr_protect_0(void)
{
	return sd_mmc_wr_protect(0);
}

bool sd_mmc_wr_protect_1(void)
{
	return sd_mmc_wr_protect(1);
}

bool sd_mmc_removal(uint8_t slot)
{
	UNUSED(slot);
	return true;
}

bool sd_mmc_removal_0(void)
{
	return sd_mmc_removal(0);
}

bool sd_mmc_removal_1(void)
{
	return sd_mmc_removal(1);
}
//! @}

#if ACCESS_USB == true
/**
 * \name MEM <-> USB Interface
 * @{
 */

#include "udi_msc.h"

COMPILER_WORD_ALIGNED
uint8_t sector_buf_0[SD_MMC_BLOCK_SIZE];

COMPILER_WORD_ALIGNED
uint8_t sector_buf_1[SD_MMC_BLOCK_SIZE];

Ctrl_status sd_mmc_usb_read_10(uint8_t slot, uint32_t addr, uint16_t nb_sector)
{
	bool b_first_step = true;
	uint16_t nb_step;

	switch (sd_mmc_init_read_blocks(slot, addr, nb_sector)) {
	case SD_MMC_OK:
		break;
	case SD_MMC_ERR_NO_CARD:
		return CTRL_NO_PRESENT;
	default:
		return CTRL_FAIL;
	}
	// Pipeline the 2 transfer in order to speed-up the performances
	nb_step = nb_sector + 1;
	while (nb_step--) {
		if (nb_step) { // Skip last step
			// MCI -> RAM
			if (SD_MMC_OK != sd_mmc_start_read_blocks(((nb_step % 2) == 0) ?
					sector_buf_0 : sector_buf_1, 1)) {
				return CTRL_FAIL;
			}
		}
		if (!b_first_step) { // Skip first step
			// RAM -> USB
			if (!udi_msc_trans_block(true,
					((nb_step % 2) == 0) ?
					sector_buf_1 : sector_buf_0,
					SD_MMC_BLOCK_SIZE,
					NULL)) {
				if (!b_first_step) {
					sd_mmc_wait_end_of_read_blocks(true);
				}
				return CTRL_FAIL;
			}
		} else {
			b_first_step = false;
		}
		if (nb_step) { // Skip last step
			if (SD_MMC_OK != sd_mmc_wait_end_of_read_blocks(false)) {
				return CTRL_FAIL;
			}
		}
		b_first_step = false;
	}
	return CTRL_GOOD;
}

Ctrl_status sd_mmc_usb_read_10_0(uint32_t addr, uint16_t nb_sector)
{
	return sd_mmc_usb_read_10(0, addr, nb_sector);
}

Ctrl_status sd_mmc_usb_read_10_1(uint32_t addr, uint16_t nb_sector)
{
	return sd_mmc_usb_read_10(1, addr, nb_sector);
}

Ctrl_status sd_mmc_usb_write_10(uint8_t slot, uint32_t addr, uint16_t nb_sector)
{
	bool b_first_step = true;
	uint16_t nb_step;

	switch (sd_mmc_init_write_blocks(slot, addr, nb_sector)) {
	case SD_MMC_OK:
		break;
	case SD_MMC_ERR_NO_CARD:
		return CTRL_NO_PRESENT;
	default:
		return CTRL_FAIL;
	}
	// Pipeline the 2 transfer in order to speed-up the performances
	nb_step = nb_sector + 1;
	while (nb_step--) {
		if (!b_first_step) { // Skip first step
			// RAM -> MCI
			if (SD_MMC_OK != sd_mmc_start_write_blocks(((nb_step % 2) == 0) ?
					sector_buf_0 : sector_buf_1, 1)) {
				return CTRL_FAIL;
			}
		}
		if (nb_step) { // Skip last step
			// USB -> RAM
			if (!udi_msc_trans_block(false,
					((nb_step % 2) == 0) ?
					sector_buf_1 : sector_buf_0,
					SD_MMC_BLOCK_SIZE,
					NULL)) {
				if (!b_first_step) {
					sd_mmc_wait_end_of_write_blocks(true);
				}
				return CTRL_FAIL;
			}
		}
		if (!b_first_step) { // Skip first step
			if (SD_MMC_OK != sd_mmc_wait_end_of_write_blocks(false)) {
				return CTRL_FAIL;
			}
		} else {
			b_first_step = false;
		}
	}
	return CTRL_GOOD;
}

Ctrl_status sd_mmc_usb_write_10_0(uint32_t addr, uint16_t nb_sector)
{
	return sd_mmc_usb_write_10(0, addr, nb_sector);
}

Ctrl_status sd_mmc_usb_write_10_1(uint32_t addr, uint16_t nb_sector)
{
	return sd_mmc_usb_write_10(1, addr, nb_sector);
}
//! @}
#endif // ACCESS_USB == true


#if ACCESS_MEM_TO_RAM == true
/**
 * \name MEM <-> RAM Interface
 * @{
 */
Ctrl_status sd_mmc_mem_2_ram(uint8_t slot, uint32_t addr, void *ram)
{
	switch (sd_mmc_init_read_blocks(slot, addr, 1)) {
	case SD_MMC_OK:
		break;
	case SD_MMC_ERR_NO_CARD:
		return CTRL_NO_PRESENT;
	default:
		return CTRL_FAIL;
	}
	if (SD_MMC_OK != sd_mmc_start_read_blocks(ram, 1)) {
		return CTRL_FAIL;
	}
	if (SD_MMC_OK != sd_mmc_wait_end_of_read_blocks(false)) {
		return CTRL_FAIL;
	}
	return CTRL_GOOD;
}

Ctrl_status sd_mmc_mem_2_ram_0(uint32_t addr, void *ram)
{
	return sd_mmc_mem_2_ram(0, addr, ram);
}

Ctrl_status sd_mmc_mem_2_ram_1(uint32_t addr, void *ram)
{
	return sd_mmc_mem_2_ram(1, addr, ram);
}

Ctrl_status sd_mmc_ram_2_mem(uint8_t slot, uint32_t addr, const void *ram)
{
	switch (sd_mmc_init_write_blocks(slot, addr, 1)) {
	case SD_MMC_OK:
		break;
	case SD_MMC_ERR_NO_CARD:
		return CTRL_NO_PRESENT;
	default:
		return CTRL_FAIL;
	}
	if (SD_MMC_OK != sd_mmc_start_write_blocks(ram, 1)) {
		return CTRL_FAIL;
	}
	if (SD_MMC_OK != sd_mmc_wait_end_of_write_blocks(false)) {
		return CTRL_FAIL;
	}
	return CTRL_GOOD;
}

Ctrl_status sd_mmc_ram_2_mem_0(uint32_t addr, const void *ram)
{
	return sd_mmc_ram_2_mem(0, addr, ram);
}

Ctrl_status sd_mmc_ram_2_mem_1(uint32_t addr, const void *ram)
{
	return sd_mmc_ram_2_mem(1, addr, ram);
}
//! @}

//! @}
#endif // ACCESS_MEM_TO_RAM == true

#endif // SD_MMC_0_MEM == ENABLE || SD_MMC_1_MEM == ENABLE
