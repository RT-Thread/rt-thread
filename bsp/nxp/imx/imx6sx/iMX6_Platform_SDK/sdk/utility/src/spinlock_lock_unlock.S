/*
 * Copyright (c) 2013, Freescale Semiconductor, Inc.
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
/*
 * Portions Copyright (c) 2011-2012 ARM Ltd.  All rights reserved.
 */

    .code 32
    .section ".text","ax"
    
    .global cpu_get_current

#define UNLOCKED 0xFF

// int spinlock_lock(spinlock_t * lock, uint32_t timeout)
    .global spinlock_lock
    .func spinlock_lock
spinlock_lock:

    ldrex   r1, [r0]                // check if the spinlock is currently unlocked
    cmp     r1, #UNLOCKED
    
    wfene                           // wait for an event signal
    bne     spinlock_lock
    
    mrc     p15, 0, r1, c0, c0, 5   // get our CPU ID
    and     r1, r1, #3
    strex   r2, r1, [r0]            // attempt to grab lock by writing CPU number into spinlock
    cmp     r2, #0                  // check if the write was successful
    bne     spinlock_lock           // if the write failed, start over
    
    dmb                             // Ensure that accesses to shared resource have completed
    
    bx      lr                      // return to caller

    .endfunc // spinlock_lock
    
// void spinlock_unlock(spinlock_t * lock)
    .global spinlock_unlock
    .func spinlock_unlock
spinlock_unlock:

    mrc     p15, 0, r1, c0, c0, 5   // get our CPU ID
    and     r1, r1, #3
    
    ldr     r2, [r0]                // read lock field of spinlock
    cmp     r1, r2                  // compare lock field with our CPU ID
    movne   r0, #1                  // doesn't match, so exit with failure
    bxne    lr
    
    dmb                             // Ensure that accesses to shared resource have completed
    
    mov     r1, #UNLOCKED           // load unlocked value
    str     r1, [r0]                // write into lock field of spinlock
    
    dsb                             // Ensure that no instructions following the barrier execute until
                                    // all memory accesses prior to the barrier have completed.
    
    sev                             // send event to wake up other cores waiting on spinlock
    
    mov     r0, #0                  // return success
    bx      lr

    .endfunc


    .end
