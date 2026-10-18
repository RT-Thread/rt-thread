/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-06-10     Bernard      first version
 * 2021-02-03     lizhirui     add limit condition for network syscall and add 64-bit arch support
 * 2021-02-06     lizhirui     fix some bugs
 * 2021-02-12     lizhirui     add 64-bit support for sys_brk
 * 2021-02-20     lizhirui     fix some warnings
 * 2023-03-13     WangXiaoyao  Format & fix syscall return value
 * 2023-07-06     Shell        adapt the signal API, and clone, fork to new implementation of lwp signal
 * 2023-07-27     Shell        Move tid_put() from lwp_free() to sys_exit()
 * 2023-11-16     xqyjlj       fix some syscalls (about sched_*, get/setpriority)
 * 2023-11-17     xqyjlj       add process group and session support
 * 2023-11-30     Shell        Fix sys_setitimer() and exit(status)
 */
#include "syscall_internal.h"

sysret_t sys_notimpl(void)
{
    return -ENOSYS;
}

uint32_t sys_hw_interrupt_disable(void)
{
    return rt_hw_interrupt_disable();
}

void sys_hw_interrupt_enable(uint32_t level)
{
    rt_hw_interrupt_enable(level);
}

#ifdef ARCH_MM_MMU
void *kmem_get(size_t size)
{
    return rt_malloc(size);
}

void kmem_put(void *kptr)
{
    rt_free(kptr);
}
#endif /* ARCH_MM_MMU */

#ifdef RT_USING_SAL
    /* The same socket option is defined differently in the user interfaces and the
    * implementation. The options should be converted in the kernel. */
void convert_sockopt(int *level, int *optname)
{
    if (*level == INTF_SOL_SOCKET)
    {
        *level = IMPL_SOL_SOCKET;

        switch (*optname)
        {
        case INTF_SO_REUSEADDR:
            *optname = IMPL_SO_REUSEADDR;
            break;
        case INTF_SO_KEEPALIVE:
            *optname = IMPL_SO_KEEPALIVE;
            break;
        case INTF_SO_BROADCAST:
            *optname = IMPL_SO_BROADCAST;
            break;
        case INTF_SO_ACCEPTCONN:
            *optname = IMPL_SO_ACCEPTCONN;
            break;
        case INTF_SO_DONTROUTE:
            *optname = IMPL_SO_DONTROUTE;
            break;
        case INTF_SO_LINGER:
            *optname = IMPL_SO_LINGER;
            break;
        case INTF_SO_OOBINLINE:
            *optname = IMPL_SO_OOBINLINE;
            break;
        case INTF_SO_REUSEPORT:
            *optname = IMPL_SO_REUSEPORT;
            break;
        case INTF_SO_SNDBUF:
            *optname = IMPL_SO_SNDBUF;
            break;
        case INTF_SO_RCVBUF:
            *optname = IMPL_SO_RCVBUF;
            break;
        case INTF_SO_SNDLOWAT:
            *optname = IMPL_SO_SNDLOWAT;
            break;
        case INTF_SO_RCVLOWAT:
            *optname = IMPL_SO_RCVLOWAT;
            break;
        case INTF_SO_SNDTIMEO:
            *optname = IMPL_SO_SNDTIMEO;
            break;
        case INTF_SO_RCVTIMEO:
            *optname = IMPL_SO_RCVTIMEO;
            break;
        case INTF_SO_ERROR:
            *optname = IMPL_SO_ERROR;
            break;
        case INTF_SO_TYPE:
            *optname = IMPL_SO_TYPE;
            break;
        case INTF_SO_NO_CHECK:
            *optname = IMPL_SO_NO_CHECK;
            break;
        case INTF_SO_BINDTODEVICE:
            *optname = IMPL_SO_BINDTODEVICE;
            break;
        case INTF_SO_TIMESTAMPNS:
            *optname = IMPL_SO_TIMESTAMPNS;
            break;
        case INTF_SO_TIMESTAMPING:
            *optname = IMPL_SO_TIMESTAMPING;
            break;
        case INTF_SO_SELECT_ERR_QUEUE:
            *optname = IMPL_SO_SELECT_ERR_QUEUE;
            break;

                /*
                * SO_DONTLINGER (*level = ((int)(~SO_LINGER))),
                * SO_USELOOPBACK (*level = 0x0040) and
                * SO_CONTIMEO (*level = 0x1009) are not supported for now.
                */
        default:
            *optname = 0;
            break;
        }
        return;
    }

    if (*level == INTF_IPPROTO_IP)
    {
        *level = IMPL_IPPROTO_IP;

        switch (*optname)
        {
        case INTF_IP_TTL:
            *optname = IMPL_IP_TTL;
            break;
        case INTF_IP_TOS:
            *optname = IMPL_IP_TOS;
            break;
        case INTF_IP_MULTICAST_TTL:
            *optname = IMPL_IP_MULTICAST_TTL;
            break;
        case INTF_IP_MULTICAST_IF:
            *optname = IMPL_IP_MULTICAST_IF;
            break;
        case INTF_IP_MULTICAST_LOOP:
            *optname = IMPL_IP_MULTICAST_LOOP;
            break;
        case INTF_IP_ADD_MEMBERSHIP:
            *optname = IMPL_IP_ADD_MEMBERSHIP;
            break;
        case INTF_IP_DROP_MEMBERSHIP:
            *optname = IMPL_IP_DROP_MEMBERSHIP;
            break;
        default:
            break;
        }
    }

    if (*level == INTF_IPPROTO_TCP)
    {
        *level = IMPL_IPPROTO_TCP;

        switch (*optname)
        {
        case INTF_TCP_NODELAY:
            *optname = IMPL_TCP_NODELAY;
            break;
        case INTF_TCP_KEEPALIVE:
            *optname = IMPL_TCP_KEEPALIVE;
            break;
        case INTF_TCP_KEEPIDLE:
            *optname = IMPL_TCP_KEEPIDLE;
            break;
        case INTF_TCP_KEEPINTVL:
            *optname = IMPL_TCP_KEEPINTVL;
            break;
        case INTF_TCP_KEEPCNT:
            *optname = IMPL_TCP_KEEPCNT;
            break;
        default:
            break;
        }
        return;
    }

    if (*level == INTF_IPPROTO_IPV6)
    {
        *level = IMPL_IPPROTO_IPV6;

        switch (*optname)
        {
        case INTF_IPV6_V6ONLY:
            *optname = IMPL_IPV6_V6ONLY;
            break;
        default:
            break;
        }
        return;
    }
}
#endif  /* RT_USING_SAL */

#if defined(RT_USING_LWIP) || defined(SAL_USING_UNET) || defined(RT_USING_SAL)
void sockaddr_tolwip(const struct musl_sockaddr *std, struct sockaddr *lwip)
{
    if (std && lwip)
    {
        lwip->sa_len = sizeof(*lwip);
        lwip->sa_family = (sa_family_t)std->sa_family;
        memcpy(lwip->sa_data, std->sa_data, sizeof(lwip->sa_data));
    }
}

void sockaddr_tomusl(const struct sockaddr *lwip, struct musl_sockaddr *std)
{
    if (std && lwip)
    {
        std->sa_family = (uint16_t)lwip->sa_family;
        memcpy(std->sa_data, lwip->sa_data, sizeof(std->sa_data));
    }
}
#endif

void _crt_thread_entry(void *parameter)
{
    rt_thread_t tid;
    rt_size_t user_stack;

    tid = rt_thread_self();

    user_stack = (rt_size_t)tid->user_stack + tid->user_stack_size;
    user_stack &= ~7; /* align 8 */

#ifdef ARCH_MM_MMU
    arch_crt_start_umode(parameter, tid->user_entry, (void *)user_stack, (char *)tid->stack_addr + tid->stack_size);
#else
    set_user_context((void *)user_stack);
    arch_start_umode(parameter, tid->user_entry, ((struct rt_lwp *)tid->lwp)->data_entry, (void *)user_stack);
#endif /* ARCH_MM_MMU */
}
