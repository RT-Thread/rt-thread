//*****************************************************************************
//
//  am_hal_rtc.h
//! @file
//!
//! @brief Functions for interfacing and accessing the Real-Time Clock (RTC).
//!
//! @addtogroup rtc2 Real-Time Clock (RTC)
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
#ifndef AM_HAL_RTC_H
#define AM_HAL_RTC_H

//*****************************************************************************
//
//! @name OSC Start and Stop
//! @brief OSC Start and Stop defines.
//!
//! OSC Start and Stop defines to be used with \e am_hal_clkgen_osc_x().
//! @{
//
//*****************************************************************************
#define AM_HAL_RTC_OSC_LFRC          0x1
#define AM_HAL_RTC_OSC_XT            0x0
//! @}

//*****************************************************************************
//
//! @name RTC Interrupts
//! @brief Macro definitions for RTC interrupt status bits.
//!
//! These macros correspond to the bits in the RTC interrupt status register.
//! They may be used with any of the \e am_hal_rtc_int_x() functions.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_RTC_INT_ALM                  AM_REG_RTC_INTEN_ALM_M
#define AM_HAL_RTC_INT_OF                   AM_REG_RTC_INTEN_OF_M
#define AM_HAL_RTC_INT_ACC                  AM_REG_RTC_INTEN_ACC_M
#define AM_HAL_RTC_INT_ACF                  AM_REG_RTC_INTEN_ACF_M
//! @}

//*****************************************************************************
//
//! @name RTC Alarm Repeat Interval.
//! @brief Macro definitions for the RTC alarm repeat interval.
//!
//! These macros correspond to the RPT bits in the RTCCTL register.
//! They may be used with the \e am_hal_rtc_alarm_interval_set() function.
//!
//! Note: AM_HAL_RTC_ALM_RPT_10TH and AM_HAL_RTC_ALM_RPT_100TH do not
//! correspond to the RPT bits but are used in conjunction with setting the
//! ALM100 bits in the ALMLOW register.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_RTC_ALM_RPT_DIS              0x0
#define AM_HAL_RTC_ALM_RPT_YR               0x1
#define AM_HAL_RTC_ALM_RPT_MTH              0x2
#define AM_HAL_RTC_ALM_RPT_WK               0x3
#define AM_HAL_RTC_ALM_RPT_DAY              0x4
#define AM_HAL_RTC_ALM_RPT_HR               0x5
#define AM_HAL_RTC_ALM_RPT_MIN              0x6
#define AM_HAL_RTC_ALM_RPT_SEC              0x7
#define AM_HAL_RTC_ALM_RPT_10TH             0x8
#define AM_HAL_RTC_ALM_RPT_100TH            0x9
//! @}

//*****************************************************************************
//
//! @name RTC Alarm 100 Interval.
//! @brief Macro definitions for the RTC alarm ms intervals.
//!
//! These macros are used inside the #am_hal_rtc_alarm_interval_set function
//! when 10ms and 100ms repeated alarm intervals are desired.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_RTC_ALM100_DEFAULT           0x00
#define AM_HAL_RTC_ALM100_10TH              0xF0
#define AM_HAL_RTC_ALM100_100TH             0xFF
//! @}

//*****************************************************************************
//
//! @brief The basic time structure used by the HAL for RTC interaction.
//!
//! All values are positive whole numbers. The HAL routines convert back and
//! forth to BCD.
//
//*****************************************************************************
typedef struct am_hal_rtc_time_struct
{
    uint32_t ui32ReadError;
    uint32_t ui32CenturyEnable;
    uint32_t ui32Weekday;
    uint32_t ui32Century;
    uint32_t ui32Year;
    uint32_t ui32Month;
    uint32_t ui32DayOfMonth;
    uint32_t ui32Hour;
    uint32_t ui32Minute;
    uint32_t ui32Second;
    uint32_t ui32Hundredths;
}am_hal_rtc_time_t;

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// External function definitions
//
//*****************************************************************************
extern void am_hal_rtc_osc_select(uint32_t ui32OSC);
extern void am_hal_rtc_osc_enable(void);
extern void am_hal_rtc_osc_disable(void);
extern void am_hal_rtc_time_12hour(bool b12Hour);
extern void am_hal_rtc_time_set(am_hal_rtc_time_t *pTime);
extern uint32_t am_hal_rtc_time_get(am_hal_rtc_time_t *pTime);
extern void am_hal_rtc_alarm_interval_set(uint32_t ui32RepeatInterval);
extern void am_hal_rtc_alarm_set(am_hal_rtc_time_t *pTime,
                                 uint32_t ui32RepeatInterval);
extern void am_hal_rtc_alarm_get(am_hal_rtc_time_t *pTime);
extern void am_hal_rtc_int_enable(uint32_t ui32Interrupt);
extern uint32_t am_hal_rtc_int_enable_get(void);
extern void am_hal_rtc_int_disable(uint32_t ui32Interrupt);
extern void am_hal_rtc_int_clear(uint32_t ui32Interrupt);
extern void am_hal_rtc_int_set(uint32_t ui32Interrupt);
extern uint32_t am_hal_rtc_int_status_get(bool bEnabledOnly);

#ifdef __cplusplus
}
#endif

#endif // AM_HAL_RTC_H

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
