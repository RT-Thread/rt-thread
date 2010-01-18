/*
 * File      : shell.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-04-30     Bernard      the first verion for FinSH
 * 2006-05-08     Bernard      change finsh thread stack to 2048
 * 2006-06-03     Bernard      add support for skyeye
 * 2006-09-24     Bernard      remove the code related with hardware
 * 2010-01-18     Bernard      fix down then up key bug.
 */

#include <rtthread.h>
#include <rthw.h>

#include "finsh.h"

/*
 * Add by caoxl 2009-10-14
 *
 */
#ifdef QEMU_CAOXL
#define  memcpy(a,b,c)	rt_memcpy(a,b,c)
extern char rt_serial_getc(void);
#endif

#define FINSH_USING_HISTORY

#if defined(__CC_ARM)					/* ARMCC compiler */
  #ifdef FINSH_USING_SYMTAB
    extern int FSymTab$$Base;
    extern int FSymTab$$Limit;
    extern int VSymTab$$Base;
    extern int VSymTab$$Limit;
  #endif
#elif defined(__ICCARM__)               /* for IAR compiler */
  #ifdef FINSH_USING_SYMTAB
    #pragma section="FSymTab"
    #pragma section="VSymTab"
  #endif
#elif defined(__GNUC__)
  #ifdef FINSH_USING_SYMTAB
  extern int __fsymtab_start;
  extern int __fsymtab_end;
  extern int __vsymtab_start;
  extern int __vsymtab_end;
  #endif
#endif

/* finsh thread */
struct rt_thread finsh_thread;
char finsh_thread_stack[2048];
struct rt_semaphore uart_sem;
#ifdef RT_USING_DEVICE
rt_device_t finsh_device;
#endif
#ifdef FINSH_USING_HISTORY
enum input_stat
{
	WAIT_NORMAL,
	WAIT_SPEC_KEY,
	WAIT_FUNC_KEY,
};
#ifndef FINSH_HISTORY_LINES
#define FINSH_HISTORY_LINES 5
#endif
#ifndef FINSH_CMD_SIZE
#define FINSH_CMD_SIZE		80
#endif
char finsh_cmd_history[FINSH_HISTORY_LINES][FINSH_CMD_SIZE];
rt_uint16_t finsh_history_count = 0;
#endif

#if !defined (RT_USING_NEWLIB) && !defined (RT_USING_MINILIBC)
void *memccpy(void *dst, const void *src, int c, size_t count)
{
	char *a = dst;
	const char *b = src;
	while (count--)
	{
		*a++ = *b;
		if (*b==c)
		{
			return (void *)a;
		}

		b++;
	}
	return 0;
}

int strcmp (const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2) s1++, s2++;

	return (*s1 - *s2);
}

#ifdef RT_USING_HEAP
char *strdup(const char *s)
{
	size_t len = strlen(s) + 1;
	char *tmp = (char *)rt_malloc(len);

	if(!tmp) return NULL;

	rt_memcpy(tmp, s, len);
	return tmp;
}
#endif

#if !defined(__CC_ARM) && !defined(__ICCARM__)
int isalpha( int ch )
{
	return (unsigned int)((ch | 0x20) - 'a') < 26u;
}

int atoi(const char* s)
{
	long int v=0;
	int sign=1;
	while ( *s == ' '  ||  (unsigned int)(*s - 9) < 5u) s++;

	switch (*s)
	{
	case '-': sign=-1;
	case '+': ++s;
	}

	while ((unsigned int) (*s - '0') < 10u)
	{
		v=v*10+*s-'0'; ++s;
	}

	return sign==-1?-v:v;
}

int isprint(unsigned char ch)
{
    return (unsigned int)(ch - ' ') < 127u - ' ';
}
#endif
#endif

#ifdef RT_USING_DEVICE
static rt_err_t finsh_rx_ind(rt_device_t dev, rt_size_t size)
{
	/* release semaphore to let finsh thread rx data */
	rt_sem_release(&uart_sem);

	return RT_EOK;
}

void finsh_set_device(char* device_name)
{
	rt_device_t dev = RT_NULL;

	dev = rt_device_find(device_name);
	if (dev != RT_NULL && rt_device_open(dev, RT_DEVICE_OFLAG_RDWR) == RT_EOK)
	{
		if (finsh_device != RT_NULL)
		{
			/* close old finsh device */
			rt_device_close(finsh_device);
		}

		finsh_device = dev;
		rt_device_set_rx_indicate(dev, finsh_rx_ind);
	}
	else
	{
		rt_kprintf("finsh: can not find device:%s\n", device_name);
	}
}
#else
void finsh_notify()
{
	rt_sem_release(&uart_sem);
}
#endif

void finsh_auto_complete(char* prefix)
{
	extern void list_prefix(char* prefix);

	rt_kprintf("\n");
	list_prefix(prefix);
	rt_kprintf("finsh>>%s", prefix);
}

void finsh_thread_entry(void* parameter)
{
	struct finsh_parser parser;
    char line[256];
	int  pos ;
#ifdef FINSH_USING_HISTORY
	enum input_stat stat;
	unsigned short  current_history, use_history;
#endif

	stat = WAIT_NORMAL;
	current_history = 0;
	use_history = 0;

    finsh_init(&parser);

	while (1)
	{
		rt_kprintf("finsh>>");

		memset(line, 0, sizeof(line));
		pos = 0;
		while (1)
		{
			if (rt_sem_take(&uart_sem, -1) == RT_EOK)
			{
				/* read one character from serial */
				char ch;

#ifndef RT_USING_DEVICE
				ch = rt_serial_getc();
				if (ch != 0)
#else
				rt_err_t rx_result;
				rx_result = rt_device_read(finsh_device, 0, &ch, 1);
				if (ch != 0 && rx_result == 1)
#endif
				{
#ifdef FINSH_USING_HISTORY
					/*
					 * handle up and down key
					 * up key  : 0x1b 0x5b 0x41
					 * down key: 0x1b 0x5b 0x42
					 */
					if (ch == 0x1b)
					{
						stat = WAIT_SPEC_KEY;
						continue;
					}

					if ((stat == WAIT_SPEC_KEY) && (ch == 0x5b))
					{
						if (ch == 0x5b)
						{
							stat = WAIT_FUNC_KEY;
							continue;
						}
						stat = WAIT_NORMAL;
					}

					if (stat == WAIT_FUNC_KEY)
					{
						stat = WAIT_NORMAL;

						if (ch == 0x41) /* up key */
						{
							/* prev history */
							if (current_history > 0)current_history --;
							else
							{
								current_history = 0;
								continue;
							}

							/* copy the history command */
							memcpy(line, &finsh_cmd_history[current_history][0],
								FINSH_CMD_SIZE);
							pos = strlen(line);
							use_history = 1;
						}
						else if (ch == 0x42) /* down key */
						{
							/* next history */
							if (current_history < finsh_history_count - 1)
								current_history ++;
							else
							{
								/* set to the end of history */
								if (finsh_history_count != 0)
								{
									current_history = finsh_history_count - 1;
								}
								else continue;
							}

							memcpy(line, &finsh_cmd_history[current_history][0],
								FINSH_CMD_SIZE);
							pos = strlen(line);
							use_history = 1;
						}

						if (use_history)
						{
							rt_kprintf("\033[2K\r");
							rt_kprintf("finsh>>%s", line);
							continue;
						}
					}
#endif
					/*
					 * handle tab key
					 */
					if (ch == '\t')
					{
						/* auto complete */
						finsh_auto_complete(&line[0]);
						/* re-calculate position */
						pos = strlen(line);
						continue;
					}

					/*
					 * handle backspace key
					 */
					if (ch == 0x7f || ch == 0x08)
					{
						if (pos != 0)rt_kprintf("%c", ch);
						line[pos--] = 0;
						if (pos < 0) pos = 0;
						continue;
					}

					line[pos] = ch;

					rt_kprintf("%c", line[pos]);

					/* if it's the end of line, break */
					if (line[pos] == 0xd || line[pos] == 0xa)
					{
						/* change to ';' and break */
						line[pos] = ';';
						break;
					}
					else use_history = 0; /* not "\n", it's a new command */
					pos ++;
				}
			}
		}

		if (pos == 0)
		{
			rt_kprintf("\n");
			continue;
		}

#ifdef FINSH_USING_HISTORY
		if (use_history == 0)
		{
			/* push history */
			if (finsh_history_count >= FINSH_HISTORY_LINES)
			{
				/* move history */
				int index;
				for (index = 0; index < FINSH_HISTORY_LINES - 1; index ++)
				{
					memcpy(&finsh_cmd_history[index][0],
						&finsh_cmd_history[index + 1][0], FINSH_CMD_SIZE);
				}
				memset(&finsh_cmd_history[index][0], 0, FINSH_CMD_SIZE);
				memcpy(&finsh_cmd_history[index][0], line, pos);

				/* it's the maximum history */
				finsh_history_count = FINSH_HISTORY_LINES;
			}
			else
			{
				memset(&finsh_cmd_history[finsh_history_count][0], 0, FINSH_CMD_SIZE);
				memcpy(&finsh_cmd_history[finsh_history_count][0], line, pos);

				/* increase count and set current history position */
				finsh_history_count ++;
			}
		}
		current_history = finsh_history_count;
#endif

		rt_kprintf("\n");
		finsh_parser_run(&parser, (unsigned char*)&line[0]);

		/* compile node root */
		if (finsh_errno() == 0)
		{
			finsh_compiler_run(parser.root);
		}
		else
		{
			rt_kprintf("%s\n", finsh_error_string(finsh_errno()));
		}

		/* run virtual machine */
		if (finsh_errno() == 0)
		{
			finsh_vm_run();

			if (isprint((unsigned char)finsh_stack_bottom()))
			{
				rt_kprintf("\t'%c', %d, 0x%08x\n",
					(unsigned char)finsh_stack_bottom(),
					(unsigned int)finsh_stack_bottom(),
					(unsigned int)finsh_stack_bottom());
			}
			else
			{
				rt_kprintf("\t%d, 0x%04x\n",
					(unsigned int)finsh_stack_bottom(),
					(unsigned int)finsh_stack_bottom());
			}
		}

        finsh_flush(&parser);
	}
}

void finsh_system_function_init(void* begin, void* end)
{
	_syscall_table_begin = (struct finsh_syscall*) begin;
	_syscall_table_end = (struct finsh_syscall*) end;
}

void finsh_system_var_init(void* begin, void* end)
{
	_sysvar_table_begin = (struct finsh_sysvar*) begin;
	_sysvar_table_end = (struct finsh_sysvar*) end;
}

/* init finsh */
void finsh_system_init()
{
	rt_sem_init(&uart_sem, "uart", 0, 0);

#ifdef FINSH_USING_SYMTAB
#ifdef __CC_ARM                 /* ARM C Compiler */
	finsh_system_function_init(&FSymTab$$Base, &FSymTab$$Limit);
	finsh_system_var_init(&VSymTab$$Base, &VSymTab$$Limit);
#elif defined (__ICCARM__)      /* for IAR Compiler */
    finsh_system_function_init(__section_begin("FSymTab"),
                               __section_end("FSymTab"));
    finsh_system_var_init(__section_begin("VSymTab"),
                          __section_end("VSymTab"));
#elif defined (__GNUC__)        /* GNU GCC Compiler */
	finsh_system_function_init(&__fsymtab_start, &__fsymtab_end);
	finsh_system_var_init(&__vsymtab_start, &__vsymtab_start);
#endif
#endif

	rt_thread_init(&finsh_thread,
		"tshell",
		finsh_thread_entry, RT_NULL,
		&finsh_thread_stack[0], sizeof(finsh_thread_stack),
		20, 100);
	rt_thread_startup(&finsh_thread);
}
