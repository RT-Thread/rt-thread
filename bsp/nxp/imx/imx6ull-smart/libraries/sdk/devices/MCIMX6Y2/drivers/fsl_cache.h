/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _FSL_CACHE_H_
#define _FSL_CACHE_H_

#include "fsl_common.h"

/*!
 * @addtogroup cache
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief cache driver version 2.0.0. */
#define FSL_CACHE_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Cache Control for Cortex-a L1 cache
 *@{
 */

/*!
 * @brief Enables L1 instruction cache.
 *
 */
static inline void L1CACHE_EnableICache(void)
{
    L1C_EnableInstructionCache();
}
/*!
 * @brief Disables L1 instruction cache.
 *
 */
static inline void L1CACHE_DisableICache(void)
{
    L1C_DisableInstructionCache();
}
/*!
 * @brief Invalidates L1 instruction cache all.
 *
 */
static inline void L1CACHE_InvalidateICache(void)
{
    L1C_InvalidateInstructionCacheAll();
}
/*!
 * @brief Invalidates L1 instruction cache by range.
 *
 * @param startAddr  The start startAddr of the memory to be invalidated.
 * @param size_byte  The memory size.
 * @note The start startAddr and size_byte should be 32-byte(FSL_FEATURE_L1ICACHE_LINESIZE_BYTE) aligned due to the
 * cache operation unit is one L1 I-cache line. The startAddr here will be forced
 * to align to L1 I-cache line size if startAddr is not aligned. For the size_byte, application should
 * make sure the alignment or make sure the right operation order if the size_byte is not aligned.
 */
static inline void L1CACHE_InvalidateICacheByRange(uint32_t startAddr, uint32_t size_byte)
{
    L1C_InvalidateInstructionCacheRange((void *)startAddr, size_byte);
}
/*!
 * @brief Enables L1 data cache.
 *
 */
static inline void L1CACHE_EnableDCache(void)
{
    L1C_EnableDataCache();
}
/*!
 * @brief Disables L1 data cache.
 *
 */
static inline void L1CACHE_DisableDCache(void)
{
    L1C_DisableDataCache();
}
/*!
 * @brief Invalidates L1 data cache all.
 *
 */
static inline void L1CACHE_InvalidateDCache(void)
{
    L1C_InvalidateDataCacheAll();
}
/*!
 * @brief Invalidates L1 data cache by range.
 *
 * @param startAddr  The start startAddr of the memory to be invalidated.
 * @param size_byte  The memory size.
 * @note The start startAddr and size_byte should be 64-byte(FSL_FEATURE_L1DCACHE_LINESIZE_BYTE) aligned due to the
 * cache operation unit is one L1 D-cache line. The startAddr here will be forced
 * to align to L1 D-cache line size if startAddr is not aligned. For the size_byte, application should
 * make sure the alignment or make sure the right operation order if the size_byte is not aligned.
 */
static inline void L1CACHE_InvalidateDCacheByRange(uint32_t startAddr, uint32_t size_byte)
{
    L1C_InvalidateDataCacheRange((void *)startAddr, size_byte);
}
/*!
 * @brief Clean L1 data cache all.
 *
 */
static inline void L1CACHE_CleanDCache(void)
{
    L1C_CleanDataCacheAll();
}
/*!
 * @brief Cleans L1 data cache by range.
 *
 * @param startAddr  The start startAddr of the memory to be cleaned.
 * @param size_byte  The memory size.
 * @note The start startAddr and size_byte should be 64-byte(FSL_FEATURE_L1DCACHE_LINESIZE_BYTE) aligned due to the
 * cache operation unit is one L1 D-cache line. The startAddr here will be forced
 * to align to L1 D-cache line size if startAddr is not aligned. For size_byte, application should
 * make sure the alignment or make sure the right operation order if the size_byte is not aligned.
 */
static inline void L1CACHE_CleanDCacheByRange(uint32_t startAddr, uint32_t size_byte)
{
    L1C_CleanDataCacheRange((void *)startAddr, size_byte);
}
/*!
 * @brief Cleans and invalidates L1 data cache all.
 *
 */
static inline void L1CACHE_CleanInvalidateDCache(void)
{
    L1C_CleanInvalidateDataCacheAll();
}
/*!
 * @brief Cleans and invalidates L1 data cache by range.
 *
 * @param startAddr  The start startAddr of the memory to be clean and invalidated.
 * @param size_byte  The memory size.
 * @note The start startAddr and size_byte should be 64-byte(FSL_FEATURE_L1DCACHE_LINESIZE_BYTE) aligned due to the
 * cache operation unit is one L1 D-cache line. The startAddr here will be forced
 * to align to L1 D-cache line size if startAddr is not aligned. For size_byte, application should
 * make sure the alignment or make sure the right operation order if the size_byte is not aligned.
 */
static inline void L1CACHE_CleanInvalidateDCacheByRange(uint32_t startAddr, uint32_t size_byte)
{
    L1C_CleanInvalidateDataCacheRange((void *)startAddr, size_byte);
}
/*@}*/

/*!
 * @name Unified Cache Control for all caches which is mainly used for
 *  SDK Driver easy use cache driver
 *@{
 */

/*!
 * @brief Invalidates instruction cache by range.
 *
 * Cortex-a L1 instruction cache line length is 32-byte.
 *
 * @param address The physical address.
 * @param size_byte size of the memory to be invalidated.
 * @note Address and size should be aligned to cache line size
 *  32-Byte due to the cache operation unit is one cache line. The startAddr here will be forced
 * to align to the cache line size if startAddr is not aligned. For the size_byte, application should
 * make sure the alignment or make sure the right operation order if the size_byte is not aligned.
 */
void ICACHE_InvalidateByRange(uint32_t address, uint32_t size_byte);

/*!
 * @brief Invalidates data cache by range.
 *
 * Cortex-a L1 data cache line length is 64-byte.
 *
 * @param address The physical address.
 * @param size_byte size of the memory to be invalidated.
 * @note Address and size should be aligned to cache line size
 *  64-byte due to the cache operation unit is one cache line. The startAddr here will be forced
 * to align to the cache line size if startAddr is not aligned. For the size_byte, application should
 * make sure the alignment or make sure the right operation order if the size_byte is not aligned.
 */
void DCACHE_InvalidateByRange(uint32_t address, uint32_t size_byte);

/*!
 * @brief Cleans data cache by range.
 *
 * Cortex-a L1 data cache line length is 64-byte.
 *
 * @param address The physical address.
 * @param size_byte size of the memory to be cleaned.
 * @note Address and size should be aligned to cache line size
 *  64-byte due to the cache operation unit is one cache line. The startAddr here will be forced
 * to align to the cache line size if startAddr is not aligned. For the size_byte, application should
 * make sure the alignment or make sure the right operation order if the size_byte is not aligned.
 */
void DCACHE_CleanByRange(uint32_t address, uint32_t size_byte);

/*!
 * @brief Cleans and Invalidates data cache by range.
 *
 * Cortex-a L1 data cache line length is 64-byte.
 *
 * @param address The physical address.
 * @param size_byte size of the memory to be cleaned and invalidated.
 * @note Address and size should be aligned to cache line size
 *  64-byte due to the cache operation unit is one cache line. The startAddr here will be forced
 * to align to the cache line size if startAddr is not aligned. For the size_byte, application should
 * make sure the alignment or make sure the right operation order if the size_byte is not aligned.
 */
void DCACHE_CleanInvalidateByRange(uint32_t address, uint32_t size_byte);
/*@}*/
#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_CACHE_H_*/
