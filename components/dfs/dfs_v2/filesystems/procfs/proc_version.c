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


static int single_show(struct dfs_seq_file *seq, void *data)
{
    dfs_seq_puts(seq, "\n \\ | /\n");
#ifdef RT_USING_SMART
    dfs_seq_puts(seq, "- RT -     Thread Smart Operating System\n");
#else
    dfs_seq_puts(seq, "- RT -     Thread Operating System\n");
#endif
    dfs_seq_printf(seq, " / | \\     %d.%d.%d build %s %s\n",
                    (rt_int32_t)RT_VERSION_MAJOR, (rt_int32_t)RT_VERSION_MINOR, (rt_int32_t)RT_VERSION_PATCH,
                    __DATE__, __TIME__);
    dfs_seq_puts(seq, " 2006 - 2022 Copyright by RT-Thread team\n");

    return 0;
}

int proc_version_init(void)
{
    struct proc_dentry *dentry = proc_create_single_data("version", 0, NULL, single_show, NULL);
    proc_release(dentry);

    return 0;
}
INIT_ENV_EXPORT(proc_version_init);
