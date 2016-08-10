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
#if !defined(__FSL_LMEM_CACHE_HAL_H__)
#define __FSL_LMEM_CACHE_HAL_H__

#include "fsl_device_registers.h"
#include <stdint.h>
#include <stdbool.h>

#if FSL_FEATURE_SOC_LMEM_COUNT

/*!
 * @addtogroup local_memory_controller_cache_hal
 * @{
 */

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Error codes for the LMEM CACHE driver. */
typedef enum _lmem_cache_status
{
    kStatus_LMEM_CACHE_Success = 0,
    kStatus_LMEM_CACHE_Busy,        /*!< CACHE busy performing an operation*/
    kStatus_LMEM_CACHE_DemoteError, /*!< CACHE region demotion error */
    kStatus_LMEM_CACHE_Error,       /*!< CACHE driver error */
} lmem_cache_status_t;

/*! @brief LMEM CACHE mode options. */
typedef enum _lmem_cache_mode {
    kCacheNonCacheable     = 0x0U, /*!< CACHE mode: non-cacheable */
    kCacheWriteThrough     = 0x2U, /*!< CACHE mode: write-through */
    kCacheWriteBack        = 0x3U, /*!< CACHE mode: write-back */
} lmem_cache_mode_t;

/*! @brief LMEM CACHE Regions. */
typedef enum _lmem_cache_region {
    kCacheRegion0   = 0U,   /*!< Cache Region 0 */
    kCacheRegion1   = 1U,   /*!< Cache Region 1 */
    kCacheRegion2   = 2U,   /*!< Cache Region 2 */
    kCacheRegion3   = 3U,   /*!< Cache Region 3 */
    kCacheRegion4   = 4U,   /*!< Cache Region 4 */
    kCacheRegion5   = 5U,   /*!< Cache Region 5 */
    kCacheRegion6   = 6U,   /*!< Cache Region 6 */
    kCacheRegion7   = 7U,   /*!< Cache Region 7 */
    kCacheRegion8   = 8U,   /*!< Cache Region 8 */
    kCacheRegion9   = 9U,   /*!< Cache Region 9 */
    kCacheRegion10  = 10U,  /*!< Cache Region 10 */
    kCacheRegion11  = 11U,  /*!< Cache Region 11 */
    kCacheRegion12  = 12U,  /*!< Cache Region 12 */
    kCacheRegion13  = 13U,  /*!< Cache Region 13 */
    kCacheRegion14  = 14U,  /*!< Cache Region 14 */
    kCacheRegion15  = 15U   /*!< Cache Region 15 */
} lmem_cache_region_t;

/*! @brief LMEM CACHE line command. */
typedef enum _lmem_cache_way {
    kCacheLineSearchReadOrWrite  = 0U,   /*!< Cache line search and read or write */
    kCacheLineInvalidate         = 1U,   /*!< Cache line invalidate */
    kCacheLinePush               = 2U,   /*!< Cache line push */
    kCacheLineClear              = 3U,   /*!< Cache line clear */
} lmem_cache_line_command_t;

/*! @brief LMEM CACHE Line Size in bytes. */
#define LMEM_CACHE_LINE_SIZE    0x10  /*!< Cache line is 32 bytes (or 4-words) */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Processor Code Bus Cache Control
 *@{
 */

/*!
 * @brief Enables or disables the Processor Code bus cache and write buffer.
 *
 * This function enables or disables the Processor Code bus cache and write buffer.
 *
 * @param base Module base pointer of type LMEM_Type.
 * @param enable Enable (true) or disable (false) the Processor Code bus cache and write buffer
 */
static inline void LMEM_HAL_SetCodeCacheEnableCmd(LMEM_Type * base, bool enable)
{
    LMEM_BWR_PCCCR_ENCACHE(base, (enable == true));
    LMEM_BWR_PCCCR_ENWRBUF(base, (enable == true));
}

/*!
 * @brief Enable or disable the Processor Code bus option to invalidate all lines.
 *
 * This function enables or disables the Processor Code bus option to invalidate all
 * lines in both WAYs.
 *
 * @param base Module base pointer of type LMEM_Type.
 * @param enable Enable (true) or disable (false) the Processor Code bus option to
 *               invalidate all lines
 */
void LMEM_HAL_SetCodeCacheInvalidateAllCmd(LMEM_Type * base, bool enable);

/*!
 * @brief Enable or disable the Processor Code bus option to push all modified lines.
 *
 * This function enables or disables the Processor Code bus option to push all modified
 * lines to both WAYs.
 *
 * @param base Module base pointer of type LMEM_Type.
 * @param enable Enable (true) or disable (false) the Processor Code bus option to push
                 all modified lines
 */
void LMEM_HAL_SetCodeCachePushAllCmd(LMEM_Type * base, bool enable);

/*!
 * @brief Enable or disable the Processor Code bus option to push and invalidate all modified
 *        lines.
 *
 * This function enables or disables the Processor Code bus option to push and invalidate all
 * modified lines.
 *
 * @param base Module base pointer of type LMEM_Type.
 * @param enable Enable (true) or disable (false) the Processor Code bus option to push
                 all modified lines
 */
void LMEM_HAL_SetCodeCacheClearAllCmd(LMEM_Type * base, bool enable);

/*!
 * @brief Initiate the Processor Code bus cache command.
 *
 * This function initiates the Processor Code bus cache command to execute
 * an invalidate command and/or push command.
 *
 * @param base Module base pointer of type LMEM_Type.
 */
static inline void LMEM_HAL_InitiateCodeCacheCommand(LMEM_Type * base)
{
    LMEM_BWR_PCCCR_GO(base, true);
}

/*!
 * @brief Returns whether or not the Processor Code bus cache command is in progress.
 *
 * This function returns the state of the Processor Code bus cache command. The
 * command is either active (in progress) or idle.
 *
 * @param base Module base pointer of type LMEM_Type.
 * @return True if the cache command is in progress or false if the command is idle
 */
static inline bool LMEM_HAL_IsCodeCacheCommandActive(LMEM_Type * base)
{
    return (bool)LMEM_RD_PCCCR_GO(base);
}


/*!
 * @brief Initiate the Processor Code bus cache line command.
 *
 * This function initiates the Processor Code bus cache line command to execute
 * a search and read or write command, an invalidate command, a push command, or
 * a clear command.
 *
 * @param base Module base pointer of type LMEM_Type.
 */
static inline void LMEM_HAL_InitiateCodeCacheLineCommand(LMEM_Type * base)
{
    LMEM_BWR_PCCLCR_LGO(base, true);
}


/*!
 * @brief Returns whether or not the Processor Code bus cache line command is in
 *        progress.
 *
 * This function returns the state of the Processor Code bus cache line command. The
 * command is either active (in progress) or idle.
 *
 * @param base Module base pointer of type LMEM_Type.
 * @return True if the cache line command is in progress or false if the command is idle
 */
static inline bool LMEM_HAL_IsCodeCacheLineCommandActive(LMEM_Type * base)
{
    return (bool)LMEM_RD_PCCLCR_LGO(base);
}

/*!
 * @brief Sets the cache line command for the Processor Code bus.
 *
 * This function sets the cache line command for the Processor Code bus. The
 * command can be search and read or write, invalidate, push, or clear.
 *
 * @param base Module base pointer of type LMEM_Type.
 * @param command The cache line command of type lmem_cache_line_command_t
 */
static inline void LMEM_HAL_SetCodeCacheLineCommand(LMEM_Type * base,
                                                    lmem_cache_line_command_t command)
{
    LMEM_BWR_PCCLCR_LCMD(base, command);
}

/*!
 * @brief Sets the physical address for cache line commands for the Processor
 *        Code bus.
 *
 * This function sets the physical address for cache line commands for the Processor
 * Code bus. The commands are specified in the CLCR[LADSEL] bits.
 *
 * @param base Module base pointer of type LMEM_Type.
 * @param addr The physical address for cache line commands
 */
static inline void LMEM_HAL_SetCodeCachePhysicalAddr(LMEM_Type * base, uint32_t addr)
{
    LMEM_WR_PCCSAR(base, (addr & LMEM_PCCSAR_PHYADDR_MASK));
}

/*!
 * @brief Sets the cache mode for a specific region for the Processor
 *        Code bus.
 *
 * This function sets the cache mode for a specific region for the Processor
 * Code bus. Note that you can only demote the cache mode.
 *
 * @param base Module base pointer of type LMEM_Type.
 * @param region The region to demote the cache mode of type lmem_cache_region_t
 * @param cacheMode The specified demoted cache mode of type lmem_cache_mode_t
 */
void LMEM_HAL_SetCodeCacheRegionMode(LMEM_Type * base, lmem_cache_region_t region,
                                     lmem_cache_mode_t cacheMode);

/*!
 * @brief Gets the current cache mode for a specific region for the Processor
 *        Code bus.
 *
 * This function gets the current cache mode for a specific region for the Processor
 * Code bus.
 *
 * @param base Module base pointer of type LMEM_Type.
 * @param region The region to obtain the cache mode of type lmem_cache_region_t
 * @return The current cache mode for the specified region
 */
uint32_t LMEM_HAL_GetCodeCacheRegionMode(LMEM_Type * base, lmem_cache_region_t region);

/*@}*/

#if FSL_FEATURE_LMEM_HAS_SYSTEMBUS_CACHE
/*!
 * @name Processor System Bus Cache Control
 *@{
 */

/*!
 * @brief Enables or disables the Processor System bus cache and write buffer.
 *
 * This function enables or disables the Processor System bus cache and write buffer.
 *
 * @param base Module base pointer of type LMEM_Type.
 * @param enable Enable (true) or disable (false) the Processor Code bus cache and write buffer
 */
static inline void LMEM_HAL_SetSystemCacheEnableCmd(LMEM_Type * base, bool enable)
{
    LMEM_BWR_PSCCR_ENCACHE(base, (enable == true));
    LMEM_BWR_PSCCR_ENWRBUF(base, (enable == true));
}

/*!
 * @brief Enable or disable the Processor System bus option to invalidate all lines.
 *
 * This function enables or disables the Processor System bus option to invalidate all
 * lines in both WAYs.
 *
 * @param base Module base pointer of type LMEM_Type.
 * @param enable Enable (true) or disable (false) the Processor System bus option to
 *               invalidate all lines
 */
void LMEM_HAL_SetSystemCacheInvalidateAllCmd(LMEM_Type * base, bool enable);

/*!
 * @brief Enable or disable the Processor System bus option to push all modified lines.
 *
 * This function enables or disables the Processor System bus option to push all
 * modified lines to both WAYs.
 *
 * @param base Module base pointer of type LMEM_Type.
 * @param enable Enable (true) or disable (false) the Processor System bus option to
 *               push all modified lines
 */
void LMEM_HAL_SetSystemCachePushAllCmd(LMEM_Type * base, bool enable);

/*!
 * @brief Enable or disable the Processor System bus option to push and invalidate all modified
 *        lines.
 *
 * This function enables or disables the Processor System bus option to push and invalidate all
 * modified lines to both WAYs.
 *
 * @param base Module base pointer of type LMEM_Type.
 * @param enable Enable (true) or disable (false) the Processor System bus option to
 *               push all modified lines
 */
void LMEM_HAL_SetSystemCacheClearAllCmd(LMEM_Type * base, bool enable);

/*!
 * @brief Initiate the Processor System bus cache command.
 *
 * This function initiates the Processor System bus cache command to execute
 * an invalidate command and/or push command.
 *
 * @param base Module base pointer of type LMEM_Type.
 */
static inline void LMEM_HAL_InitiateSystemCacheCommand(LMEM_Type * base)
{
    LMEM_BWR_PSCCR_GO(base, true);
}

/*!
 * @brief Returns whether or not the Processor System bus cache command is in progress.
 *
 * This function returns the state of the Processor System bus cache command. The
 * command is either active (in progress) or idle.
 *
 * @param base Module base pointer of type LMEM_Type.
 * @return True if the cache command is in progress or false if the command is idle
 */
static inline bool LMEM_HAL_IsSystemCacheCommandActive(LMEM_Type * base)
{
    return (bool)LMEM_RD_PSCCR_GO(base);
}

/*!
 * @brief Initiate the Processor System bus cache line command.
 *
 * This function initiates the Processor System bus cache command to execute
 * a search and read or write command, an invalidate command, a push command, or
 * a clear command.
 *
 * @param base Module base pointer of type LMEM_Type.
 */
static inline void LMEM_HAL_InitiateSystemCacheLineCommand(LMEM_Type * base)
{
    LMEM_BWR_PSCLCR_LGO(base, true);
}

/*!
 * @brief Returns whether or not the Processor System bus cache line command is in
 *        progress.
 *
 * This function returns the state of the Processor System bus cache line command. The
 * command is either active (in progress) or idle.
 *
 * @param base Module base pointer of type LMEM_Type.
 * @return True if the cache line command is in progress or false if the command is idle
 */
static inline bool LMEM_HAL_IsSystemCacheLineCommandActive(LMEM_Type * base)
{
    return (bool)LMEM_RD_PSCLCR_LGO(base);
}

/*!
 * @brief Sets the cache line command for the Processor System bus.
 *
 * This function sets the cache line command for the Processor System bus. The
 * command can be search and read or write, invalidate, push, or clear.
 *
 * @param base Module base pointer of type LMEM_Type.
 * @param command The cache line command of type lmem_cache_line_command_t
 */
static inline void LMEM_HAL_SetSystemCacheLineCommand(LMEM_Type * base,
                                                      lmem_cache_line_command_t command)
{
    LMEM_BWR_PSCLCR_LCMD(base, command);
}

/*!
 * @brief Sets the physical address for cache line commands for the Processor
 *        System bus.
 *
 * This function sets the physical address for cache line commands for the Processor
 * System bus. The commands are specified in the CLCR[LADSEL] bits.
 *
 * @param base Module base pointer of type LMEM_Type.
 * @param addr The physical address for cache line commands
 */
static inline void LMEM_HAL_SetSystemCachePhysicalAddr(LMEM_Type * base, uint32_t addr)
{
    LMEM_WR_PSCSAR(base, (addr & LMEM_PSCSAR_PHYADDR_MASK));
}

/*!
 * @brief Sets the cache mode for a specific region for the Processor
 *        System bus.
 *
 * This function sets the cache mode for a specific region for the Processor
 * System bus. Note that you can only demote the cache mode.
 *
 * @param base Module base pointer of type LMEM_Type.
 * @param region The region to demote the cache mode of type lmem_cache_region_t
 * @param cacheMode The specified demoted cache mode of type lmem_cache_mode_t
 */
void LMEM_HAL_SetSystemCacheRegionMode(LMEM_Type * base, lmem_cache_region_t region,
                                       lmem_cache_mode_t cacheMode);

/*!
 * @brief Gets the current cache mode for a specific region for the Processor
 *        System bus.
 *
 * This function gets the current cache mode for a specific region for the Processor
 * System bus.
 *
 * @param base Module base pointer of type LMEM_Type.
 * @param region The region to obtain the cache mode of type lmem_cache_region_t
 * @return The current cache mode for the specified region
 */
uint32_t LMEM_HAL_GetSystemCacheRegionMode(LMEM_Type * base, lmem_cache_region_t region);

/*@}*/
#endif /* #if FSL_FEATURE_LMEM_HAS_SYSTEMBUS_CACHE */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_FEATURE_SOC_LMEM_COUNT */
#endif /* __FSL_LMEM_CACHE_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/


