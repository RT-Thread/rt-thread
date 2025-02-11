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

static char *__proc_cmdline = NULL;

int proc_cmdline_save(const char *cmdline)
{
    if (__proc_cmdline)
    {
        free(__proc_cmdline);
        __proc_cmdline = NULL;
    }

    __proc_cmdline = strdup(cmdline);

    return 0;
}

static int single_show(struct dfs_seq_file *seq, void *data)
{
    if (__proc_cmdline)
    {
        dfs_seq_puts(seq, __proc_cmdline);
    }

    return 0;
}

int proc_cmdline_init(void)
{
    struct proc_dentry *dentry = proc_create_single_data("cmdline", 0, NULL, single_show, NULL);
    proc_release(dentry);

    return 0;
}
INIT_ENV_EXPORT(proc_cmdline_init);
