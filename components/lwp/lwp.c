/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
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

/**
 * @brief Initializes the LWP (Light-Weight Process) component
 *
 * @return int Returns RT_EOK if all initializations succeed, otherwise returns
 *         the error code from the first failed initialization
 *
 * @note This function performs initialization of various LWP subsystems in sequence:
 *       1. Thread ID (TID) initialization
 *       2. Process ID (PID) initialization
 *       3. Channel component initialization
 *       4. Futex (Fast Userspace Mutex) initialization
 */
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

/**
 * @brief Sets the current working directory for the calling LWP or system
 *
 * @param[in] buf Pointer to the path string to set as working directory
 *
 * @note This function handles both LWP-specific and system-wide working directories:
 * - For LWPs, sets the working_directory in the LWP structure
 * - For non-LWP threads, sets the global working_directory variable
 */
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

/**
 * @brief Get the current working directory for the light-weight process
 *
 * @return char* Pointer to the current working directory string
 *
 * @note The function returns either:
 *          - LWP's working directory (if valid and absolute path)
 *          - System default working directory (if no LWP or invalid path)
 */
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
 * @brief Set the kernel stack pointer for the current thread
 *
 * @param[in] sp Pointer to the new kernel stack location
 *
 * @note It's typically used during context switching or thread initialization.
 */
void lwp_set_kernel_sp(uint32_t *sp)
{
    rt_thread_self()->kernel_sp = (rt_uint32_t *)sp;
}

/**
 * @brief Get the kernel stack pointer for the current thread
 *
 * @return uint32_t* Pointer to the kernel stack
 *
 * @note Architecture-specific behavior:
 * 1. With MMU: Simply returns the current thread's stack pointer
 * 2. Without MMU: Checks interrupt context and returns either:
 *    - Interrupted thread's kernel_sp (if in interrupt)
 *    - Current thread's kernel_sp (if not in interrupt)
 */
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

/**
 * @brief Clean up resources associated with a light-weight process thread
 *
 * @param[in] tid Pointer to the thread control block to be cleaned up
 *
 * @note This function performs cleanup operations for a thread associated with a light-weight process (LWP).
 *       It handles signal detachment and reference count decrement for the LWP structure.
 *
 */
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

/**
 * @brief Set up standard I/O for a light-weight process
 *
 * @param[in] lwp Pointer to the light-weight process structure
 *
 * @note This function initializes the standard input, output, and error streams
 *       for a light-weight process by opening the console device and associating
 *       it with file descriptors 0, 1, and 2.
 */
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

/**
 * @brief Entry point for light-weight process threads
 *
 * @param[in] parameter Thread parameter (unused)
 *
 * @note This function is the main entry point for threads created within a light-weight process.
 *       It handles thread initialization, debug mode setup, and transitions to user mode.
 */
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

/**
 * @brief Get the current light-weight process
 *
 * @return Pointer to the current light-weight process structure
 *         RT_NULL if no process is associated with current thread
 *
 * @note This function retrieves the light-weight process associated with the
 *       currently running thread.
 */
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

/**
 * @brief Register a child process with its parent
 *
 * @param[in] parent Pointer to the parent process structure
 * @param[in] child  Pointer to the child process structure to register
 *
 * @return RT_EOK on success
 *
 * @note This function adds a child process to its parent's children list and
 *       increases reference counts for both processes.
 */
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

/**
 * @brief Unregister a child process from its parent
 *
 * @param[in] parent Pointer to the parent process structure
 * @param[in] child  Pointer to the child process structure to unregister
 *
 * @return RT_EOK on success
 *
 * @note This function removes a child process from its parent's children list and
 *       decreases reference counts for both processes.
 */
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

/**
 * @brief Copy process arguments and environment variables from kernel space to user space.
 *
 * @param[in] lwp  Pointer to the light-weight process structure
 * @param[in] argc Argument count
 * @param[in] argv Argument vector
 * @param[in] envp Environment variables
 *
 * @return Pointer to the process auxiliary structure on success
 *         RT_NULL if memory allocation fails or arguments initialization fails
 *
 * @note This function performs the following operations:
 *       1. Initializes argument information structure
 *       2. Copies command line arguments to user space
 *       3. Copies environment variables to user space
 *       4. Returns the auxiliary structure containing copied data
 */
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

/**
 * @brief Creates and starts a new LWP by loading and executing the specified executable file.
 *
 * @param[in] filename Path to the executable file
 * @param[in] debug     Debug flag (non-zero to enable debugging)
 * @param[in] argc      Argument count
 * @param[in] argv      Argument vector
 * @param[in] envp      Environment variables
 *
 * @return Process ID (PID) of the new LWP on success
 *         -EINVAL if filename is NULL
 *         -EACCES if file is not executable
 *         -ENOMEM if memory allocation fails
 *         -RT_ERROR on other failures
 *
 * @note This function performs the following operations:
 *       1. Validates input parameters
 *       2. Creates new LWP structure
 *       3. Initializes user space (for MMU systems)
 *       4. Copies arguments and environment
 *       5. Loads the executable
 *       6. Sets up standard I/O
 *       7. Creates and starts the main thread
 */
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
        LOG_E("lwp struct out of memory!\n");
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

/**
 * @brief Execute a new program in the current process context
 *
 * @param[in] filename Path to the executable file
 * @param[in] debug Debug flag (non-zero enables debug mode)
 * @param[in] argc Number of command line arguments
 * @param[in] argv Array of command line argument strings
 *
 * @return Process ID (PID) of the new process on success
 *         Negative error code on failure
 *
 * @note This is a wrapper function for lwp_execve.
 *
 * @see lwp_execve()
 */
pid_t exec(char *filename, int debug, int argc, char **argv)
{
    setenv("OS", "RT-Thread", 1);
    return lwp_execve(filename, debug, argc, argv, __environ);
}

#ifdef ARCH_MM_MMU
/**
 * @brief Saves thread-specific user settings (TID register)
 *
 * @param[in,out] thread Pointer to the thread control block
 *
 * @note This function stores the architecture-specific TID register
 *       into the specified thread's control block.This is typically used
 *       when switching between threads to preserve thread-specific settings
 */

void lwp_user_setting_save(rt_thread_t thread)
{
    if (thread)
    {
        thread->thread_idr = arch_get_tidr();
    }
}

/**
 * @brief Restores thread-specific user settings (TID register and debug state)
 *
 * @param[in] thread Pointer to the thread control block
 *
 * @note This function restores architecture-specific Thread ID Register (TIDR) value
 *       and debug-related settings for the specified thread.
 */
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

/**
 * @brief Saves user thread context pointer
 *
 * @param[in] ctx Pointer to user thread context structure to be saved
 *
 * @note This function stores a pointer to user thread context in the current thread's
 *       control block for later restoration. The context pointer is typically used
 *       during thread context switching.
 */
void lwp_uthread_ctx_save(void *ctx)
{
    rt_thread_t thread;
    thread = rt_thread_self();
    thread->user_ctx.ctx = ctx;
}

/**
 * @brief Restores the user thread context by clearing the context pointer
 *
 * @note Typically called during thread context switching to clean up any
 *       previously saved user context.
 */
void lwp_uthread_ctx_restore(void)
{
    rt_thread_t thread;
    thread = rt_thread_self();
    thread->user_ctx.ctx = RT_NULL;
}

/**
 * @brief Prints a backtrace of the current thread's call stack
 *
 * @param[in] uthread The thread to backtrace (must be associated with an LWP)
 * @param[in] frame Pointer to the initial stack frame
 *
 * @return RT_EOK on success, -RT_ERROR on failure
 *
 * @note This function prints a backtrace of the call stack for the specified user thread,
 *       providing addresses that can be used with addr2line to get file and line information.
 */
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
            rt_kprintf("please use: addr2line -e %s -a -f\n", argv[0]);
            lwp_free_command_line_args(argv);
        }
        else
        {
            rt_kprintf("please use: addr2line -e %s -a -f\n", lwp->cmd);
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
