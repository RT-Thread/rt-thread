/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-01-10     bernard      porting to AM1808
 */

#include <rtthread.h>
#include <mmu.h>
#include <cp15.h>

// [ref] DDI0344K_cortex_a8_r3p2_trm.pdf: 3.2.33 c2, Translation Table Base Control Register
//      Bit     Field           Description
//      31-6    Reverse
//      5       PD1             Specifies occurrence of a translation table walk on a TLB miss when using Translation Table Base Register 1.
//      4       PD0             Specifies occurrence of a translation table walk on a TLB miss when using Translation Table Base Register 0.
//      3       Reverse
//      2-0     N               Specifies the boundary size of Translation Table Base Register 0:
//                              b000 = 16KB, reset value
//                              b001 = 8KB
//                              b010 = 4KB
//                              b011 = 2KB
//                              b100 = 1KB
//                              b101 = 512B
//                              b110 = 256B
//                              b111 = 128B
static volatile unsigned int _page_table[4*1024] __attribute__((aligned(16*1024)));
void mmu_setmtt(uint32_t vaddrStart, uint32_t vaddrEnd, uint32_t paddrStart, uint32_t attr)
{
    volatile uint32_t *pTT;
    volatile int i,nSec;
    pTT=(uint32_t *)_page_table+(vaddrStart>>20);
    nSec=(vaddrEnd>>20)-(vaddrStart>>20);
    for(i=0;i<=nSec;i++)
    {
        *pTT = attr |(((paddrStart>>20)+i)<<20);
        pTT++;
    }
}

/* set page table */
RT_WEAK void mmu_setmtts(void)
{
    mmu_setmtt(0x00000000, 0xFFFFFFFF,     0x00000000, RW_NCNB);  /* None cached for 4G memory   */
    mmu_setmtt(0x80200000, 0x80800000 - 1, 0x80200000, RW_CB);    /* 126M cached DDR memory      */
    mmu_setmtt(0x80000000, 0x80200000 - 1, 0x80000000, RW_NCNB);  /* 2M none-cached DDR memory   */
    mmu_setmtt(0x402F0000, 0x40300000 - 1, 0x402F0000, RW_CB);    /* 63K OnChip memory 			 */
}

void rt_hw_mmu_init(void)
{
    rt_cpu_cache_disable();
    rt_cpu_mmu_disable();

    rt_cpu_ctl_feature_disable(CP15_SCTLR_AFE | CP15_SCTLR_TRE | CP15_SCTLR_A);
    rt_cpu_domain_access_client_set();
    rt_cpu_tlb_invalidate();
    mmu_setmtts();
    rt_cpu_tlb_set((uint32_t)_page_table);

    rt_cpu_mmu_enable();
    rt_cpu_cache_enable();
}

