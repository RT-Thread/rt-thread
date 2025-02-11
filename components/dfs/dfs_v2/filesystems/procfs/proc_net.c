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

#ifdef RT_USING_LWIP
#include "lwip/opt.h"
#endif

#if LWIP_ROUTE
extern int inet_route_foreach(void (*func)(const char *name, uint32_t ip_addr, uint32_t netmask, void *parameter), void *parameter);
#endif

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

static void route_show(const char *name, uint32_t ip_addr, uint32_t netmask, void *parameter)
{
    struct dfs_seq_file *seq = (struct dfs_seq_file *)parameter;
    /* "Iface\tDestination\tGateway "
        "\tFlags\tRefCnt\tUse\tMetric\tMask\t\tMTU"
        "\tWindow\tIRTT"); */
    /* "%63s%lx%lx%X%d%d%d%lx%d%d%d\n" */
    dfs_seq_printf(seq, "%s ", name);
    dfs_seq_printf(seq, "%lx ", ip_addr);
    dfs_seq_printf(seq, "%lx ", 0);
    dfs_seq_printf(seq, "%X ", 1);
    dfs_seq_printf(seq, "%d ", 0);
    dfs_seq_printf(seq, "%d ", 0);
    dfs_seq_printf(seq, "%d ", 0);
    dfs_seq_printf(seq, "%lx ", netmask);
    dfs_seq_printf(seq, "%d ", 0);
    dfs_seq_printf(seq, "%d ", 0);
    dfs_seq_printf(seq, "%d\n", 0);
}

static int seq_show(struct dfs_seq_file *seq, void *data)
{
    /* data: The return value of the start or next*/
    dfs_seq_printf(seq, "\n");
#if LWIP_ROUTE
    inet_route_foreach(route_show, seq);
#endif

    return 0;
}

static const struct dfs_seq_ops seq_ops = {
    .start  = seq_start,
    .stop   = seq_stop,
    .next   = seq_next,
    .show   = seq_show,
};

int proc_net_init(void)
{
    struct proc_dentry *dentry;

    dentry = proc_mkdir("net", NULL);
    if (!dentry)
        return -1;

    proc_release(dentry);

    dentry = proc_create_data("net/route", 0, NULL, NULL, NULL);
    if (dentry)
    {
        dentry->seq_ops = &seq_ops;
    }
    proc_release(dentry);

    return 0;
}
INIT_ENV_EXPORT(proc_net_init);
