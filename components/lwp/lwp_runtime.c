/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-11-11     Shell        moved lwp_startup() from lwp.c;
 *                             added lwp_teardown()
 */

#define DBG_TAG "lwp"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "lwp_internal.h"

#include <rthw.h>
#include <rtthread.h>

#include <dfs_file.h>
#include <dfs_mnt.h>
#include <dfs_fs.h>

/**
 * lwp_runtime:
 * Runtime environment provide by init process including boot scripts,
 * poweroff, shutdown, reboot, service management etc. In the kernel, lwp will
 * provide the underlying software bootstrap and cleanup for the init proc.
 *
 */

rt_weak int lwp_startup_debug_request(void)
{
    return 0;
}

#define LATENCY_TIMES (3)
#define LATENCY_IN_MSEC (128)
#define LWP_CONSOLE_PATH "CONSOLE=/dev/console"
const char *init_search_path[] = {
    "/sbin/init",
    "/bin/init",
};

/**
 * Startup process 1 and do the essential works
 */
static int lwp_startup(void)
{
    int error;

    const char *init_path;
    char *argv[] = {0, "&"};
    char *envp[] = {LWP_CONSOLE_PATH, 0};

#ifdef LWP_DEBUG_INIT
    int command;
    int countdown = LATENCY_TIMES;
    while (countdown)
    {
        command = lwp_startup_debug_request();
        if (command)
        {
            return 0;
        }
        rt_kprintf("Press any key to stop init process startup ... %d\n", countdown);
        countdown -= 1;
        rt_thread_mdelay(LATENCY_IN_MSEC);
    }
    rt_kprintf("Starting init ...\n");
#endif /* LWP_DEBUG_INIT */

    for (size_t i = 0; i < sizeof(init_search_path)/sizeof(init_search_path[0]); i++)
    {
        struct stat s;
        init_path = init_search_path[i];
        error = stat(init_path, &s);
        if (error == 0)
        {
            argv[0] = (void *)init_path;
            error = lwp_execve((void *)init_path, 0, sizeof(argv)/sizeof(argv[0]), argv, envp);
            if (error < 0)
            {
                LOG_W("%s: failed to setup runtime environment\b"
                      "\tlwp_execve() failed with code %d", __func__, error);
            }
            else if (error != 1)
            {
                LOG_W("%s: pid 1 is already allocated", __func__);
                error = -EBUSY;
            }
            else
            {
                rt_lwp_t p = lwp_from_pid_locked(1);
                p->sig_protected = 1;

                error = 0;
            }
            break;
        }
    }

    if (error)
    {
        LOG_D("%s: failed to setup runtime environment\b"
              "\tinit program not found", __func__);
    }
    return error;
}
INIT_APP_EXPORT(lwp_startup);

/* don't use heap for safety */
static struct rt_work _teardown_work;

#define INIT_PID 1
static void _teardown_entry(struct rt_work *work, void *work_data)
{
    int error;
    void (*cb_on_reboot)(void) = work_data;

    /* cleanup of process */
    do
    {
        error = lwp_pid_wait_for_empty(RT_KILLABLE, RT_WAITING_FOREVER);
    }
    while (error);
    LOG_I("All processes exited");

    cb_on_reboot();
    return;
}

static int _get_parent_pid(struct rt_lwp *lwp)
{
    return lwp->parent ? lwp->parent->pid : 0;
}

/* reverse operation of lwp_startup() */
sysret_t lwp_teardown(struct rt_lwp *lwp, void (*cb)(void))
{
    struct rt_work *work;

    if (lwp->pid != INIT_PID && _get_parent_pid(lwp) != INIT_PID)
    {
        /* The calling process has insufficient privilege */
        return -EPERM;
    }

    work = &_teardown_work;
    rt_work_init(work, _teardown_entry, cb);

#define SOME_DELAY (RT_TICK_PER_SECOND / 10) /* allow idle to cleanup resource */
    rt_work_submit(work, SOME_DELAY);

    lwp_exit(lwp, LWP_CREATE_STAT_EXIT(EXIT_SUCCESS));

    /* never return */
    RT_ASSERT(0);
    return 0;
}
