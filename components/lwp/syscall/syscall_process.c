/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "syscall_internal.h"

/**
 * @brief Terminates all threads in the current thread group.
 *
 * This system call ends execution for all threads within the same thread group,
 * releasing resources such as memory and file descriptors. It is typically used
 * in multithreaded environments to ensure a clean exit for the entire process.
 *
 * @param value The exit code to be returned to the parent process.
 * @return sysret_t: return value of the system call execution.
 */
sysret_t sys_exit_group(int value)
{
    sysret_t rc = 0;
    lwp_status_t lwp_status;
    struct rt_lwp *lwp = lwp_self();

    if (lwp)
    {
        lwp_status = LWP_CREATE_STAT_EXIT(value);
        lwp_exit(lwp, lwp_status);
    }
    else
    {
        LOG_E("Can't find matching process of current thread");
        rc = -EINVAL;
    }

    return rc;
}

/**
 * @brief Terminates the calling thread and exits the process.
 *
 * This system call ends the execution of the calling thread and the process
 * it belongs to.
 *
 * @param status The exit code to be returned to the parent process.
 *               A value of 0 typically indicates successful execution, while
 *               non-zero values indicate an error or specific exit condition.
 * @return sysret_t: return value of the system call execution.
 *
 * @note Unlike `sys_exit_group`, which terminates all threads in a thread group,
 *       `sys_exit` only terminates the calling thread and the process.
 */
sysret_t sys_exit(int status)
{
    sysret_t rc = 0;
    rt_thread_t tid;

    tid = rt_thread_self();
    if (tid && tid->lwp)
    {
        lwp_thread_exit(tid, status);
    }
    else
    {
        LOG_E("Can't find matching process of current thread");
        rc = -EINVAL;
    }

    return rc;
}

/**
 * @brief Replaces the current process with a new process.
 *
 * This system call loads a new program into the current process's address space,
 * replacing the current program with the one specified by `filename`. It passes the
 * arguments `argv` and environment variables `envp` to the new program. If the execution
 * is successful, the current process is completely replaced, and no code after the
 * `sys_exec` call is executed. If an error occurs, the system call returns, and the
 * current process continues executing.
 *
 * @param filename The path to the executable file to be run. This can be an absolute
 *                 or relative path.
 * @param argc The number of arguments passed to the new program. This includes the
 *             executable name itself as the first argument.
 * @param argv An array of strings (character pointers), where each string is an argument
 *             passed to the new program. The first element (`argv[0]`) is conventionally
 *             the name of the executable.
 * @param envp An array of strings representing the environment variables for the new
 *             process. The array is terminated by a `NULL` pointer.
 * @return This function does not return on success, as the current process is replaced.
 *         On failure, it returns error code to indicate the error.
 *
 * @note The new process inherits most of the attributes of the current process, such
 *       as file descriptors, unless explicitly modified. It is important that `argv`
 *       and `envp` are properly formatted, and the `filename` points to a valid executable.
 *
 * @warning If `filename` is invalid or not an executable, or if the arguments or
 *          environment variables are incorrectly set, the system call will fail and
 *          return `-1`. Ensure that the executable file is accessible and that `argv`
 *          and `envp` are properly constructed.
 *
 * @see execve(), execvp(), execv(), execle()
 */
sysret_t sys_exec(char *filename, int argc, char **argv, char **envp)
{
    int ret = 0;
    int len = 0;
    char *kfilename = RT_NULL;

    len = lwp_user_strlen(filename);
    if (len <= 0)
    {
        return -EFAULT;
    }

    kfilename = (char *)kmem_get(len + 1);
    if (!kfilename)
    {
        return -ENOMEM;
    }

    if (lwp_get_from_user(kfilename, (void *)filename, len + 1) != (len + 1))
    {
        kmem_put(kfilename);
        return -EFAULT;
    }

    ret = lwp_execve(kfilename, 0, argc, argv, envp);

    kmem_put(kfilename);

    return ret;
}

/**
 * @brief Sends a signal to a process or a group of processes.
 *
 * This system call sends the signal specified by `signo` to the process or process group
 * identified by `pid`. If `pid` is positive, the signal is sent to the process with the
 * specified process ID. If `pid` is `0`, the signal is sent to all processes in the
 * same process group as the caller. If `pid` is `-1`, the signal is sent to all processes
 * except for the caller. If `pid` is less than `-1`, the signal is sent to all processes
 * in the process group with the process group ID equal to `-pid`.
 *
 * @param pid The process ID or process group ID to which the signal is to be sent.
 *            - A positive value sends the signal to the process with that ID.
 *            - `0` sends the signal to all processes in the same process group as the caller.
 *            - `-1` sends the signal to all processes except the caller.
 *            - A negative value sends the signal to all processes in the process group
 *              with the process group ID equal to `-pid`.
 * @param signo The signal to send. This is an integer value that specifies the signal
 *              type. Common signal values include:
 *              - `SIGTERM` (terminate process)
 *              - `SIGKILL` (force kill process)
 *              - `SIGSTOP` (suspend process)
 *              - `SIGCONT` (resume process)
 * @return On success, returns `0`. On failure, it returns error code to indicate the error.
 *
 * @note Signals are a mechanism for inter-process communication, allowing processes
 *       to send notifications or requests to other processes. The behavior of signals
 *       depends on the signal type and how the receiving process handles them.
 *
 * @warning The `signo` value must be a valid signal number. Passing an invalid signal
 *          number or an invalid `pid` may result in an error. Additionally, some signals
 *          (e.g., `SIGKILL`) cannot be caught or ignored by processes.
 *
 * @see signal(), killpg(), raise()
 */
sysret_t sys_kill(int pid, int signo)
{
    rt_err_t kret = 0;
    sysret_t sysret;
    struct rt_lwp *lwp = RT_NULL;

    /* handling the semantics of sys_kill */
    if (pid > 0)
    {
        /**
         * Brief: Match the pid and send signal to the lwp if found
         * Note: Critical Section
         * - pid tree (READ. since the lwp is fetch from the pid tree, it must stay there)
         */
        lwp_pid_lock_take();
        lwp = lwp_from_pid_raw_locked(pid);
        if (lwp)
        {
            lwp_ref_inc(lwp);
            lwp_pid_lock_release();
        }
        else
        {
            lwp_pid_lock_release();
            kret = -RT_ENOENT;
        }

        if (lwp)
        {
            kret = lwp_signal_kill(lwp, signo, SI_USER, 0);
            lwp_ref_dec(lwp);
        }
    }
    else if (pid < -1 || pid == 0)
    {
        pid_t pgid = 0;
        rt_processgroup_t group;

        if (pid == 0)
        {
            /**
             * sig shall be sent to all processes (excluding an unspecified set
             * of system processes) whose process group ID is equal to the process
             * group ID of the sender, and for which the process has permission to
             * send a signal.
             */
            pgid = lwp_pgid_get_byprocess(lwp_self());
        }
        else
        {
            /**
             * sig shall be sent to all processes (excluding an unspecified set
             * of system processes) whose process group ID is equal to the absolute
             * value of pid, and for which the process has permission to send a signal.
             */
            pgid = -pid;
        }

        group = lwp_pgrp_find(pgid);
        if (group != RT_NULL)
        {
            PGRP_LOCK(group);
            kret = lwp_pgrp_signal_kill(group, signo, SI_USER, 0);
            PGRP_UNLOCK(group);
        }
        else
        {
            kret = -ECHILD;
        }
    }
    else if (pid == -1)
    {
        /**
         * sig shall be sent to all processes (excluding an unspecified set
         * of system processes) for which the process has permission to send
         * that signal.
         */
        kret = lwp_signal_kill_all(signo, SI_USER, 0);
    }

    switch (kret)
    {
    case -RT_ENOENT:
    case -ECHILD:
        sysret = -ESRCH;
        break;
    case -RT_EINVAL:
        sysret = -EINVAL;
        break;
    case -RT_ENOSYS:
        sysret = -ENOSYS;
        break;

        /**
         * kill() never returns ENOMEM, so return normally to caller.
         * IEEE Std 1003.1-2017 says the kill() function is successful
         * if the process has permission to send sig to any of the
         * processes specified by pid.
         */
    case -RT_ENOMEM:
    default:
        sysret = 0;
    }
    return sysret;
}

/**
 * @brief Retrieves the process ID of the calling process.
 *
 * This system call returns the process ID (PID) of the calling process. The PID is a
 * unique identifier assigned by the operating system to each running process. It can
 * be used to refer to or manipulate the process in subsequent system calls.
 *
 * @return The PID of the calling process. On failure, returns `-1` and sets `errno`
 *         to indicate the error (although this function typically does not fail).
 *
 * @note The PID returned by this function is a positive integer, and it remains
 *       unique during the lifetime of the process. This value can be used to manage
 *       the process, including sending signals or querying process information.
 *
 * @warning This function does not take any arguments and is typically used when
 *          a process needs to obtain its own PID for management or logging purposes.
 *
 * @see getppid(), getuid(), getgid()
 */
sysret_t sys_getpid(void)
{
    return lwp_getpid();
}

/**
 * @brief Retrieves the parent process ID of the calling process.
 *
 * This system call returns the process ID (PID) of the parent process of the calling process.
 * The parent process is the process that created the calling process, typically through a
 * system call like `fork()`. This information can be useful for process management and
 * for determining the hierarchy of processes.
 *
 * @return The PID of the parent process. If the calling process has no parent (for example,
 *         the init process), it typically returns `1` as the PID of the system's "root" process.
 *         On failure, returns `-1` and sets `errno` to indicate the error (although this function
 *         typically does not fail).
 *
 * @note The `getppid()` function is commonly used when a process needs to know which
 *       process is responsible for it, or for managing relationships between parent and child processes.
 *
 * @warning This function does not take any arguments and is typically used when the
 *          process requires information about its parent. It should not be confused with `getpid()`,
 *          which retrieves the PID of the calling process itself.
 *
 * @see getpid(), getuid(), getgid()
 */
sysret_t sys_getppid(void)
{
    rt_lwp_t process;

    process = lwp_self();
    if (process->parent == RT_NULL)
    {
        LOG_E("%s: process %d has no parent process", __func__, lwp_to_pid(process));
        return 0;
    }
    else
    {
        return lwp_to_pid(process->parent);
    }
}

/**
 * @brief Retrieves the priority of a process or process group.
 *
 * This system call returns the priority of a process or a process group, depending on
 * the value of the `which` argument.
 *
 * @param which The entity for which the priority is being requested. Possible values include:
 *              - `PRIO_PROCESS`: Retrieves the priority of the process specified by `who`.
 *              - `PRIO_PGRP`: Retrieves the priority of the process group specified by `who`. (Currently not supported.)
 *              - `PRIO_USER`: Retrieves the priority of the user specified by `who` (the user ID). (Currently not supported.)
 * @param who The ID of the process, process group, or user. The meaning of this parameter
 *            depends on the value of `which`:
 *            - When `which` is `PRIO_PROCESS`, `who` is the process ID (PID) of the process.
 *            - When `which` is `PRIO_PGRP`(Currently not supported.), `who` is the process group ID (PGID).
 *            - When `which` is `PRIO_USER`(Currently not supported.), `who` is the user ID (UID) of the user whose
 *              priority is being queried.
 * @return On success, returns the priority value (a negative integer indicates a lower
 *         priority).
 *
 * @warning Ensure that `which` and `who` are correctly specified to avoid errors.
 *          Invalid values for `which` or `who` may result in an error, and the function
 *          will return `-1`.
 *
 * @see setpriority(), getpid(), getppid()
 */
sysret_t sys_getpriority(int which, id_t who)
{
    long prio = 0xff;

    if (which == PRIO_PROCESS)
    {
        struct rt_lwp *lwp = RT_NULL;

        lwp_pid_lock_take();
        lwp = lwp_from_pid_locked(who);

        if (lwp)
        {
            rt_thread_t thread = rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling);
            prio = RT_SCHED_PRIV(thread).current_priority;
        }

        lwp_pid_lock_release();
    }

    return prio;
}

/**
 * @brief Sets the priority of a process, process group, or user.
 *
 * This system call sets the priority of a process, process group, or user, depending
 * on the value of the `which` argument. The priority is used by the operating system
 * for scheduling processes. Lower numerical values represent higher priority in many
 * systems, and the priority range may be system-specific.
 *
 * @param which The entity for which the priority is being set. Possible values include:
 *              - `PRIO_PROCESS`: Sets the priority of the process specified by `who`.
 *              - `PRIO_PGRP`: Sets the priority of the process group specified by `who`.(Currently not supported.)
 *              - `PRIO_USER`: Sets the priority of the user specified by `who` (the user ID).(Currently not supported.)
 * @param who The ID of the process, process group, or user for which the priority is being set.
 *            The meaning of this parameter depends on the value of `which`:
 *            - When `which` is `PRIO_PROCESS`, `who` is the process ID (PID) of the process.
 *            - When `which` is `PRIO_PGRP`(Currently not supported.)  , `who` is the process group ID (PGID).
 *            - When `which` is `PRIO_USER`(Currently not supported.)  , `who` is the user ID (UID) of the user whose priority
 *              is being set.
 * @param prio The priority value to set.
 * @return On success, returns `0`. On failure, returns `-1`.
 *
 * @note This function modifies the priority of the specified process, process group, or user.
 *       The priority value is system-specific and may vary based on the system's scheduling
 *       policies. Ensure that the specified priority is within the acceptable range.
 *
 * @warning Ensure that `which`, `who`, and `prio` are valid. Invalid values for these
 *          parameters can result in errors, and the system call will return `-1`.
 *
 * @see getpriority(), getpid(), getppid()
 */
sysret_t sys_setpriority(int which, id_t who, int prio)
{
    if (which == PRIO_PROCESS)
    {
        struct rt_lwp *lwp = RT_NULL;

        lwp_pid_lock_take();
        lwp = lwp_from_pid_locked(who);

        if (lwp && prio >= 0 && prio < RT_THREAD_PRIORITY_MAX)
        {
            rt_list_t *list;
            rt_thread_t thread;
            for (list = lwp->t_grp.next; list != &lwp->t_grp; list = list->next)
            {
                thread = rt_list_entry(list, struct rt_thread, sibling);
                rt_thread_control(thread, RT_THREAD_CTRL_RESET_PRIORITY, &prio);
            }
            lwp_pid_lock_release();
            return 0;
        }
        else
        {
            lwp_pid_lock_release();
        }
    }

    return -1;
}

/**
 * @brief Waits for a process to change state.
 *
 * This function suspends the execution of the calling process until one of its child processes terminates
 * or a specified process (identified by `pid`) changes its state. The function returns the process ID of the child
 * process that terminated, and provides information about its exit status and resource usage.
 *
 * @param[in]  pid      The process ID of the child process to wait for. The behavior of this parameter can be one of the following:
 *                      - `pid > 0`: Wait for the child process with the specified PID.
 *                      - `pid == 0`: Wait for any child process in the same process group.
 *                      - `pid == -1`: Wait for any child process (default behavior).
 *                      - `pid < -1`: Wait for any child process in the specified process group.
 *
 * @param[out] status   A pointer to an integer where the exit status of the terminated child process will be stored.
 *                      This status can be interpreted using macros such as `WIFEXITED` or `WIFSIGNALED`.
 *
 * @param[in]  options  Options for the wait operation, which can include:
 *                      - `WNOHANG`: Return immediately if no child has exited.
 *                      - `WUNTRACED`: Return if a child has stopped, but not yet terminated.
 *
 * @param[out] ru       A pointer to a `struct rusage` where resource usage information of the child process will be stored.
 *                      This includes information such as CPU time consumed by the child process.
 *
 * @return sysret_t     Returns the process ID of the terminated child on success. In case of failure, a negative error code is returned.
 *
 * @note This function is useful for monitoring and cleaning up child processes in parent-child relationships.
 *       The `status` value can be further analyzed to determine if the child process terminated normally or due to a signal.
 *
 * @see sys_waitpid(), sys_fork(), sys_exit()
 */
sysret_t sys_wait4(pid_t pid, int *status, int options, struct rusage *ru)
{
    return lwp_waitpid(pid, status, options, ru);
}
