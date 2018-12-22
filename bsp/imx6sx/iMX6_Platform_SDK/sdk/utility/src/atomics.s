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
 * @file atomics.s
 * @brief Implementation of atomic operations.
 */
 
    .code 32
    .section ".text","ax"

    @ bool atomic_compare_and_swap(volatile uint32_t * value, uint32_t oldValue, uint32_t newValue)
    .global atomic_compare_and_swap
    .func atomic_compare_and_swap
atomic_compare_and_swap:
    dsb                             @ data sync memory barrier
    mov         r12, #0             @ clear return value
    ldrex       r3, [r0]            @ load exclusive current value
    cmp         r3, r1              @ does current value equal "old" value?
    strexeq     r12, r2, [r0]       @ if it does, then store exclusive the new value
    eoreq       r12, #1             @ invert the strex result
    mov         r0, r12             @ return the result of strex
    bx          lr                  @ return to caller
    .endfunc    @atomic_compare_and_swap();

    @ int32_t atomic_add(volatile int32_t * value, int32_t delta)
    .global atomic_add
    .func atomic_add
atomic_add: 
    dsb                             @ data sync barrier
    ldrex       r3, [r0]            @ load exclusive original value
    add         r2, r3, r1          @ add delta into original
    strex       r12, r2, [r0]       @ store exclusive the new value, r12==0 if store was successful
    cmp         r12, #0             @ check if the store succeeded
    bne         atomic_add          @ if the store failed, try again
    mov         r0, r3              @ return the original value
    bx          lr
    .endfunc    @atomic_add();

    @ int32_t atomic_increment(volatile int32_t * value)
    .global atomic_increment
    .func atomic_increment
atomic_increment: 
    mov         r1, #1              @ load increment value into r1
    b           atomic_add
    .endfunc    @atomic_increment();

    @ int32_t atomic_decrement(volatile int32_t * value)
    .global atomic_decrement
    .func atomic_decrement
atomic_decrement: 
    mov         r1, #0xffffffff         @ load -1 into r1
    b           atomic_add
    .endfunc    @atomic_decrement();


@ ------------------------------------------------------------
@ End of atomics.s
@ ------------------------------------------------------------
    .end
