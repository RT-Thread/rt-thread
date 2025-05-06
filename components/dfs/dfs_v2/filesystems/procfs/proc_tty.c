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
    /* data: The return value of the start or next*/
    dfs_seq_puts(seq, "todo\n");

    return 0;
}

static const struct dfs_seq_ops seq_ops = {
    .start  = seq_start,
    .stop   = seq_stop,
    .next   = seq_next,
    .show   = seq_show,
};

void proc_tty_register_driver(void *driver)
{
    //todo
}

void proc_tty_unregister_driver(void *driver)
{
    //todo
}

int proc_tty_init(void)
{
    struct proc_dentry *dentry;

    dentry = proc_mkdir("tty", NULL);
    if (!dentry)
        return -1;

    proc_release(dentry);

    dentry = proc_mkdir("tty/ldisc", NULL);
    proc_release(dentry);

    dentry = proc_mkdir_mode("tty/driver", S_IRUSR|S_IXUSR, NULL);
    proc_release(dentry);

    dentry = proc_create_data("tty/ldiscs", 0, NULL, NULL, NULL);
    if (dentry)
    {
        dentry->seq_ops = &seq_ops;
    }
    proc_release(dentry);

    dentry = proc_create_data("tty/drivers", 0, NULL, NULL, NULL);
    if (dentry)
    {
        dentry->seq_ops = &seq_ops;
    }
    proc_release(dentry);

    return 0;
}
INIT_ENV_EXPORT(proc_tty_init);
