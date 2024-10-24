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
    dfs_seq_printf(seq, "%lu.%02lu %lu.%02lu\n",
                   (unsigned long)rt_tick_get_millisecond() / 1000, (unsigned long)(rt_tick_get_millisecond() % 1000) / 100,
                   (unsigned long)rt_tick_get_millisecond() / 1000, (unsigned long)(rt_tick_get_millisecond() % 1000) / 100);

    return 0;
}

int proc_uptime_init(void)
{
    struct proc_dentry *dentry = proc_create_single_data("uptime", 0, NULL, single_show, NULL);
    proc_release(dentry);

    return 0;
}
INIT_ENV_EXPORT(proc_uptime_init);
