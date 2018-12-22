/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
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

/*!
 * @file snvs.c
 * @brief  SNVS driver source file.
 *
 */

#include "snvs/snvs.h"
#include "registers/regssnvs.h"

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void snvs_rtc_counter(uint8_t state)
{
    if (state)
    {
        // Set RTC_EN bit in hpcr register 
        HW_SNVS_HPCR_SET(BM_SNVS_HPCR_RTC_EN);

        // Wait until the bit is set 
        while (!HW_SNVS_HPCR.B.RTC_EN);
    }
    else
    {
        // Clear RTC_EN bit in hpcr register 
        HW_SNVS_HPCR_CLR(BM_SNVS_HPCR_RTC_EN);

        // Wait until the bit is cleared 
        while (HW_SNVS_HPCR.B.RTC_EN);
    }
}

void snvs_rtc_alarm(uint8_t state)
{
    if (state)
    {
        // Set HPTA_EN bit of hpcr register 
        HW_SNVS_HPCR_SET(BM_SNVS_HPCR_HPTA_EN);

        // Wait until the bit is set 
        while (!HW_SNVS_HPCR.B.HPTA_EN);
    }
    else
    {
        // Clear HPTA_EN bit of hpcr register 
        HW_SNVS_HPCR_CLR(BM_SNVS_HPCR_HPTA_EN);

        // Wait until the bit is cleared 
        while (HW_SNVS_HPCR.B.HPTA_EN);
    }
}

void snvs_rtc_periodic_interrupt(uint8_t freq, uint8_t state)
{
    if (state)
    {
        if (freq > 15)
        {
            freq = 15;
        }

        // Set freq, SNVS interrupts the CPU whenever the
        // frequency value (0-15) bit of RTC counter toggles.
        // The counter is incremented by the slow 32KHz clock.
        HW_SNVS_HPCR.B.PI_FREQ = freq;
        HW_SNVS_HPCR_SET(BM_SNVS_HPCR_PI_EN);
        while (!HW_SNVS_HPCR.B.PI_EN);
    }
    else
    {
        // Clear freq and periodic interrupt bit to disable periodic interrupt 
        HW_SNVS_HPCR_CLR(BM_SNVS_HPCR_PI_EN);

        while (HW_SNVS_HPCR.B.PI_EN);
    }
}

void snvs_rtc_set_counter(uint64_t count)
{
    // Disable RTC
    snvs_rtc_counter(false);

    // Program the counter  
    HW_SNVS_HPRTCLR_WR(count & 0xffffffff);
    HW_SNVS_HPRTCMR_WR(count >> 32);

    // Reenable RTC 
    snvs_rtc_counter(true);
}

void snvs_rtc_set_alarm_timeout(uint64_t timeout)
{
    // Disable alarm
    snvs_rtc_alarm(false);

    // Program time alarm registers 
    HW_SNVS_HPTALR_WR(timeout & 0xffffffff);
    HW_SNVS_HPTAMR_WR(timeout >> 32);

    // Reenable alarm 
    snvs_rtc_alarm(true);
}

void snvs_srtc_counter(uint8_t state)
{
    if (state)
    {
        HW_SNVS_LPCR_SET(BM_SNVS_LPCR_SRTC_ENV);
        while (!HW_SNVS_LPCR.B.SRTC_ENV);
    }
    else
    {
        HW_SNVS_LPCR_CLR(BM_SNVS_LPCR_SRTC_ENV);
        while (HW_SNVS_LPCR.B.SRTC_ENV);
    }
}

void snvs_srtc_alarm(uint8_t state)
{
    if (state)
    {
        HW_SNVS_LPCR_SET(BM_SNVS_LPCR_LPTA_EN);
        while (!HW_SNVS_LPCR.B.LPTA_EN);
    }    
    else
    {
        HW_SNVS_LPCR_CLR(BM_SNVS_LPCR_LPTA_EN);
        while (HW_SNVS_LPCR.B.LPTA_EN);
    }
}

void snvs_srtc_set_counter(uint64_t count)
{
    // Disable RTC
    snvs_srtc_counter(false);

    // Program the counter  
    HW_SNVS_LPSRTCLR_WR(count & 0xffffffff);
    HW_SNVS_LPSRTCMR_WR(count >> 32);

    // Reenable RTC 
    snvs_srtc_counter(true);
}

void snvs_srtc_set_alarm_timeout(uint32_t timeout)
{
    // Disable alarm
    snvs_srtc_alarm(false);

    // Program time alarm register 
    HW_SNVS_LPTAR_WR(timeout);

    // Reenable alarm 
    snvs_srtc_alarm(true);
}

void snvs_init(void)
{
    // Nothing to do here.
}

void snvs_deinit(void)
{
    // Nothing to do here.
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
