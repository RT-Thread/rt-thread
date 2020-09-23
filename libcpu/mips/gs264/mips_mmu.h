/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-26     lizhirui     the first version
 */
#ifndef __MIPS_MMU_H__
#define __MIPS_MMU_H__

typedef enum cpu_mode_t
{
    CPU_MODE_KERNEL = 0x00,
    CPU_MODE_SUPERVISOR = 0x01,
    CPU_MODE_USER = 0x02
}cpu_mode_t;

typedef enum page_mask_enum_t
{
    PAGE_MASK_4KB = 0x00,
    PAGE_MASK_16KB = 0x03,
    PAGE_MASK_64KB = 0x0F,
    PAGE_MASK_256KB = 0x3F,
    PAGE_MASK_1MB = 0xFF,
    PAGE_MASK_4MB = 0x3FF,
    PAGE_MASK_16MB = 0xFFF,
    PAGE_MASK_64MB = 0x3FFF,
    PAGE_MASK_256MB = 0xFFFF,
    PAGE_MASK_1GB = 0x3FFFF
}page_mask_enum_t;

typedef struct page_mask_t
{
    uint64_t : 11;
    uint64_t : 2;
    uint64_t mask : 18;
    uint64_t : 33;
}page_mask_t;

typedef struct entry_lo_t
{
    uint64_t g : 1;
    uint64_t v : 1;
    uint64_t d : 1;
    uint64_t c : 3;
    uint64_t pfn : 24;
    uint64_t pfnx : 3;
    uint64_t : 29;
    uint64_t xi : 1;
    uint64_t ri : 1;
}entry_lo_t;

typedef struct entry_hi_t
{
    uint64_t asid : 8;
    uint64_t : 5;
    uint64_t vpn2 : 27;
    uint64_t : 22;
    uint64_t r : 2;
}entry_hi_t;

typedef struct tlb_item_t
{
    entry_lo_t entry_lo[2];
    entry_hi_t entry_hi;
    page_mask_t page_mask;
}tlb_item_t;

#define read_c0_diag()        __read_32bit_c0_register($22, 0)
#define write_c0_diag(val)    __write_32bit_c0_register($22, 0, val)
#define read_c0_badvaddr()    __read_64bit_c0_register($8, 0)
#define read_c0_random()      __read_32bit_c0_register($1, 0)

#define reg_type_convert(variable,new_type) *((new_type *)(&variable))
#define lowbit(x) ((x) & (-(x)))

void mmu_init();
void mmu_set_cpu_mode(cpu_mode_t cpu_mode);
cpu_mode_t mmu_get_cpu_mode();
void mmu_clear_tlb();
void mmu_clear_itlb();
uint32_t mmu_get_max_tlb_index();
void mmu_tlb_write_indexed(uint32_t index,tlb_item_t *tlb_item);
void mmu_tlb_write_random(tlb_item_t *tlb_item);
void mmu_tlb_read(uint32_t index,tlb_item_t *tlb_item);
uint32_t mmu_tlb_find(uint64_t vpn,uint32_t asid,uint32_t *index);
void mmu_tlb_item_init(tlb_item_t *tlb_item);
void mmu_set_map(uint64_t vpn,uint64_t ppn,page_mask_enum_t page_mask,uint32_t asid,uint32_t global);
uint32_t mmu_tlb_get_random();
uint32_t mmu_tlb_get_index();
void mmu_tlb_set_index(uint32_t index);
uint32_t mmu_tlb_is_matched();
uint64_t mmu_tlb_get_bad_vaddr();

void tlb_dump();

#endif