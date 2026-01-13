/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_CACHE_H_
#define _FSL_CACHE_H_

#include "fsl_common.h"

/*!
 * @addtogroup cache_armv8a
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief cache driver version 1.0.0. */
#define FSL_CACHE_DRIVER_VERSION (MAKE_VERSION(1, 0, 0))
/*@}*/

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif


/*!
 * @name Unified Cache Control for all caches
 * Mainly used for many drivers for easy cache operation.
 *@{
 */

/*!
 * brief Invalidates all instruction caches by range.
 *
 * param address The virtual address.
 * param size_byte size of the memory to be invalidated.
 */
void ICACHE_InvalidateByRange(uintptr_t address, size_t size_byte);

/*!
 * brief Invalidates all data caches by range.
 *
 * param address The virtual address.
 * param size_byte size of the memory to be invalidated.
 */
void DCACHE_InvalidateByRange(uintptr_t address, size_t size_byte);

/*!
 * brief Cleans all data caches by range.
 *
 * param address The virtual address.
 * param size_byte size of the memory to be cleaned.
 */
void DCACHE_CleanByRange(uintptr_t address, size_t size_byte);

/*!
 * brief Cleans and Invalidates all data caches by range.
 *
 * param address The virtual address.
 * param size_byte size of the memory to be cleaned and invalidated.
 */
void DCACHE_CleanInvalidateByRange(uintptr_t address, size_t size_byte);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_CACHE_H_*/
