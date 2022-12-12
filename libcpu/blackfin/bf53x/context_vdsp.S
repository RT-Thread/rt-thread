/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author     Notes
 * 2012-02-13   mojingxian First version
 */

.global _rt_hw_interrupt_disable;
.global _rt_hw_interrupt_enable;
.global _interrupt_thread_switch;

.extern _rt_interrupt_from_thread;
.extern _rt_interrupt_to_thread;
.extern _rt_thread_switch_interrupt_flag;

.section/DOUBLE64 program;

/*
 * rt_base_t rt_hw_interrupt_disable();
 * return value in R0.
 */
_rt_hw_interrupt_disable:
    CLI  R0;

_rt_hw_interrupt_disable.end:
    NOP;
    NOP;
    NOP;
    RTS;

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 * R0->level
 */
_rt_hw_interrupt_enable:
    STI  R0;

_rt_hw_interrupt_enable.end:
    NOP;
    NOP;
    NOP;
    RTS;

_interrupt_thread_switch:
    /* Save context, interrupts disabled by IPEND[4] bit */
    [ -- SP ]    = R0;
    [ -- SP ]    = P1;
    [ -- SP ]    = RETS;
    [ -- SP ]    = R1;
    [ -- SP ]    = R2;
    [ -- SP ]    = P0;
    [ -- SP ]    = P2;
    [ -- SP ]    = ASTAT;
    R1           = RETI;                  /* IPEND[4] is currently set, globally disabling interrupts  */
                                          /* IPEND[4] will stay set when RETI is saved through R1      */

    [ -- SP ]    = R1;
    [ -- SP ]    = (R7:3, P5:3);
    [ -- SP ]    = FP;
    [ -- SP ]    = I0;
    [ -- SP ]    = I1;
    [ -- SP ]    = I2;
    [ -- SP ]    = I3;
    [ -- SP ]    = B0;
    [ -- SP ]    = B1;
    [ -- SP ]    = B2;
    [ -- SP ]    = B3;
    [ -- SP ]    = L0;
    [ -- SP ]    = L1;
    [ -- SP ]    = L2;
    [ -- SP ]    = L3;
    [ -- SP ]    = M0;
    [ -- SP ]    = M1;
    [ -- SP ]    = M2;
    [ -- SP ]    = M3;
    R1.L         = A0.x;
    [ -- SP ]    = R1;
    R1           = A0.w;
    [ -- SP ]    = R1;
    R1.L         = A1.x;
    [ -- SP ]    = R1;
    R1           = A1.w;
    [ -- SP ]    = R1;
    [ -- SP ]    = LC0;
    R3           = 0;
    LC0          = R3;
    [ -- SP ]    = LC1;
    R3           = 0;
    LC1          = R3;
    [ -- SP ]    = LT0;
    [ -- SP ]    = LT1;
    [ -- SP ]    = LB0;
    [ -- SP ]    = LB1;

    /* Context save done so save SP in the TCB */
    P1.h         = _rt_interrupt_from_thread;
    P1.l         = _rt_interrupt_from_thread;
    P2           = [ P1 ];
    [ P2 ]       = SP;

    /* clear rt_thread_switch_interrupt_flag to 0 */
    P1.h         = _rt_thread_switch_interrupt_flag;
    P1.l         = _rt_thread_switch_interrupt_flag;
    R0           = 0;
    [ P1 ]       = R0;

    /* Get a pointer to the high ready task's TCB */
    P1.h         = _rt_interrupt_to_thread;
    P1.l         = _rt_interrupt_to_thread;
    P2           = [ P1 ];
    SP           = [ P2 ];

    /* Restoring CPU context and return to task */
    LB1          = [ SP ++ ];
    LB0          = [ SP ++ ];
    LT1          = [ SP ++ ];
    LT0          = [ SP ++ ];
    LC1          = [ SP ++ ];
    LC0          = [ SP ++ ];
    R0           = [ SP ++ ];
    A1           = R0;
    R0           = [ SP ++ ];
    A1.x         = R0.L;
    R0           = [ SP ++ ];
    A0           = R0;
    R0           = [ SP ++ ];
    A0.x         = R0.L;
    M3           = [ SP ++ ];
    M2           = [ SP ++ ];
    M1           = [ SP ++ ];
    M0           = [ SP ++ ];
    L3           = [ SP ++ ];
    L2           = [ SP ++ ];
    L1           = [ SP ++ ];
    L0           = [ SP ++ ];
    B3           = [ SP ++ ];
    B2           = [ SP ++ ];
    B1           = [ SP ++ ];
    B0           = [ SP ++ ];
    I3           = [ SP ++ ];
    I2           = [ SP ++ ];
    I1           = [ SP ++ ];
    I0           = [ SP ++ ];
    FP           = [ SP ++ ];
    (R7:3, P5:3) = [ SP ++ ];
    RETI         = [ SP ++ ];             /* IPEND[4] will stay set when RETI popped from stack        */
    ASTAT        = [ SP ++ ];
    P2           = [ SP ++ ];
    P0           = [ SP ++ ];
    R2           = [ SP ++ ];
    R1           = [ SP ++ ];
    RETS         = [ SP ++ ];
    P1           = [ SP ++ ];
    R0           = [ SP ++ ];

_interrupt_thread_switch.end:
    RTI;

