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

    dfs_seq_printf(seq, "%-16s%8d KB\n", "MemMaxUsed:", max_used / 1024);
    dfs_seq_printf(seq, "%-16s%8d KB\n", "MemAvailable:", (total - used) / 1024);
    dfs_seq_printf(seq, "%-16s%8d KB\n", "Cached:", 0);
    dfs_seq_printf(seq, "%-16s%8d KB\n", "SReclaimable:", 0);

    rt_page_get_info(&total, &freed);
    total_sum = total_sum + total * RT_MM_PAGE_SIZE;
    total_freed = total_freed + freed * RT_MM_PAGE_SIZE;

    dfs_seq_printf(seq, "%-16s%8d KB\n", "MemTotal:", total_sum / 1024);
    dfs_seq_printf(seq, "%-16s%8d KB\n", "MemFree:", total_freed / 1024);
    dfs_seq_printf(seq, "%-16s%8d KB\n", "LowPageTotal:", total * RT_MM_PAGE_SIZE / 1024);
    dfs_seq_printf(seq, "%-16s%8d KB\n", "lowPageFree:", freed * RT_MM_PAGE_SIZE/ 1024);

    rt_page_high_get_info(&total, &freed);

    dfs_seq_printf(seq, "%-16s%8d KB\n", "HighPageTotal:", total * RT_MM_PAGE_SIZE / 1024);
    dfs_seq_printf(seq, "%-16s%8d KB\n", "HighPageFree:", freed * RT_MM_PAGE_SIZE / 1024);

    return 0;
}

int proc_meminfo_init(void)
{
    struct proc_dentry *dentry = proc_create_single_data("meminfo", 0, NULL, single_show, NULL);
    proc_release(dentry);

    return 0;
}
INIT_ENV_EXPORT(proc_meminfo_init);
