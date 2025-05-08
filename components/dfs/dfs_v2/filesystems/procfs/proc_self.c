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

#if defined(RT_USING_SMART)

#include <lwp.h>


int proc_self_readlink(struct proc_dentry *dentry, char *buf, int len)
{
    struct rt_lwp *lwp  = RT_NULL;

    lwp = lwp_self();
    if (lwp)
    {
        rt_snprintf(buf, len, "%d", lwp_to_pid(lwp));
        buf[len - 1] = 0;
        return rt_strlen(buf);
    }
    else
    {
        rt_snprintf(buf, len, "null");
        buf[len - 1] = 0;
        return rt_strlen(buf);
    }

    return -1;
}

static const struct proc_ops proc_pid_fd_ops = {
    .readlink = proc_self_readlink,
};

int proc_self_init(void)
{
    struct proc_dentry *ent;

    ent = proc_symlink("self", NULL, "NULL");
    if (ent)
    {
        ent->ops = &proc_pid_fd_ops;
    }
    proc_release(ent);

    return 0;
}
INIT_ENV_EXPORT(proc_self_init);

#endif
