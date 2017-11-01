/*
 * Copyright (c) 2012-2013, Freescale Semiconductor, Inc.
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

#include "utility/spinlock.h"
#include "utility/atomics.h"
#include "timer/timer.h"

////////////////////////////////////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////////////////////////////////////

enum
{
    kUnlocked = 0xff  //!< Unlocked value for the spinlock.
};

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void spinlock_init(spinlock_t * lock)
{
//     lock->counter = kUnlocked;
    lock->owner = kUnlocked;
}

// int spinlock_lock(spinlock_t * lock, uint32_t timeout)
// {
//     uint64_t startTime = time_get_microseconds();
//     
//     // Spin until we can lock the lock.
//     while (atomic_compare_and_swap((uint32_t *)lock, kUnlocked, kLocked))
//     {
//         // Unless the caller wants to wait forever, check if the timeout has elapsed.
//         if ((timeout != kSpinlockWaitForever)
//             && (time_get_microseconds() - startTime >= timeout))
//         {
//             return 1;
//         }
//     }
// 
//     return 0;
// }

// void spinlock_unlock(spinlock_t * lock)
// {
//     // Unlock the lock.
//     while (!atomic_compare_and_swap((uint32_t *)lock, kLocked, kUnlocked));
// }

bool spinlock_is_locked(spinlock_t * lock)
{
    return (lock->owner != kUnlocked);
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
