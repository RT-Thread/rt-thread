/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-06-10     Bernard      first version
 */

/* RT-Thread System call */
#include <rthw.h>
#include <board.h>

#include <lwp.h>
#ifdef RT_USING_USERSPACE
#include <lwp_user_mm.h>
#endif

#ifdef RT_USING_DFS
#include <dfs_poll.h>
#include <dfs_posix.h>
#include <dfs_select.h>
#endif

#if (defined(RT_USING_SAL) && defined(SAL_USING_POSIX))
#include <sys/socket.h>

#define SYSCALL_NET(f)      ((void*)(f))
#else
#define SYSCALL_NET(f)      ((void*)sys_notimpl)
#endif

#if defined(RT_USING_DFS) && defined(RT_USING_USERSPACE)
#define SYSCALL_USPACE(f)   ((void*)(f))
#else
#define SYSCALL_USPACE(f)   ((void*)sys_notimpl)
#endif

#define DBG_TAG    "SYSCALL"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_SAL
#include <netdev_ipaddr.h>
#include <netdev.h>

#include <sal_netdb.h>
#include <sal.h>
#endif /* RT_USING_SAL */

#include "lwp_ipc_internal.h"

#define ALLOC_KERNEL_STACK_SIZE 5120

struct musl_sockaddr
{
    uint16_t sa_family;
    char     sa_data[14];
};

extern void lwp_user_entry(void *args, const void *text, void *data, void *user_stack);
extern void set_user_context(void *stack);

void lwp_cleanup(struct rt_thread *tid);

#ifdef RT_USING_USERSPACE
static void *kmem_get(size_t size)
{
    return rt_malloc(size);
}

static void kmem_put(void *kptr)
{
    rt_free(kptr);
}
#endif

int sys_futex(int *uaddr, int op, int val, void *timeout, void *uaddr2, int val3);

/* The same socket option is defined differently in the user interfaces and the
 * implementation. The options should be converted in the kernel. */

/* socket levels */
#define INTF_SOL_SOCKET     1
#define IMPL_SOL_SOCKET     0xFFF

#define INTF_IPPROTO_IP     0
#define IMPL_IPPROTO_IP     0

#define INTF_IPPROTO_TCP    6
#define IMPL_IPPROTO_TCP    6

#define INTF_IPPROTO_IPV6   41
#define IMPL_IPPROTO_IPV6   41

/* SOL_SOCKET option names */
#define INTF_SO_BROADCAST   6
#define INTF_SO_KEEPALIVE   9
#define INTF_SO_REUSEADDR   2
#define INTF_SO_TYPE        3
#define INTF_SO_ERROR       4
#define INTF_SO_SNDTIMEO    21
#define INTF_SO_RCVTIMEO    20
#define INTF_SO_RCVBUF      8
#define INTF_SO_LINGER      13
#define INTF_SO_NO_CHECK    11
#define INTF_SO_ACCEPTCONN  30
#define INTF_SO_DONTROUTE   5
#define INTF_SO_OOBINLINE   10
#define INTF_SO_REUSEPORT   15
#define INTF_SO_SNDBUF      7
#define INTF_SO_SNDLOWAT    19
#define INTF_SO_RCVLOWAT    18

#define IMPL_SO_BROADCAST   0x0020
#define IMPL_SO_KEEPALIVE   0x0008
#define IMPL_SO_REUSEADDR   0x0004
#define IMPL_SO_TYPE        0x1008
#define IMPL_SO_ERROR       0x1007
#define IMPL_SO_SNDTIMEO    0x1005
#define IMPL_SO_RCVTIMEO    0x1006
#define IMPL_SO_RCVBUF      0x1002
#define IMPL_SO_LINGER      0x0080
#define IMPL_SO_NO_CHECK    0x100a
#define IMPL_SO_ACCEPTCONN  0x0002
#define IMPL_SO_DONTROUTE   0x0010
#define IMPL_SO_OOBINLINE   0x0100
#define IMPL_SO_REUSEPORT   0x0200
#define IMPL_SO_SNDBUF      0x1001
#define IMPL_SO_SNDLOWAT    0x1003
#define IMPL_SO_RCVLOWAT    0x1004

/* IPPROTO_IP option names */
#define INTF_IP_TTL 2
#define INTF_IP_TOS 1
#define INTF_IP_MULTICAST_TTL   33
#define INTF_IP_MULTICAST_IF    32
#define INTF_IP_MULTICAST_LOOP  34
#define INTF_IP_ADD_MEMBERSHIP  35
#define INTF_IP_DROP_MEMBERSHIP 36

#define IMPL_IP_TTL  2
#define IMPL_IP_TOS  1
#define IMPL_IP_MULTICAST_TTL   5
#define IMPL_IP_MULTICAST_IF    6
#define IMPL_IP_MULTICAST_LOOP  7
#define IMPL_IP_ADD_MEMBERSHIP  3
#define IMPL_IP_DROP_MEMBERSHIP 4

/* IPPROTO_TCP option names */
#define INTF_TCP_NODELAY    1
#define INTF_TCP_KEEPALIVE  9
#define INTF_TCP_KEEPIDLE   4
#define INTF_TCP_KEEPINTVL  5
#define INTF_TCP_KEEPCNT    6

#define IMPL_TCP_NODELAY    0x01
#define IMPL_TCP_KEEPALIVE  0x02
#define IMPL_TCP_KEEPIDLE   0x03
#define IMPL_TCP_KEEPINTVL  0x04
#define IMPL_TCP_KEEPCNT    0x05

/* IPPROTO_IPV6 option names */
#define INTF_IPV6_V6ONLY    26
#define IMPL_IPV6_V6ONLY    27

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

static void lwp_user_thread(void *parameter)
{
    rt_thread_t tid;
    uint32_t user_stack;
    struct rt_lwp *lwp;

    tid = rt_thread_self();
    lwp = lwp_self();

    user_stack = (uint32_t)tid->user_stack + tid->user_stack_size;
    user_stack &= ~7; //align 8
    set_user_context((void*)user_stack);

    lwp_user_entry(parameter, tid->user_entry, lwp->data_entry, RT_NULL);
}

/* thread/process */
void sys_exit(int value)
{
    rt_base_t level;
    rt_thread_t tid, main_thread;
    struct rt_lwp *lwp;

    LOG_D("thread/process exit.");

    tid = rt_thread_self();
    lwp = (struct rt_lwp*)tid->lwp;

    level = rt_hw_interrupt_disable();
    if (tid->clear_child_tid)
    {
        int t = 0;
        int *clear_child_tid = tid->clear_child_tid;

        tid->clear_child_tid = RT_NULL;
        lwp_put_to_user(clear_child_tid, &t, sizeof t);
        sys_futex(tid->clear_child_tid, FUTEX_WAKE, 1, RT_NULL, RT_NULL, 0);
    }
    main_thread = rt_list_entry(lwp->t_grp.prev, struct rt_thread, sibling);
    if (main_thread == tid)
    {
        lwp_terminate(lwp);
        lwp_wait_subthread_exit();
        lwp->lwp_ret = value;
    }

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
#ifdef RT_USING_USERSPACE
    void *kmem = RT_NULL;
    ssize_t ret = -1;

    if (!nbyte)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    if (!lwp_user_accessable((void*)buf, nbyte))
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    kmem = kmem_get(nbyte);
    if (!kmem)
    {
        rt_set_errno(ENOMEM);
        return -1;
    }

    ret = read(fd, kmem, nbyte);
    if (ret)
    {
        lwp_put_to_user(buf, kmem, ret);
    }

    kmem_put(kmem);
    return ret;
#else
    return read(fd, buf, nbyte);
#endif
}

/* syscall: "write" ret: "ssize_t" args: "int" "const void *" "size_t" */
ssize_t sys_write(int fd, const void *buf, size_t nbyte)
{
#ifdef RT_USING_USERSPACE
    void *kmem = RT_NULL;
    ssize_t ret = -1;

    if (!nbyte)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    if (!lwp_user_accessable((void*)buf, nbyte))
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    kmem = kmem_get(nbyte);
    if (!kmem)
    {
        rt_set_errno(ENOMEM);
        return -1;
    }

    lwp_get_from_user(kmem, (void *)buf, nbyte);
    ret = write(fd, kmem, nbyte);

    kmem_put(kmem);
    return ret;
#else
    return write(fd, buf, nbyte);
#endif
}

/* syscall: "lseek" ret: "off_t" args: "int" "off_t" "int" */
off_t sys_lseek(int fd, off_t offset, int whence)
{
    return lseek(fd, offset, whence);
}

/* syscall: "open" ret: "int" args: "const char *" "int" "..." */
int sys_open(const char *name, int flag, ...)
{
#ifdef RT_USING_USERSPACE
    int ret = -1;
    rt_size_t len = 0;
    char *kname = RT_NULL;

    if (!lwp_user_accessable((void*)name, 1))
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    len = rt_strlen(name);
    if (!len)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        rt_set_errno(ENOMEM);
        return -1;
    }

    lwp_get_from_user(kname, (void *)name, len + 1);
    ret = open(kname, flag, 0);

    kmem_put(kname);
    return ret;
#else
    return open(name, flag, 0);
#endif
}

/* syscall: "close" ret: "int" args: "int" */
int sys_close(int fd)
{
    return close(fd);
}

/* syscall: "ioctl" ret: "int" args: "int" "u_long" "..." */
int sys_ioctl(int fd, unsigned long cmd, void* data)
{
    return ioctl(fd, cmd, data);
}

int sys_fstat(int file, struct stat *buf)
{
#ifdef RT_USING_USERSPACE
    int ret = -1;
    struct stat statbuff;

    ret = fstat(file, &statbuff);
    lwp_put_to_user(buf, &statbuff, sizeof statbuff);
    return ret;
#else
    return fstat(file, buf);
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

int sys_poll(struct pollfd *fds, nfds_t nfds, int timeout)
{
    int ret = -1;
    int i = 0;
#ifdef RT_USING_USERSPACE
    struct pollfd *kfds = RT_NULL;

    if (!lwp_user_accessable((void*)fds, nfds * sizeof *fds))
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    kfds = (struct pollfd *)kmem_get(nfds * sizeof *kfds);
    if (!kfds)
    {
        rt_set_errno(ENOMEM);
        return -1;
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
    for (i = 0; i < nfds; i++)
    {
        musl2dfs_events(&fds->events);
    }
    ret = poll(fds, nfds, timeout);
    if (ret > 0)
    {
        for (i = 0; i < nfds; i++)
        {
            dfs2musl_events(&fds->revents);
        }
    }

    return ret;
#endif
}

int sys_select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
{
#ifdef RT_USING_USERSPACE
    int ret = -1;
    fd_set *kreadfds = RT_NULL, *kwritefds = RT_NULL, *kexceptfds = RT_NULL;

    if (readfds)
    {
        if (!lwp_user_accessable((void*)readfds, sizeof *readfds))
        {
            rt_set_errno(EINVAL);
            goto quit;
        }
        kreadfds = (fd_set *)kmem_get(sizeof *kreadfds);
        if (!kreadfds)
        {
            rt_set_errno(ENOMEM);
            goto quit;
        }
        lwp_get_from_user(kreadfds, readfds, sizeof *kreadfds);
    }
    if (writefds)
    {
        if (!lwp_user_accessable((void*)writefds, sizeof *writefds))
        {
            rt_set_errno(EINVAL);
            goto quit;
        }
        kwritefds = (fd_set *)kmem_get(sizeof *kwritefds);
        if (!kwritefds)
        {
            rt_set_errno(ENOMEM);
            goto quit;
        }
        lwp_get_from_user(kwritefds, writefds, sizeof *kwritefds);
    }
    if (exceptfds)
    {
        if (!lwp_user_accessable((void*)exceptfds, sizeof *exceptfds))
        {
            rt_set_errno(EINVAL);
            goto quit;
        }
        kexceptfds = (fd_set *)kmem_get(sizeof *kexceptfds);
        if (!kexceptfds)
        {
            rt_set_errno(EINVAL);
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
    return select(nfds, readfds, writefds, exceptfds, timeout);
#endif
}

int sys_unlink(const char *pathname)
{
#ifdef RT_USING_USERSPACE
    int ret = -1;
    rt_size_t len = 0;
    char *kname = RT_NULL;

    if (!lwp_user_accessable((void*)pathname, 1))
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    len = rt_strlen(pathname);
    if (!len)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        rt_set_errno(ENOMEM);
        return -1;
    }

    lwp_get_from_user(kname, (void *)pathname, len + 1);
    ret = unlink(kname);

    kmem_put(kname);
    return ret;
#else
    return unlink(pathname);
#endif
}

/* syscall: "nanosleep" ret: "int" args: "const struct timespec *" "struct timespec *" */
int sys_nanosleep(const struct timespec *rqtp, struct timespec *rmtp)
{
    rt_tick_t tick;
#ifdef RT_USING_USERSPACE
    struct timespec rqtp_k;
    struct timespec rmtp_k;

    dbg_log(DBG_LOG, "sys_nanosleep\n");

    if (!lwp_user_accessable((void*)rqtp, sizeof *rqtp))
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    lwp_get_from_user(&rqtp_k, (void *)rqtp, sizeof rqtp_k);

    tick = rqtp_k.tv_sec * RT_TICK_PER_SECOND + ((uint64_t)rqtp_k.tv_nsec * RT_TICK_PER_SECOND) / 1000000000;
    rt_thread_delay(tick);

    if (rmtp)
    {
        if (!lwp_user_accessable((void*)rmtp, sizeof *rmtp))
        {
            rt_set_errno(EINVAL);
            return -1;
        }

        tick = rt_tick_get() - tick;
        /* get the passed time */
        rmtp_k.tv_sec = tick / RT_TICK_PER_SECOND;
        rmtp_k.tv_nsec = (tick % RT_TICK_PER_SECOND) * (1000000000 / RT_TICK_PER_SECOND);

        lwp_put_to_user(rmtp, (void *)&rmtp_k, sizeof rmtp_k);
    }
#else
    dbg_log(DBG_LOG, "sys_nanosleep\n");

    tick = rqtp->tv_sec * RT_TICK_PER_SECOND + ((uint64_t)rqtp->tv_nsec * RT_TICK_PER_SECOND) / 1000000000;
    rt_thread_delay(tick);

    if (rmtp)
    {
        tick = rt_tick_get() - tick;
        /* get the passed time */
        rmtp->tv_sec = tick / RT_TICK_PER_SECOND;
        rmtp->tv_nsec = (tick % RT_TICK_PER_SECOND) * (1000000000 / RT_TICK_PER_SECOND);
    }
#endif

    return 0;
}

/* syscall: "gettimeofday" ret: "int" args: "struct timeval *" "struct timezone *" */
int sys_gettimeofday(struct timeval *tp, struct timezone *tzp)
{
    struct timeval t_k;

#ifdef RT_USING_USERSPACE
    if (tp)
    {
        if (!lwp_user_accessable((void*)tp, sizeof *tp))
        {
            rt_set_errno(EINVAL);
            return -1;
        }

        t_k.tv_sec = rt_tick_get() / RT_TICK_PER_SECOND;
        t_k.tv_usec = (rt_tick_get() % RT_TICK_PER_SECOND) * (1000000 / RT_TICK_PER_SECOND);

        lwp_put_to_user(tp, (void *)&t_k, sizeof t_k);
    }
#else
    if (tp)
    {
        tp->tv_sec = rt_tick_get() / RT_TICK_PER_SECOND;
        tp->tv_usec = (rt_tick_get() % RT_TICK_PER_SECOND) * (1000000 / RT_TICK_PER_SECOND);
    }
#endif

    return 0;
}

int sys_settimeofday(const struct timeval *tv, const struct timezone *tzp)
{
    return 0;
}

#ifdef RT_USING_GDBSERVER
int lwp_execve(char *filename, int debug, int argc, char **argv, char **envp);
#else
int lwp_execve(char *filename, int argc, char **argv, char **envp);
#endif

int sys_exec(char *filename, int argc, char **argv, char **envp)
{
#ifdef RT_USING_GDBSERVER
    return lwp_execve(filename, 0, argc, argv, envp);
#else
    return lwp_execve(filename, argc, argv, envp);
#endif
}

int sys_kill(int pid, int sig)
{
    return lwp_kill(pid, sig);
}

int sys_getpid(void)
{
    return lwp_getpid();
}

/* syscall: "getpriority" ret: "int" args: "int" "id_t" */
int sys_getpriority(int which, id_t who)
{
    if (which == PRIO_PROCESS)
    {
        rt_thread_t tid;

        tid = rt_thread_self();
        if (who == (id_t)tid || who == 0xff)
        {
            return tid->current_priority;
        }
    }

    return 0xff;
}

/* syscall: "setpriority" ret: "int" args: "int" "id_t" "int" */
int sys_setpriority(int which, id_t who, int prio)
{
    if (which == PRIO_PROCESS)
    {
        rt_thread_t tid;

        tid = rt_thread_self();
        if ((who == (id_t)tid || who == 0xff) && (prio >= 0 && prio < RT_THREAD_PRIORITY_MAX))
        {
            rt_thread_control(tid, RT_THREAD_CTRL_CHANGE_PRIORITY, &prio);
            return 0;
        }
    }

    return -1;
}

rt_sem_t sys_sem_create(const char *name, rt_uint32_t value, rt_uint8_t flag)
{
    return rt_sem_create(name, value, flag);
}

rt_err_t sys_sem_delete(rt_sem_t sem)
{
    return rt_sem_delete(sem);
}

rt_err_t sys_sem_take(rt_sem_t sem, rt_int32_t time)
{
    return rt_sem_take_interruptible(sem, time);
}

rt_err_t sys_sem_release(rt_sem_t sem)
{
    return rt_sem_release(sem);
}

rt_mutex_t sys_mutex_create(const char *name, rt_uint8_t flag)
{
    return rt_mutex_create(name, flag);
}

rt_err_t sys_mutex_delete(rt_mutex_t mutex)
{
    return rt_mutex_delete(mutex);
}

rt_err_t sys_mutex_take(rt_mutex_t mutex, rt_int32_t time)
{
    return rt_mutex_take_interruptible(mutex, time);
}

rt_err_t sys_mutex_release(rt_mutex_t mutex)
{
    return rt_mutex_release(mutex);
}

#ifdef RT_USING_USERSPACE
/* memory allocation */
extern int lwp_brk(void *addr);
int sys_brk(void *addr)
{
    return lwp_brk(addr);
}

extern void *lwp_mmap2(void *addr, size_t length, int prot,
        int flags, int fd, off_t pgoffset);
void *sys_mmap2(void *addr, size_t length, int prot,
        int flags, int fd, off_t pgoffset)
{
    return lwp_mmap2(addr, length, prot, flags, fd, pgoffset);
}

extern int lwp_munmap(void *addr);
int sys_munmap(void *addr, size_t length)
{
    return lwp_munmap(addr);
}
#endif

rt_event_t sys_event_create(const char *name, rt_uint8_t flag)
{
    return rt_event_create(name, flag);
}

rt_err_t sys_event_delete(rt_event_t event)
{
    return rt_event_delete(event);
}

rt_err_t sys_event_send(rt_event_t event, rt_uint32_t set)
{
    return rt_event_send(event, set);
}

rt_err_t sys_event_recv(rt_event_t   event,
                       rt_uint32_t  set,
                       rt_uint8_t   opt,
                       rt_int32_t   timeout,
                       rt_uint32_t *recved)
{
    return rt_event_recv(event, set, opt, timeout, recved);
}

rt_mailbox_t sys_mb_create(const char *name, rt_size_t size, rt_uint8_t flag)
{
    return rt_mb_create(name, size, flag);
}

rt_err_t sys_mb_delete(rt_mailbox_t mb)
{
    return rt_mb_delete(mb);
}

rt_err_t sys_mb_send(rt_mailbox_t mb, rt_uint32_t value)
{
    return rt_mb_send(mb, value);
}

rt_err_t sys_mb_send_wait(rt_mailbox_t mb,
                         rt_uint32_t  value,
                         rt_int32_t   timeout)
{
    return rt_mb_send_wait(mb, value, timeout);
}

rt_err_t sys_mb_recv(rt_mailbox_t mb, rt_uint32_t *value, rt_int32_t timeout)
{
    return rt_mb_recv(mb, (rt_ubase_t*)value, timeout);
}

rt_mq_t sys_mq_create(const char *name,
                     rt_size_t   msg_size,
                     rt_size_t   max_msgs,
                     rt_uint8_t  flag)
{
    return rt_mq_create(name, msg_size, max_msgs, flag);
}

rt_err_t sys_mq_delete(rt_mq_t mq)
{
    return rt_mq_delete(mq);
}

rt_err_t sys_mq_send(rt_mq_t mq, void *buffer, rt_size_t size)
{
    return rt_mq_send(mq, buffer, size);
}

rt_err_t sys_mq_urgent(rt_mq_t mq, void *buffer, rt_size_t size)
{
    return rt_mq_urgent(mq, buffer, size);
}

rt_err_t sys_mq_recv(rt_mq_t    mq,
                    void      *buffer,
                    rt_size_t  size,
                    rt_int32_t timeout)
{
    return rt_mq_recv(mq, buffer, size, timeout);
}

static void timer_timeout_callback(void *parameter)
{
    rt_sem_t sem = (rt_sem_t)parameter;
    rt_sem_release(sem);
}

rt_timer_t sys_timer_create(const char *name,
        void *data,
        rt_tick_t   time,
        rt_uint8_t  flag)
{
    return rt_timer_create(name, timer_timeout_callback, (void*)data, time, flag);
}

rt_err_t sys_timer_delete(rt_timer_t timer)
{
    return rt_timer_delete(timer);
}

rt_err_t sys_timer_start(rt_timer_t timer)
{
    return rt_timer_start(timer);
}

rt_err_t sys_timer_stop(rt_timer_t timer)
{
    return rt_timer_stop(timer);
}

rt_err_t sys_timer_control(rt_timer_t timer, int cmd, void *arg)
{
    return rt_timer_control(timer, cmd, arg);
}

#ifdef RT_USING_USERSPACE
void *lwp_map_user(struct rt_lwp *lwp, void *map_va, size_t map_size);
#endif

rt_thread_t sys_thread_create(void *arg[])
{
    rt_base_t level = 0;
    void *user_stack = 0;
    struct rt_lwp *lwp = 0;
    rt_thread_t thread = RT_NULL;
    int tid = 0;

    lwp = rt_thread_self()->lwp;
    lwp_ref_inc(lwp);
#ifdef RT_USING_USERSPACE
    user_stack  = lwp_map_user(lwp, 0, (size_t)arg[3]);
#else
    user_stack  = (void *)RT_KERNEL_MALLOC((uint32_t)arg[3]);
#endif
    if (!user_stack)
    {
        rt_set_errno(EINVAL);
        goto fail;
    }
    if ((tid = lwp_tid_get()) == 0)
    {
        rt_set_errno(ENOMEM);
        goto fail;
    }
    thread = rt_thread_create((const char*)arg[0],
            lwp_user_thread,
            (void*)arg[2],
            ALLOC_KERNEL_STACK_SIZE,
            (rt_uint8_t)(size_t)arg[4],
            (rt_uint32_t)arg[5]);
    if (!thread)
    {
        goto fail;
    }

    thread->cleanup = lwp_cleanup;
    thread->user_entry = (void (*)(void *))arg[1];
    thread->user_stack = (void *)user_stack;
    thread->user_stack_size = (uint32_t)arg[3];
    thread->lwp = (void*)lwp;
    thread->tid = tid;
    lwp_tid_set_thread(tid, thread);

    level = rt_hw_interrupt_disable();
    rt_list_insert_after(&lwp->t_grp, &thread->sibling);
    rt_hw_interrupt_enable(level);

    return thread;

fail:
    lwp_tid_put(tid);
#ifndef RT_USING_USERSPACE
    if (user_stack)
    {
        RT_KERNEL_FREE(user_stack);
    }
#endif
    if (lwp)
    {
        lwp_ref_dec(lwp);
    }
    return RT_NULL;
}

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
int lwp_set_thread_context(void *new_thread_stack, void *origin_thread_stack, void *user_stack, void **thread_sp, int tid);
long sys_clone(void *arg[])
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
        rt_set_errno(EINVAL);
        return -1;
    }

    flags = (unsigned long)(size_t)arg[0];
    if ((flags & (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_THREAD | CLONE_SYSVSEM))
            != (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_THREAD | CLONE_SYSVSEM))
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    user_stack = arg[1];
    new_tid = (int *)arg[2];
    tls = (void *)arg[3];

    if ((flags & CLONE_PARENT_SETTID) == CLONE_PARENT_SETTID)
    {
        if (!lwp_user_accessable(new_tid, sizeof(int)))
        {
            rt_set_errno(EINVAL);
            return -1;
        }
    }

    self = rt_thread_self();
    lwp = self->lwp;
    lwp_ref_inc(lwp);
    if (!user_stack)
    {
        rt_set_errno(EINVAL);
        goto fail;
    }
    if ((tid = lwp_tid_get()) == 0)
    {
        rt_set_errno(ENOMEM);
        goto fail;
    }
    thread = rt_thread_create((const char*)"pthread",
            RT_NULL,
            RT_NULL,
            ALLOC_KERNEL_STACK_SIZE,
            self->init_priority,
            self->init_tick);
    if (!thread)
    {
        goto fail;
    }

    thread->cleanup = lwp_cleanup;
    thread->user_entry = RT_NULL;
    thread->user_stack = RT_NULL;
    thread->user_stack_size = 0;
    thread->lwp = (void*)lwp;
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
        thread->clear_child_tid = (int*)arg[4];
    }

    level = rt_hw_interrupt_disable();
    rt_list_insert_after(&lwp->t_grp, &thread->sibling);
    rt_hw_interrupt_enable(level);

    /* copy origin stack */
    rt_memcpy(thread->stack_addr, self->stack_addr, ALLOC_KERNEL_STACK_SIZE);
    lwp_tid_set_thread(tid, thread);
    tid = lwp_set_thread_context((void*)((char*)thread->stack_addr + ALLOC_KERNEL_STACK_SIZE),
            (void*)((char*)self->stack_addr + ALLOC_KERNEL_STACK_SIZE), user_stack, &thread->sp, tid);
    if (tid)
    {
        rt_thread_startup(thread);
    }
    return (long)tid;

fail:
    lwp_tid_put(tid);
    if (lwp)
    {
        lwp_ref_dec(lwp);
    }
    return -1;
}

rt_err_t sys_thread_delete(rt_thread_t thread)
{
    return rt_thread_delete(thread);
}

rt_err_t sys_thread_startup(rt_thread_t thread)
{
    return rt_thread_startup(thread);
}

rt_thread_t sys_thread_self(void)
{
    return rt_thread_self();
}

/* sys channel */

int sys_channel_open(const char *name, int flags)
{
    return lwp_channel_open(FDT_TYPE_LWP, name, flags);
}

rt_err_t sys_channel_close(int fd)
{
    return lwp_channel_close(FDT_TYPE_LWP, fd);
}

rt_err_t sys_channel_send(int fd, rt_channel_msg_t data)
{
    return lwp_channel_send(FDT_TYPE_LWP, fd, data);
}

rt_err_t sys_channel_send_recv_timeout(int fd, rt_channel_msg_t data, rt_channel_msg_t data_ret, rt_int32_t time)
{
    return lwp_channel_send_recv_timeout(FDT_TYPE_LWP, fd, data, data_ret, time);
}

rt_err_t sys_channel_reply(int fd, rt_channel_msg_t data)
{
    return lwp_channel_reply(FDT_TYPE_LWP, fd, data);
}

rt_err_t sys_channel_recv_timeout(int fd, rt_channel_msg_t data, rt_int32_t time)
{
    return lwp_channel_recv_timeout(FDT_TYPE_LWP, fd, data, time);
}

/*****/

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

int sys_log(const char* log, int size)
{
    rt_device_t console = rt_console_get_device();

    if (console && __sys_log_enable) rt_device_write(console, -1, log, size);

    return 0;
}

int sys_stat(const char *file, struct stat *buf)
{
    return stat(file, buf);
}

int sys_notimpl(void)
{
    rt_set_errno(ENOSYS);
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

#ifdef RT_USING_USERSPACE
int sys_shmget(size_t key, size_t size, int create)
{
    return lwp_shmget(key, size, create);
}

int sys_shmrm(int id)
{
    return lwp_shmrm(id);
}

void* sys_shmat(int id, void* shm_vaddr)
{
    return lwp_shmat(id, shm_vaddr);
}

int sys_shmdt(void* shm_vaddr)
{
    return lwp_shmdt(shm_vaddr);
}
#endif

/* device interfaces */
rt_err_t sys_device_init(rt_device_t dev)
{
    return rt_device_init(dev);
}

rt_err_t sys_device_register(rt_device_t dev, const char *name, rt_uint16_t flags)
{
    return rt_device_register(dev, name, flags);
}

rt_err_t sys_device_control(rt_device_t dev, int cmd, void *arg)
{
    return rt_device_control(dev, cmd, arg);
}

rt_device_t sys_device_find(const char* name)
{
    return rt_device_find(name);
}

rt_err_t sys_device_open(rt_device_t dev, rt_uint16_t oflag)
{
    return rt_device_open(dev, oflag);
}

rt_err_t sys_device_close(rt_device_t dev)
{
    return rt_device_close(dev);
}

rt_size_t sys_device_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    return rt_device_read(dev, pos, buffer, size);
}

rt_size_t sys_device_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    return rt_device_write(dev, pos, buffer, size);
}

/* network interfaces */
int sys_accept(int socket, struct musl_sockaddr *addr, socklen_t *addrlen)
{
    int ret = -1;
    struct sockaddr ksa;
    struct musl_sockaddr kmusladdr;
    socklen_t uaddrlen;
    socklen_t kaddrlen;

    if (addr)
    {
        if (!lwp_user_accessable(addrlen, sizeof (socklen_t *)))
        {
            rt_set_errno(EINVAL);
            return -1;
        }
        lwp_get_from_user(&uaddrlen, addrlen, sizeof (socklen_t *));
        if (!uaddrlen)
        {
            rt_set_errno(EINVAL);
            return -1;
        }

        if (!lwp_user_accessable(addr, uaddrlen))
        {
            rt_set_errno(EINVAL);
            return -1;
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
            lwp_put_to_user(addrlen, &uaddrlen, sizeof (socklen_t *));
        }
    }
    return ret;
}

int sys_bind(int socket, const struct musl_sockaddr *name, socklen_t namelen)
{
    struct sockaddr sa;
    struct musl_sockaddr kname;

    if (!lwp_user_accessable((void*)name, namelen))
    {
        rt_set_errno(EINVAL);
        return -1;
    }
    lwp_get_from_user(&kname, (void*)name, namelen);

    sockaddr_tolwip(&kname, &sa);

    return bind(socket, &sa, namelen);
}

int sys_shutdown(int socket, int how)
{
    return shutdown(socket, how);
}

int sys_getpeername (int socket, struct musl_sockaddr *name, socklen_t *namelen)
{
    int ret = -1;
    struct sockaddr sa;
    struct musl_sockaddr kname;
    socklen_t unamelen;
    socklen_t knamelen;

    if (!lwp_user_accessable(namelen, sizeof (socklen_t *)))
    {
        rt_set_errno(EINVAL);
        return -1;
    }
    lwp_get_from_user(&unamelen, namelen, sizeof (socklen_t *));
    if (!unamelen)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    if (!lwp_user_accessable(name, unamelen))
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    knamelen = sizeof(struct sockaddr);
    ret = getpeername (socket, &sa, &knamelen);

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

    return ret;
}

int sys_getsockname (int socket, struct musl_sockaddr *name, socklen_t *namelen)
{
    int ret = -1;
    struct sockaddr sa;
    struct musl_sockaddr kname;
    socklen_t unamelen;
    socklen_t knamelen;

    if (!lwp_user_accessable(namelen, sizeof (socklen_t *)))
    {
        rt_set_errno(EINVAL);
        return -1;
    }
    lwp_get_from_user(&unamelen, namelen, sizeof (socklen_t *));
    if (!unamelen)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    if (!lwp_user_accessable(name, unamelen))
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    knamelen = sizeof(struct sockaddr);
    ret = getsockname (socket, &sa, &knamelen);
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
    return ret;
}

int sys_getsockopt (int socket, int level, int optname, void *optval, socklen_t *optlen)
{
    convert_sockopt(&level, &optname);
    return getsockopt (socket, level, optname, optval, optlen);
}

int sys_setsockopt (int socket, int level, int optname, const void *optval, socklen_t optlen)
{
    convert_sockopt(&level, &optname);
    return setsockopt (socket, level, optname, optval, optlen);
}

int sys_connect(int socket, const struct musl_sockaddr *name, socklen_t namelen)
{
    struct sockaddr sa;
    struct musl_sockaddr kname;

    if (!lwp_user_accessable((void*)name, namelen))
    {
        rt_set_errno(EINVAL);
        return -1;
    }
    lwp_get_from_user(&kname, (void*)name, namelen);

    sockaddr_tolwip(&kname, &sa);

    return connect(socket, &sa, namelen);
}

int sys_listen(int socket, int backlog)
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
        flgs |= MSG_PEEK;
    if (flags & MUSLC_MSG_WAITALL)
        flgs |= MSG_WAITALL;
    if (flags & MUSLC_MSG_OOB)
        flgs |= MSG_OOB;
    if (flags & MUSLC_MSG_DONTWAIT)
        flgs |= MSG_DONTWAIT;
    if (flags & MUSLC_MSG_MORE)
        flgs |= MSG_MORE;
    return flgs;
}

int sys_recvfrom(int socket, void *mem, size_t len, int flags,
      struct musl_sockaddr *from, socklen_t *fromlen)
{
    int flgs = 0;
#ifdef RT_USING_USERSPACE
    int ret = -1;
    void *kmem = RT_NULL;
#endif

    flgs = netflags_muslc_2_lwip(flags);
#ifdef RT_USING_USERSPACE
    if (!len)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    if (!lwp_user_accessable((void*)mem, len))
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    kmem = kmem_get(len);
    if (!kmem)
    {
        rt_set_errno(ENOMEM);
        return -1;
    }

    if (flags == 0x2) {
        flags = 0x1;
    }

    if (from)
    {
        struct sockaddr sa;

        ret = recvfrom(socket, kmem, len, flgs, &sa, fromlen);
        sockaddr_tomusl(&sa, from);
    } else
        ret = recvfrom(socket, kmem, len, flgs, NULL, NULL);

    if (ret > 0)
        lwp_put_to_user(mem, kmem, len);

    kmem_put(kmem);
    return ret;
#else
    if (from)
    {
        int ret = -1;
        struct sockaddr sa = {0};

        ret = recvfrom(socket, mem, len, flgs, &sa, fromlen);
        sockaddr_tomusl(&sa, from);
        return ret;
    }

    return recvfrom(socket, mem, len, flags, NULL, NULL);
#endif
}

int sys_recv(int socket, void *mem, size_t len, int flags)
{
    int flgs = 0;

    flgs = netflags_muslc_2_lwip(flags);
    return recvfrom(socket, mem, len, flgs, NULL, NULL);
}

int sys_sendto(int socket, const void *dataptr, size_t size, int flags,
    const struct musl_sockaddr *to, socklen_t tolen)
{
    int flgs = 0;
#ifdef RT_USING_USERSPACE
    int ret = -1;
    void *kmem = RT_NULL;
#endif

    flgs = netflags_muslc_2_lwip(flags);
#ifdef RT_USING_USERSPACE
    if (!size)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    if (!lwp_user_accessable((void*)dataptr, size))
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    kmem = kmem_get(size);
    if (!kmem)
    {
        rt_set_errno(ENOMEM);
        return -1;
    }

    lwp_get_from_user(kmem, (void *)dataptr, size);

    if (to)
    {
        struct sockaddr sa;
        sockaddr_tolwip(to, &sa);

        ret = sendto(socket, kmem, size, flgs, &sa, tolen);
    }
    else
        ret = sendto(socket, kmem, size, flgs, NULL, tolen);

    kmem_put(kmem);
    return ret;
#else
    if (to)
    {
        struct sockaddr sa;
        sockaddr_tolwip(to, &sa);

        return sendto(socket, dataptr, size, flgs, &sa, tolen);
    }
    return sendto(socket, dataptr, size, flgs, NULL, tolen);
#endif
}

int sys_send(int socket, const void *dataptr, size_t size, int flags)
{
    int flgs = 0;

    flgs = netflags_muslc_2_lwip(flags);
    return sendto(socket, dataptr, size, flgs, NULL, 0);
}

int sys_socket(int domain, int type, int protocol)
{
    int fd = -1;
    int nonblock = 0;
    /* not support SOCK_CLOEXEC type */
    if (type & SOCK_CLOEXEC) type &= ~SOCK_CLOEXEC;
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
    return fd;
}

int sys_closesocket(int socket)
{
    return closesocket(socket);
}

rt_thread_t sys_thread_find(char *name)
{
    return rt_thread_find(name);
}

rt_tick_t sys_tick_get(void)
{
    return rt_tick_get();
}

rt_err_t sys_thread_mdelay(rt_int32_t ms)
{
    return rt_thread_mdelay(ms);
}

int sys_sigaction(int sig, const struct sigaction *act,
                     struct sigaction *oact, size_t sigsetsize)
{
    int ret = -RT_EINVAL;
    struct lwp_sigaction kact, *pkact = RT_NULL;
    struct lwp_sigaction koact, *pkoact = RT_NULL;

    if (!sigsetsize)
    {
        rt_set_errno(EINVAL);
        goto out;
    }
    if (sigsetsize > sizeof(lwp_sigset_t))
    {
        sigsetsize = sizeof(lwp_sigset_t);
    }
    if (!act && !oact)
    {
        rt_set_errno(EINVAL);
        goto out;
    }
    if (oact)
    {
        if (!lwp_user_accessable((void*)oact, sigsetsize))
        {
            rt_set_errno(EINVAL);
            goto out;
        }
        pkoact = &koact;
    }
    if (act)
    {
        if (!lwp_user_accessable((void*)act, sigsetsize))
        {
            rt_set_errno(EINVAL);
            goto out;
        }
        kact.__sa_handler._sa_handler = act->sa_handler;
        memcpy(&kact.sa_mask, &act->sa_mask, sigsetsize);
        pkact = &kact;
    }

    ret = lwp_sigaction(sig, pkact, pkoact, sigsetsize);
    if (ret == 0)
    {
        lwp_put_to_user(&oact->sa_handler, &pkoact->__sa_handler._sa_handler, sizeof(void (*)(int)));
        lwp_put_to_user(&oact->sa_mask, &pkoact->sa_mask, sigsetsize);
        lwp_put_to_user(&oact->sa_flags, &pkoact->sa_flags, sizeof(int));
        lwp_put_to_user(&oact->sa_restorer, &pkoact->sa_restorer, sizeof(void (*)(void)));
    }
out:
    return ret;
}

int sys_sigprocmask(int how, const sigset_t *sigset, sigset_t *oset, size_t size)
{
    int ret = -1;
    lwp_sigset_t newset, *pnewset = RT_NULL;
    lwp_sigset_t oldset, *poldset = RT_NULL;

    if (!size)
    {
        rt_set_errno(EINVAL);
        return ret;
    }
    if (!oset && !sigset)
    {
        rt_set_errno(EINVAL);
        return ret;
    }
    if (size > sizeof(lwp_sigset_t))
    {
        size = sizeof(lwp_sigset_t);
    }
    if (oset)
    {
        if (!lwp_user_accessable((void*)oset, size))
        {
            rt_set_errno(EINVAL);
            return ret;
        }
        poldset = &oldset;
    }
    if (sigset)
    {
        if (!lwp_user_accessable((void*)sigset, size))
        {
            rt_set_errno(EINVAL);
            return ret;
        }
        lwp_get_from_user(&newset, (void*)sigset, size);
        pnewset = &newset;
    }
    ret = lwp_sigprocmask(how, pnewset, poldset);
    if (ret < 0)
    {
        return ret;
    }
    if (oset)
    {
        lwp_put_to_user(oset, poldset, size);
    }
    return ret;
}


int sys_tkill(int tid, int sig)
{
    rt_thread_t thread = RT_NULL;

    if (tid <= 0)
    {
        rt_set_errno(EINVAL);
        return -RT_EINVAL;
    }
    thread = lwp_tid_get_thread(tid);
    return lwp_thread_kill(thread, sig);
}

int sys_thread_sigprocmask(int how, const lwp_sigset_t *sigset, lwp_sigset_t *oset, size_t size)
{
    int ret = -1;
    lwp_sigset_t newset, *pnewset = RT_NULL;
    lwp_sigset_t oldset, *poldset = RT_NULL;

    if (!size)
    {
        rt_set_errno(EINVAL);
        return ret;
    }
    if (!oset && !sigset)
    {
        rt_set_errno(EINVAL);
        return ret;
    }
    if (size != sizeof(lwp_sigset_t))
    {
        rt_set_errno(EINVAL);
        return ret;
    }
    if (oset)
    {
        if (!lwp_user_accessable((void*)oset, size))
        {
            rt_set_errno(EINVAL);
            return ret;
        }
        poldset = &oldset;
    }
    if (sigset)
    {
        if (!lwp_user_accessable((void*)sigset, size))
        {
            rt_set_errno(EINVAL);
            return ret;
        }
        lwp_get_from_user(&newset, (void*)sigset, sizeof(lwp_sigset_t));
        pnewset = &newset;
    }
    ret = lwp_thread_sigprocmask(how, pnewset, poldset);
    if (ret < 0)
    {
        return ret;
    }
    if (oset)
    {
        lwp_put_to_user(oset, poldset, sizeof(lwp_sigset_t));
    }
    return ret;
}

int32_t sys_waitpid(int32_t pid, int *status, int options)
{
    return waitpid(pid, status, options);
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

int sys_getaddrinfo(const char *nodename, const char *servname, const struct musl_addrinfo *hints, struct musl_addrinfo *res)
{
    int ret = -1;
    struct addrinfo *k_res = NULL;
    char *k_nodename = NULL;
    char *k_servname = NULL;
    struct addrinfo *k_hints = NULL;

    if (nodename)
    {
        k_nodename = rt_strdup(nodename);
        if (!k_nodename)
        {
            rt_set_errno(ENOMEM);
            goto exit;
        }
    }
    if (servname)
    {
        k_servname = rt_strdup(servname);
        if (!k_servname)
        {
            rt_set_errno(ENOMEM);
            goto exit;
        }
    }

    if (hints)
    {
        k_hints = (struct addrinfo*) rt_malloc(sizeof *hints);
        if (!k_hints)
        {
            rt_set_errno(ENOMEM);
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
int sys_gethostbyname2_r(const char *name, int af, struct hostent *ret,
        char *buf, size_t buflen,
        struct hostent **result, int *err)
{
    int ret_val = -1;
    int sal_ret = -1 , sal_err = -1;
    struct hostent sal_he;
    struct hostent *sal_result = NULL;
    char *sal_buf = NULL;
    char *k_name  = NULL;

    if (result == NULL)
    {
        /* not all arguments given */
        *err = EINVAL;
        rt_set_errno(EINVAL);
        goto __exit;
    }
    if ((name == NULL) || (ret == NULL) || (buf == NULL))
    {
        /* not all arguments given */
        *err = EINVAL;
        rt_set_errno(EINVAL);
        goto __exit;
    }

    *result = ret;
    sal_buf = (char *)malloc (HOSTENT_BUFSZ);
    if (sal_buf == NULL)
    {
        rt_set_errno(ENOMEM);
        goto __exit;
    }

    k_name = rt_strdup(name);
    if (k_name == NULL)
    {
        rt_set_errno(ENOMEM);
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
            index ++;
        }
        cnt = index + 1;

        /* update user space hostent */
        ret->h_addrtype = sal_he.h_addrtype;
        ret->h_length   = sal_he.h_length;

        rt_strncpy(ptr, k_name, buflen - (ptr - buf));
        ret->h_name = ptr;
        ptr += rt_strlen(k_name);

        ret->h_addr_list = (char**)ptr;
        ptr += cnt * sizeof(char*);

        index = 0;
        while (sal_he.h_addr_list[index] != NULL)
        {
            ret->h_addr_list[index] = ptr;
            rt_memcpy(ptr, sal_he.h_addr_list[index], sal_he.h_length);

            ptr += sal_he.h_length;
            index ++;
        }
        ret->h_addr_list[index] = NULL;
    }

    ret_val = 0;

__exit:
    /* release buffer */
    if (sal_buf) free(sal_buf);
    if (k_name) free(k_name);

    return ret_val;
}
#endif

char *sys_getcwd(char *buf, size_t size)
{
    return getcwd(buf, size);
}

int sys_chdir(const char *path)
{
    return chdir(path);
}

int sys_mkdir(const char *path, mode_t mode)
{
    return mkdir(path, mode);
}

int sys_rmdir(const char *path)
{
    return unlink(path);
}

typedef uint64_t ino_t;
struct libc_dirent {
    ino_t d_ino;
    off_t d_off;
    unsigned short d_reclen;
    unsigned char d_type;
    char d_name[256];
};
int sys_getdents(int fd, struct libc_dirent *dirp, size_t nbytes)
{
    int ret = -1;
    struct dfs_fd *dfs_fd;
    size_t cnt = (nbytes / sizeof(struct libc_dirent));
    size_t rtt_nbytes = 0;
    struct dirent *rtt_dirp;

    if (cnt == 0)
    {
        rt_set_errno(EINVAL);
        return -1;
    }
    rtt_nbytes = cnt * sizeof(struct dirent);
    rtt_dirp = (struct dirent*)rt_malloc(rtt_nbytes);
    if (!rtt_dirp)
    {
        rt_set_errno(ENOMEM);
        return -1;
    }
    dfs_fd = fd_get(fd);
    ret = dfs_file_getdents(dfs_fd, rtt_dirp, nbytes);
    if (ret)
    {
        size_t i = 0;
        cnt = ret / sizeof(struct dirent);
        for (i = 0; i < cnt; i++)
        {
            dirp[i].d_ino = 0;
            dirp[i].d_off = 0;
            dirp[i].d_type = rtt_dirp[i].d_type;
            dirp[i].d_reclen = sizeof(struct libc_dirent);
            strcpy(dirp[i].d_name, rtt_dirp[i].d_name);
        }
        ret = cnt * sizeof(struct libc_dirent);
    }
    rt_free(rtt_dirp);
    return ret;
}

rt_err_t sys_get_errno(void)
{
    return rt_get_errno();
}

int sys_set_thread_area(void *p)
{
    rt_thread_t thread;

    thread = rt_thread_self();
    thread->thread_idr = p;
    lwp_set_thread_area(p);

    return 0;
}

int sys_set_tid_address(int *tidptr)
{
    rt_thread_t thread = rt_thread_self();

    thread->clear_child_tid = tidptr;
    return thread->tid;
}

int sys_access(const char *filename, int mode)
{
    int ret = -1;
#ifdef RT_USING_USERSPACE
    rt_size_t len = 0;
    char *kname = RT_NULL;

    if (!lwp_user_accessable((void*)filename, 1))
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    len = rt_strlen(filename);
    if (!len)
    {
        rt_set_errno(EINVAL);
        return -1;
    }

    kname = (char *)kmem_get(len + 1);
    if (!kname)
    {
        rt_set_errno(ENOMEM);
        return -1;
    }

    lwp_get_from_user(kname, (void *)filename, len + 1);
    ret = open(kname, mode, 0);
    kmem_put(kname);
#else
    ret = open(filename, mode, 0);
#endif
    if (ret >= 0)
    {
        close(ret);
    }

    return (ret >= 0)? 0: ret;
}

int sys_pipe(int fd[2])
{
    return pipe(fd);
}

int sys_clock_settime(clockid_t clk, const struct timespec *ts)
{
    rt_device_t device;
    time_t now;

    device = rt_device_find("rtc");
    if (device == RT_NULL)
    {
        return -ENODEV;
    }

#ifdef RT_USING_USERSPACE
    size_t size = sizeof(struct timespec);
    struct timespec *kts = NULL;

    if (!lwp_user_accessable((void*)ts, size))
        return -EINVAL;

    kts = kmem_get(size);
    if (!kts)
        return -ENOMEM;

    lwp_get_from_user(kts, (void *)ts, size);
    now = kts->tv_sec;

    kmem_put(kts);
#else
    now = ts->tv_sec;
#endif
    return rt_device_control(device, RT_DEVICE_CTRL_RTC_SET_TIME, &now);
}

int sys_clock_gettime(clockid_t clk, struct timespec *ts)
{
    int ret = 0;
    rt_device_t device;
    time_t now;

    device = rt_device_find("rtc");
    if (device == RT_NULL)
    {
        return -ENODEV;
    }
    ret = rt_device_control(device, RT_DEVICE_CTRL_RTC_GET_TIME, &now);

#ifdef RT_USING_USERSPACE
    size_t size = sizeof(struct timespec);
    struct timespec *kts = NULL;

    if (!lwp_user_accessable((void*)ts, size))
        return -EINVAL;

    kts = kmem_get(size);
    if (!kts)
        return -ENOMEM;

    kts->tv_sec = now;
    kts->tv_nsec = 0;
    lwp_put_to_user(ts, kts, size);

    kmem_put(kts);
#else
    ts->tv_sec = now;
    ts->tv_nsec = 0;
#endif
    return ret;
}

int sys_clock_getres(clockid_t clk, struct timespec *ts)
{
#ifdef RT_USING_USERSPACE
    struct timespec kts;
    size_t size = sizeof(struct timespec);

    if (!lwp_user_accessable((void*)ts, size))
        return -EINVAL;

    kts.tv_sec = 1;
    kts.tv_nsec = 0;
    lwp_put_to_user(ts, &kts, size);
#else
    ts->tv_sec = 1;
    ts->tv_nsec = 0;
#endif
    return 0;
}

int sys_futex(int *uaddr, int op, int val, void *timeout, void *uaddr2, int val3);
int sys_pmutex(void *umutex, int op, void *arg);

int sys_dup(int oldfd);
int sys_dup2(int oldfd, int new);

const static void* func_table[] =
{
    (void*)sys_exit,            /* 01 */
    (void*)sys_read,
    (void*)sys_write,
    (void*)sys_lseek,
    (void*)sys_open,            /* 05 */
    (void*)sys_close,
    (void*)sys_ioctl,
    (void*)sys_fstat,
    (void*)sys_poll,
    (void*)sys_nanosleep,       /* 10 */
    (void*)sys_gettimeofday,
    (void*)sys_settimeofday,
    (void*)sys_exec,
    (void*)sys_kill,
    (void*)sys_getpid,          /* 15 */
    (void*)sys_getpriority,
    (void*)sys_setpriority,
    (void*)sys_sem_create,
    (void*)sys_sem_delete,
    (void*)sys_sem_take,        /* 20 */
    (void*)sys_sem_release,
    (void*)sys_mutex_create,
    (void*)sys_mutex_delete,
    (void*)sys_mutex_take,
    (void*)sys_mutex_release,   /* 25 */
    (void*)sys_event_create,
    (void*)sys_event_delete,
    (void*)sys_event_send,
    (void*)sys_event_recv,
    (void*)sys_mb_create,       /* 30 */
    (void*)sys_mb_delete,
    (void*)sys_mb_send,
    (void*)sys_mb_send_wait,
    (void*)sys_mb_recv,
    (void*)sys_mq_create,       /* 35 */
    (void*)sys_mq_delete,
    (void*)sys_mq_send,
    (void*)sys_mq_urgent,
    (void*)sys_mq_recv,
    (void*)sys_thread_create,   /* 40 */
    (void*)sys_thread_delete,
    (void*)sys_thread_startup,
    (void*)sys_thread_self,
    (void*)sys_channel_open,
    (void*)sys_channel_close,   /* 45 */
    (void*)sys_channel_send,
    (void*)sys_channel_send_recv_timeout,
    (void*)sys_channel_reply,
    (void*)sys_channel_recv_timeout,
    (void*)sys_enter_critical,  /* 50 */
    (void*)sys_exit_critical,

    SYSCALL_USPACE(sys_brk),
    SYSCALL_USPACE(sys_mmap2),
    SYSCALL_USPACE(sys_munmap),

    SYSCALL_USPACE(sys_shmget), /* 55 */
    SYSCALL_USPACE(sys_shmrm),
    SYSCALL_USPACE(sys_shmat),
    SYSCALL_USPACE(sys_shmdt),

    (void *)sys_device_init,
    (void *)sys_device_register, /* 60 */
    (void *)sys_device_control,
    (void *)sys_device_find,
    (void *)sys_device_open,
    (void *)sys_device_close,
    (void *)sys_device_read,    /* 65 */
    (void *)sys_device_write,

    (void *)sys_stat,
    (void *)sys_thread_find,

    SYSCALL_NET(sys_accept),
    SYSCALL_NET(sys_bind),      /* 70 */
    SYSCALL_NET(sys_shutdown),
    SYSCALL_NET(sys_getpeername),
    SYSCALL_NET(sys_getsockname),
    SYSCALL_NET(sys_getsockopt),
    SYSCALL_NET(sys_setsockopt), /* 75 */
    SYSCALL_NET(sys_connect),
    SYSCALL_NET(sys_listen),
    SYSCALL_NET(sys_recv),
    SYSCALL_NET(sys_recvfrom),
    SYSCALL_NET(sys_send),      /* 80 */
    SYSCALL_NET(sys_sendto),
    SYSCALL_NET(sys_socket),

    SYSCALL_NET(sys_closesocket),
    SYSCALL_NET(sys_getaddrinfo),
    SYSCALL_NET(sys_gethostbyname2_r), /* 85 */

    (void *)sys_notimpl,    //(void *)network,
    (void *)sys_notimpl,    //(void *)network,
    (void *)sys_notimpl,    //(void *)network,
    (void *)sys_notimpl,    //(void *)network,
    (void *)sys_notimpl,    //(void *)network, /* 90 */
    (void *)sys_notimpl,    //(void *)network,
    (void *)sys_notimpl,    //(void *)network,
    (void *)sys_notimpl,    //(void *)network,

#ifdef RT_USING_DFS
    (void *)sys_select,
#else
    (void *)sys_notimpl,
#endif

    (void *)sys_notimpl,    //(void *)sys_hw_interrupt_disable, /* 95 */
    (void *)sys_notimpl,    //(void *)sys_hw_interrupt_enable,

    (void *)sys_tick_get,
    (void *)sys_exit_group,

    (void *)sys_notimpl,    //(void *)rt_delayed_work_init,
    (void *)sys_notimpl,    //(void *)rt_work_submit,           /* 100 */
    (void *)sys_notimpl,    //(void *)rt_wqueue_wakeup,
    (void *)sys_thread_mdelay,
    (void *)sys_sigaction,
    (void *)sys_sigprocmask,
    (void *)sys_tkill,             /* 105 */
    (void *)sys_notimpl,
    (void *)sys_thread_sigprocmask,
    (void *)sys_notimpl,
    (void *)sys_notimpl,
    (void *)sys_waitpid,          /* 110 */

    (void *)sys_timer_create,
    (void *)sys_timer_delete,
    (void *)sys_timer_start,
    (void *)sys_timer_stop,
    (void *)sys_timer_control,  /* 115 */
    (void *)sys_getcwd,
    (void *)sys_chdir,
    (void *)sys_unlink,
    (void *)sys_mkdir,
    (void *)sys_rmdir,          /* 120 */
    (void *)sys_getdents,
    (void *)sys_get_errno,
    (void *)sys_set_thread_area,
    (void *)sys_set_tid_address,
    (void *)sys_access,         /* 125 */
    (void *)sys_pipe,
    (void *)sys_clock_settime,
    (void *)sys_clock_gettime,
    (void *)sys_clock_getres,
    (void *)sys_clone,           /* 130 */
    (void *)sys_futex,
    (void *)sys_pmutex,
    (void *)sys_dup,
    (void *)sys_dup2,
};

const void *lwp_get_sys_api(rt_uint32_t number)
{
    const void *func = (const void*)sys_notimpl;

    if (number == 0xff)
    {
        func = (void *)sys_log;
    }
    else
    {
        number -= 1;
        if (number < sizeof(func_table)/sizeof(func_table[0]))
        {
            func = func_table[number];
        }
    }

    return func;
}
