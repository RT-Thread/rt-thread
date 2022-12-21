/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-28     JasonHu      first version
 */

#include <rtthread.h>
#include <stdint.h>
#include <string.h>
#include <elf.h>
#ifdef ARCH_MM_MMU
#include <mmu.h>
#include <page.h>
#endif

typedef struct
{
    Elf32_Word st_name;
    Elf32_Addr st_value;
    Elf32_Word st_size;
    unsigned char st_info;
    unsigned char st_other;
    Elf32_Half st_shndx;
} Elf32_sym;

#ifdef ARCH_MM_MMU
void arch_elf_reloc(rt_mmu_info *m_info, void *text_start, void *rel_dyn_start, size_t rel_dyn_size, void *got_start, size_t got_size, Elf32_sym *dynsym)
{

}
#else

void arch_elf_reloc(void *text_start, void *rel_dyn_start, size_t rel_dyn_size, void *got_start, size_t got_size, Elf32_sym *dynsym)
{

}
#endif
