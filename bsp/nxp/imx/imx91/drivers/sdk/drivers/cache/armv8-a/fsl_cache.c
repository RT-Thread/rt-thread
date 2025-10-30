/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_cache.h"
#include "cache_armv8a.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.cache_armv8a"
#endif

/*!
 * brief Invalidates all instruction caches by range.
 *
 * param address The virtual address.
 * param size_byte size of the memory to be invalidated.
 */
void ICACHE_InvalidateByRange(uintptr_t address, size_t size_byte)
{
	icache_invalidate_range(address, size_byte);
}

/*!
 * brief Invalidates all data caches by range.
 *
 * param address The virtual address.
 * param size_byte size of the memory to be invalidated.
 */
void DCACHE_InvalidateByRange(uintptr_t address, size_t size_byte)
{
	dcache_invalidate_range(address, size_byte);
}

/*!
 * brief Cleans all data caches by range.
 *
 * param address The virtual address.
 * param size_byte size of the memory to be cleaned.
 */
void DCACHE_CleanByRange(uintptr_t address, size_t size_byte)
{
	dcache_clean_range(address, size_byte);
}

/*!
 * brief Cleans and Invalidates all data caches by range.
 *
 * param address The virtual address.
 * param size_byte size of the memory to be cleaned and invalidated.
 */
void DCACHE_CleanInvalidateByRange(uintptr_t address, size_t size_byte)
{
	dcache_clean_invalidate_range(address, size_byte);
}
