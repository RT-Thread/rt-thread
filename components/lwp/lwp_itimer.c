/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-30     Shell        Add itimer support
 */

#define _GNU_SOURCE
#include <sys/time.h>
#undef _GNU_SOURCE

#define DBG_TAG "lwp.signal"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <rthw.h>
#include <rtthread.h>
#include <string.h>

#include "lwp_internal.h"
#include "sys/signal.h"
#include "syscall_generic.h"

rt_err_t lwp_signal_setitimer(rt_lwp_t lwp, int which, const struct itimerspec *restrict new, struct itimerspec *restrict old)
{
    rt_err_t rc = RT_EOK;
    timer_t timerid = 0;
    int flags = 0;

    if (lwp->signal.real_timer == LWP_SIG_INVALID_TIMER)
    {
        struct sigevent sevp = {
            .sigev_signo = SIGALRM,
            .sigev_notify = SIGEV_SIGNAL,
        };

        rc = timer_create(CLOCK_REALTIME_ALARM, &sevp, &timerid);
        if (rc == RT_EOK)
        {
            RT_ASSERT(timerid != LWP_SIG_INVALID_TIMER);
            lwp->signal.real_timer = timerid;
        }
        else
        {
            /* failed to create timer */
        }
    }
    else
    {
        timerid = lwp->signal.real_timer;
    }

    if (rc == RT_EOK)
    {
        switch (which)
        {
            case ITIMER_REAL:
                rc = timer_settime(timerid, flags, new, old);
                break;
            default:
                rc = -ENOSYS;
                LOG_W("%s() unsupported timer", __func__);
                break;
        }
    }

    return rc;
}
