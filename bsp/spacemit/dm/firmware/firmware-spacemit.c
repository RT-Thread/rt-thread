/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <elf.h>
#include <dt-bindings/size.h>

rt_weak rt_ubase_t spacemit_firmwares_start, spacemit_firmwares_end;

rt_bool_t spacemit_firmware_find(const char *name, rt_ubase_t *out_base, rt_size_t *out_size)
{
    rt_ubase_t *start = &spacemit_firmwares_start, *end = &spacemit_firmwares_end;

    while (start < end)
    {
        if (!rt_strcmp((const char *)(*start), name))
        {
            ++start;

            *out_base = *start++;
            *out_size = *start++;
            *out_size -= *out_base;

            return RT_TRUE;
        }

        start += 3;
    }

    return RT_FALSE;
}

rt_err_t spacemit_firmware_load_elf(const char *name, rt_ubase_t phy_addr)
{
    void *vma;
    rt_ubase_t base, size, load_base, seg_phys, seg_src, memsz, filesz, copy, chunk;
    Elf32_Ehdr *ehdr;
    Elf32_Phdr *phdr;
    const rt_ubase_t MAX_IOMAP_SIZE = 128 * SIZE_MB;

    if (!spacemit_firmware_find(name, &base, &size))
    {
        return -RT_EEMPTY;
    }

    ehdr = (Elf32_Ehdr *)base;

    if (rt_memcmp(ehdr->e_ident, ELFMAG, SELFMAG) != 0)
    {
        return -RT_EINVAL;
    }

    if (ehdr->e_ident[EI_CLASS] != ELFCLASS32)
    {
        return -RT_EINVAL;
    }

    if (ehdr->e_phoff == 0 || ehdr->e_phnum == 0)
    {
        return -RT_EINVAL;
    }

    phdr = (Elf32_Phdr *)(base + ehdr->e_phoff);
    load_base = phy_addr - ehdr->e_entry;

    for (int i = 0; i < ehdr->e_phnum; ++i)
    {
        Elf32_Phdr *p = &phdr[i];

        if (p->p_type != PT_LOAD)
        {
            continue;
        }

        if (p->p_offset + p->p_filesz > size)
        {
            return -RT_EINVAL;
        }

        seg_phys = load_base + p->p_paddr;
        seg_src = base + p->p_offset;
        memsz = p->p_memsz;
        filesz = p->p_filesz;

        while (memsz > 0)
        {
            chunk = rt_min_t(rt_ubase_t, memsz, MAX_IOMAP_SIZE);

            if (!(vma = rt_ioremap((void *)seg_phys, chunk)))
            {
                return -RT_ENOMEM;
            }

            copy = filesz > chunk ? chunk : filesz;

            if (copy > 0)
            {
                rt_memcpy((void *)vma, (const void *)seg_src, copy);
                seg_src += copy;
                filesz -= copy;
            }

            if (chunk > copy)
            {
                rt_memset((void *)((rt_ubase_t)vma + copy), 0, chunk - copy);
            }

            rt_iounmap(vma);

            seg_phys += chunk;
            memsz -= chunk;
        }
    }

    return RT_EOK;
}
