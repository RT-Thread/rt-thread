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

static void mnt_escape(const char *source, char *target, rt_size_t target_size)
{
    rt_size_t offset = 0;
    const char *cursor = source ? source : "";

    if (target_size == 0)
    {
        return;
    }

    while (*cursor != '\0' && offset + 4 < target_size)
    {
        if (*cursor == ' ')
        {
            target[offset++] = '\\';
            target[offset++] = '0';
            target[offset++] = '4';
            target[offset++] = '0';
        }
        else if (*cursor == '\t')
        {
            target[offset++] = '\\';
            target[offset++] = '0';
            target[offset++] = '1';
            target[offset++] = '1';
        }
        else if (*cursor == '\n')
        {
            target[offset++] = '\\';
            target[offset++] = '0';
            target[offset++] = '1';
            target[offset++] = '2';
        }
        else if (*cursor == '\\')
        {
            target[offset++] = '\\';
            target[offset++] = '1';
            target[offset++] = '3';
            target[offset++] = '4';
        }
        else
        {
            target[offset++] = *cursor;
        }
        cursor++;
    }

    target[offset] = '\0';
}

const char *mnt_flag(int flag)
{
    if (flag & MNT_RDONLY)
    {
        return "ro";
    }

    return "rw";
}

static struct dfs_mnt* mnt_show(struct dfs_mnt *mnt, void *parameter)
{
    struct dfs_seq_file *seq = (struct dfs_seq_file *)parameter;
    char source[DFS_PATH_MAX];
    char target[DFS_PATH_MAX];
    const char *source_name;
    const char *filesystem_name;

    if (mnt && mnt->fs_ops && mnt->fullpath)
    {
        filesystem_name = mnt->fs_ops->name ? mnt->fs_ops->name : "unknown";
        source_name = filesystem_name;
        if (mnt->dev_id && mnt->dev_id->parent.name[0] != '\0')
        {
            source_name = mnt->dev_id->parent.name;
        }
        mnt_escape(source_name, source, sizeof(source));
        mnt_escape(mnt->fullpath, target, sizeof(target));
        dfs_seq_printf(seq, "%s %s %s %s 0 0\n", source, target,
                       filesystem_name, mnt_flag(mnt->flags));
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
