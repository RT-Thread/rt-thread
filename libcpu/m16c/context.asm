/*
 * File      : context.asm
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-04-09     fify         the first version
 *
 * For       : Renesas M16C
 * Toolchain : IAR's EW for M16C v3.401
*/

;********************************************************************************************************
;                                           PUBLIC FUNCTIONS
;********************************************************************************************************

    RSEG        CSTACK

    RSEG        ISTACK

    RSEG        CODE(1)

    EXTERN    rt_thread_switch_interrput_flag
    EXTERN    rt_interrupt_from_thread
    EXTERN    rt_interrupt_to_thread
    EXTERN    rt_interrupt_enter
    EXTERN    rt_tick_increase
    EXTERN    rt_interrupt_leave
    EXTERN    u0rec_handler

    PUBLIC    rt_hw_interrupt_disable
    PUBLIC    rt_hw_interrupt_enable    
    PUBLIC    rt_hw_context_switch_to
    PUBLIC    rt_hw_context_switch
    PUBLIC    rt_hw_context_switch_interrupt
    PUBLIC    rt_hw_timer_handler
    PUBLIC    rt_hw_uart0_receive_handler

rt_hw_interrupt_disable
    FCLR    I
    RTS

rt_hw_interrupt_enable
    FSET    I
    RTS
    
;/*
; * void rt_hw_context_switch_to(rt_uint32 to);
; * r0 --> to
; * this fucntion is used to perform the first thread switch
; */
rt_hw_context_switch_to
    MOV.W   R0, A0
    LDC     [A0], ISP
    POPM    R0,R1,R2,R3,A0,A1,SB,FB
    REIT

rt_hw_context_switch
    PUSHM    R0,R1,R2,R3,A0,A1,SB,FB 
    MOV.W    R0, A0
    STC      ISP, [A0]
    MOV.W    R1, A0
    LDC      [A0], ISP
    POPM     R0,R1,R2,R3,A0,A1,SB,FB         ; Restore all processor registers from the new task's stack
    REIT
  
rt_hw_context_switch_interrupt
    CMP.W    #1,rt_thread_switch_interrput_flag
    JEQ      jump
    MOV.W    #1,rt_thread_switch_interrput_flag
    MOV.W    R0, rt_interrupt_from_thread
jump
    MOV.W    R1, rt_interrupt_to_thread
    RTS

rt_hw_context_switch_interrupt_do
    MOV.W    #0, rt_thread_switch_interrput_flag    
    MOV.W    rt_interrupt_from_thread, A0
    STC      ISP, [A0]    
    
    MOV.W    rt_interrupt_to_thread, A0
    LDC      [A0], ISP
    POPM     R0,R1,R2,R3,A0,A1,SB,FB         ; Restore all processor registers from the new task's stack
    RTS                                      ; Normal return
    
    .EVEN
rt_hw_timer_handler:
    PUSHM    R0,R1,R2,R3,A0,A1,SB,FB             ; Save current task's registers
    JSR      rt_interrupt_enter                   
    JSR      rt_tick_increase                           
    JSR      rt_interrupt_leave

    CMP.W    #1,rt_thread_switch_interrput_flag
    JEQ      rt_hw_context_switch_interrupt_do
    
    POPM     R0,R1,R2,R3,A0,A1,SB,FB             ; Restore registers from the new task's stack
    REIT                                         ; Return from interrup

    .EVEN
rt_hw_uart0_receive_handler:
    PUSHM    R0,R1,R2,R3,A0,A1,SB,FB             ; Save current task's registers
    JSR      rt_interrupt_enter 
    JSR      u0rec_handler                         
    JSR      rt_interrupt_leave

    CMP.W    #1, rt_thread_switch_interrput_flag
    JEQ      rt_hw_context_switch_interrupt_do
    
    POPM     R0,R1,R2,R3,A0,A1,SB,FB             ; Restore registers from the new task's stack
    REIT                                         ; Return from interrup

    END
