/*
 * File      : mmu.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "mmu.h"

#ifdef __CC_ARM
void mmu_setttbase(rt_uint32_t i)
{
	register rt_uint32_t value;

   /* Invalidates all TLBs.Domain access is selected as
    * client by configuring domain access register,
    * in that case access controlled by permission value
    * set by page table entry
    */
	value = 0;
    __asm
    {
        mcr p15, 0, value, c8, c7, 0
	}

	value = 0x55555555;
	__asm
	{
        mcr p15, 0, value, c3, c0, 0
        mcr p15, 0, i, c2, c0, 0
    }
}

void mmu_set_domain(rt_uint32_t i)
{
    __asm
    {
        mcr p15,0, i, c3, c0,  0
    }
}

void mmu_enable()
{
    register rt_uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        orr value, value, #0x01
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_disable()
{
    register rt_uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        bic value, value, #0x01
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_enable_icache()
{
    register rt_uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        orr value, value, #0x1000
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_enable_dcache()
{
    register rt_uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        orr value, value, #0x04
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_disable_icache()
{
    register rt_uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        bic value, value, #0x1000
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_disable_dcache()
{
    register rt_uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        bic value, value, #0x04
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_enable_alignfault()
{
    register rt_uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        orr value, value, #0x02
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_disable_alignfault()
{
    register rt_uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        bic value, value, #0x02
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_clean_invalidated_cache_index(int index)
{
    __asm
    {
        mcr p15, 0, index, c7, c14, 2
    }
}

void mmu_clean_invalidated_dcache(rt_uint32_t buffer, rt_uint32_t size)
{
    unsigned int ptr;

    ptr = buffer & ~(CACHE_LINE_SIZE - 1);

    while(ptr < buffer + size)
    {
    	__asm
    	{
    		MCR p15, 0, ptr, c7, c14, 1
    	}
        ptr += CACHE_LINE_SIZE;
    }
}

void mmu_clean_dcache(rt_uint32_t buffer, rt_uint32_t size)
{
	unsigned int ptr;

	ptr = buffer & ~(CACHE_LINE_SIZE - 1);

	while (ptr < buffer + size)
	{
		__asm
		{
			MCR p15, 0, ptr, c7, c10, 1
		}
		ptr += CACHE_LINE_SIZE;
	}
}

void mmu_invalidate_dcache(rt_uint32_t buffer, rt_uint32_t size)
{
	unsigned int ptr;

	ptr = buffer & ~(CACHE_LINE_SIZE - 1);

	while (ptr < buffer + size)
	{
		__asm
		{
			MCR p15, 0, ptr, c7, c6, 1
		}
		ptr += CACHE_LINE_SIZE;
	}
}

void mmu_invalidate_tlb()
{
    register rt_uint32_t value;

    value = 0;
    __asm
    {
        mcr p15, 0, value, c8, c7, 0
    }
}

void mmu_invalidate_icache()
{
    register rt_uint32_t value;

    value = 0;

    __asm
    {
        mcr p15, 0, value, c7, c5, 0
    }
}


void mmu_invalidate_dcache_all()
{
    register rt_uint32_t value;

    value = 0;

    __asm
    {
        mcr p15, 0, value, c7, c6, 0
    }
}
#elif defined(__GNUC__)
void mmu_setttbase(register rt_uint32_t i)
{
	register rt_uint32_t value;

   /* Invalidates all TLBs.Domain access is selected as
    * client by configuring domain access register,
    * in that case access controlled by permission value
    * set by page table entry
    */
	value = 0;
	asm ("mcr p15, 0, %0, c8, c7, 0"::"r"(value));

	value = 0x55555555;
	asm ("mcr p15, 0, %0, c3, c0, 0"::"r"(value));
	asm ("mcr p15, 0, %0, c2, c0, 0"::"r"(i));
}

void mmu_set_domain(register rt_uint32_t i)
{
	asm ("mcr p15,0, %0, c3, c0,  0": :"r" (i));
}

void mmu_enable()
{
	register rt_uint32_t i;

	/* read control register */
	asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));

	i |= 0x1;

	/* write back to control register */
	asm ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));
}

void mmu_disable()
{
	register rt_uint32_t i;

	/* read control register */
	asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));

	i &= ~0x1;

	/* write back to control register */
	asm ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));
}

void mmu_enable_icache()
{
	register rt_uint32_t i;

	/* read control register */
	asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));

	i |= (1 << 12);

	/* write back to control register */
	asm ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));
}

void mmu_enable_dcache()
{
	register rt_uint32_t i;

	/* read control register */
	asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));

	i |= (1 << 2);

	/* write back to control register */
	asm ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));
}

void mmu_disable_icache()
{
	register rt_uint32_t i;

	/* read control register */
	asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));

	i &= ~(1 << 12);

	/* write back to control register */
	asm ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));
}

void mmu_disable_dcache()
{
	register rt_uint32_t i;

	/* read control register */
	asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));

	i &= ~(1 << 2);

	/* write back to control register */
	asm ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));
}

void mmu_enable_alignfault()
{
	register rt_uint32_t i;

	/* read control register */
	asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));

	i |= (1 << 1);

	/* write back to control register */
	asm ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));
}

void mmu_disable_alignfault()
{
	register rt_uint32_t i;

	/* read control register */
	asm ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));

	i &= ~(1 << 1);

	/* write back to control register */
	asm ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));
}

void mmu_clean_invalidated_cache_index(int index)
{
	asm ("mcr p15, 0, %0, c7, c14, 2": :"r" (index));
}

void mmu_clean_invalidated_dcache(rt_uint32_t buffer, rt_uint32_t size)
{
    unsigned int ptr;

    ptr = buffer & ~(CACHE_LINE_SIZE - 1);

    while(ptr < buffer + size)
    {
    	asm ("mcr p15, 0, %0, c7, c14, 1": :"r" (ptr));
        ptr += CACHE_LINE_SIZE;
    }
}


void mmu_clean_dcache(rt_uint32_t buffer, rt_uint32_t size)
{
	unsigned int ptr;

	ptr = buffer & ~(CACHE_LINE_SIZE - 1);

	while (ptr < buffer + size)
	{
		asm ("mcr p15, 0, %0, c7, c10, 1": :"r" (ptr));
		ptr += CACHE_LINE_SIZE;
	}
}

void mmu_invalidate_dcache(rt_uint32_t buffer, rt_uint32_t size)
{
	unsigned int ptr;

	ptr = buffer & ~(CACHE_LINE_SIZE - 1);

	while (ptr < buffer + size)
	{
		asm ("mcr p15, 0, %0, c7, c6, 1": :"r" (ptr));
		ptr += CACHE_LINE_SIZE;
	}
}

void mmu_invalidate_tlb()
{
	asm ("mcr p15, 0, %0, c8, c7, 0": :"r" (0));
}

void mmu_invalidate_icache()
{
	asm ("mcr p15, 0, %0, c7, c5, 0": :"r" (0));
}

void mmu_invalidate_dcache_all()
{
    asm ("mcr p15, 0, %0, c7, c6, 0": :"r" (0));
}
#endif

/* level1 page table */
static volatile unsigned int _page_table[4*1024] __attribute__((aligned(16*1024)));
void mmu_setmtt(rt_uint32_t vaddrStart, rt_uint32_t vaddrEnd, rt_uint32_t paddrStart, rt_uint32_t attr)
{
    volatile rt_uint32_t *pTT;
    volatile int i,nSec;
    pTT=(rt_uint32_t *)_page_table+(vaddrStart>>20);
    nSec=(vaddrEnd>>20)-(vaddrStart>>20);
    for(i=0;i<=nSec;i++)
    {
		*pTT = attr |(((paddrStart>>20)+i)<<20);
		pTT++;
    }
}

void rt_hw_mmu_init(struct mem_desc *mdesc, rt_uint32_t size)
{
	/* disable I/D cache */
	mmu_disable_dcache();
	mmu_disable_icache();
	mmu_disable();
	mmu_invalidate_tlb();

	/* set page table */
	for (; size > 0; size--)
	{
		mmu_setmtt(mdesc->vaddr_start, mdesc->vaddr_end, 
			mdesc->paddr_start, mdesc->attr);
		mdesc++;
	}

	/* set MMU table address */
	mmu_setttbase((rt_uint32_t)_page_table);

    /* enables MMU */
    mmu_enable();

    /* enable Instruction Cache */
    mmu_enable_icache();

    /* enable Data Cache */
    mmu_enable_dcache();

    mmu_invalidate_icache();
    mmu_invalidate_dcache_all();
}

