#include <rtthread.h>
#include <stdint.h>
#include <string.h>
#include <elf.h>
#ifdef RT_USING_USERSPACE
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

#ifdef RT_USING_USERSPACE
void lwp_elf_reloc(rt_mmu_info *m_info, void *text_start, void *rel_dyn_start, size_t rel_dyn_size, void *got_start, size_t got_size, Elf32_sym *dynsym)
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

        /*
        memcpy(&v1, rel_dyn_start + rel_off, 4);
        memcpy(&v2, rel_dyn_start + rel_off + 4, 4);
        */

        addr = rt_hw_mmu_v2p(m_info, rel_dyn_start + rel_off);
        addr -= PV_OFFSET;
        memcpy(&v1, addr, 4);
        addr = rt_hw_mmu_v2p(m_info, rel_dyn_start + rel_off + 4);
        addr -= PV_OFFSET;
        memcpy(&v2, addr, 4);

        addr = rt_hw_mmu_v2p(m_info, text_start + v1);
        addr -= PV_OFFSET;
        if ((v2 & 0xff) == R_ARM_RELATIVE)
        {
            // *(uint32_t*)(text_start + v1) += (uint32_t)text_start;
            *(uint32_t*)addr += (uint32_t)text_start;
        }
        else if ((v2 & 0xff) == R_ARM_ABS32)
        {
            uint32_t t;
            t = (v2 >> 8);
            if (t) /* 0 is UDF */
            {
                // *(uint32_t*)(text_start + v1) = (uint32_t)(text_start + dynsym[t].st_value);
                *(uint32_t*)addr = (uint32_t)(text_start + dynsym[t].st_value);
            }
        }
    }
    /* modify got */
    if (got_size)
    {
        uint32_t *got_item = (uint32_t*)got_start;

        for (rel_off = 0; rel_off < got_size; rel_off += 4, got_item++)
        {
            //*got_item += (uint32_t)text_start;
            addr = rt_hw_mmu_v2p(m_info, got_item);
            addr -= PV_OFFSET;
            *(uint32_t *)addr += (uint32_t)text_start;
        }
    }
}
#else

void lwp_elf_reloc(void *text_start, void *rel_dyn_start, size_t rel_dyn_size, void *got_start, size_t got_size, Elf32_sym *dynsym)
{
    size_t rel_off;

    if (rel_dyn_size && !dynsym)
    {
        return;
    }
    for (rel_off = 0; rel_off < rel_dyn_size; rel_off += 8)
    {
        uint32_t v1, v2;

        memcpy(&v1, rel_dyn_start + rel_off, 4);
        memcpy(&v2, rel_dyn_start + rel_off + 4, 4);

        if ((v2 & 0xff) == R_ARM_RELATIVE)
        {
            *(uint32_t*)(text_start + v1) += (uint32_t)text_start;
        }
        else if ((v2 & 0xff) == R_ARM_ABS32)
        {
            uint32_t t;
            t = (v2 >> 8);
            if (t) /* 0 is UDF */
            {
                *(uint32_t*)(text_start + v1) = (uint32_t)(text_start + dynsym[t].st_value);
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
