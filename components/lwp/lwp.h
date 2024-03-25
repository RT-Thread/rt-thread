/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-06-29     heyuanjie    first version
 * 2019-10-12     Jesven       Add MMU and userspace support
 * 2020-10-08     Bernard      Architecture and code cleanup
 * 2021-08-26     linzhenxing  add lwp_setcwd\lwp_getcwd
 * 2023-11-17     xqyjlj       add process group and session support
 * 2023-12-02     Shell        Add macro to create lwp status and
 *                             fix dead lock problem on pgrp
 */

/*
 * RT-Thread light-weight process
 */
#ifndef __LWP_H__
#define __LWP_H__

#include <stdint.h>

#include <rthw.h>
#include <rtthread.h>
#include <dfs.h>

#include "lwp_arch.h"
#include "lwp_pid.h"
#include "lwp_ipc.h"
#include "lwp_signal.h"
#include "lwp_syscall.h"
#include "lwp_avl.h"
#include "mm_aspace.h"

#ifdef RT_USING_MUSLLIBC
#include "libc_musl.h"
#endif /* RT_USING_MUSLLIBC */

#ifdef ARCH_MM_MMU
#include "lwp_shm.h"
#include <locale.h>
#include "mmu.h"
#include "page.h"
#else
#include "lwp_mpu.h"
#endif /* ARCH_MM_MMU */

#ifdef RT_USING_MUSLLIBC
#include <locale.h>
#endif /* RT_USING_MUSLLIBC */

#ifdef __cplusplus
extern "C" {
#endif

#define LWP_MAGIC           0x5A

#define LWP_TYPE_FIX_ADDR   0x01
#define LWP_TYPE_DYN_ADDR   0x02

#define LWP_ARG_MAX         8

struct rt_lwp_objs
{
    rt_aspace_t source;
    struct rt_mem_obj mem_obj;
};

struct rt_lwp_notify
{
    void (*notify)(rt_wqueue_t *signalfd_queue, int signo);
    rt_wqueue_t *signalfd_queue;
    rt_slist_t list_node;
};

struct lwp_tty;

#ifdef RT_USING_MUSLLIBC
#define LWP_COREDUMP_FLAG                         0x80
#define LWP_CREATE_STAT_EXIT(exit_code)           (((exit_code)&0xff) << 8)
#define LWP_CREATE_STAT_SIGNALED(signo, coredump) (((signo) & 0x7f) | (coredump ? LWP_COREDUMP_FLAG : 0))
#define LWP_CREATE_STAT_STOPPED(signo)            (LWP_CREATE_STAT_EXIT(signo) | 0x7f)
#define LWP_CREATE_STAT_CONTINUED                 (0xffff)
#else
#error "No compatible lwp set status provided for this libc"
#endif

typedef struct rt_lwp *rt_lwp_t;
typedef struct rt_session *rt_session_t;
typedef struct rt_processgroup *rt_processgroup_t;

struct rt_session {
    struct rt_object    object;
    rt_lwp_t            leader;
    rt_list_t           processgroup;
    pid_t               sid;
    pid_t               foreground_pgid;
    struct rt_mutex     mutex;
    struct lwp_tty      *ctty;
};

struct rt_processgroup {
    struct rt_object    object;
    rt_lwp_t            leader;
    rt_list_t           process;
    rt_list_t           pgrp_list_node;
    pid_t               pgid;
    pid_t               sid;
    struct rt_session   *session;
    struct rt_mutex     mutex;

    rt_atomic_t         ref;

    /* flags on process group */
    unsigned int is_orphaned:1;
};

struct rt_lwp
{
#ifdef ARCH_MM_MMU
    size_t end_heap;
    rt_aspace_t aspace;
#else
#ifdef ARCH_MM_MPU
    struct rt_mpu_info mpu_info;
#endif /* ARCH_MM_MPU */
#endif /* ARCH_MM_MMU */

#ifdef RT_USING_SMP
    int bind_cpu;
#endif

    uint8_t lwp_type;
    uint8_t reserv[3];

    /* flags */
    unsigned int terminated:1;
    unsigned int background:1;
    unsigned int term_ctrlterm:1;  /* have control terminal? */
    unsigned int did_exec:1;       /* Whether exec has been performed */
    unsigned int jobctl_stopped:1; /* job control: current proc is stopped */
    unsigned int wait_reap_stp:1;  /* job control: has wait event for parent */
    unsigned int sig_protected:1;  /* signal: protected proc cannot be killed or stopped */

    struct rt_lwp *parent;          /* parent process */
    struct rt_lwp *first_child;     /* first child process */
    struct rt_lwp *sibling;         /* sibling(child) process */

    struct rt_wqueue waitpid_waiters;
    lwp_status_t lwp_status;

    void *text_entry;
    uint32_t text_size;
    void *data_entry;
    uint32_t data_size;

    rt_atomic_t ref;
    void *args;
    uint32_t args_length;
    pid_t pid;
    pid_t sid;                      /* session ID */
    pid_t pgid;                     /* process group ID */
    struct rt_processgroup *pgrp;
    rt_list_t pgrp_node;            /* process group node */
    rt_list_t t_grp;                /* thread group */
    rt_list_t timer;                /* POSIX timer object binding to a process */

    struct dfs_fdtable fdt;
    char cmd[RT_NAME_MAX];
    char *exe_file;                 /* process file path */

    /* POSIX signal */
    struct lwp_signal signal;

    struct lwp_avl_struct *object_root;
    struct rt_mutex object_mutex;
    struct rt_user_context user_ctx;

    struct rt_wqueue wait_queue; /* for console */
    struct tty_struct *tty; /* NULL if no tty */

    struct lwp_avl_struct *address_search_head; /* for addressed object fast search */
    char working_directory[DFS_PATH_MAX];

    int debug;
    rt_uint32_t bak_first_inst; /* backup of first instruction */

    struct rt_mutex lwp_lock;

    rt_slist_t signalfd_notify_head;

#ifdef LWP_ENABLE_ASID
    uint64_t generation;
    unsigned int asid;
#endif
    struct rusage rt_rusage;
};


struct rt_lwp *lwp_self(void);
rt_err_t lwp_children_register(struct rt_lwp *parent, struct rt_lwp *child);
rt_err_t lwp_children_unregister(struct rt_lwp *parent, struct rt_lwp *child);

enum lwp_exit_request_type
{
    LWP_EXIT_REQUEST_NONE = 0,
    LWP_EXIT_REQUEST_TRIGGERED,
    LWP_EXIT_REQUEST_IN_PROCESS,
};
struct termios *get_old_termios(void);
void lwp_setcwd(char *buf);
char *lwp_getcwd(void);
int  lwp_check_exit_request(void);
void lwp_terminate(struct rt_lwp *lwp);

int lwp_tid_init(void);
int lwp_tid_get(void);
void lwp_tid_put(int tid);

/**
 * @brief Automatically get a thread and increase a reference count
 *
 * @param tid queried thread ID
 * @return rt_thread_t
 */
rt_thread_t lwp_tid_get_thread_and_inc_ref(int tid);
rt_thread_t lwp_tid_get_thread_raw(int tid);
/**
 * @brief Decrease a reference count
 *
 * @param thread target thread
 */
void lwp_tid_dec_ref(rt_thread_t thread);

void lwp_tid_set_thread(int tid, rt_thread_t thread);

int lwp_execve(char *filename, int debug, int argc, char **argv, char **envp);

/*create by lwp_setsid.c*/
int setsid(void);
#ifdef ARCH_MM_MMU
void lwp_aspace_switch(struct rt_thread *thread);
#endif
void lwp_user_setting_save(rt_thread_t thread);
void lwp_user_setting_restore(rt_thread_t thread);

void lwp_uthread_ctx_save(void *ctx);
void lwp_uthread_ctx_restore(void);

int lwp_setaffinity(pid_t pid, int cpu);

pid_t exec(char *filename, int debug, int argc, char **argv);

/* ctime lwp API */
int timer_list_free(rt_list_t *timer_list);

rt_err_t lwp_futex_init(void);
rt_err_t lwp_futex(struct rt_lwp *lwp, int *uaddr, int op, int val,
                   const struct timespec *timeout, int *uaddr2, int val3);

/* processgroup api */
rt_inline pid_t lwp_pgid_get_bypgrp(rt_processgroup_t group)
{
    return group ? group->pgid : 0;
}

rt_inline pid_t lwp_pgid_get_byprocess(rt_lwp_t process)
{
    return process ? process->pgid : 0;
}
rt_processgroup_t lwp_pgrp_find(pid_t pgid);
void lwp_pgrp_dec_ref(rt_processgroup_t pgrp);
rt_processgroup_t lwp_pgrp_find_and_inc_ref(pid_t pgid);
rt_processgroup_t lwp_pgrp_create(rt_lwp_t leader);
int lwp_pgrp_delete(rt_processgroup_t group);

/**
 * Note: all the pgrp with process operation must be called in the context where
 * process lock is taken. This is protect us from a possible dead lock condition
 *
 * The order is mandatory in the case:
 *      PGRP_LOCK(pgrp);
 *      LWP_LOCK(p);
 *      ... bussiness logic
 *      LWP_UNLOCK(p);
 *      PGRP_UNLOCK(pgrp);
 */
int lwp_pgrp_insert(rt_processgroup_t group, rt_lwp_t process);
int lwp_pgrp_remove(rt_processgroup_t group, rt_lwp_t process);
int lwp_pgrp_move(rt_processgroup_t group, rt_lwp_t process);

int lwp_pgrp_update_children_info(rt_processgroup_t group, pid_t sid, pid_t pgid);

/* session api */
rt_inline pid_t lwp_sid_get_bysession(rt_session_t session)
{
    return session ? session->sid : 0;
}

rt_inline pid_t lwp_sid_get_bypgrp(rt_processgroup_t group)
{
    return group ? group->sid : 0;
}

rt_inline pid_t lwp_sid_get_byprocess(rt_lwp_t process)
{
    return process ? process->sid : 0;
}

rt_session_t lwp_session_find(pid_t sid);
rt_session_t lwp_session_create(struct rt_lwp *leader);
int lwp_session_delete(rt_session_t session);

/**
 * Note: all the session operation must be called in the context where
 * process lock is taken. This is protect us from a possible dead lock condition
 *
 * The order is mandatory in the case:
 *      PGRP_LOCK(pgrp);
 *      LWP_LOCK(p);
 *      ... bussiness logic
 *      LWP_UNLOCK(p);
 *      PGRP_UNLOCK(pgrp);
 */
int lwp_session_insert(rt_session_t session, rt_processgroup_t group);
int lwp_session_remove(rt_session_t session, rt_processgroup_t group);
int lwp_session_move(rt_session_t session, rt_processgroup_t group);
int lwp_session_update_children_info(rt_session_t session, pid_t sid);
int lwp_session_set_foreground(rt_session_t session, pid_t pgid);

/* complete the job control related bussiness on process exit */
void lwp_jobctrl_on_exit(struct rt_lwp *lwp);

#ifdef __cplusplus
}
#endif

#ifndef AUX_ARRAY_ITEMS_NR
#define AUX_ARRAY_ITEMS_NR 32
#endif

/* aux key */
#define AT_NULL 0
#define AT_IGNORE 1
#define AT_EXECFD 2
#define AT_PHDR 3
#define AT_PHENT 4
#define AT_PHNUM 5
#define AT_PAGESZ 6
#define AT_BASE 7
#define AT_FLAGS 8
#define AT_ENTRY 9
#define AT_NOTELF 10
#define AT_UID 11
#define AT_EUID 12
#define AT_GID 13
#define AT_EGID 14
#define AT_CLKTCK 17
#define AT_PLATFORM 15
#define AT_HWCAP 16
#define AT_FPUCW 18
#define AT_DCACHEBSIZE 19
#define AT_ICACHEBSIZE 20
#define AT_UCACHEBSIZE 21
#define AT_IGNOREPPC 22
#define AT_SECURE 23
#define AT_BASE_PLATFORM 24
#define AT_RANDOM 25
#define AT_HWCAP2 26
#define AT_EXECFN 31

struct process_aux_item
{
    size_t key;
    size_t value;
};

struct process_aux
{
    struct process_aux_item item[AUX_ARRAY_ITEMS_NR];
};

struct lwp_args_info
{
    char **argv;
    char **envp;
    int argc;
    int envc;
    int size;
};

struct dbg_ops_t
{
    int (*dbg)(int argc, char **argv);
    uint32_t (*arch_get_ins)(void);
    void (*arch_activate_step)(void);
    void (*arch_deactivate_step)(void);
    int (*check_debug_event)(struct rt_hw_exp_stack *regs, unsigned long esr);
    rt_channel_t (*gdb_get_server_channel)(void);
    int (*gdb_get_step_type)(void);
    void (*lwp_check_debug_attach_req)(void *pc);
    int (*lwp_check_debug_suspend)(void);
};
extern struct dbg_ops_t *rt_dbg_ops;

int dbg_thread_in_debug(void);
void dbg_register(struct dbg_ops_t *dbg_ops);

uint32_t dbg_get_ins(void);
void dbg_activate_step(void);
void dbg_deactivate_step(void);
int dbg_check_event(struct rt_hw_exp_stack *regs, unsigned long arg);
rt_channel_t gdb_server_channel(void);
int dbg_step_type(void);
void dbg_attach_req(void *pc);
int dbg_check_suspend(void);
void rt_hw_set_process_id(int pid);
void lwp_futex_exit_robust_list(rt_thread_t thread);

/* backtrace service */
rt_err_t lwp_backtrace_frame(rt_thread_t uthread, struct rt_hw_backtrace_frame *frame);

#endif
