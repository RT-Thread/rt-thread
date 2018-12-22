//*****************************************************************************
//
//  am_hal_cachectrl.c
//! @file
//!
//! @brief Functions for interfacing with the CACHE controller.
//!
//! @addtogroup clkgen2 Clock Generator (CACHE)
//! @ingroup apollo2hal
//! @{
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

#include <stdint.h>
#include <stdbool.h>
#include "am_mcu_apollo.h"

//*****************************************************************************
//
// Default settings for the cache.
//
//*****************************************************************************
const am_hal_cachectrl_config_t am_hal_cachectrl_defaults =
{
    1, // ui32EnableCache
    0, // ui32LRU
    0, // ui32EnableNCregions
    AM_HAL_CACHECTRL_CACHECFG_CONFIG_2WAY_512, // ui32Config
    0, // ui32SerialCacheMode
    3, // ui32FlashCachingEnables
    1, // ui32EnableCacheClockGating
    0, // ui32EnableLightSleep
    1, // ui32Dly
    1, // ui32SMDly
    1, // ui32EnableDataClockGating
    0, // ui32EnableCacheMonitoring
};

//*****************************************************************************
//
//! @brief Enable the cache using the supplied settings
//!
//! @param psConfig - pointer to a config structure containing cache settings.
//!
//! This function takes in a structure of cache settings, and uses them to
//! enable the cache. This function will take care of the necessary register
//! writes both in this module and in the power control module, so a separate
//! powerctrl call is not necessary.
//!
//! For most applications, the default cache settings will be the most
//! efficient choice. To use the default cache settings with this function, use
//! the address of the global am_hal_cachectrl_defaults structure as the
//! psConfig argument.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_cachectrl_enable(const am_hal_cachectrl_config_t *psConfig)
{
    uint32_t ui32ConfigValue;
    uint32_t ui32Timeout;

    //
    // Pull the configuration data from the structure, and prepare to write the
    // cache configuration register.
    //
    // NOTE: ICACHE and DCACHE settings were left out from this step. This is a
    // workaround for a timing issue with early versions of Apollo2 that caused
    // the cache to incorrectly mark itself valid during the startup sequence.
    // The workaround calls for us to start the cache, manually invalidate it,
    // and then enable ICACHE and DCACHE operation.
    //
    ui32ConfigValue = (AM_REG_CACHECTRL_CACHECFG_ENABLE( 1 )                                                |
                       AM_REG_CACHECTRL_CACHECFG_LRU( psConfig->ui32LRU )                                   |
                       AM_REG_CACHECTRL_CACHECFG_ENABLE_NC0( (psConfig->ui32EnableNCregions & 0x1) >> 0 )   |
                       AM_REG_CACHECTRL_CACHECFG_ENABLE_NC1( (psConfig->ui32EnableNCregions & 0x2) >> 1 )   |
                       psConfig->ui32Config                                                                 |
                       AM_REG_CACHECTRL_CACHECFG_SERIAL(psConfig->ui32SerialCacheMode)                      |
                       AM_REG_CACHECTRL_CACHECFG_CACHE_CLKGATE( psConfig->ui32EnableCacheClockGating )      |
                       AM_REG_CACHECTRL_CACHECFG_CACHE_LS(psConfig->ui32EnableLightSleep )                  |
                       AM_REG_CACHECTRL_CACHECFG_DLY( psConfig->ui32Dly )                                   |
                       AM_REG_CACHECTRL_CACHECFG_SMDLY( psConfig->ui32SMDly )                               |
                       AM_REG_CACHECTRL_CACHECFG_DATA_CLKGATE(psConfig->ui32EnableDataClockGating)          |
                       AM_REG_CACHECTRL_CACHECFG_ENABLE_MONITOR(psConfig->ui32EnableCacheMonitoring) );

    //
    // Make sure the cache is enabled in the power control block.
    //
    am_hal_pwrctrl_memory_enable(AM_HAL_PWRCTRL_MEMEN_CACHE);

    //
    // Set the initial cache settings.
    //
    AM_REG(CACHECTRL, CACHECFG) = ui32ConfigValue;

    //
    // Wait for the cache ready signal.
    //
    for (ui32Timeout = 0; ui32Timeout < 50; ui32Timeout++)
    {
        if (AM_BFM(CACHECTRL, CACHECTRL, CACHE_READY))
        {
            break;
        }
    }

    //
    // Manually invalidate the cache (workaround for the issue described above.)
    //
    AM_BFW(CACHECTRL, CACHECTRL, INVALIDATE, 1);

    //
    // Wait for the cache ready signal again.
    //
    for (ui32Timeout = 0; ui32Timeout < 50; ui32Timeout++)
    {
        if (AM_BFM(CACHECTRL, CACHECTRL, CACHE_READY))
        {
            break;
        }
    }

    //
    // Now that the cache is running, and correctly marked invalid, we can OR in
    // the ICACHE and DCACHE settings.
    //
    ui32ConfigValue |= (AM_REG_CACHECTRL_CACHECFG_ICACHE_ENABLE( (psConfig->ui32FlashCachingEnables & 0x1) >> 0 )   |
                        AM_REG_CACHECTRL_CACHECFG_DCACHE_ENABLE( (psConfig->ui32FlashCachingEnables & 0x2) >> 1 ) );

    //
    // Write the final configuration settings to the CACHECTRL register.
    //
    AM_REG(CACHECTRL, CACHECFG) = ui32ConfigValue;
}

//*****************************************************************************
//
//! @brief Disable the cache.
//!
//! Call this function to completely shut down cache features.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_cachectrl_disable(void)
{
    uint32_t ui32CacheCfg;

    //
    // Save the cache settings.
    //
    ui32CacheCfg = AM_REG(CACHECTRL, CACHECFG);

    //
    // Remove the ICACHE and DCACHE settings.
    //
    ui32CacheCfg &= (AM_REG_CACHECTRL_CACHECFG_DCACHE_ENABLE(0) |
                     AM_REG_CACHECTRL_CACHECFG_ICACHE_ENABLE(0));

    //
    // Write the resulting value back to the register.
    //
    AM_REG(CACHECTRL, CACHECFG) = ui32CacheCfg;

    //
    // Read the CACHECTRL register a few times
    //
    AM_REG(CACHECTRL, CACHECTRL);
    AM_REG(CACHECTRL, CACHECTRL);
    AM_REG(CACHECTRL, CACHECTRL);

    //
    // Disable the cache completely.
    //
    AM_BFW(CACHECTRL, CACHECFG, ENABLE, 0);

    //
    // Power the cache down in the powerctrl block.
    //
    am_hal_pwrctrl_memory_enable(AM_HAL_PWRCTRL_MEMEN_CACHE_DIS);
}

//*****************************************************************************
//
//! @brief Set a default cache configuration.
//!
//! This function is used to set a default cache configuration.
//
//*****************************************************************************
void
am_hal_cachectrl_config_default(void)
{
    //
    // Set PWRCTRL
    //
    am_hal_pwrctrl_memory_enable(AM_HAL_PWRCTRL_MEMEN_CACHE);

    //
    // Write a default configuration to the CACHECFG register.
    //
    AM_REG(CACHECTRL, CACHECFG) =                                   \
        AM_REG_CACHECTRL_CACHECFG_ENABLE( 1 )                   |   \
        AM_REG_CACHECTRL_CACHECFG_LRU( 0 )                      |   \
        AM_REG_CACHECTRL_CACHECFG_ENABLE_NC0( 0 )               |   \
        AM_REG_CACHECTRL_CACHECFG_ENABLE_NC1( 0 )               |   \
        AM_REG_CACHECTRL_CACHECFG_CONFIG_W2_128B_512E           |   \
        AM_REG_CACHECTRL_CACHECFG_SERIAL( 0 )                   |   \
        AM_REG_CACHECTRL_CACHECFG_ICACHE_ENABLE( 1 )            |   \
        AM_REG_CACHECTRL_CACHECFG_DCACHE_ENABLE( 1 )            |   \
        AM_REG_CACHECTRL_CACHECFG_CACHE_CLKGATE( 1 )            |   \
        AM_REG_CACHECTRL_CACHECFG_CACHE_LS( 0 )                 |   \
        AM_REG_CACHECTRL_CACHECFG_DLY( 1 )                      |   \
        AM_REG_CACHECTRL_CACHECFG_SMDLY( 1 )                    |   \
        AM_REG_CACHECTRL_CACHECFG_DATA_CLKGATE( 1 )             |   \
        AM_REG_CACHECTRL_CACHECFG_ENABLE_MONITOR( 0 );

    //
    // Write a default configuration to the FLASHCFG register.
    //
    AM_REG(CACHECTRL, FLASHCFG) = AM_REG_CACHECTRL_FLASHCFG_RD_WAIT(1);

    //
    // Write a default configuration to the CACHECTRL register.
    //
    AM_REG(CACHECTRL, CACHECTRL) =                                  \
        AM_REG_CACHECTRL_CACHECTRL_FLASH1_SLM_ENABLE(1)         |   \
        AM_REG_CACHECTRL_CACHECTRL_FLASH1_SLM_DISABLE(0)        |   \
        AM_REG_CACHECTRL_CACHECTRL_FLASH0_SLM_ENABLE(1)         |   \
        AM_REG_CACHECTRL_CACHECTRL_FLASH0_SLM_DISABLE(0)        |   \
        AM_REG_CACHECTRL_CACHECTRL_RESET_STAT(0)                |   \
        AM_REG_CACHECTRL_CACHECTRL_INVALIDATE(0);

    //
    // Write a default configuration to the NCR0START and NCR0END registers.
    //
    AM_REG(CACHECTRL, NCR0START) =                          \
        AM_REG_CACHECTRL_NCR0START_ADDR(0);
    AM_REG(CACHECTRL, NCR0END) =                            \
        AM_REG_CACHECTRL_NCR0END_ADDR(0);

    //
    // Write a default configuration to the NCR1START and NCR1END registers.
    //
    AM_REG(CACHECTRL, NCR1START) =                          \
        AM_REG_CACHECTRL_NCR1START_ADDR(0);
    AM_REG(CACHECTRL, NCR1END) =                            \
        AM_REG_CACHECTRL_NCR1END_ADDR(0);

    //
    // Write a default configuration to the DMONn and IMONn registers.
    //
    AM_REG(CACHECTRL, DMON0) =                                      \
        AM_REG_CACHECTRL_DMON0_DACCESS_COUNT(0);
    AM_REG(CACHECTRL, DMON1)  =                                     \
        AM_REG_CACHECTRL_DMON1_DLOOKUP_COUNT(0);
    AM_REG(CACHECTRL, DMON2)  =                                     \
        AM_REG_CACHECTRL_DMON2_DHIT_COUNT(0);
    AM_REG(CACHECTRL, DMON3)  =                                     \
        AM_REG_CACHECTRL_DMON3_DLINE_COUNT(0);
    AM_REG(CACHECTRL, IMON0)  =                                     \
        AM_REG_CACHECTRL_IMON0_IACCESS_COUNT(0);
    AM_REG(CACHECTRL, IMON1)  =                                     \
        AM_REG_CACHECTRL_IMON1_ILOOKUP_COUNT(0);
    AM_REG(CACHECTRL, IMON2)  =                                     \
        AM_REG_CACHECTRL_IMON2_IHIT_COUNT(0);
    AM_REG(CACHECTRL, IMON3)  =                                     \
        AM_REG_CACHECTRL_IMON3_ILINE_COUNT(0);
}

//*****************************************************************************
//
//! @brief Enable the flash cache controller via a configuration structure.
//!
//! @param psConfig - Pointer to a data structure containing all of the data
//      necessary to configure the CACHECFG register.
//!
//! This function is used to configure all fields of the CACHECFG.
//
//*****************************************************************************
void
am_hal_cachectrl_config(am_hal_cachectrl_config_t *psConfig)
{
    uint32_t u32ConfigValue;

    //
    // Arrange all of the members of the data structure into a single u32 that
    //  can be written to the register.
    //
    u32ConfigValue =
        AM_REG_CACHECTRL_CACHECFG_ENABLE( psConfig->ui32EnableCache )       |
        AM_REG_CACHECTRL_CACHECFG_LRU( psConfig->ui32LRU )                  |
        AM_REG_CACHECTRL_CACHECFG_ENABLE_NC0(
            (psConfig->ui32EnableNCregions & 0x1) >> 0 )                    |
        AM_REG_CACHECTRL_CACHECFG_ENABLE_NC1(
            (psConfig->ui32EnableNCregions & 0x2) >> 1 )                    |
        psConfig->ui32Config                                                |
        AM_REG_CACHECTRL_CACHECFG_SERIAL(psConfig->ui32SerialCacheMode)     |
        AM_REG_CACHECTRL_CACHECFG_ICACHE_ENABLE(
            (psConfig->ui32FlashCachingEnables & 0x1) >> 0 )                |
        AM_REG_CACHECTRL_CACHECFG_DCACHE_ENABLE(
            (psConfig->ui32FlashCachingEnables & 0x2) >> 1 )                |
        AM_REG_CACHECTRL_CACHECFG_CACHE_CLKGATE(
            psConfig->ui32EnableCacheClockGating )                          |
        AM_REG_CACHECTRL_CACHECFG_CACHE_LS(
            psConfig->ui32EnableLightSleep )                                |
        AM_REG_CACHECTRL_CACHECFG_DLY( psConfig->ui32Dly )                  |
        AM_REG_CACHECTRL_CACHECFG_SMDLY( psConfig->ui32SMDly )              |
        AM_REG_CACHECTRL_CACHECFG_DATA_CLKGATE(
            psConfig->ui32EnableDataClockGating )                           |
        AM_REG_CACHECTRL_CACHECFG_ENABLE_MONITOR(
            psConfig->ui32EnableCacheMonitoring );

    //
    // Write the configuration value to the CACHECFG register.
    //
    AM_REG(CACHECTRL, CACHECFG) = u32ConfigValue;
}

//*****************************************************************************
//
//! @brief Configure the various flash cache controller enables.
//!
//! @param u32EnableMask  - Mask of features to be enabled.
//! @param u32DisableMask - Mask of features to be disabled.
//!
//! This function is used to enable or disable the various flash cache
//! controller configuration enables which consist of the following:
//!     AM_HAL_CACHECTRL_CACHECFG_ENABLE                Flash cache controller
//!     AM_HAL_CACHECTRL_CACHECFG_LRU_ENABLE            LRU (disabled = LRR)
//!     AM_HAL_CACHECTRL_CACHECFG_NC0_ENABLE            Non-cacheable region 0
//!     AM_HAL_CACHECTRL_CACHECFG_NC1_ENABLE            Non-cacheable region 1
//!     AM_HAL_CACHECTRL_CACHECFG_SERIAL_ENABLE         Serial cache mode
//!     AM_HAL_CACHECTRL_CACHECFG_ICACHE_ENABLE         Instruction caching
//!     AM_HAL_CACHECTRL_CACHECFG_DCACHE_ENABLE         Data caching.
//!     AM_HAL_CACHECTRL_CACHECFG_CACHE_CLKGATE_ENABLE  Cache clock gating
//!     AM_HAL_CACHECTRL_CACHECFG_LS_ENABLE             Light sleep cache RAMs
//!     AM_HAL_CACHECTRL_CACHECFG_DATA_CLKGATE_ENABLE   Data clock gating
//!     AM_HAL_CACHECTRL_CACHECFG_MONITOR_ENABLE        Cache Monitoring Stats
//!
//! Note that if both an enable and disable are provided in their respective
//! masks, the enable will take precendence.
//!
//! @return The previous status of the flash cache controller enables.
//
//*****************************************************************************
#define CACHECTRL_VALID_ENABLES                         (   \
        AM_REG_CACHECTRL_CACHECFG_ENABLE_M              |   \
        AM_REG_CACHECTRL_CACHECFG_LRU_M                 |   \
        AM_REG_CACHECTRL_CACHECFG_ENABLE_NC0_M          |   \
        AM_REG_CACHECTRL_CACHECFG_ENABLE_NC1_M          |   \
        AM_REG_CACHECTRL_CACHECFG_SERIAL_M              |   \
        AM_REG_CACHECTRL_CACHECFG_ICACHE_ENABLE_M       |   \
        AM_REG_CACHECTRL_CACHECFG_DCACHE_ENABLE_M       |   \
        AM_REG_CACHECTRL_CACHECFG_CACHE_CLKGATE_M       |   \
        AM_REG_CACHECTRL_CACHECFG_CACHE_LS_M            |   \
        AM_REG_CACHECTRL_CACHECFG_DATA_CLKGATE_M        |   \
        AM_REG_CACHECTRL_CACHECFG_ENABLE_MONITOR_M )

uint32_t
am_hal_cachectrl_cache_enables(uint32_t u32EnableMask, uint32_t u32DisableMask)
{
    uint32_t ui32RetVal = AM_BFR(CACHECTRL, CACHECFG, ENABLE) &
                          CACHECTRL_VALID_ENABLES;

    //
    // Make sure the enable masks include only valid bits.
    //
    u32EnableMask  &= CACHECTRL_VALID_ENABLES;
    u32DisableMask &= CACHECTRL_VALID_ENABLES;

    //
    // First, do the disables.
    //
    AM_REG(CACHECTRL, CACHECFG) &= ~u32DisableMask;

    //
    // Now set the enables.
    //
    AM_REG(CACHECTRL, CACHECFG) |= u32EnableMask;

    return ui32RetVal;
}

//*****************************************************************************
//
//! @brief Select the cache configuration type.
//!
//! This functions only sets the CACHECFG CONFIG field.
//!
//! @param ui32CacheConfig - The cache configuration value.
//!
//! This function can be used to select the type of cache.frequency of the main
//! system clock.  The ui32CacheConfig parameter should be set to one of the
//! following values:
//!
//!     AM_HAL_CACHECTRL_CACHECFG_CONFIG_DIRECT_256 : Direct mapped,
//!         128-bit linesize, 256 entries (2 SRAMs active).
//!     AM_HAL_CACHECTRL_CACHECFG_CONFIG_2WAY_256   : Two-way set associative,
//!         128-bit linesize, 256 entries (4 SRAMs active).
//!     AM_HAL_CACHECTRL_CACHECFG_CONFIG_2WAY_512   : Two-way set associative,
//!         128-bit linesize, 512 entries (8 SRAMs active).
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_cachectrl_cache_config(uint32_t ui32CacheConfig)
{
    //
    // Clear the bitfield
    //
    AM_REG(CACHECTRL, CACHECFG) &= ~AM_REG_CACHECTRL_CACHECFG_CONFIG_M;

    //
    // Write the new value to the bitfield.
    //
    AM_REG(CACHECTRL, CACHECFG) |= ui32CacheConfig &
                                   AM_REG_CACHECTRL_CACHECFG_CONFIG_M;
}

//*****************************************************************************
//
//! @brief Invalidate the flash cache.
//!
//! This function is used to invalidate the flash cache.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_cachectrl_invalidate_flash_cache(void)
{
    //
    // Write the bit to invalidate the flash cache.
    // Note - this bit is not sticky, no need to write it back to 0.
    //
    AM_REG(CACHECTRL, CACHECTRL) |= AM_REG_CACHECTRL_CACHECTRL_INVALIDATE_GO;
}

//*****************************************************************************
//
//! @brief Reset cache statistics.
//!
//! This function is used to reset cache statistics.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_cachectrl_reset_statistics(void)
{
    //
    // Write the bit to reset flash statistics.
    // Note - this bit is not sticky, no need to write it back to 0.
    //
    AM_REG(CACHECTRL, CACHECTRL) |= AM_REG_CACHECTRL_CACHECTRL_RESET_STAT_CLEAR;
}

//*****************************************************************************
//
//! @brief Get flash cache sleep mode status.
//!
//! This function returns flash cache sleep mode statuses.
//!
//! @return
//!     bit0 indicates that flash0 flash sleep mode is enabled.
//!     bit1 indicates that flash1 flash sleep mode is enabled.
//
//*****************************************************************************
uint32_t
am_hal_cachectrl_sleep_mode_status(void)
{
    uint32_t ui32Status, ui32Ret;

    //
    // Get the current sleep mode status bits.
    //
    ui32Status = AM_REG(CACHECTRL, CACHECTRL);
    ui32Ret = (ui32Status &                                                 \
                AM_REG_CACHECTRL_CACHECTRL_FLASH0_SLM_STATUS_M) >>          \
                (AM_REG_CACHECTRL_CACHECTRL_FLASH0_SLM_STATUS_S - 0);
    ui32Ret |= (ui32Status &                                                \
                AM_REG_CACHECTRL_CACHECTRL_FLASH1_SLM_STATUS_M) >>          \
                (AM_REG_CACHECTRL_CACHECTRL_FLASH1_SLM_STATUS_S - 1);

    return ui32Ret;
}

//*****************************************************************************
//
//! @brief Enable or disable flash cache sleep mode.
//!
//! This function enables or disables flash cache sleep mode.
//! @param ui32EnableMask  - bit0 for flash0, bit1 for flash1.
//! @param ui32DisableMask - bit0 for flash0, bit1 for flash1.
//!
//! Note that if both an enable and disable are provided in their respective
//! masks, the enable will take precedence.
//!
//! @return Previous status.
//!     bit0 indicates that flash0 flash sleep mode was previously enabled.
//!     bit1 indicates that flash1 flash sleep mode was previously enabled.
//
//*****************************************************************************
uint32_t
am_hal_cachectrl_sleep_mode_enable(uint32_t ui32EnableMask,
                                   uint32_t ui32DisableMask)
{
    uint32_t ui32Ret = am_hal_cachectrl_sleep_mode_status();

    if ( ui32DisableMask & 0x1 )
    {
        AM_REG(CACHECTRL, CACHECTRL) |= AM_REG_CACHECTRL_CACHECTRL_FLASH0_SLM_DISABLE_M;
    }

    if ( ui32DisableMask & 0x2 )
    {
        AM_REG(CACHECTRL, CACHECTRL) |= AM_REG_CACHECTRL_CACHECTRL_FLASH1_SLM_DISABLE_M;
    }

    if ( ui32EnableMask & 0x1 )
    {
        AM_REG(CACHECTRL, CACHECTRL) |= AM_REG_CACHECTRL_CACHECTRL_FLASH0_SLM_ENABLE_M;
    }

    if ( ui32EnableMask & 0x2 )
    {
        AM_REG(CACHECTRL, CACHECTRL) |= AM_REG_CACHECTRL_CACHECTRL_FLASH1_SLM_ENABLE_M;
    }

    return ui32Ret;
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
