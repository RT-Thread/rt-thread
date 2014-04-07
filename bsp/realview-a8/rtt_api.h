/*
 *  serial.c UART driver
 *
 * COPYRIGHT (C) 2014, Shanghai Real-Thread Technology Co., Ltd
 *
 *  This file is part of RT-Thread (http://www.rt-thread.org)
 *
 *  All rights reserved.
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
 * 2014-04-07     Grissiom     first version
 */

#ifndef __RTT_API_H__
#define __RTT_API_H__

/* 4MB in size */
#define VMM_SIZE        0x400000
#define VMM_END         0xc8000000
#define VMM_BEGIN       (VMM_END - VMM_SIZE)

/* VMM Memory Map:
 *
 * --- VMM_BEGIN --- +------+
 *     .vectors      | 4KB  |
 *   .text.share     |      |
 * ----------------- +      |
 * guest vector page | 4KB  |
 * ----------------- +      |
 *   .data.share     | 4KB  |
 * ----------------- +      |
 *    .bss.share     | 4KB  |
 * -- SHARE_BASE  -- +      | 1MB
 *  shared context          | shared region
 * -----------------        |
 *      blabla...           |
 * ----------------- +------+
 *  vmm text                |
 *      rodata              |
 *      blabla...           |
 * -----------------        | private region
 *  vmm data                |
 * -----------------        |
 *  vmm bss                 |
 * ---- VMM_END ---- +------+
 *
 */

/* 1MB is one level one page table entry, if we want to page table to be
 * simple(avoid TLB miss), we could allocate 1MB for shared memory. */
#define VMM_SHARE_PGSZ    (1024*1024)

/* the size and position of shared code text */
#define VMM_SHARE_TEXT_PGSZ 4096

/* the size and position of vector's page size in Linux */
#define LINUX_VECTOR_PGSZ   4096
#define LINUX_VECTOR_POS  (VMM_BEGIN + VMM_SHARE_TEXT_PGSZ)

/* the size and position of shared code data */
#define VMM_SHARE_DATA_PGSZ 4096
#define VMM_SHARE_DATA_POS  (LINUX_VECTOR_POS + LINUX_VECTOR_PGSZ)

/* the size and position of shared code bss */
#define VMM_SHARE_BSS_PGSZ  4096
#define VMM_SHARE_BSS_POS   (VMM_SHARE_DATA_POS + VMM_SHARE_DATA_PGSZ)

/* the size and position of shared code bss */
#define VMM_SHARE_CTX_PGSZ  (VMM_SHARE_PGSZ - \
                             LINUX_VECTOR_PGSZ - \
                             VMM_SHARE_TEXT_PGSZ - \
                             VMM_SHARE_DATA_PGSZ - \
                             VMM_SHARE_BSS_PGSZ)
#if VMM_SHARE_CTX_PGSZ <= 0
#error
#endif

#define VMM_SHARE_CTX_POS   (VMM_SHARE_BSS_POS + VMM_SHARE_BSS_PGSZ)

/* the size of FIQ stack page size in RT-Thread */
#define RT_FIQ_STACK_PGSZ 0

/* the size of IRQ stack page size in RT-Thread */
#define RT_IRQ_STACK_PGSZ 4096

#ifdef  HEAP_END
#undef  HEAP_END
#endif
#define HEAP_END  (VMM_END)

#define RT_VMM_VIRQ_TRIGGER  10

#define RT_VMM_STACK_SIZE  1024

/* the max number of iomap entries */
#define RT_VMM_IOMAP_MAXNR   16

#ifndef __iomem
#define __iomem
#endif

#define IRQS_NR_32           ((96 + 31)/32)

/*#define RT_VMM_USING_DOMAIN*/

#ifndef __ASSEMBLY__

/* keep consistent with linux/arch/arm/include/vmm/vmm.h */
struct vmm_context
{
    /* the status of vGuest irq, read only for RT-Thread */
    volatile unsigned long virq_status;

    /* has interrupt pended on vGuest OS IRQ */
    volatile unsigned long virq_pended;

    /* pending interrupt for vGuest OS */
    volatile unsigned long virq_pending[IRQS_NR_32];
};

struct vmm_domain
{
    /* the number of kernel domain */
    char kernel;
    /* the number of user domain */
    char user;
    /* the number of io domain */
    char io;
    /* the number of vmm domain */
    char vmm;
    /* the number of vmm_share domain */
    char vmm_share;
};

struct vmm_iomap
{
	const char name[16];        /* iomap name       */

	unsigned long pa;           /* physical address */
	volatile void __iomem * va; /* virtual address  */
	size_t size;                /* memory size      */
};

struct vmm_entry_param
{
    struct vmm_iomap *iomap;
    struct vmm_domain *domain;
};

typedef void (*vmm_entry_t)(struct vmm_entry_param* param);

struct rt_vmm_share_layout
{
    struct vmm_context     ctx;
};

#ifndef __KERNEL__
/* not in Linux, use better type check */
extern struct rt_vmm_share_layout rt_vmm_share;
#define RT_VMM_SHARE     (&rt_vmm_share)
#else
#define RT_VMM_SHARE     ((struct rt_vmm_share_layout*)VMM_SHARE_CTX_POS)
#endif

#endif

#endif /* end of include guard: __RTT_API_H__ */
