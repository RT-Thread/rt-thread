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
#include <mm_page.h>


extern void rt_memory_info(rt_size_t *total,
                            rt_size_t *used,
                            rt_size_t *max_used);

static int single_show(struct dfs_seq_file *seq, void *data)
{
    dfs_seq_printf(seq, "0.13 0.16 0.17 1/1035 380436\n");

    return 0;
}

int proc_loadavg_init(void)
{
    struct proc_dentry *dentry = proc_create_single_data("loadavg", 0, NULL, single_show, NULL);
    proc_release(dentry);

    return 0;
}
INIT_ENV_EXPORT(proc_loadavg_init);
