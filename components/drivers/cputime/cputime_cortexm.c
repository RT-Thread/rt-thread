/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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

static uint64_t cortexm_cputime_gettime(void)
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
