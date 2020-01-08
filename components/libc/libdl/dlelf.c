/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author      Notes
 * 2018/08/29     Bernard     first version
 */

#include "dlmodule.h"
#include "dlelf.h"

#define DBG_TAG    "DLMD"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>          // must after of DEBUG_ENABLE or some other options

rt_err_t dlmodule_load_shared_object(struct rt_dlmodule* module, void *module_ptr)
{
    rt_bool_t linked   = RT_FALSE;
    rt_uint32_t index, module_size = 0;
    Elf32_Addr vstart_addr, vend_addr;
    rt_bool_t has_vstart;

    RT_ASSERT(module_ptr != RT_NULL);

    if (rt_memcmp(elf_module->e_ident, RTMMAG, SELFMAG) == 0)
    {
        /* rtmlinker finished */
        linked = RT_TRUE;
    }

    /* get the ELF image size */
    has_vstart = RT_FALSE;
    vstart_addr = vend_addr = RT_NULL;
    for (index = 0; index < elf_module->e_phnum; index++)
    {
        if (phdr[index].p_type != PT_LOAD)
            continue;

        LOG_D("LOAD segment: %d, 0x%p, 0x%08x", index, phdr[index].p_vaddr, phdr[index].p_memsz);

        if (phdr[index].p_memsz < phdr[index].p_filesz)
        {
            rt_kprintf("invalid elf: segment %d: p_memsz: %d, p_filesz: %d\n",
                       index, phdr[index].p_memsz, phdr[index].p_filesz);
            return RT_NULL;
        }
        if (!has_vstart)
        {
            vstart_addr = phdr[index].p_vaddr;
            vend_addr = phdr[index].p_vaddr + phdr[index].p_memsz;
            has_vstart = RT_TRUE;
            if (vend_addr < vstart_addr)
            {
                rt_kprintf("invalid elf: segment %d: p_vaddr: %d, p_memsz: %d\n",
                           index, phdr[index].p_vaddr, phdr[index].p_memsz);
                return RT_NULL;
            }
        }
        else
        {
            if (phdr[index].p_vaddr < vend_addr)
            {
                rt_kprintf("invalid elf: segment should be sorted and not overlapped\n");
                return RT_NULL;
            }
            if (phdr[index].p_vaddr > vend_addr + 16)
            {
                /* There should not be too much padding in the object files. */
                LOG_W("warning: too much padding before segment %d", index);
            }

            vend_addr = phdr[index].p_vaddr + phdr[index].p_memsz;
            if (vend_addr < phdr[index].p_vaddr)
            {
                rt_kprintf("invalid elf: "
                           "segment %d address overflow\n", index);
                return RT_NULL;
            }
        }
    }

    module_size = vend_addr - vstart_addr;
    LOG_D("module size: %d, vstart_addr: 0x%p", module_size, vstart_addr);
    if (module_size == 0)
    {
        rt_kprintf("Module: size error\n");
        return -RT_ERROR;
    }

    module->vstart_addr = vstart_addr;
    module->nref = 0;

    /* allocate module space */
    module->mem_space = rt_malloc(module_size);
    if (module->mem_space == RT_NULL)
    {
        rt_kprintf("Module: allocate space failed.\n");
        return -RT_ERROR;
    }
    module->mem_size = module_size;

    /* zero all space */
    rt_memset(module->mem_space, 0, module_size);
    for (index = 0; index < elf_module->e_phnum; index++)
    {
        if (phdr[index].p_type == PT_LOAD)
        {
            rt_memcpy(module->mem_space + phdr[index].p_vaddr - vstart_addr,
                      (rt_uint8_t *)elf_module + phdr[index].p_offset,
                      phdr[index].p_filesz);
        }
    }

    /* set module entry */
    module->entry_addr = module->mem_space + elf_module->e_entry - vstart_addr;

    /* handle relocation section */
    for (index = 0; index < elf_module->e_shnum; index ++)
    {
        rt_uint32_t i, nr_reloc;
        Elf32_Sym *symtab;
        Elf32_Rel *rel;
        rt_uint8_t *strtab;
        static rt_bool_t unsolved = RT_FALSE;

        if (!IS_REL(shdr[index]))
            continue;

        /* get relocate item */
        rel = (Elf32_Rel *)((rt_uint8_t *)module_ptr + shdr[index].sh_offset);

        /* locate .rel.plt and .rel.dyn section */
        symtab = (Elf32_Sym *)((rt_uint8_t *)module_ptr +
                               shdr[shdr[index].sh_link].sh_offset);
        strtab = (rt_uint8_t *)module_ptr +
                 shdr[shdr[shdr[index].sh_link].sh_link].sh_offset;
        nr_reloc = (rt_uint32_t)(shdr[index].sh_size / sizeof(Elf32_Rel));

        /* relocate every items */
        for (i = 0; i < nr_reloc; i ++)
        {
            Elf32_Sym *sym = &symtab[ELF32_R_SYM(rel->r_info)];

            LOG_D("relocate symbol %s shndx %d", strtab + sym->st_name, sym->st_shndx);

            if ((sym->st_shndx != SHT_NULL) ||(ELF_ST_BIND(sym->st_info) == STB_LOCAL))
            {
                Elf32_Addr addr;

                addr = (Elf32_Addr)(module->mem_space + sym->st_value - vstart_addr);
                dlmodule_relocate(module, rel, addr);
            }
            else if (!linked)
            {
                Elf32_Addr addr;

                LOG_D("relocate symbol: %s", strtab + sym->st_name);
                /* need to resolve symbol in kernel symbol table */
                addr = dlmodule_symbol_find((const char *)(strtab + sym->st_name));
                if (addr == 0)
                {
                    LOG_E("Module: can't find %s in kernel symbol table", strtab + sym->st_name);
                    unsolved = RT_TRUE;
                }
                else
                {
                    dlmodule_relocate(module, rel, addr);
                }
            }
            rel ++;
        }

        if (unsolved) 
            return -RT_ERROR;
    }

    /* construct module symbol table */
    for (index = 0; index < elf_module->e_shnum; index ++)
    {
        /* find .dynsym section */
        rt_uint8_t *shstrab;
        shstrab = (rt_uint8_t *)module_ptr +
                  shdr[elf_module->e_shstrndx].sh_offset;
        if (rt_strcmp((const char *)(shstrab + shdr[index].sh_name), ELF_DYNSYM) == 0)
            break;
    }

    /* found .dynsym section */
    if (index != elf_module->e_shnum)
    {
        int i, count = 0;
        Elf32_Sym  *symtab = RT_NULL;
        rt_uint8_t *strtab = RT_NULL;

        symtab = (Elf32_Sym *)((rt_uint8_t *)module_ptr + shdr[index].sh_offset);
        strtab = (rt_uint8_t *)module_ptr + shdr[shdr[index].sh_link].sh_offset;

        for (i = 0; i < shdr[index].sh_size / sizeof(Elf32_Sym); i++)
        {
            if ((ELF_ST_BIND(symtab[i].st_info) == STB_GLOBAL) &&
                (ELF_ST_TYPE(symtab[i].st_info) == STT_FUNC))
                count ++;
        }

        module->symtab = (struct rt_module_symtab *)rt_malloc
                         (count * sizeof(struct rt_module_symtab));
        module->nsym = count;
        for (i = 0, count = 0; i < shdr[index].sh_size / sizeof(Elf32_Sym); i++)
        {
            rt_size_t length;

            if ((ELF_ST_BIND(symtab[i].st_info) != STB_GLOBAL) ||
                (ELF_ST_TYPE(symtab[i].st_info) != STT_FUNC))
                continue;

            length = rt_strlen((const char *)(strtab + symtab[i].st_name)) + 1;

            module->symtab[count].addr =
                (void *)(module->mem_space + symtab[i].st_value - module->vstart_addr);
            module->symtab[count].name = rt_malloc(length);
            rt_memset((void *)module->symtab[count].name, 0, length);
            rt_memcpy((void *)module->symtab[count].name,
                      strtab + symtab[i].st_name,
                      length);
            count ++;
        }

        /* get priority & stack size params*/
        rt_uint32_t flag = 0;
        rt_uint16_t priority;
        rt_uint32_t stacksize;
        for (i = 0; i < shdr[index].sh_size / sizeof(Elf32_Sym); i++)
        {
            if (((flag & 0x01) == 0) &&
                (rt_strcmp((const char *)(strtab + symtab[i].st_name), "dlmodule_thread_priority") == 0))
            {
                flag |= 0x01;
                priority = *(rt_uint16_t*)(module->mem_space + symtab[i].st_value - module->vstart_addr);
                if (priority < RT_THREAD_PRIORITY_MAX)
                {
                    module->priority = priority;
                }
            }

            if (((flag & 0x02) == 0) &&
                (rt_strcmp((const char *)(strtab + symtab[i].st_name), "dlmodule_thread_stacksize") == 0))
            {
                flag |= 0x02;
                stacksize = *(rt_uint32_t*)(module->mem_space + symtab[i].st_value - module->vstart_addr);
                if ((stacksize < 2048) || (stacksize > 1024 * 32))
                {
                    module->stack_size = stacksize;
                }
            }

            if ((flag & 0x03) == 0x03)
            {
                break;
            }
        }
    }

    return RT_EOK;
}

rt_err_t dlmodule_load_relocated_object(struct rt_dlmodule* module, void *module_ptr)
{
    rt_uint32_t index, rodata_addr = 0, bss_addr = 0, data_addr = 0;
    rt_uint32_t module_addr = 0, module_size = 0;
    rt_uint8_t *ptr, *strtab, *shstrab;

    /* get the ELF image size */
    for (index = 0; index < elf_module->e_shnum; index ++)
    {
        /* text */
        if (IS_PROG(shdr[index]) && IS_AX(shdr[index]))
        {
            module_size += shdr[index].sh_size;
            module_addr = shdr[index].sh_addr;
        }
        /* rodata */
        if (IS_PROG(shdr[index]) && IS_ALLOC(shdr[index]))
        {
            module_size += shdr[index].sh_size;
        }
        /* data */
        if (IS_PROG(shdr[index]) && IS_AW(shdr[index]))
        {
            module_size += shdr[index].sh_size;
        }
        /* bss */
        if (IS_NOPROG(shdr[index]) && IS_AW(shdr[index]))
        {
            module_size += shdr[index].sh_size;
        }
    }

    /* no text, data and bss on image */
    if (module_size == 0) return RT_NULL;

    module->vstart_addr = 0;

    /* allocate module space */
    module->mem_space = rt_malloc(module_size);
    if (module->mem_space == RT_NULL)
    {
        rt_kprintf("Module: allocate space failed.\n");
        return -RT_ERROR;
    }
    module->mem_size = module_size;

    /* zero all space */
    ptr = module->mem_space;
    rt_memset(ptr, 0, module_size);

    /* load text and data section */
    for (index = 0; index < elf_module->e_shnum; index ++)
    {
        /* load text section */
        if (IS_PROG(shdr[index]) && IS_AX(shdr[index]))
        {
            rt_memcpy(ptr,
                      (rt_uint8_t *)elf_module + shdr[index].sh_offset,
                      shdr[index].sh_size);
            LOG_D("load text 0x%x, size %d", ptr, shdr[index].sh_size);
            ptr += shdr[index].sh_size;
        }

        /* load rodata section */
        if (IS_PROG(shdr[index]) && IS_ALLOC(shdr[index]))
        {
            rt_memcpy(ptr,
                      (rt_uint8_t *)elf_module + shdr[index].sh_offset,
                      shdr[index].sh_size);
            rodata_addr = (rt_uint32_t)ptr;
            LOG_D("load rodata 0x%x, size %d, rodata 0x%x", ptr, 
                shdr[index].sh_size, *(rt_uint32_t *)data_addr);
            ptr += shdr[index].sh_size;
        }

        /* load data section */
        if (IS_PROG(shdr[index]) && IS_AW(shdr[index]))
        {
            rt_memcpy(ptr,
                      (rt_uint8_t *)elf_module + shdr[index].sh_offset,
                      shdr[index].sh_size);
            data_addr = (rt_uint32_t)ptr;
            LOG_D("load data 0x%x, size %d, data 0x%x", ptr, 
                shdr[index].sh_size, *(rt_uint32_t *)data_addr);
            ptr += shdr[index].sh_size;
        }

        /* load bss section */
        if (IS_NOPROG(shdr[index]) && IS_AW(shdr[index]))
        {
            rt_memset(ptr, 0, shdr[index].sh_size);
            bss_addr = (rt_uint32_t)ptr;
            LOG_D("load bss 0x%x, size %d", ptr, shdr[index].sh_size);
        }
    }

    /* set module entry */
    module->entry_addr = (rt_dlmodule_entry_func_t)((rt_uint8_t *)module->mem_space + elf_module->e_entry - module_addr);

    /* handle relocation section */
    for (index = 0; index < elf_module->e_shnum; index ++)
    {
        rt_uint32_t i, nr_reloc;
        Elf32_Sym *symtab;
        Elf32_Rel *rel;

        if (!IS_REL(shdr[index]))
            continue;

        /* get relocate item */
        rel = (Elf32_Rel *)((rt_uint8_t *)module_ptr + shdr[index].sh_offset);

        /* locate .dynsym and .dynstr */
        symtab   = (Elf32_Sym *)((rt_uint8_t *)module_ptr +
                                 shdr[shdr[index].sh_link].sh_offset);
        strtab   = (rt_uint8_t *)module_ptr +
                   shdr[shdr[shdr[index].sh_link].sh_link].sh_offset;
        shstrab  = (rt_uint8_t *)module_ptr +
                   shdr[elf_module->e_shstrndx].sh_offset;
        nr_reloc = (rt_uint32_t)(shdr[index].sh_size / sizeof(Elf32_Rel));

        /* relocate every items */
        for (i = 0; i < nr_reloc; i ++)
        {
            Elf32_Sym *sym = &symtab[ELF32_R_SYM(rel->r_info)];

            LOG_D("relocate symbol: %s", strtab + sym->st_name);

            if (sym->st_shndx != STN_UNDEF)
            {
                Elf32_Addr addr = 0;
                
                if ((ELF_ST_TYPE(sym->st_info) == STT_SECTION) ||
                    (ELF_ST_TYPE(sym->st_info) == STT_OBJECT))
                {
                    if (rt_strncmp((const char *)(shstrab +
                                                  shdr[sym->st_shndx].sh_name), ELF_RODATA, 8) == 0)
                    {
                        /* relocate rodata section */
                        LOG_D("rodata");
                        addr = (Elf32_Addr)(rodata_addr + sym->st_value);
                    }
                    else if (rt_strncmp((const char *)
                                        (shstrab + shdr[sym->st_shndx].sh_name), ELF_BSS, 5) == 0)
                    {
                        /* relocate bss section */
                        LOG_D("bss");
                        addr = (Elf32_Addr)bss_addr + sym->st_value;
                    }
                    else if (rt_strncmp((const char *)(shstrab + shdr[sym->st_shndx].sh_name),
                                        ELF_DATA, 6) == 0)
                    {
                        /* relocate data section */
                        LOG_D("data");
                        addr = (Elf32_Addr)data_addr + sym->st_value;
                    }

                    if (addr != 0) dlmodule_relocate(module, rel, addr);
                }
                else if (ELF_ST_TYPE(sym->st_info) == STT_FUNC)
                {
                    addr = (Elf32_Addr)((rt_uint8_t *) module->mem_space - module_addr + sym->st_value);

                    /* relocate function */
                    dlmodule_relocate(module, rel, addr);
                }
            }
            else if (ELF_ST_TYPE(sym->st_info) == STT_FUNC)
            {
                /* relocate function */
                dlmodule_relocate(module, rel,
                                       (Elf32_Addr)((rt_uint8_t *)
                                                    module->mem_space
                                                    - module_addr
                                                    + sym->st_value));
            }
            else
            {
                Elf32_Addr addr;

                if (ELF32_R_TYPE(rel->r_info) != R_ARM_V4BX)
                {
                    LOG_D("relocate symbol: %s", strtab + sym->st_name);

                    /* need to resolve symbol in kernel symbol table */
                    addr = dlmodule_symbol_find((const char *)(strtab + sym->st_name));
                    if (addr != (Elf32_Addr)RT_NULL)
                    {
                        dlmodule_relocate(module, rel, addr);
                        LOG_D("symbol addr 0x%x", addr);
                    }
                    else
                        LOG_E("Module: can't find %s in kernel symbol table",
                                   strtab + sym->st_name);
                }
                else
                {
                    addr = (Elf32_Addr)((rt_uint8_t *) module->mem_space - module_addr + sym->st_value);
                    dlmodule_relocate(module, rel, addr);
                }
            }

            rel ++;
        }
    }

    return RT_EOK;
}
