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
 * FilePath: fsleep.c
 * Date: 2022-02-10 14:53:41
 * LastEditTime: 2022-02-17 17:36:17
 * Description:  This file is for sleep function port for driver
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2023/2/28   first release
 */

/***************************** Include Files *********************************/
#include <gtimer.h>

#include "fassert.h"
#include "fsleep.h"
#include "fkernel.h"
/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Function *****************************************/
static u32 fsleep_general(u32 ticks, u32 div)
{
    u64 end_time;
    u64 cur_time;
    cur_time = rt_hw_get_gtimer_val();
    end_time = cur_time + ((u64)ticks * rt_hw_get_gtimer_frq() / div);

    do
    {
        cur_time = rt_hw_get_gtimer_val();
    }
    while (cur_time < end_time);

    return 0;
}

u32 fsleep_seconds(u32 seconds)
{
    return fsleep_general(seconds, 1);
}

u32 fsleep_millisec(u32 mseconds)
{
    return fsleep_general(mseconds, NANO_TO_MICRO);
}

u32 fsleep_microsec(u32 useconds)
{
    return fsleep_general(useconds, NANO_TO_KILO);
}