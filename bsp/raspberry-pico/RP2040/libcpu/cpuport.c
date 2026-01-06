/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-01-25     Bernard      first version
 * 2012-05-31     aozima       Merge all of the C source code into cpuport.c
 * 2012-08-17     aozima       fixed bug: store r8 - r11.
 * 2012-12-23     aozima       stack addr align to 8byte.
 * 2023-01-22     rose_man     add RT_USING_SMP
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtthread.h>
#include <stdint.h>

#include "board.h"

#ifdef RT_USING_SMP

#include "hardware/structs/sio.h"
#include "hardware/irq.h"
#include "pico/sync.h"
#include "pico/multicore.h"

int rt_hw_cpu_id(void)
{
    return sio_hw->cpuid;
}

void rt_hw_spin_lock_init(rt_hw_spinlock_t *lock)
{
    static uint8_t spin_cnt = 0;

    if ( spin_cnt < 32)
    {
        lock->slock = (rt_uint32_t)spin_lock_instance(spin_cnt);
        spin_cnt = spin_cnt + 1;
    }
    else
    {
        lock->slock = 0;
    }
}

void rt_hw_spin_lock(rt_hw_spinlock_t *lock)
{
    if ( lock->slock != 0 )
    {
        spin_lock_unsafe_blocking((spin_lock_t*)lock->slock);
    }
}

void rt_hw_spin_unlock(rt_hw_spinlock_t *lock)
{
    if ( lock->slock != 0 )
    {
        spin_unlock_unsafe((spin_lock_t*)lock->slock);
    }
}

void secondary_cpu_c_start(void)
{
    irq_set_enabled(SIO_IRQ_PROC1,RT_TRUE);

    extern uint32_t systick_config(uint32_t ticks);
    systick_config(frequency_count_khz(CLOCKS_FC0_SRC_VALUE_ROSC_CLKSRC)*10000/RT_TICK_PER_SECOND);

    rt_hw_spin_lock(&_cpus_lock);

    rt_system_scheduler_start();
}

void rt_hw_secondary_cpu_up(void)
{
    multicore_launch_core1(secondary_cpu_c_start);

    irq_set_enabled(SIO_IRQ_PROC0,RT_TRUE);
}

void rt_hw_secondary_cpu_idle_exec(void)
{
    asm volatile ("wfi");
}

#define IPI_MAGIC 0x5a5a

void rt_hw_ipi_send(int ipi_vector, unsigned int cpu_mask)
{
    sio_hw->fifo_wr = IPI_MAGIC;
}

void rt_hw_ipi_handler(void)
{
    uint32_t status = sio_hw->fifo_st;

    if ( status & (SIO_FIFO_ST_ROE_BITS | SIO_FIFO_ST_WOF_BITS) )
    {
        sio_hw->fifo_st = 0;
    }

    if ( status & SIO_FIFO_ST_VLD_BITS )
    {
        if ( sio_hw->fifo_rd == IPI_MAGIC )
        {
            //rt_schedule();
        }
    }
}

void isr_irq15(void)
{
    rt_hw_ipi_handler();
}

void isr_irq16(void)
{
    rt_hw_ipi_handler();
}
struct __rt_thread_switch_array
{
    rt_ubase_t flag;
    rt_ubase_t from;
    rt_ubase_t to;
};
struct __rt_thread_switch_array rt_thread_switch_array[2] = { {0,0,0}, {0,0,0} };

void __rt_cpu_switch(rt_ubase_t from, rt_ubase_t to, struct rt_thread *thread)
{
    struct rt_cpu* pcpu = rt_cpu_self();
    rt_uint32_t   cpuid = rt_hw_cpu_id();

    if ( rt_thread_switch_array[cpuid].flag != 1)
    {
        rt_thread_switch_array[cpuid].flag  = 1;
        rt_thread_switch_array[cpuid].from = from;
    }
    rt_thread_switch_array[cpuid].to = to;

    if ( pcpu->current_thread != RT_NULL )
    {
        thread->cpus_lock_nest      = pcpu->current_thread->cpus_lock_nest;
        thread->critical_lock_nest  = pcpu->current_thread->critical_lock_nest;
        thread->scheduler_lock_nest = pcpu->current_thread->scheduler_lock_nest;
    }

    pcpu->current_thread = thread;
    if (!thread->cpus_lock_nest)
    {
        rt_hw_spin_unlock(&_cpus_lock);
    }
}

#endif /*RT_USING_SMP*/

struct exception_stack_frame
{
    rt_uint32_t r0;
    rt_uint32_t r1;
    rt_uint32_t r2;
    rt_uint32_t r3;
    rt_uint32_t r12;
    rt_uint32_t lr;
    rt_uint32_t pc;
    rt_uint32_t psr;
};

struct stack_frame
{
    /* r4 ~ r7 low register */
    rt_uint32_t r4;
    rt_uint32_t r5;
    rt_uint32_t r6;
    rt_uint32_t r7;

    /* r8 ~ r11 high register */
    rt_uint32_t r8;
    rt_uint32_t r9;
    rt_uint32_t r10;
    rt_uint32_t r11;

    struct exception_stack_frame exception_stack_frame;
};

/* flag in interrupt handling */
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

/**
 * This function will initialize thread stack
 *
 * @param tentry the entry of thread
 * @param parameter the parameter of entry
 * @param stack_addr the beginning stack address
 * @param texit the function will be called when thread exit
 *
 * @return stack address
 */
rt_uint8_t *rt_hw_stack_init(void       *tentry,
                             void       *parameter,
                             rt_uint8_t *stack_addr,
                             void       *texit)
{
    struct stack_frame *stack_frame;
    rt_uint8_t         *stk;
    unsigned long       i;

    stk  = stack_addr + sizeof(rt_uint32_t);
    stk  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_uint32_t)stk, 8);
    stk -= sizeof(struct stack_frame);

    stack_frame = (struct stack_frame *)stk;

    /* init all register */
    for (i = 0; i < sizeof(struct stack_frame) / sizeof(rt_uint32_t); i ++)
    {
        ((rt_uint32_t *)stack_frame)[i] = 0xdeadbeef;
    }

    stack_frame->exception_stack_frame.r0  = (unsigned long)parameter; /* r0 : argument */
    stack_frame->exception_stack_frame.r1  = 0;                        /* r1 */
    stack_frame->exception_stack_frame.r2  = 0;                        /* r2 */
    stack_frame->exception_stack_frame.r3  = 0;                        /* r3 */
    stack_frame->exception_stack_frame.r12 = 0;                        /* r12 */
    stack_frame->exception_stack_frame.lr  = (unsigned long)texit;     /* lr */
    stack_frame->exception_stack_frame.pc  = (unsigned long)tentry;    /* entry point, pc */
    stack_frame->exception_stack_frame.psr = 0x01000000L;              /* PSR */

    /* return task's current stack address */
    return stk;
}

#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
extern long list_thread(void);
#endif
extern rt_thread_t rt_current_thread;
/**
 * fault exception handling
 */
void rt_hw_hard_fault_exception(struct exception_stack_frame *contex)
{
    rt_kprintf("psr: 0x%08x\n", contex->psr);
    rt_kprintf(" pc: 0x%08x\n", contex->pc);
    rt_kprintf(" lr: 0x%08x\n", contex->lr);
    rt_kprintf("r12: 0x%08x\n", contex->r12);
    rt_kprintf("r03: 0x%08x\n", contex->r3);
    rt_kprintf("r02: 0x%08x\n", contex->r2);
    rt_kprintf("r01: 0x%08x\n", contex->r1);
    rt_kprintf("r00: 0x%08x\n", contex->r0);

#ifdef RT_USING_SMP
    rt_thread_t rt_current_thread = rt_thread_self();
    rt_kprintf("hard fault on cpu : %d on thread: %s\n", rt_current_thread->oncpu, rt_current_thread->parent.name);
#else
    rt_kprintf("hard fault on thread: %s\n", rt_current_thread->parent.name);
#endif
#if defined(RT_USING_FINSH) && defined(MSH_USING_BUILT_IN_COMMANDS)
    list_thread();
#endif

    while (1);
}

#define SCB_CFSR        (*(volatile const unsigned *)0xE000ED28) /* Configurable Fault Status Register */
#define SCB_HFSR        (*(volatile const unsigned *)0xE000ED2C) /* HardFault Status Register */
#define SCB_MMAR        (*(volatile const unsigned *)0xE000ED34) /* MemManage Fault Address register */
#define SCB_BFAR        (*(volatile const unsigned *)0xE000ED38) /* Bus Fault Address Register */
#define SCB_AIRCR       (*(volatile unsigned long *)0xE000ED0C)  /* Reset control Address Register */
#define SCB_RESET_VALUE 0x05FA0004                               /* Reset value, write to SCB_AIRCR can reset cpu */

#define SCB_CFSR_MFSR   (*(volatile const unsigned char*)0xE000ED28)  /* Memory-management Fault Status Register */
#define SCB_CFSR_BFSR   (*(volatile const unsigned char*)0xE000ED29)  /* Bus Fault Status Register */
#define SCB_CFSR_UFSR   (*(volatile const unsigned short*)0xE000ED2A) /* Usage Fault Status Register */

/**
 * reset CPU
 */
void rt_hw_cpu_reset(void)
{
    SCB_AIRCR  = SCB_RESET_VALUE;//((0x5FAUL << SCB_AIRCR_VECTKEY_Pos) |SCB_AIRCR_SYSRESETREQ_Msk);
}
