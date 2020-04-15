//*****************************************************************************
//
//  am_hal_cachectrl.h
//! @file
//!
//! @brief Functions for accessing and configuring the CACHE controller.
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************
#ifndef AM_HAL_CACHECTRL_H
#define AM_HAL_CACHECTRL_H

//*****************************************************************************
//
// Cache configuration structure
//
//*****************************************************************************
typedef struct
{
    //
    //! Set to 1 to enable the cache.
    //
    uint8_t ui32EnableCache;

    //
    //! Set to 1 to enable the LRU cache replacement policy.
    //! Set to 0 to enable the LRR (least recently used) replacement policy.
    //! LEE minimizes writes to the TAG SRAM.
    //
    uint8_t ui32LRU;

    //
    //! Set to 3 to enable non-cachable region 1 and non-cachable region 0.
    //! Set to 2 to enable non-cachable region 1.
    //! Set to 1 to enable non-cachable region 0.
    //! Set to 0 to make all regions cacheable.
    //
    uint8_t ui32EnableNCregions;

    //
    //! Set to:
    //! AM_HAL_CACHECTRL_CACHECFG_CONFIG_DIRECT_256 for direct-mapped,
    //!     128-bit linesize, 256 entries (2 SRAMs active)
    //! AM_HAL_CACHECTRL_CACHECFG_CONFIG_2WAY_256 for two-way set associative,
    //!     128-bit linesize, 256 entries (4 SRAMs active)
    //! AM_HAL_CACHECTRL_CACHECFG_CONFIG_2WAY_512 for two-way set associative,
    //!     128-bit linesize, 512 entries (8 SRAMs active)
    //
    uint8_t ui32Config;

    //
    //! Set to 1 to enable serial cache mode.
    //
    uint8_t ui32SerialCacheMode;

    //
    //! Set to 3 to enable flash data caching and flash instruction caching.
    //! Set to 2 to enable flash data caching.
    //! Set to 1 to enable flash instruction caching.
    //! Set to 0 to disable flash data caching and flash instruction caching.
    //
    uint8_t ui32FlashCachingEnables;

    //
    //! Set to 1 to enable clock gating of cache RAMs.
    //
    uint8_t ui32EnableCacheClockGating;

    //
    //! Set to 1 to enable light sleep of cache RAMs.
    //
    uint8_t ui32EnableLightSleep;

    //
    //! Set Data RAM delay value (0x0 - 0xF).
    //
    uint8_t ui32Dly;

    //
    //! Set SM Data RAM delay value (0x0 - 0xF).
    //
    uint8_t ui32SMDly;

    //
    //! Set to 1 to enable clock gating of the entire data array.
    //
    uint8_t ui32EnableDataClockGating;

    //
    //! Set to 1 to enable cache monitor statistics.
    //
    uint8_t ui32EnableCacheMonitoring;
}
am_hal_cachectrl_config_t;

extern const am_hal_cachectrl_config_t am_hal_cachectrl_defaults;

//*****************************************************************************
//
//! @name Cache enables
//! @brief Configuration selection for the various cache enables.
//!
//! These macros may be used in conjunction with the
//!  am_hal_cachectrl_cache_enable() function to enable various cache features.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_CACHECTRL_CACHECFG_ENABLE                AM_REG_CACHECTRL_CACHECFG_ENABLE_M
#define AM_HAL_CACHECTRL_CACHECFG_LRU_ENABLE            AM_REG_CACHECTRL_CACHECFG_LRU_M
#define AM_HAL_CACHECTRL_CACHECFG_NC0_ENABLE            AM_REG_CACHECTRL_CACHECFG_ENABLE_NC0_M
#define AM_HAL_CACHECTRL_CACHECFG_NC1_ENABLE            AM_REG_CACHECTRL_CACHECFG_ENABLE_NC1_M
#define AM_HAL_CACHECTRL_CACHECFG_SERIAL_ENABLE         AM_REG_CACHECTRL_CACHECFG_SERIAL_M
#define AM_HAL_CACHECTRL_CACHECFG_ICACHE_ENABLE         AM_REG_CACHECTRL_CACHECFG_ICACHE_ENABLE_M
#define AM_HAL_CACHECTRL_CACHECFG_DCACHE_ENABLE         AM_REG_CACHECTRL_CACHECFG_DCACHE_ENABLE_M
#define AM_HAL_CACHECTRL_CACHECFG_CACHE_CLKGATE_ENABLE  AM_REG_CACHECTRL_CACHECFG_CACHE_CLKGATE_M
#define AM_HAL_CACHECTRL_CACHECFG_LS_ENABLE             AM_REG_CACHECTRL_CACHECFG_CACHE_LS_M
#define AM_HAL_CACHECTRL_CACHECFG_DATA_CLKGATE_ENABLE   AM_REG_CACHECTRL_CACHECFG_DATA_CLKGATE_M
#define AM_HAL_CACHECTRL_CACHECFG_MONITOR_ENABLE        AM_REG_CACHECTRL_CACHECFG_ENABLE_MONITOR_M
//! @}

//*****************************************************************************
//
//! @name Cache Config
//! @brief Configuration selection for the cache.
//!
//! These macros may be used in conjunction with the
//!  am_hal_cachectrl_cache_config() function to select the cache type.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_CACHECTRL_CACHECFG_CONFIG_DIRECT_256 AM_REG_CACHECTRL_CACHECFG_CONFIG_W1_128B_256E
#define AM_HAL_CACHECTRL_CACHECFG_CONFIG_2WAY_256   AM_REG_CACHECTRL_CACHECFG_CONFIG_W2_128B_256E
#define AM_HAL_CACHECTRL_CACHECFG_CONFIG_2WAY_512   AM_REG_CACHECTRL_CACHECFG_CONFIG_W2_128B_512E
//! @}

//*****************************************************************************
//
// Default cache settings
//
//*****************************************************************************
#define AM_HAL_CACHECTRL_DEFAULTS                                             \
    (AM_HAL_CACHECTRL_CACHECFG_ICACHE_ENABLE |                                \
     AM_HAL_CACHECTRL_CACHECFG_DCACHE_ENABLE |                                \
     AM_HAL_CACHECTRL_CACHECFG_CACHE_CLKGATE_ENABLE |                         \
     AM_HAL_CACHECTRL_CACHECFG_DATA_CLKGATE_ENABLE |                          \
     AM_HAL_CACHECTRL_CACHECFG_CONFIG_2WAY_512)

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// External function definitions
//
//*****************************************************************************
extern void am_hal_cachectrl_enable(const am_hal_cachectrl_config_t *psConfig);
extern void am_hal_cachectrl_disable(void);
extern void am_hal_cachectrl_config_default(void);
extern void am_hal_cachectrl_config(am_hal_cachectrl_config_t *psConfig);
extern uint32_t am_hal_cachectrl_cache_enables(uint32_t u32EnableMask,
                                               uint32_t u32DisableMask);
extern void am_hal_cachectrl_cache_config(uint32_t ui32CacheConfig);
extern void am_hal_cachectrl_invalidate_flash_cache(void);
extern void am_hal_cachectrl_reset_statistics(void);
extern uint32_t am_hal_cachectrl_sleep_mode_status(void);
extern uint32_t am_hal_cachectrl_sleep_mode_enable(uint32_t ui32EnableMask,
                                                   uint32_t ui32DisableMask);

#ifdef __cplusplus
}
#endif

#endif // AM_HAL_CACHECTRL_H
