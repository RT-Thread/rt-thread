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
#include <dfs_mnt.h>


const char *mnt_flag(int flag)
{
    /*if (flag & MNT_READONLY)
    {
        return "ro";
    }*/

    return "rw";
}

static struct dfs_mnt* mnt_show(struct dfs_mnt *mnt, void *parameter)
{
    struct dfs_seq_file *seq = (struct dfs_seq_file *)parameter;

    if (mnt)
    {
        if (mnt->dev_id)
        {
            dfs_seq_printf(seq, "%s %s %s %s 0 0\n", mnt->dev_id->parent.name, mnt->fullpath,
                            mnt->fs_ops->name, mnt_flag(mnt->flags));
        }
        else
        {
            dfs_seq_printf(seq, "%s %s %s %s 0 0\n", mnt->fs_ops->name, mnt->fullpath,
                            mnt->fs_ops->name, mnt_flag(mnt->flags));
        }
    }

    return RT_NULL;
}

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
    dfs_mnt_foreach(mnt_show, seq);

    return 0;
}

static const struct dfs_seq_ops seq_ops = {
    .start  = seq_start,
    .stop   = seq_stop,
    .next   = seq_next,
    .show   = seq_show,
};

int proc_mounts_init(void)
{
    struct proc_dentry *dentry = proc_create_data("mounts", 0, NULL, NULL, NULL);
    if (dentry)
    {
        dentry->seq_ops = &seq_ops;
    }
    proc_release(dentry);

    return 0;
}
INIT_ENV_EXPORT(proc_mounts_init);
