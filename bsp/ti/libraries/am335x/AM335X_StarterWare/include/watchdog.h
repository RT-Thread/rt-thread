/**
 *  \file   watchdog.h
 *
 *  \brief  Watchdog timer APIs and macros.
 *
 *   This file contains the driver API prototypes and macro definitions.
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#ifndef __WDT_H__
#define __WDT_H__

#include "hw_watchdog.h"

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
/*
** Values that can be passed to WatchdogTimerPreScalerClkEnable API as ptv.
*/
/* Divide functional clock by 1 */
#define WDT_PRESCALER_CLK_DIV_1        (0x00000000u)

/* Divide functional clock by 2 */
#define WDT_PRESCALER_CLK_DIV_2        (0x00000004u)

/* Divide functional clock by 4 */
#define WDT_PRESCALER_CLK_DIV_4        (0x00000008u)

/* Divide functional clock by 8 */
#define WDT_PRESCALER_CLK_DIV_8        (0x0000000Cu)

/* Divide functional clock by 16 */
#define WDT_PRESCALER_CLK_DIV_16       (0x00000010u)

/* Divide functional clock by 32 */
#define WDT_PRESCALER_CLK_DIV_32       (0x00000014u)

/* Divide functional clock by 64 */
#define WDT_PRESCALER_CLK_DIV_64       (0x00000018u)

/* Divide functional clock by 128 */
#define WDT_PRESCALER_CLK_DIV_128      (0x0000001Cu)

/*****************************************************************************/
/*
** Values that can be passed to WatchdogTimerIntRawStatusSet,
** WatchdogTimerIntStatusClear APIs as intFlags.
** These values can also be used to read the status obatined from 
** WatchdogTimerIntRawStatusGet, WatchdogTimerIntStatusGet APIs.
** These values can also be combined together and passed.
** For e.g. (WDT_INT_DELAY | WDT_INT_OVERFLOW)
*/
/* Watchdog delay interrupt */
#define WDT_INT_DELAY                   (WDT_WIRQSTATRAW_EVENT_DLY)

/* Watchdog overflow interrupt */
#define WDT_INT_OVERFLOW                (WDT_WIRQSTATRAW_EVENT_OVF)

/*****************************************************************************/
/*
** Values that can be passed to WatchdogTimerIntEnable as intFlags.
** These values can also be used to read the status obtained from 
** WatchdogTimerIntEnableStatusGet API.
** These values can also be combined together and passed.
** For e.g. (WDT_INT_ENABLE_DELAY | WDT_INT_ENABLE_OVRFLW)
*/
/* Enable delay interrupt */
#define WDT_INT_ENABLE_DELAY           (WDT_WIRQENSET_ENABLE_DLY)

/* Enable overflow interrupt */
#define WDT_INT_ENABLE_OVRFLW          (WDT_WIRQENSET_ENABLE_OVF)

/*****************************************************************************/
/*
** Values that can be passed to WatchdogTimerIntDisable as intFlags.
** These values can also be combined together and passed.
** For e.g. (WDT_INT_DISABLE_DELAY | WDT_INT_DISABLE_OVRFLW)
*/
/* Enable delay interrupt */
#define WDT_INT_DISABLE_DELAY           (WDT_WIRQENCLR_ENABLE_DLY)

/* Enable overflow interrupt */
#define WDT_INT_DISABLE_OVRFLW          (WDT_WIRQENCLR_ENABLE_OVF)

/*****************************************************************************/
/*
** Values that can be used to read the status obtained from 
** WatchdogTimerWritePostedStatusGet API.
** These values can also be combined while reading.
** For e.g. (WDT_WRITE_PENDING_WCLR | WDT_WRITE_PENDING_WCRR)
*/
/* Write pending for register WDT_WCLR */
#define WDT_WRITE_PENDING_WCLR          (WDT_WWPS_W_PEND_WCLR)

/* Write pending for register WDT_WCRR */
#define WDT_WRITE_PENDING_WCRR          (WDT_WWPS_W_PEND_WCRR)

/* Write pending for register WDT_WLDR */
#define WDT_WRITE_PENDING_WLDR          (WDT_WWPS_W_PEND_WLDR)

/* Write pending for register WDT_WTGR */
#define WDT_WRITE_PENDING_WTGR          (WDT_WWPS_W_PEND_WTGR)

/* Write pending for register WDT_WSPR */
#define WDT_WRITE_PENDING_WSPR          (WDT_WWPS_W_PEND_WSPR)

/* Write pending for register WDT_WDLY */
#define WDT_WRITE_PENDING_WDLY          (WDT_WWPS_W_PEND_WDLY)



/***************************************************************************/
/*
** Watchdog timer API prototypes 
*/
extern void WatchdogTimerEnable(unsigned int baseAdd);
extern void WatchdogTimerDisable(unsigned int baseAdd);
extern unsigned int WatchdogTimerRevisionIDGet(unsigned int baseAdd);
extern void WatchdogTimerReset(unsigned int baseAdd);
extern void WatchdogTimerPreScalerClkEnable(unsigned int baseAdd, unsigned int ptv);
extern void WatchdogTimerPreScalerClkDisable(unsigned int baseAdd);
extern void WatchdogTimerCounterSet(unsigned int baseAdd, unsigned int countVal);
extern unsigned int WatchdogTimerCounterGet(unsigned int baseAdd);
extern void WatchdogTimerReloadSet(unsigned int baseAdd, unsigned int reloadVal);
extern unsigned int WatchdogTimerReloadGet(unsigned int baseAdd);
extern void WatchdogTimerTriggerSet(unsigned int baseAdd, unsigned int trigVal);
extern void WatchdogTimerDelaySet(unsigned int baseAdd, unsigned int delayVal);
extern unsigned int WatchdogTimerDelayGet(unsigned int baseAdd);
extern void WatchdogTimerIntRawStatusSet(unsigned int baseAdd, unsigned int intFlags);
extern unsigned int WatchdogTimerIntRawStatusGet(unsigned int baseAdd);
extern unsigned int WatchdogTimerIntStatusGet(unsigned int baseAdd);
extern void WatchdogTimerIntStatusClear(unsigned int baseAdd, unsigned int intFlags);
extern void WatchdogTimerIntEnable(unsigned int baseAdd, unsigned int intFlags);
extern unsigned int WatchdogTimerIntEnableStatusGet(unsigned int baseAdd);
extern void WatchdogTimerIntDisable(unsigned int baseAdd, unsigned int intFlags);
extern unsigned int WatchdogTimerWritePostedStatusGet(unsigned int baseAdd, unsigned int flags);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/




















