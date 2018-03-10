/*
 * File      : module.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
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
 * 2010-01-09     Bernard      first version
 * 2010-04-09     yi.qiu       implement based on first version
 * 2010-10-23     yi.qiu       implement module memory allocator
 * 2011-05-25     yi.qiu       implement module hook function
 * 2011-06-23     yi.qiu       rewrite module memory allocator
 * 2012-11-23     Bernard      using RT_DEBUG_LOG instead of rt_kprintf.
 * 2012-11-28     Bernard      remove rt_current_module and user
 *                             can use rt_module_unload to remove a module.
 * 2017-08-20     parai        support intel 386 machine
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtm.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#ifdef RT_USING_MODULE
#include "module.h"

#define elf_module        ((Elf32_Ehdr *)module_ptr)
#define shdr              ((Elf32_Shdr *)((rt_uint8_t *)module_ptr + elf_module->e_shoff))
#define phdr              ((Elf32_Phdr *)((rt_uint8_t *)module_ptr + elf_module->e_phoff))

#define IS_PROG(s)        (s.sh_type == SHT_PROGBITS)
#define IS_NOPROG(s)      (s.sh_type == SHT_NOBITS)
#define IS_REL(s)         (s.sh_type == SHT_REL)
#define IS_RELA(s)        (s.sh_type == SHT_RELA)
#define IS_ALLOC(s)       (s.sh_flags == SHF_ALLOC)
#define IS_AX(s)          ((s.sh_flags & SHF_ALLOC) && (s.sh_flags & SHF_EXECINSTR))
#define IS_AW(s)          ((s.sh_flags & SHF_ALLOC) && (s.sh_flags & SHF_WRITE))

#ifdef RT_USING_MODULE_STKSZ
#undef RT_USING_MODULE_STKSZ
#endif

#ifndef RT_USING_MODULE_STKSZ
#define RT_USING_MODULE_STKSZ (4096 * 2)
#endif

#ifndef RT_USING_MODULE_PRIO
#define RT_USING_MODULE_PRIO (RT_THREAD_PRIORITY_MAX - 2)
#endif

#ifdef RT_USING_SLAB
#define PAGE_COUNT_MAX    256

/* module memory allocator */
struct rt_mem_head
{
    rt_size_t size;                /* size of memory block */
    struct rt_mem_head *next;      /* next valid memory block */
};

struct rt_page_info
{
    rt_uint32_t *page_ptr;
    rt_uint32_t npage;
};

static void *rt_module_malloc_page(rt_size_t npages);
static void rt_module_free_page(rt_module_t module,
                                void       *page_ptr,
                                rt_size_t   npages);

static struct rt_semaphore mod_sem;
#endif

static struct rt_module_symtab *_rt_module_symtab_begin = RT_NULL;
static struct rt_module_symtab *_rt_module_symtab_end   = RT_NULL;

#if defined(__IAR_SYSTEMS_ICC__) /* for IAR compiler */
    #pragma section="RTMSymTab"
#endif

/**
 * @ingroup SystemInit
 *
 * This function will initialize system module
 */
int rt_system_module_init(void)
{
#if defined(__GNUC__) && !defined(__CC_ARM)
    extern int __rtmsymtab_start;
    extern int __rtmsymtab_end;

    _rt_module_symtab_begin = (struct rt_module_symtab *)&__rtmsymtab_start;
    _rt_module_symtab_end   = (struct rt_module_symtab *)&__rtmsymtab_end;
#elif defined (__CC_ARM)
    extern int RTMSymTab$$Base;
    extern int RTMSymTab$$Limit;

    _rt_module_symtab_begin = (struct rt_module_symtab *)&RTMSymTab$$Base;
    _rt_module_symtab_end   = (struct rt_module_symtab *)&RTMSymTab$$Limit;
#elif defined (__IAR_SYSTEMS_ICC__)
    _rt_module_symtab_begin = __section_begin("RTMSymTab");
    _rt_module_symtab_end   = __section_end("RTMSymTab");
#endif

#ifdef RT_USING_SLAB
    /* initialize heap semaphore */
    rt_sem_init(&mod_sem, "module", 1, RT_IPC_FLAG_FIFO);
#endif
    return 0;
}
INIT_COMPONENT_EXPORT(rt_system_module_init);

#ifdef RT_USING_FINSH
void list_symbol(void)
{
    /* find in kernel symbol table */
    struct rt_module_symtab *index;

    for (index = _rt_module_symtab_begin;
         index != _rt_module_symtab_end;
         index ++)
    {
        rt_kprintf("%s\n", index->name);
    }

    return ;
}
FINSH_FUNCTION_EXPORT(list_symbol, list symbol for module);
MSH_CMD_EXPORT(list_symbol, list symbol for module);
#endif

static rt_uint32_t rt_module_symbol_find(const char *sym_str)
{
    /* find in kernel symbol table */
    struct rt_module_symtab *index;

    for (index = _rt_module_symtab_begin;
         index != _rt_module_symtab_end;
         index ++)
    {
        if (rt_strcmp(index->name, sym_str) == 0)
            return (rt_uint32_t)index->addr;
    }

    return 0;
}

/**
 * This function will return self module object
 *
 * @return the self module object
 */
rt_module_t rt_module_self(void)
{
    rt_thread_t tid;

    tid = rt_thread_self();
    if (tid == RT_NULL)
        return RT_NULL;

    /* return current module */
    return (rt_module_t)tid->module_id;
}
RTM_EXPORT(rt_module_self);

static int rt_module_arm_relocate(struct rt_module *module,
                                  Elf32_Rel        *rel,
                                  Elf32_Addr        sym_val)
{
    Elf32_Addr *where, tmp;
    Elf32_Sword addend, offset;
    rt_uint32_t upper, lower, sign, j1, j2;

    where = (Elf32_Addr *)((rt_uint8_t *)module->module_space
                           + rel->r_offset
                           - module->vstart_addr);
    switch (ELF32_R_TYPE(rel->r_info))
    {
    case R_ARM_NONE:
        break;
    case R_ARM_ABS32:
        *where += (Elf32_Addr)sym_val;
        RT_DEBUG_LOG(RT_DEBUG_MODULE, ("R_ARM_ABS32: %x -> %x\n",
                                       where, *where));
        break;
    case R_ARM_PC24:
    case R_ARM_PLT32:
    case R_ARM_CALL:
    case R_ARM_JUMP24:
        addend = *where & 0x00ffffff;
        if (addend & 0x00800000)
            addend |= 0xff000000;
        tmp = sym_val - (Elf32_Addr)where + (addend << 2);
        tmp >>= 2;
        *where = (*where & 0xff000000) | (tmp & 0x00ffffff);
        RT_DEBUG_LOG(RT_DEBUG_MODULE, ("R_ARM_PC24: %x -> %x\n",
                                       where, *where));
        break;
    case R_ARM_REL32:
        *where += sym_val - (Elf32_Addr)where;
        RT_DEBUG_LOG(RT_DEBUG_MODULE,
                     ("R_ARM_REL32: %x -> %x, sym %x, offset %x\n",
                      where, *where, sym_val, rel->r_offset));
        break;
    case R_ARM_V4BX:
        *where &= 0xf000000f;
        *where |= 0x01a0f000;
        break;
#ifdef MODULE_USING_386
    case R_386_GLOB_DAT:
    case R_386_JUMP_SLOT:
#endif
    case R_ARM_GLOB_DAT:
    case R_ARM_JUMP_SLOT:
        *where = (Elf32_Addr)sym_val;
        RT_DEBUG_LOG(RT_DEBUG_MODULE, ("R_ARM_JUMP_SLOT: 0x%x -> 0x%x 0x%x\n",
                                       where, *where, sym_val));
        break;
#if 0        /* To do */
    case R_ARM_GOT_BREL:
        temp   = (Elf32_Addr)sym_val;
        *where = (Elf32_Addr)&temp;
        RT_DEBUG_LOG(RT_DEBUG_MODULE, ("R_ARM_GOT_BREL: 0x%x -> 0x%x 0x%x\n",
                                       where, *where, sym_val));
        break;
#endif
#ifdef MODULE_USING_386
    case R_386_RELATIVE:
#endif
    case R_ARM_RELATIVE:
        *where = (Elf32_Addr)sym_val + *where;
        RT_DEBUG_LOG(RT_DEBUG_MODULE, ("R_ARM_RELATIVE: 0x%x -> 0x%x 0x%x\n",
                                       where, *where, sym_val));
        break;
    case R_ARM_THM_CALL:
    case R_ARM_THM_JUMP24:
        upper  = *(rt_uint16_t *)where;
        lower  = *(rt_uint16_t *)((Elf32_Addr)where + 2);

        sign   = (upper >> 10) & 1;
        j1     = (lower >> 13) & 1;
        j2     = (lower >> 11) & 1;
        offset = (sign << 24) |
                 ((~(j1 ^ sign) & 1) << 23) |
                 ((~(j2 ^ sign) & 1) << 22) |
                 ((upper & 0x03ff) << 12) |
                 ((lower & 0x07ff) << 1);
        if (offset & 0x01000000)
            offset -= 0x02000000;
        offset += sym_val - (Elf32_Addr)where;

        if (!(offset & 1) ||
            offset <= (rt_int32_t)0xff000000 ||
            offset >= (rt_int32_t)0x01000000)
        {
            rt_kprintf("Module: Only Thumb addresses allowed\n");

            return -1;
        }

        sign = (offset >> 24) & 1;
        j1   = sign ^ (~(offset >> 23) & 1);
        j2   = sign ^ (~(offset >> 22) & 1);
        *(rt_uint16_t *)where = (rt_uint16_t)((upper & 0xf800) |
                                              (sign << 10) |
                                              ((offset >> 12) & 0x03ff));
        *(rt_uint16_t *)(where + 2) = (rt_uint16_t)((lower & 0xd000) |
                                                    (j1 << 13) | (j2 << 11) |
                                                    ((offset >> 1) & 0x07ff));
        upper = *(rt_uint16_t *)where;
        lower = *(rt_uint16_t *)((Elf32_Addr)where + 2);
        break;
    default:
        return -1;
    }

    return 0;
}

void rt_module_init_object_container(struct rt_module *module)
{
    RT_ASSERT(module != RT_NULL);

    /* clear all of object information */
    rt_memset(&module->module_object[0], 0x0, sizeof(module->module_object));

    /* initialize object container - thread */
    rt_list_init(&(module->module_object[RT_Object_Class_Thread].object_list));
    module->module_object[RT_Object_Class_Thread].object_size = sizeof(struct rt_thread);
    module->module_object[RT_Object_Class_Thread].type = RT_Object_Class_Thread;

#ifdef RT_USING_SEMAPHORE
    /* initialize object container - semaphore */
    rt_list_init(&(module->module_object[RT_Object_Class_Semaphore].object_list));
    module->module_object[RT_Object_Class_Semaphore].object_size = sizeof(struct rt_semaphore);
    module->module_object[RT_Object_Class_Semaphore].type = RT_Object_Class_Semaphore;
#endif

#ifdef RT_USING_MUTEX
    /* initialize object container - mutex */
    rt_list_init(&(module->module_object[RT_Object_Class_Mutex].object_list));
    module->module_object[RT_Object_Class_Mutex].object_size = sizeof(struct rt_mutex);
    module->module_object[RT_Object_Class_Mutex].type = RT_Object_Class_Mutex;
#endif

#ifdef RT_USING_EVENT
    /* initialize object container - event */
    rt_list_init(&(module->module_object[RT_Object_Class_Event].object_list));
    module->module_object[RT_Object_Class_Event].object_size = sizeof(struct rt_event);
    module->module_object[RT_Object_Class_Event].type = RT_Object_Class_Event;
#endif

#ifdef RT_USING_MAILBOX
    /* initialize object container - mailbox */
    rt_list_init(&(module->module_object[RT_Object_Class_MailBox].object_list));
    module->module_object[RT_Object_Class_MailBox].object_size = sizeof(struct rt_mailbox);
    module->module_object[RT_Object_Class_MailBox].type = RT_Object_Class_MailBox;
#endif

#ifdef RT_USING_MESSAGEQUEUE
    /* initialize object container - message queue */
    rt_list_init(&(module->module_object[RT_Object_Class_MessageQueue].object_list));
    module->module_object[RT_Object_Class_MessageQueue].object_size = sizeof(struct rt_messagequeue);
    module->module_object[RT_Object_Class_MessageQueue].type = RT_Object_Class_MessageQueue;
#endif

#ifdef RT_USING_MEMHEAP
    /* initialize object container - memory heap */
    rt_list_init(&(module->module_object[RT_Object_Class_MemHeap].object_list));
    module->module_object[RT_Object_Class_MemHeap].object_size = sizeof(struct rt_memheap);
    module->module_object[RT_Object_Class_MemHeap].type = RT_Object_Class_MemHeap;
#endif

#ifdef RT_USING_MEMPOOL
    /* initialize object container - memory pool */
    rt_list_init(&(module->module_object[RT_Object_Class_MemPool].object_list));
    module->module_object[RT_Object_Class_MemPool].object_size = sizeof(struct rt_mempool);
    module->module_object[RT_Object_Class_MemPool].type = RT_Object_Class_MemPool;
#endif

#ifdef RT_USING_DEVICE
    /* initialize object container - device */
    rt_list_init(&(module->module_object[RT_Object_Class_Device].object_list));
    module->module_object[RT_Object_Class_Device].object_size = sizeof(struct rt_device);
    module->module_object[RT_Object_Class_Device].type = RT_Object_Class_Device;
#endif

    /* initialize object container - timer */
    rt_list_init(&(module->module_object[RT_Object_Class_Timer].object_list));
    module->module_object[RT_Object_Class_Timer].object_size = sizeof(struct rt_timer);
    module->module_object[RT_Object_Class_Timer].type = RT_Object_Class_Timer;
}

#ifdef RT_USING_HOOK
static void (*rt_module_load_hook)(rt_module_t module);
static void (*rt_module_unload_hook)(rt_module_t module);

/**
 * @addtogroup Hook
 */

/**@{*/

/**
 * This function will set a hook function, which will be invoked when module
 * be loaded to system.
 *
 * @param hook the hook function
 */
void rt_module_load_sethook(void (*hook)(rt_module_t module))
{
    rt_module_load_hook = hook;
}

/**
 * This function will set a hook function, which will be invoked when module
 * be unloaded from system.
 *
 * @param hook the hook function
 */
void rt_module_unload_sethook(void (*hook)(rt_module_t module))
{
    rt_module_unload_hook = hook;
}

/**@}*/
#endif

static struct rt_module *_load_shared_object(const char *name,
                                             void       *module_ptr)
{
    rt_module_t module = RT_NULL;
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

        RT_DEBUG_LOG(RT_DEBUG_MODULE, ("LOAD segment: %d, 0x%p, 0x%08x\n",
                                       index, phdr[index].p_vaddr, phdr[index].p_memsz));

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
                rt_kprintf("warning: too much padding before segment %d\n", index);
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

    RT_DEBUG_LOG(RT_DEBUG_MODULE, ("module size: %d, vstart_addr: 0x%p\n",
                                   module_size, vstart_addr));

    if (module_size == 0)
    {
        rt_kprintf("Module: size error\n");

        return RT_NULL;
    }

    /* allocate module */
    module = (struct rt_module *)rt_object_allocate(RT_Object_Class_Module,
                                                    name);
    if (!module)
        return RT_NULL;

    module->vstart_addr = vstart_addr;

    module->nref = 0;

    /* allocate module space */
    module->module_space = rt_malloc(module_size);
    if (module->module_space == RT_NULL)
    {
        rt_kprintf("Module: allocate space failed.\n");
        rt_object_delete(&(module->parent));

        return RT_NULL;
    }

    /* zero all space */
    rt_memset(module->module_space, 0, module_size);

    for (index = 0; index < elf_module->e_phnum; index++)
    {
        if (phdr[index].p_type == PT_LOAD)
        {
            rt_memcpy(module->module_space + phdr[index].p_vaddr - vstart_addr,
                      (rt_uint8_t *)elf_module + phdr[index].p_offset,
                      phdr[index].p_filesz);
        }
    }

    /* set module entry */
    module->module_entry = module->module_space
                           + elf_module->e_entry - vstart_addr;

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

            RT_DEBUG_LOG(RT_DEBUG_MODULE, ("relocate symbol %s shndx %d\n",
                                           strtab + sym->st_name,
                                           sym->st_shndx));

            if ((sym->st_shndx != SHT_NULL) ||
                (ELF_ST_BIND(sym->st_info) == STB_LOCAL)
#ifdef MODULE_USING_386
                || ( (ELF_ST_BIND(sym->st_info) == STB_GLOBAL) && (ELF_ST_TYPE(sym->st_info) == STT_OBJECT) )
#endif
               )
            {
                rt_module_arm_relocate(module, rel,
                                       (Elf32_Addr)(module->module_space
                                                    + sym->st_value
                                                    - vstart_addr));
            }
            else if (!linked)
            {
                Elf32_Addr addr;

                RT_DEBUG_LOG(RT_DEBUG_MODULE, ("relocate symbol: %s\n",
                                               strtab + sym->st_name));

                /* need to resolve symbol in kernel symbol table */
                addr = rt_module_symbol_find((const char *)(strtab + sym->st_name));
                if (addr == 0)
                {
                    rt_kprintf("Module: can't find %s in kernel symbol table\n",
                               strtab + sym->st_name);
                    unsolved = RT_TRUE;
                }
                else
                    rt_module_arm_relocate(module, rel, addr);
            }
            rel ++;
        }

        if (unsolved)
        {
            rt_object_delete(&(module->parent));

            return RT_NULL;
        }
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
                (void *)(module->module_space + symtab[i].st_value);
            module->symtab[count].name = rt_malloc(length);
            rt_memset((void *)module->symtab[count].name, 0, length);
            rt_memcpy((void *)module->symtab[count].name,
                      strtab + symtab[i].st_name,
                      length);
            count ++;
        }
    }

    return module;
}

static struct rt_module* _load_relocated_object(const char *name,
                                                void       *module_ptr)
{
    rt_uint32_t index, rodata_addr = 0, bss_addr = 0, data_addr = 0;
    rt_uint32_t module_addr = 0, module_size = 0;
    struct rt_module *module = RT_NULL;
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
    if (module_size == 0)
        return RT_NULL;

    /* allocate module */
    module = (struct rt_module *)
             rt_object_allocate(RT_Object_Class_Module, (const char *)name);
    if (module == RT_NULL)
        return RT_NULL;

    module->vstart_addr = 0;

    /* allocate module space */
    module->module_space = rt_malloc(module_size);
    if (module->module_space == RT_NULL)
    {
        rt_kprintf("Module: allocate space failed.\n");
        rt_object_delete(&(module->parent));

        return RT_NULL;
    }

    /* zero all space */
    ptr = module->module_space;
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
            RT_DEBUG_LOG(RT_DEBUG_MODULE, ("load text 0x%x, size %d\n",
                                           ptr, shdr[index].sh_size));
            ptr += shdr[index].sh_size;
        }

        /* load rodata section */
        if (IS_PROG(shdr[index]) && IS_ALLOC(shdr[index]))
        {
            rt_memcpy(ptr,
                      (rt_uint8_t *)elf_module + shdr[index].sh_offset,
                      shdr[index].sh_size);
            rodata_addr = (rt_uint32_t)ptr;
            RT_DEBUG_LOG(RT_DEBUG_MODULE,
                         ("load rodata 0x%x, size %d, rodata 0x%x\n",
                          ptr, shdr[index].sh_size, *(rt_uint32_t *)data_addr));
            ptr += shdr[index].sh_size;
        }

        /* load data section */
        if (IS_PROG(shdr[index]) && IS_AW(shdr[index]))
        {
            rt_memcpy(ptr,
                      (rt_uint8_t *)elf_module + shdr[index].sh_offset,
                      shdr[index].sh_size);
            data_addr = (rt_uint32_t)ptr;
            RT_DEBUG_LOG(RT_DEBUG_MODULE,
                         ("load data 0x%x, size %d, data 0x%x\n",
                          ptr, shdr[index].sh_size, *(rt_uint32_t *)data_addr));
            ptr += shdr[index].sh_size;
        }

        /* load bss section */
        if (IS_NOPROG(shdr[index]) && IS_AW(shdr[index]))
        {
            rt_memset(ptr, 0, shdr[index].sh_size);
            bss_addr = (rt_uint32_t)ptr;
            RT_DEBUG_LOG(RT_DEBUG_MODULE, ("load bss 0x%x, size %d,\n",
                                           ptr, shdr[index].sh_size));
        }
    }

    /* set module entry */
    module->module_entry =
        (rt_uint8_t *)module->module_space + elf_module->e_entry - module_addr;

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

            RT_DEBUG_LOG(RT_DEBUG_MODULE, ("relocate symbol: %s\n",
                                           strtab + sym->st_name));

            if (sym->st_shndx != STN_UNDEF)
            {
                if ((ELF_ST_TYPE(sym->st_info) == STT_SECTION) ||
                    (ELF_ST_TYPE(sym->st_info) == STT_OBJECT))
                {
                    if (rt_strncmp((const char *)(shstrab +
                                                  shdr[sym->st_shndx].sh_name), ELF_RODATA, 8) == 0)
                    {
                        /* relocate rodata section */
                        RT_DEBUG_LOG(RT_DEBUG_MODULE, ("rodata\n"));
                        rt_module_arm_relocate(module, rel,
                                               (Elf32_Addr)(rodata_addr + sym->st_value));
                    }
                    else if (rt_strncmp((const char *)
                                        (shstrab + shdr[sym->st_shndx].sh_name), ELF_BSS, 5) == 0)
                    {
                        /* relocate bss section */
                        RT_DEBUG_LOG(RT_DEBUG_MODULE, ("bss\n"));
                        rt_module_arm_relocate(module, rel,
                                               (Elf32_Addr)bss_addr + sym->st_value);
                    }
                    else if (rt_strncmp((const char *)(shstrab + shdr[sym->st_shndx].sh_name),
                                        ELF_DATA, 6) == 0)
                    {
                        /* relocate data section */
                        RT_DEBUG_LOG(RT_DEBUG_MODULE, ("data\n"));
                        rt_module_arm_relocate(module, rel,
                                               (Elf32_Addr)data_addr + sym->st_value);
                    }
                }
                else if (ELF_ST_TYPE(sym->st_info) == STT_FUNC)
                {
                    /* relocate function */
                    rt_module_arm_relocate(module, rel,
                                           (Elf32_Addr)((rt_uint8_t *)
                                                        module->module_space
                                                        - module_addr
                                                        + sym->st_value));
                }
            }
            else if (ELF_ST_TYPE(sym->st_info) == STT_FUNC)
            {
                /* relocate function */
                rt_module_arm_relocate(module, rel,
                                       (Elf32_Addr)((rt_uint8_t *)
                                                    module->module_space
                                                    - module_addr
                                                    + sym->st_value));
            }
            else
            {
                Elf32_Addr addr;

                if (ELF32_R_TYPE(rel->r_info) != R_ARM_V4BX)
                {
                    RT_DEBUG_LOG(RT_DEBUG_MODULE, ("relocate symbol: %s\n",
                                                   strtab + sym->st_name));

                    /* need to resolve symbol in kernel symbol table */
                    addr = rt_module_symbol_find((const char *)(strtab + sym->st_name));
                    if (addr != (Elf32_Addr)RT_NULL)
                    {
                        rt_module_arm_relocate(module, rel, addr);
                        RT_DEBUG_LOG(RT_DEBUG_MODULE, ("symbol addr 0x%x\n",
                                                       addr));
                    }
                    else
                        rt_kprintf("Module: can't find %s in kernel symbol table\n",
                                   strtab + sym->st_name);
                }
                else
                {
                    rt_module_arm_relocate(module, rel,
                                           (Elf32_Addr)((rt_uint8_t *)
                                                        module->module_space
                                                        - module_addr
                                                        + sym->st_value));
                }
            }
            rel ++;
        }
    }

    return module;
}

#define RT_MODULE_ARG_MAX    8
static int _rt_module_split_arg(char *cmd, rt_size_t length, char *argv[])
{
    int argc = 0;
    char *ptr = cmd;

    while ((ptr - cmd) < length)
    {
        /* strip bank and tab */
        while ((*ptr == ' ' || *ptr == '\t') && (ptr - cmd) < length)
            *ptr++ = '\0';
        /* check whether it's the end of line */
        if ((ptr - cmd) >= length) break;

        /* handle string with quote */
        if (*ptr == '"')
        {
            argv[argc++] = ++ptr;

            /* skip this string */
            while (*ptr != '"' && (ptr - cmd) < length)
                if (*ptr ++ == '\\')  ptr ++;
            if ((ptr - cmd) >= length) break;

            /* skip '"' */
            *ptr ++ = '\0';
        }
        else
        {
            argv[argc++] = ptr;
            while ((*ptr != ' ' && *ptr != '\t') && (ptr - cmd) < length)
                ptr ++;
        }

        if (argc >= RT_MODULE_ARG_MAX) break;
    }

    return argc;
}

/* module main thread entry */
static void module_main_entry(void *parameter)
{
    int argc;
    char *argv[RT_MODULE_ARG_MAX];
    typedef int (*main_func_t)(int argc, char **argv);

    rt_module_t module = (rt_module_t) parameter;
    if (module == RT_NULL)
        return;

    if (module->module_cmd_line == RT_NULL && module->module_cmd_size != 0)
        /* malloc for module_cmd_line failed. */
        return;

    /* FIXME: we should run some C++ initialize code before jump into the
     * entry. */

    if (module->module_cmd_line == RT_NULL)
    {
        RT_DEBUG_LOG(RT_DEBUG_MODULE, ("run bare entry: 0x%p\n",
                                       module->module_entry));
        ((main_func_t)module->module_entry)(0, RT_NULL);
        return;
    }

    rt_memset(argv, 0x00, sizeof(argv));
    argc = _rt_module_split_arg((char *)module->module_cmd_line,
                                module->module_cmd_size, argv);
    if (argc == 0)
        return;

    RT_DEBUG_LOG(RT_DEBUG_MODULE, ("run main entry: 0x%p with %s\n",
                                   module->module_entry,
                                   module->module_cmd_line));
    /* do the main function */
    ((main_func_t)module->module_entry)(argc, argv);
    return;
}

/**
 * This function will load a module with a main function from memory and create a
 * main thread for it
 *
 * @param name the name of module, which shall be unique
 * @param module_ptr the memory address of module image
 * @argc the count of argument
 * @argd the argument data, which should be a
 *
 * @return the module object
 */
rt_module_t rt_module_do_main(const char *name,
                              void *module_ptr,
                              const char *cmd_line,
                              int line_size)
{
    rt_module_t module;

    RT_DEBUG_NOT_IN_INTERRUPT;

    RT_DEBUG_LOG(RT_DEBUG_MODULE, ("rt_module_load: %s\n", name));

    /* check ELF header */
    if (rt_memcmp(elf_module->e_ident, RTMMAG, SELFMAG) != 0 &&
        rt_memcmp(elf_module->e_ident, ELFMAG, SELFMAG) != 0)
    {
        rt_kprintf("Module: magic error\n");

        return RT_NULL;
    }

    /* check ELF class */
    if (elf_module->e_ident[EI_CLASS] != ELFCLASS32)
    {
        rt_kprintf("Module: ELF class error\n");

        return RT_NULL;
    }

    if (elf_module->e_type == ET_REL)
    {
        module = _load_relocated_object(name, module_ptr);
    }
    else if (elf_module->e_type == ET_DYN)
    {
        module = _load_shared_object(name, module_ptr);
    }
    else
    {
        rt_kprintf("Module: unsupported elf type\n");

        return RT_NULL;
    }

    if (module == RT_NULL)
        return RT_NULL;

    /* init module object container */
    rt_module_init_object_container(module);

    if (line_size && cmd_line)
    {
        /* set module argument */
        module->module_cmd_line = (rt_uint8_t *)rt_malloc(line_size + 1);
        if (module->module_cmd_line)
        {
            rt_memcpy(module->module_cmd_line, cmd_line, line_size);
            module->module_cmd_line[line_size] = '\0';
        }
        module->module_cmd_size = line_size;
    }
    else
    {
        /* initialize an empty command */
        module->module_cmd_line = RT_NULL;
        module->module_cmd_size = 0;
    }

    /* increase module reference count */
    module->nref ++;

    if (elf_module->e_entry != 0)
    {
#ifdef RT_USING_SLAB
        /* init module memory allocator */
        module->mem_list = RT_NULL;

        /* create page array */
        module->page_array =
            (void *)rt_malloc(PAGE_COUNT_MAX * sizeof(struct rt_page_info));
        module->page_cnt = 0;
#endif

        /* create module thread */
        module->module_thread = rt_thread_create(name,
                                                 module_main_entry, module,
                                                 RT_USING_MODULE_STKSZ,
                                                 RT_USING_MODULE_PRIO, 10);

        RT_DEBUG_LOG(RT_DEBUG_MODULE, ("thread entry 0x%x\n",
                                       module->module_entry));

        /* set module id */
        module->module_thread->module_id = (void *)module;
        module->parent.flag = RT_MODULE_FLAG_WITHENTRY;

        /* startup module thread */
        rt_thread_startup(module->module_thread);
    }
    else
    {
        /* without entry point */
        module->parent.flag |= RT_MODULE_FLAG_WITHOUTENTRY;
    }

#ifdef RT_USING_HOOK
    if (rt_module_load_hook != RT_NULL)
    {
        rt_module_load_hook(module);
    }
#endif

    return module;
}

/**
 * This function will load a module from memory and create a thread for it
 *
 * @param name the name of module, which shall be unique
 * @param module_ptr the memory address of module image
 *
 * @return the module object
 */
rt_module_t rt_module_load(const char *name, void *module_ptr)
{
    return rt_module_do_main(name, module_ptr, RT_NULL, 0);
}

#ifdef RT_USING_DFS
#include <dfs_posix.h>

static char *_module_name(const char *path)
{
    const char *first, *end, *ptr;
    char *name;
    int size;

    ptr   = (char *)path;
    first = ptr;
    end   = path + rt_strlen(path);

    while (*ptr != '\0')
    {
        if (*ptr == '/')
            first = ptr + 1;
        if (*ptr == '.')
            end = ptr - 1;

        ptr ++;
    }

    size = end - first + 1;
    name = rt_malloc(size);
    rt_strncpy(name, first, size);
    name[size] = '\0';

    return name;
}

/**
 * This function will load a module from a file
 *
 * @param path the full path of application module
 *
 * @return the module object
 */
rt_module_t rt_module_open(const char *path)
{
    int fd, length;
    struct rt_module *module;
    struct stat s;
    char *buffer, *offset_ptr;
    char *name;

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* check parameters */
    RT_ASSERT(path != RT_NULL);

    if (stat(path, &s) != 0)
    {
        rt_kprintf("Module: access %s failed\n", path);

        return RT_NULL;
    }
    buffer = (char *)rt_malloc(s.st_size);
    if (buffer == RT_NULL)
    {
        rt_kprintf("Module: out of memory\n");

        return RT_NULL;
    }

    offset_ptr = buffer;
    fd = open(path, O_RDONLY, 0);
    if (fd < 0)
    {
        rt_kprintf("Module: open %s failed\n", path);
        rt_free(buffer);

        return RT_NULL;
    }

    do
    {
        length = read(fd, offset_ptr, 4096);
        if (length > 0)
        {
            offset_ptr += length;
        }
    }while (length > 0);

    /* close fd */
    close(fd);

    if ((rt_uint32_t)offset_ptr - (rt_uint32_t)buffer != s.st_size)
    {
        rt_kprintf("Module: read file failed\n");
        rt_free(buffer);

        return RT_NULL;
    }

    name   = _module_name(path);
    module = rt_module_load(name, (void *)buffer);
    rt_free(buffer);
    rt_free(name);

    return module;
}

/**
 * This function will do a excutable program with main function and parameters.
 *
 * @param path the full path of application module
 * @param cmd_line the command line of program
 * @param size the size of command line of program
 *
 * @return the module object
 */
rt_module_t rt_module_exec_cmd(const char *path, const char *cmd_line, int size)
{
    struct stat s;
    int fd, length;
    char *name, *buffer, *offset_ptr;
    struct rt_module *module = RT_NULL;

    name = buffer = RT_NULL;

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* check parameters */
    RT_ASSERT(path != RT_NULL);

    /* get file size */
    if (stat(path, &s) != 0)
    {
        rt_kprintf("Module: access %s failed\n", path);
        goto __exit;
    }

    /* allocate buffer to save program */
    offset_ptr = buffer = (char *)rt_malloc(s.st_size);
    if (buffer == RT_NULL)
    {
        rt_kprintf("Module: out of memory\n");
        goto __exit;
    }

    fd = open(path, O_RDONLY, 0);
    if (fd < 0)
    {
        rt_kprintf("Module: open %s failed\n", path);
        goto __exit;
    }

    do
    {
        length = read(fd, offset_ptr, 4096);
        if (length > 0)
        {
            offset_ptr += length;
        }
    }while (length > 0);
    /* close fd */
    close(fd);

    if ((rt_uint32_t)offset_ptr - (rt_uint32_t)buffer != s.st_size)
    {
        rt_kprintf("Module: read file failed\n");
        goto __exit;
    }

    /* get module */
    name   = _module_name(path);
    /* execute module */
    module = rt_module_do_main(name, (void *)buffer, cmd_line, size);

__exit:
    rt_free(buffer);
    rt_free(name);

    return module;
}

#if defined(RT_USING_FINSH)
#include <finsh.h>
FINSH_FUNCTION_EXPORT_ALIAS(rt_module_open, exec, exec module from a file);
#endif

#endif

/**
 * This function will destroy a module and release its resource.
 *
 * @param module the module to be destroyed.
 *
 * @return the operation status, RT_EOK on OK; -RT_ERROR on error
 */
rt_err_t rt_module_destroy(rt_module_t module)
{
    int i;
    struct rt_object *object;
    struct rt_list_node *list;

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* check parameter */
    RT_ASSERT(module != RT_NULL);
    RT_ASSERT(module->nref == 0);

    RT_DEBUG_LOG(RT_DEBUG_MODULE, ("rt_module_destroy: %8.*s\n",
                                   RT_NAME_MAX, module->parent.name));

    /* module has entry point */
    if (!(module->parent.flag & RT_MODULE_FLAG_WITHOUTENTRY))
    {
#ifdef RT_USING_SEMAPHORE
        /* delete semaphores */
        list = &module->module_object[RT_Object_Class_Semaphore].object_list;
        while (list->next != list)
        {
            object = rt_list_entry(list->next, struct rt_object, list);
            if (rt_object_is_systemobject(object) == RT_TRUE)
            {
                /* detach static object */
                rt_sem_detach((rt_sem_t)object);
            }
            else
            {
                /* delete dynamic object */
                rt_sem_delete((rt_sem_t)object);
            }
        }
#endif

#ifdef RT_USING_MUTEX
        /* delete mutexs*/
        list = &module->module_object[RT_Object_Class_Mutex].object_list;
        while (list->next != list)
        {
            object = rt_list_entry(list->next, struct rt_object, list);
            if (rt_object_is_systemobject(object) == RT_TRUE)
            {
                /* detach static object */
                rt_mutex_detach((rt_mutex_t)object);
            }
            else
            {
                /* delete dynamic object */
                rt_mutex_delete((rt_mutex_t)object);
            }
        }
#endif

#ifdef RT_USING_EVENT
        /* delete mailboxs */
        list = &module->module_object[RT_Object_Class_Event].object_list;
        while (list->next != list)
        {
            object = rt_list_entry(list->next, struct rt_object, list);
            if (rt_object_is_systemobject(object) == RT_TRUE)
            {
                /* detach static object */
                rt_event_detach((rt_event_t)object);
            }
            else
            {
                /* delete dynamic object */
                rt_event_delete((rt_event_t)object);
            }
        }
#endif

#ifdef RT_USING_MAILBOX
        /* delete mailboxs */
        list = &module->module_object[RT_Object_Class_MailBox].object_list;
        while (list->next != list)
        {
            object = rt_list_entry(list->next, struct rt_object, list);
            if (rt_object_is_systemobject(object) == RT_TRUE)
            {
                /* detach static object */
                rt_mb_detach((rt_mailbox_t)object);
            }
            else
            {
                /* delete dynamic object */
                rt_mb_delete((rt_mailbox_t)object);
            }
        }
#endif

#ifdef RT_USING_MESSAGEQUEUE
        /* delete msgqueues */
        list = &module->module_object[RT_Object_Class_MessageQueue].object_list;
        while (list->next != list)
        {
            object = rt_list_entry(list->next, struct rt_object, list);
            if (rt_object_is_systemobject(object) == RT_TRUE)
            {
                /* detach static object */
                rt_mq_detach((rt_mq_t)object);
            }
            else
            {
                /* delete dynamic object */
                rt_mq_delete((rt_mq_t)object);
            }
        }
#endif

#ifdef RT_USING_MEMPOOL
        /* delete mempools */
        list = &module->module_object[RT_Object_Class_MemPool].object_list;
        while (list->next != list)
        {
            object = rt_list_entry(list->next, struct rt_object, list);
            if (rt_object_is_systemobject(object) == RT_TRUE)
            {
                /* detach static object */
                rt_mp_detach((rt_mp_t)object);
            }
            else
            {
                /* delete dynamic object */
                rt_mp_delete((rt_mp_t)object);
            }
        }
#endif

#ifdef RT_USING_DEVICE
        /* delete devices */
        list = &module->module_object[RT_Object_Class_Device].object_list;
        while (list->next != list)
        {
            object = rt_list_entry(list->next, struct rt_object, list);
            rt_device_unregister((rt_device_t)object);
        }
#endif

        /* delete timers */
        list = &module->module_object[RT_Object_Class_Timer].object_list;
        while (list->next != list)
        {
            object = rt_list_entry(list->next, struct rt_object, list);
            if (rt_object_is_systemobject(object) == RT_TRUE)
            {
                /* detach static object */
                rt_timer_detach((rt_timer_t)object);
            }
            else
            {
                /* delete dynamic object */
                rt_timer_delete((rt_timer_t)object);
            }
        }

        /* delete command line */
        if (module->module_cmd_line != RT_NULL)
        {
            rt_free(module->module_cmd_line);
        }
    }

#ifdef RT_USING_SLAB
    if (module->page_cnt > 0)
    {
        struct rt_page_info *page = (struct rt_page_info *)module->page_array;

        rt_kprintf("Module: warning - memory still hasn't been free finished\n");

        while (module->page_cnt != 0)
        {
            rt_module_free_page(module, page[0].page_ptr, page[0].npage);
        }
    }
#endif

    /* release module space memory */
    rt_free(module->module_space);

    /* release module symbol table */
    for (i = 0; i < module->nsym; i ++)
    {
        rt_free((void *)module->symtab[i].name);
    }
    if (module->symtab != RT_NULL)
        rt_free(module->symtab);

#ifdef RT_USING_SLAB
    if (module->page_array != RT_NULL)
        rt_free(module->page_array);
#endif

    /* delete module object */
    rt_object_delete((rt_object_t)module);

    return RT_EOK;
}

/**
 * This function will unload a module from memory and release resources
 *
 * @param module the module to be unloaded
 *
 * @return the operation status, RT_EOK on OK; -RT_ERROR on error
 */
rt_err_t rt_module_unload(rt_module_t module)
{
    struct rt_object *object;
    struct rt_list_node *list;

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* check parameter */
    if (module == RT_NULL)
        return -RT_ERROR;

    rt_enter_critical();
    if (!(module->parent.flag & RT_MODULE_FLAG_WITHOUTENTRY))
    {
        /* delete all sub-threads */
        list = &module->module_object[RT_Object_Class_Thread].object_list;
        while (list->next != list)
        {
            object = rt_list_entry(list->next, struct rt_object, list);
            if (rt_object_is_systemobject(object) == RT_TRUE)
            {
                /* detach static object */
                rt_thread_detach((rt_thread_t)object);
            }
            else
            {
                /* delete dynamic object */
                rt_thread_delete((rt_thread_t)object);
            }
        }

        /* delete the main thread of module */
        if (module->module_thread != RT_NULL)
        {
            rt_thread_delete(module->module_thread);
        }
    }
    rt_exit_critical();

#ifdef RT_USING_HOOK
    if (rt_module_unload_hook != RT_NULL)
    {
        rt_module_unload_hook(module);
    }
#endif

    return RT_EOK;
}

/**
 * This function will find the specified module.
 *
 * @param name the name of module finding
 *
 * @return the module
 */
rt_module_t rt_module_find(const char *name)
{
    struct rt_object_information *information;
    struct rt_object *object;
    struct rt_list_node *node;

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* enter critical */
    rt_enter_critical();

    /* try to find device object */
    information = rt_object_get_information(RT_Object_Class_Module);
    RT_ASSERT(information != RT_NULL);
    for (node = information->object_list.next;
         node != &(information->object_list);
         node = node->next)
    {
        object = rt_list_entry(node, struct rt_object, list);
        if (rt_strncmp(object->name, name, RT_NAME_MAX) == 0)
        {
            /* leave critical */
            rt_exit_critical();

            return (rt_module_t)object;
        }
    }

    /* leave critical */
    rt_exit_critical();

    /* not found */
    return RT_NULL;
}
RTM_EXPORT(rt_module_find);

#ifdef RT_USING_SLAB
/*
 * This function will allocate the numbers page with specified size
 * in page memory.
 *
 * @param size the size of memory to be allocated.
 * @note this function is used for RT-Thread Application Module
 */
static void *rt_module_malloc_page(rt_size_t npages)
{
    void *chunk;
    struct rt_page_info *page;
    rt_module_t self_module;

    self_module = rt_module_self();
    RT_ASSERT(self_module != RT_NULL);

    chunk = rt_page_alloc(npages);
    if (chunk == RT_NULL)
        return RT_NULL;

    page = (struct rt_page_info *)self_module->page_array;
    page[self_module->page_cnt].page_ptr = chunk;
    page[self_module->page_cnt].npage    = npages;
    self_module->page_cnt ++;

    RT_ASSERT(self_module->page_cnt <= PAGE_COUNT_MAX);
    RT_DEBUG_LOG(RT_DEBUG_MODULE, ("rt_module_malloc_page 0x%x %d\n",
                                   chunk, npages));

    return chunk;
}

/*
 * This function will release the previously allocated memory page
 * by rt_malloc_page.
 *
 * @param page_ptr the page address to be released.
 * @param npages the number of page shall be released.
 *
 * @note this function is used for RT-Thread Application Module
 */
static void rt_module_free_page(rt_module_t module,
                                void       *page_ptr,
                                rt_size_t   npages)
{
    int i, index;
    struct rt_page_info *page;
    rt_module_t self_module;

    self_module = rt_module_self();
    RT_ASSERT(self_module != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_MODULE, ("rt_module_free_page 0x%x %d\n",
                                   page_ptr, npages));
    rt_page_free(page_ptr, npages);

    page = (struct rt_page_info *)module->page_array;

    for (i = 0; i < module->page_cnt; i ++)
    {
        if (page[i].page_ptr == page_ptr)
        {
            if (page[i].npage == npages + 1)
            {
                page[i].page_ptr +=
                    npages * RT_MM_PAGE_SIZE / sizeof(rt_uint32_t);
                page[i].npage    -= npages;
            }
            else if (page[i].npage == npages)
            {
                for (index = i; index < module->page_cnt - 1; index ++)
                {
                    page[index].page_ptr = page[index + 1].page_ptr;
                    page[index].npage    = page[index + 1].npage;
                }
                page[module->page_cnt - 1].page_ptr = RT_NULL;
                page[module->page_cnt - 1].npage    = 0;

                module->page_cnt --;
            }
            else
                RT_ASSERT(RT_FALSE);
            self_module->page_cnt --;

            return;
        }
    }

    /* should not get here */
    RT_ASSERT(RT_FALSE);
}

/**
 * rt_module_malloc - allocate memory block in free list
 */
void *rt_module_malloc(rt_size_t size)
{
    struct rt_mem_head *b, *n, *up;
    struct rt_mem_head **prev;
    rt_uint32_t npage;
    rt_size_t nunits;
    rt_module_t self_module;

    self_module = rt_module_self();
    RT_ASSERT(self_module != RT_NULL);

    RT_DEBUG_NOT_IN_INTERRUPT;

    nunits = (size + sizeof(struct rt_mem_head) - 1) /
             sizeof(struct rt_mem_head)
             + 1;

    RT_ASSERT(size != 0);
    RT_ASSERT(nunits != 0);

    rt_sem_take(&mod_sem, RT_WAITING_FOREVER);

    for (prev = (struct rt_mem_head **)&self_module->mem_list;
         (b = *prev) != RT_NULL;
         prev = &(b->next))
    {
        if (b->size > nunits)
        {
            /* split memory */
            n       = b + nunits;
            n->next = b->next;
            n->size = b->size - nunits;
            b->size = nunits;
            *prev   = n;

            RT_DEBUG_LOG(RT_DEBUG_MODULE, ("rt_module_malloc 0x%x, %d\n",
                                           b + 1, size));
            rt_sem_release(&mod_sem);

            return (void *)(b + 1);
        }

        if (b->size == nunits)
        {
            /* this node fit, remove this node */
            *prev = b->next;

            RT_DEBUG_LOG(RT_DEBUG_MODULE, ("rt_module_malloc 0x%x, %d\n",
                                           b + 1, size));

            rt_sem_release(&mod_sem);

            return (void *)(b + 1);
        }
    }

    /* allocate pages from system heap */
    npage = (size + sizeof(struct rt_mem_head) + RT_MM_PAGE_SIZE - 1) /
            RT_MM_PAGE_SIZE;
    if ((up = (struct rt_mem_head *)rt_module_malloc_page(npage)) == RT_NULL)
        return RT_NULL;

    up->size = npage * RT_MM_PAGE_SIZE / sizeof(struct rt_mem_head);

    for (prev = (struct rt_mem_head **)&self_module->mem_list;
         (b = *prev) != RT_NULL;
         prev = &(b->next))
    {
        if (b > up + up->size)
            break;
    }

    up->next = b;
    *prev    = up;

    rt_sem_release(&mod_sem);

    return rt_module_malloc(size);
}

/**
 * rt_module_free - free memory block in free list
 */
void rt_module_free(rt_module_t module, void *addr)
{
    struct rt_mem_head *b, *n, *r;
    struct rt_mem_head **prev;

    RT_DEBUG_NOT_IN_INTERRUPT;

    RT_ASSERT(addr);
    RT_ASSERT((((rt_uint32_t)addr) & (sizeof(struct rt_mem_head) - 1)) == 0);

    RT_DEBUG_LOG(RT_DEBUG_MODULE, ("rt_module_free 0x%x\n", addr));

    rt_sem_take(&mod_sem, RT_WAITING_FOREVER);

    n = (struct rt_mem_head *)addr - 1;
    prev = (struct rt_mem_head **)&module->mem_list;

    while ((b = *prev) != RT_NULL)
    {
        RT_ASSERT(b->size > 0);
        RT_ASSERT(b > n || b + b->size <= n);

        if (b + b->size == n && ((rt_uint32_t)n % RT_MM_PAGE_SIZE != 0))
        {
            if (b + (b->size + n->size) == b->next)
            {
                b->size += b->next->size + n->size;
                b->next = b->next->next;
            }
            else
                b->size += n->size;

            if ((rt_uint32_t)b % RT_MM_PAGE_SIZE == 0)
            {
                int npage =
                    b->size * sizeof(struct rt_page_info) / RT_MM_PAGE_SIZE;
                if (npage > 0)
                {
                    if ((b->size * sizeof(struct rt_page_info) % RT_MM_PAGE_SIZE) != 0)
                    {
                        rt_size_t nunits = npage *
                                           RT_MM_PAGE_SIZE /
                                           sizeof(struct rt_mem_head);
                        /* split memory */
                        r       = b + nunits;
                        r->next = b->next;
                        r->size = b->size - nunits;
                        *prev   = r;
                    }
                    else
                    {
                        *prev = b->next;
                    }

                    rt_module_free_page(module, b, npage);
                }
            }

            /* unlock */
            rt_sem_release(&mod_sem);

            return;
        }

        if (b == n + n->size)
        {
            n->size = b->size + n->size;
            n->next = b->next;

            if ((rt_uint32_t)n % RT_MM_PAGE_SIZE == 0)
            {
                int npage =
                    n->size * sizeof(struct rt_page_info) / RT_MM_PAGE_SIZE;
                if (npage > 0)
                {
                    if ((n->size * sizeof(struct rt_page_info) % RT_MM_PAGE_SIZE) != 0)
                    {
                        rt_size_t nunits = npage *
                                           RT_MM_PAGE_SIZE /
                                           sizeof(struct rt_mem_head);
                        /* split memory */
                        r       = n + nunits;
                        r->next = n->next;
                        r->size = n->size - nunits;
                        *prev   = r;
                    }
                    else
                        *prev = n->next;

                    rt_module_free_page(module, n, npage);
                }
            }
            else
            {
                *prev = n;
            }

            /* unlock */
            rt_sem_release(&mod_sem);

            return;
        }
        if (b > n + n->size)
            break;

        prev = &(b->next);
    }

    if ((rt_uint32_t)n % RT_MM_PAGE_SIZE == 0)
    {
        int npage = n->size * sizeof(struct rt_page_info) / RT_MM_PAGE_SIZE;
        if (npage > 0)
        {
            rt_module_free_page(module, n, npage);
            if (n->size % RT_MM_PAGE_SIZE != 0)
            {
                rt_size_t nunits =
                    npage * RT_MM_PAGE_SIZE / sizeof(struct rt_mem_head);
                /* split memory */
                r       = n + nunits;
                r->next = b;
                r->size = n->size - nunits;
                *prev   = r;
            }
            else
            {
                *prev = b;
            }
        }
    }
    else
    {
        n->next = b;
        *prev   = n;
    }

    /* unlock */
    rt_sem_release(&mod_sem);
}

/**
 * rt_module_realloc - realloc memory block in free list
 */
void *rt_module_realloc(void *ptr, rt_size_t size)
{
    struct rt_mem_head *b, *p, *prev, *tmpp;
    rt_size_t nunits;
    rt_module_t self_module;

    self_module = rt_module_self();
    RT_ASSERT(self_module != RT_NULL);

    RT_DEBUG_NOT_IN_INTERRUPT;

    if (!ptr)
        return rt_module_malloc(size);
    if (size == 0)
    {
        rt_module_free(self_module, ptr);

        return RT_NULL;
    }

    nunits = (size + sizeof(struct rt_mem_head) - 1) /
             sizeof(struct rt_mem_head)
             + 1;
    b = (struct rt_mem_head *)ptr - 1;

    if (nunits <= b->size)
    {
        /* new size is smaller or equal then before */
        if (nunits == b->size)
            return ptr;
        else
        {
            p       = b + nunits;
            p->size = b->size - nunits;
            b->size = nunits;
            rt_module_free(self_module, (void *)(p + 1));

            return (void *)(b + 1);
        }
    }
    else
    {
        /* more space then required */
        prev = (struct rt_mem_head *)self_module->mem_list;
        for (p = prev->next;
             p != (b->size + b) && p != RT_NULL;
             prev = p, p = p->next)
        {
            break;
        }

        /* available block after ap in freelist */
        if (p != RT_NULL &&
            (p->size >= (nunits - (b->size))) &&
            p == (b + b->size))
        {
            /* perfect match */
            if (p->size == (nunits - (b->size)))
            {
                b->size    = nunits;
                prev->next = p->next;
            }
            else  /* more space then required, split block */
            {
                /* pointer to old header */
                tmpp = p;
                p    = b + nunits;

                /* restoring old pointer */
                p->next = tmpp->next;

                /* new size for p */
                p->size    = tmpp->size + b->size - nunits;
                b->size    = nunits;
                prev->next = p;
            }
            self_module->mem_list = (void *)prev;

            return (void *)(b + 1);
        }
        else /* allocate new memory and copy old data */
        {
            if ((p = rt_module_malloc(size)) == RT_NULL)
                return RT_NULL;
            rt_memmove(p, (b + 1), ((b->size) * sizeof(struct rt_mem_head)));
            rt_module_free(self_module, (void *)(b + 1));

            return (void *)(p);
        }
    }
}

#ifdef RT_USING_FINSH
#include <finsh.h>

void list_memlist(const char *name)
{
    rt_module_t module;
    struct rt_mem_head **prev;
    struct rt_mem_head *b;

    module = rt_module_find(name);
    if (module == RT_NULL)
        return;

    for (prev = (struct rt_mem_head **)&module->mem_list;
         (b = *prev) != RT_NULL;
         prev = &(b->next))
    {
        rt_kprintf("0x%x--%d\n", b, b->size * sizeof(struct rt_mem_head));
    }
}
FINSH_FUNCTION_EXPORT(list_memlist, list module free memory information)

void list_mempage(const char *name)
{
    rt_module_t module;
    struct rt_page_info *page;
    int i;

    module = rt_module_find(name);
    if (module == RT_NULL)
        return;

    page = (struct rt_page_info *)module->page_array;

    for (i = 0; i < module->page_cnt; i ++)
    {
        rt_kprintf("0x%x--%d\n", page[i].page_ptr, page[i].npage);
    }
}
FINSH_FUNCTION_EXPORT(list_mempage, list module using memory page information)
#endif /* RT_USING_FINSH */

#endif /* RT_USING_SLAB */

#endif
