 /**********************************************************************
 * Copyright (C) 2011-2015 Cadence Design Systems, Inc.- http://www.cadence.com
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ***********************************************************************
 * cps_v2.h
 * Interface for Cadence Platform Services (CPS), version 2
 *
 * This is the "hardware abstraction layer" upon which all drivers are built.
 * It must be implemented for each platform.
 ***********************************************************************/
#ifndef _CPS_H_
#define _CPS_H_

#include "cdn_stdint.h"

/****************************************************************************
 * Types
 ***************************************************************************/

/** A lock handle */
typedef void* CPS_LockHandle;

/****************************************************************************
 * Prototypes
 ***************************************************************************/

/**
 * Check that sufficient locks are available
 * @param[in] lockCount number of locks requested
 * @return 0 on success (locks available)
 * @return ENOENT if insufficient locks are available
 */
extern uint32_t CPS_ProbeLocks(uint32_t lockCount);

/**
 * Initialize a lock
 * @param[out] lock where to store the allocated, initialized lock
 * @return 0 on success (lock is allocated and initialized)
 * @return ENOENT if insufficient locks are available
 */
extern uint32_t CPS_InitLock(CPS_LockHandle* lock);

/**
 * Free a lock
 * @param[in] lock the lock
 */
extern void CPS_FreeLock(CPS_LockHandle lock);

/**
 * Lock a lock, pending the current thread/task if necessary until the lock is available
 * @param[in] lock the lock
 */
extern uint32_t CPS_Lock(CPS_LockHandle lock);

/**
 * Unlock a lock, readying the next highest-priority thread/task pended on it if any
 * @param[in] lock the lock
 */
extern uint32_t CPS_Unlock(CPS_LockHandle lock);

/**
 * Read a byte, bypassing the cache
 * @param[in] address the address
 * @return the byte at the given address
 */
extern uint8_t CPS_UncachedRead8(volatile uint8_t* address);

/**
 * Read a short, bypassing the cache
 * @param[in] address the address
 * @return the short at the given address
 */
extern uint16_t CPS_UncachedRead16(volatile uint16_t* address);

/**
 * Read a (32-bit) word, bypassing the cache
 * @param[in] address the address
 * @return the word at the given address
 */
extern uint32_t CPS_UncachedRead32(volatile uint32_t* address);

/**
 * Read a (32-bit) address value, bypassing the cache.
 * This function is for reading an address value, i.e. something that
 * is seen as an address by hardware, and therefore might need to be
 * translated from a physical bus address to a CPU address.
 * @param[in] location
 * @return the CPU address of the physical bus address at the given (CPU) location
 */
extern uint32_t CPS_ReadPhysAddress32(volatile uint32_t* location);

/**
 * Write a byte to memory, bypassing the cache
 * @param[in] address the address
 * @param[in] value the byte to write
 */
extern void CPS_UncachedWrite8(volatile uint8_t* address, uint8_t value);

/**
 * Write a short to memory, bypassing the cache
 * @param[in] address the address
 * @param[in] value the short to write
 */
extern void CPS_UncachedWrite16(volatile uint16_t* address, uint16_t value);

/**
 * Write a (32-bit) word to memory, bypassing the cache
 * @param[in] address the address
 * @param[in] value the word to write
 */
extern void CPS_UncachedWrite32(volatile uint32_t* address, uint32_t value);

/**
 * Write a (32-bit) address value to memory, bypassing the cache.
 * This function is for writing an address value, i.e. something that
 * will be treated as an address by hardware, and therefore might need
 * to be translated to a physical bus address.
 * @param[in] location the (CPU) location where to write the address value
 * @param[in] addrValue the address value to write
 */
extern void CPS_WritePhysAddress32(volatile uint32_t* location, uint32_t addrValue);

/**
 * Hardware specific memcpy.
 * @param[in] src  src address
 * @param[in] dst  destination address
 * @param[in] size size of the copy
 */
extern void CPS_BufferCopy(volatile uint8_t *dst, volatile uint8_t *src, uint32_t size);

#endif /* multiple inclusion protection */
