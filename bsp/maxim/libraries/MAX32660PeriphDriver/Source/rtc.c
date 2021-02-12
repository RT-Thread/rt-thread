/* ****************************************************************************
 * Copyright (C) 2017 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 *
 **************************************************************************** */

#include "mxc_config.h"
#include "rtc_regs.h"
#include "rtc.h"
#include "mxc_sys.h"
#include "mxc_delay.h"
#include "gpio_regs.h"
#include "mxc_errors.h"

#if TARGET == 32650
    #include "pwrseq_regs.h"
#endif

#define RTC_CTRL_RESET_DEFAULT (0x0000UL)
#define RTC_IS_BUSY (MXC_RTC->ctrl & MXC_F_RTC_CTRL_BUSY)
#define RTC_IS_ENABLED (MXC_RTC->ctrl & MXC_F_RTC_CTRL_RTCE)

#define BUSY_TIMEOUT 1000   // Timeout counts for the Busy bit

// *****************************************************************************
int RTC_EnableTimeofdayInterrupt(mxc_rtc_regs_t *rtc)
{
    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    rtc->ctrl |= MXC_F_RTC_CTRL_ADE;   // Enable Time-of-day Interrupt
    return E_SUCCESS;
}

// *****************************************************************************
int RTC_DisableTimeofdayInterrupt(mxc_rtc_regs_t *rtc)
{

    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    rtc->ctrl &= ~MXC_F_RTC_CTRL_ADE;    // Disable Time-of-day Interrupt

    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    return E_SUCCESS;
}

// *****************************************************************************
int RTC_EnableSubsecondInterrupt(mxc_rtc_regs_t *rtc)
{
    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    rtc->ctrl |= MXC_F_RTC_CTRL_ASE;    // Enable Sub-Second Interrupt

    return E_SUCCESS;
}

// *****************************************************************************
int RTC_DisableSubsecondInterrupt(mxc_rtc_regs_t *rtc)
{

    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    rtc->ctrl &= ~MXC_F_RTC_CTRL_ASE;    // Alarm Sub-Second Interrupt disabled

    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    return E_SUCCESS;
}

// *****************************************************************************
int RTC_SetTimeofdayAlarm(mxc_rtc_regs_t *rtc, uint32_t ras)
{
    // ras can only be written if BUSY = 0 & (RTCE = 0 or ADE = 0);


    if(RTC_DisableTimeofdayInterrupt(rtc) == E_BUSY) {
        return E_BUSY;
    }

    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    rtc->ras = (ras << MXC_F_RTC_RAS_RAS_POS) & MXC_F_RTC_RAS_RAS;

    if(RTC_EnableTimeofdayInterrupt(rtc) == E_BUSY) {
        return E_BUSY;
    }

    return E_SUCCESS;
}

// *****************************************************************************
int RTC_SetSubsecondAlarm(mxc_rtc_regs_t *rtc, uint32_t rssa)
{
    // ras can only be written if BUSY = 0 & (RTCE = 0 or ASE = 0);

    if(RTC_DisableSubsecondInterrupt(rtc) == E_BUSY) {
        return E_BUSY;
    }

    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    rtc->rssa =  (rssa << MXC_F_RTC_RSSA_RSSA_POS) & MXC_F_RTC_RSSA_RSSA;

    if(RTC_EnableSubsecondInterrupt(rtc) == E_BUSY) {
        return E_BUSY;
    }

    return E_SUCCESS;
}


// *****************************************************************************
int RTC_EnableRTCE(mxc_rtc_regs_t *rtc)
{
    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    rtc->ctrl |= MXC_F_RTC_CTRL_WE;       // Allow writing to registers
    if (RTC_CheckBusy()) {
        return E_BUSY;
    }
    // Can only write if WE=1 and BUSY=0
    rtc->ctrl |= MXC_F_RTC_CTRL_RTCE;    // setting RTCE = 1
    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    rtc->ctrl &= ~MXC_F_RTC_CTRL_WE;       // Prevent Writing...

    return E_SUCCESS;
}

// *****************************************************************************
int RTC_DisableRTCE(mxc_rtc_regs_t *rtc)
{
    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    rtc->ctrl |= MXC_F_RTC_CTRL_WE;      // Allow writing to registers
    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    // Can only write if WE=1 and BUSY=0
    rtc->ctrl &= ~MXC_F_RTC_CTRL_RTCE;  // setting RTCE = 0
    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    rtc->ctrl &= ~MXC_F_RTC_CTRL_WE;       // Prevent Writing...

    return E_SUCCESS;
}


// *****************************************************************************
int RTC_Init(mxc_rtc_regs_t *rtc, uint32_t sec, uint8_t ssec, sys_cfg_rtc_t *sys_cfg)
{
#if((TARGET == 32650) || (TARGET == 32660))
    SYS_ClockEnable_X32K(sys_cfg);
#else
    SYS_RTCClockEnable(sys_cfg);
#endif

    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    rtc->ctrl = MXC_F_RTC_CTRL_WE;        //  Allow Writes
    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    rtc->ctrl = RTC_CTRL_RESET_DEFAULT;  // Start with a Clean Register
    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    rtc->ctrl |= MXC_F_RTC_CTRL_WE;      // Set Write Enable, allow writing to reg.
    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    rtc->ssec = ssec;
    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    rtc->sec = sec;
    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    rtc->ctrl &= ~MXC_F_RTC_CTRL_WE;       // Prevent Writing...

    return E_SUCCESS;
}

// *****************************************************************************
int RTC_SquareWave(mxc_rtc_regs_t *rtc, rtc_sqwave_en_t sqe, rtc_freq_sel_t ft,
                   rtc_osc_mode_t x32kmd, const sys_cfg_rtc_t* sys_cfg)
{

    SYS_RTC_SqwavInit(sys_cfg);  // Set the Output pins for the squarewave.

    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    rtc->ctrl |= MXC_F_RTC_CTRL_WE;   // Allow writing to registers

    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    if (sqe == SQUARE_WAVE_ENABLED) {
        if (ft == F_32KHZ){        // if 32KHz output is selected...
            rtc->oscctrl |= MXC_F_RTC_OSCCTRL_OUT32K;   // Enable 32KHz wave
            if (RTC_CheckBusy()) {
                return E_BUSY;
            }
            rtc->ctrl |= MXC_F_RTC_CTRL_SQE;                  // Enable output on the pin
        } else {                  // if 1Hz, 512Hz, 4KHz output is selected

            rtc->oscctrl &= ~MXC_F_RTC_OSCCTRL_OUT32K;  // Must make sure that the 32KHz is disabled
            if (RTC_CheckBusy()) {
                return E_BUSY;
            }
            rtc->ctrl &= ~(MXC_F_RTC_CTRL_FT | MXC_F_RTC_CTRL_X32KMD);
            if (RTC_CheckBusy()) {
                return E_BUSY;
            }
            rtc->ctrl |= (MXC_F_RTC_CTRL_SQE | ft | x32kmd);  // Enable Sq. wave,
        }

        if (RTC_CheckBusy()) {
            return E_BUSY;
        }
        rtc->ctrl |= MXC_F_RTC_CTRL_RTCE;     // Enable Real Time Clock
    } else { // Turn off the square wave output on the pin

        rtc->oscctrl &= ~MXC_F_RTC_OSCCTRL_OUT32K;     // Must make sure that the 32KHz is disabled
        if (RTC_CheckBusy()) {
            return E_BUSY;
        }
        rtc->ctrl &= ~MXC_F_RTC_CTRL_SQE;  // No sq. wave output
    }

    if (RTC_CheckBusy()) {
        return E_BUSY;
    }
    rtc->ctrl &= ~MXC_F_RTC_CTRL_WE;       // Disable Writing to register

    return E_SUCCESS;
}

// *****************************************************************************
int RTC_Trim(mxc_rtc_regs_t *rtc, int8_t trim)
{

    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    rtc->ctrl |= MXC_F_RTC_CTRL_WE;

    if (RTC_CheckBusy()) {
        return E_BUSY;
    }

    MXC_SETFIELD(rtc->trim, MXC_F_RTC_TRIM_TRIM, trim << MXC_F_RTC_TRIM_TRIM_POS);

    if (RTC_CheckBusy()) {
        return E_BUSY;
    }
    rtc->ctrl &= ~MXC_F_RTC_CTRL_WE;       // Disable Writing to register

    return E_SUCCESS;
}

// *****************************************************************************
int RTC_CheckBusy(void)
{
    // Time-out transfer if it takes > BUSY_TIMEOUT microseconds
    mxc_delay_start(MXC_DELAY_USEC(BUSY_TIMEOUT));
    while (RTC_IS_BUSY) {
        if (mxc_delay_check() != E_BUSY){
            return E_BUSY;
        }
    }
    mxc_delay_stop();
    return E_SUCCESS;
}

// *****************************************************************************
int RTC_GetFlags(void)
{
    return MXC_RTC->ctrl & (MXC_F_RTC_CTRL_ALDF | MXC_F_RTC_CTRL_ALSF | MXC_F_RTC_CTRL_RDY);
}

// *****************************************************************************
int RTC_ClearFlags(int flags)
{
    if (RTC_CheckBusy()) {
        return E_BUSY;
    }
    MXC_RTC->ctrl &= ~(flags & (MXC_F_RTC_CTRL_ALDF | MXC_F_RTC_CTRL_ALSF | MXC_F_RTC_CTRL_RDY));

    return E_SUCCESS;
}

// *****************************************************************************
int RTC_GetSubSecond(void)
{
#if TARGET == 32650
    int ssec;
    if(ChipRevision > 0xA1){
        ssec = ((MXC_PWRSEQ->lpcn >> 12)& 0xF00) | (MXC_RTC->ssec & 0xFF);
    }else{
        ssec = MXC_RTC->ssec;
    }
        return ssec;
#else
    return MXC_RTC->ssec;
#endif
}

// *****************************************************************************
int RTC_GetSecond(void)
{
    return MXC_RTC->sec;
}

// *****************************************************************************
int RTC_GetTime(uint32_t* sec, uint32_t* subsec)
{
    uint32_t temp_sec;
    do {
        // Check if an update is about to happen.
        if(!(MXC_RTC->ctrl & MXC_F_RTC_CTRL_RDY)) {
            return E_BUSY;
        }

        // Read the seconds count.
        temp_sec = RTC_GetSecond();

        // Check if an update is about to happen.
        if(!(MXC_RTC->ctrl & MXC_F_RTC_CTRL_RDY)) {
            return E_BUSY;
        }

        // Read the sub-seconds count.
        *subsec = RTC_GetSubSecond();

        // Check if an update is about to happen.
        if(!(MXC_RTC->ctrl & MXC_F_RTC_CTRL_RDY)) {
            return E_BUSY;
        }

        // Read the seconds count.
        *sec = RTC_GetSecond();

        // Repeat until a steady state is reached.
    } while (temp_sec != *sec);

    return E_NO_ERROR;
}

// *****************************************************************************
int RTC_IsEnabled(void)
{
    return RTC_IS_ENABLED;
}
