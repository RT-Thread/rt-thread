/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fgeneric_timer.c
 * Date: 2022-02-10 14:53:41
 * LastEditTime: 2022-02-17 17:36:17
 * Description:  This file is for generic timer function port for driver
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2023/2/28   first release
 */

/***************************** Include Files *********************************/
#include <gtimer.h>

#include "fkernel.h"
#include "fassert.h"
#include "fgeneric_timer.h"

/************************** Constant Definitions *****************************/
#define CNTP_CTL_ENABLE     (1U << 0)    /* Enables the timer */
#define CNTP_CTL_IMASK      (1U << 1)    /* Timer interrupt mask bit */
#define CNTP_CTL_ISTATUS    (1U << 2)    /* The status of the timer */

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Function *****************************************/
u64 GenericTimerRead(void)
{
    return (u64)gtimer_get_current_value();
}

void GenericTimerStart(void)
{
    u32 ctrl = gtimer_get_control(); /* get CNTP_CTL */

    if (!(ctrl & CNTP_CTL_ENABLE))
    {
        ctrl |= CNTP_CTL_ENABLE; /* enable gtimer if off */
        gtimer_set_control(ctrl); /* set CNTP_CTL */
    }
}

void GenericTimerStop(void)
{
    u32 ctrl = gtimer_get_control(); /* get CNTP_CTL */
    if ((ctrl & CNTP_CTL_ENABLE))
    {
        ctrl &= ~CNTP_CTL_ENABLE; /* disable gtimer if on */
        gtimer_set_control(ctrl); /* set CNTP_CTL */
    }
}

u32 GenericTimerFrequecy(void)
{
    u32 rate = gtimer_get_counter_frequency(); /* get CNTFRQ bit[31:0] freq of system counter */
    FASSERT_MSG((rate > 1000000), "invalid freqency %ud", rate);
    return rate;
}

void GenericTimerCompare(u32 interval)
{
    /* set CNTP_CVAL, set compare value for physical timer */
    gtimer_set_load_value((rt_uint64_t)interval);
}

void GenericTimerInterruptEnable(void)
{
    u64 ctrl = gtimer_get_control();
    if (ctrl & CNTP_CTL_IMASK)
    {
        ctrl &= ~CNTP_CTL_IMASK;
        gtimer_set_control(ctrl);
    }
}