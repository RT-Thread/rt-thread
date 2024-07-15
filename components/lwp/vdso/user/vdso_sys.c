/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-07-04     rcitach        init ver.
 */

#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <stdbool.h>
#include <vdso_sys.h>

#ifndef rt_vdso_cycles_ready
static inline bool rt_vdso_cycles_ready(uint64_t cycles)
{
    return true;
}
#endif

#ifndef rt_vdso_get_ns
static inline
uint64_t rt_vdso_get_ns(uint64_t cycles, uint64_t last)
{
    return (cycles - last) * NSEC_PER_SEC / __arch_get_hw_frq();
}
#endif

static int
__rt_vdso_getcoarse(struct timespec *ts, clockid_t clock, const struct vdso_data *vdns)
{
    const struct vdso_data *vd;
    const struct timespec *vdso_ts;
    uint32_t seq;
    uint64_t sec, last, ns, cycles;

    if (clock != CLOCK_MONOTONIC_RAW)
        vd = &vdns[CS_HRES_COARSE];
    else
        vd = &vdns[CS_RAW];

    vdso_ts = &vd->basetime[clock];

    do {
        seq = rt_vdso_read_begin(vd);
        cycles = __arch_get_hw_counter(vd->clock_mode, vd);
        if (unlikely(!rt_vdso_cycles_ready(cycles)))
            return -1;
        ns = vdso_ts->tv_nsec;
        last = vd->cycle_last;
        ns += rt_vdso_get_ns(cycles, last);
        sec = vdso_ts->tv_sec;
    } while (unlikely(rt_vdso_read_retry(vd, seq)));

    ts->tv_sec = sec + __iter_div_u64_rem(ns, NSEC_PER_SEC, &ns);
    ts->tv_nsec = ns;

    return 0;
}

static inline int
__vdso_clock_gettime_common(const struct vdso_data *vd, clockid_t clock,
                 struct timespec *ts)
{
    u_int32_t msk;

    if (unlikely((u_int32_t) clock >= MAX_CLOCKS))
        return -1;

    msk = 1U << clock;
    if (likely(msk & VDSO_REALTIME))
        return __rt_vdso_getcoarse(ts,CLOCK_REALTIME,vd);
    else if (msk & VDSO_MONOTIME)
        return __rt_vdso_getcoarse(ts,CLOCK_MONOTONIC,vd);
    else
        return ENOENT;
}

static __maybe_unused int
rt_vdso_clock_gettime_data(const struct vdso_data *vd, clockid_t clock,
               struct timespec *ts)
{
    int ret = 0;
    ret = __vdso_clock_gettime_common(vd, clock, ts);
    return ret;
}

int
__kernel_clock_gettime(clockid_t clock, struct timespec *ts)
{
    return rt_vdso_clock_gettime_data(__arch_get_vdso_data(), clock, ts);
}
