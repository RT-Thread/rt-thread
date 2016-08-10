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

#include "fsl_lmem_cache_driver.h"

#if FSL_FEATURE_SOC_LMEM_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_CodeCacheInvalidateAll
 * Description   : This function invalidates the entire Processor Code bus cache.
 *
 * This function invalidates the entire cache meaning that it invalidates both Ways.
 * Invalidate - Unconditionally clear valid and modify bits of a cache entry
 *
 *END**************************************************************************/
void LMEM_DRV_CodeCacheInvalidateAll(uint32_t instance)
{
    LMEM_Type *base = g_lmemBase[instance];

    LMEM_HAL_SetCodeCacheInvalidateAllCmd(base, true);
    LMEM_HAL_InitiateCodeCacheCommand(base);

    /* Wait until the cache command completes */
    while (LMEM_HAL_IsCodeCacheCommandActive(base)) { }

    /* As a precaution clear the bits to avoid inadvertently re-running this command */
    LMEM_HAL_SetCodeCacheInvalidateAllCmd(base, false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_CodeCachePushAll
 * Description   : This function pushes all modified lines in the entire Processor Code bus cache.
 *
 * This function pushes all modified lines in both Ways (the entire cache).
 * Push - Push a cache entry if it is valid and modified, then clear the modify bit. If
 * entry not valid or not modified, leave as is. This action does not clear the valid
 * bit. A cache push is synonymous with a cache flush.
 *
 *END**************************************************************************/
void LMEM_DRV_CodeCachePushAll(uint32_t instance)
{
    LMEM_Type *base = g_lmemBase[instance];

    LMEM_HAL_SetCodeCachePushAllCmd(base, true);
    LMEM_HAL_InitiateCodeCacheCommand(base);

    /* Wait until the cache command completes */
    while (LMEM_HAL_IsCodeCacheCommandActive(base)) { }

    /* As a precaution clear the bits to avoid inadvertently re-running this command */
    LMEM_HAL_SetCodeCachePushAllCmd(base, false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_CodeCacheClearAll
 * Description   : This function clears the entire Processor Code bus cache.
 *
 * This function clears the entire cache, which is basically a push (flush) and
 * invalidate operation.
 * Clear - Push a cache entry if it is valid and modified, then clear the valid and
 * modify bits. If entry not valid or not modified, clear the valid bit.
 *
 *END**************************************************************************/
void LMEM_DRV_CodeCacheClearAll(uint32_t instance)
{
    LMEM_Type *base = g_lmemBase[instance];

    /* Push and invalidate all */
    LMEM_HAL_SetCodeCachePushAllCmd(base, true);
    LMEM_HAL_SetCodeCacheInvalidateAllCmd(base, true);
    LMEM_HAL_InitiateCodeCacheCommand(base);

    /* Wait until the cache command completes */
    while (LMEM_HAL_IsCodeCacheCommandActive(base)) { }

    /* As a precaution clear the bits to avoid inadvertently re-running this command */
    LMEM_HAL_SetCodeCachePushAllCmd(base, false);
    LMEM_HAL_SetCodeCacheInvalidateAllCmd(base, false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_CodeCacheEnable
 * Description   : This function enables the Processor Code bus cache.
 *
 * This function enables the cache.  The function first invalidates the entire cache,
 * then it enables both the cache and write buffer.
 *
 *END**************************************************************************/
void LMEM_DRV_CodeCacheEnable(uint32_t instance)
{
    LMEM_Type *base = g_lmemBase[instance];

    /* First, invalidate the entire cache */
    LMEM_DRV_CodeCacheInvalidateAll(instance);

    /* Now enable the cache */
    LMEM_HAL_SetCodeCacheEnableCmd(base, true);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_CodeCacheEnable
 * Description   : This function disables the Processor Code bus cache.
 *
 * This function disables the cache and write buffer.
 *
 *END**************************************************************************/
void LMEM_DRV_CodeCacheDisable(uint32_t instance)
{
    LMEM_Type *base = g_lmemBase[instance];

    /* First, push any modified contents */
    LMEM_DRV_CodeCachePushAll(instance);

    /* Now disable the cache */
    LMEM_HAL_SetCodeCacheEnableCmd(base, false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_CodeCacheInvalidateLine
 * Description   : This function invalidates a specific line in the Processor Code bus cache.
 *
 * This function invalidates a specific line in the cache. The function invalidates a
 * line in cache based on the physical address passed in by the user.
 * Invalidate - Unconditionally clear valid and modify bits of a cache entry
 *
 *END**************************************************************************/
void LMEM_DRV_CodeCacheInvalidateLine(uint32_t instance, uint32_t addr)
{
    LMEM_Type *base = g_lmemBase[instance];

    /* Set the invalidate by line command */
    LMEM_HAL_SetCodeCacheLineCommand(base, kCacheLineInvalidate);

    /* Since we're using the physical address, both ways are searched */
    LMEM_HAL_SetCodeCachePhysicalAddr(base, addr);

    LMEM_HAL_InitiateCodeCacheLineCommand(base);

    /* Set the line command to use the physical address */
    LMEM_BWR_PCCLCR_LADSEL(base, 1U);

    /* Wait until the cache command completes */
    while (LMEM_HAL_IsCodeCacheLineCommandActive(base)) { }

    /* No need to clear this command since future line commands will overwrite
     * the line command field
     */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_CodeCacheInvalidateMultiLines
 * Description   : This function invalidates multiple lines in the Processor Code bus cache.
 *
 * This function invalidates multiple lines in the cache. The function invalidates the
 * lines in cache based on the physical address and length in bytes passed in by the
 * user.  If the function detects that the length meets or exceeds half the total amount of
 * cache, then the function shall perform an entire cache invalidate function (which is
 * more efficient than invalidating the cache line-by-line).
 * The need to check half the total amount of cache is due to the fact that the cache consists of
 * two ways and that line commands based on the physical address will search both ways.
 * Invalidate - Unconditionally clear valid and modify bits of a cache entry
 *
 *END**************************************************************************/
void LMEM_DRV_CodeCacheInvalidateMultiLines(uint32_t instance, uint32_t addr, uint32_t length)
{
    uint32_t endAddr = addr + length;
    addr = addr & ~(LMEM_CACHE_LINE_SIZE - 1U);  /* Align address to cache line size */

    /* If the length exceeds 4KB, invalidate all */
    if (length >= 4096U)
    {
        LMEM_DRV_CodeCacheInvalidateAll(instance);
    }
    /* Else proceed with multi-line invalidate */
    else
    {
        while (addr < endAddr)
        {
            LMEM_DRV_CodeCacheInvalidateLine(instance, addr);
            addr = addr + LMEM_CACHE_LINE_SIZE;
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_CodeCachePushLine
 * Description   : This function pushes a specific modified line in the Processor Code bus cache.
 *
 * This function pushes a specific modified line based on the physical address passed in
 * by the user.
 * Push - Push a cache entry if it is valid and modified, then clear the modify bit. If
 * entry not valid or not modified, leave as is. This action does not clear the valid
 * bit. A cache push is synonymous with a cache flush.
 *
 *END**************************************************************************/
void LMEM_DRV_CodeCachePushLine(uint32_t instance, uint32_t addr)
{
    LMEM_Type *base = g_lmemBase[instance];

    /* Set the push by line command */
    LMEM_HAL_SetCodeCacheLineCommand(base, kCacheLinePush);

    /* Since we're using the physical address, both ways are searched */
    LMEM_HAL_SetCodeCachePhysicalAddr(base, addr);

    LMEM_HAL_InitiateCodeCacheLineCommand(base);

    /* Set the line command to use the physical address */
    LMEM_BWR_PCCLCR_LADSEL(base, 1U);

    /* Wait until the cache command completes */
    while (LMEM_HAL_IsCodeCacheLineCommandActive(base)) { }

    /* No need to clear this command since future line commands will overwrite
     * the line command field
     */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_CodeCachePushMultiLines
 * Description   : This function pushes multiple modified lines in the Processor Code bus cache.
 *
 * This function pushes multiple modified lines in the cache. The function pushes the
 * lines in cache based on the physical address and length in bytes passed in by the
 * user.  If the function detects that the length meets or exceeds half the total amount of
 * cache, then the function shall perform an entire cache push function (which is
 * more efficient than pushing the modified lines in the cache line-by-line).
 * The need to check half the total amount of cache is due to the fact that the cache consists of
 * two ways and that line commands based on the physical address will search both ways.
 * Push - Push a cache entry if it is valid and modified, then clear the modify bit. If
 * entry not valid or not modified, leave as is. This action does not clear the valid
 * bit. A cache push is synonymous with a cache flush.
 *
 *END**************************************************************************/
void LMEM_DRV_CodeCachePushMultiLines(uint32_t instance, uint32_t addr, uint32_t length)
{
    uint32_t endAddr = addr + length;
    addr = addr & ~(LMEM_CACHE_LINE_SIZE - 1U);  /* Align address to cache line size */

    /* If the length exceeds 4KB, push all */
    if (length >= 4096U)
    {
        LMEM_DRV_CodeCachePushAll(instance);
    }
    /* Else proceed with multi-line push */
    else
    {
        while (addr < endAddr)
        {
            LMEM_DRV_CodeCachePushLine(instance, addr);
            addr = addr + LMEM_CACHE_LINE_SIZE;
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_CodeCacheClearLine
 * Description   : This function clears a specific line in the Processor Code bus cache.
 *
 * This function clears a specific line based on the physical address passed in
 * by the user.
 * Clear - Push a cache entry if it is valid and modified, then clear the valid and
 * modify bits. If entry not valid or not modified, clear the valid bit.
 *
 *END**************************************************************************/
void LMEM_DRV_CodeCacheClearLine(uint32_t instance, uint32_t addr)
{
    LMEM_Type *base = g_lmemBase[instance];

    /* Set the clear by line command */
    LMEM_HAL_SetCodeCacheLineCommand(base, kCacheLineClear);

    /* Since we're using the physical address, both ways are searched */
    LMEM_HAL_SetCodeCachePhysicalAddr(base, addr);

    LMEM_HAL_InitiateCodeCacheLineCommand(base);

    /* Set the line command to use the physical address */
    LMEM_BWR_PCCLCR_LADSEL(base, 1U);

    /* Wait until the cache command completes */
    while (LMEM_HAL_IsCodeCacheLineCommandActive(base)) { }

    /* No need to clear this command since future line commands will overwrite
     * the line command field
     */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_CodeCacheClearMultiLines
 * Description   : This function clears multiple lines in the Processor Code bus cache.
 *
 * This function clears multiple lines in the cache. The function clears the
 * lines in cache based on the physical address and length in bytes passed in by the
 * user.  If the function detects that the length meets or exceeds half the total amount of
 * cache, then the function shall perform an entire cache clear function (which is
 * more efficient than clearing the lines in the cache line-by-line).
 * The need to check half the total amount of cache is due to the fact that the cache consists of
 * two ways and that line commands based on the physical address will search both ways.
 * Clear - Push a cache entry if it is valid and modified, then clear the valid and
 * modify bits. If entry not valid or not modified, clear the valid bit.
 *
 *END**************************************************************************/
void LMEM_DRV_CodeCacheClearMultiLines(uint32_t instance, uint32_t addr, uint32_t length)
{
    uint32_t endAddr = addr + length;
    addr = addr & ~(LMEM_CACHE_LINE_SIZE - 1U);  /* Align address to cache line size */

    /* If the length exceeds 4KB, clear all */
    if (length >= 4096U)
    {
        LMEM_DRV_CodeCacheClearAll(instance);
    }
    /* Else proceed with multi-line clear */
    else
    {
        while (addr < endAddr)
        {
            LMEM_DRV_CodeCacheClearLine(instance, addr);
            addr = addr + LMEM_CACHE_LINE_SIZE;
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_CodeCacheDemoteRegion
 * Description   : This function demotes the cache mode of a region in Processor Code bus cache.
 *
 * This function allows the user to demote the cache mode of a region within the device's
 * memory map. Demoting the cache mode reduces the cache function applied to a memory
 * region from write-back to write-through to non-cacheable.  The function checks to see
 * if the requested cache mode is higher than or equal to the current cache mode, and if
 * so, will return an error. After a region is demoted, its cache mode can only be raised
 * by a reset, which returns it to its default state.
 * To maintain cache coherency, changes to the cache mode should be completed while the
 * address space being changed is not being accessed or the cache is disabled. Before a
 * cache mode change, this function completes a cache clear all command to push and invalidate any
 * cache entries that may have changed.
 *
 * @param region The desired region to demote of type lmem_cache_region_t
 * @param cacheMode The new, demoted cache mode of type lmem_cache_mode_t
 *
 * @return kStatus_LMEM_CACHE_Success The cache clear operation was successful, or
 *         kStatus_LMEM_CACHE_Busy The cache is busy performing another operation
 *         kStatus_LMEM_CACHE_Error The requested cache mode is higher than or equal to the
 *                                  current cache mode
 *
 *END**************************************************************************/
lmem_cache_status_t LMEM_DRV_CodeCacheDemoteRegion(uint32_t instance, lmem_cache_region_t region,
                                                   lmem_cache_mode_t cacheMode)
{
    LMEM_Type *base = g_lmemBase[instance];

    /* If the current cache mode is higher than the requested mode, return error */
    if ((uint32_t)cacheMode >= LMEM_HAL_GetCodeCacheRegionMode(base, region))
    {
        return kStatus_LMEM_CACHE_DemoteError;
    }
    /* Else, proceed to demote the region */
    else
    {
        LMEM_DRV_CodeCacheClearAll(instance);
        LMEM_HAL_SetCodeCacheRegionMode(base, region, cacheMode);
        return kStatus_LMEM_CACHE_Success;
    }
}

#if FSL_FEATURE_LMEM_HAS_SYSTEMBUS_CACHE

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_SystemCacheInvalidateAll
 * Description   : This function invalidates the entire Processor System bus cache.
 *
 * This function invalidates the entire cache meaning that it invalidates both Ways.
 * Invalidate - Unconditionally clear valid and modify bits of a cache entry
 *
 *END**************************************************************************/
void LMEM_DRV_SystemCacheInvalidateAll(uint32_t instance)
{
    LMEM_Type *base = g_lmemBase[instance];

    LMEM_HAL_SetSystemCacheInvalidateAllCmd(base, true);
    LMEM_HAL_InitiateSystemCacheCommand(base);

    /* Wait until the cache command completes */
    while (LMEM_HAL_IsSystemCacheCommandActive(base)) { }

    /* As a precaution clear the bits to avoid inadvertently re-running this command */
    LMEM_HAL_SetSystemCacheInvalidateAllCmd(base, false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_SystemCachePushAll
 * Description   : This function pushes all modified lines in the entire Processor System bus
 *        cache.
 *
 * This function pushes all modified lines in both Ways (the entire cache).
 * Push - Push a cache entry if it is valid and modified, then clear the modify bit. If
 * entry not valid or not modified, leave as is. This action does not clear the valid
 * bit. A cache push is synonymous with a cache flush.
 *
 *END**************************************************************************/
void LMEM_DRV_SystemCachePushAll(uint32_t instance)
{
    LMEM_Type *base = g_lmemBase[instance];

    LMEM_HAL_SetSystemCachePushAllCmd(base, true);
    LMEM_HAL_InitiateSystemCacheCommand(base);

    /* Wait until the cache command completes */
    while (LMEM_HAL_IsSystemCacheCommandActive(base)) { }

    /* As a precaution clear the bits to avoid inadvertently re-running this command */
    LMEM_HAL_SetSystemCachePushAllCmd(base, false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_SystemCacheClearAll
 * Description   : This function clears the entire Processor System bus cache.
 *
 * This function clears the entire cache, which is basically a push (flush) and
 * invalidate operation.
 * Clear - Push a cache entry if it is valid and modified, then clear the valid and
 * modify bits. If entry not valid or not modified, clear the valid bit.
 *
 *END**************************************************************************/
void LMEM_DRV_SystemCacheClearAll(uint32_t instance)
{
    LMEM_Type *base = g_lmemBase[instance];

    /* Push and invalidate all */
    LMEM_HAL_SetSystemCachePushAllCmd(base, true);
    LMEM_HAL_SetSystemCacheInvalidateAllCmd(base, true);
    LMEM_HAL_InitiateSystemCacheCommand(base);

    /* Wait until the cache command completes */
    while (LMEM_HAL_IsSystemCacheCommandActive(base)) { }

    /* As a precaution clear the bits to avoid inadvertently re-running this command */
    LMEM_HAL_SetSystemCachePushAllCmd(base, false);
    LMEM_HAL_SetSystemCacheInvalidateAllCmd(base, false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_SystemCacheEnable
 * Description   : This function enables the Processor System bus cache.
 *
 * This function enables the cache.  The function first invalidates the entire cache,
 * then it enables both the cache and write buffer.
 *
 *END**************************************************************************/
void LMEM_DRV_SystemCacheEnable(uint32_t instance)
{
    LMEM_Type *base = g_lmemBase[instance];

    /* First, invalidate the entire cache */
    LMEM_DRV_SystemCacheInvalidateAll(instance);

    /* Now enable the cache */
    LMEM_HAL_SetSystemCacheEnableCmd(base, true);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_SystemCacheDisable
 * Description   : This function disables the Processor System bus cache.
 *
 * This function disables the cache and write buffer.
 *
 *END**************************************************************************/
void LMEM_DRV_SystemCacheDisable(uint32_t instance)
{
    LMEM_Type *base = g_lmemBase[instance];

    /* First, push any modified contents */
    LMEM_DRV_SystemCachePushAll(instance);

    /* Now disable the cache */
    LMEM_HAL_SetSystemCacheEnableCmd(base, false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_SystemCacheInvalidateLine
 * Description   : This function invalidates a specific line in the Processor System bus cache.
 *
 * This function invalidates a specific line in the cache. The function invalidates a
 * line in cache based on the physical address passed in by the user.
 * Invalidate - Unconditionally clear valid and modify bits of a cache entry
 *
 *END**************************************************************************/
void LMEM_DRV_SystemCacheInvalidateLine(uint32_t instance, uint32_t addr)
{
    LMEM_Type *base = g_lmemBase[instance];

    /* Set the invalidate by line command */
    LMEM_HAL_SetSystemCacheLineCommand(base, kCacheLineInvalidate);

    /* Since we're using the physical address, both ways are searched */
    LMEM_HAL_SetSystemCachePhysicalAddr(base, addr);

    LMEM_HAL_InitiateSystemCacheLineCommand(base);

    /* Set the line command to use the physical address */
    LMEM_BWR_PSCLCR_LADSEL(base, 1U);

    /* Wait until the cache command completes */
    while (LMEM_HAL_IsSystemCacheLineCommandActive(base)) { }

    /* No need to clear this command since future line commands will overwrite
     * the line command field
     */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_SystemCacheInvalidateMultiLines
 * Description   : This function invalidates multiple lines in the Processor System bus cache.
 *
 * This function invalidates multiple lines in the cache. The function invalidates the
 * lines in cache based on the physical address and length in bytes passed in by the
 * user.  If the function detects that the length meets or exceeds half the total amount of
 * cache, then the function shall perform an entire cache invalidate function (which is
 * more efficient than invalidating the cache line-by-line).
 * The need to check half the total amount of cache is due to the fact that the cache consists of
 * two ways and that line commands based on the physical address will search both ways.
 * Invalidate - Unconditionally clear valid and modify bits of a cache entry
 *
 *END**************************************************************************/
void LMEM_DRV_SystemCacheInvalidateMultiLines(uint32_t instance, uint32_t addr, uint32_t length)
{
    uint32_t endAddr = addr + length;
    addr = addr & ~(LMEM_CACHE_LINE_SIZE - 1U);  /* Align address to cache line size */

    /* If the length exceeds 4KB, invalidate all */
    if (length >= 4096U)
    {
        LMEM_DRV_SystemCacheInvalidateAll(instance);
    }
    /* Else proceed with multi-line invalidate */
    else
    {
        while (addr < endAddr)
        {
            LMEM_DRV_SystemCacheInvalidateLine(instance, addr);
            addr = addr + LMEM_CACHE_LINE_SIZE;
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_SystemCachePushLine
 * Description   : This function pushes a specific modified line in the Processor System bus
 *                 cache.
 *
 * This function pushes a specific modified line based on the physical address passed in
 * by the user.
 * Push - Push a cache entry if it is valid and modified, then clear the modify bit. If
 * entry not valid or not modified, leave as is. This action does not clear the valid
 * bit. A cache push is synonymous with a cache flush.
 *
 *END**************************************************************************/
void LMEM_DRV_SystemCachePushLine(uint32_t instance, uint32_t addr)
{
    LMEM_Type *base = g_lmemBase[instance];

    /* Set the push by line command */
    LMEM_HAL_SetSystemCacheLineCommand(base, kCacheLinePush);

    /* Since we're using the physical address, both ways are searched */
    LMEM_HAL_SetSystemCachePhysicalAddr(base, addr);

    LMEM_HAL_InitiateSystemCacheLineCommand(base);

    /* Set the line command to use the physical address */
    LMEM_BWR_PSCLCR_LADSEL(base, 1U);

    /* Wait until the cache command completes */
    while (LMEM_HAL_IsSystemCacheLineCommandActive(base)) { }

    /* No need to clear this command since future line commands will overwrite
     * the line command field
     */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_SystemCachePushMultiLines
 * Description   : This function pushes multiple modified lines in the Processor System bus cache.
 *
 * This function pushes multiple modified lines in the cache. The function pushes the
 * lines in cache based on the physical address and length in bytes passed in by the
 * user.  If the function detects that the length meets or exceeds half the total amount of
 * cache, then the function shall perform an entire cache push function (which is
 * more efficient than pushing the modified lines in the cache line-by-line).
 * The need to check half the total amount of cache is due to the fact that the cache consists of
 * two ways and that line commands based on the physical address will search both ways.
 * Push - Push a cache entry if it is valid and modified, then clear the modify bit. If
 * entry not valid or not modified, leave as is. This action does not clear the valid
 * bit. A cache push is synonymous with a cache flush.
 *
 *END**************************************************************************/
void LMEM_DRV_SystemCachePushMultiLines(uint32_t instance, uint32_t addr, uint32_t length)
{
    uint32_t endAddr = addr + length;
    addr = addr & ~(LMEM_CACHE_LINE_SIZE - 1U);  /* Align address to cache line size */

    /* If the length exceeds 4KB, push all */
    if (length >= 4096U)
    {
        LMEM_DRV_SystemCachePushAll(instance);
    }
    /* Else proceed with multi-line push */
    else
    {
        while (addr < endAddr)
        {
            LMEM_DRV_SystemCachePushLine(instance, addr);
            addr = addr + LMEM_CACHE_LINE_SIZE;
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_SystemCacheClearLine
 * Description   : This function clears a specific line in the Processor System bus cache.
 *
 * This function clears a specific line based on the physical address passed in
 * by the user.
 * Clear - Push a cache entry if it is valid and modified, then clear the valid and
 * modify bits. If entry not valid or not modified, clear the valid bit.
 *
 *END**************************************************************************/
void LMEM_DRV_SystemCacheClearLine(uint32_t instance, uint32_t addr)
{
    LMEM_Type *base = g_lmemBase[instance];

    /* Set the clear by line command */
    LMEM_HAL_SetSystemCacheLineCommand(base, kCacheLineClear);

    /* Since we're using the physical address, both ways are searched */
    LMEM_HAL_SetSystemCachePhysicalAddr(base, addr);

    LMEM_HAL_InitiateSystemCacheLineCommand(base);

    /* Set the line command to use the physical address */
    LMEM_BWR_PSCLCR_LADSEL(base, 1U);

    /* Wait until the cache command completes */
    while (LMEM_HAL_IsSystemCacheLineCommandActive(base)) { }

    /* No need to clear this command since future line commands will overwrite
     * the line command field
     */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_SystemCacheClearMultiLines
 * Description   : This function clears multiple lines in the Processor System bus cache.
 *
 * This function clears multiple lines in the cache. The function clears the
 * lines in cache based on the physical address and length in bytes passed in by the
 * user.  If the function detects that the length meets or exceeds half the total amount of
 * cache, then the function shall perform an entire cache clear function (which is
 * more efficient than clearing the lines in the cache line-by-line).
 * The need to check half the total amount of cache is due to the fact that the cache consists of
 * two ways and that line commands based on the physical address will search both ways.
 * Clear - Push a cache entry if it is valid and modified, then clear the valid and
 * modify bits. If entry not valid or not modified, clear the valid bit.
 *
 *END**************************************************************************/
void LMEM_DRV_SystemCacheClearMultiLines(uint32_t instance, uint32_t addr, uint32_t length)
{
    uint32_t endAddr = addr + length;
    addr = addr & ~(LMEM_CACHE_LINE_SIZE - 1U);  /* Align address to cache line size */

    /* If the length exceeds 4KB, clear all */
    if (length >= 4096U)
    {
        LMEM_DRV_SystemCacheClearAll(instance);
    }
    /* Else proceed with multi-line clear */
    else
    {
        while (addr < endAddr)
        {
            LMEM_DRV_SystemCacheClearLine(instance, addr);
            addr = addr + LMEM_CACHE_LINE_SIZE;
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LMEM_DRV_SystemCacheDemoteRegion
 * Description   : This function demotes the cache mode of a region in Processor System bus cache.
 *
 * This function allows the user to demote the cache mode of a region within the device's
 * memory map. Demoting the cache mode reduces the cache function applied to a memory
 * region from write-back to write-through to non-cacheable.  The function checks to see
 * if the requested cache mode is higher than or equal to the current cache mode, and if
 * so, will return an error. After a region is demoted, its cache mode can only be raised
 * by a  reset, which returns it to its default state.
 * To maintain cache coherency, changes to the cache mode should be completed while the
 * address space being changed is not being accessed or the cache is disabled. Before a
 * cache mode change, this function completes a cache clear all command to push and invalidate any
 * cache entries that may have changed.
 *
 *END**************************************************************************/
lmem_cache_status_t LMEM_DRV_SystemCacheDemoteRegion(uint32_t instance, lmem_cache_region_t region,
                                                     lmem_cache_mode_t cacheMode)
{
    LMEM_Type *base = g_lmemBase[instance];

    /* If the current cache mode is higher than the requested mode, return error */
    if ((uint32_t)cacheMode >= LMEM_HAL_GetSystemCacheRegionMode(base, region))
    {
        return kStatus_LMEM_CACHE_DemoteError;
    }
    /* Else, proceed to demote the region */
    else
    {
        LMEM_DRV_SystemCacheClearAll(instance);
        LMEM_HAL_SetSystemCacheRegionMode(base, region, cacheMode);
        return kStatus_LMEM_CACHE_Success;
    }
}

#endif /* #if FSL_FEATURE_LMEM_HAS_SYSTEMBUS_CACHE */

#endif /* FSL_FEATURE_SOC_LMEM_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

