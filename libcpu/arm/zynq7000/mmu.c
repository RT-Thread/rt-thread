/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-20     Bernard      first version
 */

#include <rtthread.h>
#include <rthw.h>
#include <board.h>

#include "cp15.h"

#define DESC_SEC       (0x2)
#define CB             (3<<2)  //cache_on, write_back
#define CNB            (2<<2)  //cache_on, write_through
#define NCB            (1<<2)  //cache_off,WR_BUF on
#define NCNB           (0<<2)  //cache_off,WR_BUF off
#define AP_RW          (3<<10) //supervisor=RW, user=RW
#define AP_RO          (2<<10) //supervisor=RW, user=RO
#define XN             (1<<4)  //eXecute Never

#define DOMAIN_FAULT   (0x0)
#define DOMAIN_CHK     (0x1)
#define DOMAIN_NOTCHK  (0x3)
#define DOMAIN0        (0x0<<5)
#define DOMAIN1        (0x1<<5)

#define DOMAIN0_ATTR   (DOMAIN_CHK<<0)
#define DOMAIN1_ATTR   (DOMAIN_FAULT<<2)

/* Read/Write, cache, write back */
#define RW_CB          (AP_RW|DOMAIN0|CB|DESC_SEC)
/* Read/Write, cache, write through */
#define RW_CNB         (AP_RW|DOMAIN0|CNB|DESC_SEC)
/* Read/Write, device type */
#define RW_NCB         (AP_RW|DOMAIN0|NCB|DESC_SEC)
/* Read/Write strongly ordered type */
#define RW_NCNB        (AP_RW|DOMAIN0|NCNB|DESC_SEC)
/* Read/Write without cache and write buffer, no execute */
#define RW_NCNBXN      (AP_RW|DOMAIN0|NCNB|DESC_SEC|XN)
/* Read/Write without cache and write buffer */
#define RW_FAULT       (AP_RW|DOMAIN1|NCNB|DESC_SEC)

void rt_hw_cpu_dump_page_table(rt_uint32_t *ptb)
{
    int i;
    int fcnt = 0;

    rt_kprintf("page table@%p\n", ptb);
    for (i = 0; i < 1024*4; i++)
    {
        rt_uint32_t pte1 = ptb[i];
        if ((pte1 & 0x3) == 0)
        {
            rt_kprintf("%03x: ", i);
            fcnt++;
            if (fcnt == 16)
            {
                rt_kprintf("fault\n");
                fcnt = 0;
            }
            continue;
        }
        if (fcnt != 0)
        {
            rt_kprintf("fault\n");
            fcnt = 0;
        }

        rt_kprintf("%03x: %08x: ", i, pte1);
        if ((pte1 & 0x3) == 0x3)
        {
            rt_kprintf("LPAE\n");
        }
        else if ((pte1 & 0x3) == 0x1)
        {
            rt_kprintf("pte,ns:%d,domain:%d\n",
                       (pte1 >> 3) & 0x1, (pte1 >> 5) & 0xf);
            /*
             *rt_hw_cpu_dump_page_table_2nd((void*)((pte1 & 0xfffffc000)
             *                               - 0x80000000 + 0xC0000000));
             */
        }
        else if (pte1 & (1 << 18))
        {
            rt_kprintf("super section,ns:%d,ap:%x,xn:%d,texcb:%02x\n",
                       (pte1 >> 19) & 0x1,
                       ((pte1 >> 13) | (pte1 >> 10))& 0xf,
                       (pte1 >> 4) & 0x1,
                       ((pte1 >> 10) | (pte1 >> 2)) & 0x1f);
        }
        else
        {
            rt_kprintf("section,ns:%d,ap:%x,"
                       "xn:%d,texcb:%02x,domain:%d\n",
                       (pte1 >> 19) & 0x1,
                       ((pte1 >> 13) | (pte1 >> 10))& 0xf,
                       (pte1 >> 4) & 0x1,
                       (((pte1 & (0x7 << 12)) >> 10) |
                        ((pte1 &        0x0c) >>  2)) & 0x1f,
                       (pte1 >> 5) & 0xf);
        }
    }
}

/* level1 page table, each entry for 1MB memory. */
/* MMUTable is the name used by codes of Xilinx */
volatile unsigned long MMUTable[4*1024] RT_SECTION("mmu_tbl") __attribute__((aligned(16*1024)));
void rt_hw_mmu_setmtt(rt_uint32_t vaddrStart,
                      rt_uint32_t vaddrEnd,
                      rt_uint32_t paddrStart,
                      rt_uint32_t attr)
{
    volatile rt_uint32_t *pTT;
    volatile int i, nSec;
    pTT  = (rt_uint32_t *)MMUTable + (vaddrStart >> 20);
    nSec = (vaddrEnd >> 20) - (vaddrStart >> 20);
    for(i = 0; i <= nSec; i++)
    {
        *pTT = attr | (((paddrStart >> 20) + i) << 20);
        pTT++;
    }
}

unsigned long rt_hw_set_domain_register(unsigned long domain_val)
{
    unsigned long old_domain;

    asm volatile ("mrc p15, 0, %0, c3, c0\n" : "=r" (old_domain));
    asm volatile ("mcr p15, 0, %0, c3, c0\n" : :"r" (domain_val) : "memory");

    return old_domain;
}

void rt_hw_mmu_init(void)
{
    extern rt_uint32_t __text_start;
    rt_hw_cpu_dcache_disable();
    rt_hw_cpu_icache_disable();
    rt_cpu_mmu_disable();

    /* set page table */
    /* no access to the memory below .text */
    /* 128M cached DDR memory */
    rt_hw_mmu_setmtt((rt_uint32_t)&__text_start, 0x20000000-1,
                     0x1ff00000, RW_CB);
    /* PL region */
    rt_hw_mmu_setmtt(0x40000000, 0xBFFFFFFF, 0x40000000, RW_NCNBXN);
    /* IOP registers */
    rt_hw_mmu_setmtt(0xE0000000, 0xE02FFFFF, 0xE0000000, RW_NCNBXN);
    /* no access to the SMC memory(enable it if you want) */
    /* SLCR, PS and CPU private registers, note we map more memory space as the
     * entry is 1MB in size. */
    rt_hw_mmu_setmtt(0xF8000000, 0xF8FFFFFF, 0xF8000000, RW_NCNBXN);

    /*rt_hw_cpu_dump_page_table(MMUTable);*/

    /* become clients for all domains */
    rt_hw_set_domain_register(0x55555555);

    rt_cpu_tlb_set(MMUTable);

    rt_cpu_mmu_enable();

    rt_hw_cpu_icache_enable();
    rt_hw_cpu_dcache_enable();
}

