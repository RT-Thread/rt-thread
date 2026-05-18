/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2026-04-21     rcitach        init ver.
 */
#include "vdso_user_internal.h"

static int rt_vdso_resolve_clock_index(clockid_t clock, unsigned int *index)
{
    switch (clock)
    {
    case CLOCK_REALTIME:
    case CLOCK_REALTIME_COARSE:
        *index = RT_VDSO_CLOCK_REALTIME_INDEX;
        return 0;

    case CLOCK_MONOTONIC:
    case CLOCK_MONOTONIC_COARSE:
    case CLOCK_MONOTONIC_RAW:
    case CLOCK_BOOTTIME:
        *index = RT_VDSO_CLOCK_MONOTONIC_INDEX;
        return 0;

    default:
        if ((unsigned int)clock >= RT_VDSO_CLOCK_ID_MAX)
        {
            return -EINVAL;
        }
        return -ENOSYS;
    }
}

int rt_vdso_clock_gettime_impl(clockid_t clock, struct timespec *ts)
{
    const struct rt_vdso_data_page *data_page = rt_vdso_get_data_page();
    uint32_t seq;
    unsigned int index;
    uint64_t last;
    uint64_t freq;
    uint64_t now;
    uint64_t delta_ns;
    struct timespec base_time;
    int ret;

    ret = rt_vdso_resolve_clock_index(clock, &index);
    if (ret != 0)
    {
        return ret;
    }

    do
    {
        seq = rt_vdso_data_read_begin(data_page);
        if (index == RT_VDSO_CLOCK_REALTIME_INDEX &&
            !(data_page->flags & RT_VDSO_FLAG_REALTIME_VALID))
        {
            return -ENOSYS;
        }
        base_time = data_page->base_time[index];
        last = data_page->counter_last;
        freq = data_page->counter_freq;
        now = rt_vdso_arch_read_counter();
    } while (unlikely(rt_vdso_data_read_retry(data_page, seq)));

    if (freq == 0)
    {
        return -ENOSYS;
    }

    delta_ns = rt_vdso_counter_delta_to_ns(now, last, freq);
    rt_vdso_timespec_add_nanoseconds(&base_time, delta_ns);
    *ts = base_time;

    return 0;
}

int __vdso_clock_gettime(clockid_t clock, struct timespec *ts)
    __attribute__((alias("rt_vdso_clock_gettime_impl"), visibility("default")));

int __kernel_clock_gettime(clockid_t clock, struct timespec *ts)
    __attribute__((alias("rt_vdso_clock_gettime_impl"), visibility("default")));
