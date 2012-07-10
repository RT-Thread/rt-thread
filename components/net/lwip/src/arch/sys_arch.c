#include <rtthread.h>

#include "lwip/sys.h"
#include "lwip/opt.h"
#include "lwip/stats.h"
#include "lwip/err.h"
#include "arch/sys_arch.h"
#include "lwip/debug.h"
#include "lwip/netif.h"
#include "lwip/tcpip.h"
#include "netif/ethernetif.h"

#include <string.h>

static err_t netif_device_init(struct netif *netif)
{
	struct eth_device *ethif;

	ethif = (struct eth_device*)netif->state;
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

static void tcpip_init_done_callback(void *arg)
{
	rt_device_t device;
	struct eth_device *ethif;
	struct ip_addr ipaddr, netmask, gw;
	struct rt_list_node* node;
	struct rt_object* object;
	struct rt_object_information *information;

	extern struct rt_object_information rt_object_container[];

	LWIP_ASSERT("invalid arg.\n",arg);

	IP4_ADDR(&gw, 0,0,0,0);
	IP4_ADDR(&ipaddr, 0,0,0,0);
	IP4_ADDR(&netmask, 0,0,0,0);

	/* enter critical */
	rt_enter_critical();

	/* for each network interfaces */
	information = &rt_object_container[RT_Object_Class_Device];
	for (node = information->object_list.next; node != &(information->object_list); node = node->next)
	{
		object = rt_list_entry(node, struct rt_object, list);
		device = (rt_device_t) object;
		if (device->type == RT_Device_Class_NetIf)
		{
			ethif = (struct eth_device*)device;

			/* leave critical */
			rt_exit_critical();

			netif_add(ethif->netif, &ipaddr, &netmask, &gw,
				ethif, netif_device_init, tcpip_input);

			if (netif_default == RT_NULL)
				netif_set_default(ethif->netif);

#if LWIP_DHCP
			if (ethif->flags & NETIF_FLAG_DHCP)
			{
				/* if this interface uses DHCP, start the DHCP client */
				dhcp_start(ethif->netif);
			}
			else
#endif
			{
				/* set interface up */
				netif_set_up(ethif->netif);
			}

#ifdef LWIP_NETIF_LINK_CALLBACK
			netif_set_link_up(ethif->netif);
#endif

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
void lwip_system_init(void)
{
	rt_err_t rc;
	struct rt_semaphore done_sem;

	rc = rt_sem_init(&done_sem, "done", 0, RT_IPC_FLAG_FIFO);

	if(rc != RT_EOK)
	{
    	LWIP_ASSERT("Failed to create semaphore", 0);
		return;
	}

	tcpip_init(tcpip_init_done_callback,(void *)&done_sem);

	/* waiting for initialization done */
	if (rt_sem_take(&done_sem, RT_WAITING_FOREVER) != RT_EOK)
	{
		rt_sem_detach(&done_sem);
		return;
	}
	rt_sem_detach(&done_sem);

	/* set default ip address */
#if !LWIP_DHCP
	{
		struct ip_addr ipaddr, netmask, gw;

		IP4_ADDR(&ipaddr, RT_LWIP_IPADDR0, RT_LWIP_IPADDR1, RT_LWIP_IPADDR2, RT_LWIP_IPADDR3);
		IP4_ADDR(&gw, RT_LWIP_GWADDR0, RT_LWIP_GWADDR1, RT_LWIP_GWADDR2, RT_LWIP_GWADDR3);
		IP4_ADDR(&netmask, RT_LWIP_MSKADDR0, RT_LWIP_MSKADDR1, RT_LWIP_MSKADDR2, RT_LWIP_MSKADDR3);

		netifapi_netif_set_addr(netif_default, &ipaddr, &netmask, &gw);
	}
#endif
}

void sys_init(void)
{
	/* nothing on RT-Thread porting */
}

void lwip_sys_init(void)
{
	lwip_system_init();
}

err_t sys_sem_new(sys_sem_t *sem, u8_t count)
{
	static unsigned short counter = 0;
	char tname[RT_NAME_MAX];
	sys_sem_t tmpsem;

	RT_DEBUG_NOT_IN_INTERRUPT;

	rt_snprintf(tname, RT_NAME_MAX, "%s%d", SYS_LWIP_SEM_NAME, counter);
	counter++;

	tmpsem = rt_sem_create(tname, count, RT_IPC_FLAG_FIFO);
	if( tmpsem == RT_NULL )
		return ERR_MEM;
	else
	{
		*sem = tmpsem;
		return ERR_OK;
	}
}


void sys_sem_free(sys_sem_t *sem)
{
	RT_DEBUG_NOT_IN_INTERRUPT;
	rt_sem_delete(*sem);
}


void sys_sem_signal(sys_sem_t *sem)
{
	rt_sem_release(*sem);
}

u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout)
{
	rt_err_t ret;
	s32_t t;
	u32_t tick;

	RT_DEBUG_NOT_IN_INTERRUPT;
	
	/* get the begin tick */
	tick = rt_tick_get();
	if(timeout == 0) t = RT_WAITING_FOREVER;
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
	tick = tick * (1000/RT_TICK_PER_SECOND);
	if (tick == 0)
		tick = 1;

	return tick;
}

#ifndef sys_sem_valid
/** Check if a semaphore is valid/allocated: return 1 for valid, 0 for invalid */
int sys_sem_valid(sys_sem_t *sem)
{
	return (int)(*sem);
}
#endif
#ifndef sys_sem_set_invalid
/** Set a semaphore invalid so that sys_sem_valid returns 0 */
void sys_sem_set_invalid(sys_sem_t *sem)
{
	*sem = RT_NULL;
}
#endif


/* ====================== Mutex ====================== */

/** Create a new mutex
 * @param mutex pointer to the mutex to create
 * @return a new mutex */
err_t sys_mutex_new(sys_mutex_t *mutex)
{
	static unsigned short counter = 0;
	char tname[RT_NAME_MAX];
	sys_mutex_t tmpmutex;

	RT_DEBUG_NOT_IN_INTERRUPT;

	rt_snprintf(tname, RT_NAME_MAX, "%s%d", SYS_LWIP_MUTEX_NAME, counter);
	counter++;

	tmpmutex = rt_mutex_create(tname, RT_IPC_FLAG_FIFO);
	if( tmpmutex == RT_NULL )
		return ERR_MEM;
	else
	{
		*mutex = tmpmutex;
		return ERR_OK;
	}
}

/** Lock a mutex
 * @param mutex the mutex to lock */
void sys_mutex_lock(sys_mutex_t *mutex)
{
	RT_DEBUG_NOT_IN_INTERRUPT;
	rt_mutex_take(*mutex, RT_WAITING_FOREVER);

	return;
}


/** Unlock a mutex
 * @param mutex the mutex to unlock */
void sys_mutex_unlock(sys_mutex_t *mutex)
{
	rt_mutex_release(*mutex);
}

/** Delete a semaphore
 * @param mutex the mutex to delete */
void sys_mutex_free(sys_mutex_t *mutex)
{
	RT_DEBUG_NOT_IN_INTERRUPT;

	rt_mutex_delete(*mutex);
}

#ifndef sys_mutex_valid
/** Check if a mutex is valid/allocated: return 1 for valid, 0 for invalid */
int sys_mutex_valid(sys_mutex_t *mutex)
{
	return (int)(*mutex);
}
#endif

#ifndef sys_mutex_set_invalid
/** Set a mutex invalid so that sys_mutex_valid returns 0 */
void sys_mutex_set_invalid(sys_mutex_t *mutex)
{
	*mutex = RT_NULL;
}
#endif

/* ====================== Mailbox ====================== */

err_t sys_mbox_new(sys_mbox_t *mbox, int size)
{
	static unsigned short counter = 0;
	char tname[RT_NAME_MAX];
	sys_mbox_t tmpmbox;

	RT_DEBUG_NOT_IN_INTERRUPT;

	rt_snprintf(tname, RT_NAME_MAX, "%s%d", SYS_LWIP_MBOX_NAME, counter);
	counter++;

	tmpmbox = rt_mb_create(tname, size, RT_IPC_FLAG_FIFO);
	if( tmpmbox != RT_NULL )
	{
		*mbox = tmpmbox;
		return ERR_OK;
	}

	return ERR_MEM;
}

void sys_mbox_free(sys_mbox_t *mbox)
{
	RT_DEBUG_NOT_IN_INTERRUPT;

	rt_mb_delete(*mbox);

	return;
}

/** Post a message to an mbox - may not fail
 * -> blocks if full, only used from tasks not from ISR
 * @param mbox mbox to posts the message
 * @param msg message to post (ATTENTION: can be NULL) */
void sys_mbox_post(sys_mbox_t *mbox, void *msg)
{
	RT_DEBUG_NOT_IN_INTERRUPT;

	rt_mb_send_wait(*mbox, (rt_uint32_t)msg,RT_WAITING_FOREVER);

	return;
}

err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg)
{
	if (rt_mb_send(*mbox, (rt_uint32_t)msg) == RT_EOK)
		return ERR_OK;

	return ERR_MEM;
}

/** Wait for a new message to arrive in the mbox
 * @param mbox mbox to get a message from
 * @param msg pointer where the message is stored
 * @param timeout maximum time (in milliseconds) to wait for a message
 * @return time (in milliseconds) waited for a message, may be 0 if not waited
           or SYS_ARCH_TIMEOUT on timeout
 *         The returned time has to be accurate to prevent timer jitter! */
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

	ret = rt_mb_recv(*mbox, (rt_uint32_t *)msg, t);

	if(ret == -RT_ETIMEOUT)
		return SYS_ARCH_TIMEOUT;
	else
	{
		LWIP_ASSERT("rt_mb_recv returned with error!", ret == RT_EOK);
	}

	/* get elapse msecond */
	tick = rt_tick_get() - tick;

	/* convert tick to msecond */
	tick = tick * (1000/RT_TICK_PER_SECOND);
	if (tick == 0)
		tick = 1;

	return tick;
}

/** Wait for a new message to arrive in the mbox
 * @param mbox mbox to get a message from
 * @param msg pointer where the message is stored
 * @param timeout maximum time (in milliseconds) to wait for a message
 * @return 0 (milliseconds) if a message has been received
 *         or SYS_MBOX_EMPTY if the mailbox is empty */
u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg)
{
	int ret;

	ret = rt_mb_recv(*mbox, (rt_uint32_t *)msg, 0);

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
/** Check if an mbox is valid/allocated: return 1 for valid, 0 for invalid */
int sys_mbox_valid(sys_mbox_t *mbox)
{
	return (int)(*mbox);
}
#endif
#ifndef sys_mbox_set_invalid
/** Set an mbox invalid so that sys_mbox_valid returns 0 */
void sys_mbox_set_invalid(sys_mbox_t *mbox)
{
	*mbox = RT_NULL;
}
#endif




/* ====================== System ====================== */

sys_thread_t sys_thread_new(const char *name, lwip_thread_fn thread, void *arg, int stacksize, int prio)
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

void sys_arch_assert(const char* file, int line)
{
	rt_kprintf("\nAssertion: %d in %s, thread %s\n", line, file,
        rt_thread_self()->name);
	RT_ASSERT(0);
}
