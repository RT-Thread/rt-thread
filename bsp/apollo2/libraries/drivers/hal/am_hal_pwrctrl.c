//*****************************************************************************
//
//  am_hal_pwrctrl.c
//! @file
//!
//! @brief Functions for enabling and disabling power domains.
//!
//! @addtogroup pwrctrl2 Power Control
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
//  ONE_BIT - true iff value has exactly 1 bit set.
//
//*****************************************************************************
#define ONE_BIT(ui32Value)   (ui32Value  &&  !(ui32Value & (ui32Value - 1)))

//*****************************************************************************
//
//  Determine if this is an Apollo2 revision that requires additional handling
//  of the BUCK to LDO transition when only the ADC is in use and going to
//  deepsleep.
//
//*****************************************************************************
static bool
isRev_ADC(void)
{
    return AM_BFM(MCUCTRL, CHIPREV, REVMAJ) == AM_REG_MCUCTRL_CHIPREV_REVMAJ_B ?
            true : false;
}

//*****************************************************************************
//
//! @brief Enable power for a peripheral.
//!
//! @param ui32Peripheral - The peripheral to enable
//!
//! This function directly enables or disables power for the chosen peripheral.
//!
//! @note Unpowered peripherals may lose their configuration information. This
//! function does not save or restore peripheral configuration registers.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_pwrctrl_periph_enable(uint32_t ui32Peripheral)
{

    am_hal_debug_assert_msg(ONE_BIT(ui32Peripheral),
                        "Cannot enable more than one peripheral at a time.");

    //
    // Begin critical section.
    //
    AM_CRITICAL_BEGIN_ASM

    //
    // Enable power control for the given device.
    //
    AM_REG(PWRCTRL, DEVICEEN) |= ui32Peripheral;

    //
    // End Critical Section.
    //
    AM_CRITICAL_END_ASM

    //
    // Wait for the power to stablize.  Using a simple delay loop is more
    // power efficient than a polling loop.
    //
    am_hal_flash_delay(AM_HAL_PWRCTRL_DEVICEEN_DELAYCYCLES / 3);

    //
    // Quick check to guarantee we're good (should never be more than 1 read).
    //
    POLL_PWRSTATUS(ui32Peripheral);
}

//*****************************************************************************
//
//! @brief Disable power for a peripheral.
//!
//! @param ui32Peripheral - The peripheral to disable
//!
//! This function directly disables or disables power for the chosen peripheral.
//!
//! @note Unpowered peripherals may lose their configuration information. This
//! function does not save or restore peripheral configuration registers.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_pwrctrl_periph_disable(uint32_t ui32Peripheral)
{

    am_hal_debug_assert_msg(ONE_BIT(ui32Peripheral),
                        "Cannot enable more than one peripheral at a time.");

    //
    // Begin critical section.
    //
    AM_CRITICAL_BEGIN_ASM

    //
    // Disable power control for the given device.
    //
    AM_REG(PWRCTRL, DEVICEEN) &= ~ui32Peripheral;

    //
    // End critical section.
    //
    AM_CRITICAL_END_ASM

    //
    // Wait for the power to stablize
    //
    am_hal_flash_delay(AM_HAL_PWRCTRL_DEVICEDIS_DELAYCYCLES / 3);
}

//*****************************************************************************
//
//! @brief Enable and disable power for memory devices (SRAM, flash, cache).
//!
//! @param ui32MemEn - The memory and amount to be enabled.
//!         Must be one of the following:
//!         AM_HAL_PWRCTRL_MEMEN_CACHE
//!         AM_HAL_PWRCTRL_MEMEN_CACHE_DIS
//!         AM_HAL_PWRCTRL_MEMEN_FLASH512K
//!         AM_HAL_PWRCTRL_MEMEN_FLASH1M
//!         AM_HAL_PWRCTRL_MEMEN_SRAM8K
//!         AM_HAL_PWRCTRL_MEMEN_SRAM16K
//!         AM_HAL_PWRCTRL_MEMEN_SRAM24K
//!         AM_HAL_PWRCTRL_MEMEN_SRAM32K
//!         AM_HAL_PWRCTRL_MEMEN_SRAM64K
//!         AM_HAL_PWRCTRL_MEMEN_SRAM96K
//!         AM_HAL_PWRCTRL_MEMEN_SRAM128K
//!         AM_HAL_PWRCTRL_MEMEN_SRAM160K
//!         AM_HAL_PWRCTRL_MEMEN_SRAM192K
//!         AM_HAL_PWRCTRL_MEMEN_SRAM224K
//!         AM_HAL_PWRCTRL_MEMEN_SRAM256K
//!         AM_HAL_PWRCTRL_MEMEN_ALL (the default, power-up state)
//!
//! This function enables/disables power to provide only the given amount of
//! the type of memory specified.
//!
//! Only the type of memory specified is affected. Therefore separate calls
//! are required to affect power settings for FLASH, SRAM, or CACHE.
//!
//! Settings for zero SRAM or FLASH are not provided as device behavior under
//! either of those conditions is undefined.
//!
//! @note Unpowered memory devices may lose their configuration information.
//! This function does not save or restore peripheral configuration registers.
//!
//! @return None.
//
//*****************************************************************************
bool
am_hal_pwrctrl_memory_enable(uint32_t ui32MemEn)
{
    uint32_t ui32MemEnMask, ui32MemDisMask;
    uint32_t ui32PwrStatEnMask, ui32PwrStatDisMask;
    int32_t i32TOcnt;

    if ( ui32MemEn == AM_HAL_PWRCTRL_MEMEN_FLASH512K )
    {
        ui32MemEnMask  = AM_REG_PWRCTRL_MEMEN_FLASH0_EN;
        ui32MemDisMask = AM_REG_PWRCTRL_MEMEN_FLASH1_EN;
        ui32PwrStatEnMask  = AM_REG_PWRCTRL_PWRONSTATUS_PD_FLAM0_M;
        ui32PwrStatDisMask = AM_REG_PWRCTRL_PWRONSTATUS_PD_FLAM1_M;
    }
    else if ( ui32MemEn == AM_HAL_PWRCTRL_MEMEN_FLASH1M )
    {
        ui32MemEnMask  = AM_REG_PWRCTRL_MEMEN_FLASH0_EN |
                         AM_REG_PWRCTRL_MEMEN_FLASH1_EN;
        ui32MemDisMask = 0;
        ui32PwrStatEnMask  = AM_REG_PWRCTRL_PWRONSTATUS_PD_FLAM0_M  |
                             AM_REG_PWRCTRL_PWRONSTATUS_PD_FLAM1_M;
        ui32PwrStatDisMask = 0;
    }
    else if ( ui32MemEn == AM_HAL_PWRCTRL_MEMEN_SRAM8K )
    {
        ui32MemEnMask  = AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM8K;
        ui32MemDisMask = AM_REG_PWRCTRL_MEMEN_SRAMEN_ALL    &
                         ~AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM8K;
        ui32PwrStatEnMask  = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_8K;
        ui32PwrStatDisMask = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_ALL    &
                             ~AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_8K;
    }
    else if ( ui32MemEn == AM_HAL_PWRCTRL_MEMEN_SRAM16K )
    {
        ui32MemEnMask  = AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM16K;
        ui32MemDisMask = AM_REG_PWRCTRL_MEMEN_SRAMEN_ALL    &
                         ~AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM16K;
        ui32PwrStatEnMask  = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_16K;
        ui32PwrStatDisMask = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_ALL    &
                             ~AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_16K;
    }
    else if ( ui32MemEn == AM_HAL_PWRCTRL_MEMEN_SRAM24K )
    {
        ui32MemEnMask  = AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP0_SRAM0       |
                         AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP0_SRAM1       |
                         AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP0_SRAM2;
        ui32MemDisMask = AM_REG_PWRCTRL_MEMEN_SRAMEN_ALL    &
                         ~(AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP0_SRAM0     |
                           AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP0_SRAM1     |
                           AM_REG_PWRCTRL_MEMEN_SRAMEN_GROUP0_SRAM2);
        ui32PwrStatEnMask  = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_24K;
        ui32PwrStatDisMask = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_ALL    &
                             ~AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_24K;
    }
    else if ( ui32MemEn == AM_HAL_PWRCTRL_MEMEN_SRAM32K )
    {
        ui32MemEnMask  = AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM32K;
        ui32MemDisMask = AM_REG_PWRCTRL_MEMEN_SRAMEN_ALL    &
                         ~AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM32K;
        ui32PwrStatEnMask  = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_32K;
        ui32PwrStatDisMask = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_ALL    &
                             ~AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_32K;
    }
    else if ( ui32MemEn == AM_HAL_PWRCTRL_MEMEN_SRAM64K )
    {
        ui32MemEnMask  = AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM64K;
        ui32MemDisMask = AM_REG_PWRCTRL_MEMEN_SRAMEN_ALL    &
                         ~AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM64K;
        ui32PwrStatEnMask  = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_64K;
        ui32PwrStatDisMask = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_ALL    &
                             ~AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_64K;
    }
    else if ( ui32MemEn == AM_HAL_PWRCTRL_MEMEN_SRAM96K )
    {
        ui32MemEnMask  = AM_HAL_PWRCTRL_MEMEN_SRAM96K;
        ui32MemDisMask = AM_REG_PWRCTRL_MEMEN_SRAMEN_ALL    &
                         ~AM_HAL_PWRCTRL_MEMEN_SRAM96K;
        ui32PwrStatEnMask  = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_96K;
        ui32PwrStatDisMask = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_ALL    &
                             ~AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_96K;
    }
    else if ( ui32MemEn == AM_HAL_PWRCTRL_MEMEN_SRAM128K )
    {
        ui32MemEnMask  = AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM128K;
        ui32MemDisMask = AM_REG_PWRCTRL_MEMEN_SRAMEN_ALL    &
                         ~AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM128K;
        ui32PwrStatEnMask  = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_128K;
        ui32PwrStatDisMask = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_ALL    &
                             ~AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_128K;
    }
    else if ( ui32MemEn == AM_HAL_PWRCTRL_MEMEN_SRAM160K )
    {
        ui32MemEnMask  = AM_HAL_PWRCTRL_MEMEN_SRAM160K;
        ui32MemDisMask = AM_REG_PWRCTRL_MEMEN_SRAMEN_ALL    &
                         ~AM_HAL_PWRCTRL_MEMEN_SRAM160K;
        ui32PwrStatEnMask  = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_160K;
        ui32PwrStatDisMask = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_ALL    &
                             ~AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_160K;
    }
    else if ( ui32MemEn == AM_HAL_PWRCTRL_MEMEN_SRAM192K )
    {
        ui32MemEnMask  = AM_HAL_PWRCTRL_MEMEN_SRAM192K;
        ui32MemDisMask = AM_REG_PWRCTRL_MEMEN_SRAMEN_ALL    &
                         ~AM_HAL_PWRCTRL_MEMEN_SRAM192K;
        ui32PwrStatEnMask  = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_192K;
        ui32PwrStatDisMask = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_ALL    &
                             ~AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_192K;
    }
    else if ( ui32MemEn == AM_HAL_PWRCTRL_MEMEN_SRAM224K )
    {
        ui32MemEnMask  = AM_HAL_PWRCTRL_MEMEN_SRAM224K;
        ui32MemDisMask = AM_REG_PWRCTRL_MEMEN_SRAMEN_ALL    &
                         ~AM_HAL_PWRCTRL_MEMEN_SRAM224K;
        ui32PwrStatEnMask  = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_224K;
        ui32PwrStatDisMask = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_ALL    &
                             ~AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_224K;
    }
    else if ( ui32MemEn == AM_HAL_PWRCTRL_MEMEN_SRAM256K )
    {
        ui32MemEnMask  = AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM256K;
        ui32MemDisMask = AM_REG_PWRCTRL_MEMEN_SRAMEN_ALL    &
                         ~AM_REG_PWRCTRL_MEMEN_SRAMEN_SRAM256K;
        ui32PwrStatEnMask  = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_256K;
        ui32PwrStatDisMask = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_ALL    &
                             ~AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_256K;
    }
    else if ( ui32MemEn == AM_HAL_PWRCTRL_MEMEN_CACHE )
    {
        ui32MemEnMask  = AM_REG_PWRCTRL_MEMEN_CACHEB0_EN    |
                         AM_REG_PWRCTRL_MEMEN_CACHEB2_EN;
        ui32MemDisMask = 0;
        ui32PwrStatEnMask  = AM_REG_PWRCTRL_PWRONSTATUS_PD_CACHEB2_M    |
                             AM_REG_PWRCTRL_PWRONSTATUS_PD_CACHEB0_M;
        ui32PwrStatDisMask = 0;
    }
    else if ( ui32MemEn == AM_HAL_PWRCTRL_MEMEN_CACHE_DIS )
    {
        ui32MemEnMask = 0;
        ui32MemDisMask  = AM_REG_PWRCTRL_MEMEN_CACHEB0_EN   |
                          AM_REG_PWRCTRL_MEMEN_CACHEB2_EN;
        ui32PwrStatEnMask  = 0;
        ui32PwrStatDisMask = AM_REG_PWRCTRL_PWRONSTATUS_PD_CACHEB2_M    |
                             AM_REG_PWRCTRL_PWRONSTATUS_PD_CACHEB0_M;
    }
    else if ( ui32MemEn == AM_HAL_PWRCTRL_MEMEN_ALL )
    {
        ui32MemEnMask  = AM_HAL_PWRCTRL_MEMEN_ALL;
        ui32MemDisMask = 0;
        ui32PwrStatEnMask  = AM_HAL_PWRCTRL_PWRONSTATUS_SRAM_ALL;
        ui32PwrStatDisMask = 0;
    }
    else
    {
        return false;
    }

    //
    // Disable unneeded memory. If nothing to be disabled, skip to save time.
    //
    // Note that a deliberate disable step using a disable mask is taken here
    // for 2 reasons: 1) To only affect the specified type of memory, and 2)
    // To avoid inadvertently disabling any memory currently being depended on.
    //
    if ( ui32MemDisMask != 0 )
    {
        AM_REG(PWRCTRL, MEMEN) &= ~ui32MemDisMask;
    }

    //
    // Enable the required memory.
    //
    if ( ui32MemEnMask != 0 )
    {
        AM_REG(PWRCTRL, MEMEN) |= ui32MemEnMask;
    }

    //
    // Wait for the power to be turned on.
    // Apollo2 note - these loops typically end up taking 1 iteration.
    //
    i32TOcnt = 200;
    if ( ui32PwrStatDisMask )
    {
        while ( --i32TOcnt              &&
                ( AM_REG(PWRCTRL, PWRONSTATUS) & ui32PwrStatDisMask ) );
    }

    if ( i32TOcnt <= 0 )
    {
        return false;
    }

    i32TOcnt = 200;
    if ( ui32PwrStatEnMask )
    {
        while ( --i32TOcnt              &&
            (( AM_REG(PWRCTRL, PWRONSTATUS) & ui32PwrStatEnMask )
                != ui32PwrStatEnMask) );
    }
    if ( i32TOcnt <= 0 )
    {
        return false;
    }

    return true;
}

//*****************************************************************************
//
//! @brief Initialize the core and memory buck converters.
//!
//! This function is intended to be used for first time core and memory buck
//! converters initialization.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_pwrctrl_bucks_init(void)
{
    am_hal_pwrctrl_bucks_enable();

    while ( ( AM_REG(PWRCTRL, POWERSTATUS) &
              ( AM_REG_PWRCTRL_POWERSTATUS_COREBUCKON_M |
                AM_REG_PWRCTRL_POWERSTATUS_MEMBUCKON_M ) )  !=
              ( AM_REG_PWRCTRL_POWERSTATUS_COREBUCKON_M |
                AM_REG_PWRCTRL_POWERSTATUS_MEMBUCKON_M ) );

    //
    // Additional delay to make sure BUCKs are initialized.
    //
    am_hal_flash_delay(200 / 3);
}

//*****************************************************************************
//
//! @brief Enable the core and memory buck converters.
//!
//! This function enables the core and memory buck converters.
//!
//! @return None
//
//*****************************************************************************
#define LDO_TRIM_REG_ADDR   (0x50023004)
#define BUCK_TRIM_REG_ADDR  (0x50023000)

void
am_hal_pwrctrl_bucks_enable(void)
{
    //
    // Check to see if the bucks are already on. If so, we can just return.
    //
    if ( AM_BFR(PWRCTRL, POWERSTATUS, COREBUCKON)   &&
         AM_BFR(PWRCTRL, POWERSTATUS, MEMBUCKON) )
    {
        return;
    }

    //
    // Enable BUCK power up
    //
    AM_BFW(PWRCTRL, SUPPLYSRC, COREBUCKEN, 1);
    AM_BFW(PWRCTRL, SUPPLYSRC, MEMBUCKEN, 1);

    //
    // Make sure bucks are ready.
    //
    while ( ( AM_REG(PWRCTRL, POWERSTATUS)                      &
              ( AM_REG_PWRCTRL_POWERSTATUS_COREBUCKON_M |
                AM_REG_PWRCTRL_POWERSTATUS_MEMBUCKON_M ) )  !=
              ( AM_REG_PWRCTRL_POWERSTATUS_COREBUCKON_M |
                AM_REG_PWRCTRL_POWERSTATUS_MEMBUCKON_M ) );
}

//*****************************************************************************
//
//! @brief Disable the core and memory buck converters.
//!
//! This function disables the core and memory buck converters.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_pwrctrl_bucks_disable(void)
{
    //
    // Check to see if the bucks are already off. If so, we can just return.
    //
    if ( AM_BFR(PWRCTRL, POWERSTATUS, COREBUCKON) == 0  &&
         AM_BFR(PWRCTRL, POWERSTATUS, MEMBUCKON) == 0)
    {
        return;
    }

    //
    // Handle the special case if only the ADC is powered.
    //
    if ( isRev_ADC()  &&
         (AM_REG(PWRCTRL, DEVICEEN) == AM_REG_PWRCTRL_DEVICEEN_ADC_EN) )
    {
            //
            // Set SUPPLYSRC to handle this case
            //
            AM_REG(PWRCTRL, SUPPLYSRC) &=
                (AM_REG_PWRCTRL_SUPPLYSRC_SWITCH_LDO_IN_SLEEP_EN    |
                 AM_REG_PWRCTRL_SUPPLYSRC_MEMBUCKEN_EN);
    }
    else
    {
        //
        // Power them down
        //
        AM_BFW(PWRCTRL, SUPPLYSRC, COREBUCKEN, 0);
        AM_BFW(PWRCTRL, SUPPLYSRC, MEMBUCKEN, 0);
    }

    //
    // Wait until BUCKs are disabled.
    //
    am_hal_flash_delay(AM_HAL_PWRCTRL_BUCKDIS_DELAYCYCLES / 3);
}

//*****************************************************************************
//
//! @brief Misc low power initializations.
//!
//! This function performs low power initializations that aren't specifically
//! handled elsewhere.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_pwrctrl_low_power_init(void)
{
    //
    // For lowest power, we enable clock gating for all SRAM configuration.
    //
    AM_REG(PWRCTRL, SRAMCTRL) |=
        AM_REG_PWRCTRL_SRAMCTRL_SRAM_MASTER_CLKGATE_EN  |
        AM_REG_PWRCTRL_SRAMCTRL_SRAM_CLKGATE_EN         |
        AM_REG_PWRCTRL_SRAMCTRL_SRAM_LIGHT_SLEEP_DIS;

    //
    // For lowest deep sleep power, make sure we stay in BUCK mode.
    //
    AM_REG(PWRCTRL, SUPPLYSRC) &=
        ~AM_REG_PWRCTRL_SUPPLYSRC_SWITCH_LDO_IN_SLEEP_M;
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
