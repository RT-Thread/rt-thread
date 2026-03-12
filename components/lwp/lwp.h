/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
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
#include "lwp_args.h"
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

/**
 * @brief Light-weight process memory objects structure
 */
struct rt_lwp_objs
{
    rt_aspace_t source;                  /**< The address space associated with this LWP */
    struct rt_mem_obj mem_obj;           /**< The memory object containing memory management information */
};

/**
 * @brief Light-weight process notification structure
 */
struct rt_lwp_notify
{
    /**
     * @brief Callback function pointer for signal notification
     * @param signalfd_queue Wait queue for signal file descriptors
     * @param signo Signal number
     */
    void (*notify)(rt_wqueue_t *signalfd_queue, int signo);
    rt_wqueue_t *signalfd_queue;         /**< Wait queue for signal file descriptors */
    rt_slist_t list_node;                /**< List node for notification */
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

/**
 * @brief Session control structure for process groups
 */
struct rt_session {
    struct rt_object    object;
    rt_lwp_t            leader;          /**< Session leader process */
    rt_list_t           processgroup;    /**< List head of process groups in this session */
    pid_t               sid;             /**< Session ID */
    pid_t               foreground_pgid; /**< Foreground process group ID */
    struct rt_mutex     mutex;           /**< Mutex for session operations synchronization */
    struct lwp_tty      *ctty;           /**< Control terminal */
};

/**
 * @brief Process group control structure
 */
struct rt_processgroup {
    struct rt_object    object;
    rt_lwp_t            leader;         /**< Process group leader process */
    rt_list_t           process;        /**< List head of processes in this process group */
    rt_list_t           pgrp_list_node; /**< List node for process group */
    pid_t               pgid;           /**< Process group ID */
    pid_t               sid;            /**< Session ID */
    struct rt_session   *session;       /**< Session pointer */
    struct rt_mutex     mutex;          /**< Mutex for process group operations synchronization */

    rt_atomic_t         ref;            /**< Reference count for process group */

    /* flags on process group */
    unsigned int is_orphaned:1;         /**< Whether the process group is orphaned */
};

/**
 * @brief Light-weight process structure
 */
struct rt_lwp
{
#ifdef ARCH_MM_MMU
    size_t end_heap;                            /**< End address of heap */
    rt_aspace_t aspace;                         /**< Address space associated with this LWP */
#else
#ifdef ARCH_MM_MPU
    struct rt_mpu_info mpu_info;                /**< MPU information for this LWP */
#endif /* ARCH_MM_MPU */
#endif /* ARCH_MM_MMU */

#ifdef RT_USING_SMP
    int bind_cpu;                               /**< CPU ID to which the LWP is bound */
#endif

    uint8_t lwp_type;                           /**< Type of LWP */
    uint8_t reserv[3];

    /* flags */
    unsigned int terminated:1;                  /**< Process termination flag */
    unsigned int background:1;                  /**< Background process flag */
    unsigned int term_ctrlterm:1;               /**< have control terminal? */
    unsigned int did_exec:1;                    /**< Whether exec has been performed */
    unsigned int jobctl_stopped:1;              /**< job control: current proc is stopped */
    unsigned int wait_reap_stp:1;               /**< job control: has wait event for parent */
    unsigned int sig_protected:1;               /**< signal: protected proc cannot be killed or stopped */

    struct rt_lwp *parent;                      /**< parent process */
    struct rt_lwp *first_child;                 /**< first child process */
    struct rt_lwp *sibling;                     /**< sibling(child) process */

    struct rt_wqueue waitpid_waiters;           /**< Wait queue for waitpid system call */
    lwp_status_t lwp_status;                    /**< Status of LWP */

    void *text_entry;                           /**< Entry point of text segment */
    uint32_t text_size;                         /**< Size of text segment */
    void *data_entry;                           /**< Entry point of data segment */
    uint32_t data_size;                         /**< Size of data segment */

    rt_atomic_t ref;                            /**< Reference count for LWP */
    void *args;                                 /**< Arguments passed to LWP */
    uint32_t args_length;                       /**< Length of arguments */
    pid_t pid;                                  /**< Process ID */
    pid_t sid;                                  /**< session ID */
    pid_t pgid;                                 /**< process group ID */
    struct rt_processgroup *pgrp;               /**< process group */
    rt_list_t pgrp_node;                        /**< process group node */
    rt_list_t t_grp;                            /**< thread group */
    rt_list_t timer;                            /**< POSIX timer object binding to a process */

    struct dfs_fdtable fdt;                     /**< File descriptor table */
    char cmd[RT_NAME_MAX];                      /**< process name */
    char *exe_file;                             /**< process file path */

    /* POSIX signal */
    struct lwp_signal signal;                   /**< Signal handling structure */

    struct lwp_avl_struct *object_root;         /**< AVL tree root for objects */
    struct rt_mutex object_mutex;               /**< Mutex for object operations synchronization */
    struct rt_user_context user_ctx;            /**< User context for LWP */

    struct rt_wqueue wait_queue;                /**< wait queue for console */
    struct tty_struct *tty;                     /**< Controlling terminal, NULL if no tty */

    struct lwp_avl_struct *address_search_head; /**< for saving private futexes with a user-space address key */
    char working_directory[DFS_PATH_MAX];       /**< Current working directory */

    int debug;                                  /**< Debug flag */
    rt_uint32_t bak_first_inst;                 /**< backup of first instruction */

    struct rt_mutex lwp_lock;                   /**< Mutex for LWP operations synchronization */

    rt_slist_t signalfd_notify_head;            /**< Signal file descriptor notification head */

#ifdef LWP_ENABLE_ASID
    uint64_t generation;                        /**< ASID generation */
    unsigned int asid;                          /**< Address space ID */
#endif
    struct rusage rt_rusage;                    /**< Resource usage information */

#ifdef RT_USING_VDSO
    void *vdso_vbase;                           /**< VDSO base address */
#endif
};


struct rt_lwp *lwp_self(void);
rt_err_t lwp_children_register(struct rt_lwp *parent, struct rt_lwp *child);
rt_err_t lwp_children_unregister(struct rt_lwp *parent, struct rt_lwp *child);

/**
 * @brief LWP exit request type
 */
enum lwp_exit_request_type
{
    LWP_EXIT_REQUEST_NONE = 0,                  /**< No exit request */
    LWP_EXIT_REQUEST_TRIGGERED,                 /**< Exit request triggered */
    LWP_EXIT_REQUEST_IN_PROCESS,                /**< Exit request in process */
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
int lwp_load(const char *filename, struct rt_lwp *lwp, uint8_t *load_addr, size_t addr_size, struct process_aux *aux);
void lwp_user_obj_free(struct rt_lwp *lwp);

/*create by lwp_setsid.c*/
int setsid(void);
#ifdef ARCH_MM_MMU
void lwp_aspace_switch(struct rt_thread *thread);
#endif
void lwp_user_setting_save(rt_thread_t thread);
void lwp_user_setting_restore(rt_thread_t thread);

void lwp_uthread_ctx_save(void *ctx);
void lwp_uthread_ctx_restore(void);

int lwp_setaffinity(int tid, int cpu);

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

sysret_t lwp_teardown(struct rt_lwp *lwp, void (*cb)(void));

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
#define AT_SYSINFO_EHDR 33

/**
 * @brief Process auxiliary vector item
 */
struct process_aux_item
{
    size_t key;                            /**< Auxiliary vector key */
    size_t value;                          /**< Auxiliary vector value */
};

/**
 * @brief Process auxiliary vector
 */
struct process_aux
{
    struct process_aux_item item[AUX_ARRAY_ITEMS_NR]; /**< Auxiliary vector items */
};

/**
 * @brief Debug operations structure
 */
struct dbg_ops_t
{
    int (*dbg)(int argc, char **argv);                                         /**< Debug function */
    uint32_t (*arch_get_ins)(void);                                            /**< Architecture-specific instruction getter */
    void (*arch_activate_step)(void);                                          /**< Architecture-specific step activation */
    void (*arch_deactivate_step)(void);                                        /**< Architecture-specific step deactivation */
    int (*check_debug_event)(struct rt_hw_exp_stack *regs, unsigned long esr); /**< Debug event checker */
    rt_channel_t (*gdb_get_server_channel)(void);                              /**< GDB server channel getter */
    int (*gdb_get_step_type)(void);                                            /**< GDB step type getter */
    void (*lwp_check_debug_attach_req)(void *pc);                              /**< LWP debug attach request checker */
    int (*lwp_check_debug_suspend)(void);                                      /**< LWP debug suspend checker */
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
