/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-28     GuEe-GUI     the first version
 */

#ifndef __MMU_H_
#define __MMU_H_

#include <rtthread.h>

/* normal memory wra mapping type */
#define NORMAL_MEM          0
/* normal nocache memory mapping type */
#define NORMAL_NOCACHE_MEM  1
/* device mapping type */
#define DEVICE_MEM          2

#define MMU_MAP_ERROR_VANOTALIGN    (-1)
#define MMU_MAP_ERROR_PANOTALIGN    (-2)
#define MMU_MAP_ERROR_NOPAGE        (-3)
#define MMU_MAP_ERROR_CONFLICT      (-4)

struct mem_desc
{
    unsigned long vaddr_start;
    unsigned long vaddr_end;
    unsigned long paddr_start;
    unsigned long attr;
};

#define MMU_AF_SHIFT        10
#define MMU_SHARED_SHIFT    8
#define MMU_AP_SHIFT        6
#define MMU_MA_SHIFT        2

#define MMU_AP_KAUN         0UL /* kernel r/w, user none */
#define MMU_AP_KAUA         1UL /* kernel r/w, user r/w */
#define MMU_AP_KRUN         2UL /* kernel r, user none */
#define MMU_AP_KRUR         3UL /* kernel r, user r */

#define MMU_MAP_CUSTOM(ap, mtype) \
(\
    (0x1UL << MMU_AF_SHIFT) |\
    (0x2UL << MMU_SHARED_SHIFT) |\
    ((ap) << MMU_AP_SHIFT) |\
    ((mtype) << MMU_MA_SHIFT)\
)
#define MMU_MAP_K_RO        MMU_MAP_CUSTOM(MMU_AP_KRUN, NORMAL_MEM)
#define MMU_MAP_K_RWCB      MMU_MAP_CUSTOM(MMU_AP_KAUN, NORMAL_MEM)
#define MMU_MAP_K_RW        MMU_MAP_CUSTOM(MMU_AP_KAUN, NORMAL_NOCACHE_MEM)
#define MMU_MAP_K_DEVICE    MMU_MAP_CUSTOM(MMU_AP_KAUN, DEVICE_MEM)
#define MMU_MAP_U_RO        MMU_MAP_CUSTOM(MMU_AP_KRUR, NORMAL_NOCACHE_MEM)
#define MMU_MAP_U_RWCB      MMU_MAP_CUSTOM(MMU_AP_KAUA, NORMAL_MEM)
#define MMU_MAP_U_RW        MMU_MAP_CUSTOM(MMU_AP_KAUA, NORMAL_NOCACHE_MEM)
#define MMU_MAP_U_DEVICE    MMU_MAP_CUSTOM(MMU_AP_KAUA, DEVICE_MEM)

void rt_hw_init_mmu_table(struct mem_desc *mdesc, rt_size_t desc_nr);
void rt_hw_mmu_init(void);
int rt_hw_mmu_map(unsigned long addr, unsigned long size, unsigned long attr);

void rt_hw_dcache_flush_all(void);
void rt_hw_dcache_invalidate_all(void);
void rt_hw_dcache_flush_range(unsigned long start_addr, unsigned long size);
void rt_hw_dcache_invalidate_range(unsigned long start_addr,unsigned long size);

void rt_hw_icache_invalidate_all();
void rt_hw_icache_invalidate_range(unsigned long start_addr, int size);

#endif /* __MMU_H_ */
