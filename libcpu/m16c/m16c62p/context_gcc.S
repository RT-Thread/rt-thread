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
 */

    .section .text
  
    .globl _rt_interrupt_from_thread
    .globl _rt_interrupt_to_thread
    .global	_os_context_switch
    .type	_os_context_switch, @function
_os_context_switch:
    PUSHM   R0,R1,R2,R3,A0,A1,SB,FB
    
    MOV.W   _rt_interrupt_from_thread, A0
    STC     ISP, [A0]
    MOV.W   _rt_interrupt_to_thread, A0
    LDC     [A0], ISP

    POPM    R0,R1,R2,R3,A0,A1,SB,FB             ; Restore registers from the new task's stack
    REIT                                        ; Return from interrup    
    
/*
 * void rt_hw_context_switch_to(rt_uint32 to);
 * this fucntion is used to perform the first thread switch
 */
    .global	_rt_hw_context_switch_to
    .type	_rt_hw_context_switch_to, @function
_rt_hw_context_switch_to:
    ENTER   #0x0
    MOV.W   0x5[FB], A0
    LDC     [A0], ISP
    POPM    R0,R1,R2,R3,A0,A1,SB,FB
    REIT

    .end
