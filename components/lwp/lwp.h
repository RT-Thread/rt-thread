/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-06-29     heyuanjie    first version
 * 2019-10-12     Jesven       Add MMU and userspace support
 * 2020-10-08     Bernard      Architecture and code cleanup
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

#include "arch.h"

#include "lwp_pid.h"
#include "lwp_ipc.h"
#include "lwp_signal.h"
#include "lwp_syscall.h"

#ifdef RT_USING_USERSPACE
#include "lwp_shm.h"

#include "mmu.h"
#include "page.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define LWP_MAGIC           0x5A

#define LWP_TYPE_FIX_ADDR   0x01
#define LWP_TYPE_DYN_ADDR   0x02

#define LWP_ARG_MAX         8

typedef int32_t pid_t;

struct rt_lwp
{
#ifdef RT_USING_USERSPACE
    rt_mmu_info mmu_info;
    struct lwp_avl_struct *map_area;
    size_t end_heap;
#endif

    uint8_t lwp_type;
    uint8_t heap_cnt;
    uint8_t reserv[2];

    struct rt_lwp *parent;
    struct rt_lwp *first_child;
    struct rt_lwp *sibling;

    rt_list_t wait_list;
    int32_t  finish;
    int  lwp_ret;

    void *text_entry;
    uint32_t text_size;
    void *data_entry;
    uint32_t *data_size;

    int ref;
    void *args;
    pid_t pid;
    rt_list_t t_grp;
    struct dfs_fdtable fdt;
    char cmd[RT_NAME_MAX];

    lwp_sigset_t signal;
    lwp_sigset_t signal_mask;
    int signal_mask_bak;
    rt_uint32_t signal_in_process;
    lwp_sighandler_t signal_handler[_LWP_NSIG];

    rt_list_t object_list;
    struct rt_user_context user_ctx;

    struct rt_wqueue wait_queue; /*for console */

#ifdef RT_USING_GDBSERVER
    int debug;
    uint32_t bak_first_ins;
#endif
};

struct rt_lwp *lwp_self(void);

enum lwp_exit_request_type
{
    LWP_EXIT_REQUEST_NONE = 0,
    LWP_EXIT_REQUEST_TRIGGERED,
    LWP_EXIT_REQUEST_IN_PROCESS,
};

void lwp_request_thread_exit(rt_thread_t thread_to_exit);
int  lwp_check_exit_request(void);
void lwp_terminate(struct rt_lwp *lwp);
void lwp_wait_subthread_exit(void);

void lwp_set_thread_area(void *p);
void* rt_cpu_get_thread_idr(void);
void rt_cpu_set_thread_idr(void *p);

#ifdef RT_USING_USERSPACE
void lwp_mmu_switch(struct rt_thread *thread);
#endif

#ifdef RT_USING_USERSPACE
struct __pthread {
    /* Part 1 -- these fields may be external or
     *      * internal (accessed via asm) ABI. Do not change. */
    struct pthread *self;
    uintptr_t *dtv;
    struct pthread *prev, *next; /* non-ABI */
    uintptr_t sysinfo;
    uintptr_t canary, canary2;

    /* Part 2 -- implementation details, non-ABI. */
    int tid;
    int errno_val;
    volatile int detach_state;
    volatile int cancel;
    volatile unsigned char canceldisable, cancelasync;
    unsigned char tsd_used:1;
    unsigned char dlerror_flag:1;
    unsigned char *map_base;
    size_t map_size;
    void *stack;
    size_t stack_size;
    size_t guard_size;
    void *result;
    struct __ptcb *cancelbuf;
    void **tsd;
    struct {
        volatile void *volatile head;
        long off;
        volatile void *volatile pending;
    } robust_list;
    volatile int timer_id;
    locale_t locale;
    volatile int killlock[1];
    char *dlerror_buf;
    void *stdio_locks;

    /* Part 3 -- the positions of these fields relative to
     *      * the end of the structure is external and internal ABI. */
    uintptr_t canary_at_end;
    uintptr_t *dtv_copy;
};
#endif

#ifdef __cplusplus
}
#endif

#endif
