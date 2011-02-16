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
 * 2010-04-19     fify         rewrite rt_hw_interrupt_disable/enable fuction
 * 2010-04-20     fify         move peripheral ISR to bsp/interrupts.s34 
 *
 * For       : Renesas M16C
 * Toolchain : IAR's EW for M16C v3.401
*/

    RSEG        CSTACK

    RSEG        ISTACK

    RSEG        CODE(1)

    EXTERN    rt_thread_switch_interrput_flag
    EXTERN    rt_interrupt_from_thread
    EXTERN    rt_interrupt_to_thread

    PUBLIC    rt_hw_interrupt_disable
    PUBLIC    rt_hw_interrupt_enable    
    PUBLIC    rt_hw_context_switch_to
    PUBLIC    rt_hw_context_switch
    PUBLIC    rt_hw_context_switch_interrupt
    PUBLIC    os_context_switch

rt_hw_interrupt_disable
    STC      FLG, R0    ;fify 20100419
    FCLR     I
    RTS

rt_hw_interrupt_enable
    LDC      R0, FLG    ;fify 20100419
    RTS
    
    .EVEN
os_context_switch:
    PUSHM    R0,R1,R2,R3,A0,A1,SB,FB
    CMP.W    #0,rt_thread_switch_interrput_flag
    JEQ      exit
    MOV.W    #0, rt_thread_switch_interrput_flag
    MOV.W    rt_interrupt_from_thread, A0
    STC      ISP, [A0]    
    MOV.W    rt_interrupt_to_thread, A0
    LDC      [A0], ISP
exit
    POPM     R0,R1,R2,R3,A0,A1,SB,FB             ; Restore registers from the new task's stack
    REIT                                         ; Return from interrup    
    
/*
 * void rt_hw_context_switch_to(rt_uint32 to);
 * r0 --> to
 * this fucntion is used to perform the first thread switch
 */
rt_hw_context_switch_to
    MOV.W    R0, A0
    LDC      [A0], ISP
    POPM     R0,R1,R2,R3,A0,A1,SB,FB
    REIT

rt_hw_context_switch
    CMP.W    #1,rt_thread_switch_interrput_flag
    JEQ      jump1
    MOV.W    #1,rt_thread_switch_interrput_flag
    MOV.W    R0, rt_interrupt_from_thread
jump1
    MOV.W    R1, rt_interrupt_to_thread
    INT      #0
    RTS
  
rt_hw_context_switch_interrupt
    CMP.W    #1,rt_thread_switch_interrput_flag
    JEQ      jump
    MOV.W    #1,rt_thread_switch_interrput_flag
    MOV.W    R0, rt_interrupt_from_thread
jump
    MOV.W    R1, rt_interrupt_to_thread
    RTS

    END
