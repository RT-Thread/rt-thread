/*
 * COPYRIGHT (C) 2006-2021, RT-Thread Development Team
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-12-8      Bernard      add file header
 *                             export bsd socket symbol for RT-Thread Application Module
 * 2017-11-15     Bernard      add lock for init_done callback.
 */

#include <rtthread.h>
#include <rthw.h>

#include "lwip/sys.h"
#include "lwip/opt.h"
#include "lwip/stats.h"
#include "lwip/err.h"
#include "arch/sys_arch.h"
#include "lwip/debug.h"
#include "lwip/netif.h"
#include "lwip/netifapi.h"
#include "lwip/tcpip.h"
#include "netif/ethernetif.h"
#include "lwip/sio.h"
#include "lwip/init.h"
#include "lwip/dhcp.h"
#include "lwip/inet.h"

#include <string.h>

/*
 * Initialize the network interface device
 *
 * @return the operation status, ERR_OK on OK, ERR_IF on error
 */
static err_t netif_device_init(struct netif *netif)
{
    struct eth_device *ethif;

    ethif = (struct eth_device *)netif->state;
    if (ethif != RT_NULL)
    {
        rt_device_t device;

        /* get device object */
        device = (rt_device_t) ethif;
        if (rt_device_init(device) != RT_EOK)
        {
            return ERR_IF;
        }

        /* copy device flags to netif flags */
        netif->flags = ethif->flags;

        return ERR_OK;
    }

    return ERR_IF;
}
/*
 * Initialize the ethernetif layer and set network interface device up
 */
static void tcpip_init_done_callback(void *arg)
{
    rt_device_t device;
    struct eth_device *ethif;
    ip4_addr_t ipaddr, netmask, gw;
    struct rt_list_node* node;
    struct rt_object* object;
    struct rt_object_information *information;

    LWIP_ASSERT("invalid arg.\n",arg);

    IP4_ADDR(&gw, 0,0,0,0);
    IP4_ADDR(&ipaddr, 0,0,0,0);
    IP4_ADDR(&netmask, 0,0,0,0);

    /* enter critical */
    rt_enter_critical();

    /* for each network interfaces */
    information = rt_object_get_information(RT_Object_Class_Device);
    RT_ASSERT(information != RT_NULL);
    for (node = information->object_list.next;
         node != &(information->object_list);
         node = node->next)
    {
        object = rt_list_entry(node, struct rt_object, list);
        device = (rt_device_t)object;
        if (device->type == RT_Device_Class_NetIf)
        {
            ethif = (struct eth_device *)device;

            /* leave critical */
            rt_exit_critical();
            LOCK_TCPIP_CORE();

            netif_add(ethif->netif, &ipaddr, &netmask, &gw,
                      ethif, netif_device_init, tcpip_input);

            if (netif_default == RT_NULL)
                netif_set_default(ethif->netif);

#if LWIP_DHCP
            /* set interface up */
            netif_set_up(ethif->netif);
            /* if this interface uses DHCP, start the DHCP client */
            dhcp_start(ethif->netif);
#else
            /* set interface up */
            netif_set_up(ethif->netif);
#endif

            if (ethif->flags & ETHIF_LINK_PHYUP)
            {
                netif_set_link_up(ethif->netif);
            }

            UNLOCK_TCPIP_CORE();
            /* enter critical */
            rt_enter_critical();
        }
    }

    /* leave critical */
    rt_exit_critical();
    rt_sem_release((rt_sem_t)arg);
}

/**
 * LwIP system initialization
 */
extern int eth_system_device_init_private(void);
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

    /* set default ip address */
#if !LWIP_DHCP
    if (netif_default != RT_NULL)
    {
        struct ip4_addr ipaddr, netmask, gw;

        ipaddr.addr = inet_addr(RT_LWIP_IPADDR);
        gw.addr = inet_addr(RT_LWIP_GWADDR);
        netmask.addr = inet_addr(RT_LWIP_MSKADDR);

        netifapi_netif_set_addr(netif_default, &ipaddr, &netmask, &gw);
    }
#endif
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
        return ERR_MEM;
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
        t = RT_WAITING_FOREVER;
    else
    {
        /* convert msecond to os tick */
        if (timeout < (1000/RT_TICK_PER_SECOND))
            t = 1;
        else
            t = timeout / (1000/RT_TICK_PER_SECOND);
    }

    ret = rt_sem_take(*sem, t);

    if (ret == -RT_ETIMEOUT)
        return SYS_ARCH_TIMEOUT;
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
    return (int)(*sem);
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

    tmpmutex = rt_mutex_create(tname, RT_IPC_FLAG_FIFO);
    if (tmpmutex == RT_NULL)
        return ERR_MEM;
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
    return (int)(*mutex);
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
        return ERR_OK;

    return ERR_MEM;
}

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
        t = RT_WAITING_FOREVER;
    else
    {
        /* convirt msecond to os tick */
        if (timeout < (1000/RT_TICK_PER_SECOND))
            t = 1;
        else
            t = timeout / (1000/RT_TICK_PER_SECOND);
    }

    ret = rt_mb_recv(*mbox, (rt_ubase_t *)msg, t);
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

/** Wait for a new message to arrive in the mbox
 * @param mbox mbox to get a message from
 * @param msg pointer where the message is stored
 * @param timeout maximum time (in milliseconds) to wait for a message
 * @return 0 (milliseconds) if a message has been received
 *         or SYS_MBOX_EMPTY if the mailbox is empty
 */
u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg)
{
    int ret;

    ret = rt_mb_recv(*mbox, (rt_ubase_t *)msg, 0);

    if(ret == -RT_ETIMEOUT)
        return SYS_ARCH_TIMEOUT;
    else
    {
        if (ret == RT_EOK)
            ret = 1;
    }

    return ret;
}

#ifndef sys_mbox_valid
/** Check if an mbox is valid/allocated:
 *  return 1 for valid, 0 for invalid
 */
int sys_mbox_valid(sys_mbox_t *mbox)
{
    return (int)(*mbox);
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

sys_prot_t sys_arch_protect(void)
{
    rt_base_t level;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    return level;
}

void sys_arch_unprotect(sys_prot_t pval)
{
    /* enable interrupt */
    rt_hw_interrupt_enable(pval);

    return;
}

void sys_arch_assert(const char *file, int line)
{
    rt_kprintf("\nAssertion: %d in %s, thread %s\n",
               line, file, rt_thread_self()->name);
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


RT_WEAK
void mem_init(void)
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
#endif

/*
 * export bsd socket symbol for RT-Thread Application Module
 */
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
#endif

#endif

#if LWIP_DHCP
#include <lwip/dhcp.h>
RTM_EXPORT(dhcp_start);
RTM_EXPORT(dhcp_renew);
RTM_EXPORT(dhcp_stop);
#endif

#if LWIP_NETIF_API
#include <lwip/netifapi.h>
RTM_EXPORT(netifapi_netif_set_addr);
#endif

#if LWIP_NETIF_LINK_CALLBACK
RTM_EXPORT(netif_set_link_callback);
#endif

#if LWIP_NETIF_STATUS_CALLBACK
RTM_EXPORT(netif_set_status_callback);
#endif

RTM_EXPORT(netif_find);
RTM_EXPORT(netif_set_addr);
RTM_EXPORT(netif_set_ipaddr);
RTM_EXPORT(netif_set_gw);
RTM_EXPORT(netif_set_netmask);
