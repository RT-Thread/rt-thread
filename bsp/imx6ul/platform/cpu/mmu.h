/*
 * Copyright (c) 2008-2012, Freescale Semiconductor, Inc.
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

//! @addtogroup diag_mmu
//! @{

/*!
 * @file  mmu.h
 * @brief System memory arrangement.
 */

#ifndef _MMU_H_
#define _MMU_H_

#include "sdk.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Memory region attributes.
typedef enum _mmu_memory_type
{
    kStronglyOrdered,
    kDevice,
    kOuterInner_WB_WA,
    kOuterInner_WT,
    kNoncacheable,
} mmu_memory_type_t;

//! @brief Memory region shareability options.
typedef enum _mmu_shareability
{
    kShareable = 1,
    kNonshareable = 0
} mmu_shareability_t;

//! @brief Access permissions for a memory region.
typedef enum _mmu_access
{
    kNoAccess,
    kROAccess,
    kRWAccess
} mmu_access_t;

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Enable the MMU.
 *
 * The L1 page tables and MMU settings must have already been configured by
 * calling mmu_init() before the MMU is enabled.
 */
void mmu_enable();

/*!
 * @brief Disable the MMU.
 */
void mmu_disable();

/*!
 * @brief Set up the default first-level page table.
 *
 * Initializes the L1 page table with the following regions:
 *  - 0x00000000...0x00900000 : ROM and peripherals, strongly-ordered
 *  - 0x00900000...0x00a00000 : OCRAM, strongly-ordered
 *  - For MX6DQ or MX6SDL: 0x10000000...0x90000000 : DDR, normal, outer inner, write-back, write-allocate
 *  - For MX6SL: 0x80000000...0xc0000000 : DDR, normal, outer inner, write-back, write-allocate
 *
 * If the CPU is participating in SMP, then the DDR regions are made shareable. Otherwise they
 * are marked as non-shareable.
 *
 * The TTBR0 register is set to the base of the L1 table.
 *
 * All memory domains are configured to allow client access. However, note that only domain 0 is
 * used by mmu_map_l1_range().
 */
void mmu_init();

/*!
 * @brief Maps a range of memory in the first-level page table.
 *
 * Entries in the first-level page table are filled in for the range of virtual addresses
 * starting at @a va and continuing for @a length bytes. These virtual addreses are mapped
 * to the physical addresses starting at @a pa and continuing for @a length bytes. All table
 * entries for the range of mapped memory have the same attributes, which are selected with
 * the @a memoryType, @a isShareable, and @a access parameters.
 *
 * @param pa The base physical address of the range to which the virtual address will be mapped.
 * @param va The base virtual address of the range.
 * @param length The size of the range to be mapped, in bytes. This value must be divisible by 1MB.
 * @param memoryType The type of the memory region. This controls caching, buffering, ordering of
 *      memory accesses, and other attributes of the region.
 * @param isShareable The shareability of the physical memory. Ignored for strongly-ordered memory.
 * @param access Access permissions.
 */
void mmu_map_l1_range(uint32_t pa, uint32_t va, uint32_t length, mmu_memory_type_t memoryType, mmu_shareability_t isShareable, mmu_access_t access);

/*!
 * @brief Convert virtual address to physical.
 *
 * First attempts a priviledged read translation for the current security mode. If that fails,
 * a priviledged write translation, also for the current security mode, is attempted. If this
 * second attempt at translation fails, then false will be returned.
 *
 * @param virtualAddress Virtual address to convert to a physical address.
 * @param[out] physicalAddress This parameter is filled in with the physical address corresponding
 *      to the virtual address passed in @a virtualAddress.
 * @retval true The address returned through @a physicalAddress is valid.
 * @retval false The conversion failed for some reason.
 */
bool mmu_virtual_to_physical(uint32_t virtualAddress, uint32_t * physicalAddress);

#if defined(__cplusplus)
}
#endif

//! @}

#endif // _MMU_H_
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////

