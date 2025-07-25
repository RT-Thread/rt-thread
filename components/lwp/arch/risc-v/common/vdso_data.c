/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2025-04-22     ScuDays        Add VDSO functionality under the riscv64 architecture.
 */

#include <rtthread.h>
#include <ktime.h>
#include <time.h>
#include <vdso_datapage.h>
#include <vdso_data.h>
#include <encoding.h>

void rt_vdso_update_glob_time(void)
{
    struct vdso_data *vdata = get_k_vdso_data();
    struct timespec  *vdso_ts;
    uint64_t          initdata = vdata->realtime_initdata;
    rt_vdso_write_begin(vdata);

    vdso_ts = &vdata[CS_HRES_COARSE].basetime[CLOCK_REALTIME];
    rt_ktime_boottime_get_ns(vdso_ts);
    vdso_ts->tv_sec = initdata + vdso_ts->tv_sec;

    vdso_ts = &vdata[CS_HRES_COARSE].basetime[CLOCK_MONOTONIC];
    rt_ktime_boottime_get_ns(vdso_ts);

    vdata->cycle_last = rdtime();
    rt_vdso_write_end(vdata);
}
