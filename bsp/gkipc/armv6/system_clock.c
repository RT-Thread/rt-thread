/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 *  Visit http://www.goke.com to get contact with Goke.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include "gk7101.h"
#include "board.h"

/**
 * @brief System Clock Configuration
 */
void rt_hw_clock_init(void)
{

}

void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint32_t     start_time = 0;
    rt_uint32_t     end_time = 0;
    int     time_difference  = 0;

    start_time = gkosGetTicks();
    do
    {
        end_time = gkosGetTicks();
        time_difference = (rt_uint32_t)(end_time - start_time);
        /* check overflow */
        if(start_time > end_time)
        {
            time_difference = ((time_difference < 0L) ? -time_difference : time_difference); /* C-LIB code for labs() */
        }
    }while(time_difference < (us/1000));

}


