/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 * Copyright (c) 2019-Present Nuclei Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/03/26     Huaqi        Nuclei RISC-V Core porting code.
 */

#include <rthw.h>
#include <rtthread.h>
#include <sys/types.h>
#include <unistd.h>

#include "cpuport.h"

#define SYSTICK_TICK_CONST                      (SOC_TIMER_FREQ / RT_TICK_PER_SECOND)

/* Interrupt level for kernel systimer interrupt and software timer interrupt */
#define RT_KERNEL_INTERRUPT_LEVEL               0

/* Initial CSR MSTATUS value when thread created */
#define RT_INITIAL_MSTATUS                      (MSTATUS_MPP | MSTATUS_MPIE | MSTATUS_FS_INITIAL)

/**
 * @brief from thread used interrupt context switch
 *
 */
volatile rt_ubase_t  rt_interrupt_from_thread = 0;
/**
 * @brief to thread used interrupt context switch
 *
 */
volatile rt_ubase_t  rt_interrupt_to_thread   = 0;
/**
 * @brief flag to indicate context switch in interrupt or not
 *
 */
volatile rt_ubase_t rt_thread_switch_interrupt_flag = 0;

/**
 * @brief thread stack frame of saved context
 *
 */
struct rt_hw_stack_frame
{
    rt_ubase_t epc;        /*!< epc - epc    - program counter                     */
    rt_ubase_t ra;         /*!< x1  - ra     - return address for jumps            */
    rt_ubase_t t0;         /*!< x5  - t0     - temporary register 0                */
    rt_ubase_t t1;         /*!< x6  - t1     - temporary register 1                */
    rt_ubase_t t2;         /*!< x7  - t2     - temporary register 2                */
    rt_ubase_t s0_fp;      /*!< x8  - s0/fp  - saved register 0 or frame pointer   */
    rt_ubase_t s1;         /*!< x9  - s1     - saved register 1                    */
    rt_ubase_t a0;         /*!< x10 - a0     - return value or function argument 0 */
    rt_ubase_t a1;         /*!< x11 - a1     - return value or function argument 1 */
    rt_ubase_t a2;         /*!< x12 - a2     - function argument 2                 */
    rt_ubase_t a3;         /*!< x13 - a3     - function argument 3                 */
    rt_ubase_t a4;         /*!< x14 - a4     - function argument 4                 */
    rt_ubase_t a5;         /*!< x15 - a5     - function argument 5                 */
#ifndef __riscv_32e
    rt_ubase_t a6;         /*!< x16 - a6     - function argument 6                 */
    rt_ubase_t a7;         /*!< x17 - s7     - function argument 7                 */
    rt_ubase_t s2;         /*!< x18 - s2     - saved register 2                    */
    rt_ubase_t s3;         /*!< x19 - s3     - saved register 3                    */
    rt_ubase_t s4;         /*!< x20 - s4     - saved register 4                    */
    rt_ubase_t s5;         /*!< x21 - s5     - saved register 5                    */
    rt_ubase_t s6;         /*!< x22 - s6     - saved register 6                    */
    rt_ubase_t s7;         /*!< x23 - s7     - saved register 7                    */
    rt_ubase_t s8;         /*!< x24 - s8     - saved register 8                    */
    rt_ubase_t s9;         /*!< x25 - s9     - saved register 9                    */
    rt_ubase_t s10;        /*!< x26 - s10    - saved register 10                   */
    rt_ubase_t s11;        /*!< x27 - s11    - saved register 11                   */
    rt_ubase_t t3;         /*!< x28 - t3     - temporary register 3                */
    rt_ubase_t t4;         /*!< x29 - t4     - temporary register 4                */
    rt_ubase_t t5;         /*!< x30 - t5     - temporary register 5                */
    rt_ubase_t t6;         /*!< x31 - t6     - temporary register 6                */
#endif
    rt_ubase_t mstatus;    /*!<              - machine status register             */
};

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
    struct rt_hw_stack_frame *frame;
    rt_uint8_t         *stk;
    int                i;

    stk  = stack_addr + sizeof(rt_ubase_t);
    stk  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_ubase_t)stk, REGBYTES);
    stk -= sizeof(struct rt_hw_stack_frame);

    frame = (struct rt_hw_stack_frame *)stk;

    for (i = 0; i < sizeof(struct rt_hw_stack_frame) / sizeof(rt_ubase_t); i++)
    {
        ((rt_ubase_t *)frame)[i] = 0xdeadbeef;
    }

    frame->ra      = (rt_ubase_t)texit;
    frame->a0      = (rt_ubase_t)parameter;
    frame->epc     = (rt_ubase_t)tentry;

    frame->mstatus = RT_INITIAL_MSTATUS;

    return stk;
}

/**
 * @brief Do rt-thread context switch in interrupt context
 *
 * @param from thread sp of from thread
 * @param to thread sp of to thread
 */
void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to)
{
    if (rt_thread_switch_interrupt_flag == 0)
        rt_interrupt_from_thread = from;

    rt_interrupt_to_thread = to;
    rt_thread_switch_interrupt_flag = 1;
    RT_YIELD();
}

/**
 * @brief Do rt-thread context switch in task context
 *
 * @param from thread sp of from thread
 * @param to thread sp of to thread
 */
void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to)
{
    rt_hw_context_switch_interrupt(from, to);
}

/**
 * @brief shutdown CPU
 *
 */
RT_WEAK void rt_hw_cpu_shutdown()
{
    rt_base_t level;
    rt_kprintf("shutdown...\n");

    level = rt_hw_interrupt_disable();
    while (level)
    {
        RT_ASSERT(0);
    }
}

/**
 * @brief Do extra task switch code
 *
 * @details
 *
 * - Clear software timer interrupt request flag
 * - clear rt_thread_switch_interrupt_flag to 0
 */
void rt_hw_taskswitch(void)
{
    /* Clear Software IRQ, A MUST */
    SysTimer_ClearSWIRQ();
    rt_thread_switch_interrupt_flag = 0;
}

/**
 * @brief Setup systimer and software timer interrupt
 *
 * @details
 *
 * - Set Systimer interrupt as NON-VECTOR interrupt with lowest interrupt level
 * - Set software timer interrupt as VECTOR interrupt with lowest interrupt level
 * - Enable these two interrupts
 */
void rt_hw_ticksetup(void)
{
    uint64_t ticks = SYSTICK_TICK_CONST;

    /* Make SWI and SysTick the lowest priority interrupts. */
    /* Stop and clear the SysTimer. SysTimer as Non-Vector Interrupt */
    SysTick_Config(ticks);
    ECLIC_DisableIRQ(SysTimer_IRQn);
    ECLIC_SetLevelIRQ(SysTimer_IRQn, RT_KERNEL_INTERRUPT_LEVEL);
    ECLIC_SetShvIRQ(SysTimer_IRQn, ECLIC_NON_VECTOR_INTERRUPT);
    ECLIC_EnableIRQ(SysTimer_IRQn);

    /* Set SWI interrupt level to lowest level/priority, SysTimerSW as Vector Interrupt */
    ECLIC_SetShvIRQ(SysTimerSW_IRQn, ECLIC_VECTOR_INTERRUPT);
    ECLIC_SetLevelIRQ(SysTimerSW_IRQn, RT_KERNEL_INTERRUPT_LEVEL);
    ECLIC_EnableIRQ(SysTimerSW_IRQn);
}

/**
 * systimer interrupt handler eclic_mtip_handler
 * is hard coded in startup_<Device>.S
 * We define SysTick_Handler as eclic_mtip_handler
 * for easy understanding
 */
#define SysTick_Handler     eclic_mtip_handler

/**
 * @brief This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* Reload systimer */
    SysTick_Reload(SYSTICK_TICK_CONST);

    /* enter interrupt */
    rt_interrupt_enter();

    /* tick increase */
    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * @brief Disable cpu interrupt
 *
 * @details
 *
 * - Disable cpu interrupt by clear MIE bit in MSTATUS
 * - Return the previous value in MSTATUS before clear MIE bit
 *
 * @return the previous value in MSTATUS before clear MIE bit
 */
rt_base_t rt_hw_interrupt_disable(void)
{
    return __RV_CSR_READ_CLEAR(CSR_MSTATUS, MSTATUS_MIE);
}

/**
 * @brief Restore previous saved interrupt status
 *
 * @param level previous saved MSTATUS value
 */
void rt_hw_interrupt_enable(rt_base_t level)
{
    __RV_CSR_WRITE(CSR_MSTATUS, level);
}
