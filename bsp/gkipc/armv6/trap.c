/*
 * File      : trap.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
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
 */

#include <rtthread.h>
#include <rthw.h>

#include "gk7101.h"
#include <gtypes.h>
#include <gd_int.h>
#include "rtos_lib.h"


extern struct rt_thread *rt_current_thread;
#ifdef RT_USING_FINSH
extern long list_thread(void);
#endif

/**
 * this function will show registers of CPU
 *
 * @param regs the registers point
 */

/* FIXME(Heyong): add for print the system infos when sys abort */
static void _rtt_statistics()
{
    rt_uint32_t total;
    rt_uint32_t used;
    rt_uint32_t max_used;
    struct rt_thread *thread;
    struct rt_list_node *node;
    rt_uint8_t *ptr;

    rt_base_t level;
    struct rt_object_information *information;

    information = rt_object_get_information(RT_Object_Class_Thread);
    RT_ASSERT(information != RT_NULL);

    struct rt_list_node *list = &(information->object_list);

    level = rt_hw_interrupt_disable();

    for (node = list->next; node != list; node = node->next)
    {
        thread = rt_list_entry(node, struct rt_thread, list);
        //if(thread) thread->total_tick = 0;
    }

    rt_hw_interrupt_enable(level);
    rt_memory_info(&total,&used,&max_used);
    rt_kprintf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    rt_kprintf("\n         memory info       size \n");
    rt_kprintf("------------------------- ------\n");
    rt_kprintf("total memory:             (%dKB)\n",  total/1024);
    rt_kprintf("used memory :             (%dKB)\n",  used/1024);
    rt_kprintf("maximum allocated memory: (%dKB)\n\n",  max_used/1024);

    rt_kprintf("          thread                 pri  status     sp     stack addr stack size  max used \n");
    rt_kprintf("-------------------------------- --- ------- ---------- ---------- ---------- ---------- \n");
    for (node = list->next; node != list; node = node->next)
    {
        thread = rt_list_entry(node, struct rt_thread, list);
#if 0
        rt_kprintf("%-32.*s 0x%02x", RT_NAME_MAX, thread->name, thread->current_priority);
#else
        int priority = thread->current_priority;
        rt_kprintf("%-32.*s %03d", RT_NAME_MAX, thread->name, priority);
#endif
        if (thread->stat == RT_THREAD_READY)        rt_kprintf(" ready  ");
        else if (thread->stat == RT_THREAD_SUSPEND) rt_kprintf(" suspend");
        else if (thread->stat == RT_THREAD_INIT)    rt_kprintf(" init   ");
        else if (thread->stat == RT_THREAD_CLOSE)   rt_kprintf(" close  ");

        ptr = (rt_uint8_t*)thread->stack_addr;
        while (*ptr == '#')ptr++;

        rt_kprintf("  0x%08x 0x%08x 0x%08x 0x%08x  \n",
            thread->stack_size + ((rt_uint32_t)thread->stack_addr - (rt_uint32_t)thread->sp),
            thread->stack_addr,
            thread->stack_size,
            thread->stack_size - ((rt_uint32_t) ptr - (rt_uint32_t)thread->stack_addr)
           );
    }
    rt_kprintf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}

// FIXME(heyong): add for debug when sys abort.
int g_eth_input = 0;
int g_eth_output = 0;
int g_wifi_input = 0;
int g_wifi_output = 0;
void rt_hw_show_register (struct rt_hw_register *regs)
{
	rt_kprintf("Execption:\n");
	rt_kprintf("r00:0x%08x r01:0x%08x r02:0x%08x r03:0x%08x\n", regs->r0, regs->r1, regs->r2, regs->r3);
	rt_kprintf("r04:0x%08x r05:0x%08x r06:0x%08x r07:0x%08x\n", regs->r4, regs->r5, regs->r6, regs->r7);
	rt_kprintf("r08:0x%08x r09:0x%08x r10:0x%08x\n", regs->r8, regs->r9, regs->r10);
	rt_kprintf("fp :0x%08x ip :0x%08x\n", regs->fp, regs->ip);
	rt_kprintf("sp :0x%08x lr :0x%08x pc :0x%08x\n", regs->sp, regs->lr, regs->pc);
	rt_kprintf("cpsr:0x%08x\n", regs->cpsr);
	rt_kprintf("eth info : in = %d out = %d\n", g_eth_input, g_eth_output);
	rt_kprintf("wifi info: in = %d out = %d\n", g_wifi_input, g_wifi_output);
	_rtt_statistics();
}

/**
 * When ARM7TDMI comes across an instruction which it cannot handle,
 * it takes the undefined instruction trap.
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_udef(struct rt_hw_register *regs)
{
	rt_hw_show_register(regs);

	rt_kprintf("undefined instruction\n");
	rt_kprintf("thread - %s stack:\n", rt_current_thread->name);

#ifdef RT_USING_FINSH
	list_thread();
#endif
	rt_hw_cpu_shutdown();
}

/**
 * The software interrupt instruction (SWI) is used for entering
 * Supervisor mode, usually to request a particular supervisor
 * function.
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_swi(struct rt_hw_register *regs)
{
	rt_hw_show_register(regs);

	rt_kprintf("software interrupt\n");
	rt_hw_cpu_shutdown();
}

/**
 * An abort indicates that the current memory access cannot be completed,
 * which occurs during an instruction prefetch.
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_pabt(struct rt_hw_register *regs)
{
	rt_hw_show_register(regs);

	rt_kprintf("prefetch abort\n");
	rt_kprintf("thread - %s stack:\n", rt_current_thread->name);

#ifdef RT_USING_FINSH
	list_thread();
#endif
	rt_hw_cpu_shutdown();
}

/**
 * An abort indicates that the current memory access cannot be completed,
 * which occurs during a data access.
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_dabt(struct rt_hw_register *regs)
{

	rt_kprintf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	rt_kprintf("data abort\n");
	rt_kprintf("thread - [%s] stack:\n", rt_current_thread->name);

	rt_hw_show_register(regs);

#ifdef RT_USING_FINSH
	list_thread();
#endif
	rt_hw_cpu_shutdown();
}

/**
 * Normally, system will never reach here
 *
 * @param regs system registers
 *
 * @note never invoke this function in application
 */
void rt_hw_trap_resv(struct rt_hw_register *regs)
{
	rt_kprintf("not used\n");
	rt_hw_show_register(regs);
	rt_hw_cpu_shutdown();
}

extern struct rt_irq_desc irq_desc[];

void rt_hw_trap_irq()
{
    int index;
	//rt_kprintf("irq interrupt request\n");
    GD_IRQ_ISR();

	if(gkosHookData)
	{
	    for( index=0; index < gkosHookData->timerFunctionCount; index++ )
	    {
	        if( gkosHookData->timerFunctionArray[index] )
	        {
	            (*gkosHookData->timerFunctionArray[index])(NULL);
	        }
	    }
	}
}

void rt_hw_trap_fiq()
{
	//rt_kprintf("fast interrupt request\n");
	GD_FIQ_ISR();
	//rt_tick_increase();
}

/*@}*/
