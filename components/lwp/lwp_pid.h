/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-02-23     Jesven         first version.
 */

#ifndef LWP_PID_H__
#define LWP_PID_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rtthread.h>

#define LWP_CREATE_FLAG_NONE         0x0000
#define LWP_CREATE_FLAG_ALLOC_PID    0x0001  /* allocate pid on lwp object create */
#define LWP_CREATE_FLAG_INIT_USPACE  0x0002  /* do user space initialization */
#define LWP_CREATE_FLAG_NOTRACE_EXEC 0x0004  /* not trace if execve() after fork() */

struct rt_lwp;

struct lwp_avl_struct *lwp_get_pid_ary(void);
int lwp_pid_init(void);
int lwp_pid_wait_for_empty(int wait_flags, rt_tick_t to);
int lwp_pid_for_each(int (*cb)(pid_t pid, void *data), void *data);
void lwp_pid_put(struct rt_lwp *lwp);
void lwp_pid_lock_take(void);
void lwp_pid_lock_release(void);

/**
 * @brief Create a new lwp object
 *        This will initialize the member in the object and register to system.
 *        Besides, a new pid is allocate with lwp
 *
 * @param flags control the property of the lwp object. Can be ORed with:
 *        LWP_CREATE_FLAG_NONE: raw lwp object
 *        LWP_CREATE_FLAG_ALLOC_PID: lwp object with specified pid
 *
 * @return struct rt_lwp* object
 */
struct rt_lwp* lwp_create(rt_base_t flags);

void lwp_free(struct rt_lwp* lwp);

int lwp_ref_inc(struct rt_lwp *lwp);
int lwp_ref_dec(struct rt_lwp *lwp);

struct rt_lwp* lwp_from_pid_raw_locked(pid_t pid);
struct rt_lwp* lwp_from_pid_locked(pid_t pid);
pid_t lwp_to_pid(struct rt_lwp* lwp);

pid_t lwp_name2pid(const char* name);
char* lwp_pid2name(int32_t pid);

int lwp_getpid(void);

/**
 * @brief Resource usage statistics structure
 *
 * @note The structure tracks various system resource usage statistics for a process,
 * including CPU time, memory usage, I/O operations, and context switches.
 * It follows the traditional Unix rusage structure format.
 */
struct rusage
{
    struct timeval ru_utime;   /**< User CPU time */
    struct timeval ru_stime;   /**< System CPU time */

    long ru_maxrss;            /**< Maximum resident set size */
    long ru_ixrss;             /**< Integral shared memory size */
    long ru_idrss;             /**< Integral unshared data size */
    long ru_isrss;             /**< Integral unshared stack size */
    long ru_minflt;            /**< Page reclaims (soft page faults) */
    long ru_majflt;            /**< Page faults (hard page faults) */
    long ru_nswap;             /**< Swaps */
    long ru_inblock;           /**< Block input operations */
    long ru_oublock;           /**< Block output operations */
    long ru_msgsnd;            /**< IPC messages sent */
    long ru_msgrcv;            /**< IPC messages received */
    long ru_nsignals;          /**< Signals received */
    long ru_nvcsw;             /**< voluntary context switches */
    long ru_nivcsw;            /**< involuntary context switches */
    long reserved[16];         /**< Reserved for future use */
};
pid_t lwp_waitpid(const pid_t pid, int *status, int options, struct rusage *ru);
rt_err_t lwp_waitpid_kick(struct rt_lwp *parent, struct rt_lwp *self_lwp);
pid_t waitpid(pid_t pid, int *status, int options);
long list_process(void);

void lwp_user_object_lock_init(struct rt_lwp *lwp);
void lwp_user_object_lock_destroy(struct rt_lwp *lwp);
void lwp_user_object_lock(struct rt_lwp *lwp);
void lwp_user_object_unlock(struct rt_lwp *lwp);
int lwp_user_object_add(struct rt_lwp *lwp, rt_object_t object);
rt_err_t lwp_user_object_delete(struct rt_lwp *lwp, rt_object_t object);
void lwp_user_object_clear(struct rt_lwp *lwp);
void lwp_user_object_dup(struct rt_lwp *dst_lwp, struct rt_lwp *src_lwp);

rt_inline struct rt_lwp *lwp_from_pid_and_lock(pid_t pid)
{
    struct rt_lwp *lwp;
    lwp_pid_lock_take();
    lwp = lwp_from_pid_locked(pid);
    if (lwp)
        lwp_ref_inc(lwp);
    lwp_pid_lock_release();

    return lwp;
}

rt_inline void lwp_from_pid_release_lock(struct rt_lwp *lwp)
{
    if (lwp)
        lwp_ref_dec(lwp);
}

typedef rt_base_t lwp_status_t;
void lwp_thread_exit(rt_thread_t thread, int status);
void lwp_exit(struct rt_lwp *lwp, lwp_status_t status);

#ifdef __cplusplus
}
#endif

#endif
