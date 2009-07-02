/*
 * File      : cmd.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-04-30     Bernard      first implementation
 * 2006-05-04     Bernard      add list_thread,
 *                                 list_sem,
 *                                 list_timer
 * 2006-05-20     Bernard      add list_mutex,
 *                                 list_mailbox,
 *                                 list_msgqueue,
 *                                 list_event,
 *                                 list_fevent,
 *                                 list_mempool
 * 2006-06-03     Bernard      display stack information in list_thread
 * 2006-08-10     Bernard      change version to invoke rt_show_version
 * 2008-09-10     Bernard      update the list function for finsh syscall
 *                                 list and sysvar list
 * 2009-05-30     Bernard      add list_device
 */

#include <rtthread.h>
#include "finsh.h"

long hello()
{
	rt_kprintf("Hello RT-Thread!\n");

	return 0;
}
FINSH_FUNCTION_EXPORT(hello, say hello world)

extern void rt_show_version(void);
long version()
{
	rt_show_version();

	return 0;
}
FINSH_FUNCTION_EXPORT(version, show RT-Thread version information)

#define rt_list_entry(node, type, member) \
    ((type *)((char *)(node) - (unsigned long)(&((type *)0)->member)))
extern struct rt_object_information rt_object_container[];

int list_thread()
{
	struct rt_thread *thread;
	struct rt_list_node *list, *node;
	rt_uint8_t* ptr;

	list = &rt_object_container[RT_Object_Class_Thread].object_list;

	rt_kprintf(" thread  pri  status      sp     stack size max used   left tick  error\n");
	rt_kprintf("-------- ---- ------- ---------- ---------- ---------- ---------- ---\n");
	for (node = list->next; node != list; node = node->next)
	{
		thread = rt_list_entry(node, struct rt_thread, list);
		rt_kprintf("%-8s 0x%02x", thread->name, thread->current_priority);

		if (thread->stat == RT_THREAD_READY)		rt_kprintf(" ready  ");
		else if (thread->stat == RT_THREAD_SUSPEND) rt_kprintf(" suspend");
		else if (thread->stat == RT_THREAD_INIT)	rt_kprintf(" init   ");

		ptr = (rt_uint8_t*)thread->stack_addr;
		while (*ptr == '#')ptr ++;

		rt_kprintf(" 0x%08x 0x%08x 0x%08x 0x%08x %03d\n",
			thread->stack_size + ((rt_uint32_t)thread->stack_addr - (rt_uint32_t)thread->sp),
			thread->stack_size,
			thread->stack_size - ((rt_uint32_t) ptr - (rt_uint32_t)thread->stack_addr),
			thread->remaining_tick,
			thread->error);

	}
	return 0;
}
FINSH_FUNCTION_EXPORT(list_thread, list thread)

static void show_wait_queue(struct rt_list_node* list)
{
	struct rt_thread *thread;
	struct rt_list_node *node;

	for (node = list->next; node != list; node = node->next)
	{
		thread = rt_list_entry(node, struct rt_thread, tlist);
		rt_kprintf("%s", thread->name);
		if (node->next != list) rt_kprintf("/");
	}
}

#ifdef RT_USING_SEMAPHORE
int list_sem()
{
	struct rt_semaphore *sem;
	struct rt_list_node *list, *node;

	list = &rt_object_container[RT_Object_Class_Semaphore].object_list;

	rt_kprintf("semaphore v   suspend thread\n");
	rt_kprintf("--------  --- --------------\n");
	for (node = list->next; node != list; node = node->next)
	{
		sem = (struct rt_semaphore*)(rt_list_entry(node, struct rt_object, list));
		if (sem->parent.suspend_thread_count != 0)
		{
			rt_kprintf("%-8s  %03d %d:", sem->parent.parent.name, sem->value, sem->parent.suspend_thread_count);
			show_wait_queue(&(sem->parent.suspend_thread));
			rt_kprintf("\n");
		}
		else
		{
			rt_kprintf("%-8s  %03d %d\n", sem->parent.parent.name, sem->value, sem->parent.suspend_thread_count);
		}
	}

	return 0;
}
FINSH_FUNCTION_EXPORT(list_sem, list semaphone in system)
#endif

#ifdef RT_USING_FASTEVENT
int list_fevent()
{
	struct rt_fast_event *e;
	struct rt_list_node *list, *node;

	list = &rt_object_container[RT_Object_Class_FastEvent].object_list;

	rt_kprintf("fevent   set       \n");
	rt_kprintf("-------- ----------\n");
	for (node = list->next; node != list; node = node->next)
	{
		e = (struct rt_fast_event*)(rt_list_entry(node, struct rt_object, list));
		rt_kprintf("%-8s  0x%08x\n", e->parent.name, e->set);
	}

	return 0;
}
FINSH_FUNCTION_EXPORT(list_fevent, list fast event in system)
#endif

#ifdef RT_USING_EVENT
int list_event()
{
	struct rt_event *e;
	struct rt_list_node *list, *node;

	list = &rt_object_container[RT_Object_Class_Event].object_list;

	rt_kprintf("event    set        suspend thread\n");
	rt_kprintf("-------- ---------- --------------\n");
	for (node = list->next; node != list; node = node->next)
	{
		e = (struct rt_event*)(rt_list_entry(node, struct rt_object, list));
		rt_kprintf("%-8s  0x%08x %03d\n", e->parent.parent.name, e->set, e->parent.suspend_thread_count);
	}

	return 0;
}
FINSH_FUNCTION_EXPORT(list_event, list event in system)
#endif

#ifdef RT_USING_MUTEX
int list_mutex()
{
	struct rt_mutex *m;
	struct rt_list_node *list, *node;

	list = &rt_object_container[RT_Object_Class_Mutex].object_list;

	rt_kprintf("mutex    owner    hold suspend thread\n");
	rt_kprintf("-------- -------- ---- --------------\n");
	for (node = list->next; node != list; node = node->next)
	{
		m = (struct rt_mutex*)(rt_list_entry(node, struct rt_object, list));
		rt_kprintf("%-8s %-8s %04d %d\n", m->parent.parent.name, m->owner->name, m->hold, m->parent.suspend_thread_count);
	}

	return 0;
}
FINSH_FUNCTION_EXPORT(list_mutex, list mutex in system)
#endif

#ifdef RT_USING_MAILBOX
int list_mailbox()
{
	struct rt_mailbox *m;
	struct rt_list_node *list, *node;

	list = &rt_object_container[RT_Object_Class_MailBox].object_list;

	rt_kprintf("mailbox  entry size suspend thread\n");
	rt_kprintf("-------- ----  ---- --------------\n");
	for (node = list->next; node != list; node = node->next)
	{
		m = (struct rt_mailbox*)(rt_list_entry(node, struct rt_object, list));
		if (m->parent.suspend_thread_count != 0)
		{
			rt_kprintf("%-8s %04d  %04d %d:", m->parent.parent.name, m->entry, m->size, m->parent.suspend_thread_count);
			show_wait_queue(&(m->parent.suspend_thread));
			rt_kprintf("\n");
		}
		else
		{
			rt_kprintf("%-8s %04d  %04d %d\n", m->parent.parent.name, m->entry, m->size, m->parent.suspend_thread_count);
		}
	}

	return 0;
}
FINSH_FUNCTION_EXPORT(list_mailbox, list mail box in system)
#endif

#ifdef RT_USING_MESSAGEQUEUE
int list_msgqueue()
{
	struct rt_messagequeue *m;
	struct rt_list_node *list, *node;

	list = &rt_object_container[RT_Object_Class_MessageQueue].object_list;

	rt_kprintf("msgqueue entry suspend thread\n");
	rt_kprintf("-------- ----  --------------\n");
	for (node = list->next; node != list; node = node->next)
	{
		m = (struct rt_messagequeue*)(rt_list_entry(node, struct rt_object, list));
		rt_kprintf("%-8s %04d  %d\n", m->parent.parent.name, m->entry, m->parent.suspend_thread_count);
	}

	return 0;
}
FINSH_FUNCTION_EXPORT(list_msgqueue, list message queue in system)
#endif

#ifdef RT_USING_MEMPOOL
int list_mempool()
{
	struct rt_mempool *mp;

	struct rt_list_node *list, *node;

	list = &rt_object_container[RT_Object_Class_MemPool].object_list;

	rt_kprintf("mempool  block total free suspend thread\n");
	rt_kprintf("-------- ----  ----  ---- --------------\n");
	for (node = list->next; node != list; node = node->next)
	{
		mp = (struct rt_mempool*)rt_list_entry(node, struct rt_object, list);
		rt_kprintf("%-8s %04d  %04d  %04d %d\n", mp->parent.name,
			mp->block_size, mp->block_total_count, mp->block_free_count,
			mp->suspend_thread_count);
	}

	return 0;
}
FINSH_FUNCTION_EXPORT(list_mempool, list memory pool in system)
#endif

int list_timer()
{
	struct rt_timer *timer;
	struct rt_list_node *list, *node;

	list = &rt_object_container[RT_Object_Class_Timer].object_list;

	rt_kprintf("timer    periodic   timeout    flag\n");
	rt_kprintf("-------- ---------- ---------- -----------\n");
	for (node = list->next; node != list; node = node->next)
	{
		timer = (struct rt_timer*)(rt_list_entry(node, struct rt_object, list));
		rt_kprintf("%-8s 0x%08x 0x%08x ", timer->parent.name, timer->init_tick, timer->timeout_tick);
		if (timer->parent.flag & RT_TIMER_FLAG_ACTIVATED) rt_kprintf("activated\n");
		else rt_kprintf("deactivated\n");
	}

	rt_kprintf("current tick:0x%08x\n", rt_tick_get());

	return 0;
}
FINSH_FUNCTION_EXPORT(list_timer, list timer in system)

#ifdef RT_USING_DEVICE
int list_device()
{
	struct rt_device *device;
	struct rt_list_node *list, *node;
	const char *device_type_str[] = 
	{
		"Character Device",
		"Block Device",
		"Network Interface",
		"MTD Device",
		"CAN",
		"RTC",
		"Unknown"
	};

	list = &rt_object_container[RT_Object_Class_Device].object_list;

	rt_kprintf("device    type      \n");
	rt_kprintf("-------- ---------- \n");
	for (node = list->next; node != list; node = node->next)
	{
		device = (struct rt_device*)(rt_list_entry(node, struct rt_object, list));
		rt_kprintf("%-8s %-8s \n", device->parent.name, device_type_str[device->type]);
	}

	return 0;
}
FINSH_FUNCTION_EXPORT(list_device, list device in system)
#endif

int list()
{
	struct finsh_syscall_item* syscall_item;
	struct finsh_sysvar_item*  sysvar_item;

	rt_kprintf("--Function List:\n");
	{
		struct finsh_syscall* index;
		for (index = _syscall_table_begin; index < _syscall_table_end; index ++)
		{
#ifdef FINSH_USING_DESCRIPTION
			rt_kprintf("%-16s -- %s\n", index->name, index->desc);
#else
			rt_kprintf("%s\n", index->name);
#endif
		}
	}

	/* list syscall list */
	syscall_item = global_syscall_list;
	while (syscall_item != NULL)
	{
		rt_kprintf("[l] %s\n", syscall_item->syscall.name);
		syscall_item = syscall_item->next;
	}

	rt_kprintf("--Variable List:\n");
	{
		struct finsh_sysvar* index;
		for (index = _sysvar_table_begin; index < _sysvar_table_end; index ++)
		{
#ifdef FINSH_USING_DESCRIPTION
			rt_kprintf("%-16s -- %s\n", index->name, index->desc);
#else
			rt_kprintf("%s\n", index->name);
#endif
		}
	}

	sysvar_item = global_sysvar_list;
	while (sysvar_item != NULL)
	{
		rt_kprintf("[l] %s\n", sysvar_item->sysvar.name);
		sysvar_item = sysvar_item->next;
	}

	return 0;
}
FINSH_FUNCTION_EXPORT(list, list all symbol in system)

#ifdef FINSH_USING_SYMTAB
static int dummy = 0;
FINSH_VAR_EXPORT(dummy, finsh_type_int, dummy variable for finsh)
#endif
