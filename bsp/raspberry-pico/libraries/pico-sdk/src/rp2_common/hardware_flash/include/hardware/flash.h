/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_FLASH_H
#define _HARDWARE_FLASH_H

#include "pico.h"

// PICO_CONFIG: PARAM_ASSERTIONS_ENABLED_FLASH, Enable/disable assertions in the flash module, type=bool, default=0, group=hardware_flash
#ifndef PARAM_ASSERTIONS_ENABLED_FLASH
#define PARAM_ASSERTIONS_ENABLED_FLASH 0
#endif

#define FLASH_PAGE_SIZE (1u << 8)
#define FLASH_SECTOR_SIZE (1u << 12)
#define FLASH_BLOCK_SIZE (1u << 16)

/** \file flash.h
 *  \defgroup hardware_flash hardware_flash
 *
 * Low level flash programming and erase API
 *
 * Note these functions are *unsafe* if you have two cores concurrently
 * executing from flash. In this case you must perform your own
 * synchronisation to make sure no XIP accesses take place during flash
 * programming.
 *
 * If PICO_NO_FLASH=1 is not defined (i.e. if the program is built to run from
 * flash) then these functions will make a static copy of the second stage
 * bootloader in SRAM, and use this to reenter execute-in-place mode after
 * programming or erasing flash, so that they can safely be called from
 * flash-resident code.
 *
 * \subsection flash_example Example
 * \include flash_program.c
 */


/*! \brief  Erase areas of flash
 *  \ingroup hardware_flash
 *
 * \param flash_offs Offset into flash, in bytes, to start the erase. Must be aligned to a 4096-byte flash sector.
 * \param count Number of bytes to be erased. Must be a multiple of 4096 bytes (one sector).
 */
void flash_range_erase(uint32_t flash_offs, size_t count);

/*! \brief  Program flash
 *  \ingroup hardware_flash
 *
 * \param flash_offs Flash address of the first byte to be programmed. Must be aligned to a 256-byte flash page.
 * \param data Pointer to the data to program into flash
 * \param count Number of bytes to program. Must be a multiple of 256 bytes (one page).
 */
void flash_range_program(uint32_t flash_offs, const uint8_t *data, size_t count);

#endif
