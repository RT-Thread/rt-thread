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
    rt_size_t total, used, max_used, freed;
    rt_size_t total_sum = 0;
    rt_size_t total_freed = 0;

    rt_memory_info(&total, &used, &max_used);
    total_sum = total_sum + total;
    total_freed = total_freed + total - used;

    dfs_seq_printf(seq, "%-16s%8lu kB\n", "MemMaxUsed:", (unsigned long)(max_used / 1024));
    dfs_seq_printf(seq, "%-16s%8lu kB\n", "MemAvailable:", (unsigned long)((total - used) / 1024));

    rt_page_get_info(&total, &freed);
    total_sum = total_sum + total * RT_MM_PAGE_SIZE;
    total_freed = total_freed + freed * RT_MM_PAGE_SIZE;

    dfs_seq_printf(seq, "%-16s%8lu kB\n", "MemTotal:", (unsigned long)(total_sum / 1024));
    dfs_seq_printf(seq, "%-16s%8lu kB\n", "MemFree:", (unsigned long)(total_freed / 1024));
    dfs_seq_printf(seq, "%-16s%8lu kB\n", "Buffers:", 0UL);
    dfs_seq_printf(seq, "%-16s%8lu kB\n", "Cached:", 0UL);
    dfs_seq_printf(seq, "%-16s%8lu kB\n", "SwapCached:", 0UL);
    dfs_seq_printf(seq, "%-16s%8lu kB\n", "SwapTotal:", 0UL);
    dfs_seq_printf(seq, "%-16s%8lu kB\n", "SwapFree:", 0UL);
    dfs_seq_printf(seq, "%-16s%8lu kB\n", "LowPageTotal:", (unsigned long)(total * RT_MM_PAGE_SIZE / 1024));
    dfs_seq_printf(seq, "%-16s%8lu kB\n", "LowPageFree:", (unsigned long)(freed * RT_MM_PAGE_SIZE / 1024));

    rt_page_high_get_info(&total, &freed);

    dfs_seq_printf(seq, "%-16s%8lu kB\n", "HighPageTotal:", (unsigned long)(total * RT_MM_PAGE_SIZE / 1024));
    dfs_seq_printf(seq, "%-16s%8lu kB\n", "HighPageFree:", (unsigned long)(freed * RT_MM_PAGE_SIZE / 1024));

    return 0;
}

int proc_meminfo_init(void)
{
    struct proc_dentry *dentry = proc_create_single_data("meminfo", 0, NULL, single_show, NULL);
    proc_release(dentry);

    return 0;
}
INIT_ENV_EXPORT(proc_meminfo_init);
