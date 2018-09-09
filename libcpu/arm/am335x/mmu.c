/*
 * File      : mmu.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-01-10     bernard      porting to AM1808
 */

#include <rtthread.h>
#include "am33xx.h"

#define DESC_SEC		(0x2)
#define CB				(3<<2)  //cache_on, write_back
#define CNB				(2<<2)  //cache_on, write_through
#define NCB				(1<<2)  //cache_off,WR_BUF on
#define NCNB			(0<<2)  //cache_off,WR_BUF off
#define AP_RW			(3<<10) //supervisor=RW, user=RW
#define AP_RO			(2<<10) //supervisor=RW, user=RO

#define DOMAIN_FAULT	(0x0)
#define DOMAIN_CHK		(0x1)
#define DOMAIN_NOTCHK	(0x3)
#define DOMAIN0			(0x0<<5)
#define DOMAIN1			(0x1<<5)

#define DOMAIN0_ATTR	(DOMAIN_CHK<<0)
#define DOMAIN1_ATTR	(DOMAIN_FAULT<<2)

#define RW_CB		(AP_RW|DOMAIN0|CB|DESC_SEC)		/* Read/Write, cache, write back */
#define RW_CNB		(AP_RW|DOMAIN0|CNB|DESC_SEC)	/* Read/Write, cache, write through */
#define RW_NCNB		(AP_RW|DOMAIN0|NCNB|DESC_SEC)	/* Read/Write without cache and write buffer */
#define RW_FAULT	(AP_RW|DOMAIN1|NCNB|DESC_SEC)	/* Read/Write without cache and write buffer */

extern void rt_cpu_dcache_disable(void);
extern void rt_hw_cpu_dcache_enable(void);
extern void rt_cpu_icache_disable(void);
extern void rt_hw_cpu_icache_enable(void);
extern void rt_cpu_mmu_disable(void);
extern void rt_cpu_mmu_enable(void);
extern void rt_cpu_tlb_set(register rt_uint32_t i);

void mmu_disable_dcache()
{
	rt_cpu_dcache_disable();
}

void mmu_enable_dcache()
{
	rt_hw_cpu_dcache_enable();
}

void mmu_disable_icache()
{
	rt_cpu_icache_disable();
}

void mmu_enable_icache()
{
	rt_hw_cpu_icache_enable();
}

void mmu_disable()
{
	rt_cpu_mmu_disable();
}

void mmu_enable()
{
	rt_cpu_mmu_enable();
}

void mmu_setttbase(register rt_uint32_t i)
{
	register rt_uint32_t value;

   /* Invalidates all TLBs.Domain access is selected as
    * client by configuring domain access register,
    * in that case access controlled by permission value
    * set by page table entry
    */
	value = 0;
	asm volatile ("mcr p15, 0, %0, c8, c7, 0"::"r"(value));

	value = 0x55555555;
	asm volatile ("mcr p15, 0, %0, c3, c0, 0"::"r"(value));
	
	rt_cpu_tlb_set(i);
}

void mmu_set_domain(register rt_uint32_t i)
{
	asm volatile ("mcr p15,0, %0, c3, c0,  0": :"r" (i));
}

void mmu_enable_alignfault()
{
	register rt_uint32_t i;

	/* read control register */
	asm volatile ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));

	i |= (1 << 1);

	/* write back to control register */
	asm volatile ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));
}

void mmu_disable_alignfault()
{
	register rt_uint32_t i;

	/* read control register */
	asm volatile ("mrc p15, 0, %0, c1, c0, 0":"=r" (i));

	i &= ~(1 << 1);

	/* write back to control register */
	asm volatile ("mcr p15, 0, %0, c1, c0, 0": :"r" (i));
}

void mmu_clean_invalidated_cache_index(int index)
{
	asm volatile ("mcr p15, 0, %0, c7, c14, 2": :"r" (index));
}

void mmu_clean_dcache(rt_uint32_t buffer, rt_uint32_t size)
{
	unsigned int ptr;

	ptr = buffer & ~0x1f;

	while (ptr < buffer + size)
	{
		asm volatile ("mcr p15, 0, %0, c7, c10, 1": :"r" (ptr));
		ptr += 32;
	}
}

void mmu_invalidate_dcache(rt_uint32_t buffer, rt_uint32_t size)
{
	unsigned int ptr;

	ptr = buffer & ~0x1f;

	while (ptr < buffer + size)
	{
		asm volatile ("mcr p15, 0, %0, c7, c6, 1": :"r" (ptr));
		ptr += 32;
	}
}

void mmu_invalidate_tlb()
{
	asm volatile ("mcr p15, 0, %0, c8, c7, 0": :"r" (0));
}

void mmu_invalidate_icache()
{
	asm volatile ("mcr p15, 0, %0, c7, c5, 0": :"r" (0));
}

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

void rt_hw_mmu_init(void)
{
	/* disable I/D cache */
	mmu_disable_dcache();
	mmu_disable_icache();
	mmu_disable();
	mmu_invalidate_tlb();

	/* set page table */
	mmu_setmtt(0x00000000, 0xFFFFFFFF, 0x00000000, RW_NCNB);    /* None cached for 4G memory	*/
	mmu_setmtt(0xC0000000, 0xC8000000-1, 0xC0000000, RW_CB);    /* 128M cached DDR memory 		*/
	mmu_setmtt(0xD0000000, 0xD8000000-1, 0xC0000000, RW_NCNB);  /* 128M none-cached DDR memory */
	mmu_setmtt(0x80000000, 0x80020000-1, 0x80000000, RW_CB);    /* 128k OnChip memory 			*/

	/* set MMU table address */
	mmu_setttbase((rt_uint32_t)_page_table);

    /* enables MMU */
    mmu_enable();

    /* enable Instruction Cache */
    mmu_enable_icache();

    /* enable Data Cache */
    mmu_enable_dcache();
}

