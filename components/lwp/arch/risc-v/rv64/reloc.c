#include "mm_aspace.h"
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
    Elf64_Word st_name;
    Elf64_Addr st_value;
    Elf64_Word st_size;
    unsigned char st_info;
    unsigned char st_other;
    Elf64_Half st_shndx;
} Elf64_sym;

#ifdef ARCH_MM_MMU
void arch_elf_reloc(rt_aspace_t aspace, void *text_start, void *rel_dyn_start, size_t rel_dyn_size, void *got_start, size_t got_size, Elf64_sym *dynsym)
{
    size_t rel_off;
    void* addr;

    if (rel_dyn_size && !dynsym)
    {
        return;
    }
    for (rel_off = 0; rel_off < rel_dyn_size; rel_off += 8)
    {
        uint32_t v1, v2;

        addr = rt_hw_mmu_v2p(aspace, (void *)(((rt_size_t)rel_dyn_start) + rel_off));
        memcpy(&v1, addr, 4);
        addr = rt_hw_mmu_v2p(aspace, (void *)(((rt_size_t)rel_dyn_start) + rel_off + 4));
        memcpy(&v2, addr, 4);

        addr = rt_hw_mmu_v2p(aspace, (void *)((rt_size_t)text_start + v1));
        if ((v2 & 0xff) == R_ARM_RELATIVE)
        {
            *(rt_size_t*)addr += (rt_size_t)text_start;
        }
        else if ((v2 & 0xff) == R_ARM_ABS32)
        {
            uint32_t t;
            t = (v2 >> 8);
            if (t) /* 0 is UDF */
            {
                *(rt_size_t*)addr = (((rt_size_t)text_start) + dynsym[t].st_value);
            }
        }
    }
    /* modify got */
    if (got_size)
    {
        uint32_t *got_item = (uint32_t*)got_start;

        for (rel_off = 0; rel_off < got_size; rel_off += 4, got_item++)
        {
            addr = rt_hw_mmu_v2p(aspace, got_item);
            *(rt_size_t *)addr += (rt_size_t)text_start;
        }
    }
}
#else

void arch_elf_reloc(void *text_start, void *rel_dyn_start, size_t rel_dyn_size, void *got_start, size_t got_size, Elf64_sym *dynsym)
{
    size_t rel_off;

    if (rel_dyn_size && !dynsym)
    {
        return;
    }
    for (rel_off = 0; rel_off < rel_dyn_size; rel_off += 8)
    {
        uint32_t v1, v2;

        memcpy(&v1, ((rt_uint8_t *)rel_dyn_start) + rel_off, 4);
        memcpy(&v2, ((rt_uint8_t *)rel_dyn_start) + rel_off + 4, 4);

        if ((v2 & 0xff) == R_ARM_RELATIVE)
        {
            *(uint32_t*)(((rt_size_t)text_start) + v1) += (uint32_t)text_start;
        }
        else if ((v2 & 0xff) == R_ARM_ABS32)
        {
            uint32_t t;
            t = (v2 >> 8);
            if (t) /* 0 is UDF */
            {
                *(uint32_t*)(((rt_size_t)text_start) + v1) = (uint32_t)(((rt_size_t)text_start) + dynsym[t].st_value);
            }
        }
    }
    /* modify got */
    if (got_size)
    {
        uint32_t *got_item = (uint32_t*)got_start;

        for (rel_off = 0; rel_off < got_size; rel_off += 4, got_item++)
        {
            *got_item += (uint32_t)text_start;
        }
    }
}
#endif
