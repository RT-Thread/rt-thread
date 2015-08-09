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

    .code 32
    .section ".text","ax"

    .extern  dump_regs

/*
 * A very simple implementation of the data abort handler.
 *
 * It just dumps the registers before this exception occured, to make the debugging easier.
 */
    .global  common_abort_handler
    .func  common_abort_handler
common_abort_handler: 
	push    {r0-r12}	// push the general registers to this exception's stack
	mrs     r7, cpsr
	mrs     r6, spsr
	mov     r5, sp
	msr     cpsr, r6    // go to the mode before this exception so we can get its sp and pc
	dsb
	stmfd   r5!, {sp, lr} // push sp/lr to this exception's stack
	msr     cpsr, r7    // switch back to abort mode
	dsb
	mov     sp, r5      // restore our stack pointer
	push    {r6, lr}    // r6 is exception's cpsr, lr is the exception's pc
	
	// save coprocessor abort info registers
	mrc     p15, 0, r4, c5, c0, 0   // read DFSR
	mrc     p15, 0, r3, c6, c0, 0   // read DFAR
	mrc     p15, 0, r2, c5, c0, 1   // read IFSR
	mrc     p15, 0, r1, c6, c0, 2   // read IFAR
	push    {r1-r4}        // save DFSR, DFAR, IFSR, IFAR to stack
	
	ldr     r1,=.Labort_type
	ldr     r0,[r1]     // put abort type in r0
	mov     r1, sp      // put address to saved registers into r1
	bl      dump_regs   // call a C function to print the register values
	
	// clean up
	pop     {r0-r12}
	add     sp, sp, #16 // adjust the sp pointer, just like 'pop {lr, r6}'

    // Loop forever.
1:
	b       1b
	
	sub     pc, lr, #4 // abort handler's standard return, although never reach here.
    .endfunc

    .global data_abort_handler
    .func data_abort_handler
data_abort_handler:
    push    {r0-r1}
    ldr     r1,=.Labort_type
    mov     r0,#0
    str     r0,[r1]
    pop     {r0-r1}
    b       common_abort_handler
    .endfunc

    .global prefetch_abort_handler
    .func prefetch_abort_handler
prefetch_abort_handler:
    push    {r0-r1}
    ldr     r1,=.Labort_type
    mov     r0,#1
    str     r0,[r1]
    pop     {r0-r1}
    b       common_abort_handler
    .endfunc


    // Switch to data section
    .data

    // Place to store whether we got a prefetch or data abort.
    // 0=data abort
    // 1=prefetch abort
.Labort_type:
    .word   0

    .end
