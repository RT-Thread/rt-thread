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
#if !defined(__ATOMICS_H__)
#define __ATOMICS_H__

#include <stdint.h>
#include <stdbool.h>

//! @addtogroup atomics
//! @{

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

//! @name Atomic operations
//@{

//! @brief Atomic compare and swap operation.
//!
//! Tests the word pointed to by @a value for equality with @a oldValue. If they are
//! equal, the word pointed to by @a value is set to @a newValue. If *value is not
//! equal to @a oldValue, then no change is made. The return value indicates whether
//! the swap was performed. Of course, this entire operation is guaranteed to be
//! atomic even on multiprocessor platforms.
//!
//! A memory barrier is performed prior to the compare and swap operation.
//!
//! @param value Pointer to the word to compare and swap.
//! @param oldValue Value to compare against.
//! @param newValue Value to value to swap in if *value is equal to oldValue.
//! @retval false No change was made to *value.
//! @retval true The swap was performed, and *value is now equal to newValue.
bool atomic_compare_and_swap(volatile uint32_t * value, uint32_t oldValue, uint32_t newValue);

//! @brief Atomic add operation.
//!
//! A memory barrier is performed prior to the add operation.
//!
//! @param value Pointer to the word to add to.
//! @param delta Signed value to atomically add to *value.
//! @return The original value is returned.
int32_t atomic_add(volatile int32_t * value, int32_t delta);

//! @brief Atomically increment a value.
//!
//! @param value Pointer to the word to increment.
//! @return The original value is returned.
int32_t atomic_increment(volatile int32_t * value);

//! @brief Atomically decrement a value.
//!
//! @param value Pointer to the word to decrement.
//! @return The original value is returned.
int32_t atomic_decrement(volatile int32_t * value);

//@}

#if defined(__cplusplus)
}
#endif

//! @}

#endif // __ATOMICS_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
