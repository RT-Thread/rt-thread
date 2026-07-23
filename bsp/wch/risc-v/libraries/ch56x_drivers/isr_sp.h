/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-27     Emuzit            first version
 */
#ifndef __ISR_SP_H__
#define __ISR_SP_H__

/* usrstack is no more in use right after rt_system_scheduler_start().
 * It is also the time global interrupt is enabled.
*/
#define isr_sp_enter() \
        asm("la   t0, rt_interrupt_nest"); \
        asm("bnez t0, 1f"); \
        asm("la   t0, _eusrstack"); \
        asm("sw   sp, -4(t0)"); \
        asm("addi sp, t0, -4"); \
        asm("1:")

#define isr_sp_leave() \
        asm("la   t0, rt_interrupt_nest"); \
        asm("bnez t0, 1f"); \
        asm("la   t0, _eusrstack"); \
        asm("lw   sp, -4(t0)"); \
        asm("1:")

#endif
