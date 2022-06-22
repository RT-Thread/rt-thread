/* *****************************************************************************
 * Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
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
 * $Date: 2018-12-18 15:37:22 -0600 (Tue, 18 Dec 2018) $
 * $Revision: 40072 $
 *
 **************************************************************************** */

/* **** Includes **** */
#include "mxc_config.h"
#include "mxc_errors.h"
#include "mxc_assert.h"
#include "mxc_sys.h"
#include "wdt.h"

/* **** Definitions **** */

/* **** Globals **** */

/* **** Functions **** */

/* ************************************************************************** */
int WDT_Init(mxc_wdt_regs_t* wdt, sys_cfg_wdt_t sys_cfg)
{
    SYS_WDT_Init(wdt, sys_cfg);

    return E_NO_ERROR;
}

/* ************************************************************************** */
void WDT_SetIntPeriod(mxc_wdt_regs_t* wdt, wdt_period_t period)
{
    MXC_SETFIELD(wdt->ctrl, MXC_F_WDT_CTRL_INT_PERIOD, period);
}

/* ************************************************************************** */
void WDT_SetResetPeriod(mxc_wdt_regs_t* wdt, wdt_period_t period)
{
    MXC_SETFIELD(wdt->ctrl, MXC_F_WDT_CTRL_RST_PERIOD, (period << (MXC_F_WDT_CTRL_RST_PERIOD_POS - MXC_F_WDT_CTRL_INT_PERIOD_POS)));
}

/* ************************************************************************** */
void WDT_Enable(mxc_wdt_regs_t* wdt, int enable)
{
    if (enable) {
        wdt->ctrl |= MXC_F_WDT_CTRL_WDT_EN;
    } else {
        wdt->ctrl &= ~(MXC_F_WDT_CTRL_WDT_EN);
    }
}

/* ************************************************************************** */
void WDT_EnableInt(mxc_wdt_regs_t* wdt, int enable)
{
    if (enable) {
        wdt->ctrl |= MXC_F_WDT_CTRL_INT_EN;
    } else {
        wdt->ctrl &= ~(MXC_F_WDT_CTRL_INT_EN);
    }
}

/* ************************************************************************** */
void WDT_EnableReset(mxc_wdt_regs_t* wdt, int enable)
{
    if (enable) {
        wdt->ctrl |= MXC_F_WDT_CTRL_RST_EN;
    } else {
        wdt->ctrl &= ~(MXC_F_WDT_CTRL_RST_EN);
    }
}

/* ************************************************************************** */
void WDT_ResetTimer(mxc_wdt_regs_t* wdt)
{
    wdt->rst = 0x00A5;
    wdt->rst = 0x005A;
}

/* ************************************************************************** */
int WDT_GetResetFlag(mxc_wdt_regs_t* wdt)
{
    return !!(wdt->ctrl & MXC_F_WDT_CTRL_RST_FLAG);
}

/* ************************************************************************** */
void WDT_ClearResetFlag(mxc_wdt_regs_t* wdt)
{
    wdt->ctrl &= ~(MXC_F_WDT_CTRL_RST_FLAG);
}

/* ************************************************************************** */
int WDT_GetIntFlag(mxc_wdt_regs_t* wdt)
{
    return !!(wdt->ctrl & MXC_F_WDT_CTRL_INT_FLAG);
}

/* ************************************************************************** */
void WDT_ClearIntFlag(mxc_wdt_regs_t* wdt)
{
    wdt->ctrl &= ~(MXC_F_WDT_CTRL_INT_FLAG);
}
