/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
  
/*!
 * @file startup.s
 * @brief this file contains startup code with support for multi-core startup
 */

#include "asm_defines.h"

    // External symbol references
    .global top_of_stacks
    .global vectors
    .global __ram_vectors_start
    .global __ram_vectors_end
    .global __bss_start__
    .global __bss_end__
    .global main
    .global _sys_exit
    
    .code 32
    .section ".startup","ax"
    
    .global _start
    .func _start 
    .fnstart
_start:
    @ save r0 for cores 1-3, r0 arg field passed by ROM
    @ r0 is a function pointer for secondary cpus
    mov 	r4, r0

    @ clear some registers
    mov     r11,#0
    mov     r12,#0
    mov     lr,#0
    
    ldr		r0, =top_of_stacks  @ symbol defined in linker file
    mov		r1, #EXCEPTION_STACK_SIZE

    @ get cpu id, and subtract the offset from the stacks base address
    mrc     p15,0,r2,c0,c0,5  @ read multiprocessor affinity register
    and     r2, r2, #3        @ mask off, leaving CPU ID field
    mov     r5, r2		      @ save cpu id for later
    
    mul     r3, r2, r1
    sub     r0, r0, r3
  
    mov     r1, r1, lsl #2
           
    @ set stacks for all other modes 
    msr     CPSR_c, #MODE_FIQ | I_BIT | F_BIT
    mov     sp, r0
    sub     r0, r0, r1 
    
    msr     CPSR_c, #MODE_IRQ | I_BIT | F_BIT
    mov     sp, r0
    sub     r0, r0, r1 
    
    msr     CPSR_c, #MODE_ABT | I_BIT | F_BIT
    mov     sp, r0
    sub     r0, r0, r1 
    
    msr     CPSR_c, #MODE_UND | I_BIT | F_BIT
    mov     sp, r0
    sub     r0, r0, r1 
    
    msr     CPSR_c, #MODE_SYS | I_BIT | F_BIT
    mov     sp, r0
    sub     r0, r0, r1 
    
    @ Set SVC mode stack with interrupts disabled 
    msr     CPSR_c, #MODE_SVC | I_BIT | F_BIT
    mov     sp, r0
    sub     r0, r0, r1 
    
    @ check cpu id - cpu0 is primary cpu
    cmp     r5, #0
    beq     primary_cpu_init
    bx      r4     @ for secondary cpus, jump to argument function pointer passed in by ROM
    
    @ control should not return from the secondary cpu entry point
    b       startup_exit

primary_cpu_init:
    /*
     * copy the vector table into the RAM vectors
     * this assumes that the RAM vectors size is divisible by 3 words (12 bytes)
     */
    ldr     r1,=__ram_vectors_start
    ldr     r2,=__ram_vectors_end
    ldr     r3,=vectors
1:  cmp     r1,r2
    ldmlt   r3!,{r4,r5,r6}
    stmlt   r1!,{r4,r5,r6}
    blt     1b
    
    /*
     * fill the stacks with a pattern
     * the stack must be 8 byte aligned
     */
    ldr     r1,=__stacks_start      @ stack region start address
    ldr     r2,=top_of_stacks       @ stack region end address
    bic     r2,r2,#0x7              @ round length down to nearest 8 byte alignment
    ldr     r3,=.Ldeadfeed          @ get fill pattern address
    ldr     r3,[r3]                 @ read fill pattern into r3
    mov     r4,r3                   @ copy fill pattern to r4
1:  cmp     r1,r2                   @ the fill loop
    stmltia r1!,{r3-r4}
    blt     1b    

   	/* init .bss */
    /* clear the .bss section (zero init) */
    ldr     r1,=__bss_start__
    ldr     r2,=__bss_end__
    mov     r3,#0
1:  cmp     r1,r2
    stmltia r1!,{r3}
    blt     1b
    
    @ take care of C++ static initialization. this won't cause any harm for plain C apps.
    ldr     r12,=__libc_init_array
    blx     r12
    
    @ branch to c library entry point 
    mov     r0,#0 @ argc
    mov     r1,#0 @ argv
    mov     r2,#0 @ env
    
    ldr     r12, =main               /* save this in register for possible long jump */
    blx     r12                         /* branch to __main */ 

    @ if either main() or the secondary cpu entry point return, which they should not,
    @ then call _sys_exit().
startup_exit:
    mov     r0,#0
    ldr     r12,=_sys_exit
    bx      r12
    
    .cantunwind
    .fnend
    .endfunc    @ _start()

    /* local label for the stack fill pattern */
.Ldeadfeed:
    .word   0xdeadfeed


    .end

