/*
 * File      : exception.c
 * Change Logs:
 * Date           Author       Notes
 * 2010-05-17     swkyer       first version
 */
#include <rtthread.h>
#include <rthw.h>
#include "../common/exception.h"
#include "../common/mipsregs.h"

/**
 * @addtogroup Jz47xx
 */
/*@{*/

/**
 * exception handle table
 */
exception_func_t sys_exception_handlers[33];

/**
 * setup the exception handle
 */
exception_func_t rt_set_except_vector(int n, exception_func_t func)
{
    exception_func_t old_handler = sys_exception_handlers[n];

    if ((n == 0) || (n > 32) || (!func))
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
	rt_kprintf("exception happens, epc: 0x%08x\n", regs->cp0_epc);
}

void install_default_execpt_handle(void)
{
	rt_int32_t i;

	for (i=0; i<33; i++)
		sys_exception_handlers[i] = (exception_func_t)unhandled_exception_handle;
}

/*@}*/

