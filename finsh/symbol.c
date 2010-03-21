/*
 * File      : symbol.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-22     Bernard      first version
 */
#include "finsh.h"

long hello(void);
long version(void);
long list(void);
long list_thread(void);
long list_sem(void);
long list_mutex(void);
long list_fevent(void);
long list_event(void);
long list_mailbox(void);
long list_msgqueue(void);
long list_mempool(void);
long list_timer(void);

#ifdef FINSH_USING_SYMTAB
struct finsh_syscall *_syscall_table_begin 	= NULL;
struct finsh_syscall *_syscall_table_end 	= NULL;
struct finsh_sysvar *_sysvar_table_begin 	= NULL;
struct finsh_sysvar *_sysvar_table_end 		= NULL;
#else
struct finsh_syscall _syscall_table[] =
{
	{"hello", hello},
	{"version", version},
	{"list", list},
	{"list_thread", list_thread},
#ifdef RT_USING_SEMAPHORE
	{"list_sem", list_sem},
#endif
#ifdef RT_USING_MUTEX
	{"list_mutex", list_mutex},
#endif
#ifdef RT_USING_FEVENT
	{"list_fevent", list_fevent},
#endif
#ifdef RT_USING_EVENT
	{"list_event", list_event},
#endif
#ifdef RT_USING_MAILBOX
	{"list_mb", list_mailbox},
#endif
#ifdef RT_USING_MESSAGEQUEUE
	{"list_mq", list_msgqueue},
#endif
#ifdef RT_USING_MEMPOOL
	{"list_memp", list_mempool},
#endif
	{"list_timer", list_timer},
};
struct finsh_syscall *_syscall_table_begin = &_syscall_table[0];
struct finsh_syscall *_syscall_table_end   = &_syscall_table[sizeof(_syscall_table) / sizeof(struct finsh_syscall)];

struct finsh_sysvar *_sysvar_table_begin  = NULL;
struct finsh_sysvar *_sysvar_table_end    = NULL;
#endif
