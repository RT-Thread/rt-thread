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


static void *seq_start(struct dfs_seq_file *seq, off_t *index)
{
    off_t i = *index; // seq->index

    return NULL + (i == 0);
}

static void seq_stop(struct dfs_seq_file *seq, void *data)
{
}

static void *seq_next(struct dfs_seq_file *seq, void *data, off_t *index)
{
    /* data: The return value of the start or next*/
    off_t i = *index + 1; // seq->index

    *index = i;

    return NULL;
}

static int seq_show(struct dfs_seq_file *seq, void *data)
{
    int i;
    rt_cpu_t pcpu;
    rt_uint64_t user_total = 0;
    rt_uint64_t system_total = 0;
    rt_uint64_t idle_total = 0;

    for (i = 0; i < RT_CPUS_NR; i++)
    {
        pcpu   = rt_cpu_index(i);
        user_total = user_total + pcpu->cpu_stat.user;
        system_total = system_total + pcpu->cpu_stat.system;
        idle_total = idle_total + pcpu->cpu_stat.idle;
    }
    dfs_seq_printf(seq, "cpu  %llu 0 %llu %llu 0 0 0 0 0 0\n", user_total, system_total, idle_total);

    for (i = 0; i < RT_CPUS_NR; i++)
    {
        pcpu   = rt_cpu_index(i);
        dfs_seq_printf(seq, "cpu%d ",i);
        dfs_seq_printf(seq, "%llu ",pcpu->cpu_stat.user);//user
        dfs_seq_printf(seq, "0 ");//nice
        dfs_seq_printf(seq, "%llu ",pcpu->cpu_stat.system);//system
        dfs_seq_printf(seq, "%llu ",pcpu->cpu_stat.idle);//idle
        dfs_seq_printf(seq, "0 ");//iowait
        dfs_seq_printf(seq, "0 ");//irq
        dfs_seq_printf(seq, "0 ");//softirq
        dfs_seq_printf(seq, "0 0 0\n");//steal,guest,guest_nice

    }

    return 0;
}

static const struct dfs_seq_ops seq_ops = {
    .start  = seq_start,
    .stop   = seq_stop,
    .next   = seq_next,
    .show   = seq_show,
};

rt_weak const struct dfs_seq_ops *stat_get_seq_ops(void)
{
    return &seq_ops;
}

static int proc_open(struct dfs_file *file)
{
    return dfs_seq_open(file, stat_get_seq_ops());
}

static int proc_close(struct dfs_file *file)
{
    return dfs_seq_release(file);
}

static const struct dfs_file_ops file_ops = {
    .open   = proc_open,
    .read   = dfs_seq_read,
    .lseek  = dfs_seq_lseek,
    .close  = proc_close,
};

int proc_stat_init(void)
{
    struct proc_dentry *dentry = proc_create_data("stat", 0, NULL, &file_ops, NULL);
    proc_release(dentry);

    return 0;
}
INIT_ENV_EXPORT(proc_stat_init);
