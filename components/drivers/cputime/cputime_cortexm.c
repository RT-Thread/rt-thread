/*
 * File      : cputime_cortexm.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
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
 * Date           Author            Notes
 * 2017-12-23     Bernard           first version
 */

#include <rthw.h>
#include <rtdevice.h>
#include <rtthread.h>

#include <board.h>

/* Use Cycle counter of Data Watchpoint and Trace Register for CPU time */

static float cortexm_cputime_getres(void)
{
    float ret = 1000 * 1000 * 1000;
    
    ret = ret / SystemCoreClock;
    return ret;
}

static uint32_t cortexm_cputime_gettime(void)
{
    return DWT->CYCCNT;
}

const static struct rt_clock_cputime_ops _cortexm_ops = 
{
    cortexm_cputime_getres,
    cortexm_cputime_gettime
};

int cortexm_cputime_init(void)
{
    /* check support bit */
    if ((DWT->CTRL & (1UL << DWT_CTRL_NOCYCCNT_Pos)) == 0) 
    {
        /* enable trace*/
        CoreDebug->DEMCR |= (1UL << CoreDebug_DEMCR_TRCENA_Pos);
        
        /* whether cycle counter not enabled */
        if ((DWT->CTRL & (1UL << DWT_CTRL_CYCCNTENA_Pos)) == 0) 
        {
            /* enable cycle counter */
            DWT->CTRL |= (1UL << DWT_CTRL_CYCCNTENA_Pos);
        }

        clock_cpu_setops(&_cortexm_ops);
    }

    return 0;
}
INIT_BOARD_EXPORT(cortexm_cputime_init);
