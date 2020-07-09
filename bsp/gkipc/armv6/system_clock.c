/*
 * File      : clock.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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


