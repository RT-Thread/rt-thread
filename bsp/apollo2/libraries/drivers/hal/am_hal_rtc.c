//*****************************************************************************
//
//  am_hal_rtc.c
//! @file
//!
//! @brief Functions for interfacing with the Real-Time Clock (RTC).
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

#include <stdint.h>
#include <stdbool.h>
#include "am_mcu_apollo.h"

//*****************************************************************************
//
// Converts a Binary Coded Decimal (BCD) byte to its Decimal form.
//
//*****************************************************************************
static uint8_t
bcd_to_dec(uint8_t ui8BCDByte)
{
  return (((ui8BCDByte & 0xF0) >> 4) * 10) + (ui8BCDByte & 0x0F);
}

//*****************************************************************************
//
// Converts a Decimal byte to its Binary Coded Decimal (BCD) form.
//
//*****************************************************************************
static uint8_t
dec_to_bcd(uint8_t ui8DecimalByte)
{
  return (((ui8DecimalByte / 10) << 4) | (ui8DecimalByte % 10));
}

//*****************************************************************************
//
//! @brief Selects the clock source for the RTC.
//!
//! @param ui32OSC the clock source for the RTC.
//!
//! This function selects the clock source for the RTC.
//!
//! Valid values for ui32OSC are:
//!
//!     AM_HAL_RTC_OSC_LFRC
//!     AM_HAL_RTC_OSC_XT
//!
//! @return None
//
//*****************************************************************************
void
am_hal_rtc_osc_select(uint32_t ui32OSC)
{
    //
    // Set XT if flag is set.
    // Otherwise configure for LFRC.
    //
    if (ui32OSC)
    {
        AM_REG(CLKGEN, OCTRL) |= AM_REG_CLKGEN_OCTRL_OSEL_M;
    }
    else
    {
        AM_REG(CLKGEN, OCTRL) &= ~AM_REG_CLKGEN_OCTRL_OSEL_M;
    }
}

//*****************************************************************************
//
//! @brief Enable/Start the RTC oscillator.
//!
//! Starts the RTC oscillator.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_rtc_osc_enable(void)
{
    //
    // Start the RTC Oscillator.
    //
    AM_REG(RTC, RTCCTL) &= ~AM_REG_RTC_RTCCTL_RSTOP(1);
}

//*****************************************************************************
//
//! @brief Disable/Stop the RTC oscillator.
//!
//! Stops the RTC oscillator.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_rtc_osc_disable(void)
{
    //
    // Stop the RTC Oscillator.
    //
    AM_REG(RTC, RTCCTL) |= AM_REG_RTC_RTCCTL_RSTOP(1);
}

//*****************************************************************************
//
//! @brief Configures the RTC for 12 or 24 hour time keeping.
//!
//! @param b12Hour - A 'true' configures the RTC for 12 hour time keeping.
//!
//! Configures the RTC for 12 (true) or 24 (false) hour time keeping.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_rtc_time_12hour(bool b12Hour)
{
    //
    // Set the 12/24 hour bit.
    //
    AM_REG(RTC, RTCCTL) |= AM_REG_RTC_RTCCTL_HR1224(b12Hour);
}

//*****************************************************************************
//
//! @brief Enable selected RTC interrupts.
//!
//! @param ui32Interrupt - desired interrupts
//!
//! Enables the RTC interrupts.
//!
//! ui32Interrupt should be an OR of the following:
//!
//!     AM_HAL_RTC_INT_ALM
//!     AM_HAL_RTC_INT_OF
//!     AM_HAL_RTC_INT_ACC
//!     AM_HAL_RTC_INT_ACF
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_rtc_int_enable(uint32_t ui32Interrupt)
{
    //
    // Enable the interrupts.
    //
    AM_REG(RTC, INTEN) |= ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Return the enabled RTC interrupts.
//!
//! Returns the enabled RTC interrupts.
//!
//! @return enabled RTC interrupts. Return is a logical or of:
//!
//!     AM_HAL_RTC_INT_ALM
//!     AM_HAL_RTC_INT_OF
//!     AM_HAL_RTC_INT_ACC
//!     AM_HAL_RTC_INT_ACF
//
//*****************************************************************************
uint32_t
am_hal_rtc_int_enable_get(void)
{
    //
    // Read the RTC interrupt enable register, and return its contents.
    //
    return AM_REG(RTC, INTEN);
}

//*****************************************************************************
//
//! @brief Disable selected RTC interrupts.
//!
//! @param ui32Interrupt - desired interrupts
//!
//! Disables the RTC interrupts.
//!
//! ui32Interrupt should be an OR of the following:
//!
//!     AM_HAL_RTC_INT_ALM
//!     AM_HAL_RTC_INT_OF
//!     AM_HAL_RTC_INT_ACC
//!     AM_HAL_RTC_INT_ACF
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_rtc_int_disable(uint32_t ui32Interrupt)
{
    //
    // Disable the interrupts.
    //
    AM_REG(RTC, INTEN) &= ~ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Sets the selected RTC interrupts.
//!
//! @param ui32Interrupt - desired interrupts
//!
//! Sets the RTC interrupts causing them to immediately trigger.
//!
//! ui32Interrupt should be an OR of the following:
//!
//!     AM_HAL_RTC_INT_ALM
//!     AM_HAL_RTC_INT_OF
//!     AM_HAL_RTC_INT_ACC
//!     AM_HAL_RTC_INT_ACF
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_rtc_int_set(uint32_t ui32Interrupt)
{
    //
    // Set the interrupts.
    //
    AM_REG(RTC, INTSET) = ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Clear selected RTC interrupts.
//!
//! @param ui32Interrupt - desired interrupts
//!
//! Clears the RTC interrupts.
//!
//! ui32Interrupt should be an OR of the following:
//!
//!     AM_HAL_RTC_INT_ALM
//!     AM_HAL_RTC_INT_OF
//!     AM_HAL_RTC_INT_ACC
//!     AM_HAL_RTC_INT_ACF
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_rtc_int_clear(uint32_t ui32Interrupt)
{
    //
    // Clear the interrupts.
    //
    AM_REG(RTC, INTCLR) = ui32Interrupt;
}

//*****************************************************************************
//
//! @brief Returns the RTC interrupt status.
//!
//! @param bEnabledOnly - return the status of only the enabled interrupts.
//!
//! Returns the RTC interrupt status.
//!
//! @return Bitwise representation of the current interrupt status.
//!
//! The return value will be the logical OR of one or more of the following
//! values:
//!
//!     AM_HAL_RTC_INT_ALM
//!     AM_HAL_RTC_INT_OF
//!     AM_HAL_RTC_INT_ACC
//!     AM_HAL_RTC_INT_ACF
//
//*****************************************************************************
uint32_t
am_hal_rtc_int_status_get(bool bEnabledOnly)
{
    //
    // Get the interrupt status.
    //
    if (bEnabledOnly)
    {
        uint32_t u32RetVal;
        u32RetVal  = AM_REG(RTC, INTSTAT);
        u32RetVal &= AM_REG(RTC, INTEN);
        return u32RetVal &
                (AM_HAL_RTC_INT_ALM | AM_HAL_RTC_INT_OF |
                AM_HAL_RTC_INT_ACC | AM_HAL_RTC_INT_ACF);
    }
    else
    {
        return (AM_REG(RTC, INTSTAT) & (AM_HAL_RTC_INT_ALM |
                                        AM_HAL_RTC_INT_OF |
                                        AM_HAL_RTC_INT_ACC |
                                        AM_HAL_RTC_INT_ACF));
    }
}

//*****************************************************************************
//
//! @brief Set the Real Time Clock counter registers.
//!
//! @param *pTime - A pointer to the time structure.
//!
//! Sets the RTC counter registers to the supplied values.
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_rtc_time_set(am_hal_rtc_time_t *pTime)
{
    //
    // Enable writing to the counters.
    //
    AM_REG(RTC, RTCCTL) |= AM_REG_RTC_RTCCTL_WRTC(1);

    //
    // Write the RTCLOW register.
    //
    AM_REG(RTC, CTRLOW) =
        AM_REG_RTC_CTRLOW_CTRHR(dec_to_bcd(pTime->ui32Hour))                |
        AM_REG_RTC_CTRLOW_CTRMIN(dec_to_bcd(pTime->ui32Minute))             |
        AM_REG_RTC_CTRLOW_CTRSEC(dec_to_bcd(pTime->ui32Second))             |
        AM_REG_RTC_CTRLOW_CTR100(dec_to_bcd(pTime->ui32Hundredths));

    //
    // Write the RTCUP register.
    //
    AM_REG(RTC, CTRUP) =
        AM_REG_RTC_CTRUP_CEB((pTime->ui32CenturyEnable))                   |
        AM_REG_RTC_CTRUP_CB((pTime->ui32Century))                          |
        AM_REG_RTC_CTRUP_CTRWKDY((pTime->ui32Weekday))                     |
        AM_REG_RTC_CTRUP_CTRYR(dec_to_bcd((pTime->ui32Year)))              |
        AM_REG_RTC_CTRUP_CTRMO(dec_to_bcd((pTime->ui32Month)))             |
        AM_REG_RTC_CTRUP_CTRDATE(dec_to_bcd((pTime->ui32DayOfMonth)));

    //
    // Disable writing to the counters.
    //
    AM_REG(RTC, RTCCTL) |= AM_REG_RTC_RTCCTL_WRTC(0);
}

//*****************************************************************************
//
//! @brief Get the Real Time Clock current time.
//!
//! @param *pTime - A pointer to the time structure to store the current time.
//!
//! Gets the RTC's current time
//!
//! @return 0 for success and 1 for error.
//
//*****************************************************************************
uint32_t
am_hal_rtc_time_get(am_hal_rtc_time_t *pTime)
{
    uint32_t ui32RTCLow, ui32RTCUp, ui32Value;

    //
    // Read the upper and lower RTC registers.
    //
    ui32RTCLow = AM_REG(RTC, CTRLOW);
    ui32RTCUp = AM_REG(RTC, CTRUP);

    //
    // Break out the lower word.
    //
    ui32Value =
        ((ui32RTCLow & AM_REG_RTC_CTRLOW_CTRHR_M) >> AM_REG_RTC_CTRLOW_CTRHR_S);
    pTime->ui32Hour = bcd_to_dec(ui32Value);

    ui32Value =
        ((ui32RTCLow & AM_REG_RTC_CTRLOW_CTRMIN_M) >> AM_REG_RTC_CTRLOW_CTRMIN_S);
    pTime->ui32Minute = bcd_to_dec(ui32Value);

    ui32Value =
        ((ui32RTCLow & AM_REG_RTC_CTRLOW_CTRSEC_M) >> AM_REG_RTC_CTRLOW_CTRSEC_S);
    pTime->ui32Second = bcd_to_dec(ui32Value);

    ui32Value =
        ((ui32RTCLow & AM_REG_RTC_CTRLOW_CTR100_M) >> AM_REG_RTC_CTRLOW_CTR100_S);
    pTime->ui32Hundredths = bcd_to_dec(ui32Value);

    //
    // Break out the upper word.
    //
    pTime->ui32ReadError =
        ((ui32RTCUp & AM_REG_RTC_CTRUP_CTERR_M) >> AM_REG_RTC_CTRUP_CTERR_S);

    pTime->ui32CenturyEnable =
        ((ui32RTCUp & AM_REG_RTC_CTRUP_CEB_M) >> AM_REG_RTC_CTRUP_CEB_S);

    pTime->ui32Century =
        ((ui32RTCUp & AM_REG_RTC_CTRUP_CB_M) >> AM_REG_RTC_CTRUP_CB_S);

    ui32Value =
        ((ui32RTCUp & AM_REG_RTC_CTRUP_CTRWKDY_M) >> AM_REG_RTC_CTRUP_CTRWKDY_S);
    pTime->ui32Weekday = bcd_to_dec(ui32Value);

    ui32Value =
        ((ui32RTCUp & AM_REG_RTC_CTRUP_CTRYR_M) >> AM_REG_RTC_CTRUP_CTRYR_S);
    pTime->ui32Year = bcd_to_dec(ui32Value);

    ui32Value =
        ((ui32RTCUp & AM_REG_RTC_CTRUP_CTRMO_M) >> AM_REG_RTC_CTRUP_CTRMO_S);
    pTime->ui32Month = bcd_to_dec(ui32Value);

    ui32Value =
        ((ui32RTCUp & AM_REG_RTC_CTRUP_CTRDATE_M) >> AM_REG_RTC_CTRUP_CTRDATE_S);
    pTime->ui32DayOfMonth = bcd_to_dec(ui32Value);

    //
    // Was there a read error?
    //
    if (pTime->ui32ReadError)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//*****************************************************************************
//
//! @brief Sets the alarm repeat interval.
//!
//! @param ui32RepeatInterval the desired repeat interval.
//!
//! Sets the alarm repeat interval.
//!
//! Valid values for ui32RepeatInterval:
//!
//!     AM_HAL_RTC_ALM_RPT_DIS
//!     AM_HAL_RTC_ALM_RPT_YR
//!     AM_HAL_RTC_ALM_RPT_MTH
//!     AM_HAL_RTC_ALM_RPT_WK
//!     AM_HAL_RTC_ALM_RPT_DAY
//!     AM_HAL_RTC_ALM_RPT_HR
//!     AM_HAL_RTC_ALM_RPT_MIN
//!     AM_HAL_RTC_ALM_RPT_SEC
//!     AM_HAL_RTC_ALM_RPT_10TH
//!     AM_HAL_RTC_ALM_RPT_100TH
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_rtc_alarm_interval_set(uint32_t ui32RepeatInterval)
{
    uint32_t ui32RptInt, ui32Alm100, ui32Value;

    switch(ui32RepeatInterval)
    {
        //
        // If repeat every 10th set RPT and ALM100 field accordinly
        //
        case AM_HAL_RTC_ALM_RPT_10TH:
            ui32RptInt = AM_HAL_RTC_ALM_RPT_SEC;
            ui32Alm100 = AM_HAL_RTC_ALM100_10TH;
            break;
        //
        // If repeat every 100th set RPT and ALM100 field accordinly
        //
        case AM_HAL_RTC_ALM_RPT_100TH:
            ui32RptInt = AM_HAL_RTC_ALM_RPT_SEC;
            ui32Alm100 = AM_HAL_RTC_ALM100_100TH;
            break;
        //
        // Otherwise set RPT as value passed.  ALM100 values need to be 0xnn
        // in this setting where n = 0-9.
        //
        default:
            //
            // Get the current value of the ALM100 field.
            //
            ui32Value = AM_BFR(RTC, ALMLOW, ALM100);

            //
            // If ALM100 was previous EVERY_10TH or EVERY_100TH reset to zero
            // otherwise keep previous setting.
            //
            ui32Alm100 = ui32Value >= 0xF0 ? 0 : ui32Value;

            //
            // Set RPT value to value passed.
            //
            ui32RptInt = ui32RepeatInterval;
            break;
    }

    //
    // Write the interval to the register.
    //
    AM_BFW(RTC, RTCCTL, RPT, ui32RptInt);

    //
    // Write the Alarm 100 bits in the ALM100 register.
    //
    AM_BFW(RTC, ALMLOW, ALM100, ui32Alm100);
}

//*****************************************************************************
//
//! @brief Sets the RTC's Alarm.
//!
//! @param *pTime - A pointer to the time structure.
//! @param ui32RepeatInterval - the desired alarm repeat interval.
//!
//! Set the Real Time Clock Alarm Parameters.
//!
//! Valid values for ui32RepeatInterval:
//!
//!     AM_HAL_RTC_ALM_RPT_DIS
//!     AM_HAL_RTC_ALM_RPT_YR
//!     AM_HAL_RTC_ALM_RPT_MTH
//!     AM_HAL_RTC_ALM_RPT_WK
//!     AM_HAL_RTC_ALM_RPT_DAY
//!     AM_HAL_RTC_ALM_RPT_HR
//!     AM_HAL_RTC_ALM_RPT_MIN
//!     AM_HAL_RTC_ALM_RPT_SEC
//!     AM_HAL_RTC_ALM_RPT_10TH
//!     AM_HAL_RTC_ALM_RPT_EVERY_100TH
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_rtc_alarm_set(am_hal_rtc_time_t *pTime, uint32_t ui32RepeatInterval)
{
    uint8_t ui8Value = 0;

    //
    // Write the interval to the register.
    //
    AM_REG(RTC, RTCCTL) |=
        AM_REG_RTC_RTCCTL_RPT(ui32RepeatInterval > 0x7 ? 0x7 : ui32RepeatInterval);

    //
    // Check if the interval is 10th or every 100th and track it in ui8Value.
    //
    if (ui32RepeatInterval == AM_HAL_RTC_ALM_RPT_10TH)
    {
        ui8Value = 0xF0;
    }
    else if (ui32RepeatInterval == AM_HAL_RTC_ALM_RPT_100TH)
    {
        ui8Value = 0xFF;
    }

    //
    // Write the ALMUP register.
    //
    AM_REG(RTC, ALMUP) =
        AM_REG_RTC_ALMUP_ALMWKDY((pTime->ui32Weekday))                     |
        AM_REG_RTC_ALMUP_ALMMO(dec_to_bcd((pTime->ui32Month)))             |
        AM_REG_RTC_ALMUP_ALMDATE(dec_to_bcd((pTime->ui32DayOfMonth)));

    //
    // Write the ALMLOW register.
    //
    AM_REG(RTC, ALMLOW) =
        AM_REG_RTC_ALMLOW_ALMHR(dec_to_bcd(pTime->ui32Hour))                |
        AM_REG_RTC_ALMLOW_ALMMIN(dec_to_bcd(pTime->ui32Minute))             |
        AM_REG_RTC_ALMLOW_ALMSEC(dec_to_bcd(pTime->ui32Second))             |
        AM_REG_RTC_ALMLOW_ALM100(dec_to_bcd(pTime->ui32Hundredths) | ui8Value);
}

//*****************************************************************************
//
//! @brief Get the Real Time Clock Alarm Parameters
//!
//! @param *pTime - A pointer to the time structure to store the current alarm.
//!
//! Gets the RTC's Alarm time
//!
//! @return None.
//
//*****************************************************************************
void
am_hal_rtc_alarm_get(am_hal_rtc_time_t *pTime)
{
    uint32_t ui32ALMLow, ui32ALMUp, ui32Value;

    //
    // Read the upper and lower RTC registers.
    //
    ui32ALMLow = AM_REG(RTC, ALMLOW);
    ui32ALMUp = AM_REG(RTC, ALMUP);

    //
    // Break out the lower word.
    //
    ui32Value =
        ((ui32ALMLow & AM_REG_RTC_ALMLOW_ALMHR_M) >> AM_REG_RTC_ALMLOW_ALMHR_S);
    pTime->ui32Hour = bcd_to_dec(ui32Value);

    ui32Value =
        ((ui32ALMLow & AM_REG_RTC_ALMLOW_ALMMIN_M) >> AM_REG_RTC_ALMLOW_ALMMIN_S);
    pTime->ui32Minute = bcd_to_dec(ui32Value);

    ui32Value =
        ((ui32ALMLow & AM_REG_RTC_ALMLOW_ALMSEC_M) >> AM_REG_RTC_ALMLOW_ALMSEC_S);
    pTime->ui32Second = bcd_to_dec(ui32Value);

    ui32Value =
        ((ui32ALMLow & AM_REG_RTC_ALMLOW_ALM100_M) >> AM_REG_RTC_ALMLOW_ALM100_S);
    pTime->ui32Hundredths = bcd_to_dec(ui32Value);

    //
    // Break out the upper word.
    //
    pTime->ui32ReadError = 0;
    pTime->ui32CenturyEnable = 0;
    pTime->ui32Century = 0;

    ui32Value =
        ((ui32ALMUp & AM_REG_RTC_ALMUP_ALMWKDY_M) >> AM_REG_RTC_ALMUP_ALMWKDY_S);
    pTime->ui32Weekday = bcd_to_dec(ui32Value);

    pTime->ui32Year = 0;

    ui32Value =
        ((ui32ALMUp & AM_REG_RTC_ALMUP_ALMMO_M) >> AM_REG_RTC_ALMUP_ALMMO_S);
    pTime->ui32Month = bcd_to_dec(ui32Value);

    ui32Value =
        ((ui32ALMUp & AM_REG_RTC_ALMUP_ALMDATE_M) >> AM_REG_RTC_ALMUP_ALMDATE_S);
    pTime->ui32DayOfMonth = bcd_to_dec(ui32Value);
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
