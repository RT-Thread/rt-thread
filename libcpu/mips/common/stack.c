/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-04     Jiaxun Yang  Initial version
 */

#include <rtthread.h>

#include "mips.h"

register rt_uint32_t $GP __asm__ ("$28");

rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter, rt_uint8_t *stack_addr, void *texit)
{
    static rt_uint32_t wSR=0;
    static rt_uint32_t wGP;
    rt_uint8_t *stk;

    struct pt_regs *pt;

    rt_uint32_t i;

    /* Get stack aligned */
    stk = (rt_uint8_t *)RT_ALIGN_DOWN((rt_uint32_t)stack_addr, 8);
    stk -= sizeof(struct pt_regs);
    pt =  (struct pt_regs*)stk;

    for (i = 0; i < 8; ++i)
    {
        pt->pad0[i] = 0xdeadbeef;
    }

    /* Fill Stack register numbers */
    for (i = 0; i < 32; ++i)
    {
        pt->regs[i] = 0xdeadbeef;
    }

    pt->regs[REG_SP] = (rt_uint32_t)stk;
    pt->regs[REG_A0] = (rt_uint32_t)parameter;
    pt->regs[REG_GP] = (rt_uint32_t)$GP;
    pt->regs[REG_FP] = (rt_uint32_t)0x0;
    pt->regs[REG_RA] = (rt_uint32_t)texit;

    pt->hi	= 0x0;
    pt->lo	= 0x0;
    pt->cp0_status = (ST0_IE | ST0_CU0 | ST0_IM);
#ifdef RT_USING_FPU
    pt->cp0_status |= (ST0_CU1 | ST0_FR);
#endif
    pt->cp0_cause	= read_c0_cause();
    pt->cp0_epc	= (rt_uint32_t)tentry;
    pt->cp0_badvaddr	= 0x0;

    return stk;
}
