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

#ifdef RT_USING_SMART
#include "lwp_pid.h"
#ifdef RT_USING_MUSLLIBC
#include "lwp.h"
#endif
#endif

#ifdef RT_USING_SMART
struct loadavg_count
{
    int total;
    int runnable;
};

static int loadavg_count_pid(pid_t pid, void *arg)
{
    struct loadavg_count *count = (struct loadavg_count *)arg;
    struct rt_lwp *lwp = lwp_from_pid_locked(pid);

    if (!lwp)
    {
        return 0;
    }
    count->total++;
#ifdef RT_USING_MUSLLIBC
    {
        rt_list_t *node;

        node = lwp->t_grp.next;
        while (node != &lwp->t_grp)
        {
            rt_thread_t thread = rt_list_entry(node, struct rt_thread, sibling);
            if (RT_SCHED_CTX(thread).stat == RT_THREAD_RUNNING)
            {
                count->runnable++;
                break;
            }
            node = node->next;
        }
    }
#endif
    return 0;
}
#endif

static int single_show(struct dfs_seq_file *seq, void *data)
{
#ifdef RT_USING_SMART
    struct loadavg_count count = {0, 0};

    lwp_pid_for_each(loadavg_count_pid, &count);
    dfs_seq_printf(seq, "0.00 0.00 0.00 %d/%d 0\n", count.runnable, count.total);
#else
    dfs_seq_puts(seq, "0.00 0.00 0.00 0/0 0\n");
#endif

    return 0;
}

int proc_loadavg_init(void)
{
    struct proc_dentry *dentry = proc_create_single_data("loadavg", 0, NULL, single_show, NULL);
    proc_release(dentry);

    return 0;
}
INIT_ENV_EXPORT(proc_loadavg_init);
