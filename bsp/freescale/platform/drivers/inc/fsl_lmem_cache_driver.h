/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
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
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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
#if !defined(__FSL_LMEM_CACHE_DRIVER_H__)
#define __FSL_LMEM_CACHE_DRIVER_H__

#include "fsl_lmem_cache_hal.h"

#if FSL_FEATURE_SOC_LMEM_COUNT

/*!
 * @addtogroup local_memory_controller_cache_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Table of base addresses for the LMEM instances. */
extern LMEM_Type * const g_lmemBase[LMEM_INSTANCE_COUNT];

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Processor Code Bus Cache Control Peripheral Driver
 *@{
 */

/*!
 * @brief Invalidates the processor code bus cache.
 *
 * This function invalidates the cache both ways, which means that
 * it unconditionally clears valid bits and modifies bits of a cache entry.
 *
 * @param instance The instance number of the LMEM peripheral
 */
void LMEM_DRV_CodeCacheInvalidateAll(uint32_t instance);

/*!
 * @brief Pushes all modified lines in the processor code bus cache.
 *
 * This function pushes all modified lines in both ways (the entire cache).
 * Pushes a cache entry if it is valid and modified, then clears the modify bit. If
 * entry is not valid or not modified, leave as is. This action does not clear the valid
 * bit. A cache push is synonymous with a cache flush.
 *
 * @param instance The instance number of the LMEM peripheral
 */
void LMEM_DRV_CodeCachePushAll(uint32_t instance);

/*!
 * @brief Cears the processor code bus cache.
 *
 * This function clears the entire cache and pushes (flushes) and
 * invalidates the operation.
 * Clear - Push a cache entry if it is valid and modified, then clear the valid and
 * modify bits. If the entry is not valid or not modified, clear the valid bit.
 *
 * @param instance The instance number of the LMEM peripheral
 */
void LMEM_DRV_CodeCacheClearAll(uint32_t instance);

/*!
 * @brief Enables the processor code bus cache.
 *
 * This function enables the cache.  The function first invalidates the entire cache,
 * then enables both the cache and write buffer.
 *
 * @param instance The instance number of the LMEM peripheral
 */
void LMEM_DRV_CodeCacheEnable(uint32_t instance);

/*!
 * @brief Disables the processor code bus cache.
 *
 * This function disables the cache and write buffer.
 *
 * @param instance The instance number of the LMEM peripheral
 */
void LMEM_DRV_CodeCacheDisable(uint32_t instance);

/*!
 * @brief Invalidates a specific line in the processor code bus cache.
 *
 * This function invalidates a specific line in the cache
 * based on the physical address passed in by the user.
 * Invalidate - Unconditionally clear valid and modify bits of a cache entry
 *
 * @param instance The instance number of the LMEM peripheral
 * @param addr The physical address of the cache line
 */
void LMEM_DRV_CodeCacheInvalidateLine(uint32_t instance, uint32_t addr);

/*!
 * @brief Invalidates multiple lines in the processor code bus cache.
 *
 * This function invalidates multiple lines in the cache
 * based on the physical address and length in bytes passed in by the
 * user.  If the function detects that the length meets or exceeds half the
 * cache, then the function performs an entire cache invalidate function which is
 * more efficient than invalidating the cache line-by-line.
 * The need to check half the total amount of cache is due to the fact that the cache consists of
 * two ways and that line commands based on the physical address searches both ways.
 * Invalidate - Unconditionally clear valid and modify bits of a cache entry
 *
 * @param instance The instance number of the LMEM peripheral
 * @param addr The physical address of the cache line
 * @param length The length in bytes of the total amount of cache lines
 */
void LMEM_DRV_CodeCacheInvalidateMultiLines(uint32_t instance, uint32_t addr, uint32_t length);

/*!
 * @brief Pushes a specific modified line in the processor code bus cache.
 *
 * This function pushes a specific modified line based on the physical address passed in
 * by the user.
 * Push - Push a cache entry if it is valid and modified, then clear the modify bit. If
 * entry not valid or not modified, leave as is. This action does not clear the valid
 * bit. A cache push is synonymous with a cache flush.
 *
 * @param instance The instance number of the LMEM peripheral
 * @param addr The physical address of the cache line
 */
void LMEM_DRV_CodeCachePushLine(uint32_t instance, uint32_t addr);

/*!
 * @brief Pushes multiple modified lines in the processor code bus cache.
 *
 * This function pushes multiple modified lines in the cache
 * based on the physical address and length in bytes passed in by the
 * user.  If the function detects that the length meets or exceeds half of the
 * cache, the function performs an cache push function (which is
 * more efficient than pushing the modified lines in the cache line-by-line).
 * The need to check half the total amount of cache is due to the fact that the cache consists of
 * two ways and that line commands based on the physical address searches both ways.
 * Push - Push a cache entry if it is valid and modified, then clear the modify bit. If
 * entry not valid or not modified, leave as is. This action does not clear the valid
 * bit. A cache push is synonymous with a cache flush.
 *
 * @param instance The instance number of the LMEM peripheral
 * @param addr The physical address of the cache line
 * @param length The length in bytes of the total amount of cache lines
 */
void LMEM_DRV_CodeCachePushMultiLines(uint32_t instance, uint32_t addr, uint32_t length);

/*!
 * @brief Clears a specific line in the processor code bus cache.
 *
 * This function clears a specific line based on the physical address passed in
 * by the user.
 * Clear - Push a cache entry if it is valid and modified, then clear the valid and
 * modify bits. If entry not valid or not modified, clear the valid bit.
 *
 * @param instance The instance number of the LMEM peripheral
 * @param addr The physical address of the cache line
 */
void LMEM_DRV_CodeCacheClearLine(uint32_t instance, uint32_t addr);

/*!
 * @brief Clears multiple lines in the processor code bus cache.
 *
 * This function clears multiple lines in the cache
 * based on the physical address and length in bytes passed in by the
 * user.  If the function detects that the length meets or exceeds half the total amount of
 * cache, the function performs a cache clear function which is
 * more efficient than clearing the lines in the cache line-by-line.
 * The need to check half the total amount of cache is due to the fact that the cache consists of
 * two ways and that line commands based on the physical address searches both ways.
 * Clear - Push a cache entry if it is valid and modified, then clear the valid and
 * modify bits. If entry not valid or not modified, clear the valid bit.
 *
 * @param instance The instance number of the LMEM peripheral
 * @param addr The physical address of the cache line
 * @param length The length in bytes of the total amount of cache lines
 */
void LMEM_DRV_CodeCacheClearMultiLines(uint32_t instance, uint32_t addr, uint32_t length);

/*!
 * @brief Demotes the cache mode of a region in processor code bus cache.
 *
 * This function allows the user to demote the cache mode of a region within the device's
 * memory map. Demoting the cache mode reduces the cache function applied to a memory
 * region from write-back to write-through to non-cacheable.  The function checks to see
 * if the requested cache mode is higher than or equal to the current cache mode, and if
 * so, returns an error. After a region is demoted, its cache mode can only be raised
 * by a reset, which returns it to its default state.
 * To maintain cache coherency, changes to the cache mode should be completed while the
 * address space being changed is not being accessed or the cache is disabled. Before a
 * cache mode change, this function completes a cache clear all command to push and invalidate any
 * cache entries that may have changed.
 *
 * @param instance The instance number of the LMEM peripheral
 * @param region The desired region to demote of type lmem_cache_region_t
 * @param cacheMode The new, demoted cache mode of type lmem_cache_mode_t
 *
 * @return kStatus_LMEM_CACHE_Success The cache clear operation was successful, or
 *         kStatus_LMEM_CACHE_Busy The cache is busy performing another operation
 *         kStatus_LMEM_CACHE_Error The requested cache mode is higher than or equal to the
 *                                  current cache mode
 */
lmem_cache_status_t LMEM_DRV_CodeCacheDemoteRegion(uint32_t instance, lmem_cache_region_t region,
                                                   lmem_cache_mode_t cacheMode);

/*@}*/

#if FSL_FEATURE_LMEM_HAS_SYSTEMBUS_CACHE
/*!
 * @name Processor System Bus Cache Control Peripheral Driver
 *@{
 */

/*!
 * @brief Invalidates the processor code bus cache.
 *
 * This function invalidates the entire cache both ways.
 * Invalidate - Unconditionally clear valid and modify bits of a cache entry
 *
 * @param instance The instance number of the LMEM peripheral
 */
void LMEM_DRV_SystemCacheInvalidateAll(uint32_t instance);

/*!
 * @brief Pushes all modified lines in the  processor code bus
 *        cache.
 *
 * This function pushes all modified lines in both ways (the entire cache).
 * Push - Push a cache entry if it is valid and modified, then clear the modify bit. If
 * entry is not valid or not modified, leave as is. This action does not clear the valid
 * bit. A cache push is synonymous with a cache flush.
 *
 * @param instance The instance number of the LMEM peripheral
 */
void LMEM_DRV_SystemCachePushAll(uint32_t instance);

/*!
 * @brief Clears the entire processor code bus cache.
 *
 * This function clears the entire cache, which is a push (flush) and
 * invalidate operation.
 * Clear - Push a cache entry if it is valid and modified, then clear the valid and
 * modify bits. If entry not valid or not modified, clear the valid bit.
 *
 * @param instance The instance number of the LMEM peripheral
 */
void LMEM_DRV_SystemCacheClearAll(uint32_t instance);

/*!
 * @brief Enables the processor code bus cache.
 *
 * This function enables the cache. It first invalidates the entire cache,
 * then enables both the cache and write buffer.
 *
 * @param instance The instance number of the LMEM peripheral
 */
void LMEM_DRV_SystemCacheEnable(uint32_t instance);

/*!
 * @brief Disables the processor code bus cache.
 *
 * This function disables the cache and write buffer.
 *
 * @param instance The instance number of the LMEM peripheral
 */
void LMEM_DRV_SystemCacheDisable(uint32_t instance);

/*!
 * @brief Invalidates a specific line in the processor code bus cache.
 *
 * This function invalidates a specific line in the cache
 * based on the physical address passed in by the user.
 * Invalidate - Unconditionally clear valid and modify bits of a cache entry
 *
 * @param instance The instance number of the LMEM peripheral
 * @param addr The physical address of the cache line
 */
void LMEM_DRV_SystemCacheInvalidateLine(uint32_t instance, uint32_t addr);

/*!
 * @brief Invalidates multiple lines in the processor code bus cache.
 *
 * This function invalidates multiple lines in the cache
 * based on the physical address and length in bytes passed in by the
 * user.  If the function detects that the length meets or exceeds half of the
 * cache, the function performs an entire cache invalidate function (which is
 * more efficient than invalidating the cache line-by-line).
 * The need to check half the total amount of cache is due to the fact that the cache consists of
 * two ways and that line commands based on the physical address  searches both ways.
 * Invalidate - Unconditionally clear valid and modify bits of a cache entry
 *
 * @param instance The instance number of the LMEM peripheral
 * @param addr The physical address of the cache line
 * @param length The length in bytes of the total amount of cache lines
 */
void LMEM_DRV_SystemCacheInvalidateMultiLines(uint32_t instance, uint32_t addr, uint32_t length);

/*!
 * @brief Pushes a specific modified line in the processor code bus
 *        cache.
 *
 * This function pushes a specific modified line based on the physical address passed in
 * by the user.
 * Push - Push a cache entry if it is valid and modified, then clear the modify bit. If
 * entry not valid or not modified, leave as is. This action does not clear the valid
 * bit. A cache push is synonymous with a cache flush.
 *
 * @param instance The instance number of the LMEM peripheral
 * @param addr The physical address of the cache line
 */
void LMEM_DRV_SystemCachePushLine(uint32_t instance, uint32_t addr);

/*!
 * @brief Pushes multiple modified lines in the processor code bus cache.
 *
 * This function pushes multiple modified lines in the cache
 * based on the physical address and length in bytes passed in by the
 * user.  If the function detects that the length meets or exceeds half of the
 * cache, the function performs an entire cache push function (which is
 * more efficient than pushing the modified lines in the cache line-by-line).
 * The need to check half the total amount of cache is due to the fact that the cache consists of
 * two ways and that line commands based on the physical address searches both ways.
 * Push - Push a cache entry if it is valid and modified, then clear the modify bit. If
 * entry not valid or not modified, leave as is. This action does not clear the valid
 * bit. A cache push is synonymous with a cache flush.
 *
 * @param instance The instance number of the LMEM peripheral
 * @param addr The physical address of the cache line
 * @param length The length in bytes of the total amount of cache lines
 */
void LMEM_DRV_SystemCachePushMultiLines(uint32_t instance, uint32_t addr, uint32_t length);

/*!
 * @brief Clears a specific line in the processor code bus cache.
 *
 * This function clears a specific line based on the physical address passed in
 * by the user.
 * Clear - Push a cache entry if it is valid and modified, then clear the valid and
 * modify bits. If entry not valid or not modified, clear the valid bit.
 *
 * @param instance The instance number of the LMEM peripheral
 * @param addr The physical address of the cache line
 */
void LMEM_DRV_SystemCacheClearLine(uint32_t instance, uint32_t addr);

/*!
 * @brief Clears multiple lines in the processor code bus cache.
 *
 * This function clears multiple lines in the cache
 * based on the physical address and length in bytes passed in by the
 * user.  If the function detects that the length meets or exceeds half of the
 * cache, the function performs an entire cache clear function (which is
 * more efficient than clearing the lines in the cache line-by-line).
 * The need to check half the total amount of cache is due to the fact that the cache consists of
 * two ways and that line commands based on the physical address searches both ways.
 * Clear - Push a cache entry if it is valid and modified, then clear the valid and
 * modify bits. If entry not valid or not modified, clear the valid bit.
 *
 * @param instance The instance number of the LMEM peripheral
 * @param addr The physical address of the cache line
 * @param length The length in bytes of the total amount of cache lines
 */
void LMEM_DRV_SystemCacheClearMultiLines(uint32_t instance, uint32_t addr, uint32_t length);

/*!
 * @brief Demotes the cache mode of a region in the processor code bus cache.
 *
 * This function allows the user to demote the cache mode of a region within the device's
 * memory map. Demoting the cache mode reduces the cache function applied to a memory
 * region from write-back to write-through to non-cacheable.  The function checks to see
 * if the requested cache mode is higher than or equal to the current cache mode, and if
 * so, returns an error. After a region is demoted, its cache mode can only be raised
 * by a reset, which returns it to its default state.
 * To maintain cache coherency, changes to the cache mode should be completed while the
 * address space being changed is not being accessed or the cache is disabled. Before a
 * cache mode change, this function completes a cache clear all command to push and invalidate any
 * cache entries that may have changed.
 *
 * @param instance The instance number of the LMEM peripheral
 * @param region The desired region to demote of type lmem_cache_region_t
 * @param cacheMode The new, demoted cache mode of type lmem_cache_mode_t
 *
 * @return kStatus_LMEM_CACHE_Success The cache clear operation was successful, or
 *         kStatus_LMEM_CACHE_Busy The cache is busy performing another operation
 *         kStatus_LMEM_CACHE_Error The requested cache mode is higher than or equal to the
 *                                  current cache mode
 */
lmem_cache_status_t LMEM_DRV_SystemCacheDemoteRegion(uint32_t instance, lmem_cache_region_t region,
                                                     lmem_cache_mode_t cacheMode);

/*@}*/
#endif /* #if FSL_FEATURE_LMEM_HAS_SYSTEMBUS_CACHE */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FEATURE_SOC_LMEM_COUNT */
#endif /* __FSL_LMEM_CACHE_DRIVER_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

