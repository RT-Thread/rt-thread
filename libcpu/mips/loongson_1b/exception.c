/*
 * File      : cpu.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-05-17     swkyer       first version
 */
#include <rtthread.h>
#include <rthw.h>
#include "../common/exception.h"
#include "../common/mipsregs.h"

/**
 * @addtogroup Loongson
 */

/*@{*/

/**
 * exception handle table
 */
#define RT_EXCEPTION_MAX	8
exception_func_t sys_exception_handlers[RT_EXCEPTION_MAX];

/**
 * setup the exception handle
 */
exception_func_t rt_set_except_vector(int n, exception_func_t func)
{
    exception_func_t old_handler = sys_exception_handlers[n];

    if ((n == 0) || (n > RT_EXCEPTION_MAX) || (!func))
    {
        return 0;
    }

    sys_exception_handlers[n] = func;

    return old_handler;
}

void tlb_refill_handler(void)
{
	rt_kprintf("tlb-miss happens, epc: 0x%08x\n", read_c0_epc());
	rt_hw_cpu_shutdown();
}

void cache_error_handler(void)
{
	rt_kprintf("cache exception happens, epc: 0x%08x\n", read_c0_epc());
	rt_hw_cpu_shutdown();
}

static void unhandled_exception_handle(pt_regs_t *regs)
{
	rt_kprintf("exception happens, epc: 0x%08x, cause: 0x%08x\n", regs->cp0_epc, read_c0_cause());
}

void install_default_execpt_handle(void)
{
	rt_int32_t i;

	for (i=0; i<RT_EXCEPTION_MAX; i++)
		sys_exception_handlers[i] = (exception_func_t)unhandled_exception_handle;
}

void exception_handler(pt_regs_t *regs)
{
	rt_uint32_t cause;
	rt_uint32_t index;

	cause = (read_c0_cause() & read_c0_config());
	cause = (cause & 0xfc00) >> 8;

	for (index = RT_EXCEPTION_MAX; index > 0; index --)
	{
		if (cause & (1 << index))
		{
			sys_exception_handlers[index](regs);
			cause &= ~(1 << index);
		}
	}
}

/*@}*/
