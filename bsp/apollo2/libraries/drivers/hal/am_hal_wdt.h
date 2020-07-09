//*****************************************************************************
//
//  am_hal_wdt.h
//! @file
//!
//! @brief Hardware abstraction layer for the Watchdog Timer module.
//!
//! @addtogroup wdt2 Watchdog Timer (WDT)
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
#ifndef AM_HAL_WDT_H
#define AM_HAL_WDT_H

#include <stdint.h>
#include <stdbool.h>

//*****************************************************************************
//
// Macro definitions
//
//*****************************************************************************

//*****************************************************************************
//
//! @name WDT Clock Divider Selections.
//! @brief Macro definitions for WDT clock frequencies.
//!
//! These macros may be used with the am_hal_wdt_config_t structure to set the
//! clock frequency of the watch dog timer.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_WDT_LFRC_CLK_DEFAULT AM_REG_WDT_CFG_CLKSEL_128HZ
#define AM_HAL_WDT_LFRC_CLK_128HZ   AM_REG_WDT_CFG_CLKSEL_128HZ
#define AM_HAL_WDT_LFRC_CLK_16HZ    AM_REG_WDT_CFG_CLKSEL_16HZ
#define AM_HAL_WDT_LFRC_CLK_1HZ     AM_REG_WDT_CFG_CLKSEL_1HZ
#define AM_HAL_WDT_LFRC_CLK_1_16HZ  AM_REG_WDT_CFG_CLKSEL_1_16HZ
#define AM_HAL_WDT_LFRC_CLK_OFF     AM_REG_WDT_CFG_CLKSEL_OFF
//! @}

//*****************************************************************************
//
//! @name WDT Enable Reset in the WDT Configuration.
//! @brief Macro definitions for WDT Reset Enable.
//!
//! These macros may be used with the am_hal_wdt_config_t structure to enable
//! the watch dog timer to generate resets to the chip.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_WDT_ENABLE_RESET      AM_REG_WDT_CFG_RESEN(1)
#define AM_HAL_WDT_DISABLE_RESET     AM_REG_WDT_CFG_RESEN(0)
//! @}

//*****************************************************************************
//
//! @name WDT Enable Interrupt Generation from the WDT Configuration.
//! @brief Macro definitions for WDT Interrupt Enable.
//!
//! These macros may be used with the am_hal_wdt_config_t structure to enable
//! the watch dog timer to generate generate WDT interrupts.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_WDT_ENABLE_INTERRUPT      AM_REG_WDT_CFG_INTEN(1)
#define AM_HAL_WDT_DISABLE_INTERRUPT     AM_REG_WDT_CFG_INTEN(0)
//! @}

//*****************************************************************************
//
//! @brief Watchdog timer configuration structure.
//!
//! This structure is made to be used with the am_hal_wdt_init() function. It
//! describes the configuration of the watchdog timer.
//
//*****************************************************************************
typedef struct
{
    //! Configuration Values for watchdog timer
    //! event is generated.
    uint32_t ui32Config;

    //! Number of watchdog timer ticks allowed before a watchdog interrupt
    //! event is generated.
    uint16_t ui16InterruptCount;

    //! Number of watchdog timer ticks allowed before the watchdog will issue a
    //! system reset.
    uint16_t ui16ResetCount;

}
am_hal_wdt_config_t;


//*****************************************************************************
//
//! @brief Restarts the watchdog timer ("Pets" the dog)
//!
//! This function restarts the watchdog timer from the beginning, preventing
//! any interrupt or reset even from occuring until the next time the watchdog
//! timer expires.
//!
//! @return None.
//
//*****************************************************************************
#define am_hal_wdt_restart()                                                  \
    do                                                                        \
    {                                                                         \
        AM_REGn(WDT, 0, RSTRT) = AM_REG_WDT_RSTRT_RSTRT_KEYVALUE;             \
        (void)AM_REGn(WDT, 0, RSTRT);                                         \
    }                                                                         \
    while(0)

#ifdef __cplusplus
extern "C"
{
#endif
//*****************************************************************************
//
// External function definitions
//
//*****************************************************************************
extern void am_hal_wdt_init(const am_hal_wdt_config_t *psConfig);
extern void am_hal_wdt_start(void);
extern void am_hal_wdt_halt(void);
extern void am_hal_wdt_lock_and_start(void);
extern void am_hal_wdt_int_enable(void);
extern uint32_t am_hal_wdt_int_enable_get(void);
extern void am_hal_wdt_int_disable(void);
extern void am_hal_wdt_int_clear(void);
extern void am_hal_wdt_int_set(void);
extern uint32_t am_hal_wdt_int_status_get(bool bEnabledOnly);
#ifdef __cplusplus
}
#endif

#endif // AM_HAL_WDT_H

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
