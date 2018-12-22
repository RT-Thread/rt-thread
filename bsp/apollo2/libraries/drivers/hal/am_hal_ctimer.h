//*****************************************************************************
//
//  am_hal_ctimer.h
//! @file
//!
//! @brief Functions for accessing and configuring the CTIMER.
//!
//! @addtogroup ctimer2 Counter/Timer (CTIMER)
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
#ifndef AM_HAL_CTIMER_H
#define AM_HAL_CTIMER_H

//*****************************************************************************
//
//! Number of timers
//
//*****************************************************************************
#define AM_HAL_CTIMER_TIMERS_NUM    4

//*****************************************************************************
//
//! Timer offset value
//
//*****************************************************************************
#define AM_HAL_CTIMER_TIMER_OFFSET  (AM_REG_CTIMER_TMR1_O - AM_REG_CTIMER_TMR0_O)

//*****************************************************************************
//
//! @name Interrupt Status Bits
//! @brief Interrupt Status Bits for enable/disble use
//!
//! These macros may be used to set and clear interrupt bits
//! @{
//
//*****************************************************************************
#define AM_HAL_CTIMER_INT_TIMERA0C0         AM_REG_CTIMER_INTEN_CTMRA0C0INT_M
#define AM_HAL_CTIMER_INT_TIMERA0C1         AM_REG_CTIMER_INTEN_CTMRA0C1INT_M
#define AM_HAL_CTIMER_INT_TIMERA1C0         AM_REG_CTIMER_INTEN_CTMRA1C0INT_M
#define AM_HAL_CTIMER_INT_TIMERA1C1         AM_REG_CTIMER_INTEN_CTMRA1C1INT_M
#define AM_HAL_CTIMER_INT_TIMERA2C0         AM_REG_CTIMER_INTEN_CTMRA2C0INT_M
#define AM_HAL_CTIMER_INT_TIMERA2C1         AM_REG_CTIMER_INTEN_CTMRA2C1INT_M
#define AM_HAL_CTIMER_INT_TIMERA3C0         AM_REG_CTIMER_INTEN_CTMRA3C0INT_M
#define AM_HAL_CTIMER_INT_TIMERA3C1         AM_REG_CTIMER_INTEN_CTMRA3C1INT_M

#define AM_HAL_CTIMER_INT_TIMERB0C0         AM_REG_CTIMER_INTEN_CTMRB0C0INT_M
#define AM_HAL_CTIMER_INT_TIMERB0C1         AM_REG_CTIMER_INTEN_CTMRB0C1INT_M
#define AM_HAL_CTIMER_INT_TIMERB1C0         AM_REG_CTIMER_INTEN_CTMRB1C0INT_M
#define AM_HAL_CTIMER_INT_TIMERB1C1         AM_REG_CTIMER_INTEN_CTMRB1C1INT_M
#define AM_HAL_CTIMER_INT_TIMERB2C0         AM_REG_CTIMER_INTEN_CTMRB2C0INT_M
#define AM_HAL_CTIMER_INT_TIMERB2C1         AM_REG_CTIMER_INTEN_CTMRB2C1INT_M
#define AM_HAL_CTIMER_INT_TIMERB3C0         AM_REG_CTIMER_INTEN_CTMRB3C0INT_M
#define AM_HAL_CTIMER_INT_TIMERB3C1         AM_REG_CTIMER_INTEN_CTMRB3C1INT_M

//
// Deprecated, use the newer macros above.
//
#define AM_HAL_CTIMER_INT_TIMERA0           AM_HAL_CTIMER_INT_TIMERA0C0
#define AM_HAL_CTIMER_INT_TIMERB0           AM_HAL_CTIMER_INT_TIMERB0C0
#define AM_HAL_CTIMER_INT_TIMERA1           AM_HAL_CTIMER_INT_TIMERA1C0
#define AM_HAL_CTIMER_INT_TIMERB1           AM_HAL_CTIMER_INT_TIMERB1C0
#define AM_HAL_CTIMER_INT_TIMERA2           AM_HAL_CTIMER_INT_TIMERA2C0
#define AM_HAL_CTIMER_INT_TIMERB2           AM_HAL_CTIMER_INT_TIMERB2C0
#define AM_HAL_CTIMER_INT_TIMERA3           AM_HAL_CTIMER_INT_TIMERA3C0
#define AM_HAL_CTIMER_INT_TIMERB3           AM_HAL_CTIMER_INT_TIMERB3C0
//! @}

//*****************************************************************************
//
//! @name Configuration options
//! @brief Configuration options for \e am_hal_ctimer_config_t
//!
//! These options are to be used with the \e am_hal_ctimer_config_t structure
//! used by \e am_hal_ctimer_config
//! @{
//
//*****************************************************************************
#define AM_HAL_CTIMER_CLK_PIN               AM_REG_CTIMER_CTRL0_TMRA0CLK(0x0)
#define AM_HAL_CTIMER_HFRC_12MHZ            AM_REG_CTIMER_CTRL0_TMRA0CLK(0x1)
#define AM_HAL_CTIMER_HFRC_3MHZ             AM_REG_CTIMER_CTRL0_TMRA0CLK(0x2)
#define AM_HAL_CTIMER_HFRC_187_5KHZ         AM_REG_CTIMER_CTRL0_TMRA0CLK(0x3)
#define AM_HAL_CTIMER_HFRC_47KHZ            AM_REG_CTIMER_CTRL0_TMRA0CLK(0x4)
#define AM_HAL_CTIMER_HFRC_12KHZ            AM_REG_CTIMER_CTRL0_TMRA0CLK(0x5)
#define AM_HAL_CTIMER_XT_32_768KHZ          AM_REG_CTIMER_CTRL0_TMRA0CLK(0x6)
#define AM_HAL_CTIMER_XT_16_384KHZ          AM_REG_CTIMER_CTRL0_TMRA0CLK(0x7)
#define AM_HAL_CTIMER_XT_2_048KHZ           AM_REG_CTIMER_CTRL0_TMRA0CLK(0x8)
#define AM_HAL_CTIMER_XT_256HZ              AM_REG_CTIMER_CTRL0_TMRA0CLK(0x9)
#define AM_HAL_CTIMER_LFRC_512HZ            AM_REG_CTIMER_CTRL0_TMRA0CLK(0xA)
#define AM_HAL_CTIMER_LFRC_32HZ             AM_REG_CTIMER_CTRL0_TMRA0CLK(0xB)
#define AM_HAL_CTIMER_LFRC_1HZ              AM_REG_CTIMER_CTRL0_TMRA0CLK(0xC)
#define AM_HAL_CTIMER_LFRC_1_16HZ           AM_REG_CTIMER_CTRL0_TMRA0CLK(0xD)
#define AM_HAL_CTIMER_RTC_100HZ             AM_REG_CTIMER_CTRL0_TMRA0CLK(0xE)
#define AM_HAL_CTIMER_HCLK                  AM_REG_CTIMER_CTRL0_TMRA0CLK(0xF)
#define AM_HAL_CTIMER_BUCK                  AM_REG_CTIMER_CTRL0_TMRA0CLK(0x10)
//! @}

//*****************************************************************************
//
// Timer function macros.
//
//*****************************************************************************
#define AM_HAL_CTIMER_FN_ONCE               AM_REG_CTIMER_CTRL0_TMRA0FN(0)
#define AM_HAL_CTIMER_FN_REPEAT             AM_REG_CTIMER_CTRL0_TMRA0FN(1)
#define AM_HAL_CTIMER_FN_PWM_ONCE           AM_REG_CTIMER_CTRL0_TMRA0FN(2)
#define AM_HAL_CTIMER_FN_PWM_REPEAT         AM_REG_CTIMER_CTRL0_TMRA0FN(3)
#define AM_HAL_CTIMER_FN_CONTINUOUS         AM_REG_CTIMER_CTRL0_TMRA0FN(4)

//*****************************************************************************
//
// Half-timer options.
//
//*****************************************************************************
#define AM_HAL_CTIMER_INT_ENABLE            AM_REG_CTIMER_CTRL0_TMRA0IE0_M
#define AM_HAL_CTIMER_PIN_ENABLE            AM_REG_CTIMER_CTRL0_TMRA0PE_M
#define AM_HAL_CTIMER_PIN_INVERT            AM_REG_CTIMER_CTRL0_TMRA0POL_M
#define AM_HAL_CTIMER_CLEAR                 AM_REG_CTIMER_CTRL0_TMRA0CLR_M

//*****************************************************************************
//
// Additional timer options.
//
//*****************************************************************************
#define AM_HAL_CTIMER_LINK                  AM_REG_CTIMER_CTRL0_CTLINK0_M
#define AM_HAL_CTIMER_ADC_TRIG              AM_REG_CTIMER_CTRL3_ADCEN_M

//*****************************************************************************
//
// Timer selection macros.
//
//*****************************************************************************
#define AM_HAL_CTIMER_TIMERA                0x0000FFFF
#define AM_HAL_CTIMER_TIMERB                0xFFFF0000
#define AM_HAL_CTIMER_BOTH                  0xFFFFFFFF
//! @}

//*****************************************************************************
//
// Timer configuration structure
//
//*****************************************************************************
typedef struct
{
    //
    //! Set to 1 to operate this timer as a 32-bit timer instead of two 16-bit
    //! timers.
    //
    uint32_t ui32Link;

    //
    //! Configuration options for TIMERA
    //
    uint32_t ui32TimerAConfig;

    //
    //! Configuration options for TIMERB
    //
    uint32_t ui32TimerBConfig;

}
am_hal_ctimer_config_t;

//*****************************************************************************
//
// Function pointer type for CTimer interrupt handlers.
//
//*****************************************************************************
typedef void (*am_hal_ctimer_handler_t)(void);

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// External function definitions
//
//*****************************************************************************
extern void am_hal_ctimer_config(uint32_t ui32TimerNumber,
                                 am_hal_ctimer_config_t *psConfig);

extern void am_hal_ctimer_config_single(uint32_t ui32TimerNumber,
                                        uint32_t ui32TimerSegment,
                                        uint32_t ui32ConfigVal);

extern void am_hal_ctimer_start(uint32_t ui32TimerNumber,
                                uint32_t ui32TimerSegment);

extern void am_hal_ctimer_stop(uint32_t ui32TimerNumber,
                               uint32_t ui32TimerSegment);

extern void am_hal_ctimer_clear(uint32_t ui32TimerNumber,
                                uint32_t ui32TimerSegment);

extern uint32_t am_hal_ctimer_read(uint32_t ui32TimerNumber,
                                   uint32_t ui32TimerSegment);

extern void am_hal_ctimer_pin_enable(uint32_t ui32TimerNumber,
                                     uint32_t ui32TimerSegment);

extern void am_hal_ctimer_pin_disable(uint32_t ui32TimerNumber,
                                      uint32_t ui32TimerSegment);

extern void am_hal_ctimer_pin_invert(uint32_t ui32TimerNumber,
                                     uint32_t ui32TimerSegment,
                                     bool bInvertOutput);

extern void am_hal_ctimer_compare_set(uint32_t ui32TimerNumber,
                                      uint32_t ui32TimerSegment,
                                      uint32_t ui32CompareReg,
                                      uint32_t ui32Value);

extern void am_hal_ctimer_period_set(uint32_t ui32TimerNumber,
                                     uint32_t ui32TimerSegment,
                                     uint32_t ui32Period,
                                     uint32_t ui32OnTime);

extern void am_hal_ctimer_adc_trigger_enable(void);
extern void am_hal_ctimer_adc_trigger_disable(void);
extern void am_hal_ctimer_int_enable(uint32_t ui32Interrupt);
extern uint32_t am_hal_ctimer_int_enable_get(void);
extern void am_hal_ctimer_int_disable(uint32_t ui32Interrupt);
extern void am_hal_ctimer_int_set(uint32_t ui32Interrupt);
extern void am_hal_ctimer_int_clear(uint32_t ui32Interrupt);
extern uint32_t am_hal_ctimer_int_status_get(bool bEnabledOnly);
extern void am_hal_ctimer_int_register(uint32_t ui32Interrupt,
                                       am_hal_ctimer_handler_t pfnHandler);
extern void am_hal_ctimer_int_service(uint32_t ui32Status);

#ifdef __cplusplus
}
#endif

#endif // AM_HAL_CTIMER_H

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
