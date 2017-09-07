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

/*!
 * @file  mmu.c
 * @brief System memory arangement.
 */
#include "cortex_a9.h"
#include "mmu.h"
#include "arm_cp_registers.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Size in bytes of the first-level page table.
#define MMU_L1_PAGE_TABLE_SIZE (16 * 1024)

//! @brief First-level 1MB section descriptor entry.
typedef union mmu_l1_section {
    uint32_t u;
    struct {
        uint32_t id:2;  //!< ID
        uint32_t b:1;   //!< Bufferable
        uint32_t c:1;   //!< Cacheable
        uint32_t xn:1;  //!< Execute-not
        uint32_t domain:4;  //!< Domain
        uint32_t _impl_defined:1;   //!< Implementation defined, should be zero.
        uint32_t ap1_0:2;  //!< Access permissions AP[1:0]
        uint32_t tex:3; //!< TEX remap
        uint32_t ap2:1; //!< Access permissions AP[2] 
        uint32_t s:1;   //!< Shareable
        uint32_t ng:1;  //!< Not-global
        uint32_t _zero:1;   //!< Should be zero.
        uint32_t ns:1;  //!< Non-secure
        uint32_t address:12;   //!< Physical base address
    };
} mmu_l1_section_t;

enum {
    kMMU_L1_Section_ID = 2,  //!< ID value for a 1MB section first-level entry.
    kMMU_L1_Section_Address_Shift = 20  //!< Bit offset of the physical base address field.
};

////////////////////////////////////////////////////////////////////////////////
// Externs
////////////////////////////////////////////////////////////////////////////////

extern char __l1_page_table_start;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void mmu_enable()
{
    // invalidate all tlb 
    arm_unified_tlb_invalidate();

    // read SCTLR 
    uint32_t sctlr;
    _ARM_MRC(15, 0, sctlr, 1, 0, 0);
    
    // set MMU enable bit 
    sctlr |= BM_SCTLR_M;

    // write modified SCTLR
    _ARM_MCR(15, 0, sctlr, 1, 0, 0);
}

void mmu_disable()
{
    // read current SCTLR 
    uint32_t sctlr;
    _ARM_MRC(15, 0, sctlr, 1, 0, 0);
    
    // clear MMU enable bit 
    sctlr &=~ BM_SCTLR_M;

    // write modified SCTLR
    _ARM_MCR(15, 0, sctlr, 1, 0, 0);
}

void mmu_init()
{
    // Get the L1 page table base address.
    uint32_t * table = (uint32_t *)&__l1_page_table_start;
    uint32_t share_attr = kShareable;

    // write table address to TTBR0
    _ARM_MCR(15, 0, table, 2, 0, 0);

    // set Client mode for all Domains
    uint32_t dacr = 0x55555555; 
    _ARM_MCR(15, 0, dacr, 3, 0, 0); // MCR p15, 0, <Rd>, c3, c0, 0 ; Write DACR

    // Clear the L1 table.
    bzero(table, MMU_L1_PAGE_TABLE_SIZE);
    
    // Create default mappings.
    mmu_map_l1_range(0x00000000, 0x00000000, 0x00900000, kStronglyOrdered, kShareable, kRWAccess); // ROM and peripherals
    mmu_map_l1_range(0x00900000, 0x00900000, 0x00100000, kStronglyOrdered, kShareable, kRWAccess); // OCRAM
    mmu_map_l1_range(0x00a00000, 0x00a00000, 0x0f600000, kStronglyOrdered, kShareable, kRWAccess); // More peripherals
   
    // Check whether SMP is enabled. If it is not, then we don't want to make SDRAM shareable.
    uint32_t actlr = 0x0;
    _ARM_MRC(15, 0, actlr, 1, 0, 1);
    if (actlr & BM_ACTLR_SMP)
    {
        share_attr = kShareable;
    }
    else
    {
        share_attr = kNonshareable;
    }

#if defined(CHIP_MX6DQ) || defined(CHIP_MX6SDL)
    mmu_map_l1_range(0x10000000, 0x10000000, 0x80000000, kOuterInner_WB_WA, share_attr, kRWAccess); // 2GB DDR
#elif defined(CHIP_MX6SL)
    mmu_map_l1_range(0x80000000, 0x80000000, 0x40000000, kOuterInner_WB_WA, share_attr, kRWAccess); // 1GB DDR
#else
#error Unknown chip type!
#endif
}

void mmu_map_l1_range(uint32_t pa, uint32_t va, uint32_t length, mmu_memory_type_t memoryType, mmu_shareability_t isShareable, mmu_access_t access)
{
    register mmu_l1_section_t entry;
    entry.u = 0;
    
    // Set constant attributes.
    entry.id = kMMU_L1_Section_ID;
    entry.xn = 0; // Allow execution
    entry.domain = 0; // Domain 0
    entry.ng = 0; // Global
    entry.ns = 0; // Secure
    
    // Set attributes based on the selected memory type.
    switch (memoryType)
    {
        case kStronglyOrdered:
            entry.c = 0;
            entry.b = 0;
            entry.tex = 0;
            entry.s = 1; // Ignored
            break;
        case kDevice:
            if (isShareable)
            {
                entry.c = 0;
                entry.b = 1;
                entry.tex = 0;
                entry.s = 1; // Ignored
            }
            else
            {
                entry.c = 0;
                entry.b = 0;
                entry.tex = 2;
                entry.s = 0; // Ignored
            }
            break;
        case kOuterInner_WB_WA:
            entry.c = 1;
            entry.b = 1;
            entry.tex = 1;
            entry.s = isShareable;
            break;
        case kOuterInner_WT:
            entry.c = 1;
            entry.b = 0;
            entry.tex = 0;
            entry.s = isShareable;
            break;
        case kNoncacheable:
            entry.c = 0;
            entry.b = 0;
            entry.tex = 1;
            entry.s = isShareable;
            break;
    }
    
    // Set attributes from specified access mode.
    switch (access)
    {
        case kNoAccess:
            entry.ap2 = 0;
            entry.ap1_0 = 0;
            break;
        case kROAccess:
            entry.ap2 = 1;
            entry.ap1_0 = 3;
            break;
        case kRWAccess:
            entry.ap2 = 0;
            entry.ap1_0 = 3;
            break;
    }
    
    // Get the L1 page table base address.
    uint32_t * table = (uint32_t *)&__l1_page_table_start;
    
    // Convert addresses to 12-bit bases.
    uint32_t vbase = va >> kMMU_L1_Section_Address_Shift;
    uint32_t pbase = pa >> kMMU_L1_Section_Address_Shift;
    uint32_t entries = length >> kMMU_L1_Section_Address_Shift;

    // Fill in L1 page table entries.
    for (; entries > 0; ++pbase, ++vbase, --entries)
    {
        entry.address = pbase;
        table[vbase] = entry.u;
    }
    
    // Invalidate TLB
    arm_unified_tlb_invalidate();
}

bool mmu_virtual_to_physical(uint32_t virtualAddress, uint32_t * physicalAddress)
{
    uint32_t pa = 0;
    
    // VA to PA translation with privileged read permission check  
    _ARM_MCR(15, 0, virtualAddress & 0xfffffc00, 7, 8, 0);
    
    // Read PA register 
    _ARM_MRC(15, 0, pa, 7, 4, 0);
    
    // First bit of returned value is Result of conversion (0 is successful translation) 
    if (pa & 1)
    {
        // We can try write permission also 
        // VA to PA translation with privileged write permission check  
        _ARM_MCR(15, 0, virtualAddress & 0xfffffc00, 7, 8, 1);
        
        // Read PA register 
        _ARM_MRC(15, 0, pa, 7, 4, 0);
        
        // First bit of returned value is Result of conversion (0 is successful translation) 
        if (pa & 1)
        {
            return false;
        }
    }
    
    if (physicalAddress)
    {
        // complete address returning base + offset
        pa = (pa & 0xfffff000) | (virtualAddress & 0x00000fff);
        *physicalAddress = pa;
    }
    
    return true;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
