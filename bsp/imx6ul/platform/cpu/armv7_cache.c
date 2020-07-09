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

#include "cortex_a.h"
#include "arm_cp_registers.h"

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

//! @brief Check if dcache is enabled or disabled
int arm_dcache_state_query()
{
    uint32_t sctlr; // System Control Register 
    
    // read sctlr 
    _ARM_MRC(15, 0, sctlr, 1, 0, 0);
        
    if (sctlr & BM_SCTLR_C)
    {
        return 1;
    }

    return 0;
}

void arm_dcache_enable()
{
    uint32_t sctlr; // System Control Register 
    
    // read sctlr 
    _ARM_MRC(15, 0, sctlr, 1, 0, 0);
        
    if (!(sctlr & BM_SCTLR_C))
    {
        // set  C bit (data caching enable) 
        sctlr |= BM_SCTLR_C;
        
        // write modified sctlr
        _ARM_MCR(15, 0, sctlr, 1, 0, 0);
        
        // All Cache, Branch predictor and TLB maintenance operations before followed instruction complete
        _ARM_DSB();
    }
}

void arm_dcache_disable()
{
    uint32_t sctlr; // System Control Register 
    
    // read sctlr 
    _ARM_MRC(15, 0, sctlr, 1, 0, 0);
    
    // set  C bit (data caching enable) 
    sctlr &= ~BM_SCTLR_C;

    // write modified sctlr
    _ARM_MCR(15, 0, sctlr, 1, 0, 0);
    
    // All Cache, Branch predictor and TLB maintenance operations before followed instruction complete
    _ARM_DSB();
}

void arm_dcache_invalidate()
{
    uint32_t csid;    // Cache Size ID
    uint32_t wayset;  // wayset parameter 
    int num_sets; // number of sets  
    int num_ways; // number of ways

    _ARM_MRC(15, 1, csid, 0, 0, 0);    // Read Cache Size ID 
    
    // Fill number of sets  and number of ways from csid register  This walues are decremented by 1
    num_ways = (csid >> 0x03) & 0x3FFu; //((csid& csid_ASSOCIATIVITY_MASK) >> csid_ASSOCIATIVITY_SHIFT)
    
    // Invalidation all lines (all Sets in all ways) 
    while (num_ways >= 0)
    {
        num_sets = (csid >> 0x0D) & 0x7FFFu; //((csid & csid_NUMSETS_MASK) >> csid_NUMSETS_SHIFT)
        while (num_sets >= 0 )
        {
            wayset = (num_sets << 5u) | (num_ways << 30u); //(num_sets << SETWAY_SET_SHIFT) | (num_sets << 3SETWAY_WAY_SHIFT)
            // invalidate line if we know set and way 
            _ARM_MCR(15, 0, wayset, 7, 6, 2);
            num_sets--;
        }
        num_ways--;
    }
    
    // All Cache, Branch predictor and TLB maintenance operations before followed instruction complete
    _ARM_DSB();
}

void arm_dcache_invalidate_line(const void * addr)
{
    uint32_t csidr = 0, line_size = 0;
    uint32_t va;
    
    // get the cache line size
    _ARM_MRC(15, 1, csidr, 0, 0, 0);
    line_size = 1 << ((csidr & 0x7) + 4);    
    va = (uint32_t) addr & (~(line_size - 1)); //addr & va_VIRTUAL_ADDRESS_MASK

    // Invalidate data cache line by va to PoC (Point of Coherency). 
    _ARM_MCR(15, 0, va, 7, 6, 1);
    
    // All Cache, Branch predictor and TLB maintenance operations before followed instruction complete
    _ARM_DSB();
}

void arm_dcache_invalidate_mlines(const void * addr, size_t length)
{
    uint32_t va;
    uint32_t csidr = 0, line_size = 0;
    
    // get the cache line size
    _ARM_MRC(15, 1, csidr, 0, 0, 0);
    line_size = 1 << ((csidr & 0x7) + 4);

    // align the address with line
    const void * end_addr = (const void *)((uint32_t)addr + length);
            
    do
    {
        // Clean data cache line to PoC (Point of Coherence) by va. 
        va = (uint32_t) ((uint32_t)addr & (~(line_size - 1))); //addr & va_VIRTUAL_ADDRESS_MASK
        _ARM_MCR(15, 0, va, 7, 6, 1);
        // increment addres to next line and decrement lenght 
        addr = (const void *) ((uint32_t)addr + line_size);
    } while (addr < end_addr);
    
    // All Cache, Branch predictor and TLB maintenance operations before followed instruction complete
    _ARM_DSB();
}

void arm_dcache_flush()
{
    uint32_t csid;    // Cache Size ID
    uint32_t wayset;  // wayset parameter 
    int num_sets; // number of sets  
    int num_ways; // number of ways

    _ARM_MRC(15, 1, csid, 0, 0, 0);    // Read Cache Size ID 
    
    // Fill number of sets  and number of ways from csid register  This walues are decremented by 1
    num_ways = (csid >> 0x03) & 0x3FFu; //((csid& csid_ASSOCIATIVITY_MASK) >> csid_ASSOCIATIVITY_SHIFT`)
    while (num_ways >= 0)
    {
        num_sets = (csid >> 0x0D) & 0x7FFFu; //((csid & csid_NUMSETS_MASK)      >> csid_NUMSETS_SHIFT       )
        while (num_sets >= 0 )
        {
            wayset = (num_sets << 5u) | (num_ways << 30u); //(num_sets << SETWAY_SET_SHIFT) | (num_ways << 3SETWAY_WAY_SHIFT)
            // FLUSH (clean) line if we know set and way 
            _ARM_MCR(15, 0, wayset, 7, 10, 2);
            num_sets--;
        }
        num_ways--;
    }
    
    // All Cache, Branch predictor and TLB maintenance operations before followed instruction complete
    _ARM_DSB();
}

void arm_dcache_flush_line(const void * addr)
{
    uint32_t csidr = 0, line_size = 0;
    uint32_t va;
    
    // get the cache line size
    _ARM_MRC(15, 1, csidr, 0, 0, 0);
    line_size = 1 << ((csidr & 0x7) + 4);    
    va = (uint32_t) addr & (~(line_size - 1)); //addr & va_VIRTUAL_ADDRESS_MASK
    
    // Clean data cache line to PoC (Point of Coherence) by va. 
    _ARM_MCR(15, 0, va, 7, 10, 1);
    
    // All Cache, Branch predictor and TLB maintenance operations before followed instruction complete
    _ARM_DSB();
}

void arm_dcache_flush_mlines(const void * addr, size_t length)
{
    uint32_t va;
    uint32_t csidr = 0, line_size = 0;
    const void * end_addr = (const void *)((uint32_t)addr + length);

    // get the cache line size
    _ARM_MRC(15, 1, csidr, 0, 0, 0);
    line_size = 1 << ((csidr & 0x7) + 4);
    
    do
    {
        // Clean data cache line to PoC (Point of Coherence) by va. 
        va = (uint32_t) ((uint32_t)addr & (~(line_size  - 1))); //addr & va_VIRTUAL_ADDRESS_MASK
        _ARM_MCR(15, 0, va, 7, 10, 1);
        
        // increment addres to next line and decrement lenght 
        addr = (const void *) ((uint32_t)addr + line_size);
    } while (addr < end_addr);
    
    // All Cache, Branch predictor and TLB maintenance operations before followed instruction complete
    _ARM_DSB();
}

int arm_icache_state_query()
{
    uint32_t sctlr; // System Control Register 
    
    // read sctlr 
    _ARM_MRC(15, 0, sctlr, 1, 0, 0);
        
    if (sctlr & BM_SCTLR_I)
    {
        return 1;
    }

    return 0;
}

void arm_icache_enable()
{
    uint32_t sctlr  ;// System Control Register 
    
    // read sctlr 
    _ARM_MRC(15, 0, sctlr, 1, 0, 0);
    
    // ignore the operation if I is enabled already
    if(!(sctlr & BM_SCTLR_I))
    {	
        // set  I bit (instruction caching enable)
        sctlr |= BM_SCTLR_I;
        
        // write modified sctlr
        _ARM_MCR(15, 0, sctlr, 1, 0, 0);
        
        // synchronize context on this processor 
        _ARM_ISB();
    }
}

void arm_icache_disable()
{
    uint32_t sctlr  ;// System Control Register 
    
    // read sctlr 
    _ARM_MRC(15, 0, sctlr, 1, 0, 0);
    
    // Clear  I bit (instruction caching enable) 
    sctlr &= ~BM_SCTLR_I;

    // write modified sctlr
    _ARM_MCR(15, 0, sctlr, 1, 0, 0);
    
    // synchronize context on this processor 
    _ARM_ISB();
}

void arm_icache_invalidate()
{
    uint32_t SBZ = 0x0u;
    
    _ARM_MCR(15, 0, SBZ, 7, 5, 0);
    
    // synchronize context on this processor 
    _ARM_ISB();
}

void arm_icache_invalidate_is()
{
    uint32_t SBZ = 0x0u;
    
    _ARM_MCR(15, 0, SBZ, 7, 1, 0);
    
    // synchronize context on this processor 
    _ARM_ISB();
}

void arm_icache_invalidate_line(const void * addr)
{
    uint32_t csidr = 0, line_size = 0;
    uint32_t va;
    
    // get the cache line size
    _ARM_MRC(15, 1, csidr, 0, 0, 0);
    line_size = 1 << ((csidr & 0x7) + 4);    
    va = (uint32_t) addr & (~(line_size - 1)); //addr & va_VIRTUAL_ADDRESS_MASK
    
    // Invalidate instruction cache by va to PoU (Point of unification). 
    _ARM_MCR(15, 0, va, 7, 5, 1);
    
    // synchronize context on this processor 
    _ARM_ISB();
}

void arm_icache_invalidate_mlines(const void * addr, size_t length)
{
    uint32_t va;
    uint32_t csidr = 0, line_size = 0;
    const void * end_addr = (const void *)((uint32_t)addr + length);

    // get the cache line size
    _ARM_MRC(15, 1, csidr, 0, 0, 0);
    line_size = 1 << ((csidr & 0x7) + 4);    
    
    do
    {
        // Clean data cache line to PoC (Point of Coherence) by va. 
        va = (uint32_t) ((uint32_t)addr & (~(line_size - 1))); //addr & va_VIRTUAL_ADDRESS_MASK
        _ARM_MCR(15, 0, va, 7, 5, 1);
        // increment addres to next line and decrement lenght 
        addr = (const void *) ((uint32_t)addr + line_size);
    } while (addr < end_addr);
    
    // synchronize context on this processor 
    _ARM_ISB();
}


////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
