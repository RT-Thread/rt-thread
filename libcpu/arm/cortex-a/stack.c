/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-09-23     Bernard      the first version
 * 2011-10-05     Bernard      add thumb mode
 */
#include <rtthread.h>
#include <cpuport.h>
#include <board.h>

/**
 * @addtogroup ARM Cortex-A
 */
/*@{*/

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
rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter,
                             rt_uint8_t *stack_addr, void *texit)
{
    rt_uint32_t *stk;

    stack_addr += sizeof(rt_uint32_t);
    stack_addr  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_uint32_t)stack_addr, 8);
    stk      = (rt_uint32_t *)stack_addr;
    *(--stk) = (rt_uint32_t)_thread_start;  /* entry point */
    *(--stk) = (rt_uint32_t)texit;          /* lr */
    *(--stk) = 0xdeadbeef;                  /* r12 */
    *(--stk) = 0xdeadbeef;                  /* r11 */
    *(--stk) = 0xdeadbeef;                  /* r10 */
    *(--stk) = 0xdeadbeef;                  /* r9 */
    *(--stk) = 0xdeadbeef;                  /* r8 */
    *(--stk) = 0xdeadbeef;                  /* r7 */
    *(--stk) = 0xdeadbeef;                  /* r6 */
    *(--stk) = 0xdeadbeef;                  /* r5 */
    *(--stk) = 0xdeadbeef;                  /* r4 */
    *(--stk) = 0xdeadbeef;                  /* r3 */
    *(--stk) = 0xdeadbeef;                  /* r2 */
    *(--stk) = (rt_uint32_t)tentry;         /* r1 : argument 2 for trampoline */
    *(--stk) = (rt_uint32_t)parameter;      /* r0 : argument 1 */
    /* cpsr */
    if ((rt_uint32_t)tentry & 0x01)
        *(--stk) = SVCMODE | 0x20;          /* thumb mode */
    else
        *(--stk) = SVCMODE;                 /* arm mode   */

#ifdef RT_USING_SMART
    *(--stk) = 0;       /* user lr */
    *(--stk) = 0;       /* user sp*/
#endif
#ifdef RT_USING_FPU
    /* FPU context initialization matches context_gcc.S restore order:
     * Stack layout (high to low): FPEXC -> FPSCR -> D16-D31 -> D0-D15
     */
    stk -= VFP_DATA_NR;
    rt_memset(stk, 0, VFP_DATA_NR * sizeof(rt_uint32_t));  /* Initialize D0-D31 (64 words for 32 double regs) */
    *(--stk) = 0;       /* FPSCR: Floating-Point Status and Control Register */
    *(--stk) = 0x40000000;  /* FPEXC: Enable FPU (bit 30 = EN) */
#endif

    /* return task's current stack address */
    return (rt_uint8_t *)stk;
}

/*@}*/
