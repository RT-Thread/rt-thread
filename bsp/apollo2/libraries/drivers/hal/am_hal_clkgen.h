//*****************************************************************************
//
//  am_hal_clkgen.h
//! @file
//!
//! @brief Functions for accessing and configuring the CLKGEN.
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
#ifndef AM_HAL_CLKGEN_H
#define AM_HAL_CLKGEN_H

//*****************************************************************************
//
//! @name System Clock max frequency
//! @brief Defines the maximum clock frequency for this device.
//!
//! These macros provide a definition of the maximum clock frequency.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_CLKGEN_FREQ_MAX_HZ       48000000
#define AM_HAL_CLKGEN_FREQ_MAX_MHZ      (AM_HAL_CLKGEN_FREQ_MAX_HZ / 1000000)
//! @}

//*****************************************************************************
//
//! @name System Clock Selection
//! @brief Divisor selection for the main system clock.
//!
//! These macros may be used along with the am_hal_clkgen_sysctl_select()
//! function to select the frequency of the main system clock.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_CLKGEN_SYSCLK_MAX        AM_REG_CLKGEN_CCTRL_CORESEL_HFRC
#define AM_HAL_CLKGEN_SYSCLK_48MHZ      AM_REG_CLKGEN_CCTRL_CORESEL_HFRC
//! @}

//*****************************************************************************
//
//! @name Interrupt Status Bits
//! @brief Interrupt Status Bits for enable/disble use
//!
//! These macros may be used to set and clear interrupt bits.
//! @{
//
//*****************************************************************************
#define AM_HAL_CLKGEN_INT_ALM           AM_REG_CLKGEN_INTEN_ALM_M
#define AM_HAL_CLKGEN_INT_OF            AM_REG_CLKGEN_INTEN_OF_M
#define AM_HAL_CLKGEN_INT_ACC           AM_REG_CLKGEN_INTEN_ACC_M
#define AM_HAL_CLKGEN_INT_ACF           AM_REG_CLKGEN_INTEN_ACF_M
//! @}

//*****************************************************************************
//
//! @name OSC Start and Stop
//! @brief OSC Start and Stop defines.
//!
//! OSC Start and Stop defines to be used with \e am_hal_clkgen_osc_x().
//! @{
//
//*****************************************************************************
#define AM_HAL_CLKGEN_OSC_LFRC          AM_REG_CLKGEN_OCTRL_STOPRC_M
#define AM_HAL_CLKGEN_OSC_XT            AM_REG_CLKGEN_OCTRL_STOPXT_M
//! @}

//*****************************************************************************
//
// OSC Start, Stop, Select defines
//
//*****************************************************************************
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_LFRC         AM_REG_CLKGEN_CLKOUT_CKSEL_LFRC
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_XT_DIV2      AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV2
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_XT_DIV4      AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV4
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_XT_DIV8      AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV8
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_XT_DIV16     AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV16
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_XT_DIV32     AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV32
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_RTC_100Hz    AM_REG_CLKGEN_CLKOUT_CKSEL_RTC_100Hz
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_XT_DIV2M     AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV2M
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_XT           AM_REG_CLKGEN_CLKOUT_CKSEL_XT
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_CG_100Hz     AM_REG_CLKGEN_CLKOUT_CKSEL_CG_100Hz
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_HFRC         AM_REG_CLKGEN_CLKOUT_CKSEL_HFRC
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_HFRC_DIV4    AM_REG_CLKGEN_CLKOUT_CKSEL_HFRC_DIV4
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_HFRC_DIV8    AM_REG_CLKGEN_CLKOUT_CKSEL_HFRC_DIV8
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_HFRC_DIV32   AM_REG_CLKGEN_CLKOUT_CKSEL_HFRC_DIV32
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_HFRC_DIV64   AM_REG_CLKGEN_CLKOUT_CKSEL_HFRC_DIV64
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_HFRC_DIV128  AM_REG_CLKGEN_CLKOUT_CKSEL_HFRC_DIV128
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_HFRC_DIV256  AM_REG_CLKGEN_CLKOUT_CKSEL_HFRC_DIV256
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_CORE_CLK     AM_REG_CLKGEN_CLKOUT_CKSEL_CORE_CLK
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_FLASH_CLK    AM_REG_CLKGEN_CLKOUT_CKSEL_FLASH_CLK
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_LFRC_DIV2    AM_REG_CLKGEN_CLKOUT_CKSEL_LFRC_DIV2
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_LFRC_DIV32   AM_REG_CLKGEN_CLKOUT_CKSEL_LFRC_DIV32
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_LFRC_DIV512  AM_REG_CLKGEN_CLKOUT_CKSEL_LFRC_DIV512
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_LFRC_DIV32K  AM_REG_CLKGEN_CLKOUT_CKSEL_LFRC_DIV32K
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_XT_DIV256    AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV256
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_XT_DIV8K     AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV8K
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_XT_DIV64K    AM_REG_CLKGEN_CLKOUT_CKSEL_XT_DIV64K
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_ULFRC_DIV16  AM_REG_CLKGEN_CLKOUT_CKSEL_ULFRC_DIV16
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_ULFRC_DIV128 AM_REG_CLKGEN_CLKOUT_CKSEL_ULFRC_DIV128
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_ULFRC_1Hz    AM_REG_CLKGEN_CLKOUT_CKSEL_ULFRC_1Hz
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_ULFRC_DIV4K  AM_REG_CLKGEN_CLKOUT_CKSEL_ULFRC_DIV4K
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_ULFRC_DIV1M  AM_REG_CLKGEN_CLKOUT_CKSEL_ULFRC_DIV1M
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_HFRC_DIV64K  AM_REG_CLKGEN_CLKOUT_CKSEL_HFRC_DIV64K
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_HFRC_DIV16M  AM_REG_CLKGEN_CLKOUT_CKSEL_HFRC_DIV16M
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_LFRC_DIV2M   AM_REG_CLKGEN_CLKOUT_CKSEL_LFRC_DIV2M
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_HFRCNE       AM_REG_CLKGEN_CLKOUT_CKSEL_HFRCNE
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_HFRCNE_DIV8  AM_REG_CLKGEN_CLKOUT_CKSEL_HFRCNE_DIV8
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_CORE_CLKNE   AM_REG_CLKGEN_CLKOUT_CKSEL_CORE_CLKNE
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_XTNE         AM_REG_CLKGEN_CLKOUT_CKSEL_XTNE
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_XTNE_DIV16   AM_REG_CLKGEN_CLKOUT_CKSEL_XTNE_DIV16
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_LFRCNE_DIV32 AM_REG_CLKGEN_CLKOUT_CKSEL_LFRCNE_DIV32
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_FCLKNE       AM_REG_CLKGEN_CLKOUT_CKSEL_FCLKNE
#define AM_HAL_CLKGEN_CLKOUT_CKSEL_LFRCNE       AM_REG_CLKGEN_CLKOUT_CKSEL_LFRCNE

//*****************************************************************************
//
// UARTEN
//
//*****************************************************************************
#define AM_HAL_CLKGEN_UARTEN_DIS          AM_REG_CLKGEN_UARTEN_UART0EN_DIS
#define AM_HAL_CLKGEN_UARTEN_EN           AM_REG_CLKGEN_UARTEN_UART0EN_EN
#define AM_HAL_CLKGEN_UARTEN_REDUCE_FREQ  AM_REG_CLKGEN_UARTEN_UART0EN_REDUCE_FREQ
#define AM_HAL_CLKGEN_UARTEN_EN_POWER_SAV AM_REG_CLKGEN_UARTEN_UART0EN_EN_POWER_SAV

#define AM_HAL_CLKGEN_UARTEN_UARTENn_S(module)                                  \
        ((module) *                                                             \
        (AM_REG_CLKGEN_UARTEN_UART1EN_S - AM_REG_CLKGEN_UARTEN_UART0EN_S))

#define AM_HAL_CLKGEN_UARTEN_UARTENn_M(module)                                  \
        (AM_REG_CLKGEN_UARTEN_UART0EN_M << AM_HAL_CLKGEN_UARTEN_UARTENn_S(module))

//
// UARTEN: entype is one of DIS, EN, REDUCE_FREQ, EN_POWER_SAV.
//
#define AM_HAL_CLKGEN_UARTEN_UARTENn(module, entype)                            \
        (AM_REG_CLKGEN_UARTEN_UART0EN_##entype <<                               \
         AM_HAL_CLKGEN_UARTEN_UARTENn_S(module))

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// External function definitions
//
//*****************************************************************************
extern void am_hal_clkgen_sysclk_select(uint32_t ui32ClockSetting);
extern uint32_t am_hal_clkgen_sysclk_get(void);
extern void am_hal_clkgen_osc_start(uint32_t ui32OscFlags);
extern void am_hal_clkgen_osc_stop(uint32_t ui32OscFlags);
extern void am_hal_clkgen_clkout_enable(uint32_t ui32Signal);
extern void am_hal_clkgen_clkout_disable(void);
extern void am_hal_clkgen_uarten_set(uint32_t ui32Module, uint32_t ui32UartEn);
extern void am_hal_clkgen_int_enable(uint32_t ui32Interrupt);
extern uint32_t am_hal_clkgen_int_enable_get(void);
extern void am_hal_clkgen_int_disable(uint32_t ui32Interrupt);
extern void am_hal_clkgen_int_clear(uint32_t ui32Interrupt);
extern void am_hal_clkgen_int_set(uint32_t ui32Interrupt);
extern uint32_t am_hal_clkgen_int_status_get(bool bEnabledOnly);
extern void am_hal_clkgen_hfrc_adjust_enable(uint32_t ui32Warmup, uint32_t ui32Frequency);
extern void am_hal_clkgen_hfrc_adjust_disable(void);

#ifdef __cplusplus
}
#endif

#endif // AM_HAL_CLKGEN_H
