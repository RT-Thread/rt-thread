/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "proc.h"
#include "procfs.h"

#include <rthw.h>
#include <rtdbg.h>

#include <fcntl.h>
#include <errno.h>

#include <dfs_dentry.h>


static int single_show(struct dfs_seq_file *seq, void *data)
{
    rt_tick_t ticks = rt_tick_get();
    rt_uint64_t uptime_ms;
    rt_uint64_t idle_ticks = 0;
    int index;

    uptime_ms = ((rt_uint64_t)ticks * 1000U) / RT_TICK_PER_SECOND;
#ifdef RT_USING_SMP
    for (index = 0; index < RT_CPUS_NR; index++)
    {
        idle_ticks += rt_cpu_index(index)->cpu_stat.idle;
    }
#else
    idle_ticks = rt_cpu_index(0)->cpu_stat.idle;
#endif
    dfs_seq_printf(seq, "%llu.%02llu %llu.%02llu\n",
                   uptime_ms / 1000U, (uptime_ms % 1000U) / 10U,
                   ((rt_uint64_t)idle_ticks * 1000U) / RT_TICK_PER_SECOND / 1000U,
                   (((rt_uint64_t)idle_ticks * 1000U) / RT_TICK_PER_SECOND % 1000U) / 10U);

    return 0;
}

int proc_uptime_init(void)
{
    struct proc_dentry *dentry = proc_create_single_data("uptime", 0, NULL, single_show, NULL);
    proc_release(dentry);

    return 0;
}
INIT_ENV_EXPORT(proc_uptime_init);
