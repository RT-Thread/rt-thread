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

    PUBLIC  rt_hw_timer_handler
    PUBLIC  rt_hw_uart0_receive_handler

    EXTERN  rt_thread_switch_interrupt_flag
    EXTERN  rt_interrupt_from_thread
    EXTERN  rt_interrupt_to_thread
    EXTERN  rt_interrupt_enter
    EXTERN  rt_interrupt_leave
    EXTERN  rt_tick_increase
    EXTERN  u0rec_handler

    RSEG    CSTACK
    RSEG    ISTACK
    RSEG    CODE:CODE:NOROOT(2)

rt_hw_context_switch_interrupt_do
    MOV.B   #0, rt_thread_switch_interrupt_flag
    MOV.W   rt_interrupt_from_thread, A0
    STC     ISP, [A0]

    MOV.W   rt_interrupt_to_thread, A0
    LDC     [A0], ISP
    POPM    R0,R1,R2,R3,A0,A1,SB,FB             ; Restore all processor registers from the new task's stack
    REIT

    .EVEN
rt_hw_timer_handler:
    PUSHM   R0,R1,R2,R3,A0,A1,SB,FB             ; Save current task's registers
    JSR     rt_interrupt_enter
    JSR     rt_tick_increase
    JSR     rt_interrupt_leave

    CMP.B   #1, rt_thread_switch_interrupt_flag
    JEQ     rt_hw_context_switch_interrupt_do

    POPM    R0,R1,R2,R3,A0,A1,SB,FB             ; Restore current task's registers
    REIT                                        ; Return from interrup

    .EVEN
rt_hw_uart0_receive_handler:
    PUSHM   R0,R1,R2,R3,A0,A1,SB,FB             ; Save current task's registers
    JSR     rt_interrupt_enter
    JSR     u0rec_handler
    JSR     rt_interrupt_leave

    CMP.B   #1, rt_thread_switch_interrupt_flag
    JEQ     rt_hw_context_switch_interrupt_do

    POPM    R0,R1,R2,R3,A0,A1,SB,FB             ; Restore current task's registers
    REIT                                        ; Return from interrup

    END
