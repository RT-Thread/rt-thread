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
#include "lwp.h"
#include "lwp_pid.h"
#endif

#ifdef RT_USING_SMART
struct loadavg_count
{
    int total;
    int runnable;
};

/* Fixed-point load averages, 11 bits of fraction like Linux FSHIFT. */
#define PROC_LOAD_FSHIFT 11
#define PROC_LOAD_FIXED_1 (1UL << PROC_LOAD_FSHIFT)
#define PROC_LOAD_EXP_1  1884UL /* 1 / exp(5s / 60s)  * 2048 */
#define PROC_LOAD_EXP_5  2014UL /* 1 / exp(5s / 300s) * 2048 */
#define PROC_LOAD_EXP_15 2037UL /* 1 / exp(5s / 900s) * 2048 */

static unsigned long load_1 = 0;
static unsigned long load_5 = 0;
static unsigned long load_15 = 0;
static rt_tick_t load_last_tick = 0;

static int loadavg_count_pid(pid_t pid, void *arg)
{
    struct loadavg_count *count = (struct loadavg_count *)arg;
    struct rt_lwp *lwp = lwp_from_pid_locked(pid);

    if (!lwp)
    {
        return 0;
    }
    count->total++;
    {
        rt_list_t *node;

        node = lwp->t_grp.next;
        while (node != &lwp->t_grp)
        {
            rt_thread_t thread = rt_list_entry(node, struct rt_thread, sibling);
            int stat = RT_SCHED_CTX(thread).stat & RT_THREAD_STAT_MASK;

            if (stat == RT_THREAD_RUNNING || stat == RT_THREAD_READY)
            {
                count->runnable++;
                break;
            }
            node = node->next;
        }
    }
    return 0;
}

static void loadavg_fold(unsigned long active)
{
    load_1 = load_1 * PROC_LOAD_EXP_1 / PROC_LOAD_FIXED_1 +
             active * (PROC_LOAD_FIXED_1 - PROC_LOAD_EXP_1) / PROC_LOAD_FIXED_1;
    load_5 = load_5 * PROC_LOAD_EXP_5 / PROC_LOAD_FIXED_1 +
             active * (PROC_LOAD_FIXED_1 - PROC_LOAD_EXP_5) / PROC_LOAD_FIXED_1;
    load_15 = load_15 * PROC_LOAD_EXP_15 / PROC_LOAD_FIXED_1 +
              active * (PROC_LOAD_FIXED_1 - PROC_LOAD_EXP_15) / PROC_LOAD_FIXED_1;
}

static void loadavg_update(unsigned long active)
{
    rt_tick_t now = rt_tick_get();
    rt_tick_t period = RT_TICK_PER_SECOND * 5;

    if (load_last_tick == 0)
    {
        load_1 = load_5 = load_15 = active;
        load_last_tick = now;
        return;
    }

    while ((rt_tick_t)(now - load_last_tick) >= period)
    {
        loadavg_fold(active);
        load_last_tick += period;
    }
}

static void loadavg_print(struct dfs_seq_file *seq, unsigned long load)
{
    unsigned long integer = load >> PROC_LOAD_FSHIFT;
    unsigned long frac = ((load & (PROC_LOAD_FIXED_1 - 1)) * 100) >> PROC_LOAD_FSHIFT;

    dfs_seq_printf(seq, "%lu.%02lu", integer, frac);
}
#endif

static int single_show(struct dfs_seq_file *seq, void *data)
{
    RT_UNUSED(data);
#ifdef RT_USING_SMART
    struct loadavg_count count = { 0, 0 };

    lwp_pid_for_each(loadavg_count_pid, &count);
    loadavg_update(((unsigned long)count.runnable) << PROC_LOAD_FSHIFT);
    loadavg_print(seq, load_1);
    dfs_seq_puts(seq, " ");
    loadavg_print(seq, load_5);
    dfs_seq_puts(seq, " ");
    loadavg_print(seq, load_15);
    dfs_seq_printf(seq, " %d/%d %d\n", count.runnable, count.total,
                   (int)lwp_pid_get_last());
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
