/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-04-20     fify         the first version
 *
 * For       : Renesas M16C
 * Toolchain : IAR's EW for M16C v3.401
 */

    .text

    .globl  _rt_hw_context_switch_interrupt_do
    .type   _rt_hw_context_switch_interrupt_do, #function
_rt_hw_context_switch_interrupt_do:
    MOV.B   #0, _rt_thread_switch_interrupt_flag
    MOV.W   _rt_interrupt_from_thread, A0
    STC     ISP, [A0]

    MOV.W   _rt_interrupt_to_thread, A0
    LDC     [A0], ISP
    POPM    R0,R1,R2,R3,A0,A1,SB,FB             ; Restore all processor registers from the new task's stack
    REIT

    .text
    .globl  _rt_hw_timer_handler
    .type   _rt_hw_timer_handler, #function
_rt_hw_timer_handler:
    PUSHM   R0,R1,R2,R3,A0,A1,SB,FB             ; Save current task's registers
    jsr.a     _rt_interrupt_enter
    jsr.a     _rt_tick_increase
    jsr.a     _rt_interrupt_leave

    CMP.B   #1, _rt_thread_switch_interrupt_flag
    JEQ     _rt_hw_context_switch_interrupt_do

    POPM    R0,R1,R2,R3,A0,A1,SB,FB             ; Restore current task's registers
    REIT                                        ; Return from interrup

    .text
    .globl  _rt_hw_uart0_receive_handler
    .type   _rt_hw_uart0_receive_handler, #function
_rt_hw_uart0_receive_handler:
    PUSHM   R0,R1,R2,R3,A0,A1,SB,FB             ; Save current task's registers
    jsr.a     _rt_interrupt_enter
    jsr.a     _u0rec_handler
    jsr.a     _rt_interrupt_leave

    CMP.B   #1, _rt_thread_switch_interrupt_flag
    JEQ     _rt_hw_context_switch_interrupt_do

    POPM    R0,R1,R2,R3,A0,A1,SB,FB             ; Restore current task's registers
    REIT                                        ; Return from interrup

