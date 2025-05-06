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
#include <dfs_fs.h>

static void *seq_start(struct dfs_seq_file *seq, off_t *index)
{
    off_t i = *index; // seq->index
    struct dfs_filesystem_type *fs = dfs_filesystems();

    if (fs)
    {
        while (i--)
        {
            fs = fs->next;
            if (!fs)
            {
                break;
            }
        }
    }

    return fs;
}

static void seq_stop(struct dfs_seq_file *seq, void *data)
{
}

static void *seq_next(struct dfs_seq_file *seq, void *data, off_t *index)
{
    /* data: The return value of the start or next*/
    off_t i = *index + 1; // seq->index
    struct dfs_filesystem_type *fs = (struct dfs_filesystem_type *)data;

    *index = i;

    return fs->next;
}

static int seq_show(struct dfs_seq_file *seq, void *data)
{
    /* data: The return value of the start or next*/
    struct dfs_filesystem_type *fs = (struct dfs_filesystem_type *)data;

    dfs_seq_printf(seq, "%-9s%s\n", (fs->fs_ops->flags == FS_NEED_DEVICE) ? "" : "nodev", fs->fs_ops->name);

    return 0;
}

static const struct dfs_seq_ops seq_ops = {
    .start  = seq_start,
    .stop   = seq_stop,
    .next   = seq_next,
    .show   = seq_show,
};

int proc_filesystems_init(void)
{
    struct proc_dentry *dentry = proc_create_data("filesystems", 0, NULL, NULL, NULL);
    if (dentry)
    {
        dentry->seq_ops = &seq_ops;
    }
    proc_release(dentry);

    return 0;
}
INIT_ENV_EXPORT(proc_filesystems_init);
