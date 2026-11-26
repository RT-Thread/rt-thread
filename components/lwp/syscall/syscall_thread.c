/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "syscall_internal.h"

/**
 * @brief Creates a new thread.
 *
 * This system call creates a new thread within the calling process. The newly created
 * thread starts executing the function specified by the `arg` argument, which typically
 * contains the necessary arguments or function pointer for the thread's execution.
 *
 * @param[in] arg     An array of arguments that will be passed to the function executed
 *                    by the new thread. This can include function pointers, structures,
 *                    or any necessary data the thread will need to execute its work.
 *
 * @return rt_thread_t    Returns a handle to the newly created thread. If the thread
 *                        creation fails, `NULL` is returned.
 *
 * @warning Ensure that the system has sufficient resources to create a new thread.
 *          Thread creation failures can occur if system limits are exceeded or resources
 *          are unavailable.
 */
rt_thread_t sys_thread_create(void *arg[])
{
    int tid = 0;
    void *user_stack = 0;
    struct rt_lwp *lwp = 0;
    rt_thread_t thread = RT_NULL;

    lwp = rt_thread_self()->lwp;
    lwp_ref_inc(lwp);

#ifdef ARCH_MM_MMU
    user_stack = lwp_map_user(lwp, 0, (size_t)arg[3], 0);
    if (!user_stack)
    {
        goto fail;
    }
    if ((tid = lwp_tid_get()) == 0)
    {
        goto fail;
    }
    thread = rt_thread_create((const char *)arg[0],
                              _crt_thread_entry,
                              (void *)arg[2],
                              ALLOC_KERNEL_STACK_SIZE,
                              (rt_uint8_t)(size_t)arg[4],
                              (rt_uint32_t)(rt_size_t)arg[5]);
    if (!thread)
    {
        goto fail;
    }

#ifdef RT_USING_SMP
    RT_SCHED_CTX(thread).bind_cpu = lwp->bind_cpu;
#endif
    thread->cleanup = lwp_cleanup;
    thread->user_entry = (void (*)(void *))arg[1];
    thread->user_stack = (void *)user_stack;
    thread->user_stack_size = (rt_size_t)arg[3];
#else
    rt_uint32_t kstack_size = (rt_uint32_t)arg[7];
    if (kstack_size < ALLOC_KERNEL_STACK_SIZE_MIN)
    {
        /* When kstack size is 0, the default size of the kernel stack is used */
        kstack_size = kstack_size ? ALLOC_KERNEL_STACK_SIZE_MIN : ALLOC_KERNEL_STACK_SIZE;
    }
    else if (kstack_size > ALLOC_KERNEL_STACK_SIZE_MAX)
    {
        kstack_size = ALLOC_KERNEL_STACK_SIZE_MAX;
    }

    user_stack = (void *)arg[3];
    if ((!user_stack) || ((rt_uint32_t)arg[6] == RT_NULL))
    {
        goto fail;
    }

    if ((tid = lwp_tid_get()) == 0)
    {
        goto fail;
    }

    thread = rt_thread_create((const char *)arg[0], _crt_thread_entry, (void *)arg[2], kstack_size, (rt_uint8_t)(size_t)arg[5], (rt_uint32_t)arg[6]);
    if (!thread)
    {
        goto fail;
    }
    thread->cleanup = lwp_cleanup;
    thread->user_entry = (void (*)(void *))arg[1];
    thread->user_stack = (void *)user_stack;
    thread->user_stack_size = (uint32_t)arg[4];
    rt_memset(thread->user_stack, '#', thread->user_stack_size);
#endif /* ARCH_MM_MMU */

    thread->lwp = (void *)lwp;
    thread->tid = tid;
    lwp_tid_set_thread(tid, thread);

    if (lwp->debug)
    {
        rt_thread_control(thread, RT_THREAD_CTRL_BIND_CPU, (void *)0);
    }

    LWP_LOCK(lwp);
    rt_list_insert_after(&lwp->t_grp, &thread->sibling);
    LWP_UNLOCK(lwp);

    return thread;

fail:
    lwp_tid_put(tid);
    if (lwp)
    {
        lwp_ref_dec(lwp);
    }
    return RT_NULL;
}

#ifdef ARCH_MM_MMU

long _sys_clone(void *arg[])
{
    struct rt_lwp *lwp = 0;
    rt_thread_t thread = RT_NULL;
    rt_thread_t self = RT_NULL;
    int tid = 0;
    rt_err_t err;

    unsigned long flags = 0;
    void *user_stack = RT_NULL;
    int *new_tid = RT_NULL;
    void *tls = RT_NULL;
    /*
       musl call flags (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND
       | CLONE_THREAD | CLONE_SYSVSEM | CLONE_SETTLS
       | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_DETACHED);
       */

    /* check args */
    if (!lwp_user_accessable(arg, sizeof(void *[SYS_CLONE_ARGS_NR])))
    {
        return -EFAULT;
    }

    flags = (unsigned long)(size_t)arg[0];
    if ((flags & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_THREAD | CLONE_SYSVSEM)) != (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_THREAD | CLONE_SYSVSEM))
    {
        return -EINVAL;
    }

    user_stack = arg[1];
    new_tid = (int *)arg[2];
    tls = (void *)arg[3];

    if ((flags & CLONE_PARENT_SETTID) == CLONE_PARENT_SETTID)
    {
        if (!lwp_user_accessable(new_tid, sizeof(int)))
        {
            return -EFAULT;
        }
    }

    self = rt_thread_self();
    lwp = self->lwp;
    lwp_ref_inc(lwp);
    if (!user_stack)
    {
        SET_ERRNO(EINVAL);
        goto fail;
    }
    if ((tid = lwp_tid_get()) == 0)
    {
        SET_ERRNO(ENOMEM);
        goto fail;
    }

    thread = rt_thread_create(self->parent.name,
                              RT_NULL,
                              RT_NULL,
                              self->stack_size,
                              RT_SCHED_PRIV(self).init_priority,
                              RT_SCHED_PRIV(self).init_tick);
    if (!thread)
    {
        goto fail;
    }

#ifdef RT_USING_SMP
    RT_SCHED_CTX(self).bind_cpu = lwp->bind_cpu;
#endif
    thread->cleanup = lwp_cleanup;
    thread->user_entry = RT_NULL;
    thread->user_stack = RT_NULL;
    thread->user_stack_size = 0;
    thread->lwp = (void *)lwp;
    thread->tid = tid;

    if ((flags & CLONE_SETTLS) == CLONE_SETTLS)
    {
        thread->thread_idr = tls;
    }
    if ((flags & CLONE_PARENT_SETTID) == CLONE_PARENT_SETTID)
    {
        *new_tid = (int)(tid);
    }
    if ((flags & CLONE_CHILD_CLEARTID) == CLONE_CHILD_CLEARTID)
    {
        thread->clear_child_tid = (int *)arg[4];
    }

    if (lwp->debug)
    {
        rt_thread_control(thread, RT_THREAD_CTRL_BIND_CPU, (void *)0);
    }

    LWP_LOCK(lwp);
    rt_list_insert_after(&lwp->t_grp, &thread->sibling);
    LWP_UNLOCK(lwp);

    /* copy origin stack */
    lwp_memcpy(thread->stack_addr, self->stack_addr, thread->stack_size);
    lwp_tid_set_thread(tid, thread);
    arch_set_thread_context(arch_clone_exit,
                            (void *)((char *)thread->stack_addr + thread->stack_size),
                            user_stack, &thread->sp);
    /* new thread never reach there */
    rt_thread_startup(thread);
    return (long)tid;
fail:
    err = GET_ERRNO();
    RT_ASSERT(err < 0);

    lwp_tid_put(tid);
    if (thread)
    {
        rt_thread_delete(thread);
    }
    if (lwp)
    {
        lwp_ref_dec(lwp);
    }
    return (long)err;
}

/**
 * @brief Creates a new process or thread (clone).
 *
 * This system call creates a new process or thread by duplicating the calling process.
 * The new process/thread begins execution by calling the function specified in the
 * `arg[]` array, which typically contains the necessary arguments or function pointer.
 * It is used to implement process/thread creation in the system and is often a lower-level
 * operation in process management.
 *
 * @param[in] arg   An array of arguments passed to the new process or thread. This could
 *                  include function pointers, structures, or any necessary data the
 *                  new process/thread will need to execute its work.
 *
 * @return long     Returns a status code or the process/thread ID of the newly created
 *                  process/thread. On success, it may return a positive value (such as a
 *                  thread ID). On failure, a negative value indicating the error is returned.
 *
 * @warning Be cautious when using this function as improper management of process/thread
 *          creation can lead to resource exhaustion, deadlocks, or other synchronization issues.
 */
rt_weak long sys_clone(void *arg[])
{
    return _sys_clone(arg);
}

static void lwp_struct_copy(struct rt_lwp *dst, struct rt_lwp *src)
{
#ifdef ARCH_MM_MMU
    dst->end_heap = src->end_heap;
#endif
    dst->lwp_type = src->lwp_type;
    dst->text_entry = src->text_entry;
    dst->text_size = src->text_size;
    dst->data_entry = src->data_entry;
    dst->data_size = src->data_size;
    dst->args = src->args;
    dst->background = src->background;
    dst->tty = src->tty;

    /* terminal API */
    dst->term_ctrlterm = src->term_ctrlterm;

    rt_memcpy(dst->cmd, src->cmd, RT_NAME_MAX);
    if (src->exe_file)
    {
        if (dst->exe_file)
        {
            rt_free(dst->exe_file);
        }
        dst->exe_file = strndup(src->exe_file, DFS_PATH_MAX);
    }

    rt_memcpy(&dst->signal.sig_action, &src->signal.sig_action, sizeof(dst->signal.sig_action));
    rt_memcpy(&dst->signal.sig_action_mask, &src->signal.sig_action_mask, sizeof(dst->signal.sig_action_mask));
    rt_memcpy(&dst->signal.sig_action_nodefer, &src->signal.sig_action_nodefer, sizeof(dst->signal.sig_action_nodefer));
    rt_memcpy(&dst->signal.sig_action_onstack, &src->signal.sig_action_onstack, sizeof(dst->signal.sig_action_onstack));
    rt_memcpy(&dst->signal.sig_action_restart, &dst->signal.sig_action_restart, sizeof(dst->signal.sig_action_restart));
    rt_memcpy(&dst->signal.sig_action_siginfo, &dst->signal.sig_action_siginfo, sizeof(dst->signal.sig_action_siginfo));
    rt_memcpy(&dst->signal.sig_action_nocldstop, &dst->signal.sig_action_nocldstop, sizeof(dst->signal.sig_action_nocldstop));
    rt_memcpy(&dst->signal.sig_action_nocldwait, &dst->signal.sig_action_nocldwait, sizeof(dst->signal.sig_action_nocldwait));
    rt_strcpy(dst->working_directory, src->working_directory);
}

static int lwp_copy_files(struct rt_lwp *dst, struct rt_lwp *src)
{
    struct dfs_fdtable *dst_fdt;
    struct dfs_fdtable *src_fdt;

    src_fdt = &src->fdt;
    dst_fdt = &dst->fdt;
    /* init fds */
    dst_fdt->fds = rt_calloc(src_fdt->maxfd, sizeof(void *));
    if (dst_fdt->fds)
    {
        struct dfs_file *d_s;
        int i;

        dst_fdt->maxfd = src_fdt->maxfd;

        dfs_file_lock();
        /* dup files */
        for (i = 0; i < src_fdt->maxfd; i++)
        {
            d_s = fdt_get_file(src_fdt, i);
            if (d_s)
            {
                dst_fdt->fds[i] = d_s;
                d_s->ref_count++;
            }
        }
        dfs_file_unlock();
        return 0;
    }
    return -RT_ERROR;
}

sysret_t _sys_fork(void)
{
    int tid = 0;
    sysret_t falival = 0;
    struct rt_lwp *lwp = RT_NULL;
    struct rt_lwp *self_lwp = RT_NULL;
    rt_thread_t thread = RT_NULL;
    rt_thread_t self_thread = RT_NULL;
    void *user_stack = RT_NULL;
    rt_processgroup_t group;

    /* new lwp */
    lwp = lwp_create(LWP_CREATE_FLAG_ALLOC_PID);
    if (!lwp)
    {
        SET_ERRNO(ENOMEM);
        goto fail;
    }

    /* new tid */
    if ((tid = lwp_tid_get()) == 0)
    {
        SET_ERRNO(ENOMEM);
        goto fail;
    }

    /* user space init */
    if (lwp_user_space_init(lwp, 1) != 0)
    {
        SET_ERRNO(ENOMEM);
        goto fail;
    }

    self_lwp = lwp_self();

    /* copy address space of process from this proc to forked one */
    if (lwp_fork_aspace(lwp, self_lwp) != 0)
    {
        SET_ERRNO(ENOMEM);
        goto fail;
    }

    /* copy lwp struct data */
    lwp_struct_copy(lwp, self_lwp);

    /* copy files */
    if (lwp_copy_files(lwp, self_lwp) != 0)
    {
        SET_ERRNO(ENOMEM);
        goto fail;
    }

    /* create thread */
    self_thread = rt_thread_self();

    thread = rt_thread_create(self_thread->parent.name,
                              RT_NULL,
                              RT_NULL,
                              self_thread->stack_size,
                              RT_SCHED_PRIV(self_thread).init_priority,
                              RT_SCHED_PRIV(self_thread).init_tick);
    if (!thread)
    {
        SET_ERRNO(ENOMEM);
        goto fail;
    }

    thread->cleanup = self_thread->cleanup;
    thread->user_entry = self_thread->user_entry;
    thread->user_stack = self_thread->user_stack;
    thread->user_stack_size = self_thread->user_stack_size;
    thread->signal.sigset_mask = self_thread->signal.sigset_mask;
    thread->thread_idr = self_thread->thread_idr;
    thread->clear_child_tid = self_thread->clear_child_tid;
    thread->lwp = (void *)lwp;
    thread->tid = tid;

    LWP_LOCK(self_lwp);
    /* add thread to lwp process */
    rt_list_insert_after(&lwp->t_grp, &thread->sibling);
    LWP_UNLOCK(self_lwp);

    lwp_children_register(self_lwp, lwp);

    /* set pgid and sid */
    group = lwp_pgrp_find(lwp_pgid_get_byprocess(self_lwp));
    if (group)
    {
        lwp_pgrp_insert(group, lwp);
    }
    else
    {
        LOG_W("the process group of pid: %d cannot be found", lwp_pgid_get_byprocess(self_lwp));
    }

    /* copy kernel stack context from self thread */
    lwp_memcpy(thread->stack_addr, self_thread->stack_addr, self_thread->stack_size);
    lwp_tid_set_thread(tid, thread);

    /* duplicate user objects */
    lwp_user_object_dup(lwp, self_lwp);

    user_stack = arch_get_user_sp();
    arch_set_thread_context(arch_fork_exit,
                            (void *)((char *)thread->stack_addr + thread->stack_size),
                            user_stack, &thread->sp);

    rt_thread_startup(thread);
    return lwp_to_pid(lwp);
fail:
    falival = GET_ERRNO();

    if (tid != 0)
    {
        lwp_tid_put(tid);
    }
    if (thread)
    {
        rt_thread_delete(thread);
    }
    if (lwp)
    {
        lwp_ref_dec(lwp);
    }
    return falival;
}

/* arm needs to wrap fork/clone call to preserved lr & caller saved regs */

/**
 * @brief Creates a child process by duplicating the calling process.
 *
 * This system call creates a new child process by duplicating the calling process. The
 * new child process is a copy of the parent process, except for the returned value.
 * The child process starts executing from the point of the fork, but the return value
 * differs between the parent and child: the parent receives the process ID (PID) of the
 * child, and the child receives a return value of 0.
 *
 * @return sysret_t    Returns a status code indicating the result of the operation:
 *                      - A positive value (the child's PID) is returned to the parent.
 *                      - A value of 0 is returned to the child process.
 *                      - A negative value indicates an error (e.g., resource limits exceeded).
 *
 * @note This function is commonly used in operating systems to create new processes.
 *
 * @warning Be aware that improper management of child processes (such as failing to handle
 *          process termination or excessive forking) can lead to resource exhaustion or
 *          other system issues. Ensure proper process handling in the parent and child
 *          processes to avoid leaks and inconsistencies.
 */
rt_weak sysret_t sys_fork(void)
{
    return _sys_fork();
}

/**
 * @brief Creates a child process using vfork-compatible semantics.
 *
 * This implementation delegates to `sys_fork`.
 *
 * @return sysret_t The child process ID in the parent or a negative error code.
 */
rt_weak sysret_t sys_vfork(void)
{
    return sys_fork();
}

#define _swap_lwp_data(lwp_used, lwp_new, type, member) \
    do                                                  \
    {                                                   \
        type tmp;                                       \
        tmp = lwp_used->member;                         \
        lwp_used->member = lwp_new->member;             \
        lwp_new->member = tmp;                          \
    } while (0)

/**
 * @brief Executes a program in the current process.
 *
 * This system call replaces the current process image with a new program specified by the
 * `path` argument. It loads the program located at the given `path` and passes the arguments
 * (`argv`) and environment variables (`envp`) to it. This effectively replaces the calling
 * process with a new one, and if successful, it never returns. If there is an error, the current
 * process continues to execute, and an error code is returned.
 *
 * @param[in]  path   The path to the executable file to be executed. This should be an
 *                    absolute or relative file path to the program.
 * @param[in]  argv   An array of arguments to pass to the new program. The first element
 *                    (`argv[0]`) should typically be the name of the program, and the array
 *                    should be terminated with a `NULL` pointer.
 * @param[in]  envp   An array of environment variables to pass to the new program. This is
 *                    typically in the form of `key=value` strings, with the array terminated
 *                    by a `NULL` pointer.
 *
 * @return sysret_t  Returns a status code:
 *                    - `0`: The program was successfully executed (this value is
 *                      never returned since the process is replaced).
 *                   - Other error codes may indicate issues with the program execution
 *
 * @note If `execve` is successful, it does not return to the calling function. The process
 *       image is replaced by the new program.
 */
sysret_t sys_execve(const char *path, char * const argv[], char * const envp[])
{
    rt_err_t error = -1;
    size_t len;
    struct rt_lwp *new_lwp = NULL;
    struct rt_lwp *lwp;
    int uni_thread;
    rt_thread_t thread;
    struct process_aux *aux;
    struct lwp_args_info args_info;
    char *kpath = RT_NULL;

    lwp = lwp_self();
    thread = rt_thread_self();
    uni_thread = 1;

    LWP_LOCK(lwp);
    if (lwp->t_grp.prev != &thread->sibling)
    {
        uni_thread = 0;
    }
    if (lwp->t_grp.next != &thread->sibling)
    {
        uni_thread = 0;
    }
    LWP_UNLOCK(lwp);

    if (!uni_thread)
    {
        return -EINVAL;
    }

    len = lwp_user_strlen(path);
    if (len <= 0)
    {
        return -EFAULT;
    }

    kpath = rt_malloc(len + 1);
    if (!kpath)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(kpath, (void *)path, len) != len)
    {
        rt_free(kpath);
        return -EFAULT;
    }
    kpath[len] = '\0';

    if (access(kpath, X_OK) != 0)
    {
        error = rt_get_errno();
        rt_free(kpath);
        return (sysret_t)error;
    }

    /* setup args */
    error = lwp_args_init(&args_info);
    if (error)
    {
        rt_free(kpath);
        return -ENOMEM;
    }

    if (argv)
    {
        error = lwp_args_put_argv(&args_info, (void *)argv);
        if (error)
        {
            error = -EFAULT;
            goto quit;
        }
    }

    if (envp)
    {
        error = lwp_args_put_envp(&args_info, (void *)envp);
        if (error)
        {
            error = -EFAULT;
            goto quit;
        }
    }

    /* alloc new lwp to operation */
    new_lwp = lwp_create(LWP_CREATE_FLAG_NONE);
    if (!new_lwp)
    {
        error = -ENOMEM;
        goto quit;
    }

    error = lwp_user_space_init(new_lwp, 0);
    if (error != 0)
    {
        error = -ENOMEM;
        goto quit;
    }

    /* file is a script ? */
    path = kpath;
    while (1)
    {
        error = lwp_args_load_script(&args_info, path);
        if (error != 0)
        {
            break;
        }
        path = lwp_args_get_argv_0(&args_info);
    }

    /* now load elf */
    if ((aux = lwp_argscopy(new_lwp, &args_info)) == NULL)
    {
        error = -ENOMEM;
        goto quit;
    }
    error = lwp_load(path, new_lwp, RT_NULL, 0, aux);
    if (error == RT_EOK)
    {
        int off = 0;
        int last_backslash = 0;

        /* clear all user objects */
        lwp_user_object_clear(lwp);

        /* find last \ or / to get base name */
        while (1)
        {
            char c = path[off++];

            if (c == '\0')
            {
                break;
            }
            if (c == '\\' || c == '/')
            {
                last_backslash = off;
            }
        }

        /**
         * Set thread name and swap the data of lwp and new_lwp.
         * Since no other threads can access the lwp field, it't uneccessary to
         * take a lock here
         */
        RT_ASSERT(rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling) == thread);

        strncpy(thread->parent.name, path + last_backslash, RT_NAME_MAX - 1);
        strncpy(lwp->cmd, new_lwp->cmd, RT_NAME_MAX);
        rt_free(lwp->exe_file);
        lwp->exe_file = strndup(new_lwp->exe_file, DFS_PATH_MAX);

#ifdef ARCH_MM_MMU
        _swap_lwp_data(lwp, new_lwp, struct rt_aspace *, aspace);
        _swap_lwp_data(lwp, new_lwp, size_t, end_heap);
#endif

        _swap_lwp_data(lwp, new_lwp, uint8_t, lwp_type);
        _swap_lwp_data(lwp, new_lwp, void *, text_entry);
        _swap_lwp_data(lwp, new_lwp, uint32_t, text_size);
        _swap_lwp_data(lwp, new_lwp, void *, data_entry);
        _swap_lwp_data(lwp, new_lwp, uint32_t, data_size);

        _swap_lwp_data(lwp, new_lwp, void *, args);

        lwp_thread_signal_detach(&thread->signal);
        rt_memset(&thread->signal.sigset_mask, 0, sizeof(thread->signal.sigset_mask));

        lwp_signal_detach(&lwp->signal);
        lwp_signal_init(&lwp->signal);

        /* to do: clsoe files with flag CLOEXEC, recy sub-thread */

        lwp_aspace_switch(thread);

        lwp_ref_dec(new_lwp);
        arch_start_umode(lwp->args,
                         lwp->text_entry,
                         (void *)USER_STACK_VEND,
                         (char *)thread->stack_addr + thread->stack_size);
        /* never reach here */
    }
    error = -EINVAL;
quit:
    if (kpath)
    {
        rt_free(kpath);
    }
    lwp_args_detach(&args_info);
    if (new_lwp)
    {
        lwp_ref_dec(new_lwp);
    }
    return error;
}
#endif /* ARCH_MM_MMU */

/**
 * @brief Deletes a thread.
 *
 * This system call is used to delete an existing thread. The specified thread is terminated,
 * and its resources are released. If the thread is currently running, it will be forcefully
 * terminated. The thread identifier (`thread`) refers to the thread that is to be deleted.
 *
 * @param[in] thread   The identifier of the thread to be deleted.
 *
 * @return sysret_t    Returns a status code:
 *                      - `SYSRET_OK`: The thread was successfully deleted.
 *                     - Other error codes may indicate additional failures.
 *
 * @note This function should be used carefully, as forcefully terminating a thread may
 *       lead to resource leaks or inconsistent state if the thread is performing critical
 *       operations at the time of termination.
 *
 * @warning Ensure that the thread being deleted has completed its necessary operations
 *          and that there are no outstanding resources or critical tasks before deleting
 *          it. Otherwise, it might lead to undefined behavior or resource leaks.
 */
sysret_t sys_thread_delete(rt_thread_t thread)
{
#ifdef ARCH_MM_MMU
    return rt_thread_delete(thread);
#else
    sysret_t ret = 0;

    if (thread->parent.type != RT_Object_Class_Thread)
    {
        ret = -EINVAL;
        goto __exit;
    }

    ret = rt_thread_delete(thread);

    if (rt_thread_self() == thread)
    {
        rt_schedule();
    }

__exit:
    return ret;
#endif
}

/**
 * @brief Starts a previously created thread.
 *
 * This system call is used to start a thread that was created but has not yet started running.
 * It initiates the thread's execution, allowing it to begin performing its assigned task.
 * The `thread` parameter refers to the thread that is to be started.
 *
 * @param[in] thread   The identifier of the thread to be started.
 *
 * @return sysret_t    Returns a status code:
 *                      - `0`: The thread was successfully started.
 *                      - Other error codes may indicate additional failures.
 *
 * @warning Ensure that the thread has been correctly initialized and is in a valid state
 *          before calling this function to avoid undefined behavior. Improper initialization
 *          could lead to issues such as the thread not running as expected.
 */
sysret_t sys_thread_startup(rt_thread_t thread)
{
    return rt_thread_startup(thread);
}

/**
 * @brief Retrieves the identifier of the current thread.
 *
 * This system call returns the thread identifier of the currently executing thread. It allows
 * a thread to obtain its own identifier, which can be useful for various thread management
 * tasks such as self-identification, logging, or checking the thread's status.
 *
 * @return rt_thread_t  The identifier of the current thread.
 *                      If no thread is currently executing, a null or invalid thread ID
 *                      might be returned depending on the system's implementation.
 *
 * @note This function is typically used when a thread needs to identify itself, especially
 *       in cases where thread management is performed dynamically or the thread identifier
 *       is required for synchronization or debugging purposes.
 *
 * @warning Be aware that in environments where there is no concept of threads or if the
 *          current context is not a thread (e.g., during interrupt handling or early system
 *          initialization), the return value might be invalid.
 */
rt_thread_t sys_thread_self(void)
{
    return rt_thread_self();
}

/**
 * @brief Finds a thread by its name.
 *
 * This system call is used to search for a thread based on its name. It returns a reference to the
 * thread if found, otherwise it returns `RT_NULL`. The name comparison is case-sensitive.
 *
 * @param[in] name    The name of the thread to search for. This should be a valid string that
 *                    uniquely identifies the thread within the system.
 *
 * @return rt_thread_t   The thread object corresponding to the given name, or `RT_NULL` if no
 *                        matching thread was found.
 *
 * @note The thread name is typically assigned when the thread is created, and it can be used to
 *       identify threads in the system.
 *
 * @warning Ensure that the `name` string is correctly set and unique within the system to avoid
 *          unexpected behavior.
 *
 * @see sys_thread_create(), sys_thread_delete()
 */
rt_thread_t sys_thread_find(char *name)
{
    int len = 0;
    char *kname = RT_NULL;
    rt_thread_t thread;

    len = lwp_user_strlen(name);
    if (len <= 0)
    {
        return RT_NULL;
    }

    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        return RT_NULL;
    }

    if (lwp_get_from_user(kname, (void *)name, len + 1) != (len + 1))
    {
        kmem_put(kname);
        return RT_NULL;
    }

    thread = rt_thread_find(name);

    kmem_put(kname);

    return thread;
}

/**
 * @brief Gets the current system tick count.
 *
 * This system call returns the current value of the system tick counter, which is typically incremented
 * at a fixed interval (e.g., every millisecond or microsecond). The tick count can be used for timing
 * purposes, such as measuring the elapsed time or triggering time-based events.
 *
 * @return rt_tick_t    The current value of the system tick counter.
 *
 * @note The system tick counter typically wraps around after reaching its maximum value, so the
 *       returned tick value may reset after a certain period of time, depending on the configuration
 *       of the system tick timer.
 *
 * @warning Be cautious when using the tick value for time-based calculations, as the counter may
 *          overflow and wrap around. Ensure that the code handling the tick count properly accounts
 *          for potential overflow.
 *
 * @see sys_tick_init(), sys_tick_delay()
 */
rt_tick_t sys_tick_get(void)
{
    return rt_tick_get();
}

/**
 * @brief Delays the current thread for a specified number of milliseconds.
 *
 * This system call puts the calling thread to sleep for a given number of milliseconds. It is a blocking
 * call, meaning the thread will not execute any further instructions until the specified delay has
 * passed. The delay is achieved by the system's timer mechanism.
 *
 * @param[in] ms   The number of milliseconds to delay. The value must be a positive integer.
 *
 * @return sysret_t   Returns `0` on success, or a negative error code on failure.
 *
 * @note This function is useful for introducing a fixed delay in time-sensitive applications or when
 *       the thread needs to be paused before continuing execution.
 *
 * @warning Be cautious when using this function in real-time or time-critical applications, as
 *          excessive delays may affect overall system performance or responsiveness.
 *
 * @see sys_thread_delay(), sys_thread_sleep()
 */
sysret_t sys_thread_mdelay(rt_int32_t ms)
{
    return rt_thread_mdelay(ms);
}

/**
 * @brief Retrieves the current value of the error code.
 *
 * This function returns the most recent error code set by a system call. The error code is typically set
 * when a system call fails. This function allows users to retrieve the last error that occurred, helping to
 * diagnose issues or handle errors in a more controlled manner.
 *
 * @return sysret_t  The current error code. A value of `0` indicates no error, while a non-zero value
 *                   represents the most recent error. The error codes are system-specific and can
 *                   represent various failure conditions (e.g., `EINVAL`, `ENOMEM`, `EIO`).
 *
 * @note The error code returned is specific to the current thread or process and is typically updated
 *       each time a system call fails. The error code is persistent until it is overwritten by the next
 *       failed system call or explicitly reset.
 *
 * @see sys_set_errno(), sys_perror(), sys_strerror()
 */
/**
 * @brief Retrieves the current thread's error code.
 *
 * @return sysret_t The current error code.
 */
sysret_t sys_get_errno(void)
{
    return rt_get_errno();
}

#ifdef ARCH_MM_MMU

/**
 * @brief Sets the thread-specific data area.
 *
 * This function is used to associate a specific area of memory with the current thread. The area pointed to
 * by `p` is set as the thread's local storage. Thread-specific data is used to store data that is unique to
 * each thread, allowing different threads to maintain independent state information.
 *
 * @param[in] p  A pointer to the memory area that is to be set as the thread's local storage. This area
 *               will be used by the thread to store its specific data. The structure and size of the data
 *               area depend on the implementation and use case.
 *
 * @return sysret_t   Returns `0` on success. On failure, it returns a negative error code.
 *
 * @note This function is typically used to set up thread-specific storage for managing data that should
 *       not be shared between threads. The data area is accessible only by the thread that set it, ensuring
 *       thread safety for the stored information.
 *
 * @see sys_get_thread_area(), sys_thread_create(), sys_thread_self()
 */
sysret_t sys_set_thread_area(void *p)
{
    rt_thread_t thread;

    thread = rt_thread_self();
    thread->thread_idr = p;
    arch_set_thread_area(p);

    return 0;
}

/**
 * @brief Sets the address at which the thread ID is stored.
 *
 * This function sets the address of a variable that will store the thread ID for the calling thread.
 * The specified address `tidptr` will hold the thread's unique identifier. This can be useful for
 * managing thread-specific state or for synchronization mechanisms where the thread's ID needs to be
 * shared or checked by other parts of the system.
 *
 * @param[in] tidptr  A pointer to an integer where the thread ID will be stored. This value will
 *                    hold the calling thread's ID, and it can be accessed to identify the thread
 *                    later. The value of the thread ID can be used in various thread management
 *                    operations.
 *
 * @return sysret_t   Returns `0` on success. On failure, returns a negative error code.
 *
 * @note This function is typically used in systems that require associating a specific address with the
 *       thread ID, often in real-time or embedded systems where managing and accessing thread IDs is
 *       crucial for scheduling or resource allocation.
 *
 * @see sys_get_tid(), sys_thread_self(), sys_thread_create()
 */
sysret_t sys_set_tid_address(int *tidptr)
{
    rt_thread_t thread;

#ifdef ARCH_MM_MMU
    if (!lwp_user_accessable((void *)tidptr, sizeof(int)))
    {
        return -EFAULT;
    }
#endif
    thread = rt_thread_self();
    thread->clear_child_tid = tidptr;
    return thread->tid;
}
#endif /* ARCH_MM_MMU */

/**
 * @brief Gets the thread ID of the calling thread.
 *
 * This function returns the unique thread identifier (thread ID) for the calling thread. The thread ID
 * can be used to uniquely identify the thread within the system and is typically used for debugging,
 * thread management, or scheduling purposes.
 *
 * @return sysret_t   The thread ID of the calling thread. The value is typically a positive integer
 *                     representing the unique ID assigned to the thread. In case of failure, an error code
 *                     may be returned.
 *
 * @note The thread ID returned by this function is unique within the system, and it may be used to
 *       reference or manipulate the specific thread associated with the ID.
 *
 * @see sys_set_tid_address(), sys_thread_self(), sys_thread_create()
 */
sysret_t sys_gettid(void)
{
    return rt_thread_self()->tid;
}

/**
 * @brief Checks the accessibility of a file or directory.
 *
 * This function checks whether the calling process has the specified access rights for the given file or directory.
 * The check is performed based on the provided `mode`, which can indicate whether read, write, or execute permissions
 * are required.
 *
 * @param[in] filename  The path to the file or directory whose accessibility is being checked.
 * @param[in] mode      The access mode to check for. This can be a combination of the following:
 *                      - `R_OK`: Check for read permission.
 *                      - `W_OK`: Check for write permission.
 *                      - `X_OK`: Check for execute permission.
 *                      - `F_OK`: Check if the file exists.
 *
 * @return sysret_t     Returns `0` if the specified access is allowed. On failure, returns a negative error code.
 *
 * @note This function does not modify the file or directory, it only checks if the specified access rights are granted.
 *
 * @see sys_open(), sys_stat(), sys_fstat(), sys_chmod(), sys_chown()
 */
