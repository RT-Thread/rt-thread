#include <rtthread.h>

#include "lwip/debug.h"
#include "lwip/sys.h"
#include "lwip/opt.h"
#include "lwip/stats.h"
#include "lwip/err.h"
#include "arch/sys_arch.h"

#include <string.h>

#define LWIP_THREAD_MAGIC	0x1919


void sys_init(void)
{
	/* nothing to do in RT-Thread */

	return;
}

/* ====================== Semaphore ====================== */

err_t sys_sem_new(sys_sem_t *sem, u8_t count)
{
	static unsigned short counter = 0;
	char tname[RT_NAME_MAX];
	sys_sem_t tmpsem;

	rt_snprintf(tname, RT_NAME_MAX, "%s%d", SYS_LWIP_SEM_NAME, counter);

#if SYS_DEBUG
	{
		struct rt_thread *thread;

		thread = rt_thread_self();
		LWIP_DEBUGF(SYS_DEBUG, ("%s, Create sem: %s \n",thread->name, tname));
	}
#endif

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
#if SYS_DEBUG
	{
		struct rt_thread *thread;
		thread = rt_thread_self();

		LWIP_DEBUGF(SYS_DEBUG, ("%s, Delete sem: %s \n",thread->name,
			(*sem)->parent.parent.name));
	}
#endif

	rt_sem_delete(*sem);

}


void sys_sem_signal(sys_sem_t *sem)
{
#if SYS_DEBUG
	{
		struct rt_thread *thread;
		thread = rt_thread_self();

		LWIP_DEBUGF(SYS_DEBUG, ("%s, Release signal: %s , %d\n",thread->name,
			(*sem)->parent.parent.name, (*sem)->value));
	}
#endif

	rt_sem_release(*sem);

}

u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout)
{
	rt_err_t ret;
	s32_t t;
	u32_t tick;

	/* get the begin tick */
	tick = rt_tick_get();
#if SYS_DEBUG
	{
		struct rt_thread *thread;
		thread = rt_thread_self();

		LWIP_DEBUGF(SYS_DEBUG, ("%s, Wait sem: %s , %d\n",thread->name,
			(*sem)->parent.parent.name, (*sem)->value));
	}
#endif

	if(timeout == 0)
		t = RT_WAITING_FOREVER;
	else
	{
		/* convirt msecond to os tick */
		if (timeout < (1000/RT_TICK_PER_SECOND)) t = 1;
		else t = timeout / (1000/RT_TICK_PER_SECOND);
	}

	ret = rt_sem_take(*sem, t);

	if (ret == -RT_ETIMEOUT) return SYS_ARCH_TIMEOUT;
	else if (ret == RT_EOK) ret = 1;

	/* get elapse msecond */
	tick = rt_tick_get() - tick;

	/* convert tick to msecond */
	tick = tick * (1000/RT_TICK_PER_SECOND);
	if (tick == 0) tick = 1;

	return tick;
}

#ifndef sys_sem_valid
/** Check if a sempahore is valid/allocated: return 1 for valid, 0 for invalid */
int sys_sem_valid(sys_sem_t *sem)
{
	////////////////////
	// to be implemented.
	////////////////////
	return (int)(*sem);
}
#endif
#ifndef sys_sem_set_invalid
/** Set a semaphore invalid so that sys_sem_valid returns 0 */
void sys_sem_set_invalid(sys_sem_t *sem)
{
	////////////////////
	// to be implemented.
	////////////////////
	*sem = RT_NULL;
}
#endif




/* ====================== Mailbox ====================== */

err_t sys_mbox_new(sys_mbox_t *mbox, int size)
{
	static unsigned short counter = 0;
	char tname[RT_NAME_MAX];
	sys_mbox_t tmpmbox;

	rt_snprintf(tname, RT_NAME_MAX, "%s%d", SYS_LWIP_MBOX_NAME, counter);

#if SYS_DEBUG
	{
		struct rt_thread *thread;
		thread = rt_thread_self();

		LWIP_DEBUGF(SYS_DEBUG, ("%s, Create mbox: %s \n",thread->name, tname));
	}
#endif

	counter++;

	tmpmbox = rt_mb_create(tname, size, RT_IPC_FLAG_FIFO);
	if( tmpmbox != RT_NULL )
	{
		*mbox = tmpmbox;
		return ERR_OK;
	}
	else
		return ERR_MEM;

}

void sys_mbox_free(sys_mbox_t *mbox)
{
#if SYS_DEBUG
	{
		struct rt_thread *thread;
		thread = rt_thread_self();

		LWIP_DEBUGF(SYS_DEBUG, ("%s, Delete mbox: %s\n",thread->name,
			(*mbox)->parent.parent.name));
	}
#endif

	rt_mb_delete(*mbox);

	return;
}

void sys_mbox_post(sys_mbox_t *mbox, void *msg)
{
#if SYS_DEBUG
	{
		struct rt_thread *thread;
		thread = rt_thread_self();

		LWIP_DEBUGF(SYS_DEBUG, ("%s, Post mail: %s ,0x%x\n",thread->name,
			(*mbo)x->parent.parent.name, (rt_uint32_t)msg));
	}
#endif

	rt_mb_send(*mbox, (rt_uint32_t)msg);

	return;
}

err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg)
{
#if SYS_DEBUG
	{
		struct rt_thread *thread;
		thread = rt_thread_self();

		LWIP_DEBUGF(SYS_DEBUG, ("%s, Post mail: %s ,0x%x\n",thread->name,
			(*mbox)->parent.parent.name, (rt_uint32_t)msg));
	}
#endif

	if (rt_mb_send(*mbox, (rt_uint32_t)msg) == RT_EOK) return ERR_OK;

	return ERR_MEM;
}

u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout)
{
	rt_err_t ret;
	s32_t t;
	u32_t tick;

	/* get the begin tick */
	tick = rt_tick_get();

	if(timeout == 0)
		t = RT_WAITING_FOREVER;
	else
	{
		/* convirt msecond to os tick */
		if (timeout < (1000/RT_TICK_PER_SECOND)) t = 1;
		else t = timeout / (1000/RT_TICK_PER_SECOND);
	}

	ret = rt_mb_recv(*mbox, (rt_uint32_t *)msg, t);

	if(ret == -RT_ETIMEOUT) return SYS_ARCH_TIMEOUT;
	else if (ret == RT_EOK) ret = 1;

#if SYS_DEBUG
	{
		struct rt_thread *thread;
		thread = rt_thread_self();

		LWIP_DEBUGF(SYS_DEBUG, ("%s, Fetch mail: %s , 0x%x\n",thread->name,
			mbox->parent.parent.name, *(rt_uint32_t **)msg));
	}
#endif

	/* get elapse msecond */
	tick = rt_tick_get() - tick;

	/* convert tick to msecond */
	tick = tick * (1000/RT_TICK_PER_SECOND);
	if (tick == 0) tick = 1;

	return tick;
}

u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg)
{
	int ret;

	ret = rt_mb_recv(*mbox, (rt_uint32_t *)msg, 0);

	if(ret == -RT_ETIMEOUT) return SYS_ARCH_TIMEOUT;
	else if (ret == RT_EOK) ret = 1;

#if SYS_DEBUG
	{
		struct rt_thread *thread;
		thread = rt_thread_self();

		LWIP_DEBUGF(SYS_DEBUG, ("%s, Fetch mail: %s , 0x%x\n",thread->name,
			(*mbox)->parent.parent.name, *(rt_uint32_t **)msg));
	}
#endif

	return ret;
}

#ifndef sys_mbox_valid
/** Check if an mbox is valid/allocated: return 1 for valid, 0 for invalid */
int sys_mbox_valid(sys_mbox_t *mbox)
{
	////////////////////
	// to be implemented.
	////////////////////
	return (int)(*mbox);
}
#endif
#ifndef sys_mbox_set_invalid
/** Set an mbox invalid so that sys_mbox_valid returns 0 */
void sys_mbox_set_invalid(sys_mbox_t *mbox)
{
	////////////////////
	// to be implemented.
	////////////////////
	*mbox = RT_NULL;
}
#endif




/* ====================== System ====================== */

sys_thread_t sys_thread_new(const char *name, lwip_thread_fn thread, void *arg, int stacksize, int prio)
{
	rt_thread_t t;

	/* create thread */
	t = rt_thread_create(name, thread, arg, stacksize, prio, 20);
	RT_ASSERT(t != RT_NULL);

	/* startup thread */
	rt_thread_startup(t);

	return t;
}

sys_prot_t sys_arch_protect(void)
{
	/* disable interrupt */
	return rt_hw_interrupt_disable();
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

