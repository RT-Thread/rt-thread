/*******************************************************************************
*
* Copyright 2013 - 2016, Freescale Semiconductor, Inc.
* Copyright 2016-2019 NXP
*
* This software is owned or controlled by NXP and may only be used
* strictly in accordance with the applicable license terms.  By expressly
* accepting such terms or by downloading, installing, activating and/or
* otherwise using the software, you are agreeing that you have read, and
* that you agree to comply with and are bound by, such license terms.  If
* you do not agree to be bound by the applicable license terms, then you
* may not retain, install, activate or otherwise use the software.
*
*
*******************************************************************************/

#include "safety_config.h"

/*******************************************************************************
* Prototypes
******************************************************************************/
extern void common_startup(void);
extern int main(void);

extern void WatchdogEnable(RTWDOG_Type *WDOGx, unsigned long timeout);
extern void WatchdogDisable(RTWDOG_Type *WDOGx);

/*******************************************************************************
* Code
******************************************************************************/
/*!
* @brief Device Start
*
* @param void
*
* @return None
*
* This function sets up watchdog, calls all of the needed starup routines and then
* branches to the main process.
*/
void start(void)
{
    /* Update of watchdog configuration */
#ifdef WATCHDOG_ON
    WatchdogEnable(RTWDOG, WATCHDOG_TIMEOUT_VALUE);
#else
    WatchdogDisable(RTWDOG);
#endif

    /* Copy any vector or data sections that need to be in RAM */
    common_startup();

    /* Jump to main process */
    main();

    /* No actions to perform after this so wait forever */
    while(1);
}
