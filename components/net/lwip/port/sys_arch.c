/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-12-8      Bernard      add file header
 *                             export bsd socket symbol for RT-Thread Application Module
 * 2013-05-25     Bernard      port to v1.4.1
 * 2017-03-26     HuangXiHans  port to v2.0.2
 * 2017-11-15     Bernard      add lock for init_done callback
 * 2018-11-02     MurphyZhao   port to v2.1.0
 * 2020-06-20     liuxianliang port to v2.1.2
 * 2021-06-25     liuxianliang port to v2.0.3
 * 2022-01-18     Meco Man     remove v2.0.2
 * 2022-02-20     Meco Man     integrate v1.4.1 v2.0.3 and v2.1.2 porting layer
 */

#include <rtthread.h>
#include <rthw.h>

#include <arch/sys_arch.h>
#include <lwip/sys.h>
#include <lwip/opt.h>
#include <lwip/stats.h>
#include <lwip/err.h>
#include <lwip/debug.h>
#include <lwip/netif.h>
#include <lwip/netifapi.h>
#include <lwip/tcpip.h>
#include <lwip/sio.h>
#include <lwip/init.h>
#include <lwip/dhcp.h>
#include <lwip/inet.h>
#include <netif/ethernetif.h>
#include <netif/etharp.h>

/*
 * Initialize the ethernetif layer and set network interface device up
 */
static void tcpip_init_done_callback(void *arg)
{
    rt_sem_release((rt_sem_t)arg);
}

/**
 * LwIP system initialization
 */
int lwip_system_init(void)
{
    rt_err_t rc;
    struct rt_semaphore done_sem;
    static rt_bool_t init_ok = RT_FALSE;

    if (init_ok)
    {
        rt_kprintf("lwip system already init.\n");
        return 0;
    }

    extern int eth_system_device_init_private(void);
    eth_system_device_init_private();

    /* set default netif to NULL */
    netif_default = RT_NULL;

    rc = rt_sem_init(&done_sem, "done", 0, RT_IPC_FLAG_FIFO);
    if (rc != RT_EOK)
    {
        LWIP_ASSERT("Failed to create semaphore", 0);

        return -1;
    }

    tcpip_init(tcpip_init_done_callback, (void *)&done_sem);

    /* waiting for initialization done */
    if (rt_sem_take(&done_sem, RT_WAITING_FOREVER) != RT_EOK)
    {
        rt_sem_detach(&done_sem);

        return -1;
    }
    rt_sem_detach(&done_sem);

    rt_kprintf("lwIP-%d.%d.%d initialized!\n", LWIP_VERSION_MAJOR, LWIP_VERSION_MINOR, LWIP_VERSION_REVISION);

    init_ok = RT_TRUE;

    return 0;
}
INIT_PREV_EXPORT(lwip_system_init);

void sys_init(void)
{
    /* nothing on RT-Thread porting */
}

void lwip_sys_init(void)
{
    lwip_system_init();
}

/*
 * Create a new semaphore
 *
 * @return the operation status, ERR_OK on OK; others on error
 */
err_t sys_sem_new(sys_sem_t *sem, u8_t count)
{
    static unsigned short counter = 0;
    char tname[RT_NAME_MAX];
    sys_sem_t tmpsem;

    RT_DEBUG_NOT_IN_INTERRUPT;

    rt_snprintf(tname, RT_NAME_MAX, "%s%d", SYS_LWIP_SEM_NAME, counter);
    counter ++;

    tmpsem = rt_sem_create(tname, count, RT_IPC_FLAG_FIFO);
    if (tmpsem == RT_NULL)
    {
        return ERR_MEM;
    }
    else
    {
        *sem = tmpsem;

        return ERR_OK;
    }
}

/*
 * Deallocate a semaphore
 */
void sys_sem_free(sys_sem_t *sem)
{
    RT_DEBUG_NOT_IN_INTERRUPT;
    rt_sem_delete(*sem);
}

/*
 * Signal a semaphore
 */
void sys_sem_signal(sys_sem_t *sem)
{
    rt_sem_release(*sem);
}

/*
 * Block the thread while waiting for the semaphore to be signaled
 *
 * @return If the timeout argument is non-zero, it will return the number of milliseconds
 *         spent waiting for the semaphore to be signaled; If the semaphore isn't signaled
 *         within the specified time, it will return SYS_ARCH_TIMEOUT; If the thread doesn't
 *         wait for the semaphore, it will return zero
 */
u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout)
{
    rt_err_t ret;
    s32_t t;
    u32_t tick;

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* get the begin tick */
    tick = rt_tick_get();
    if (timeout == 0)
    {
        t = RT_WAITING_FOREVER;
    }
    else
    {
        /* convert msecond to os tick */
        if (timeout < (1000 / RT_TICK_PER_SECOND))
            t = 1;
        else
            t = timeout / (1000 / RT_TICK_PER_SECOND);
    }

    ret = rt_sem_take(*sem, t);

    if (ret == -RT_ETIMEOUT)
    {
        return SYS_ARCH_TIMEOUT;
    }
    else
    {
        if (ret == RT_EOK)
            ret = 1;
    }

    /* get elapse msecond */
    tick = rt_tick_get() - tick;

    /* convert tick to msecond */
    tick = tick * (1000 / RT_TICK_PER_SECOND);
    if (tick == 0)
        tick = 1;

    return tick;
}

#ifndef sys_sem_valid
/** Check if a semaphore is valid/allocated:
 *  return 1 for valid, 0 for invalid
 */
int sys_sem_valid(sys_sem_t *sem)
{
    int ret = 0;

    if (*sem) ret = 1;

    return ret;
}
#endif

#ifndef sys_sem_set_invalid
/** Set a semaphore invalid so that sys_sem_valid returns 0
 */
void sys_sem_set_invalid(sys_sem_t *sem)
{
    *sem = RT_NULL;
}
#endif

/* ====================== Mutex ====================== */

/** Create a new mutex
 * @param mutex pointer to the mutex to create
 * @return a new mutex
 */
err_t sys_mutex_new(sys_mutex_t *mutex)
{
    static unsigned short counter = 0;
    char tname[RT_NAME_MAX];
    sys_mutex_t tmpmutex;

    RT_DEBUG_NOT_IN_INTERRUPT;

    rt_snprintf(tname, RT_NAME_MAX, "%s%d", SYS_LWIP_MUTEX_NAME, counter);
    counter ++;

    tmpmutex = rt_mutex_create(tname, RT_IPC_FLAG_PRIO);
    if (tmpmutex == RT_NULL)
    {
        return ERR_MEM;
    }
    else
    {
        *mutex = tmpmutex;
        return ERR_OK;
    }
}

/** Lock a mutex
 * @param mutex the mutex to lock
 */
void sys_mutex_lock(sys_mutex_t *mutex)
{
    RT_DEBUG_NOT_IN_INTERRUPT;
    rt_mutex_take(*mutex, RT_WAITING_FOREVER);
    return;
}

/** Unlock a mutex
 * @param mutex the mutex to unlock
 */
void sys_mutex_unlock(sys_mutex_t *mutex)
{
    rt_mutex_release(*mutex);
}

/** Delete a semaphore
 * @param mutex the mutex to delete
 */
void sys_mutex_free(sys_mutex_t *mutex)
{
    RT_DEBUG_NOT_IN_INTERRUPT;
    rt_mutex_delete(*mutex);
}

#ifndef sys_mutex_valid
/** Check if a mutex is valid/allocated:
 *  return 1 for valid, 0 for invalid
 */
int sys_mutex_valid(sys_mutex_t *mutex)
{
    int ret = 0;

    if (*mutex) ret = 1;

    return ret;
}
#endif

#ifndef sys_mutex_set_invalid
/** Set a mutex invalid so that sys_mutex_valid returns 0
 */
void sys_mutex_set_invalid(sys_mutex_t *mutex)
{
    *mutex = RT_NULL;
}
#endif

/* ====================== Mailbox ====================== */

/*
 * Create an empty mailbox for maximum "size" elements
 *
 * @return the operation status, ERR_OK on OK; others on error
 */
err_t sys_mbox_new(sys_mbox_t *mbox, int size)
{
    static unsigned short counter = 0;
    char tname[RT_NAME_MAX];
    sys_mbox_t tmpmbox;

    RT_DEBUG_NOT_IN_INTERRUPT;

    rt_snprintf(tname, RT_NAME_MAX, "%s%d", SYS_LWIP_MBOX_NAME, counter);
    counter ++;

    tmpmbox = rt_mb_create(tname, size, RT_IPC_FLAG_FIFO);
    if (tmpmbox != RT_NULL)
    {
        *mbox = tmpmbox;

        return ERR_OK;
    }

    return ERR_MEM;
}

/*
 * Deallocate a mailbox
 */
void sys_mbox_free(sys_mbox_t *mbox)
{
    RT_DEBUG_NOT_IN_INTERRUPT;
    rt_mb_delete(*mbox);
    return;
}

/** Post a message to an mbox - may not fail
 * -> blocks if full, only used from tasks not from ISR
 * @param mbox mbox to posts the message
 * @param msg message to post (ATTENTION: can be NULL)
 */
void sys_mbox_post(sys_mbox_t *mbox, void *msg)
{
    RT_DEBUG_NOT_IN_INTERRUPT;
    rt_mb_send_wait(*mbox, (rt_ubase_t)msg, RT_WAITING_FOREVER);
    return;
}

/*
 * Try to post the "msg" to the mailbox
 *
 * @return return ERR_OK if the "msg" is posted, ERR_MEM if the mailbox is full
 */
err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg)
{
    if (rt_mb_send(*mbox, (rt_ubase_t)msg) == RT_EOK)
    {
        return ERR_OK;
    }

    return ERR_MEM;
}

#if (LWIP_VERSION_MAJOR * 100 + LWIP_VERSION_MINOR) >= 201 /* >= v2.1.0 */
err_t sys_mbox_trypost_fromisr(sys_mbox_t *q, void *msg)
{
  return sys_mbox_trypost(q, msg);
}
#endif /* (LWIP_VERSION_MAJOR * 100 + LWIP_VERSION_MINOR) >= 201 */

/** Wait for a new message to arrive in the mbox
 * @param mbox mbox to get a message from
 * @param msg pointer where the message is stored
 * @param timeout maximum time (in milliseconds) to wait for a message
 * @return time (in milliseconds) waited for a message, may be 0 if not waited
           or SYS_ARCH_TIMEOUT on timeout
 *         The returned time has to be accurate to prevent timer jitter!
 */
u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout)
{
    rt_err_t ret;
    s32_t t;
    u32_t tick;

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* get the begin tick */
    tick = rt_tick_get();

    if(timeout == 0)
    {
        t = RT_WAITING_FOREVER;
    }
    else
    {
        /* convirt msecond to os tick */
        if (timeout < (1000 / RT_TICK_PER_SECOND))
            t = 1;
        else
            t = timeout / (1000 / RT_TICK_PER_SECOND);
    }
    /*When the waiting msg is generated by the application through signaling mechanisms,
    only by using interruptible mode can the program be made runnable again*/
    ret = rt_mb_recv_interruptible(*mbox, (rt_ubase_t *)msg, t);
    if(ret != RT_EOK)
    {
        return SYS_ARCH_TIMEOUT;
    }

    /* get elapse msecond */
    tick = rt_tick_get() - tick;

    /* convert tick to msecond */
    tick = tick * (1000 / RT_TICK_PER_SECOND);
    if (tick == 0)
        tick = 1;

    return tick;
}

/**
 * @ingroup sys_mbox
 * This is similar to sys_arch_mbox_fetch, however if a message is not
 * present in the mailbox, it immediately returns with the code
 * SYS_MBOX_EMPTY. On success 0 is returned.
 * To allow for efficient implementations, this can be defined as a
 * function-like macro in sys_arch.h instead of a normal function. For
 * example, a naive implementation could be:
 * \#define sys_arch_mbox_tryfetch(mbox,msg) sys_arch_mbox_fetch(mbox,msg,1)
 * although this would introduce unnecessary delays.
 *
 * @param mbox mbox to get a message from
 * @param msg pointer where the message is stored
 * @return 0 (milliseconds) if a message has been received
 *         or SYS_MBOX_EMPTY if the mailbox is empty
 */
u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg)
{
    int ret;

    ret = rt_mb_recv(*mbox, (rt_ubase_t *)msg, 0);
    if(ret == -RT_ETIMEOUT)
    {
        return SYS_ARCH_TIMEOUT;
    }
    else
    {
        if (ret == RT_EOK)
            ret = 0;
    }

    return ret;
}

#ifndef sys_mbox_valid
/** Check if an mbox is valid/allocated:
 *  return 1 for valid, 0 for invalid
 */
int sys_mbox_valid(sys_mbox_t *mbox)
{
    int ret = 0;

    if (*mbox) ret = 1;

    return ret;
}
#endif

#ifndef sys_mbox_set_invalid
/** Set an mbox invalid so that sys_mbox_valid returns 0
 */
void sys_mbox_set_invalid(sys_mbox_t *mbox)
{
    *mbox = RT_NULL;
}
#endif

/* ====================== System ====================== */

/*
 * Start a new thread named "name" with priority "prio" that will begin
 * its execution in the function "thread()". The "arg" argument will be
 * passed as an argument to the thread() function
 */
sys_thread_t sys_thread_new(const char    *name,
                            lwip_thread_fn thread,
                            void          *arg,
                            int            stacksize,
                            int            prio)
{
    rt_thread_t t;

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* create thread */
    t = rt_thread_create(name, thread, arg, stacksize, prio, 20);
    RT_ASSERT(t != RT_NULL);

    /* startup thread */
    rt_thread_startup(t);

    return t;
}

static RT_DEFINE_SPINLOCK(_spinlock);

sys_prot_t sys_arch_protect(void)
{
    rt_base_t level;
    level = rt_spin_lock_irqsave(&_spinlock); /* disable interrupt */
    return level;
}

void sys_arch_unprotect(sys_prot_t pval)
{
    rt_spin_unlock_irqrestore(&_spinlock, pval); /* enable interrupt */
}

void sys_arch_assert(const char *file, int line)
{
    rt_kprintf("\nAssertion: %d in %s, thread %s\n",
               line, file, rt_thread_self()->parent.name);
    RT_ASSERT(0);
}

u32_t sys_jiffies(void)
{
    return rt_tick_get();
}

u32_t sys_now(void)
{
    return rt_tick_get_millisecond();
}

rt_weak void mem_init(void)
{
}

void *mem_calloc(mem_size_t count, mem_size_t size)
{
    return rt_calloc(count, size);
}

void *mem_trim(void *mem, mem_size_t size)
{
    // return rt_realloc(mem, size);
    /* not support trim yet */
    return mem;
}

void *mem_malloc(mem_size_t size)
{
    return rt_malloc(size);
}

void  mem_free(void *mem)
{
    rt_free(mem);
}

#ifdef RT_LWIP_PPP
u32_t sio_read(sio_fd_t fd, u8_t *buf, u32_t size)
{
    u32_t len;

    RT_ASSERT(fd != RT_NULL);

    len = rt_device_read((rt_device_t)fd, 0, buf, size);
    if (len <= 0)
        return 0;

    return len;
}

u32_t sio_write(sio_fd_t fd, u8_t *buf, u32_t size)
{
    RT_ASSERT(fd != RT_NULL);
    return rt_device_write((rt_device_t)fd, 0, buf, size);
}

void sio_read_abort(sio_fd_t fd)
{
    rt_kprintf("read_abort\n");
}

void ppp_trace(int level, const char *format, ...)
{
    va_list args;
    rt_size_t length;
    static char rt_log_buf[RT_CONSOLEBUF_SIZE];

    va_start(args, format);
    length = rt_vsprintf(rt_log_buf, format, args);
    rt_device_write((rt_device_t)rt_console_get_device(), 0, rt_log_buf, length);
    va_end(args);
}
#endif /* RT_LWIP_PPP */

#if LWIP_VERSION_MAJOR >= 2 /* >= v2.x */
#if MEM_OVERFLOW_CHECK || MEMP_OVERFLOW_CHECK
/**
 * Check if a mep element was victim of an overflow or underflow
 * (e.g. the restricted area after/before it has been altered)
 *
 * @param p the mem element to check
 * @param size allocated size of the element
 * @param descr1 description of the element source shown on error
 * @param descr2 description of the element source shown on error
 */
void mem_overflow_check_raw(void *p, size_t size, const char *descr1, const char *descr2)
{
#if MEM_SANITY_REGION_AFTER_ALIGNED || MEM_SANITY_REGION_BEFORE_ALIGNED
  u16_t k;
  u8_t *m;

#if MEM_SANITY_REGION_AFTER_ALIGNED > 0
  m = (u8_t *)p + size;
  for (k = 0; k < MEM_SANITY_REGION_AFTER_ALIGNED; k++) {
    if (m[k] != 0xcd) {
      char errstr[128];
      rt_snprintf(errstr, sizeof(errstr), "detected mem overflow in %s%s", descr1, descr2);
      LWIP_ASSERT(errstr, 0);
    }
  }
#endif /* MEM_SANITY_REGION_AFTER_ALIGNED > 0 */

#if MEM_SANITY_REGION_BEFORE_ALIGNED > 0
  m = (u8_t *)p - MEM_SANITY_REGION_BEFORE_ALIGNED;
  for (k = 0; k < MEM_SANITY_REGION_BEFORE_ALIGNED; k++) {
    if (m[k] != 0xcd) {
      char errstr[128];
      rt_snprintf(errstr, sizeof(errstr), "detected mem underflow in %s%s", descr1, descr2);
      LWIP_ASSERT(errstr, 0);
    }
  }
#endif /* MEM_SANITY_REGION_BEFORE_ALIGNED > 0 */
#else
  LWIP_UNUSED_ARG(p);
  LWIP_UNUSED_ARG(descr1);
  LWIP_UNUSED_ARG(descr2);
#endif /* MEM_SANITY_REGION_AFTER_ALIGNED || MEM_SANITY_REGION_BEFORE_ALIGNED */
}

/**
 * Initialize the restricted area of a mem element.
 */
void mem_overflow_init_raw(void *p, size_t size)
{
#if MEM_SANITY_REGION_BEFORE_ALIGNED > 0 || MEM_SANITY_REGION_AFTER_ALIGNED > 0
  u8_t *m;
#if MEM_SANITY_REGION_BEFORE_ALIGNED > 0
  m = (u8_t *)p - MEM_SANITY_REGION_BEFORE_ALIGNED;
  rt_memset(m, 0xcd, MEM_SANITY_REGION_BEFORE_ALIGNED);
#endif
#if MEM_SANITY_REGION_AFTER_ALIGNED > 0
  m = (u8_t *)p + size;
  rt_memset(m, 0xcd, MEM_SANITY_REGION_AFTER_ALIGNED);
#endif
#else /* MEM_SANITY_REGION_BEFORE_ALIGNED > 0 || MEM_SANITY_REGION_AFTER_ALIGNED > 0 */
  LWIP_UNUSED_ARG(p);
  LWIP_UNUSED_ARG(size);
#endif /* MEM_SANITY_REGION_BEFORE_ALIGNED > 0 || MEM_SANITY_REGION_AFTER_ALIGNED > 0 */
}
#endif /* MEM_OVERFLOW_CHECK || MEMP_OVERFLOW_CHECK */

#ifdef LWIP_HOOK_IP4_ROUTE_SRC
struct netif *lwip_ip4_route_src(const ip4_addr_t *dest, const ip4_addr_t *src)
{
    struct netif *netif;

    if (src == NULL)
        return NULL;

    /* iterate through netifs */
    for (netif = netif_list; netif != NULL; netif = netif->next)
    {
        /* is the netif up, does it have a link and a valid address? */
        if (netif_is_up(netif) && netif_is_link_up(netif) && !ip4_addr_isany_val(*netif_ip4_addr(netif)))
        {
            /* source ip address equals netif's ip address? */
            if (ip4_addr_cmp(src, netif_ip4_addr(netif)))
            {
                return netif;
            }
        }
    }

    return NULL;
}
#endif /* LWIP_HOOK_IP4_ROUTE_SRC */
#endif /*LWIP_VERSION_MAJOR >= 2 */

#if LWIP_SOCKET
#include <lwip/sockets.h>
RTM_EXPORT(lwip_accept);
RTM_EXPORT(lwip_bind);
RTM_EXPORT(lwip_shutdown);
RTM_EXPORT(lwip_getpeername);
RTM_EXPORT(lwip_getsockname);
RTM_EXPORT(lwip_getsockopt);
RTM_EXPORT(lwip_setsockopt);
RTM_EXPORT(lwip_close);
RTM_EXPORT(lwip_connect);
RTM_EXPORT(lwip_listen);
RTM_EXPORT(lwip_recv);
RTM_EXPORT(lwip_read);
RTM_EXPORT(lwip_recvfrom);
RTM_EXPORT(lwip_send);
RTM_EXPORT(lwip_sendto);
RTM_EXPORT(lwip_socket);
RTM_EXPORT(lwip_write);
RTM_EXPORT(lwip_select);
RTM_EXPORT(lwip_ioctl);
RTM_EXPORT(lwip_fcntl);
RTM_EXPORT(lwip_htons);
RTM_EXPORT(lwip_htonl);

#if LWIP_DNS
#include <lwip/netdb.h>
RTM_EXPORT(lwip_gethostbyname);
RTM_EXPORT(lwip_gethostbyname_r);
RTM_EXPORT(lwip_freeaddrinfo);
RTM_EXPORT(lwip_getaddrinfo);
#endif /* LWIP_DNS */
#endif /* LWIP_SOCKET */

#if LWIP_DHCP
#include <lwip/dhcp.h>
RTM_EXPORT(dhcp_start);
RTM_EXPORT(dhcp_renew);
RTM_EXPORT(dhcp_stop);
#endif /* LWIP_DHCP */

#if LWIP_NETIF_API
#include <lwip/netifapi.h>
RTM_EXPORT(netifapi_netif_set_addr);
#endif /* LWIP_NETIF_API */

#if LWIP_NETIF_LINK_CALLBACK
RTM_EXPORT(netif_set_link_callback);
#endif /* LWIP_NETIF_LINK_CALLBACK */

#if LWIP_NETIF_STATUS_CALLBACK
RTM_EXPORT(netif_set_status_callback);
#endif /* LWIP_NETIF_STATUS_CALLBACK */

RTM_EXPORT(netif_find);
RTM_EXPORT(netif_set_addr);
RTM_EXPORT(netif_set_ipaddr);
RTM_EXPORT(netif_set_gw);
RTM_EXPORT(netif_set_netmask);
