/*
 * File      : cmd.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
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
 * 2010-04-21     yi.qiu          add list_module
 */

#include <rtthread.h>
#include "finsh.h"

// Copy from kservice.h because we can not use it out of the kernel.
// Ugly. Should let kservice.h avaliable for applications?
rt_inline int rt_list_isempty(const rt_list_t *l)
{
	return l->next == l;
}

rt_inline unsigned int rt_list_len(const rt_list_t *l)
{
	unsigned int len = 0;
	const rt_list_t *p = l;
	while( p->next != l )
	{
		p = p->next;
		len++;
	}
	return len;
}

long hello(void)
{
	rt_kprintf("Hello RT-Thread!\n");

	return 0;
}
FINSH_FUNCTION_EXPORT(hello, say hello world);

extern void rt_show_version(void);
long version(void)
{
	rt_show_version();

	return 0;
}
FINSH_FUNCTION_EXPORT(version, show RT-Thread version information);

#define rt_list_entry(node, type, member) \
    ((type *)((char *)(node) - (unsigned long)(&((type *)0)->member)))
extern struct rt_object_information rt_object_container[];

static long _list_thread(struct rt_list_node* list)
{
	struct rt_thread *thread;
	struct rt_list_node *node;
	rt_uint8_t* ptr;

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

long list_thread(void)
{
	return _list_thread(&rt_object_container[RT_Object_Class_Thread].object_list);
}
FINSH_FUNCTION_EXPORT(list_thread, list thread);

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
static long _list_sem(struct rt_list_node *list)
{
	struct rt_semaphore *sem;
	struct rt_list_node *node;

	rt_kprintf("semaphore v   suspend thread\n");
	rt_kprintf("--------  --- --------------\n");
	for (node = list->next; node != list; node = node->next)
	{
		sem = (struct rt_semaphore*)(rt_list_entry(node, struct rt_object, list));
		if( !rt_list_isempty(&sem->parent.suspend_thread) )
		{
			rt_kprintf("%-8s  %03d %d:", sem->parent.parent.name, sem->value, rt_list_len(&sem->parent.suspend_thread) );
			show_wait_queue(&(sem->parent.suspend_thread));
			rt_kprintf("\n");
		}
		else
		{
			rt_kprintf("%-8s  %03d %d\n", sem->parent.parent.name, sem->value, rt_list_len(&sem->parent.suspend_thread));
		}
	}

	return 0;
}

long list_sem(void)
{
	return _list_sem(&rt_object_container[RT_Object_Class_Semaphore].object_list);
}
FINSH_FUNCTION_EXPORT(list_sem, list semaphone in system)
#endif

#ifdef RT_USING_EVENT
static long _list_event(struct rt_list_node *list)
{
	struct rt_event *e;
	struct rt_list_node *node;

	rt_kprintf("event    set        suspend thread\n");
	rt_kprintf("-------- ---------- --------------\n");
	for (node = list->next; node != list; node = node->next)
	{
		e = (struct rt_event*)(rt_list_entry(node, struct rt_object, list));
		if( !rt_list_isempty(&e->parent.suspend_thread) )
		{
			rt_kprintf("%-8s  0x%08x %03d\n", e->parent.parent.name, e->set, rt_list_len(&e->parent.suspend_thread));
			show_wait_queue(&(e->parent.suspend_thread));
			rt_kprintf("\n");
		}
		else
		{
			rt_kprintf("%-8s  0x%08x 0\n", e->parent.parent.name, e->set);
		}
	}

	return 0;
}

long list_event(void)
{
	return _list_event(&rt_object_container[RT_Object_Class_Event].object_list);
}
FINSH_FUNCTION_EXPORT(list_event, list event in system)
#endif

#ifdef RT_USING_MUTEX
static long _list_mutex(struct rt_list_node *list)
{
	struct rt_mutex *m;
	struct rt_list_node *node;

	rt_kprintf("mutex    owner    hold suspend thread\n");
	rt_kprintf("-------- -------- ---- --------------\n");
	for (node = list->next; node != list; node = node->next)
	{
		m = (struct rt_mutex*)(rt_list_entry(node, struct rt_object, list));
		rt_kprintf("%-8s %-8s %04d %d\n", m->parent.parent.name, m->owner->name, m->hold, rt_list_len(&m->parent.suspend_thread));
	}

	return 0;
}

long list_mutex(void)
{
	return _list_mutex(&rt_object_container[RT_Object_Class_Mutex].object_list);
}
FINSH_FUNCTION_EXPORT(list_mutex, list mutex in system)
#endif

#ifdef RT_USING_MAILBOX
static long _list_mailbox(struct rt_list_node *list)
{
	struct rt_mailbox *m;
	struct rt_list_node *node;

	rt_kprintf("mailbox  entry size suspend thread\n");
	rt_kprintf("-------- ----  ---- --------------\n");
	for (node = list->next; node != list; node = node->next)
	{
		m = (struct rt_mailbox*)(rt_list_entry(node, struct rt_object, list));
		if( !rt_list_isempty(&m->parent.suspend_thread) )
		{
			rt_kprintf("%-8s %04d  %04d %d:", m->parent.parent.name, m->entry, m->size, rt_list_len(&m->parent.suspend_thread));
			show_wait_queue(&(m->parent.suspend_thread));
			rt_kprintf("\n");
		}
		else
		{
			rt_kprintf("%-8s %04d  %04d %d\n", m->parent.parent.name, m->entry, m->size, rt_list_len(&m->parent.suspend_thread));
		}
	}

	return 0;
}

long list_mailbox(void)
{
	return _list_mailbox(&rt_object_container[RT_Object_Class_MailBox].object_list);
}
FINSH_FUNCTION_EXPORT(list_mailbox, list mail box in system)
#endif

#ifdef RT_USING_MESSAGEQUEUE
static long _list_msgqueue(struct rt_list_node *list)
{
	struct rt_messagequeue *m;
	struct rt_list_node *node;

	rt_kprintf("msgqueue entry suspend thread\n");
	rt_kprintf("-------- ----  --------------\n");
	for (node = list->next; node != list; node = node->next)
	{
		m = (struct rt_messagequeue*)(rt_list_entry(node, struct rt_object, list));
		if( !rt_list_isempty(&m->parent.suspend_thread) )
		{
			rt_kprintf("%-8s %04d  %d:", m->parent.parent.name, m->entry, rt_list_len(&m->parent.suspend_thread));
			show_wait_queue(&(m->parent.suspend_thread));
			rt_kprintf("\n");
		}
		else
		{
			rt_kprintf("%-8s %04d  %d\n", m->parent.parent.name, m->entry, rt_list_len(&m->parent.suspend_thread));
		}
	}

	return 0;
}

long list_msgqueue(void)
{
	return _list_msgqueue(&rt_object_container[RT_Object_Class_MessageQueue].object_list);
}
FINSH_FUNCTION_EXPORT(list_msgqueue, list message queue in system)
#endif

#ifdef RT_USING_MEMPOOL
static long _list_mempool(struct rt_list_node *list)
{
	struct rt_mempool *mp;
	struct rt_list_node *node;

	rt_kprintf("mempool  block total free suspend thread\n");
	rt_kprintf("-------- ----  ----  ---- --------------\n");
	for (node = list->next; node != list; node = node->next)
	{
		mp = (struct rt_mempool*)rt_list_entry(node, struct rt_object, list);
		if (mp->suspend_thread_count > 0)
		{
			rt_kprintf("%-8s %04d  %04d  %04d %d:", mp->parent.name,
				mp->block_size, mp->block_total_count, mp->block_free_count,
				mp->suspend_thread_count);
			show_wait_queue(&(mp->suspend_thread));
			rt_kprintf("\n");			
		}
		else
		{
			rt_kprintf("%-8s %04d  %04d  %04d %d\n", mp->parent.name,
				mp->block_size, mp->block_total_count, mp->block_free_count,
				mp->suspend_thread_count);
		}
	}

	return 0;
}

long list_mempool(void)
{
	return _list_mempool(&rt_object_container[RT_Object_Class_MemPool].object_list);
}
FINSH_FUNCTION_EXPORT(list_mempool, list memory pool in system)
#endif

static long _list_timer(struct rt_list_node *list)
{
	struct rt_timer *timer;
	struct rt_list_node *node;

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

long list_timer(void)
{
	return _list_timer(&rt_object_container[RT_Object_Class_Timer].object_list);
}
FINSH_FUNCTION_EXPORT(list_timer, list timer in system)

#ifdef RT_USING_DEVICE
static long _list_device(struct rt_list_node *list)
{
	struct rt_device *device;
	struct rt_list_node *node;
	const char *device_type_str[] =
	{
		"Character Device",
		"Block Device",
		"Network Interface",
		"MTD Device",
		"CAN Device",
		"RTC",
		"Sound Device",
		"Graphic Device",
		"I2C Device",
		"USB Slave Device",
		"USB Host Bus",
		"Unknown"
	};

	rt_kprintf("device    type      \n");
	rt_kprintf("-------- ---------- \n");
	for (node = list->next; node != list; node = node->next)
	{
		device = (struct rt_device*)(rt_list_entry(node, struct rt_object, list));
		rt_kprintf("%-8s %-8s \n", device->parent.name, device_type_str[device->type]);
	}

	return 0;
}

long list_device(void)
{
	return _list_device(&rt_object_container[RT_Object_Class_Device].object_list);
}
FINSH_FUNCTION_EXPORT(list_device, list device in system)
#endif

#ifdef RT_USING_MODULE
#include <rtm.h>

int list_module(void)
{
	struct rt_module *module;
	struct rt_list_node *list, *node;

	list = &rt_object_container[RT_Object_Class_Module].object_list;

	rt_kprintf("module name     ref\n");
	rt_kprintf("------------ --------\n");
	for (node = list->next; node != list; node = node->next)
	{
		module = (struct rt_module*)(rt_list_entry(node, struct rt_object, list));
		rt_kprintf("%-16s ", module->parent.name);
		rt_kprintf("%-04d \n", module->nref);
	}

	return 0;

}

FINSH_FUNCTION_EXPORT(list_module, list module in system)

int list_mod_detail(const char* name)
{
	int i;
	struct rt_module *module;
	
	/* find module */
	if((module = rt_module_find(name)) != RT_NULL)
	{
		/* module has entry point */
		if(!(module->parent.flag & RT_MODULE_FLAG_WITHOUTENTRY))
		{	
			struct rt_thread *thread;
			struct rt_list_node *tlist;
			rt_uint8_t* ptr;

			/* list main thread in module */
			if(module->module_thread != RT_NULL)
			{	
				rt_kprintf("main thread  pri  status      sp     stack size max used   left tick  error\n");
				rt_kprintf("------------- ---- ------- ---------- ---------- ---------- ---------- ---\n");
				thread = module->module_thread;
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

			/* list sub thread in module */
			tlist = &module->module_object[RT_Object_Class_Thread].object_list;
			if(!rt_list_isempty(tlist)) _list_thread(tlist);
#ifdef RT_USING_SEMAPHORE
			/* list semaphored in module */
			tlist = &module->module_object[RT_Object_Class_Semaphore].object_list;
			if(!rt_list_isempty(tlist)) _list_sem(tlist);
#endif
#ifdef RT_USING_MUTEX
			/* list mutex in module */
			tlist = &module->module_object[RT_Object_Class_Mutex].object_list;
			if(!rt_list_isempty(tlist)) _list_mutex(tlist);
#endif
#ifdef RT_USING_EVENT
			/* list event in module */
			tlist = &module->module_object[RT_Object_Class_Event].object_list;
			if(!rt_list_isempty(tlist)) _list_event(tlist);
#endif
#ifdef RT_USING_MAILBOX
			/* list mailbox in module */
			tlist = &module->module_object[RT_Object_Class_MailBox].object_list;
			if(!rt_list_isempty(tlist)) _list_mailbox(tlist);
#endif
#ifdef RT_USING_MESSAGEQUEUE
			/* list message queue in module */
			tlist = &module->module_object[RT_Object_Class_MessageQueue].object_list;
			if(!rt_list_isempty(tlist)) _list_msgqueue(tlist);
#endif
#ifdef RT_USING_MEMPOOL
			/* list memory pool in module */
			tlist = &module->module_object[RT_Object_Class_MemPool].object_list;
			if(!rt_list_isempty(tlist)) _list_mempool(tlist);
#endif
#ifdef RT_USING_DEVICE
			/* list device in module */
			tlist = &module->module_object[RT_Object_Class_Device].object_list;
			if(!rt_list_isempty(tlist)) _list_device(tlist);
#endif
			/* list timer in module */
			tlist = &module->module_object[RT_Object_Class_Timer].object_list;
			if(!rt_list_isempty(tlist)) _list_timer(tlist);
		}

		rt_kprintf("symbol    address   \n");
		rt_kprintf("-------- ----------\n");
	
		/* list module export symbols */
		for(i=0; i<module->nsym; i++)
		{
			rt_kprintf("%s 0x%x\n", module->symtab[i].name, module->symtab[i].addr);
		}	
	}

	return 0;
}
FINSH_FUNCTION_EXPORT(list_mod_detail, list module objects in system)
#endif

long list(void)
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

static int str_is_prefix(const char* prefix, const char* str)
{
	while ((*prefix) && (*prefix == *str))
	{
		prefix ++;
		str ++;
	}

	if (*prefix == 0) return 0;
	return -1;
}

void list_prefix(char* prefix)
{
	struct finsh_syscall_item* syscall_item;
	struct finsh_sysvar_item*  sysvar_item;
	rt_uint16_t func_cnt, var_cnt;
	const char* name_ptr;

	func_cnt = 0;
	var_cnt  = 0;
	name_ptr = RT_NULL;

	{
		struct finsh_syscall* index;
		for (index = _syscall_table_begin; index < _syscall_table_end; index ++)
		{
			if (str_is_prefix(prefix, index->name) == 0)
			{
				if (func_cnt == 0)
					rt_kprintf("--function:\n");

				func_cnt ++;
				/* set name_ptr */
				name_ptr = index->name;

#ifdef FINSH_USING_DESCRIPTION
				rt_kprintf("%-16s -- %s\n", index->name, index->desc);
#else
				rt_kprintf("%s\n", index->name);
#endif
			}
		}
	}

	/* list syscall list */
	syscall_item = global_syscall_list;
	while (syscall_item != NULL)
	{
		if (str_is_prefix(prefix, syscall_item->syscall.name) == 0)
		{
			if (func_cnt == 0)
				rt_kprintf("--function:\n");
			func_cnt ++;
			/* set name_ptr */
			name_ptr = syscall_item->syscall.name;

			rt_kprintf("[l] %s\n", syscall_item->syscall.name);
		}
		syscall_item = syscall_item->next;
	}

	{
		struct finsh_sysvar* index;
		for (index = _sysvar_table_begin; index < _sysvar_table_end; index ++)
		{
			if (str_is_prefix(prefix, index->name) == 0)
			{
				if (var_cnt == 0)
					rt_kprintf("--variable:\n");

				var_cnt ++;
				/* set name ptr */
				name_ptr = index->name;

#ifdef FINSH_USING_DESCRIPTION
				rt_kprintf("%-16s -- %s\n", index->name, index->desc);
#else
				rt_kprintf("%s\n", index->name);
#endif
			}
		}
	}

	sysvar_item = global_sysvar_list;
	while (sysvar_item != NULL)
	{
		if (str_is_prefix(prefix, sysvar_item->sysvar.name) == 0)
		{
			if (var_cnt == 0)
				rt_kprintf("--variable:\n");

			var_cnt ++;
			/* set name ptr */
			name_ptr = sysvar_item->sysvar.name;

			rt_kprintf("[l] %s\n", sysvar_item->sysvar.name);
		}
		sysvar_item = sysvar_item->next;
	}

	/* only one matched */
	if ((func_cnt + var_cnt) == 1)
	{
		rt_strncpy(prefix, name_ptr, strlen(name_ptr));
	}
}

#ifdef FINSH_USING_SYMTAB
static int dummy = 0;
FINSH_VAR_EXPORT(dummy, finsh_type_int, dummy variable for finsh)
#endif
