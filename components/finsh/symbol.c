/*
 *  symbols in finsh shell.
 *
 * COPYRIGHT (C) 2006 - 2013, RT-Thread Development Team
 *
 *  This file is part of RT-Thread (http://www.rt-thread.org)
 *  Maintainer: bernard.xiong <bernard.xiong at gmail.com>
 *
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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
