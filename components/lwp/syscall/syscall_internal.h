/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __LWP_SYSCALL_INTERNAL_H__
#define __LWP_SYSCALL_INTERNAL_H__

#define __RT_IPC_SOURCE__
#define _GNU_SOURCE

#include <rtthread.h>
#include <rthw.h>
#include <board.h>

#include <string.h>
#include <stdint.h>

#define DBG_TAG "lwp.syscall"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "syscall_generic.h"
#include "libc_musl.h"
#include "lwp_internal.h"
#include "lwp_ipc_internal.h"
#include "mqueue.h"

#ifdef ARCH_MM_MMU
#include <mm_aspace.h>
#include <lwp_user_mm.h>
#include <lwp_arch.h>
#endif

#include <fcntl.h>
#include <sys/utsname.h>

#ifdef RT_USING_DFS
#include <eventfd.h>
#include <poll.h>
#include <sys/epoll.h>
#include <sys/select.h>
#include <dfs_file.h>
#ifdef RT_USING_DFS_V2
#include <dfs_dentry.h>
#endif
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/timerfd.h>
#include <sys/ioctl.h>
#ifdef RT_USING_MUSLLIBC
#include <sys/signalfd.h>
#endif
#endif

#ifdef RT_USING_SAL
#include <netdev_ipaddr.h>
#include <netdev.h>
#include <sal_netdb.h>
#include <sal_socket.h>
#include <sys/socket.h>
#include "lwp_sys_socket.h"
#endif

#include <sched.h>
#include <sys/sysinfo.h>

#ifndef GRND_NONBLOCK
#define GRND_NONBLOCK 0x0001
#endif
#ifndef GRND_RANDOM
#define GRND_RANDOM 0x0002
#endif

#ifndef RT_USING_POSIX_TIMER
#error "No definition RT_USING_POSIX_TIMER"
#endif
#ifndef RT_USING_POSIX_CLOCK
#error "No definition RT_USING_POSIX_CLOCK"
#endif

void lwp_cleanup(struct rt_thread *tid);
void _crt_thread_entry(void *parameter);

#ifdef ARCH_MM_MMU
void *kmem_get(size_t size);
void kmem_put(void *kptr);
#define ALLOC_KERNEL_STACK_SIZE 5120
#else
#define ALLOC_KERNEL_STACK_SIZE     1536
#define ALLOC_KERNEL_STACK_SIZE_MIN 1024
#define ALLOC_KERNEL_STACK_SIZE_MAX 4096
void set_user_context(void *stack);
#endif

sysret_t sys_notimpl(void);

#ifdef RT_USING_SAL
void convert_sockopt(int *level, int *optname);
#endif

#if defined(RT_USING_LWIP) || defined(SAL_USING_UNET) || defined(RT_USING_SAL)
struct musl_sockaddr;
void sockaddr_tolwip(const struct musl_sockaddr *std, struct sockaddr *lwip);
void sockaddr_tomusl(const struct sockaddr *lwip, struct musl_sockaddr *std);
#endif

#endif /* __LWP_SYSCALL_INTERNAL_H__ */
