/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-12     Bernard      first version
 * 2018-11-02     heyuanjie    fix complie error in iar
 * 2021-02-03     lizhirui     add 64-bit arch support and riscv64 arch support
 * 2021-08-26     linzhenxing  add lwp_setcwd\lwp_getcwd
 * 2023-02-20     wangxiaoyao  inv icache before new app startup
 * 2023-02-20     wangxiaoyao  fix bug on foreground app switch
 * 2023-10-16     Shell        Support a new backtrace framework
 * 2023-11-17     xqyjlj       add process group and session support
 * 2023-11-30     Shell        add lwp_startup()
 */

#define DBG_TAG "lwp"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <rthw.h>
#include <rtthread.h>

#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h> /* rename() */
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/statfs.h> /* statfs() */

#include <lwp_elf.h>

#ifndef RT_USING_DFS
#error "lwp need file system(RT_USING_DFS)"
#endif

#include "lwp_internal.h"
#include "lwp_arch.h"
#include "lwp_arch_comm.h"
#include "lwp_signal.h"
#include "lwp_dbg.h"
#include <terminal/terminal.h>

#ifdef ARCH_MM_MMU
#include <lwp_user_mm.h>
#endif /* end of ARCH_MM_MMU */


#ifndef O_DIRECTORY
#define O_DIRECTORY 0x200000
#endif

#ifndef O_BINARY
#define O_BINARY 0x10000
#endif

#ifdef DFS_USING_WORKDIR
extern char working_directory[];
#endif

static int lwp_component_init(void)
{
    int rc;
    if ((rc = lwp_tid_init()) != RT_EOK)
    {
        LOG_E("%s: lwp_component_init() failed", __func__);
    }
    else if ((rc = lwp_pid_init()) != RT_EOK)
    {
        LOG_E("%s: lwp_pid_init() failed", __func__);
    }
    else if ((rc = rt_channel_component_init()) != RT_EOK)
    {
        LOG_E("%s: rt_channel_component_init failed", __func__);
    }
    else if ((rc = lwp_futex_init()) != RT_EOK)
    {
        LOG_E("%s: lwp_futex_init() failed", __func__);
    }
    return rc;
}
INIT_COMPONENT_EXPORT(lwp_component_init);

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
 * Startup process 0 and do the essential works
 * This is the "Hello World" point of RT-Smart
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
                LOG_E("%s: failed to startup process 0 (init)\n"
                    "Switching to legacy mode...", __func__);
            }
            else if (error != 1)
            {
                LOG_E("%s: pid 1 is already allocated", __func__);
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
        LOG_D("%s: init program not found\n"
            "Switching to legacy mode...", __func__);
    }
    return error;
}
INIT_APP_EXPORT(lwp_startup);

void lwp_setcwd(char *buf)
{
    struct rt_lwp *lwp = RT_NULL;

    if(strlen(buf) >= DFS_PATH_MAX)
    {
        rt_kprintf("buf too long!\n");
        return ;
    }

    lwp = (struct rt_lwp *)rt_thread_self()->lwp;
    if (lwp)
    {
        rt_strncpy(lwp->working_directory, buf, DFS_PATH_MAX - 1);
    }
    else
    {
        rt_strncpy(working_directory, buf, DFS_PATH_MAX - 1);
    }

    return ;
}

char *lwp_getcwd(void)
{
    char *dir_buf = RT_NULL;
    struct rt_lwp *lwp = RT_NULL;
    rt_thread_t thread = rt_thread_self();

    if (thread)
    {
        lwp = (struct rt_lwp *)thread->lwp;
    }

    if (lwp)
    {
        if(lwp->working_directory[0] != '/')
        {
            dir_buf = &working_directory[0];
        }
        else
        {
            dir_buf = &lwp->working_directory[0];
        }
    }
    else
        dir_buf = &working_directory[0];

    return dir_buf;
}

/**
 * RT-Thread light-weight process
 */
void lwp_set_kernel_sp(uint32_t *sp)
{
    rt_thread_self()->kernel_sp = (rt_uint32_t *)sp;
}

uint32_t *lwp_get_kernel_sp(void)
{
#ifdef ARCH_MM_MMU
    return (uint32_t *)rt_thread_self()->sp;
#else
    uint32_t* kernel_sp;
    extern rt_uint32_t rt_interrupt_from_thread;
    extern rt_uint32_t rt_thread_switch_interrupt_flag;
    if (rt_thread_switch_interrupt_flag)
    {
        kernel_sp = (uint32_t *)((rt_thread_t)rt_container_of(rt_interrupt_from_thread, struct rt_thread, sp))->kernel_sp;
    }
    else
    {
        kernel_sp = (uint32_t *)rt_thread_self()->kernel_sp;
    }
    return kernel_sp;
#endif
}


/* lwp-thread clean up routine */
void lwp_cleanup(struct rt_thread *tid)
{
    struct rt_lwp *lwp;

    if (tid == NULL)
    {
        LOG_I("%s: invalid parameter tid == NULL", __func__);
        return;
    }
    else
        LOG_D("cleanup thread: %s, stack_addr: 0x%x", tid->parent.name, tid->stack_addr);

    /**
     * Brief: lwp thread cleanup
     *
     * Note: Critical Section
     * - thread control block (RW. It's ensured that no one else can access tcb
     *   other than itself)
     */
    lwp = (struct rt_lwp *)tid->lwp;
    lwp_thread_signal_detach(&tid->signal);

    /* tty will be release in lwp_ref_dec() if ref is cleared */
    lwp_ref_dec(lwp);
    return;
}

static void lwp_execve_setup_stdio(struct rt_lwp *lwp)
{
    struct dfs_fdtable *lwp_fdt;
    struct dfs_file *cons_file;
    int cons_fd;

    lwp_fdt = &lwp->fdt;

    /* open console */
    cons_fd = open("/dev/console", O_RDWR);
    if (cons_fd < 0)
    {
        LOG_E("%s: Cannot open console tty", __func__);
        return ;
    }
    LOG_D("%s: open console as fd %d", __func__, cons_fd);

    /* init 4 fds */
    lwp_fdt->fds = rt_calloc(4, sizeof(void *));
    if (lwp_fdt->fds)
    {
        cons_file = fd_get(cons_fd);
        lwp_fdt->maxfd = 4;
        fdt_fd_associate_file(lwp_fdt, 0, cons_file);
        fdt_fd_associate_file(lwp_fdt, 1, cons_file);
        fdt_fd_associate_file(lwp_fdt, 2, cons_file);
    }

    close(cons_fd);
    return;
}

static void _lwp_thread_entry(void *parameter)
{
    rt_thread_t tid;
    struct rt_lwp *lwp;

    tid = rt_thread_self();
    lwp = (struct rt_lwp *)tid->lwp;
    tid->cleanup = lwp_cleanup;
    tid->user_stack = RT_NULL;

    if (lwp->debug)
    {
        lwp->bak_first_inst = *(uint32_t *)lwp->text_entry;
        *(uint32_t *)lwp->text_entry = dbg_get_ins();
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, lwp->text_entry, sizeof(uint32_t));
        icache_invalid_all();
    }

    /**
     * without ASID support, it will be a special case when trying to run application
     * and exit multiple times and a same page frame allocated to it bound to
     * different text segment. Then we are in a situation where icache contains
     * out-of-dated data and must be handle by the running core itself.
     * with ASID support, this should be a rare case that ASID & page frame both
     * identical to previous running application.
     *
     * For a new application loaded into memory, icache are seen as empty. And there
     * should be nothing in the icache entry to match. So this icache invalidation
     * operation should have barely influence.
     */
    rt_hw_icache_invalidate_all();

#ifdef ARCH_MM_MMU
    arch_start_umode(lwp->args, lwp->text_entry, (void *)USER_STACK_VEND, (char *)tid->stack_addr + tid->stack_size);
#else
    arch_start_umode(lwp->args, lwp->text_entry, lwp->data_entry, (void *)((uint32_t)lwp->data_entry + lwp->data_size));
#endif /* ARCH_MM_MMU */
}

struct rt_lwp *lwp_self(void)
{
    rt_thread_t tid;

    tid = rt_thread_self();
    if (tid)
    {
        return (struct rt_lwp *)tid->lwp;
    }

    return RT_NULL;
}

rt_err_t lwp_children_register(struct rt_lwp *parent, struct rt_lwp *child)
{
    /* lwp add to children link */
    LWP_LOCK(parent);
    child->sibling = parent->first_child;
    parent->first_child = child;
    child->parent = parent;
    LWP_UNLOCK(parent);

    LOG_D("%s(parent=%p, child=%p)", __func__, parent, child);
    /* parent holds reference to child */
    lwp_ref_inc(parent);
    /* child holds reference to parent */
    lwp_ref_inc(child);

    return 0;
}

rt_err_t lwp_children_unregister(struct rt_lwp *parent, struct rt_lwp *child)
{
    struct rt_lwp **lwp_node;

    LWP_LOCK(parent);
    /* detach from children link */
    lwp_node = &parent->first_child;
    while (*lwp_node != child)
    {
        RT_ASSERT(*lwp_node != RT_NULL);
        lwp_node = &(*lwp_node)->sibling;
    }
    (*lwp_node) = child->sibling;
    child->parent = RT_NULL;
    LWP_UNLOCK(parent);

    LOG_D("%s(parent=%p, child=%p)", __func__, parent, child);
    lwp_ref_dec(child);
    lwp_ref_dec(parent);

    return 0;
}

struct process_aux *argscopy(struct rt_lwp *lwp, int argc, char **argv, char **envp)
{
    struct lwp_args_info ai;
    rt_err_t error;
    struct process_aux *ua;
    const char **tail_argv[2] = {0};

    error = lwp_args_init(&ai);
    if (error)
    {
        return RT_NULL;
    }

    if (argc > 0)
    {
        tail_argv[0] = (void *)argv[argc - 1];
        argv[argc - 1] = NULL;
        lwp_args_put(&ai, (void *)argv, LWP_ARGS_TYPE_KARG);
        lwp_args_put(&ai, (void *)tail_argv, LWP_ARGS_TYPE_KARG);
    }
    lwp_args_put(&ai, (void *)envp, LWP_ARGS_TYPE_KENVP);

    ua = lwp_argscopy(lwp, &ai);
    lwp_args_detach(&ai);

    return ua;
}

pid_t lwp_execve(char *filename, int debug, int argc, char **argv, char **envp)
{
    int result;
    struct rt_lwp *lwp;
    char *thread_name;
    struct process_aux *aux;
    int tid = 0;

    if (filename == RT_NULL)
    {
        return -EINVAL;
    }

    if (access(filename, X_OK) != 0)
    {
        return -EACCES;
    }

    lwp = lwp_create(LWP_CREATE_FLAG_ALLOC_PID | LWP_CREATE_FLAG_NOTRACE_EXEC);

    if (lwp == RT_NULL)
    {
        dbg_log(DBG_ERROR, "lwp struct out of memory!\n");
        return -ENOMEM;
    }
    LOG_D("lwp malloc : %p, size: %d!", lwp, sizeof(struct rt_lwp));

    if ((tid = lwp_tid_get()) == 0)
    {
        lwp_ref_dec(lwp);
        return -ENOMEM;
    }
#ifdef ARCH_MM_MMU
    if (lwp_user_space_init(lwp, 0) != 0)
    {
        lwp_tid_put(tid);
        lwp_ref_dec(lwp);
        return -ENOMEM;
    }
#endif

    if ((aux = argscopy(lwp, argc, argv, envp)) == RT_NULL)
    {
        lwp_tid_put(tid);
        lwp_ref_dec(lwp);
        return -ENOMEM;
    }

    result = lwp_load(filename, lwp, RT_NULL, 0, aux);
    if (result == RT_EOK)
    {
        rt_thread_t thread = RT_NULL;
        rt_uint32_t priority = 25, tick = 200;

        lwp_execve_setup_stdio(lwp);

        /* obtain the base name */
        thread_name = strrchr(filename, '/');
        thread_name = thread_name ? thread_name + 1 : filename;
#ifndef ARCH_MM_MMU
        struct lwp_app_head *app_head = lwp->text_entry;
        if (app_head->priority)
        {
            priority = app_head->priority;
        }
        if (app_head->tick)
        {
            tick = app_head->tick;
        }
#endif /* not defined ARCH_MM_MMU */
        thread = rt_thread_create(thread_name, _lwp_thread_entry, RT_NULL,
                LWP_TASK_STACK_SIZE, priority, tick);
        if (thread != RT_NULL)
        {
            struct rt_lwp *self_lwp;
            rt_session_t session;
            rt_processgroup_t group;

            thread->tid = tid;
            lwp_tid_set_thread(tid, thread);
            LOG_D("lwp kernel => (0x%08x, 0x%08x)\n", (rt_size_t)thread->stack_addr,
                    (rt_size_t)thread->stack_addr + thread->stack_size);
            self_lwp = lwp_self();

            /* when create init, self_lwp == null */
            if (self_lwp == RT_NULL && lwp_to_pid(lwp) != 1)
            {
                self_lwp = lwp_from_pid_and_lock(1);
            }

            if (self_lwp)
            {
                /* lwp add to children link */
                lwp_children_register(self_lwp, lwp);
            }

            session = RT_NULL;
            group = RT_NULL;

            group = lwp_pgrp_create(lwp);
            if (group)
            {
                lwp_pgrp_insert(group, lwp);
                if (self_lwp == RT_NULL)
                {
                    session = lwp_session_create(lwp);
                    lwp_session_insert(session, group);
                }
                else
                {
                    session = lwp_session_find(lwp_sid_get_byprocess(self_lwp));
                    lwp_session_insert(session, group);
                }
            }

            thread->lwp = lwp;
#ifndef ARCH_MM_MMU
            struct lwp_app_head *app_head = (struct lwp_app_head*)lwp->text_entry;
            thread->user_stack = app_head->stack_offset ?
                              (void *)(app_head->stack_offset -
                                       app_head->data_offset +
                                       (uint32_t)lwp->data_entry) : RT_NULL;
            thread->user_stack_size = app_head->stack_size;
            /* init data area */
            rt_memset(lwp->data_entry, 0, lwp->data_size);
            /* init user stack */
            rt_memset(thread->user_stack, '#', thread->user_stack_size);
#endif /* not defined ARCH_MM_MMU */
            rt_list_insert_after(&lwp->t_grp, &thread->sibling);

            lwp->did_exec = RT_TRUE;

            if (debug && rt_dbg_ops)
            {
                lwp->debug = debug;
                rt_thread_control(thread, RT_THREAD_CTRL_BIND_CPU, (void*)0);
            }

            rt_thread_startup(thread);
            return lwp_to_pid(lwp);
        }
    }

    lwp_tid_put(tid);
    lwp_ref_dec(lwp);

    return -RT_ERROR;
}

#ifdef RT_USING_MUSLLIBC
extern char **__environ;
#else
char **__environ = 0;
#endif

pid_t exec(char *filename, int debug, int argc, char **argv)
{
    setenv("OS", "RT-Thread", 1);
    return lwp_execve(filename, debug, argc, argv, __environ);
}

#ifdef ARCH_MM_MMU
void lwp_user_setting_save(rt_thread_t thread)
{
    if (thread)
    {
        thread->thread_idr = arch_get_tidr();
    }
}

void lwp_user_setting_restore(rt_thread_t thread)
{
    if (!thread)
    {
        return;
    }
#if !defined(ARCH_RISCV64)
    /* tidr will be set in RESTORE_ALL in risc-v */
    arch_set_tidr(thread->thread_idr);
#endif

    if (rt_dbg_ops)
    {
        struct rt_lwp *l = (struct rt_lwp *)thread->lwp;

        if (l != 0)
        {
            rt_hw_set_process_id((size_t)l->pid);
        }
        else
        {
            rt_hw_set_process_id(0);
        }
        if (l && l->debug)
        {
            uint32_t step_type = 0;

            step_type = dbg_step_type();

            if ((step_type == 2) || (thread->step_exec && (step_type == 1)))
            {
                dbg_activate_step();
            }
            else
            {
                dbg_deactivate_step();
            }
        }
    }
}
#endif /* ARCH_MM_MMU */

void lwp_uthread_ctx_save(void *ctx)
{
    rt_thread_t thread;
    thread = rt_thread_self();
    thread->user_ctx.ctx = ctx;
}

void lwp_uthread_ctx_restore(void)
{
    rt_thread_t thread;
    thread = rt_thread_self();
    thread->user_ctx.ctx = RT_NULL;
}

rt_err_t lwp_backtrace_frame(rt_thread_t uthread, struct rt_hw_backtrace_frame *frame)
{
    rt_err_t rc = -RT_ERROR;
    long nesting = 0;
    char **argv;
    rt_lwp_t lwp;

    if (uthread && uthread->lwp && rt_scheduler_is_available())
    {
        lwp = uthread->lwp;
        argv = lwp_get_command_line_args(lwp);
        if (argv)
        {
            rt_kprintf("please use: addr2line -e %s -a -f", argv[0]);
            lwp_free_command_line_args(argv);
        }
        else
        {
            rt_kprintf("please use: addr2line -e %s -a -f", lwp->cmd);
        }

        while (nesting < RT_BACKTRACE_LEVEL_MAX_NR)
        {
            rt_kprintf(" 0x%lx", frame->pc);
            if (rt_hw_backtrace_frame_unwind(uthread, frame))
            {
                break;
            }
            nesting++;
        }
        rt_kprintf("\n");
        rc = RT_EOK;
    }
    return rc;
}
