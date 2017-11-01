/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
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
#if !defined(__SPINLOCK_H__)
#define __SPINLOCK_H__

#include <stdint.h>
#include <stdbool.h>

//! @addtogroup spinlock
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Typedef for a spinlock.
typedef struct _spinlock {
    uint32_t owner;   //!< Lock count.
//     uint32_t owner;     //!< Core number of the owning CPU.
    uint32_t _cacheLineFiller[7]; //! Padding to make the lock consume a full cache line (32 bytes).
} spinlock_t __attribute__ ((aligned (32)));

//! @brief Special timeout values for the spinlock.
enum _spinlock_timeouts
{
    //! Timeout value meaning do not block at all if the spinlock isn't free.
    kSpinlockNoWait = 0,
    
    //! Timeout value to use to wait indefinitely for the spinlock to become available.
    kSpinlockWaitForever = 0xffffffff
};

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

//! @name Spinlock API
//@{

//! @brief Initialize a new spinlock.
//!
//! The spinlock is initialized in the unlocked state. Call spinlock_lock() if you need it
//! to be locked.
//!
//! @param lock Pointer to the new spinlock.
void spinlock_init(spinlock_t * lock);

//! @brief Lock the given spinlock.
//!
//! Use this function to lock a spinlock. If the spinlock is unlocked, it will be locked and
//! this function will return immediately. However, if the spinlock is already locked then
//! this function will block for up to @a timeout microseconds waiting for another thread to
//! unlock it.
//!
//! If #kSpinlockNoWait is passed for the timeout, then the function will not block at all.
//! In this case, either the spinlock is locked immediately or it is left untouched.
//!
//! To wait infinitely for the spinlock to become free, pass #kSpinlockWaitForever. If the
//! spinlock is already locked and no other thread unlocks it, then this function will never
//! return (i.e., deadlock).
//!
//! @param lock Pointer to the spinlock to lock.
//! @param timeout Maximum number of microseconds to block waiting for the spinlock to become
//!     available if it was locked upon entry to this function.
//!
//! @retval 0 The spinlock was locked successfully.
//! @retval 1 A timeout occurred while waiting for the spinlock to be unlocked.
int spinlock_lock(spinlock_t * lock, uint32_t timeout);

//! @brief Unlock the given spinlock.
//!
//! @param lock Pointer to the spinlock to unlock.
void spinlock_unlock(spinlock_t * lock);

//! @brief Check whether a spinlock is currently locked.
//!
//! @param lock Pointer to the spinlock to test.
bool spinlock_is_locked(spinlock_t * lock);

//@}

#if defined(__cplusplus)
}
#endif

//! @}

#endif // __SPINLOCK_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
