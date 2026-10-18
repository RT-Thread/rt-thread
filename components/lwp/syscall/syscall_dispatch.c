/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include "syscall_generic.h"

#define DBG_TAG "lwp.syscall"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#if (defined(RT_USING_SAL) && defined(SAL_USING_POSIX))
#define SYSCALL_NET(f) f
#else
#define SYSCALL_NET(f) SYSCALL_SIGN(sys_notimpl)
#endif

#if defined(RT_USING_DFS) && defined(ARCH_MM_MMU)
#define SYSCALL_USPACE(f) f
#else
#define SYSCALL_USPACE(f) SYSCALL_SIGN(sys_notimpl)
#endif

extern int __sys_log_enable;
extern void sys_accept();
extern void sys_access();
extern void sys_api();
extern void sys_bind();
extern void sys_brk();
extern void sys_cacheflush();
extern void sys_channel_close();
extern void sys_channel_open();
extern void sys_channel_recv_timeout();
extern void sys_channel_reply();
extern void sys_channel_send();
extern void sys_channel_send_recv_timeout();
extern void sys_chdir();
extern void sys_chmod();
extern void sys_chown();
extern void sys_clock_getres();
extern void sys_clock_gettime();
extern void sys_clock_nanosleep();
extern void sys_clock_settime();
extern void sys_clone();
extern void sys_close();
extern void sys_closesocket();
extern void sys_connect();
extern void sys_device_close();
extern void sys_device_control();
extern void sys_device_find();
extern void sys_device_init();
extern void sys_device_open();
extern void sys_device_read();
extern void sys_device_register();
extern void sys_device_write();
extern void sys_dup();
extern void sys_dup2();
extern void sys_enter_critical();
extern void sys_epoll_create1();
extern void sys_epoll_ctl();
extern void sys_epoll_pwait();
extern void sys_event_create();
extern void sys_event_delete();
extern void sys_event_recv();
extern void sys_event_send();
extern void sys_eventfd2();
extern void sys_exec();
extern void sys_execve();
extern void sys_exit();
extern void sys_exit_critical();
extern void sys_exit_group();
extern void sys_fchdir();
extern void sys_fchmod();
extern void sys_fork();
extern void sys_fstat();
extern void sys_fstatfs();
extern void sys_fstatfs64();
extern void sys_fsync();
extern void sys_ftruncate();
extern void sys_futex();
extern void sys_get_errno();
extern void sys_get_robust_list();
extern void sys_getaddrinfo();
extern void sys_getcwd();
extern void sys_getdents();
extern void sys_gethostbyname2_r();
extern void sys_getpeername();
extern void sys_getpgid();
extern void sys_getpid();
extern void sys_getppid();
extern void sys_getpriority();
extern void sys_getrandom();
extern void sys_getrlimit();
extern void sys_getsid();
extern void sys_getsockname();
extern void sys_getsockopt();
extern void sys_gettid();
extern void sys_gettimeofday();
extern void sys_hw_interrupt_disable();
extern void sys_hw_interrupt_enable();
extern void sys_ioctl();
extern void sys_kill();
extern void sys_link();
extern void sys_listen();
extern void sys_log();
extern void sys_log_enable();
extern void sys_lseek();
extern void sys_lstat();
extern void sys_lwp_sighandler_set();
extern void sys_madvise();
extern void sys_mb_create();
extern void sys_mb_delete();
extern void sys_mb_recv();
extern void sys_mb_send();
extern void sys_mb_send_wait();
extern void sys_memfd_create();
extern void sys_mkdir();
extern void sys_mmap2();
extern void sys_mount();
extern void sys_mq_close();
extern void sys_mq_create();
extern void sys_mq_delete();
extern void sys_mq_getsetattr();
extern void sys_mq_notify();
extern void sys_mq_open();
extern void sys_mq_recv();
extern void sys_mq_send();
extern void sys_mq_timedreceive();
extern void sys_mq_timedsend();
extern void sys_mq_unlink();
extern void sys_mq_urgent();
extern void sys_mremap();
extern void sys_munmap();
extern void sys_mutex_create();
extern void sys_mutex_delete();
extern void sys_mutex_release();
extern void sys_mutex_take();
extern void sys_nanosleep();
extern void sys_notimpl();
extern void sys_open();
extern void sys_openat();
extern void sys_pipe();
extern void sys_pmutex();
extern void sys_poll();
extern void sys_pread64();
extern void sys_prlimit64();
extern void sys_pwrite64();
extern void sys_read();
extern void sys_readlink();
extern void sys_reboot();
extern void sys_recv();
extern void sys_recvfrom();
extern void sys_recvmsg();
extern void sys_rename();
extern void sys_rmdir();
extern void sys_rt_timer_control();
extern void sys_rt_timer_create();
extern void sys_rt_timer_delete();
extern void sys_rt_timer_start();
extern void sys_rt_timer_stop();
extern void sys_sched_get_priority_max();
extern void sys_sched_get_priority_min();
extern void sys_sched_getaffinity();
extern void sys_sched_getparam();
extern void sys_sched_getscheduler();
extern void sys_sched_setaffinity();
extern void sys_sched_setparam();
extern void sys_sched_setscheduler();
extern void sys_sched_yield();
extern void sys_select();
extern void sys_sem_create();
extern void sys_sem_delete();
extern void sys_sem_release();
extern void sys_sem_take();
extern void sys_send();
extern void sys_sendmsg();
extern void sys_sendto();
extern void sys_set_robust_list();
extern void sys_set_thread_area();
extern void sys_set_tid_address();
extern void sys_setitimer();
extern void sys_setpgid();
extern void sys_setpriority();
extern void sys_setrlimit();
extern void sys_setsid();
extern void sys_setsockopt();
extern void sys_settimeofday();
extern void sys_shm_alloc();
extern void sys_shm_free();
extern void sys_shm_retain();
extern void sys_shmat();
extern void sys_shmdt();
extern void sys_shmget();
extern void sys_shmrm();
extern void sys_shutdown();
extern void sys_sigaction();
extern void sys_signalfd();
extern void sys_sigpending();
extern void sys_sigprocmask();
extern void sys_sigtimedwait();
extern void sys_socket();
extern void sys_socketpair();
extern void sys_stat();
extern void sys_statfs();
extern void sys_statfs64();
extern void sys_symlink();
extern void sys_sysinfo();
extern void sys_syslog();
extern void sys_thread_create();
extern void sys_thread_delete();
extern void sys_thread_find();
extern void sys_thread_mdelay();
extern void sys_thread_self();
extern void sys_thread_sighandler_set();
extern void sys_thread_sigprocmask();
extern void sys_thread_startup();
extern void sys_tick_get();
extern void sys_timer_create();
extern void sys_timer_delete();
extern void sys_timer_getoverrun();
extern void sys_timer_gettime();
extern void sys_timer_settime();
extern void sys_timerfd_create();
extern void sys_timerfd_gettime();
extern void sys_timerfd_settime();
extern void sys_tkill();
extern void sys_umount2();
extern void sys_uname();
extern void sys_unlink();
extern void sys_utimensat();
extern void sys_vfork();
extern void sys_wait4();
extern void sys_waitpid();
extern void sys_write();
const static struct rt_syscall_def func_table[] = {
    SYSCALL_SIGN(sys_exit),            /* 01 */
    SYSCALL_SIGN(sys_read),
    SYSCALL_SIGN(sys_write),
    SYSCALL_SIGN(sys_lseek),
    SYSCALL_SIGN(sys_open),            /* 05 */
    SYSCALL_SIGN(sys_close),
    SYSCALL_SIGN(sys_ioctl),
    SYSCALL_SIGN(sys_fstat),
    SYSCALL_SIGN(sys_poll),
    SYSCALL_SIGN(sys_nanosleep),       /* 10 */
    SYSCALL_SIGN(sys_gettimeofday),
    SYSCALL_SIGN(sys_settimeofday),
    SYSCALL_SIGN(sys_exec),
    SYSCALL_SIGN(sys_kill),
    SYSCALL_SIGN(sys_getpid),          /* 15 */
    SYSCALL_SIGN(sys_getpriority),
    SYSCALL_SIGN(sys_setpriority),
    SYSCALL_SIGN(sys_sem_create),
    SYSCALL_SIGN(sys_sem_delete),
    SYSCALL_SIGN(sys_sem_take),        /* 20 */
    SYSCALL_SIGN(sys_sem_release),
    SYSCALL_SIGN(sys_mutex_create),
    SYSCALL_SIGN(sys_mutex_delete),
    SYSCALL_SIGN(sys_mutex_take),
    SYSCALL_SIGN(sys_mutex_release),   /* 25 */
    SYSCALL_SIGN(sys_event_create),
    SYSCALL_SIGN(sys_event_delete),
    SYSCALL_SIGN(sys_event_send),
    SYSCALL_SIGN(sys_event_recv),
    SYSCALL_SIGN(sys_mb_create),       /* 30 */
    SYSCALL_SIGN(sys_mb_delete),
    SYSCALL_SIGN(sys_mb_send),
    SYSCALL_SIGN(sys_mb_send_wait),
    SYSCALL_SIGN(sys_mb_recv),
    SYSCALL_SIGN(sys_mq_create),       /* 35 */
    SYSCALL_SIGN(sys_mq_delete),
    SYSCALL_SIGN(sys_mq_send),
    SYSCALL_SIGN(sys_mq_urgent),
    SYSCALL_SIGN(sys_mq_recv),
    SYSCALL_SIGN(sys_thread_create),   /* 40 */
    SYSCALL_SIGN(sys_thread_delete),
    SYSCALL_SIGN(sys_thread_startup),
    SYSCALL_SIGN(sys_thread_self),
    SYSCALL_SIGN(sys_channel_open),
    SYSCALL_SIGN(sys_channel_close),   /* 45 */
    SYSCALL_SIGN(sys_channel_send),
    SYSCALL_SIGN(sys_channel_send_recv_timeout),
    SYSCALL_SIGN(sys_channel_reply),
    SYSCALL_SIGN(sys_channel_recv_timeout),
    SYSCALL_SIGN(sys_enter_critical),  /* 50 */
    SYSCALL_SIGN(sys_exit_critical),

    SYSCALL_USPACE(SYSCALL_SIGN(sys_brk)),
    SYSCALL_USPACE(SYSCALL_SIGN(sys_mmap2)),
    SYSCALL_USPACE(SYSCALL_SIGN(sys_munmap)),
#ifdef ARCH_MM_MMU
    SYSCALL_USPACE(SYSCALL_SIGN(sys_shmget)), /* 55 */
    SYSCALL_USPACE(SYSCALL_SIGN(sys_shmrm)),
    SYSCALL_USPACE(SYSCALL_SIGN(sys_shmat)),
    SYSCALL_USPACE(SYSCALL_SIGN(sys_shmdt)),
#else
#ifdef RT_LWP_USING_SHM
    SYSCALL_SIGN(sys_shm_alloc),      /* 55 */
    SYSCALL_SIGN(sys_shm_free),
    SYSCALL_SIGN(sys_shm_retain),
    SYSCALL_SIGN(sys_notimpl),
#else
    SYSCALL_SIGN(sys_notimpl),      /* 55 */
    SYSCALL_SIGN(sys_notimpl),
    SYSCALL_SIGN(sys_notimpl),
    SYSCALL_SIGN(sys_notimpl),
#endif /* RT_LWP_USING_SHM */
#endif /* ARCH_MM_MMU */
    SYSCALL_SIGN(sys_device_init),
    SYSCALL_SIGN(sys_device_register), /* 60 */
    SYSCALL_SIGN(sys_device_control),
    SYSCALL_SIGN(sys_device_find),
    SYSCALL_SIGN(sys_device_open),
    SYSCALL_SIGN(sys_device_close),
    SYSCALL_SIGN(sys_device_read),    /* 65 */
    SYSCALL_SIGN(sys_device_write),

    SYSCALL_SIGN(sys_stat),
    SYSCALL_SIGN(sys_thread_find),

    SYSCALL_NET(SYSCALL_SIGN(sys_accept)),
    SYSCALL_NET(SYSCALL_SIGN(sys_bind)),      /* 70 */
    SYSCALL_NET(SYSCALL_SIGN(sys_shutdown)),
    SYSCALL_NET(SYSCALL_SIGN(sys_getpeername)),
    SYSCALL_NET(SYSCALL_SIGN(sys_getsockname)),
    SYSCALL_NET(SYSCALL_SIGN(sys_getsockopt)),
    SYSCALL_NET(SYSCALL_SIGN(sys_setsockopt)), /* 75 */
    SYSCALL_NET(SYSCALL_SIGN(sys_connect)),
    SYSCALL_NET(SYSCALL_SIGN(sys_listen)),
    SYSCALL_NET(SYSCALL_SIGN(sys_recv)),
    SYSCALL_NET(SYSCALL_SIGN(sys_recvfrom)),
    SYSCALL_NET(SYSCALL_SIGN(sys_send)),      /* 80 */
    SYSCALL_NET(SYSCALL_SIGN(sys_sendto)),
    SYSCALL_NET(SYSCALL_SIGN(sys_socket)),

    SYSCALL_NET(SYSCALL_SIGN(sys_closesocket)),
    SYSCALL_NET(SYSCALL_SIGN(sys_getaddrinfo)),
    SYSCALL_NET(SYSCALL_SIGN(sys_gethostbyname2_r)), /* 85 */

    SYSCALL_NET(SYSCALL_SIGN(sys_sendmsg)),
    SYSCALL_NET(SYSCALL_SIGN(sys_recvmsg)),
    SYSCALL_SIGN(sys_notimpl),    /* network */
    SYSCALL_SIGN(sys_notimpl),    /* network */
    SYSCALL_SIGN(sys_notimpl),    /* network, 90 */
    SYSCALL_SIGN(sys_notimpl),    /* network */
    SYSCALL_SIGN(sys_notimpl),    /* network */
    SYSCALL_SIGN(sys_notimpl),    /* network */

#ifdef RT_USING_DFS
    SYSCALL_SIGN(sys_select),
#else
    SYSCALL_SIGN(sys_notimpl),
#endif

    SYSCALL_SIGN(sys_notimpl),    /* SYSCALL_SIGN(sys_hw_interrupt_disable), 95 */
    SYSCALL_SIGN(sys_notimpl),    /* SYSCALL_SIGN(sys_hw_interrupt_enable) */

    SYSCALL_SIGN(sys_tick_get),
    SYSCALL_SIGN(sys_exit_group),

    SYSCALL_SIGN(sys_notimpl),    /* rt_delayed_work_init */
    SYSCALL_SIGN(sys_notimpl),    /* rt_work_submit, 100 */
    SYSCALL_SIGN(sys_notimpl),    /* rt_wqueue_wakeup */
    SYSCALL_SIGN(sys_thread_mdelay),
    SYSCALL_SIGN(sys_sigaction),
    SYSCALL_SIGN(sys_sigprocmask),
    SYSCALL_SIGN(sys_tkill),             /* 105 */
    SYSCALL_SIGN(sys_thread_sigprocmask),
#ifdef ARCH_MM_MMU
    SYSCALL_SIGN(sys_cacheflush),
    SYSCALL_SIGN(sys_notimpl),
    SYSCALL_SIGN(sys_notimpl),
#else
    SYSCALL_SIGN(sys_notimpl),
    SYSCALL_SIGN(sys_lwp_sighandler_set),
    SYSCALL_SIGN(sys_thread_sighandler_set),
#endif
    SYSCALL_SIGN(sys_waitpid),          /* 110 */

    SYSCALL_SIGN(sys_rt_timer_create),
    SYSCALL_SIGN(sys_rt_timer_delete),
    SYSCALL_SIGN(sys_rt_timer_start),
    SYSCALL_SIGN(sys_rt_timer_stop),
    SYSCALL_SIGN(sys_rt_timer_control),  /* 115 */
    SYSCALL_SIGN(sys_getcwd),
    SYSCALL_SIGN(sys_chdir),
    SYSCALL_SIGN(sys_unlink),
    SYSCALL_SIGN(sys_mkdir),
    SYSCALL_SIGN(sys_rmdir),          /* 120 */
    SYSCALL_SIGN(sys_getdents),
    SYSCALL_SIGN(sys_get_errno),
#ifdef ARCH_MM_MMU
    SYSCALL_SIGN(sys_set_thread_area),
    SYSCALL_SIGN(sys_set_tid_address),
#else
    SYSCALL_SIGN(sys_notimpl),
    SYSCALL_SIGN(sys_notimpl),
#endif
    SYSCALL_SIGN(sys_access),         /* 125 */
    SYSCALL_SIGN(sys_pipe),
    SYSCALL_SIGN(sys_clock_settime),
    SYSCALL_SIGN(sys_clock_gettime),
    SYSCALL_SIGN(sys_clock_getres),
    SYSCALL_USPACE(SYSCALL_SIGN(sys_clone)),            /* 130 */
    SYSCALL_USPACE(SYSCALL_SIGN(sys_futex)),
    SYSCALL_SIGN(sys_notimpl),                          /* discarded: sys_pmutex */
    SYSCALL_SIGN(sys_dup),
    SYSCALL_SIGN(sys_dup2),
    SYSCALL_SIGN(sys_rename),                           /* 135 */
    SYSCALL_USPACE(SYSCALL_SIGN(sys_fork)),
    SYSCALL_USPACE(SYSCALL_SIGN(sys_execve)),
    SYSCALL_USPACE(SYSCALL_SIGN(sys_vfork)),
    SYSCALL_SIGN(sys_gettid),
    SYSCALL_SIGN(sys_prlimit64),                        /* 140 */
    SYSCALL_SIGN(sys_getrlimit),
    SYSCALL_SIGN(sys_setrlimit),
    SYSCALL_SIGN(sys_setsid),
    SYSCALL_SIGN(sys_getrandom),
    SYSCALL_SIGN(sys_readlink),                         /* 145 */
    SYSCALL_USPACE(SYSCALL_SIGN(sys_mremap)),
    SYSCALL_USPACE(SYSCALL_SIGN(sys_madvise)),
    SYSCALL_SIGN(sys_sched_setparam),
    SYSCALL_SIGN(sys_sched_getparam),
    SYSCALL_SIGN(sys_sched_get_priority_max),           /* 150 */
    SYSCALL_SIGN(sys_sched_get_priority_min),
    SYSCALL_SIGN(sys_sched_setscheduler),
    SYSCALL_SIGN(sys_sched_getscheduler),
    SYSCALL_SIGN(sys_sched_setaffinity),
    SYSCALL_SIGN(sys_fsync),                            /* 155 */
    SYSCALL_SIGN(sys_clock_nanosleep),
    SYSCALL_SIGN(sys_timer_create),
    SYSCALL_SIGN(sys_timer_delete),
    SYSCALL_SIGN(sys_timer_settime),
    SYSCALL_SIGN(sys_timer_gettime),                    /* 160 */
    SYSCALL_SIGN(sys_timer_getoverrun),
    SYSCALL_SIGN(sys_mq_open),
    SYSCALL_SIGN(sys_mq_unlink),
    SYSCALL_SIGN(sys_mq_timedsend),
    SYSCALL_SIGN(sys_mq_timedreceive),                  /* 165 */
    SYSCALL_SIGN(sys_mq_notify),
    SYSCALL_SIGN(sys_mq_getsetattr),
    SYSCALL_SIGN(sys_mq_close),
    SYSCALL_SIGN(sys_lstat),
    SYSCALL_SIGN(sys_uname),                            /* 170 */
    SYSCALL_SIGN(sys_statfs),
    SYSCALL_SIGN(sys_statfs64),
    SYSCALL_SIGN(sys_fstatfs),
    SYSCALL_SIGN(sys_fstatfs64),
    SYSCALL_SIGN(sys_openat),                           /* 175 */
    SYSCALL_SIGN(sys_mount),
    SYSCALL_SIGN(sys_umount2),
    SYSCALL_SIGN(sys_link),
    SYSCALL_SIGN(sys_symlink),
    SYSCALL_SIGN(sys_sched_getaffinity),                /* 180 */
    SYSCALL_SIGN(sys_sysinfo),
    SYSCALL_SIGN(sys_chmod),
    SYSCALL_SIGN(sys_reboot),
    SYSCALL_SIGN(sys_sched_yield),
    SYSCALL_SIGN(sys_pread64),                          /* 185 */
    SYSCALL_SIGN(sys_pwrite64),
    SYSCALL_SIGN(sys_sigpending),
    SYSCALL_SIGN(sys_sigtimedwait),
    SYSCALL_SIGN(sys_notimpl),
    SYSCALL_SIGN(sys_notimpl),                          /* 190 */
    SYSCALL_SIGN(sys_eventfd2),
    SYSCALL_SIGN(sys_epoll_create1),
    SYSCALL_SIGN(sys_epoll_ctl),
    SYSCALL_SIGN(sys_epoll_pwait),
    SYSCALL_SIGN(sys_notimpl),                          /* 195 */
    SYSCALL_SIGN(sys_timerfd_create),
    SYSCALL_SIGN(sys_timerfd_settime),
    SYSCALL_SIGN(sys_timerfd_gettime),
    SYSCALL_SIGN(sys_signalfd),
    SYSCALL_SIGN(sys_memfd_create),                     /* 200 */
    SYSCALL_SIGN(sys_ftruncate),
    SYSCALL_SIGN(sys_setitimer),
    SYSCALL_SIGN(sys_utimensat),
#ifdef RT_USING_POSIX_SOCKET
    SYSCALL_SIGN(sys_syslog),
    SYSCALL_SIGN(sys_socketpair),                             /* 205 */
#else
    SYSCALL_SIGN(sys_notimpl),
    SYSCALL_SIGN(sys_notimpl),                          /* 205 */
#endif
    SYSCALL_SIGN(sys_wait4),
    SYSCALL_SIGN(sys_set_robust_list),
    SYSCALL_SIGN(sys_get_robust_list),
    SYSCALL_SIGN(sys_setpgid),
    SYSCALL_SIGN(sys_getpgid),                          /* 210 */
    SYSCALL_SIGN(sys_getsid),
    SYSCALL_SIGN(sys_getppid),
    SYSCALL_SIGN(sys_fchdir),
    SYSCALL_SIGN(sys_chown),
    SYSCALL_SIGN(sys_fchmod),
};

const void *lwp_get_sys_api(rt_uint32_t number)
{
    const void *func = (const void *)sys_notimpl;

    if (number == 0xff)
    {
        func = (void *)sys_log;
    }
    else
    {
        number -= 1;
        if (number < sizeof(func_table) / sizeof(func_table[0]))
        {
            func = func_table[number].func;
        }
        else
        {
            if (__sys_log_enable)
            {
                LOG_I("Unimplement syscall %d", number);
            }
        }
    }

    return func;
}

const char *lwp_get_syscall_name(rt_uint32_t number)
{
    const char *name = "sys_notimpl";

    if (number == 0xff)
    {
        name = "sys_log";
    }
    else
    {
        number -= 1;
        if (number < sizeof(func_table) / sizeof(func_table[0]))
        {
            name = (char *)func_table[number].name;
        }
        else
        {
            if (__sys_log_enable)
            {
                LOG_I("Unimplement syscall %d", number);
            }
        }
    }

    /* skip sys_ */
    return name;
}
