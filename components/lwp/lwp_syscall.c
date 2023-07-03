/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
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
 */
#define _GNU_SOURCE
/* RT-Thread System call */
#include <rtthread.h>
#include <rthw.h>
#include <board.h>
#include <mm_aspace.h>
#include <string.h>
#include <stdint.h>

#define DBG_TAG    "SYSCALL"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#include "syscall_generic.h"

#include <lwp.h>
#ifdef ARCH_MM_MMU
#include <lwp_user_mm.h>
#include <lwp_arch.h>
#endif

#include <fcntl.h>
#include <sys/utsname.h>

#ifdef RT_USING_DFS
#include <poll.h>
#include <sys/select.h>
#include <dfs_file.h>
#ifdef RT_USING_DFS_V2
#include <dfs_dentry.h>
#endif
#include <unistd.h>
#include <stdio.h> /* rename() */
#include <sys/stat.h>
#include <sys/statfs.h> /* statfs() */
#endif

#include "mqueue.h"

#ifdef RT_USING_SAL
    #include <netdev_ipaddr.h>
    #include <netdev.h>

    #include <sal_netdb.h>
    #include <sal_socket.h>
    #include <sys/socket.h>

#endif /* RT_USING_SAL */

#if (defined(RT_USING_SAL) && defined(SAL_USING_POSIX))
    #include <sys/socket.h>

    #define SYSCALL_NET(f)      f
#else
    #define SYSCALL_NET(f)      SYSCALL_SIGN(sys_notimpl)
#endif /* (defined(RT_USING_SAL) && defined(SAL_USING_POSIX)) */

#if defined(RT_USING_DFS) && defined(ARCH_MM_MMU)
    #define SYSCALL_USPACE(f)   f
#else
    #define SYSCALL_USPACE(f)   SYSCALL_SIGN(sys_notimpl)
#endif /* defined(RT_USING_DFS) && defined(ARCH_MM_MMU) */

#include <tty.h>
#include "lwp_ipc_internal.h"
#include <sched.h>

#include <sys/sysinfo.h>

#ifndef GRND_NONBLOCK
#define GRND_NONBLOCK   0x0001
#endif /* GRND_NONBLOCK */

#ifndef GRND_RANDOM
#define GRND_RANDOM 0x0002
#endif /*GRND_RANDOM */

#ifndef RT_USING_POSIX_TIMER
#error "No definition RT_USING_POSIX_TIMER"
#endif /* RT_USING_POSIX_TIMER */

#ifndef RT_USING_POSIX_CLOCK
#error "No definition RT_USING_POSIX_CLOCK"
#endif /* RT_USING_POSIX_CLOCK */

struct musl_sockaddr
{
    uint16_t sa_family;
    char     sa_data[14];
};

void lwp_cleanup(struct rt_thread *tid);

#ifdef ARCH_MM_MMU
    #define ALLOC_KERNEL_STACK_SIZE 5120

    static void *kmem_get(size_t size)
    {
        return rt_malloc(size);
    }

    static void kmem_put(void *kptr)
    {
        rt_free(kptr);
    }
#else /* ARCH_MM_MMU */
    #define ALLOC_KERNEL_STACK_SIZE 1536
    #define ALLOC_KERNEL_STACK_SIZE_MIN 1024
    #define ALLOC_KERNEL_STACK_SIZE_MAX 4096

    extern void set_user_context(void *stack);
#endif /* ARCH_MM_MMU */

#ifdef RT_USING_SAL
    /* The same socket option is defined differently in the user interfaces and the
    * implementation. The options should be converted in the kernel. */
    #include "lwp_sys_socket.h"

    static void convert_sockopt(int *level, int *optname)
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

#if defined(RT_USING_LWIP) || defined(SAL_USING_UNET)
    static void sockaddr_tolwip(const struct musl_sockaddr *std, struct sockaddr *lwip)
    {
        if (std && lwip)
        {
            lwip->sa_len = sizeof(*lwip);
            lwip->sa_family = (sa_family_t) std->sa_family;
            memcpy(lwip->sa_data, std->sa_data, sizeof(lwip->sa_data));
        }
    }

    static void sockaddr_tomusl(const struct sockaddr *lwip, struct musl_sockaddr *std)
    {
        if (std && lwip)
        {
            std->sa_family = (uint16_t) lwip->sa_family;
            memcpy(std->sa_data, lwip->sa_data, sizeof(std->sa_data));
        }
    }
#endif

static void _crt_thread_entry(void *parameter)
{
    rt_thread_t tid;
    rt_size_t user_stack;

    tid = rt_thread_self();

    user_stack = (rt_size_t)tid->user_stack + tid->user_stack_size;
    user_stack &= ~7; //align 8

#ifdef ARCH_MM_MMU
    arch_crt_start_umode(parameter, tid->user_entry, (void *)user_stack, (char *)tid->stack_addr + tid->stack_size);
#else
    set_user_context((void*)user_stack);
    arch_start_umode(parameter, tid->user_entry, ((struct rt_lwp *)tid->lwp)->data_entry, (void*)user_stack);
#endif /* ARCH_MM_MMU */
}

/* thread/process */
void sys_exit(int value)
{
    rt_base_t level;
    rt_thread_t tid, main_thread;
    struct rt_lwp *lwp;

    LOG_D("thread/process exit.");

    tid = rt_thread_self();
    lwp = (struct rt_lwp *)tid->lwp;

    level = rt_hw_interrupt_disable();
#ifdef ARCH_MM_MMU
    if (tid->clear_child_tid)
    {
        int t = 0;
        int *clear_child_tid = tid->clear_child_tid;

        tid->clear_child_tid = RT_NULL;
        lwp_put_to_user(clear_child_tid, &t, sizeof t);
        sys_futex(clear_child_tid, FUTEX_WAKE, 1, RT_NULL, RT_NULL, 0);
    }
    main_thread = rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling);
    if (main_thread == tid)
    {
        lwp_terminate(lwp);
        lwp_wait_subthread_exit();
        lwp->lwp_ret = value;
    }
#else
    main_thread = rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling);
    if (main_thread == tid)
    {
        rt_thread_t sub_thread;
        rt_list_t *list;

        lwp_terminate(lwp);

        /* delete all subthread */
        while ((list = tid->sibling.prev) != &lwp->t_grp)
        {
            sub_thread = rt_list_entry(list, struct rt_thread, sibling);
            rt_list_remove(&sub_thread->sibling);
            rt_thread_delete(sub_thread);
        }
        lwp->lwp_ret = value;
    }
#endif /* ARCH_MM_MMU */

    rt_thread_delete(tid);
    rt_schedule();
    rt_hw_interrupt_enable(level);

    return;
}

/* exit group */
void sys_exit_group(int status)
{
    return;
}

/* syscall: "read" ret: "ssize_t" args: "int" "void *" "size_t" */
ssize_t sys_read(int fd, void *buf, size_t nbyte)
{
#ifdef ARCH_MM_MMU
    void *kmem = RT_NULL;
    ssize_t ret = -1;

    if (!nbyte)
    {
        return -EINVAL;
    }

    if (!lwp_user_accessable((void *)buf, nbyte))
    {
        return -EFAULT;
    }

    kmem = kmem_get(nbyte);
    if (!kmem)
    {
        return -ENOMEM;
    }

    ret = read(fd, kmem, nbyte);
    if (ret > 0)
    {
        lwp_put_to_user(buf, kmem, ret);
    }

    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kmem);

    return ret;
#else
    if (!lwp_user_accessable((void *)buf, nbyte))
    {
        return -EFAULT;
    }
    ssize_t ret = read(fd, buf, nbyte);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/* syscall: "write" ret: "ssize_t" args: "int" "const void *" "size_t" */
ssize_t sys_write(int fd, const void *buf, size_t nbyte)
{
#ifdef ARCH_MM_MMU
    void *kmem = RT_NULL;
    ssize_t ret = -1;

    if (!nbyte)
    {
        return -EINVAL;
    }

    if (!lwp_user_accessable((void *)buf, nbyte))
    {
        return -EFAULT;
    }

    kmem = kmem_get(nbyte);
    if (!kmem)
    {
        return -ENOMEM;
    }

    lwp_get_from_user(kmem, (void *)buf, nbyte);
    ret = write(fd, kmem, nbyte);
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kmem);

    return ret;
#else
    if (!lwp_user_accessable((void *)buf, nbyte))
    {
        return -EFAULT;
    }
    ssize_t ret = write(fd, buf, nbyte);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/* syscall: "lseek" ret: "off_t" args: "int" "off_t" "int" */
off_t sys_lseek(int fd, off_t offset, int whence)
{
    off_t ret = lseek(fd, offset, whence);
    return (ret < 0 ? GET_ERRNO() : ret);
}

/* syscall: "open" ret: "int" args: "const char *" "int" "..." */
sysret_t sys_open(const char *name, int flag, ...)
{
#ifdef ARCH_MM_MMU
    int ret = -1;
    rt_size_t len = 0;
    char *kname = RT_NULL;
    mode_t mode = 0;

    if (!lwp_user_accessable((void *)name, 1))
    {
        return -EFAULT;
    }

    len = rt_strlen(name);
    if (!len)
    {
        return -EINVAL;
    }

    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        return -ENOMEM;
    }

    if ((flag & O_CREAT) || (flag & O_TMPFILE) == O_TMPFILE)
    {
        va_list ap;
        va_start(ap, flag);
        mode = va_arg(ap, mode_t);
        va_end(ap);
    }

    lwp_get_from_user(kname, (void *)name, len + 1);
    ret = open(kname, flag, mode);
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kname);

    return ret;
#else
    int ret;
    mode_t mode = 0;

    if (!lwp_user_accessable((void *)name, 1))
    {
        return -EFAULT;
    }

    if ((flag & O_CREAT) || (flag & O_TMPFILE) == O_TMPFILE)
    {
        va_list ap;
        va_start(ap, flag);
        mode = va_arg(ap, mode_t);
        va_end(ap);
    }

    ret = open(name, flag, mode);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/* syscall: "open" ret: "int" args: "const char *" "mode_t" "mode" */
sysret_t sys_openat(int dirfd, const char *name, int flag, mode_t mode)
{
#ifdef ARCH_MM_MMU
    int ret = -1;
    int err = 0;
    rt_size_t len = 0;
    char *kname = RT_NULL;

    len = lwp_user_strlen(name, &err);
    if (!len || err != 0)
    {
        return -EINVAL;
    }

    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        return -ENOMEM;
    }

    lwp_get_from_user(kname, (void *)name, len + 1);
    ret = openat(dirfd, kname, flag, mode);
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kname);

    return ret;
#else
    if (!lwp_user_accessable((void *)name, 1))
    {
        return -EFAULT;
    }
    int ret = openat(dirfd, name, flag, mode);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/* syscall: "close" ret: "int" args: "int" */
sysret_t sys_close(int fd)
{
    int ret = close(fd);
    return (ret < 0 ? GET_ERRNO() : ret);
}

/* syscall: "ioctl" ret: "int" args: "int" "u_long" "..." */
sysret_t sys_ioctl(int fd, unsigned long cmd, void* data)
{
    int ret = ioctl(fd, cmd, data);
    return (ret < 0 ? GET_ERRNO() : ret);
}

sysret_t sys_fstat(int file, struct stat *buf)
{
#ifdef ARCH_MM_MMU
    int ret = -1;
    struct stat statbuff = {0};

    if (!lwp_user_accessable((void *)buf, sizeof(struct stat)))
    {
        return -EFAULT;
    }
    else
    {
        ret = fstat(file, &statbuff);

        if (ret == 0)
        {
            lwp_put_to_user(buf, &statbuff, sizeof statbuff);
        }
        else
        {
            ret = GET_ERRNO();
        }

        return ret;
    }
#else
    if (!lwp_user_accessable((void *)buf, sizeof(struct stat)))
    {
        return -EFAULT;
    }
    int ret = fstat(file, buf);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/* DFS and lwip definitions */
#define IMPL_POLLIN     (0x01)

#define IMPL_POLLOUT    (0x02)

#define IMPL_POLLERR    (0x04)
#define IMPL_POLLHUP    (0x08)
#define IMPL_POLLNVAL   (0x10)

/* musl definitions */
#define INTF_POLLIN     0x001
#define INTF_POLLPRI    0x002
#define INTF_POLLOUT    0x004
#define INTF_POLLERR    0x008
#define INTF_POLLHUP    0x010
#define INTF_POLLNVAL   0x020
#define INTF_POLLRDNORM 0x040
#define INTF_POLLRDBAND 0x080
#define INTF_POLLWRNORM 0x100
#define INTF_POLLWRBAND 0x200
#define INTF_POLLMSG    0x400
#define INTF_POLLRDHUP  0x2000

#define INTF_POLLIN_MASK    (INTF_POLLIN | INTF_POLLRDNORM | INTF_POLLRDBAND | INTF_POLLPRI)
#define INTF_POLLOUT_MASK   (INTF_POLLOUT | INTF_POLLWRNORM | INTF_POLLWRBAND)

static void musl2dfs_events(short *events)
{
    short origin_e = *events;
    short result_e = 0;

    if (origin_e & INTF_POLLIN_MASK)
    {
        result_e |= IMPL_POLLIN;
    }

    if (origin_e & INTF_POLLOUT_MASK)
    {
        result_e |= IMPL_POLLOUT;
    }

    if (origin_e & INTF_POLLERR)
    {
        result_e |= IMPL_POLLERR;
    }

    if (origin_e & INTF_POLLHUP)
    {
        result_e |= IMPL_POLLHUP;
    }

    if (origin_e & INTF_POLLNVAL)
    {
        result_e |= IMPL_POLLNVAL;
    }

    *events = result_e;
}

static void dfs2musl_events(short *events)
{
    short origin_e = *events;
    short result_e = 0;

    if (origin_e & IMPL_POLLIN)
    {
        result_e |= INTF_POLLIN_MASK;
    }

    if (origin_e & IMPL_POLLOUT)
    {
        result_e |= INTF_POLLOUT_MASK;
    }

    if (origin_e & IMPL_POLLERR)
    {
        result_e |= INTF_POLLERR;
    }

    if (origin_e & IMPL_POLLHUP)
    {
        result_e |= INTF_POLLHUP;
    }

    if (origin_e & IMPL_POLLNVAL)
    {
        result_e |= INTF_POLLNVAL;
    }

    *events = result_e;
}

sysret_t sys_poll(struct pollfd *fds, nfds_t nfds, int timeout)
{
    int ret = -1;
    int i = 0;
#ifdef ARCH_MM_MMU
    struct pollfd *kfds = RT_NULL;

    if (!lwp_user_accessable((void *)fds, nfds * sizeof *fds))
    {
        return -EFAULT;
    }

    kfds = (struct pollfd *)kmem_get(nfds * sizeof *kfds);
    if (!kfds)
    {
        return -ENOMEM;
    }

    lwp_get_from_user(kfds, fds, nfds * sizeof *kfds);

    for (i = 0; i < nfds; i++)
    {
        musl2dfs_events(&kfds[i].events);
    }
    ret = poll(kfds, nfds, timeout);
    if (ret > 0)
    {
        for (i = 0; i < nfds; i++)
        {
            dfs2musl_events(&kfds->revents);
        }
        lwp_put_to_user(fds, kfds, nfds * sizeof *kfds);
    }

    kmem_put(kfds);
    return ret;
#else
#ifdef RT_USING_MUSL
    for (i = 0; i < nfds; i++)
    {
        musl2dfs_events(&fds->events);
    }
#endif /* RT_USING_MUSL */
    if (!lwp_user_accessable((void *)fds, nfds * sizeof *fds))
    {
        return -EFAULT;
    }
    ret = poll(fds, nfds, timeout);
#ifdef RT_USING_MUSL
    if (ret > 0)
    {
        for (i = 0; i < nfds; i++)
        {
            dfs2musl_events(&fds->revents);
        }
    }
#endif /* RT_USING_MUSL */
    return ret;
#endif /* ARCH_MM_MMU */
}

sysret_t sys_select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
{
#ifdef ARCH_MM_MMU
    int ret = -1;
    fd_set *kreadfds = RT_NULL, *kwritefds = RT_NULL, *kexceptfds = RT_NULL;

    if (readfds)
    {
        if (!lwp_user_accessable((void *)readfds, sizeof *readfds))
        {
            SET_ERRNO(EFAULT);
            goto quit;
        }
        kreadfds = (fd_set *)kmem_get(sizeof *kreadfds);
        if (!kreadfds)
        {
            SET_ERRNO(ENOMEM);
            goto quit;
        }
        lwp_get_from_user(kreadfds, readfds, sizeof *kreadfds);
    }
    if (writefds)
    {
        if (!lwp_user_accessable((void *)writefds, sizeof *writefds))
        {
            SET_ERRNO(EFAULT);
            goto quit;
        }
        kwritefds = (fd_set *)kmem_get(sizeof *kwritefds);
        if (!kwritefds)
        {
            SET_ERRNO(ENOMEM);
            goto quit;
        }
        lwp_get_from_user(kwritefds, writefds, sizeof *kwritefds);
    }
    if (exceptfds)
    {
        if (!lwp_user_accessable((void *)exceptfds, sizeof *exceptfds))
        {
            SET_ERRNO(EFAULT);
            goto quit;
        }
        kexceptfds = (fd_set *)kmem_get(sizeof *kexceptfds);
        if (!kexceptfds)
        {
            SET_ERRNO(EINVAL);
            goto quit;
        }
        lwp_get_from_user(kexceptfds, exceptfds, sizeof *kexceptfds);
    }

    ret = select(nfds, kreadfds, kwritefds, kexceptfds, timeout);
    if (kreadfds)
    {
        lwp_put_to_user(readfds, kreadfds, sizeof *kreadfds);
    }
    if (kwritefds)
    {
        lwp_put_to_user(writefds, kwritefds, sizeof *kwritefds);
    }
    if (kexceptfds)
    {
        lwp_put_to_user(exceptfds, kexceptfds, sizeof *kexceptfds);
    }
quit:
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    if (kreadfds)
    {
        kmem_put(kreadfds);
    }
    if (kwritefds)
    {
        kmem_put(kwritefds);
    }
    if (kexceptfds)
    {
        kmem_put(kexceptfds);
    }
    return ret;
#else
    int ret;

    if (!lwp_user_accessable((void *)readfds, sizeof *readfds))
    {
        return -EFAULT;
    }
    if (!lwp_user_accessable((void *)writefds, sizeof *writefds))
    {
        return -EFAULT;
    }
    if (!lwp_user_accessable((void *)exceptfds, sizeof *exceptfds))
    {
        return -EFAULT;
    }
    ret = select(nfds, readfds, writefds, exceptfds, timeout);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

sysret_t sys_unlink(const char *pathname)
{
#ifdef ARCH_MM_MMU
    int ret = -1;
    rt_size_t len = 0;
    char *kname = RT_NULL;
    int a_err = 0;

    lwp_user_strlen(pathname, &a_err);
    if (a_err)
    {
        return -EFAULT;
    }

    len = rt_strlen(pathname);
    if (!len)
    {
        return -EINVAL;
    }

    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        return -ENOMEM;
    }

    lwp_get_from_user(kname, (void *)pathname, len + 1);
    ret = unlink(kname);
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kname);
    return ret;
#else
    int ret = 0;
    ret = unlink(pathname);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

/* syscall: "nanosleep" ret: "int" args: "const struct timespec *" "struct timespec *" */
sysret_t sys_nanosleep(const struct timespec *rqtp, struct timespec *rmtp)
{
    int ret = 0;
    dbg_log(DBG_LOG, "sys_nanosleep\n");
    if (!lwp_user_accessable((void *)rqtp, sizeof *rqtp))
        return -EFAULT;

#ifdef ARCH_MM_MMU
    struct timespec rqtp_k;
    struct timespec rmtp_k;

    lwp_get_from_user(&rqtp_k, (void *)rqtp, sizeof rqtp_k);
    ret = nanosleep(&rqtp_k, &rmtp_k);
    if ((ret != -1 || rt_get_errno() == EINTR) && rmtp && lwp_user_accessable((void *)rmtp, sizeof *rmtp))
    {
        lwp_put_to_user(rmtp, (void *)&rmtp_k, sizeof rmtp_k);
        if(ret != 0)
            return -EINTR;
    }
#else
    if (rmtp)
    {
        if (!lwp_user_accessable((void *)rmtp, sizeof *rmtp))
            return -EFAULT;
        ret = nanosleep(rqtp, rmtp);
    }
#endif
    return (ret < 0 ? GET_ERRNO() : ret);
}

/* syscall: "gettimeofday" ret: "int" args: "struct timeval *" "struct timezone *" */
sysret_t sys_gettimeofday(struct timeval *tp, struct timezone *tzp)
{
#ifdef ARCH_MM_MMU
    struct timeval t_k;

    if (tp)
    {
        if (!lwp_user_accessable((void *)tp, sizeof *tp))
        {
            return -EFAULT;
        }

        t_k.tv_sec = rt_tick_get() / RT_TICK_PER_SECOND;
        t_k.tv_usec = (rt_tick_get() % RT_TICK_PER_SECOND) * (1000000 / RT_TICK_PER_SECOND);

        lwp_put_to_user(tp, (void *)&t_k, sizeof t_k);
    }
#else
    if (tp)
    {
        if (!lwp_user_accessable((void *)tp, sizeof *tp))
        {
            return -EFAULT;
        }
        tp->tv_sec = rt_tick_get() / RT_TICK_PER_SECOND;
        tp->tv_usec = (rt_tick_get() % RT_TICK_PER_SECOND) * (1000000 / RT_TICK_PER_SECOND);
    }
#endif

    return 0;
}

sysret_t sys_settimeofday(const struct timeval *tv, const struct timezone *tzp)
{
    return 0;
}

sysret_t sys_exec(char *filename, int argc, char **argv, char **envp)
{
    return lwp_execve(filename, 0, argc, argv, envp);
}

sysret_t sys_kill(int pid, int sig)
{
    int ret = 0;
    ret = lwp_kill(pid, sig);
    return (ret < 0 ? GET_ERRNO() : ret);
}

sysret_t sys_getpid(void)
{
    return lwp_getpid();
}

/* syscall: "getpriority" ret: "int" args: "int" "id_t" */
sysret_t sys_getpriority(int which, id_t who)
{
    if (which == PRIO_PROCESS)
    {
        rt_thread_t tid;

        tid = rt_thread_self();
        if (who == (id_t)(rt_size_t)tid || who == 0xff)
        {
            return tid->current_priority;
        }
    }

    return 0xff;
}

/* syscall: "setpriority" ret: "int" args: "int" "id_t" "int" */
sysret_t sys_setpriority(int which, id_t who, int prio)
{
    if (which == PRIO_PROCESS)
    {
        rt_thread_t tid;

        tid = rt_thread_self();
        if ((who == (id_t)(rt_size_t)tid || who == 0xff) && (prio >= 0 && prio < RT_THREAD_PRIORITY_MAX))
        {
            rt_thread_control(tid, RT_THREAD_CTRL_CHANGE_PRIORITY, &prio);
            return 0;
        }
    }

    return -1;
}

rt_sem_t sys_sem_create(const char *name, rt_uint32_t value, rt_uint8_t flag)
{
    rt_sem_t sem = rt_sem_create(name, value, flag);
    if (lwp_user_object_add(lwp_self(), (rt_object_t)sem) != 0)
    {
        rt_sem_delete(sem);
        sem = NULL;
    }
    return sem;
}

sysret_t sys_sem_delete(rt_sem_t sem)
{
    return lwp_user_object_delete(lwp_self(), (rt_object_t)sem);
}

sysret_t sys_sem_take(rt_sem_t sem, rt_int32_t time)
{
    return rt_sem_take_interruptible(sem, time);
}

sysret_t sys_sem_release(rt_sem_t sem)
{
    return rt_sem_release(sem);
}

rt_mutex_t sys_mutex_create(const char *name, rt_uint8_t flag)
{
    rt_mutex_t mutex = rt_mutex_create(name, flag);
    if(mutex == NULL)
        return NULL;
    if (lwp_user_object_add(lwp_self(), (rt_object_t)mutex) != 0)
    {
        rt_mutex_delete(mutex);
        mutex = NULL;
    }
    return mutex;
}

sysret_t sys_mutex_delete(rt_mutex_t mutex)
{
    return lwp_user_object_delete(lwp_self(), (rt_object_t)mutex);
}

sysret_t sys_mutex_take(rt_mutex_t mutex, rt_int32_t time)
{
    return rt_mutex_take_interruptible(mutex, time);
}

sysret_t sys_mutex_release(rt_mutex_t mutex)
{
    return rt_mutex_release(mutex);
}

#ifdef ARCH_MM_MMU
/* memory allocation */
rt_base_t sys_brk(void *addr)
{
    return lwp_brk(addr);
}

void *sys_mmap2(void *addr, size_t length, int prot,
        int flags, int fd, off_t pgoffset)
{
    return lwp_mmap2(addr, length, prot, flags, fd, pgoffset);
}

sysret_t sys_munmap(void *addr, size_t length)
{
    return lwp_munmap(addr);
}

void *sys_mremap(void *old_address, size_t old_size,
             size_t new_size, int flags, void *new_address)
{
    return (void *)-1;
}

sysret_t sys_madvise(void *addr, size_t len, int behav)
{
    return -ENOSYS;
}
#endif

rt_event_t sys_event_create(const char *name, rt_uint8_t flag)
{
    rt_event_t event = rt_event_create(name, flag);
    if (lwp_user_object_add(lwp_self(), (rt_object_t)event) != 0)
    {
        rt_event_delete(event);
        event = NULL;
    }
    return event;
}

sysret_t sys_event_delete(rt_event_t event)
{
    return lwp_user_object_delete(lwp_self(), (rt_object_t)event);
}

sysret_t sys_event_send(rt_event_t event, rt_uint32_t set)
{
    return rt_event_send(event, set);
}

sysret_t sys_event_recv(rt_event_t   event,
                       rt_uint32_t  set,
                       rt_uint8_t   opt,
                       rt_int32_t   timeout,
                       rt_uint32_t *recved)
{
    if ((recved != NULL) && !lwp_user_accessable((void *)recved, sizeof(rt_uint32_t *)))
    {
        return -EFAULT;
    }
    return rt_event_recv(event, set, opt, timeout, recved);
}

rt_mailbox_t sys_mb_create(const char *name, rt_size_t size, rt_uint8_t flag)
{
    rt_mailbox_t mb = rt_mb_create(name, size, flag);
    if (lwp_user_object_add(lwp_self(), (rt_object_t)mb) != 0)
    {
        rt_mb_delete(mb);
        mb = NULL;
    }
    return mb;
}

sysret_t sys_mb_delete(rt_mailbox_t mb)
{
    return lwp_user_object_delete(lwp_self(), (rt_object_t)mb);
}

sysret_t sys_mb_send(rt_mailbox_t mb, rt_ubase_t value)
{
    return rt_mb_send(mb, value);
}

sysret_t sys_mb_send_wait(rt_mailbox_t mb,
                         rt_ubase_t  value,
                         rt_int32_t   timeout)
{
    return rt_mb_send_wait(mb, value, timeout);
}

sysret_t sys_mb_recv(rt_mailbox_t mb, rt_ubase_t *value, rt_int32_t timeout)
{
    if (!lwp_user_accessable((void *)value, sizeof(rt_ubase_t *)))
    {
        return -EFAULT;
    }
    return rt_mb_recv(mb, (rt_ubase_t *)value, timeout);
}

rt_mq_t sys_mq_create(const char *name,
                     rt_size_t   msg_size,
                     rt_size_t   max_msgs,
                     rt_uint8_t  flag)
{
    rt_mq_t mq = rt_mq_create(name, msg_size, max_msgs, flag);
    if (lwp_user_object_add(lwp_self(), (rt_object_t)mq) != 0)
    {
        rt_mq_delete(mq);
        mq = NULL;
    }
    return mq;
}

sysret_t sys_mq_delete(rt_mq_t mq)
{
    return lwp_user_object_delete(lwp_self(), (rt_object_t)mq);
}

sysret_t sys_mq_send(rt_mq_t mq, void *buffer, rt_size_t size)
{
    if (!lwp_user_accessable((void *)buffer, size))
    {
        return -EFAULT;
    }
    return rt_mq_send(mq, buffer, size);
}

sysret_t sys_mq_urgent(rt_mq_t mq, void *buffer, rt_size_t size)
{
    if (!lwp_user_accessable((void *)buffer, size))
    {
        return -EFAULT;
    }
    return rt_mq_urgent(mq, buffer, size);
}

sysret_t sys_mq_recv(rt_mq_t    mq,
                    void      *buffer,
                    rt_size_t  size,
                    rt_int32_t timeout)
{
    if (!lwp_user_accessable((void *)buffer, size))
    {
        return -EFAULT;
    }
    return rt_mq_recv(mq, buffer, size, timeout);
}

static void timer_timeout_callback(void *parameter)
{
    rt_sem_t sem = (rt_sem_t)parameter;
    rt_sem_release(sem);
}

rt_timer_t sys_rt_timer_create(const char *name,
                               void *data,
                               rt_tick_t time,
                               rt_uint8_t flag)
{
    rt_timer_t timer = rt_timer_create(name, timer_timeout_callback, (void *)data, time, flag);
    if (lwp_user_object_add(lwp_self(), (rt_object_t)timer) != 0)
    {
        rt_timer_delete(timer);
        timer = NULL;
    }
    return timer;
}

sysret_t sys_rt_timer_delete(rt_timer_t timer)
{
    return lwp_user_object_delete(lwp_self(), (rt_object_t)timer);
}

sysret_t sys_rt_timer_start(rt_timer_t timer)
{
    return rt_timer_start(timer);
}

sysret_t sys_rt_timer_stop(rt_timer_t timer)
{
    return rt_timer_stop(timer);
}

sysret_t sys_rt_timer_control(rt_timer_t timer, int cmd, void *arg)
{
    return rt_timer_control(timer, cmd, arg);
}

/* MUSL compatible */
struct ksigevent
{
    union sigval sigev_value;
    int sigev_signo;
    int sigev_notify;
    int sigev_tid;
};

/* to protect unsafe implementation in current rt-smart toolchain */
RT_CTASSERT(sigevent_compatible, offsetof(struct ksigevent, sigev_tid) == offsetof(struct sigevent, sigev_notify_function));

sysret_t sys_timer_create(clockid_t clockid, struct sigevent *restrict sevp, timer_t *restrict timerid)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    struct sigevent sevp_k;
    timer_t timerid_k;
    int utimer;

    if (sevp == NULL)
    {
        sevp_k.sigev_notify = SIGEV_SIGNAL;
        sevp_k.sigev_signo = SIGALRM;
        sevp = &sevp_k;
    }
    else
    {
        /* clear extra bytes if any */
        if (sizeof(struct ksigevent) < sizeof(struct sigevent))
            memset(&sevp_k, 0, sizeof(sevp_k));

        /* musl passes `struct ksigevent` to kernel, we shoule only get size of that bytes */
        if (!lwp_get_from_user(&sevp_k, (void *)sevp, sizeof(struct ksigevent)))
        {
            return -EINVAL;
        }
    }

    ret = _SYS_WRAP(timer_create(clockid, &sevp_k, &timerid_k));

    if (ret != -RT_ERROR)
    {
        utimer = (rt_ubase_t)timerid_k;
        if (!lwp_put_to_user(sevp, (void *)&sevp_k, sizeof(struct ksigevent)) ||
            !lwp_put_to_user(timerid, (void *)&utimer, sizeof(utimer)))
            ret = -EINVAL;
    }
#else
    ret = _SYS_WRAP(timer_create(clockid, sevp, timerid));
#endif
    return ret;
}

sysret_t sys_timer_delete(timer_t timerid)
{
    int ret = timer_delete(timerid);
    return (ret < 0 ? GET_ERRNO() : ret);
}

sysret_t sys_timer_settime(timer_t timerid, int flags,
                           const struct itimerspec *restrict new_value,
                           struct itimerspec *restrict old_value)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    struct itimerspec new_value_k;
    struct itimerspec old_value_k;

    if (!lwp_get_from_user(&new_value_k, (void *)new_value, sizeof(*new_value)) ||
        (old_value && !lwp_get_from_user(&old_value_k, (void *)old_value, sizeof(*old_value))))
    {
        return -EFAULT;
    }

    ret = timer_settime(timerid, flags, &new_value_k, &old_value_k);
    lwp_put_to_user(old_value, (void *)&old_value_k, sizeof old_value_k);

#else
    ret = timer_settime(timerid, flags, new_value, old_value);
#endif
    return (ret < 0 ? GET_ERRNO() : ret);
}

sysret_t sys_timer_gettime(timer_t timerid, struct itimerspec *curr_value)
{
    int ret = 0;
#ifdef ARCH_MM_MMU

    struct itimerspec curr_value_k;
    lwp_get_from_user(&curr_value_k, (void *)curr_value, sizeof curr_value_k);
    ret = timer_gettime(timerid, &curr_value_k);
    lwp_put_to_user(curr_value, (void *)&curr_value_k, sizeof curr_value_k);
#else
    ret = timer_gettime(timerid, curr_value);
#endif
    return (ret < 0 ? GET_ERRNO() : ret);
}

sysret_t sys_timer_getoverrun(timer_t timerid)
{
    int ret = 0;
    ret = timer_getoverrun(timerid);
    return (ret < 0 ? GET_ERRNO() : ret);
}

rt_thread_t sys_thread_create(void *arg[])
{
    rt_base_t level = 0;
    void *user_stack = 0;
    struct rt_lwp *lwp = 0;
    rt_thread_t thread = RT_NULL;
    int tid = 0;

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
    thread->bind_cpu = lwp->bind_cpu;
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

    user_stack  = (void *)arg[3];
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

    thread->lwp = (void*)lwp;
    thread->tid = tid;
    lwp_tid_set_thread(tid, thread);

    if (lwp->debug)
    {
        rt_thread_control(thread, RT_THREAD_CTRL_BIND_CPU, (void*)0);
    }

    level = rt_hw_interrupt_disable();
    rt_list_insert_after(&lwp->t_grp, &thread->sibling);
    rt_hw_interrupt_enable(level);

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
#define CLONE_VM    0x00000100
#define CLONE_FS    0x00000200
#define CLONE_FILES 0x00000400
#define CLONE_SIGHAND   0x00000800
#define CLONE_PTRACE    0x00002000
#define CLONE_VFORK 0x00004000
#define CLONE_PARENT    0x00008000
#define CLONE_THREAD    0x00010000
#define CLONE_NEWNS 0x00020000
#define CLONE_SYSVSEM   0x00040000
#define CLONE_SETTLS    0x00080000
#define CLONE_PARENT_SETTID 0x00100000
#define CLONE_CHILD_CLEARTID    0x00200000
#define CLONE_DETACHED  0x00400000
#define CLONE_UNTRACED  0x00800000
#define CLONE_CHILD_SETTID  0x01000000
#define CLONE_NEWCGROUP 0x02000000
#define CLONE_NEWUTS    0x04000000
#define CLONE_NEWIPC    0x08000000
#define CLONE_NEWUSER   0x10000000
#define CLONE_NEWPID    0x20000000
#define CLONE_NEWNET    0x40000000
#define CLONE_IO    0x80000000

/* arg[] -> flags
 *          stack
 *          new_tid
 *          tls
 *          set_clear_tid_address
 *          quit_func
 *          start_args
 *          */
#define SYS_CLONE_ARGS_NR 7

long _sys_clone(void *arg[])
{
    rt_base_t level = 0;
    struct rt_lwp *lwp = 0;
    rt_thread_t thread = RT_NULL;
    rt_thread_t self = RT_NULL;
    int tid = 0;

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
    if ((flags & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_THREAD | CLONE_SYSVSEM))
            != (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_THREAD | CLONE_SYSVSEM))
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
            self->init_priority,
            self->init_tick);
    if (!thread)
    {
        goto fail;
    }

#ifdef RT_USING_SMP
    thread->bind_cpu = lwp->bind_cpu;
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
        rt_thread_control(thread, RT_THREAD_CTRL_BIND_CPU, (void*)0);
    }

    level = rt_hw_interrupt_disable();
    rt_list_insert_after(&lwp->t_grp, &thread->sibling);
    rt_hw_interrupt_enable(level);

    /* copy origin stack */
    rt_memcpy(thread->stack_addr, self->stack_addr, thread->stack_size);
    lwp_tid_set_thread(tid, thread);
    arch_set_thread_context(arch_clone_exit,
            (void *)((char *)thread->stack_addr + thread->stack_size),
            user_stack, &thread->sp);
    /* new thread never reach there */
    rt_thread_startup(thread);
    return (long)tid;
fail:
    lwp_tid_put(tid);
    if (lwp)
    {
        lwp_ref_dec(lwp);
    }
    return GET_ERRNO();
}

rt_weak long sys_clone(void *arg[])
{
    return _sys_clone(arg);
}

int lwp_dup_user(rt_varea_t varea, void *arg);

static int _copy_process(struct rt_lwp *dest_lwp, struct rt_lwp *src_lwp)
{
    int err;
    dest_lwp->lwp_obj->source = src_lwp->aspace;
    err = rt_aspace_traversal(src_lwp->aspace, lwp_dup_user, dest_lwp);
    dest_lwp->lwp_obj->source = NULL;
    return err;
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
    dst->leader = 0;
    dst->session = src->session;
    dst->tty_old_pgrp = 0;
    dst->__pgrp = src->__pgrp;
    dst->tty = src->tty;
    rt_memcpy(dst->cmd, src->cmd, RT_NAME_MAX);

    dst->sa_flags = src->sa_flags;
    dst->signal_mask = src->signal_mask;
    rt_memcpy(dst->signal_handler, src->signal_handler, sizeof dst->signal_handler);
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
            d_s = fdt_fd_get(src_fdt, i);
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
    rt_base_t level;
    int tid = 0;
    sysret_t falival = 0;
    struct rt_lwp *lwp = RT_NULL;
    struct rt_lwp *self_lwp = RT_NULL;
    rt_thread_t thread = RT_NULL;
    rt_thread_t self_thread = RT_NULL;
    void *user_stack = RT_NULL;

    /* new lwp */
    lwp = lwp_new();
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

    /* copy process */
    if (_copy_process(lwp, self_lwp) != 0)
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
            self_thread->init_priority,
            self_thread->init_tick);
    if (!thread)
    {
        SET_ERRNO(ENOMEM);
        goto fail;
    }

    thread->cleanup = self_thread->cleanup;
    thread->user_entry = self_thread->user_entry;
    thread->user_stack = self_thread->user_stack;
    thread->user_stack_size = self_thread->user_stack_size;
    thread->signal_mask = self_thread->signal_mask;
    thread->thread_idr = self_thread->thread_idr;
    thread->lwp = (void *)lwp;
    thread->tid = tid;

    level = rt_hw_interrupt_disable();

    /* add thread to lwp process */
    rt_list_insert_after(&lwp->t_grp, &thread->sibling);

    /* lwp add to children link */
    lwp->sibling = self_lwp->first_child;
    self_lwp->first_child = lwp;
    lwp->parent = self_lwp;

    rt_hw_interrupt_enable(level);

    /* copy origin stack */
    rt_memcpy(thread->stack_addr, self_thread->stack_addr, self_thread->stack_size);
    lwp_tid_set_thread(tid, thread);

    /* duplicate user objects */
    lwp_user_object_dup(lwp, self_lwp);

    level = rt_hw_interrupt_disable();
    user_stack = arch_get_user_sp();
    rt_hw_interrupt_enable(level);

    arch_set_thread_context(arch_fork_exit,
            (void *)((char *)thread->stack_addr + thread->stack_size),
            user_stack, &thread->sp);
    /* new thread never reach there */
    level = rt_hw_interrupt_disable();
    if (lwp->tty != RT_NULL)
    {
        int ret;
        struct rt_lwp *old_lwp;

        old_lwp = lwp->tty->foreground;
        rt_mutex_take(&lwp->tty->lock, RT_WAITING_FOREVER);
        ret = tty_push(&lwp->tty->head, old_lwp);
        rt_mutex_release(&lwp->tty->lock);
        if (ret < 0)
        {
            LOG_E("malloc fail!\n");
            SET_ERRNO(ENOMEM);
            goto fail;
        }

        lwp->tty->foreground = lwp;
    }
    rt_hw_interrupt_enable(level);
    rt_thread_startup(thread);
    return lwp_to_pid(lwp);
fail:
    falival = GET_ERRNO();

    if (tid != 0)
    {
        lwp_tid_put(tid);
    }
    if (lwp)
    {
        lwp_ref_dec(lwp);
    }
    return falival;
}

size_t lwp_user_strlen(const char *s, int *err)
{
    size_t len = 0;

    while (1)
    {
        if (!lwp_user_accessable((void *)(s + len), sizeof(char)))
        {
            if (err)
            {
                *err = 1;
            }
            return 0;
        }
        if (s[len] == '\0')
        {
            if (err)
            {
                *err = 0;
            }
            return len;
        }
        len++;
    }
}

/* arm needs to wrap fork/clone call to preserved lr & caller saved regs */

rt_weak sysret_t sys_fork(void)
{
    return _sys_fork();
}

rt_weak sysret_t sys_vfork(void)
{
    return sys_fork();
}

struct process_aux *lwp_argscopy(struct rt_lwp *lwp, int argc, char **argv, char **envp);
int lwp_load(const char *filename, struct rt_lwp *lwp, uint8_t *load_addr, size_t addr_size, struct process_aux *aux);
void lwp_user_obj_free(struct rt_lwp *lwp);

#define _swap_lwp_data(lwp_used, lwp_new, type, member) \
    do {\
        type tmp;\
        tmp = lwp_used->member;\
        lwp_used->member = lwp_new->member;\
        lwp_new->member = tmp;\
    } while (0)

static char *_insert_args(int new_argc, char *new_argv[], struct lwp_args_info *args)
{
    void *page = NULL;
    int err = 0;
    char **nargv;
    char **nenvp;
    char *p;
    int i, len;
    int nsize;

    if (new_argc == 0)
    {
        goto quit;
    }
    page = rt_pages_alloc_ext(0, PAGE_ANY_AVAILABLE); /* 1 page */
    if (!page)
    {
        goto quit;
    }

    nsize = new_argc * sizeof(char *);
    for (i = 0; i < new_argc; i++)
    {
        nsize += rt_strlen(new_argv[i]) + 1;
    }
    if (nsize + args->size > ARCH_PAGE_SIZE)
    {
        err = 1;
        goto quit;
    }
    nargv = (char **)page;
    nenvp = nargv + args->argc + new_argc + 1;
    p = (char *)(nenvp + args->envc + 1);
    /* insert argv */
    for (i = 0; i < new_argc; i++)
    {
        nargv[i] = p;
        len = rt_strlen(new_argv[i]) + 1;
        rt_memcpy(p, new_argv[i], len);
        p += len;
    }
    /* copy argv */
    nargv += new_argc;
    for (i = 0; i < args->argc; i++)
    {
        nargv[i] = p;
        len = rt_strlen(args->argv[i]) + 1;
        rt_memcpy(p, args->argv[i], len);
        p += len;
    }
    nargv[i] = NULL;
    /* copy envp */
    for (i = 0; i < args->envc; i++)
    {
        nenvp[i] = p;
        len = rt_strlen(args->envp[i]) + 1;
        rt_memcpy(p, args->envp[i], len);
        p += len;
    }
    nenvp[i] = NULL;

    /* update args */
    args->argv = (char **)page;
    args->argc = args->argc + new_argc;
    args->envp = args->argv + args->argc + 1;
    /* args->envc no change */
    args->size = args->size + nsize;

quit:
    if (err && page)
    {
        rt_pages_free(page, 0);
        page = NULL;
    }
    return page;
}

#define INTERP_BUF_SIZE 128
static char *_load_script(const char *filename, void *old_page, struct lwp_args_info *args)
{
    char *new_page = NULL;
    int fd = -RT_ERROR;
    int len;
    char interp[INTERP_BUF_SIZE];
    char *cp;
    char *i_name;
    char *i_arg;

    fd = open(filename, O_BINARY | O_RDONLY, 0);
    if (fd < 0)
    {
        goto quit;
    }
    len = read(fd, interp, INTERP_BUF_SIZE);
    if (len < 2)
    {
        goto quit;
    }
    /*
    * match find file header the first line.
    * eg: #!/bin/sh
    */
    if ((interp[0] != '#') || (interp[1] != '!'))
    {
        goto quit;
    }

    if (len == INTERP_BUF_SIZE)
    {
        len--;
    }
    interp[len] = '\0';

    if ((cp = strchr(interp, '\n')) == NULL)
    {
        cp = interp + INTERP_BUF_SIZE - 1;
    }
    *cp = '\0';
    while (cp > interp)
    {
        cp--;
        if ((*cp == ' ') || (*cp == '\t'))
        {
            *cp = '\0';
        }
        else
        {
            break;
        }
    }
    for (cp = interp + 2; (*cp == ' ') || (*cp == '\t'); cp++)
    {
        /* nothing */
    }
    if (*cp == '\0')
    {
        goto quit; /* No interpreter name found */
    }
    i_name = cp;
    i_arg = NULL;
    for (; *cp && (*cp != ' ') && (*cp != '\t'); cp++)
    {
        /* nothing */
    }
    while ((*cp == ' ') || (*cp == '\t'))
    {
        *cp++ = '\0';
    }
    if (*cp)
    {
        i_arg = cp;
    }

    if (i_arg)
    {
        new_page = _insert_args(1, &i_arg, args);
        if (!new_page)
        {
            goto quit;
        }
        rt_pages_free(old_page, 0);
        old_page = new_page;
    }
    new_page = _insert_args(1, &i_name, args);
    if (!new_page)
    {
        goto quit;
    }
    rt_pages_free(old_page, 0);

quit:
    if (fd >= 0)
    {
        close(fd);
    }
    return new_page;
}

int load_ldso(struct rt_lwp *lwp, char *exec_name, char *const argv[], char *const envp[])
{
    int ret = -1;
    int i;
    void *page;
    void *new_page;
    int argc = 0;
    int envc = 0;
    int size;
    char **kargv;
    char **kenvp;
    size_t len;
    char *p;
    char *i_arg;
    struct lwp_args_info args_info;
    struct process_aux *aux;

    size = sizeof(char *);
    if (argv)
    {
        while (1)
        {
            if (!argv[argc])
            {
                break;
            }
            len = rt_strlen((const char *)argv[argc]);
            size += sizeof(char *) + len + 1;
            argc++;
        }
    }
    if (envp)
    {
        while (1)
        {
            if (!envp[envc])
            {
                break;
            }
            len = rt_strlen((const char *)envp[envc]);
            size += sizeof(char *) + len + 1;
            envc++;
        }
    }

    page = rt_pages_alloc_ext(0, PAGE_ANY_AVAILABLE); /* 1 page */
    if (!page)
    {
        SET_ERRNO(ENOMEM);
        goto quit;
    }
    kargv = (char **)page;
    kenvp = kargv + argc + 1;
    p = (char *)(kenvp + envc + 1);
    /* copy argv */
    if (argv)
    {
        for (i = 0; i < argc; i++)
        {
            kargv[i] = p;
            len = rt_strlen(argv[i]) + 1;
            rt_memcpy(p, argv[i], len);
            p += len;
        }
        kargv[i] = NULL;
    }
    /* copy envp */
    if (envp)
    {
        for (i = 0; i < envc; i++)
        {
            kenvp[i] = p;
            len = rt_strlen(envp[i]) + 1;
            rt_memcpy(p, envp[i], len);
            p += len;
        }
        kenvp[i] = NULL;
    }

    args_info.argc = argc;
    args_info.argv = kargv;
    args_info.envc = envc;
    args_info.envp = kenvp;
    args_info.size = size;

    new_page = _insert_args(1, &exec_name, &args_info);
    if (!new_page)
    {
        SET_ERRNO(ENOMEM);
        goto quit;
    }
    rt_pages_free(page, 0);
    page = new_page;

    i_arg = "-e";
    new_page = _insert_args(1, &i_arg, &args_info);
    if (!new_page)
    {
        SET_ERRNO(ENOMEM);
        goto quit;
    }
    rt_pages_free(page, 0);
    page = new_page;

    i_arg = "ld.so";
    new_page = _insert_args(1, &i_arg, &args_info);
    if (!new_page)
    {
        SET_ERRNO(ENOMEM);
        goto quit;
    }
    rt_pages_free(page, 0);
    page = new_page;

    if ((aux = lwp_argscopy(lwp, args_info.argc, args_info.argv, args_info.envp)) == NULL)
    {
        SET_ERRNO(ENOMEM);
        goto quit;
    }

    ret = lwp_load("/lib/ld.so", lwp, RT_NULL, 0, aux);

    rt_strncpy(lwp->cmd, exec_name, RT_NAME_MAX);
quit:
    if (page)
    {
        rt_pages_free(page, 0);
    }
    return (ret < 0 ? GET_ERRNO() : ret);
}

sysret_t sys_execve(const char *path, char *const argv[], char *const envp[])
{
    int ret = -1;
    int argc = 0;
    int envc = 0;
    void *page = NULL;
    void *new_page;
    int size = 0;
    size_t len;
    int access_err;
    char **kargv;
    char **kenvp;
    char *p;
    struct rt_lwp *new_lwp = NULL;
    struct rt_lwp *lwp;
    rt_base_t level;
    int uni_thread;
    rt_thread_t thread;
    struct process_aux *aux;
    int i;
    struct lwp_args_info args_info;

    if (access(path, X_OK) != 0)
    {
        return -EACCES;
    }

    lwp = lwp_self();
    thread = rt_thread_self();
    uni_thread = 1;
    level = rt_hw_interrupt_disable();
    if (lwp->t_grp.prev != &thread->sibling)
    {
        uni_thread = 0;
    }
    if (lwp->t_grp.next != &thread->sibling)
    {
        uni_thread = 0;
    }
    rt_hw_interrupt_enable(level);
    if (!uni_thread)
    {
        SET_ERRNO(EINVAL);
        goto quit;
    }

    len = lwp_user_strlen(path, &access_err);
    if (access_err)
    {
        SET_ERRNO(EFAULT);
        goto quit;
    }

    size += sizeof(char *);
    if (argv)
    {
        while (1)
        {
            if (!lwp_user_accessable((void *)(argv + argc), sizeof(char *)))
            {
                SET_ERRNO(EFAULT);
                goto quit;
            }
            if (!argv[argc])
            {
                break;
            }
            len = lwp_user_strlen((const char *)argv[argc], &access_err);
            if (access_err)
            {
                SET_ERRNO(EFAULT);
                goto quit;
            }
            size += sizeof(char *) + len + 1;
            argc++;
        }
    }
    size += sizeof(char *);
    if (envp)
    {
        while (1)
        {
            if (!lwp_user_accessable((void *)(envp + envc), sizeof(char *)))
            {
                SET_ERRNO(EFAULT);
                goto quit;
            }
            if (!envp[envc])
            {
                break;
            }
            len = lwp_user_strlen((const char *)envp[envc], &access_err);
            if (access_err)
            {
                SET_ERRNO(EFAULT);
                goto quit;
            }
            size += sizeof(char *) + len + 1;
            envc++;
        }
    }
    if (size > ARCH_PAGE_SIZE)
    {
        SET_ERRNO(EINVAL);
        goto quit;
    }
    page = rt_pages_alloc_ext(0, PAGE_ANY_AVAILABLE); /* 1 page */
    if (!page)
    {
        SET_ERRNO(ENOMEM);
        goto quit;
    }

    kargv = (char **)page;
    kenvp = kargv + argc + 1;
    p = (char *)(kenvp + envc + 1);
    /* copy argv */
    if (argv)
    {
        for (i = 0; i < argc; i++)
        {
            kargv[i] = p;
            len = rt_strlen(argv[i]) + 1;
            rt_memcpy(p, argv[i], len);
            p += len;
        }
        kargv[i] = NULL;
    }
    /* copy envp */
    if (envp)
    {
        for (i = 0; i < envc; i++)
        {
            kenvp[i] = p;
            len = rt_strlen(envp[i]) + 1;
            rt_memcpy(p, envp[i], len);
            p += len;
        }
        kenvp[i] = NULL;
    }

    /* alloc new lwp to operation */
    new_lwp = (struct rt_lwp *)rt_malloc(sizeof(struct rt_lwp));
    if (!new_lwp)
    {
        SET_ERRNO(ENOMEM);
        goto quit;
    }
    rt_memset(new_lwp, 0, sizeof(struct rt_lwp));
    new_lwp->ref = 1;
    lwp_user_object_lock_init(new_lwp);
    ret = lwp_user_space_init(new_lwp, 0);
    if (ret != 0)
    {
        SET_ERRNO(ENOMEM);
        goto quit;
    }
    /* file is a script ? */
    args_info.argc = argc;
    args_info.argv = kargv;
    args_info.envc = envc;
    args_info.envp = kenvp;
    args_info.size = size;
    while (1)
    {
        new_page = _load_script(path, page, &args_info);
        if (!new_page)
        {
            break;
        }

        page = new_page;
        path = args_info.argv[0];
    }

    /* now load elf */
    if ((aux = lwp_argscopy(new_lwp, args_info.argc, args_info.argv, args_info.envp)) == NULL)
    {
        SET_ERRNO(ENOMEM);
        goto quit;
    }
    ret = lwp_load(path, new_lwp, RT_NULL, 0, aux);
    if (ret == 1)
    {
        /* dynamic */
        lwp_unmap_user(new_lwp, (void *)(USER_VADDR_TOP - ARCH_PAGE_SIZE));
        ret = load_ldso(new_lwp, (char *)path, args_info.argv, args_info.envp);
    }
    if (ret == RT_EOK)
    {
        int off = 0;
        int last_backslash = 0;
        char *run_name = args_info.argv[0];

        /* clear all user objects */
        lwp_user_object_clear(lwp);

        /* find last \ or / */
        while (1)
        {
            char c = run_name[off++];

            if (c == '\0')
            {
                break;
            }
            if (c == '\\' || c == '/')
            {
                last_backslash = off;
            }
        }

        /* load ok, now set thread name and swap the data of lwp and new_lwp */
        level = rt_hw_interrupt_disable();

        rt_strncpy(thread->parent.name, run_name + last_backslash, RT_NAME_MAX);

        rt_pages_free(page, 0);

#ifdef ARCH_MM_MMU
        _swap_lwp_data(lwp, new_lwp, struct rt_aspace *, aspace);
        _swap_lwp_data(lwp, new_lwp, struct rt_lwp_objs *, lwp_obj);

        _swap_lwp_data(lwp, new_lwp, size_t, end_heap);
#endif
        _swap_lwp_data(lwp, new_lwp, uint8_t, lwp_type);
        _swap_lwp_data(lwp, new_lwp, void *, text_entry);
        _swap_lwp_data(lwp, new_lwp, uint32_t, text_size);
        _swap_lwp_data(lwp, new_lwp, void *, data_entry);
        _swap_lwp_data(lwp, new_lwp, uint32_t, data_size);

        _swap_lwp_data(lwp, new_lwp, void *, args);

        rt_memset(&thread->signal_mask, 0, sizeof(thread->signal_mask));
        rt_memset(&thread->signal_mask_bak, 0, sizeof(thread->signal_mask_bak));
        lwp->sa_flags = 0;
        rt_memset(&lwp->signal_mask, 0, sizeof(lwp->signal_mask));
        rt_memset(&lwp->signal_mask_bak, 0, sizeof(lwp->signal_mask_bak));
        rt_memset(lwp->signal_handler, 0, sizeof(lwp->signal_handler));

        /* to do: clsoe files with flag CLOEXEC */

        lwp_aspace_switch(thread);

        rt_hw_interrupt_enable(level);

        lwp_ref_dec(new_lwp);
        arch_start_umode(lwp->args,
                lwp->text_entry,
                (void*)USER_STACK_VEND,
                (char *)thread->stack_addr + thread->stack_size);
        /* never reach here */
    }
    return -EINVAL;
quit:
    if (page)
    {
        rt_pages_free(page, 0);
    }
    if (new_lwp)
    {
        lwp_ref_dec(new_lwp);
    }
    return (ret < 0 ? GET_ERRNO() : ret);
}
#endif /* ARCH_MM_MMU */

sysret_t sys_thread_delete(rt_thread_t thread)
{
#ifdef ARCH_MM_MMU
    return rt_thread_delete(thread);
#else
    sysret_t ret = 0;

    if(thread->parent.type != RT_Object_Class_Thread)
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

sysret_t sys_thread_startup(rt_thread_t thread)
{
    return rt_thread_startup(thread);
}

rt_thread_t sys_thread_self(void)
{
    return rt_thread_self();
}

/* sys channel */

sysret_t sys_channel_open(const char *name, int flags)
{
    return lwp_channel_open(FDT_TYPE_LWP, name, flags);
}

sysret_t sys_channel_close(int fd)
{
    return lwp_channel_close(FDT_TYPE_LWP, fd);
}

sysret_t sys_channel_send(int fd, rt_channel_msg_t data)
{
    return lwp_channel_send(FDT_TYPE_LWP, fd, data);
}

sysret_t sys_channel_send_recv_timeout(int fd, rt_channel_msg_t data, rt_channel_msg_t data_ret, rt_int32_t time)
{
    return lwp_channel_send_recv_timeout(FDT_TYPE_LWP, fd, data, data_ret, time);
}

sysret_t sys_channel_reply(int fd, rt_channel_msg_t data)
{
    return lwp_channel_reply(FDT_TYPE_LWP, fd, data);
}

sysret_t sys_channel_recv_timeout(int fd, rt_channel_msg_t data, rt_int32_t time)
{
    return lwp_channel_recv_timeout(FDT_TYPE_LWP, fd, data, time);
}

static struct rt_semaphore critical_lock;

static int critical_init(void)
{
    rt_sem_init(&critical_lock, "ct_lock", 1, RT_IPC_FLAG_FIFO);
    return 0;
}
INIT_DEVICE_EXPORT(critical_init);

void sys_enter_critical(void)
{
    rt_sem_take(&critical_lock, RT_WAITING_FOREVER);
}

void sys_exit_critical(void)
{
    rt_sem_release(&critical_lock);
}

/* syscall: "sys_log" ret: "int" args: "const char*" "size" */
static int __sys_log_enable = 0;
static int sys_log_enable(int argc, char** argv)
{
    if (argc == 1)
    {
        rt_kprintf("sys_log = %d\n", __sys_log_enable);
        return 0;
    }
    else
    {
        __sys_log_enable = atoi(argv[1]);
    }

    return 0;
}
MSH_CMD_EXPORT_ALIAS(sys_log_enable, sys_log, sys_log 1(enable)/0(disable));

sysret_t sys_log(const char* log, int size)
{
    rt_device_t console = rt_console_get_device();

    if (console && __sys_log_enable)
    {
        rt_device_write(console, -1, log, size);
    }

    return 0;
}

sysret_t sys_stat(const char *file, struct stat *buf)
{
    int ret = 0;
    int err;
    size_t len;
    size_t copy_len;
    char *copy_path;
    struct stat statbuff = {0};

    if (!lwp_user_accessable((void *)buf, sizeof(struct stat)))
    {
        return -EFAULT;
    }

    len = lwp_user_strlen(file, &err);
    if (err)
    {
        return -EFAULT;
    }

    copy_path = (char*)rt_malloc(len + 1);
    if (!copy_path)
    {
        return -ENOMEM;
    }

    copy_len = lwp_get_from_user(copy_path, (void*)file, len);
    if (copy_len == 0)
    {
        rt_free(copy_path);
        return -EFAULT;
    }
    copy_path[copy_len] = '\0';

    ret = _SYS_WRAP(stat(copy_path, &statbuff));
    rt_free(copy_path);

    if (ret == 0)
    {
        lwp_put_to_user(buf, &statbuff, sizeof statbuff);
    }

    return ret;
}

sysret_t sys_lstat(const char *file, struct stat *buf)
{
    int ret = 0;
    int err;
    size_t len;
    size_t copy_len;
    char *copy_path;
    struct stat statbuff = {0};

    if (!lwp_user_accessable((void *)buf, sizeof(struct stat)))
    {
        return -EFAULT;
    }

    len = lwp_user_strlen(file, &err);
    if (err)
    {
        return -EFAULT;
    }

    copy_path = (char*)rt_malloc(len + 1);
    if (!copy_path)
    {
        return -ENOMEM;
    }

    copy_len = lwp_get_from_user(copy_path, (void*)file, len);
    if (copy_len == 0)
    {
        rt_free(copy_path);
        return -EFAULT;
    }
    copy_path[copy_len] = '\0';
#ifdef RT_USING_DFS_V2
    ret = _SYS_WRAP(dfs_file_lstat(copy_path, &statbuff));
#else
    ret = _SYS_WRAP(stat(copy_path, &statbuff));
#endif
    rt_free(copy_path);

    if (ret == 0)
    {
        lwp_put_to_user(buf, &statbuff, sizeof statbuff);
    }

    return ret;
}

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
sysret_t sys_shmget(size_t key, size_t size, int create)
{
    return lwp_shmget(key, size, create);
}

sysret_t sys_shmrm(int id)
{
    return lwp_shmrm(id);
}

void* sys_shmat(int id, void* shm_vaddr)
{
    return lwp_shmat(id, shm_vaddr);
}

sysret_t sys_shmdt(void* shm_vaddr)
{
    return lwp_shmdt(shm_vaddr);
}
#elif defined RT_LWP_USING_SHM
void *sys_shm_alloc(int size)
{
    if (size < 0)
    {
        return RT_NULL;
    }
    return lwp_shm_alloc((rt_size_t)size);
}

void *sys_shm_retain(void *mem)
{
    if (!lwp_user_accessable(mem, sizeof (void *)))
    {
        return RT_NULL;
    }
    return lwp_shm_retain(mem);
}

sysret_t sys_shm_free(void *mem)
{
    if (!lwp_user_accessable(mem, sizeof (void *)))
    {
        return -EFAULT;
    }
    lwp_shm_free(mem);
    return 0;
}
#endif

/* device interfaces */
sysret_t sys_device_init(rt_device_t dev)
{
    return rt_device_init(dev);
}

sysret_t sys_device_register(rt_device_t dev, const char *name, rt_uint16_t flags)
{
    return rt_device_register(dev, name, flags);
}

sysret_t sys_device_control(rt_device_t dev, int cmd, void *arg)
{
    return rt_device_control(dev, cmd, arg);
}

rt_device_t sys_device_find(const char* name)
{
    return rt_device_find(name);
}

sysret_t sys_device_open(rt_device_t dev, rt_uint16_t oflag)
{
    return rt_device_open(dev, oflag);
}

sysret_t sys_device_close(rt_device_t dev)
{
    return rt_device_close(dev);
}

rt_ssize_t sys_device_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    return rt_device_read(dev, pos, buffer, size);
}

rt_ssize_t sys_device_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    return rt_device_write(dev, pos, buffer, size);
}

#ifdef RT_USING_SAL
/* network interfaces */
sysret_t sys_accept(int socket, struct musl_sockaddr *addr, socklen_t *addrlen)
{
    int ret = -1;
    struct sockaddr ksa;
    struct musl_sockaddr kmusladdr;
    socklen_t uaddrlen;
    socklen_t kaddrlen;

    if (addr)
    {
        if (!lwp_user_accessable(addrlen, sizeof (socklen_t)))
        {
            return -EFAULT;
        }
        lwp_get_from_user(&uaddrlen, addrlen, sizeof (socklen_t));
        if (!uaddrlen)
        {
            return -EINVAL;
        }

        if (!lwp_user_accessable(addr, uaddrlen))
        {
            return -EFAULT;
        }
    }

    kaddrlen = sizeof(struct sockaddr);
    ret = accept(socket, &ksa, &kaddrlen);
    if (ret >= 0)
    {
        if (addr)
        {
            sockaddr_tomusl(&ksa, &kmusladdr);
            if (uaddrlen > sizeof(struct musl_sockaddr))
            {
                uaddrlen = sizeof(struct musl_sockaddr);
            }
            lwp_put_to_user(addr, &kmusladdr, uaddrlen);
            lwp_put_to_user(addrlen, &uaddrlen, sizeof (socklen_t));
        }
    }
    return ret;
}

sysret_t sys_bind(int socket, const struct musl_sockaddr *name, socklen_t namelen)
{
    struct sockaddr sa;
    struct musl_sockaddr kname;

    if (!lwp_user_accessable((void *)name, namelen))
    {
        return -EFAULT;
    }

#ifdef SAL_USING_AF_UNIX
    if (name->sa_family  == AF_UNIX)
    {
        namelen = sizeof(struct sockaddr);
    }
#endif /* SAL_USING_AF_UNIX */

    lwp_get_from_user(&kname, (void *)name, namelen);

    sockaddr_tolwip(&kname, &sa);

    return bind(socket, &sa, namelen);
}

sysret_t sys_shutdown(int socket, int how)
{
    return shutdown(socket, how);
}

sysret_t sys_getpeername(int socket, struct musl_sockaddr *name, socklen_t *namelen)
{
    int ret = -1;
    struct sockaddr sa;
    struct musl_sockaddr kname;
    socklen_t unamelen;
    socklen_t knamelen;

    if (!lwp_user_accessable(namelen, sizeof (socklen_t *)))
    {
        return -EFAULT;
    }
    lwp_get_from_user(&unamelen, namelen, sizeof (socklen_t *));
    if (!unamelen)
    {
        return -EINVAL;
    }

    if (!lwp_user_accessable(name, unamelen))
    {
        return -EFAULT;
    }

    knamelen = sizeof(struct sockaddr);
    ret = getpeername(socket, &sa, &knamelen);

    if (ret == 0)
    {
        sockaddr_tomusl(&sa, &kname);
        if (unamelen > sizeof(struct musl_sockaddr))
        {
            unamelen = sizeof(struct musl_sockaddr);
        }
        lwp_put_to_user(name, &kname, unamelen);
        lwp_put_to_user(namelen, &unamelen, sizeof (socklen_t *));
    }
    else
    {
        ret = GET_ERRNO();
    }

    return ret;
}

sysret_t sys_getsockname(int socket, struct musl_sockaddr *name, socklen_t *namelen)
{
    int ret = -1;
    struct sockaddr sa;
    struct musl_sockaddr kname;
    socklen_t unamelen;
    socklen_t knamelen;

    if (!lwp_user_accessable(namelen, sizeof (socklen_t *)))
    {
        return -EFAULT;
    }
    lwp_get_from_user(&unamelen, namelen, sizeof (socklen_t *));
    if (!unamelen)
    {
        return -EINVAL;
    }

    if (!lwp_user_accessable(name, unamelen))
    {
        return -EFAULT;
    }

    knamelen = sizeof(struct sockaddr);
    ret = getsockname(socket, &sa, &knamelen);
    if (ret == 0)
    {
        sockaddr_tomusl(&sa, &kname);
        if (unamelen > sizeof(struct musl_sockaddr))
        {
            unamelen = sizeof(struct musl_sockaddr);
        }
        lwp_put_to_user(name, &kname, unamelen);
        lwp_put_to_user(namelen, &unamelen, sizeof(socklen_t *));
    }
    else
    {
        ret = GET_ERRNO();
    }
    return ret;
}

sysret_t sys_getsockopt(int socket, int level, int optname, void *optval, socklen_t *optlen)
{
    int ret;
    convert_sockopt(&level, &optname);
    ret = getsockopt(socket, level, optname, optval, optlen);

    return (ret < 0 ? GET_ERRNO() : ret);
}

sysret_t sys_setsockopt(int socket, int level, int optname, const void *optval, socklen_t optlen)
{
    int ret;
    convert_sockopt(&level, &optname);
    ret = setsockopt(socket, level, optname, optval, optlen);
    return (ret < 0 ? GET_ERRNO() : ret);
}

sysret_t sys_connect(int socket, const struct musl_sockaddr *name, socklen_t namelen)
{
    int ret;
    struct sockaddr sa;
    struct musl_sockaddr kname;

    if (!lwp_user_accessable((void *)name, namelen))
    {
        return -EFAULT;
    }

#ifdef SAL_USING_AF_UNIX
    if (name->sa_family  == AF_UNIX)
    {
        namelen = sizeof(struct sockaddr);
    }
#endif /* SAL_USING_AF_UNIX */

    lwp_get_from_user(&kname, (void *)name, namelen);

    sockaddr_tolwip(&kname, &sa);

    ret = connect(socket, &sa, namelen);
    return (ret < 0 ? GET_ERRNO() : ret);
}

sysret_t sys_listen(int socket, int backlog)
{
    return listen(socket, backlog);
}

#define MUSLC_MSG_OOB       0x0001
#define MUSLC_MSG_PEEK      0x0002
#define MUSLC_MSG_DONTWAIT  0x0040
#define MUSLC_MSG_WAITALL   0x0100
#define MUSLC_MSG_MORE      0x8000

static int netflags_muslc_2_lwip(int flags)
{
    int flgs = 0;

    if (flags & MUSLC_MSG_PEEK)
    {
        flgs |= MSG_PEEK;
    }
    if (flags & MUSLC_MSG_WAITALL)
    {
        flgs |= MSG_WAITALL;
    }
    if (flags & MUSLC_MSG_OOB)
    {
        flgs |= MSG_OOB;
    }
    if (flags & MUSLC_MSG_DONTWAIT)
    {
        flgs |= MSG_DONTWAIT;
    }
    if (flags & MUSLC_MSG_MORE)
    {
        flgs |= MSG_MORE;
    }
    return flgs;
}

sysret_t sys_recvfrom(int socket, void *mem, size_t len, int flags,
      struct musl_sockaddr *from, socklen_t *fromlen)
{
    int flgs = 0;
#ifdef ARCH_MM_MMU
    int ret = -1;
    void *kmem = RT_NULL;
#endif

    flgs = netflags_muslc_2_lwip(flags);
#ifdef ARCH_MM_MMU
    if (!len)
    {
        return -EINVAL;
    }

    if (!lwp_user_accessable((void *)mem, len))
    {
        return -EFAULT;
    }

    kmem = kmem_get(len);
    if (!kmem)
    {
        return -ENOMEM;
    }

    if (flags == 0x2)
    {
        flags = 0x1;
    }

    if (from)
    {
        struct sockaddr sa;

        ret = recvfrom(socket, kmem, len, flgs, &sa, fromlen);
        sockaddr_tomusl(&sa, from);
    }
    else
    {
        ret = recvfrom(socket, kmem, len, flgs, NULL, NULL);
    }

    if (ret > 0)
    {
        lwp_put_to_user(mem, kmem, len);
    }

    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kmem);

    return ret;
#else
    int ret = -1;
    if (from)
    {
        struct sockaddr sa = {0};

        ret = recvfrom(socket, mem, len, flgs, &sa, fromlen);
        sockaddr_tomusl(&sa, from);
    }
    else
    {
        ret = recvfrom(socket, mem, len, flags, NULL, NULL);
    }
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

sysret_t sys_recv(int socket, void *mem, size_t len, int flags)
{
    int flgs = 0;
    int ret;

    flgs = netflags_muslc_2_lwip(flags);
    ret = recvfrom(socket, mem, len, flgs, NULL, NULL);
    return (ret < 0 ? GET_ERRNO() : ret);
}

sysret_t sys_sendto(int socket, const void *dataptr, size_t size, int flags,
    const struct musl_sockaddr *to, socklen_t tolen)
{
    int flgs = 0;
#ifdef ARCH_MM_MMU
    int ret = -1;
    void *kmem = RT_NULL;
#endif

    flgs = netflags_muslc_2_lwip(flags);
#ifdef ARCH_MM_MMU
    if (!size)
    {
        return -EINVAL;
    }

    if (!lwp_user_accessable((void *)dataptr, size))
    {
        return -EFAULT;
    }

    kmem = kmem_get(size);
    if (!kmem)
    {
        return -ENOMEM;
    }

    lwp_get_from_user(kmem, (void *)dataptr, size);

    if (to)
    {
        struct sockaddr sa;
        sockaddr_tolwip(to, &sa);

        ret = sendto(socket, kmem, size, flgs, &sa, tolen);
    }
    else
    {
        ret = sendto(socket, kmem, size, flgs, NULL, tolen);
    }

    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kmem);

    return ret;
#else
    int ret;
    if (to)
    {
        struct sockaddr sa;
        sockaddr_tolwip(to, &sa);

        ret = sendto(socket, dataptr, size, flgs, &sa, tolen);
    }
    else
    {
        ret = sendto(socket, dataptr, size, flgs, NULL, tolen);
    }
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

sysret_t sys_send(int socket, const void *dataptr, size_t size, int flags)
{
    int ret;
    int flgs = 0;

    flgs = netflags_muslc_2_lwip(flags);
    ret = sendto(socket, dataptr, size, flgs, NULL, 0);
    return (ret < 0 ? GET_ERRNO() : ret);
}

sysret_t sys_socket(int domain, int type, int protocol)
{
    int fd = -1;
    int nonblock = 0;
    /* not support SOCK_CLOEXEC type */
    if (type & SOCK_CLOEXEC)
    {
        type &= ~SOCK_CLOEXEC;
    }
    if (type & SOCK_NONBLOCK)
    {
        nonblock = 1;
        type &= ~SOCK_NONBLOCK;
    }

    fd = socket(domain, type, protocol);
    if (fd < 0)
    {
        goto out;
    }
    if (nonblock)
    {
        fcntl(fd, F_SETFL, O_NONBLOCK);
    }

out:
    return (fd < 0 ? GET_ERRNO() : fd);
}

sysret_t sys_closesocket(int socket)
{
    return closesocket(socket);
}

#endif

rt_thread_t sys_thread_find(char *name)
{
    return rt_thread_find(name);
}

rt_tick_t sys_tick_get(void)
{
    return rt_tick_get();
}

sysret_t sys_thread_mdelay(rt_int32_t ms)
{
    return rt_thread_mdelay(ms);
}

struct k_sigaction {
    void (*handler)(int);
    unsigned long flags;
    void (*restorer)(void);
    unsigned mask[2];
};

sysret_t sys_sigaction(int sig, const struct k_sigaction *act,
                     struct k_sigaction *oact, size_t sigsetsize)
{
    int ret = -RT_EINVAL;
    struct lwp_sigaction kact, *pkact = RT_NULL;
    struct lwp_sigaction koact, *pkoact = RT_NULL;

    if (!sigsetsize)
    {
        SET_ERRNO(EINVAL);
        goto out;
    }
    if (sigsetsize > sizeof(lwp_sigset_t))
    {
        sigsetsize = sizeof(lwp_sigset_t);
    }
    if (!act && !oact)
    {
        SET_ERRNO(EINVAL);
        goto out;
    }
    if (oact)
    {
        if (!lwp_user_accessable((void *)oact, sizeof(*oact)))
        {
            SET_ERRNO(EFAULT);
            goto out;
        }
        pkoact = &koact;
    }
    if (act)
    {
        if (!lwp_user_accessable((void *)act, sizeof(*act)))
        {
            SET_ERRNO(EFAULT);
            goto out;
        }
        kact.sa_flags = act->flags;
        kact.__sa_handler._sa_handler = act->handler;
        memcpy(&kact.sa_mask, &act->mask, sigsetsize);
        kact.sa_restorer = act->restorer;
        pkact = &kact;
    }

    ret = lwp_sigaction(sig, pkact, pkoact, sigsetsize);
#ifdef ARCH_MM_MMU
    if (ret == 0 && oact)
    {
        lwp_put_to_user(&oact->handler, &pkoact->__sa_handler._sa_handler, sizeof(void (*)(int)));
        lwp_put_to_user(&oact->mask, &pkoact->sa_mask, sigsetsize);
        lwp_put_to_user(&oact->flags, &pkoact->sa_flags, sizeof(int));
        lwp_put_to_user(&oact->restorer, &pkoact->sa_restorer, sizeof(void (*)(void)));
    }
#endif /* ARCH_MM_MMU */
out:
    return (ret < 0 ? GET_ERRNO() : ret);
}

sysret_t sys_sigprocmask(int how, const sigset_t *sigset, sigset_t *oset, size_t size)
{
    int ret = -1;
    lwp_sigset_t *pnewset = RT_NULL, *poldset = RT_NULL;
#ifdef ARCH_MM_MMU
    lwp_sigset_t newset, oldset;
#endif /* ARCH_MM_MMU*/

    if (!size)
    {
        return -EINVAL;
    }
    if (!oset && !sigset)
    {
        return -EINVAL;
    }
    if (size > sizeof(lwp_sigset_t))
    {
        size = sizeof(lwp_sigset_t);
    }
    if (oset)
    {
#ifdef ARCH_MM_MMU
        if (!lwp_user_accessable((void *)oset, size))
        {
            return -EFAULT;
        }
        poldset = &oldset;
#else
        if (!lwp_user_accessable((void *)oset, size))
        {
            return -EFAULT;
        }
        poldset = (lwp_sigset_t *)oset;
#endif
    }
    if (sigset)
    {
#ifdef ARCH_MM_MMU
        if (!lwp_user_accessable((void *)sigset, size))
        {
            return -EFAULT;
        }
        lwp_get_from_user(&newset, (void *)sigset, size);
        pnewset = &newset;
#else
        if (!lwp_user_accessable((void *)sigset, size))
        {
            return -EFAULT;
        }
        pnewset = (lwp_sigset_t *)sigset;
#endif /* ARCH_MM_MMU */
    }
    ret = lwp_sigprocmask(how, pnewset, poldset);
#ifdef ARCH_MM_MMU
    if (ret < 0)
    {
        return ret;
    }
    if (oset)
    {
        lwp_put_to_user(oset, poldset, size);
    }
#endif /* ARCH_MM_MMU */
    return (ret < 0 ? -EFAULT: ret);
}

sysret_t sys_tkill(int tid, int sig)
{
#ifdef ARCH_MM_MMU
    rt_base_t level;
    rt_thread_t thread;
    int ret;

    level = rt_hw_interrupt_disable();
    thread = lwp_tid_get_thread(tid);
    ret =  lwp_thread_kill(thread, sig);
    rt_hw_interrupt_enable(level);
    return ret;
#else
    return lwp_thread_kill((rt_thread_t)tid, sig);
#endif
}

sysret_t sys_thread_sigprocmask(int how, const lwp_sigset_t *sigset, lwp_sigset_t *oset, size_t size)
{
    int ret = -1;
    lwp_sigset_t *pnewset = RT_NULL, *poldset = RT_NULL;
#ifdef ARCH_MM_MMU
    lwp_sigset_t newset, oldset;
#endif /* ARCH_MM_MMU */

    if (!size)
    {
        return -EINVAL;
    }
    if (!oset && !sigset)
    {
        return -EINVAL;
    }
    if (size != sizeof(lwp_sigset_t))
    {
        return -EINVAL;
    }
    if (oset)
    {
#ifdef ARCH_MM_MMU
        if (!lwp_user_accessable((void *)oset, size))
        {
            return -EFAULT;
        }
        poldset = &oldset;
#else
        if (!lwp_user_accessable((void *)oset, size))
        {
            return -EFAULT;
        }
        poldset = oset;
#endif
    }
    if (sigset)
    {
#ifdef ARCH_MM_MMU
        if (!lwp_user_accessable((void *)sigset, size))
        {
            return -EFAULT;
        }
        lwp_get_from_user(&newset, (void *)sigset, sizeof(lwp_sigset_t));
        pnewset = &newset;
#else
        if (!lwp_user_accessable((void *)sigset, size))
        {
            return -EFAULT;
        }
        pnewset = (lwp_sigset_t *)sigset;
#endif
    }
    ret = lwp_thread_sigprocmask(how, pnewset, poldset);
    if (ret < 0)
    {
        return ret;
    }
#ifdef ARCH_MM_MMU
    if (oset)
    {
        lwp_put_to_user(oset, poldset, sizeof(lwp_sigset_t));
    }
#endif
    return (ret < 0 ? -EFAULT: ret);
}

#ifndef ARCH_MM_MMU
sysret_t sys_lwp_sighandler_set(int sig, lwp_sighandler_t func)
{
    if (!lwp_user_accessable((void *)func, sizeof(lwp_sighandler_t)))
    {
        return -EFAULT;
    }

    lwp_sighandler_set(sig, func);
    return 0;
}

sysret_t sys_thread_sighandler_set(int sig, lwp_sighandler_t func)
{
    if (!lwp_user_accessable((void *)func, sizeof(lwp_sighandler_t)))
    {
        return -EFAULT;
    }

    lwp_thread_sighandler_set(sig, func);
    return 0;
}
#endif /* not defined ARCH_MM_MMU */

sysret_t sys_waitpid(int32_t pid, int *status, int options)
{
    int ret = -1;
#ifdef ARCH_MM_MMU
    if (!lwp_user_accessable((void *)status, sizeof(int)))
    {
        return -EFAULT;
    }
    else
    {
        ret = waitpid(pid, status, options);
    }
#else
    if (!lwp_user_accessable((void *)status, sizeof(int)))
    {
        return -EFAULT;
    }
    ret = waitpid(pid, status, options);
#endif
    return ret;
}

#if defined(RT_USING_SAL) && defined(SAL_USING_POSIX)
struct musl_addrinfo
{
    int ai_flags;
    int ai_family;
    int ai_socktype;
    int ai_protocol;
    socklen_t ai_addrlen;

    struct musl_sockaddr *ai_addr;
    char *ai_canonname;

    struct musl_addrinfo *ai_next;
};

sysret_t sys_getaddrinfo(const char *nodename,
        const char *servname,
        const struct musl_addrinfo *hints,
        struct musl_addrinfo *res)
{
    int ret = -1;
    struct addrinfo *k_res = NULL;
    char *k_nodename = NULL;
    char *k_servname = NULL;
    struct addrinfo *k_hints = NULL;
#ifdef ARCH_MM_MMU
    int err;
#endif

#ifdef ARCH_MM_MMU
    if (!lwp_user_accessable((void *)res, sizeof(*res)))
    {
        SET_ERRNO(EFAULT);
        goto exit;
    }
#endif
    if (nodename)
    {
#ifdef ARCH_MM_MMU
        lwp_user_strlen(nodename, &err);
        if (err)
        {
            SET_ERRNO(EFAULT);
            goto exit;
        }
#endif
        k_nodename = rt_strdup(nodename);
        if (!k_nodename)
        {
            SET_ERRNO(ENOMEM);
            goto exit;
        }
    }
    if (servname)
    {
#ifdef ARCH_MM_MMU
        lwp_user_strlen(servname, &err);
        if (err)
        {
            SET_ERRNO(EFAULT);
            goto exit;
        }
#endif
        k_servname = rt_strdup(servname);
        if (!k_servname)
        {
            SET_ERRNO(ENOMEM);
            goto exit;
        }
    }

    if (hints)
    {
#ifdef ARCH_MM_MMU
        if (!lwp_user_accessable((void *)hints, sizeof(*hints)))
        {
            SET_ERRNO(EFAULT);
            goto exit;
        }
#endif
        k_hints = (struct addrinfo *) rt_malloc(sizeof *hints);
        if (!k_hints)
        {
            SET_ERRNO(ENOMEM);
            goto exit;
        }

        rt_memset(k_hints, 0x0, sizeof(struct addrinfo));
        k_hints->ai_flags    = hints->ai_flags;
        k_hints->ai_family   = hints->ai_family;
        k_hints->ai_socktype = hints->ai_socktype;
        k_hints->ai_protocol = hints->ai_protocol;
        k_hints->ai_addrlen  = hints->ai_addrlen;
    }

    ret = sal_getaddrinfo(k_nodename, k_servname, k_hints, &k_res);
    if (ret == 0)
    {
        /* set sockaddr */
        sockaddr_tomusl(k_res->ai_addr, res->ai_addr);
        res->ai_addrlen = k_res->ai_addrlen;

        /* set up addrinfo */
        res->ai_family = k_res->ai_family;
        res->ai_flags  = k_res->ai_flags;
        res->ai_next = NULL;

        if (hints != NULL)
        {
            /* copy socktype & protocol from hints if specified */
            res->ai_socktype = hints->ai_socktype;
            res->ai_protocol = hints->ai_protocol;
        }

        sal_freeaddrinfo(k_res);
        k_res = NULL;
    }

exit:
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    if (k_nodename)
    {
        rt_free(k_nodename);
    }
    if (k_servname)
    {
        rt_free(k_servname);
    }
    if (k_hints)
    {
        rt_free(k_hints);
    }

    return ret;
}

#define HOSTENT_BUFSZ   512
sysret_t sys_gethostbyname2_r(const char *name, int af, struct hostent *ret,
        char *buf, size_t buflen,
        struct hostent **result, int *err)
{
    int ret_val = -1;
    int sal_ret = -1 , sal_err = -1;
    struct hostent sal_he;
    struct hostent *sal_result = NULL;
    char *sal_buf = NULL;
    char *k_name  = NULL;
    int a_err = 0;

#ifdef ARCH_MM_MMU
    if (!lwp_user_accessable((void *)err, sizeof(*err)))
    {
        SET_ERRNO(EFAULT);
        goto __exit;
    }

    if (!lwp_user_accessable((void *)result, sizeof(*result))
    || !lwp_user_accessable((void *)ret, sizeof(*ret))
    || !lwp_user_accessable((void *)buf, buflen))
    {
        /* not all arguments given */
        *err = EFAULT;
        SET_ERRNO(EFAULT);
        goto __exit;
    }

    lwp_user_strlen(name, &a_err);
    if (a_err)
    {
        *err = EFAULT;
        SET_ERRNO(EFAULT);
        goto __exit;
    }
#endif

    *result = ret;
    sal_buf = (char *)malloc(HOSTENT_BUFSZ);
    if (sal_buf == NULL)
    {
        SET_ERRNO(ENOMEM);
        goto __exit;
    }

    k_name = rt_strdup(name);
    if (k_name == NULL)
    {
        SET_ERRNO(ENOMEM);
        goto __exit;
    }

    /* get host by name in SAL */
    sal_ret = sal_gethostbyname_r(k_name, &sal_he, sal_buf, HOSTENT_BUFSZ, &sal_result, &sal_err);
    if (sal_ret == 0)
    {
        int index = 0, cnt = 0;
        char *ptr = buf;

        /* get counter */
        index = 0;
        while (sal_he.h_addr_list[index] != NULL)
        {
            index++;
        }
        cnt = index + 1;

        /* update user space hostent */
        ret->h_addrtype = sal_he.h_addrtype;
        ret->h_length   = sal_he.h_length;

        rt_strncpy(ptr, k_name, buflen - (ptr - buf));
        ret->h_name = ptr;
        ptr += rt_strlen(k_name);

        ret->h_addr_list = (char**)ptr;
        ptr += cnt * sizeof(char *);

        index = 0;
        while (sal_he.h_addr_list[index] != NULL)
        {
            ret->h_addr_list[index] = ptr;
            rt_memcpy(ptr, sal_he.h_addr_list[index], sal_he.h_length);

            ptr += sal_he.h_length;
            index++;
        }
        ret->h_addr_list[index] = NULL;
    }

    ret_val = 0;

__exit:
    if (ret_val < 0)
    {
        ret_val = GET_ERRNO();
    }

    /* release buffer */
    if (sal_buf)
    {
        free(sal_buf);
    }
    if (k_name)
    {
        free(k_name);
    }

    return ret_val;
}
#endif

char *sys_getcwd(char *buf, size_t size)
{
    if (!lwp_user_accessable((void *)buf, size))
    {
        return RT_NULL;
    }
    getcwd(buf, size);

    return (char *)strlen(buf);
}

sysret_t sys_chdir(const char *path)
{
#ifdef ARCH_MM_MMU
    int err = 0;

    lwp_user_strlen(path, &err);
    if (err)
    {
        return -EFAULT;
    }
    err = chdir(path);
    return (err < 0 ? GET_ERRNO() : err);
#else
    int ret = chdir(path);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

sysret_t sys_mkdir(const char *path, mode_t mode)
{
#ifdef ARCH_MM_MMU
    int err = 0;

    lwp_user_strlen(path, &err);
    if (err)
    {
        return -EFAULT;
    }
    err = mkdir(path, mode);
    return (err < 0 ? GET_ERRNO() : err);
#else
    int ret = mkdir(path, mode);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

sysret_t sys_rmdir(const char *path)
{
#ifdef ARCH_MM_MMU
    int err = 0;

    lwp_user_strlen(path, &err);
    if (err)
    {
        return -EFAULT;
    }
    err = rmdir(path);
    return (err < 0 ? GET_ERRNO() : err);
#else
    int ret = rmdir(path);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

#ifdef RT_USING_MUSL
typedef uint64_t ino_t;
#endif

struct libc_dirent {
    ino_t d_ino;
    off_t d_off;
    unsigned short d_reclen;
    unsigned char d_type;
    char d_name[256];
};

sysret_t sys_getdents(int fd, struct libc_dirent *dirp, size_t nbytes)
{
    int ret = -1;
    struct dfs_file *file;
    size_t cnt = (nbytes / sizeof(struct libc_dirent));
    size_t rtt_nbytes = 0;
    struct dirent *rtt_dirp;

#ifdef ARCH_MM_MMU
    if (!lwp_user_accessable((void *)dirp, sizeof(struct libc_dirent)))
    {
        return -EFAULT;
    }
#endif

    if (cnt == 0)
    {
        return -EINVAL;
    }
    rtt_nbytes = cnt * sizeof(struct dirent);
    rtt_dirp = (struct dirent *)rt_malloc(rtt_nbytes);
    if (!rtt_dirp)
    {
        return -ENOMEM;
    }
    file = fd_get(fd);
    ret = dfs_file_getdents(file, rtt_dirp, rtt_nbytes);
    if (ret > 0)
    {
        size_t i = 0;
        cnt = ret / sizeof(struct dirent);
        for (i = 0; i < cnt; i++)
        {
            dirp[i].d_ino = 0;
            dirp[i].d_off = i*sizeof(struct libc_dirent);
            dirp[i].d_type = rtt_dirp[i].d_type;
            dirp[i].d_reclen = sizeof(struct libc_dirent);
            strcpy(dirp[i].d_name, rtt_dirp[i].d_name);
        }
        ret = cnt * sizeof(struct libc_dirent);
    }

    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    rt_free(rtt_dirp);

    return ret;
}

sysret_t sys_get_errno(void)
{
    return rt_get_errno();
}

#ifdef ARCH_MM_MMU
sysret_t sys_set_thread_area(void *p)
{
    rt_thread_t thread;

    thread = rt_thread_self();
    thread->thread_idr = p;
    arch_set_thread_area(p);

    return 0;
}

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

sysret_t sys_gettid(void)
{
    return rt_thread_self()->tid;
}

sysret_t sys_access(const char *filename, int mode)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    rt_size_t len = 0;
    char *kname = RT_NULL;
    int a_err = 0;

    lwp_user_strlen(filename, &a_err);
    if (a_err)
    {
        return -EFAULT;
    }

    len = rt_strlen(filename);
    if (!len)
    {
        return -EINVAL;
    }

    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        return -ENOMEM;
    }

    lwp_get_from_user(kname, (void *)filename, len + 1);
    ret = access(kname, mode);
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kname);
    return ret;
#else
    ret = access(filename, mode);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

sysret_t sys_pipe(int fd[2])
{
    int ret;
    if (!lwp_user_accessable((void *)fd, sizeof(int[2])))
    {
        return -EFAULT;
    }
    ret = pipe(fd);
    return (ret < 0 ? GET_ERRNO() : ret);
}

sysret_t sys_clock_settime(clockid_t clk, const struct timespec *ts)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    size_t size = sizeof(struct timespec);
    struct timespec *kts = NULL;

    if (!lwp_user_accessable((void *)ts, size))
    {
        return -EFAULT;
    }

    kts = kmem_get(size);
    if (!kts)
    {
        return -ENOMEM;
    }

    lwp_get_from_user(kts, (void *)ts, size);
    ret = clock_settime(clk, kts);
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kts);

    return ret;
#else
    if (!lwp_user_accessable((void *)ts, sizeof(struct timespec)))
    {
        return -EFAULT;
    }
    ret = clock_settime(clk, ts);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

sysret_t sys_clock_gettime(clockid_t clk, struct timespec *ts)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    size_t size = sizeof(struct timespec);
    struct timespec *kts = NULL;

    if (!lwp_user_accessable((void *)ts, size))
    {
        return -EFAULT;
    }

    kts = kmem_get(size);
    if (!kts)
    {
        return -ENOMEM;
    }

    ret = clock_gettime(clk, kts);
    if (ret != -1)
        lwp_put_to_user(ts, kts, size);

    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kts);

    return ret;
#else
    if (!lwp_user_accessable((void *)ts, sizeof(struct timespec)))
    {
        return -EFAULT;
    }
    ret = clock_gettime(clk, ts);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

sysret_t sys_clock_nanosleep(clockid_t clk, int flags, const struct timespec *rqtp, struct timespec *rmtp)
{
    int ret = 0;
    dbg_log(DBG_LOG, "sys_nanosleep\n");
    if (!lwp_user_accessable((void *)rqtp, sizeof *rqtp))
        return -EFAULT;

#ifdef ARCH_MM_MMU
    struct timespec rqtp_k;
    struct timespec rmtp_k;

    lwp_get_from_user(&rqtp_k, (void *)rqtp, sizeof rqtp_k);
    ret = clock_nanosleep(clk, flags, &rqtp_k, &rmtp_k);
    if ((ret != -1 || rt_get_errno() == EINTR) && rmtp && lwp_user_accessable((void *)rmtp, sizeof *rmtp))
    {
        lwp_put_to_user(rmtp, (void *)&rmtp_k, sizeof rmtp_k);
                if(ret != 0)
            return -EINTR;
    }
#else
    if (rmtp)
    {
        if (!lwp_user_accessable((void *)rmtp, sizeof *rmtp))
            return -EFAULT;
        ret = clock_nanosleep(clk, flags, rqtp, rmtp);
    }
#endif
    return (ret < 0 ? GET_ERRNO() : ret);
}

sysret_t sys_clock_getres(clockid_t clk, struct timespec *ts)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    struct timespec kts;
    size_t size = sizeof(struct timespec);

    if (!lwp_user_accessable((void *)ts, size))
    {
        return -EFAULT;
    }

    ret = clock_getres(clk, &kts);

    if (ret != -1)
        lwp_put_to_user(ts, &kts, size);
#else
    if (!lwp_user_accessable((void *)ts, sizeof(struct timespec)))
    {
        return -EFAULT;
    }
    ret = clock_getres(clk, ts);
#endif
    return (ret < 0 ? GET_ERRNO() : ret);
}

sysret_t sys_rename(const char *oldpath, const char *newpath)
{
    int ret = -1;
#ifdef ARCH_MM_MMU
    int err;

    lwp_user_strlen(oldpath, &err);
    if (err)
    {
        return -EFAULT;
    }

    lwp_user_strlen(newpath, &err);
    if (err)
    {
        return -EFAULT;
    }
#endif
    ret = rename(oldpath, newpath);
    return (ret < 0 ? GET_ERRNO() : ret);
}

typedef unsigned long long rlim_t;

struct rlimit {
    rlim_t rlim_cur;
    rlim_t rlim_max;
};

#define RLIMIT_CPU     0
#define RLIMIT_FSIZE   1
#define RLIMIT_DATA    2
#define RLIMIT_STACK   3
#define RLIMIT_CORE    4
#define RLIMIT_RSS     5
#define RLIMIT_NPROC   6
#define RLIMIT_NOFILE  7
#define RLIMIT_MEMLOCK 8
#define RLIMIT_AS      9

sysret_t sys_prlimit64(pid_t pid,
        unsigned int resource,
        const struct rlimit *new_rlim,
        struct rlimit *old_rlim)
{
    return -ENOSYS;
}

sysret_t sys_getrlimit(unsigned int resource, unsigned long rlim[2])
{
    int ret = -1;

    if (!lwp_user_accessable((void *)rlim, sizeof(unsigned long [2])))
    {
        return -EFAULT;
    }
    switch (resource)
    {
    case RLIMIT_NOFILE:
        {
            struct dfs_fdtable *fdt = dfs_fdtable_get();

            dfs_file_lock();
            rlim[0] = fdt->maxfd;
            dfs_file_unlock();
            rlim[1] = DFS_FD_MAX;
            ret = 0;
        }
        break;
    default:
        return -EINVAL;
        break;
    }
    return (ret < 0 ? GET_ERRNO() : ret);
}

sysret_t sys_setrlimit(unsigned int resource, struct rlimit *rlim)
{
    return -ENOSYS;
}

sysret_t sys_setsid(void)
{
    int ret = 0;
    ret = setsid();
    return (ret < 0 ? GET_ERRNO() : ret);
}

sysret_t sys_getrandom(void *buf, size_t buflen, unsigned int flags)
{
    int ret = -1;
    int count = 0;
    void *kmem = RT_NULL;
    rt_device_t rd_dev = RT_NULL;

    if (flags & GRND_RANDOM)
        rd_dev = rt_device_find("random");
    else
        rd_dev = rt_device_find("urandom");

    if (rd_dev == RT_NULL)
    {
        return -EFAULT;
    }

    if (rt_device_open(rd_dev, RT_DEVICE_OFLAG_RDONLY) != RT_EOK)
    {
        return -EFAULT;
    }

    if (!lwp_user_accessable(buf, buflen))
    {
        rt_device_close(rd_dev);
        return -EFAULT;
    }

#ifdef ARCH_MM_MMU
    kmem = kmem_get(buflen);
    if (!kmem)
    {
        rt_device_close(rd_dev);
        return -ENOMEM;
    }

    while (count < buflen)
    {
        ret = rt_device_read(rd_dev, count, (char *)kmem + count, buflen - count);
        if (ret <= 0)
            break;
        count += ret;
    }
    rt_device_close(rd_dev);

    ret = count;
    if (count > 0)
    {
        ret = lwp_put_to_user(buf, kmem, count);
    }
    kmem_put(kmem);
#else
    while (count < buflen)
    {
        ret = rt_device_read(rd_dev, count, (char *)kmem + count, buflen - count);
        if (ret <= 0)
            break;
        count += ret;
    }
    rt_device_close(rd_dev);

    ret = count;
#endif
    return ret;
}

ssize_t sys_readlink(char* path, char *buf, size_t bufsz)
{
    size_t len, copy_len;
    int err, rtn;
    int fd = -1;
    struct dfs_file *d;
    char *copy_path;

    len = lwp_user_strlen(path, &err);
    if (err)
    {
        return -EFAULT;
    }

    if (!lwp_user_accessable(buf, bufsz))
    {
        return -EINVAL;
    }

    copy_path = (char*)rt_malloc(len + 1);
    if (!copy_path)
    {
        return -ENOMEM;
    }

    copy_len = lwp_get_from_user(copy_path, path, len);
    copy_path[copy_len] = '\0';

    /* musl __procfdname */
    err = sscanf(copy_path, "/proc/self/fd/%d", &fd);

    if (err != 1)
    {
        rtn = 0;
        if (access(copy_path, 0))
        {
            rtn = -ENOENT;
            LOG_E("readlink: path not is /proc/self/fd/* and path not exits, call by musl __procfdname()?");
        }
        else
        {
#ifdef RT_USING_DFS_V2
            char *link_fn = (char *)rt_malloc(DFS_PATH_MAX);
            if (link_fn)
            {
                err = dfs_file_readlink(copy_path, link_fn, DFS_PATH_MAX);
                if (err > 0)
                {
                    rtn = lwp_put_to_user(buf, link_fn, bufsz > err ? err : bufsz - 1);
                }
                else
                {
                    rtn = -EIO;
                }
                rt_free(link_fn);
            }
            else
            {
                rtn = -ENOMEM;
            }
#else
            rtn = lwp_put_to_user(buf, copy_path, copy_len);
#endif
        }
        rt_free(copy_path);
        return rtn;
    }
    else
    {
        rt_free(copy_path);
    }

    d = fd_get(fd);
    if (!d)
    {
        return -EBADF;
    }

    if (!d->vnode)
    {
        return -EBADF;
    }

#ifdef RT_USING_DFS_V2
    {
        char *fullpath = dfs_dentry_full_path(d->dentry);
        if (fullpath)
        {
            copy_len = strlen(fullpath);
            if (copy_len > bufsz)
            {
                copy_len = bufsz;
            }

            bufsz = lwp_put_to_user(buf, fullpath, copy_len);
            rt_free(fullpath);
        }
        else
        {
            bufsz = 0;
        }
    }
#else
    copy_len = strlen(d->vnode->fullpath);
    if (copy_len > bufsz)
    {
        copy_len = bufsz;
    }

    bufsz = lwp_put_to_user(buf, d->vnode->fullpath, copy_len);
#endif

    return bufsz;
}

sysret_t sys_setaffinity(pid_t pid, size_t size, void *set)
{
    if (!lwp_user_accessable(set, sizeof(cpu_set_t)))
    {
        return -EFAULT;
    }
    for (int i = 0;i < size * 8; i++)
    {
        if (CPU_ISSET(i, (cpu_set_t *)set))
        {
            return lwp_setaffinity(pid, i);
        }
    }
    return -1;
}

sysret_t sys_getaffinity(pid_t pid, size_t size, void *set)
{
#ifdef ARCH_MM_MMU
    cpu_set_t mask;
    struct rt_lwp *lwp;

    if (size <= 0 || size > sizeof(cpu_set_t))
    {
        return -EINVAL;
    }
    if (!lwp_user_accessable(set, size))
    {
        return -EFAULT;
    }

    if (pid == 0) lwp = lwp_self();
    else lwp = lwp_from_pid(pid);
    if (!lwp)
    {
        return -ESRCH;
    }

#ifdef RT_USING_SMP
    if (lwp->bind_cpu == RT_CPUS_NR)    /* not bind */
    {
        CPU_ZERO_S(size, &mask);
    }
    else /* set bind cpu */
    {
        /* TODO: only single-core bindings are now supported of rt-smart */
        CPU_SET_S(lwp->bind_cpu, size, &mask);
    }
#else
    CPU_SET_S(0, size, &mask);
#endif

    if (lwp_put_to_user(set, &mask, size) != size)
    {
        return -1;
    }

    return 0;
#else
    return -1;
#endif
}

sysret_t sys_sysinfo(void *info)
{
#ifdef ARCH_MM_MMU
    struct sysinfo kinfo = {0};
    rt_size_t total_pages = 0, free_pages = 0;

    if (!lwp_user_accessable(info, sizeof(struct sysinfo)))
    {
        return -EFAULT;
    }

    kinfo.uptime = rt_tick_get_millisecond() / 1000;
    /* TODO: 1, 5, and 15 minute load averages */
    kinfo.loads[0] = kinfo.loads[1] = kinfo.loads[2] = rt_object_get_length(RT_Object_Class_Thread);
    rt_page_get_info(&total_pages, &free_pages);
    kinfo.totalram = total_pages;
    kinfo.freeram = free_pages;

    /* TODO: implementation procfs, here is counter the lwp number */
    struct lwp_avl_struct *pids = lwp_get_pid_ary();
    for (int index = 0; index < RT_LWP_MAX_NR; index++)
    {
        struct rt_lwp *lwp = (struct rt_lwp *)pids[index].data;

        if (lwp)
        {
            kinfo.procs++;
        }
    }

    rt_page_high_get_info(&total_pages, &free_pages);
    kinfo.totalhigh = total_pages;
    kinfo.freehigh = free_pages;
    kinfo.mem_unit = ARCH_PAGE_SIZE;

    if (lwp_put_to_user(info, &kinfo, sizeof(struct sysinfo)) != sizeof(struct sysinfo))
    {
        return -EFAULT;
    }

    return 0;
#else
    return -1;
#endif
}

sysret_t sys_sched_setparam(pid_t pid, void *param)
{
    struct sched_param *sched_param = (struct sched_param *)param;
    struct rt_lwp *lwp = NULL;
    rt_thread_t main_thread;
    int ret = -1;
    if (!lwp_user_accessable(param, sizeof(struct sched_param)))
    {
        return -EFAULT;
    }
    if (pid > 0)
    {
        lwp = lwp_from_pid(pid);
    }
    else if (pid == 0)
    {
        lwp = lwp_self();
    }
    if (lwp)
    {
        main_thread = rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling);
        return rt_thread_control(main_thread, RT_THREAD_CTRL_CHANGE_PRIORITY, (void *)&sched_param->sched_priority);
    }
    return ret;
}

sysret_t sys_sched_getparam(pid_t pid, void *param)
{
    struct sched_param *sched_param = (struct sched_param *)param;
    struct rt_lwp *lwp = NULL;
    rt_thread_t main_thread;
    int ret = -1;
    if (!lwp_user_accessable(param, sizeof(struct sched_param)))
    {
        return -EFAULT;
    }
    if (pid > 0)
    {
        lwp = lwp_from_pid(pid);
    }
    else if (pid == 0)
    {
        lwp = lwp_self();
    }
    if (lwp)
    {
        main_thread = rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling);
        sched_param->sched_priority = main_thread->current_priority;
        ret = 0;
    }
    return ret;
}

sysret_t sys_sched_get_priority_max(int policy)
{
    if(policy < 0)
    {
        SET_ERRNO(EINVAL);
        return -rt_get_errno();
    }
    return RT_THREAD_PRIORITY_MAX;
}

sysret_t sys_sched_get_priority_min(int policy)
{
    if(policy < 0)
    {
        SET_ERRNO(EINVAL);
        return -rt_get_errno();
    }
    return 0;
}

sysret_t sys_sched_setscheduler(int tid, int policy, void *param)
{
    struct sched_param *sched_param = (struct sched_param *)param;
    rt_thread_t thread = lwp_tid_get_thread(tid);

    if (!lwp_user_accessable(param, sizeof(struct sched_param)))
    {
        return -EFAULT;
    }
    return rt_thread_control(thread, RT_THREAD_CTRL_CHANGE_PRIORITY, (void *)&sched_param->sched_priority);
    return 0;
}

sysret_t sys_sched_getscheduler(int tid, int *policy, void *param)
{
    struct sched_param *sched_param = (struct sched_param *)param;
    rt_thread_t thread = lwp_tid_get_thread(tid);
    if (!lwp_user_accessable(sched_param, sizeof(struct sched_param)))
    {
        return -EFAULT;
    }
    sched_param->sched_priority = thread->current_priority;
    *policy = 0;
    return 0;
}

sysret_t sys_fsync(int fd)
{
    int res = fsync(fd);
    if (res < 0)
        res = rt_get_errno();
    return res;
}

mqd_t sys_mq_open(const char *name, int flags, mode_t mode, struct mq_attr *attr)
{
    mqd_t mqdes;
    sysret_t ret = 0;
#ifdef ARCH_MM_MMU
    char *kname = RT_NULL;
    int a_err = 0;
    rt_size_t len = 0;
    struct mq_attr attr_k;

    lwp_user_strlen(name, &a_err);
    if (a_err)
        return (mqd_t)-EFAULT;
    len = rt_strlen(name);
    if (!len)
        return (mqd_t)-EINVAL;
    kname = (char *)kmem_get(len + 1);
    if (!kname)
        return (mqd_t)-ENOMEM;

    if (attr == NULL)
    {
        attr_k.mq_maxmsg = 10;
        attr_k.mq_msgsize = 8192;
        attr_k.mq_flags = 0;
        attr = &attr_k;
    }
    else
    {
        if (!lwp_get_from_user(&attr_k, (void *)attr, sizeof(struct mq_attr)))
            return -EINVAL;
    }

    lwp_get_from_user(kname, (void *)name, len + 1);
    mqdes = mq_open(kname, flags, mode, &attr_k);
    if (mqdes == -1)
    {
        ret = GET_ERRNO();
    }
    lwp_put_to_user(attr, &attr_k, sizeof(struct mq_attr));
    kmem_put(kname);
#else
    mqdes = mq_open(name, flags, mode, attr);
#endif
    if (mqdes == -1)
        return (mqd_t)ret;
    else
        return mqdes;
}

sysret_t sys_mq_unlink(const char *name)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    char *kname = RT_NULL;
    int a_err = 0;
    rt_size_t len = 0;

    lwp_user_strlen(name, &a_err);
    if (a_err)
        return -EFAULT;
    len = rt_strlen(name);
    if (!len)
        return -EINVAL;
    kname = (char *)kmem_get(len + 1);
    if (!kname)
        return -ENOMEM;

    lwp_get_from_user(kname, (void *)name, len + 1);
    ret = mq_unlink(kname);
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }
    kmem_put(kname);
    return ret;
#else
    ret = mq_unlink(name);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

sysret_t sys_mq_timedsend(mqd_t mqd, const char *msg, size_t len, unsigned prio, const struct timespec *at)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    char *kmsg = RT_NULL;
    int a_err = 0;
    struct timespec at_k;

    lwp_user_strlen(msg, &a_err);
    if (a_err)
        return -EFAULT;
    kmsg = (char *)kmem_get(len + 1);
    if (!kmsg)
        return -ENOMEM;

    lwp_get_from_user(&at_k, (void *)at, sizeof(struct timespec));
    lwp_get_from_user(kmsg, (void *)msg, len + 1);
    ret = mq_timedsend(mqd, kmsg, len, prio, &at_k);
    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kmsg);

    return ret;
#else
    ret = mq_timedsend(mqd, msg, len, prio, at);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

sysret_t sys_mq_timedreceive(mqd_t mqd, char *restrict msg, size_t len, unsigned *restrict prio, const struct timespec *restrict at)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    char *restrict kmsg = RT_NULL;
    int a_err = 0;

    struct timespec at_k;

    lwp_user_strlen(msg, &a_err);
    if (a_err)
        return -EFAULT;
    kmsg = (char *restrict)kmem_get(len + 1);
    if (!kmsg)
        return -ENOMEM;

    lwp_get_from_user(kmsg, (void *)msg, len + 1);
    if (at == RT_NULL)
    {
        ret = mq_timedreceive(mqd, kmsg, len, prio, RT_NULL);
    }
    else
    {
        if (!lwp_get_from_user(&at_k, (void *)at, sizeof(struct timespec)))
            return -EINVAL;
        ret = mq_timedreceive(mqd, kmsg, len, prio, &at_k);
    }

    if (ret > 0)
        lwp_put_to_user(msg, kmsg, len + 1);

    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kmsg);

    return ret;
#else
    ret = mq_timedreceive(mqd, msg, len, prio, at);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

sysret_t sys_mq_notify(mqd_t mqd, const struct sigevent *sev)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    struct sigevent sev_k;
    lwp_get_from_user(&sev_k, (void *)sev, sizeof(struct timespec));
    ret = mq_notify(mqd, &sev_k);
#else
    ret = mq_notify(mqd, sev);
#endif
    return (ret < 0 ? GET_ERRNO() : ret);
}

sysret_t sys_mq_getsetattr(mqd_t mqd, const struct mq_attr *restrict new, struct mq_attr *restrict old)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    size_t size = sizeof(struct mq_attr);
    struct mq_attr *restrict knew = NULL;
    struct mq_attr *restrict kold = NULL;

    if (new != RT_NULL)
    {
        if (!lwp_user_accessable((void *)new, size))
            return -EFAULT;
        knew = kmem_get(size);
        if (!knew)
            return -ENOMEM;
        lwp_get_from_user(knew, (void *)new, size);
    }

    if (!lwp_user_accessable((void *)old, size))
        return -EFAULT;
    kold = kmem_get(size);
    if (!kold)
        return -ENOMEM;

    lwp_get_from_user(kold, (void *)old, size);
    ret = mq_setattr(mqd, knew, kold);
    if (ret != -1)
        lwp_put_to_user(old, kold, size);

    if (ret < 0)
    {
        ret = GET_ERRNO();
    }

    kmem_put(kold);
    if (new != RT_NULL)
        kmem_put(knew);

    return ret;
#else
    ret = mq_setattr(mqd, new, old);
    return (ret < 0 ? GET_ERRNO() : ret);
#endif
}

sysret_t sys_mq_close(mqd_t mqd)
{
    int ret = 0;
#ifdef ARCH_MM_MMU
    ret = mq_close(mqd);
#else
    ret = mq_close(mqd);
#endif
    return (ret < 0 ? GET_ERRNO() : ret);
}

#define ICACHE (1<<0)
#define DCACHE (1<<1)
#define BCACHE (ICACHE|DCACHE)

rt_weak sysret_t sys_cacheflush(void *addr, int size, int cache)
{
    if (((size_t)addr < (size_t)addr + size) &&
        ((size_t)addr >= USER_VADDR_START) &&
        ((size_t)addr + size < USER_VADDR_TOP))
    {
        if ((cache & DCACHE))
        {
            rt_hw_cpu_dcache_clean_and_invalidate(addr, size);
        }

        if ((cache & ICACHE))
        {
            rt_hw_cpu_icache_invalidate(addr, size);
        }

        return 0;
    }
    return -EFAULT;
}

sysret_t sys_uname(struct utsname *uts)
{
    struct utsname utsbuff = {0};
    int ret = 0;
    const char *machine;

    if (!lwp_user_accessable((void *)uts, sizeof(struct utsname)))
    {
        return -EFAULT;
    }
    rt_strncpy(utsbuff.sysname, "RT-Thread", sizeof(utsbuff.sysname));
    utsbuff.nodename[0] = '\0';
    ret = rt_snprintf(utsbuff.release, sizeof(utsbuff.release), "%u.%u.%u",
                      RT_VERSION_MAJOR, RT_VERSION_MINOR, RT_VERSION_PATCH);
    if (ret < 0) {
        return -EIO;
    }
    ret = rt_snprintf(utsbuff.version, sizeof(utsbuff.version), "RT-Thread %u.%u.%u %s %s",
                      RT_VERSION_MAJOR, RT_VERSION_MINOR, RT_VERSION_PATCH, __DATE__, __TIME__);
    if (ret < 0) {
        return -EIO;
    }

    machine = rt_hw_cpu_arch();
    rt_strncpy(utsbuff.machine, machine, sizeof(utsbuff.machine));

    utsbuff.domainname[0] = '\0';
    lwp_put_to_user(uts, &utsbuff, sizeof utsbuff);
    return 0;
}

sysret_t sys_statfs(const char *path, struct statfs *buf)
{
    int ret = 0;
    int err;
    size_t len;
    size_t copy_len;
    char *copy_path;
    struct statfs statfsbuff = {0};

    if (!lwp_user_accessable((void *)buf, sizeof(struct statfs)))
    {
        return -EFAULT;
    }

    len = lwp_user_strlen(path, &err);
    if (err)
    {
        return -EFAULT;
    }

    copy_path = (char*)rt_malloc(len + 1);
    if (!copy_path)
    {
        return -ENOMEM;
    }

    copy_len = lwp_get_from_user(copy_path, (void*)path, len);
    if (copy_len == 0)
    {
        rt_free(copy_path);
        return -EFAULT;
    }
    copy_path[copy_len] = '\0';

    ret = _SYS_WRAP(statfs(copy_path, &statfsbuff));
    rt_free(copy_path);

    if (ret == 0)
    {
        lwp_put_to_user(buf, &statfsbuff, sizeof statfsbuff);
    }

    return ret;
}

sysret_t sys_statfs64(const char *path, size_t sz, struct statfs *buf)
{
    int ret = 0;
    int err;
    size_t len;
    size_t copy_len;
    char *copy_path;
    struct statfs statfsbuff = {0};

    if (!lwp_user_accessable((void *)buf, sizeof(struct statfs)))
    {
        return -EFAULT;
    }

    if (sz != sizeof(struct statfs)) {
        return -EINVAL;
    }

    len = lwp_user_strlen(path, &err);
    if (err)
    {
        return -EFAULT;
    }

    copy_path = (char*)rt_malloc(len + 1);
    if (!copy_path)
    {
        return -ENOMEM;
    }

    copy_len = lwp_get_from_user(copy_path, (void*)path, len);
    if (copy_len == 0)
    {
        rt_free(copy_path);
        return -EFAULT;
    }
    copy_path[copy_len] = '\0';

    ret = _SYS_WRAP(statfs(copy_path, &statfsbuff));
    rt_free(copy_path);

    if (ret == 0)
    {
        lwp_put_to_user(buf, &statfsbuff, sizeof statfsbuff);
    }

    return ret;
}

sysret_t sys_fstatfs(int fd, struct statfs *buf)
{
    int ret = 0;
    struct statfs statfsbuff = {0};

    if (!lwp_user_accessable((void *)buf, sizeof(struct statfs)))
    {
        return -EFAULT;
    }

    ret = _SYS_WRAP(fstatfs(fd, &statfsbuff));

    if (ret == 0)
    {
        lwp_put_to_user(buf, &statfsbuff, sizeof statfsbuff);
    }

    return ret;
}

sysret_t sys_fstatfs64(int fd, size_t sz, struct statfs *buf)
{
    int ret = 0;
    struct statfs statfsbuff = {0};

    if (!lwp_user_accessable((void *)buf, sizeof(struct statfs)))
    {
        return -EFAULT;
    }

    if (sz != sizeof(struct statfs)) {
        return -EINVAL;
    }

    ret = _SYS_WRAP(fstatfs(fd, &statfsbuff));

    if (ret == 0)
    {
        lwp_put_to_user(buf, &statfsbuff, sizeof statfsbuff);
    }

    return ret;
}

sysret_t sys_mount(char *source, char *target,
        char *filesystemtype,
        unsigned long mountflags, void *data)
{
    char *copy_source;
    char *copy_target;
    char *copy_filesystemtype;
    size_t len_source, copy_len_source;
    size_t len_target, copy_len_target;
    size_t len_filesystemtype, copy_len_filesystemtype;
    int err_source, err_target, err_filesystemtype;
    char *tmp = NULL;
    int ret = 0;

    len_source = lwp_user_strlen(source, &err_source);
    len_target = lwp_user_strlen(target, &err_target);
    len_filesystemtype = lwp_user_strlen(filesystemtype, &err_filesystemtype);
    if (err_source || err_target || err_filesystemtype)
    {
        return -EFAULT;
    }

    copy_source = (char*)rt_malloc(len_source + 1 + len_target + 1 + len_filesystemtype + 1);
    if (!copy_source)
    {
        return -ENOMEM;
    }
    copy_target = copy_source + len_source + 1;
    copy_filesystemtype = copy_target + len_target + 1;

    copy_len_source = lwp_get_from_user(copy_source, source, len_source);
    copy_source[copy_len_source] = '\0';
    copy_len_target = lwp_get_from_user(copy_target, target, len_target);
    copy_target[copy_len_target] = '\0';
    copy_len_filesystemtype = lwp_get_from_user(copy_filesystemtype, filesystemtype, len_filesystemtype);
    copy_filesystemtype[copy_len_filesystemtype] = '\0';

    if (strcmp(copy_filesystemtype, "nfs") == 0)
    {
        tmp = copy_source;
        copy_source = NULL;
    }
    if (strcmp(copy_filesystemtype, "tmp") == 0)
    {
        copy_source = NULL;
    }
    ret = dfs_mount(copy_source, copy_target, copy_filesystemtype, 0, tmp);
    rt_free(copy_source);

    return ret;
}

sysret_t sys_umount2(char *__special_file, int __flags)
{
    char *copy_special_file;
    size_t len_special_file, copy_len_special_file;
    int err_special_file;
    int ret = 0;

    len_special_file = lwp_user_strlen(__special_file, &err_special_file);
    if (err_special_file)
    {
        return -EFAULT;
    }

    copy_special_file = (char*)rt_malloc(len_special_file + 1);
    if (!copy_special_file)
    {
        return -ENOMEM;
    }

    copy_len_special_file = lwp_get_from_user(copy_special_file, __special_file, len_special_file);
    copy_special_file[copy_len_special_file] = '\0';

    ret = dfs_unmount(copy_special_file);
    rt_free(copy_special_file);

    return ret;
}

sysret_t sys_link(const char *existing, const char *new)
{
    int ret = -1;

#ifdef ARCH_MM_MMU
    int err;

    lwp_user_strlen(existing, &err);
    if (err)
    {
        return -EFAULT;
    }

    lwp_user_strlen(new, &err);
    if (err)
    {
        return -EFAULT;
    }
#endif
#ifdef RT_USING_DFS_V2
    ret = dfs_file_link(existing, new);
#else
    SET_ERRNO(EFAULT);
#endif
    return (ret < 0 ? GET_ERRNO() : ret);
}

sysret_t sys_symlink(const char *existing, const char *new)
{
    int ret = -1;

#ifdef ARCH_MM_MMU
    int err;

    lwp_user_strlen(existing, &err);
    if (err)
    {
        return -EFAULT;
    }

    lwp_user_strlen(new, &err);
    if (err)
    {
        return -EFAULT;
    }
#endif
#ifdef RT_USING_DFS_V2
    ret = dfs_file_symlink(existing, new);
#else
    SET_ERRNO(EFAULT);
#endif
    return (ret < 0 ? GET_ERRNO() : ret);
}

const static struct rt_syscall_def func_table[] =
{
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

    SYSCALL_SIGN(sys_notimpl),    //network,
    SYSCALL_SIGN(sys_notimpl),    //network,
    SYSCALL_SIGN(sys_notimpl),    //network,
    SYSCALL_SIGN(sys_notimpl),    //network,
    SYSCALL_SIGN(sys_notimpl),    //network, /* 90 */
    SYSCALL_SIGN(sys_notimpl),    //network,
    SYSCALL_SIGN(sys_notimpl),    //network,
    SYSCALL_SIGN(sys_notimpl),    //network,

#ifdef RT_USING_DFS
    SYSCALL_SIGN(sys_select),
#else
    SYSCALL_SIGN(sys_notimpl),
#endif

    SYSCALL_SIGN(sys_notimpl),    //SYSCALL_SIGN(sys_hw_interrupt_disable), /* 95 */
    SYSCALL_SIGN(sys_notimpl),    //SYSCALL_SIGN(sys_hw_interrupt_enable),

    SYSCALL_SIGN(sys_tick_get),
    SYSCALL_SIGN(sys_exit_group),

    SYSCALL_SIGN(sys_notimpl),    //rt_delayed_work_init,
    SYSCALL_SIGN(sys_notimpl),    //rt_work_submit,           /* 100 */
    SYSCALL_SIGN(sys_notimpl),    //rt_wqueue_wakeup,
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
    SYSCALL_USPACE(SYSCALL_SIGN(sys_clone)),           /* 130 */
    SYSCALL_USPACE(SYSCALL_SIGN(sys_futex)),
    SYSCALL_USPACE(SYSCALL_SIGN(sys_pmutex)),
    SYSCALL_SIGN(sys_dup),
    SYSCALL_SIGN(sys_dup2),
    SYSCALL_SIGN(sys_rename),         /* 135 */
    SYSCALL_USPACE(SYSCALL_SIGN(sys_fork)),
    SYSCALL_USPACE(SYSCALL_SIGN(sys_execve)),
    SYSCALL_USPACE(SYSCALL_SIGN(sys_vfork)),
    SYSCALL_SIGN(sys_gettid),
    SYSCALL_SIGN(sys_prlimit64),      /* 140 */
    SYSCALL_SIGN(sys_getrlimit),
    SYSCALL_SIGN(sys_setrlimit),
    SYSCALL_SIGN(sys_setsid),
    SYSCALL_SIGN(sys_getrandom),
    SYSCALL_SIGN(sys_readlink),    // SYSCALL_SIGN(sys_readlink)     /* 145 */
    SYSCALL_USPACE(SYSCALL_SIGN(sys_mremap)),
    SYSCALL_USPACE(SYSCALL_SIGN(sys_madvise)),
    SYSCALL_SIGN(sys_sched_setparam),
    SYSCALL_SIGN(sys_sched_getparam),
    SYSCALL_SIGN(sys_sched_get_priority_max),           /* 150 */
    SYSCALL_SIGN(sys_sched_get_priority_min),
    SYSCALL_SIGN(sys_sched_setscheduler),
    SYSCALL_SIGN(sys_sched_getscheduler),
    SYSCALL_SIGN(sys_setaffinity),
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
    SYSCALL_SIGN(sys_getaffinity),                      /* 180 */
    SYSCALL_SIGN(sys_sysinfo),
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
            name = (char*)func_table[number].name;
        }
    }

    // skip sys_
    return name;
}
