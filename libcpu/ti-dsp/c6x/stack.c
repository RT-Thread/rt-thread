/*
 * Copyright (c) 2021, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-16     Dystopia     the first version
 */

#include <rtthread.h>
#include <c66xx.h>

extern rt_uint32_t rt_hw_get_current_dp(void);

/**
 * @addtogroup C66xx
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
    rt_hw_thread_stack_register *thread_context = RT_NULL;
    rt_uint32_t stk = 0;

    stack_addr += sizeof(rt_uint32_t);
    stack_addr  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_uint32_t)stack_addr, 8);
    stk         = (rt_uint32_t)stack_addr;
    thread_context = (rt_hw_thread_stack_register *)(stk - sizeof(rt_hw_thread_stack_register));

    thread_context->pc = (rt_uint32_t)tentry;
    thread_context->csr = 0x0103;
    thread_context->tsr = 0x3;
    thread_context->orig_a4 = 1;
    thread_context->ilc = 0;
    thread_context->rilc = 0;

    thread_context->hw_register.b17 = 0xB17;
    thread_context->hw_register.b16  = 0xB16;
    thread_context->hw_register.b19  = 0xB19;
    thread_context->hw_register.b18  = 0xB18;
    thread_context->hw_register.b21  = 0xB21;
    thread_context->hw_register.b20  = 0xB20;
    thread_context->hw_register.b23  = 0xB23;
    thread_context->hw_register.b22  = 0xB22;
    thread_context->hw_register.b25  = 0xB25;
    thread_context->hw_register.b24  = 0xB24;
    thread_context->hw_register.b27  = 0xB27;
    thread_context->hw_register.b26  = 0xB26;
    thread_context->hw_register.b29  = 0xB29;
    thread_context->hw_register.b28  = 0xB28;
    thread_context->hw_register.b31  = 0xB31;
    thread_context->hw_register.b30  = 0xB30;

    thread_context->hw_register.b1  = 0xB01;
    thread_context->hw_register.b0  = 0xB00;
    thread_context->hw_register.b3  = (rt_uint32_t)texit;
    thread_context->hw_register.b2  = 0xB02;
    thread_context->hw_register.b5  = 0xB05;
    thread_context->hw_register.b4  = 0xB04;
    thread_context->hw_register.b7  = 0xB07;
    thread_context->hw_register.b6  = 0xB06;
    thread_context->hw_register.b9  = 0xB09;
    thread_context->hw_register.b8  = 0xB08;
    thread_context->hw_register.b11  = 0xB11;
    thread_context->hw_register.b10  = 0xB10;
    thread_context->hw_register.b13  = 0xB13;
    thread_context->hw_register.b12  = 0xB12;

    thread_context->hw_register.a17  = 0xA17;
    thread_context->hw_register.a16  = 0xA16;
    thread_context->hw_register.a19  = 0xA19;
    thread_context->hw_register.a18  = 0xA18;
    thread_context->hw_register.a21  = 0xA21;
    thread_context->hw_register.a20  = 0xA20;
    thread_context->hw_register.a23  = 0xA23;
    thread_context->hw_register.a22  = 0xA22;
    thread_context->hw_register.a25  = 0xA25;
    thread_context->hw_register.a24  = 0xA24;
    thread_context->hw_register.a27  = 0xA27;
    thread_context->hw_register.a26  = 0xA26;
    thread_context->hw_register.a29  = 0xA29;
    thread_context->hw_register.a28  = 0xA28;
    thread_context->hw_register.a31  = 0xA31;
    thread_context->hw_register.a30  = 0xA30;

    thread_context->hw_register.a1  = 0xA01;
    thread_context->hw_register.a0  = 0xA00;
    thread_context->hw_register.a3  = 0xA03;
    thread_context->hw_register.a2  = 0xA02;
    thread_context->hw_register.a5  = 0xA05;
    thread_context->hw_register.a4  = (rt_uint32_t)parameter;
    thread_context->hw_register.a7  = 0xA07;
    thread_context->hw_register.a6  = 0xA06;
    thread_context->hw_register.a9  = 0xA09;
    thread_context->hw_register.a8  = 0xA08;
    thread_context->hw_register.a11  = 0xA11;
    thread_context->hw_register.a10  = 0xA10;
    thread_context->hw_register.a13  = 0xA13;
    thread_context->hw_register.a12  = 0xA12;

    thread_context->hw_register.a15  = 0xA15;
    thread_context->hw_register.a14  = 0xA14;
    thread_context->hw_register.dp  = rt_hw_get_current_dp();
    thread_context->hw_register.sp  = (rt_uint32_t)stk;

    /* return task's current stack address */
    return (rt_uint8_t *)thread_context - 8;
}
