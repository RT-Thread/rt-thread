//*****************************************************************************
//
//  am_hal_stimer.h
//! @file
//!
//! @brief Functions for accessing and configuring the STIMER.
//!
//! @addtogroup stimer2 Counter/Timer (STIMER)
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
#ifndef AM_HAL_STIMER_H
#define AM_HAL_STIMER_H

//
// Compute address of a given COMPARE or CAPTURE register.
// Note - For Apollo2, the parameter n should be 0 (as only 1 stimer module
//        exists) and the parameter r should be 0-7 (compare) or 0-3 (capture).
//
#define AM_REG_STIMER_COMPARE(n, r) (AM_REG_CTIMERn(n) +                \
                                     AM_REG_CTIMER_SCMPR0_O + (r * 4))

#define AM_REG_STIMER_CAPTURE(n, r) (AM_REG_CTIMERn(n) +                \
                                     AM_REG_CTIMER_SCAPT0_O + (r * 4))

//*****************************************************************************
//
//! @name Interrupt Status Bits
//! @brief Interrupt Status Bits for enable/disble use
//!
//! These macros may be used to set and clear interrupt bits
//! @{
//
//*****************************************************************************
#define AM_HAL_STIMER_INT_COMPAREA         AM_REG_CTIMER_STMINTSTAT_COMPAREA_M
#define AM_HAL_STIMER_INT_COMPAREB         AM_REG_CTIMER_STMINTSTAT_COMPAREB_M
#define AM_HAL_STIMER_INT_COMPAREC         AM_REG_CTIMER_STMINTSTAT_COMPAREC_M
#define AM_HAL_STIMER_INT_COMPARED         AM_REG_CTIMER_STMINTSTAT_COMPARED_M
#define AM_HAL_STIMER_INT_COMPAREE         AM_REG_CTIMER_STMINTSTAT_COMPAREE_M
#define AM_HAL_STIMER_INT_COMPAREF         AM_REG_CTIMER_STMINTSTAT_COMPAREF_M
#define AM_HAL_STIMER_INT_COMPAREG         AM_REG_CTIMER_STMINTSTAT_COMPAREG_M
#define AM_HAL_STIMER_INT_COMPAREH         AM_REG_CTIMER_STMINTSTAT_COMPAREH_M

#define AM_HAL_STIMER_INT_OVERFLOW         AM_REG_CTIMER_STMINTSTAT_OVERFLOW_M

#define AM_HAL_STIMER_INT_CAPTUREA         AM_REG_CTIMER_STMINTSTAT_CAPTUREA_M
#define AM_HAL_STIMER_INT_CAPTUREB         AM_REG_CTIMER_STMINTSTAT_CAPTUREB_M
#define AM_HAL_STIMER_INT_CAPTUREC         AM_REG_CTIMER_STMINTSTAT_CAPTUREC_M
#define AM_HAL_STIMER_INT_CAPTURED         AM_REG_CTIMER_STMINTSTAT_CAPTURED_M

//! @}



//*****************************************************************************
//
//! @name STimer Configuration Bits
//! @brief Interrupt Status Bits for enable/disble use
//!
//! These macros may be used to set and clear interrupt bits
//! @{
//
//*****************************************************************************
#define AM_HAL_STIMER_CFG_THAW                                                \
                                                AM_REG_CTIMER_STCFG_FREEZE_THAW
#define AM_HAL_STIMER_CFG_FREEZE                                              \
                                              AM_REG_CTIMER_STCFG_FREEZE_FREEZE
#define AM_HAL_STIMER_CFG_RUN                                                 \
                                                  AM_REG_CTIMER_STCFG_CLEAR_RUN
#define AM_HAL_STIMER_CFG_CLEAR                                               \
                                                AM_REG_CTIMER_STCFG_CLEAR_CLEAR
#define AM_HAL_STIMER_CFG_COMPARE_A_ENABLE                                    \
                                        AM_REG_CTIMER_STCFG_COMPARE_A_EN_ENABLE
#define AM_HAL_STIMER_CFG_COMPARE_B_ENABLE                                    \
                                        AM_REG_CTIMER_STCFG_COMPARE_B_EN_ENABLE
#define AM_HAL_STIMER_CFG_COMPARE_C_ENABLE                                    \
                                        AM_REG_CTIMER_STCFG_COMPARE_C_EN_ENABLE
#define AM_HAL_STIMER_CFG_COMPARE_D_ENABLE                                    \
                                        AM_REG_CTIMER_STCFG_COMPARE_D_EN_ENABLE
#define AM_HAL_STIMER_CFG_COMPARE_E_ENABLE                                    \
                                        AM_REG_CTIMER_STCFG_COMPARE_E_EN_ENABLE
#define AM_HAL_STIMER_CFG_COMPARE_F_ENABLE                                    \
                                        AM_REG_CTIMER_STCFG_COMPARE_F_EN_ENABLE
#define AM_HAL_STIMER_CFG_COMPARE_G_ENABLE                                    \
                                        AM_REG_CTIMER_STCFG_COMPARE_G_EN_ENABLE
#define AM_HAL_STIMER_CFG_COMPARE_H_ENABLE                                    \
                                        AM_REG_CTIMER_STCFG_COMPARE_H_EN_ENABLE

//! @}

//*****************************************************************************
//
//! @name Clock Configuration options
//! @brief STimer Configuration register options.
//!
//! These options are to be used with the am_hal_stimer_config() function.
//!  @{
//
//*****************************************************************************
#define AM_HAL_STIMER_NO_CLK                                                  \
              AM_REG_CTIMER_STCFG_CLKSEL(AM_REG_CTIMER_STCFG_CLKSEL_NOCLK)
#define AM_HAL_STIMER_HFRC_3MHZ                                               \
              AM_REG_CTIMER_STCFG_CLKSEL(AM_REG_CTIMER_STCFG_CLKSEL_HFRC_DIV16)
#define AM_HAL_STIMER_HFRC_187_5KHZ                                           \
              AM_REG_CTIMER_STCFG_CLKSEL(AM_REG_CTIMER_STCFG_CLKSEL_HFRC_DIV256)
#define AM_HAL_STIMER_XTAL_32KHZ                                              \
              AM_REG_CTIMER_STCFG_CLKSEL(AM_REG_CTIMER_STCFG_CLKSEL_XTAL_DIV1)
#define AM_HAL_STIMER_XTAL_16KHZ                                              \
              AM_REG_CTIMER_STCFG_CLKSEL(AM_REG_CTIMER_STCFG_CLKSEL_XTAL_DIV2)
#define AM_HAL_STIMER_XTAL_1KHZ                                               \
              AM_REG_CTIMER_STCFG_CLKSEL(AM_REG_CTIMER_STCFG_CLKSEL_XTAL_DIV32)
#define AM_HAL_STIMER_LFRC_1KHZ                                               \
              AM_REG_CTIMER_STCFG_CLKSEL(AM_REG_CTIMER_STCFG_CLKSEL_LFRC_DIV1)
#define AM_HAL_STIMER_HFRC_CTIMER0A                                           \
              AM_REG_CTIMER_STCFG_CLKSEL(AM_REG_CTIMER_STCFG_CLKSEL_CTIMER0A)
#define AM_HAL_STIMER_HFRC_CTIMER0B                                           \
              AM_REG_CTIMER_STCFG_CLKSEL(AM_REG_CTIMER_STCFG_CLKSEL_CTIMER0B)
//! @}



//*****************************************************************************
//
//! @name Capture Control Register options.
//! @brief Configuration options for capture control register.
//!
//! These options are to be used with the am_hal_stimer_capture_control_set
//! function.
//!  @{
//
//*****************************************************************************
#define AM_HAL_STIMER_CAPTURE_A_ENABLE                                        \
                                 AM_REG_CTIMER_CAPTURE_CONTROL_CAPTURE_A_ENABLE
#define AM_HAL_STIMER_CAPTURE_B_ENABLE                                        \
                                 AM_REG_CTIMER_CAPTURE_CONTROL_CAPTURE_B_ENABLE
#define AM_HAL_STIMER_CAPTURE_C_ENABLE                                        \
                                 AM_REG_CTIMER_CAPTURE_CONTROL_CAPTURE_C_ENABLE
#define AM_HAL_STIMER_CAPTURE_D_ENABLE                                        \
                                 AM_REG_CTIMER_CAPTURE_CONTROL_CAPTURE_D_ENABLE

//! @}


//*****************************************************************************
//
//
//
//*****************************************************************************

//*****************************************************************************
//
// Stimer configuration structure
//
//*****************************************************************************
typedef struct
{
    //
    //! Configuration options for the STIMER
    //
    uint32_t ui32STimerConfig;
}
am_hal_stimer_config_t;



#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// External function definitions
//
//*****************************************************************************
extern uint32_t am_hal_stimer_config(uint32_t ui32STimerConfig);
extern uint32_t am_hal_stimer_counter_get(void);
extern void     am_hal_stimer_counter_clear(void);
extern void     am_hal_stimer_compare_delta_set(uint32_t ui32CmprInstance,
                                                uint32_t ui32Delta);
extern uint32_t am_hal_stimer_compare_get(uint32_t ui32CmprInstance);
extern void     am_hal_stimer_capture_start(uint32_t ui32CaptureNum,
                                            uint32_t ui32GPIONumber,
                                            bool bPolarity);
extern void     am_hal_stimer_capture_stop(uint32_t ui32CaptureNum);
extern uint32_t am_hal_stimer_capture_get(uint32_t ui32CaptureNum);
extern void     am_hal_stimer_int_enable(uint32_t ui32Interrupt);
extern uint32_t am_hal_stimer_int_enable_get(void);
extern void     am_hal_stimer_int_disable(uint32_t ui32Interrupt);
extern void     am_hal_stimer_int_set(uint32_t ui32Interrupt);
extern void     am_hal_stimer_int_clear(uint32_t ui32Interrupt);
extern uint32_t am_hal_stimer_int_status_get(bool bEnabledOnly);


#ifdef __cplusplus
}
#endif

#endif // AM_HAL_STIMER_H

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
