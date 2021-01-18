/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-12     Bernard      first version
 * 2018-11-02     heyuanjie    fix complie error in iar
 */

#include <rthw.h>
#include <rtthread.h>

#include <dfs_posix.h>
#include <lwp_elf.h>
#include <lwp_console.h>

#ifndef RT_USING_DFS
#error "lwp need file system(RT_USING_DFS)"
#endif

#include "lwp.h"

#define DBG_TAG "LWP"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

#define AUX_ARRAY_ITEMS_NR 6

/* aux key */
#define AT_NULL 0
#define AT_IGNORE 1
#define AT_EXECFD 2
#define AT_PHDR 3
#define AT_PHENT 4
#define AT_PHNUM 5
#define AT_PAGESZ 6
#define AT_BASE 7
#define AT_FLAGS 8
#define AT_ENTRY 9
#define AT_NOTELF 10
#define AT_UID 11
#define AT_EUID 12
#define AT_GID 13
#define AT_EGID 14
#define AT_CLKTCK 17
#define AT_PLATFORM 15
#define AT_HWCAP 16
#define AT_FPUCW 18
#define AT_DCACHEBSIZE 19
#define AT_ICACHEBSIZE 20
#define AT_UCACHEBSIZE 21
#define AT_IGNOREPPC 22
#define AT_SECURE 23
#define AT_BASE_PLATFORM 24
#define AT_RANDOM 25
#define AT_HWCAP2 26
#define AT_EXECFN 31

struct process_aux_item
{
    uint32_t key;
    uint32_t value;
};

struct process_aux
{
    struct process_aux_item item[AUX_ARRAY_ITEMS_NR];
};

#ifdef RT_USING_USERSPACE
#ifdef RT_USING_GDBSERVER
#include <hw_breakpoint.h>
#include <lwp_gdbserver.h>
#endif

#include <lwp_mm_area.h>
#include <lwp_user_mm.h>

#define USER_LOAD_VADDR 0x100000
#endif

static const char elf_magic[] = {0x7f, 'E', 'L', 'F'};

extern void lwp_user_entry(void *args, const void *text, void *data, void *user_stack);
extern int libc_stdio_get_console(void);

/**
 * RT-Thread light-weight process
 */
void lwp_set_kernel_sp(uint32_t *sp)
{
    rt_thread_self()->kernel_sp = (rt_uint32_t *)sp;
}

uint32_t *lwp_get_kernel_sp(void)
{
#ifdef RT_USING_USERSPACE
    return (uint32_t *)rt_thread_self()->sp;
#else
    return (uint32_t *)rt_thread_self()->kernel_sp;
#endif
}

#ifdef RT_USING_USERSPACE
static struct process_aux *lwp_argscopy(struct rt_lwp *lwp, int argc, char **argv, char **envp)
{
    int size = sizeof(int) * 5; /* store argc, argv, envp, aux, NULL */
    int *args;
    char *str;
    char *str_k;
    char **new_argve;
    int i;
    int len;
    int *args_k;
    struct process_aux *aux;

    for (i = 0; i < argc; i++)
    {
        size += (rt_strlen(argv[i]) + 1);
    }
    size += (sizeof(int) * argc);

    i = 0;
    if (envp)
    {
        while (envp[i] != 0)
        {
            size += (rt_strlen(envp[i]) + 1);
            size += sizeof(int);
            i++;
        }
    }

    /* for aux */
    size += sizeof(struct process_aux);

    if (size > ARCH_PAGE_SIZE)
        return RT_NULL;

    /* args = (int*)lwp_map_user(lwp, 0, size); */
    args = (int *)lwp_map_user(lwp, (void *)(KERNEL_VADDR_START - ARCH_PAGE_SIZE), size);
    if (args == RT_NULL)
        return RT_NULL;

    args_k = (int *)rt_hw_mmu_v2p(&lwp->mmu_info, args);
    args_k = (int *)((size_t)args_k - PV_OFFSET);

    /* argc, argv[], 0, envp[], 0 , aux[] */
    str = (char *)((size_t)args + (argc + 2 + i + 1 + AUX_ARRAY_ITEMS_NR * 2 + 1) * sizeof(int));
    str_k = (char *)((size_t)args_k + (argc + 2 + i + 1 + AUX_ARRAY_ITEMS_NR * 2 + 1) * sizeof(int));

    new_argve = (char **)&args_k[1];
    args_k[0] = argc;

    for (i = 0; i < argc; i++)
    {
        len = rt_strlen(argv[i]) + 1;
        new_argve[i] = str;
        rt_memcpy(str_k, argv[i], len);
        str += len;
        str_k += len;
    }
    new_argve[i] = 0;
    i++;

    new_argve[i] = 0;
    if (envp)
    {
        int j;

        for (j = 0; envp[j] != 0; j++)
        {
            len = rt_strlen(envp[j]) + 1;
            new_argve[i] = str;
            rt_memcpy(str_k, envp[j], len);
            str += len;
            str_k += len;
            i++;
        }
        new_argve[i] = 0;
    }
    i++;

    /* aux */
    aux = (struct process_aux *)(new_argve + i);
    aux->item[0].key = AT_EXECFN;
    aux->item[0].value = (uint32_t)(size_t)new_argve[0];
    i += AUX_ARRAY_ITEMS_NR * 2;
    new_argve[i] = 0;

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, args_k, size);

    lwp->args = args;

    return aux;
}
#else
static struct process_aux *lwp_argscopy(struct rt_lwp *lwp, int argc, char **argv, char **envp)
{
    int size = sizeof(int) * 5; /* store argc, argv, envp, aux, NULL */
    int *args;
    char *str;
    char **new_argve;
    int i;
    int len;
    struct process_aux *aux;

    for (i = 0; i < argc; i++)
    {
        size += (rt_strlen(argv[i]) + 1);
    }
    size += (sizeof(int) * argc);

    i = 0;
    if (envp)
    {
        while (envp[i] != 0)
        {
            size += (rt_strlen(envp[i]) + 1);
            size += sizeof(int);
            i++;
        }
    }

    /* for aux */
    size += sizeof(struct process_aux);

    args = (int *)rt_malloc(size);
    if (args == RT_NULL)
        return RT_NULL;

    /* argc, argv[], 0, envp[], 0 */
    str = (char *)((size_t)args + (argc + 2 + i + 1 + AUX_ARRAY_ITEMS_NR * 2 + 1) * sizeof(int));

    new_argve = (char **)&args[1];
    args[0] = argc;

    for (i = 0; i < argc; i++)
    {
        len = rt_strlen(argv[i]) + 1;
        new_argve[i] = str;
        rt_memcpy(str, argv[i], len);
        str += len;
    }
    new_argve[i] = 0;
    i++;

    new_argve[i] = 0;
    if (envp)
    {
        int j;
        for (j = 0; envp[j] != 0; j++)
        {
            len = rt_strlen(envp[j]) + 1;
            new_argve[i] = str;
            rt_memcpy(str, envp[j], len);
            str += len;
            i++;
        }
        new_argve[i] = 0;
    }

    /* aux */
    aux = (struct process_aux *)(new_argve + i);
    aux->item[0].key = AT_EXECFN;
    aux->item[0].value = (uint32_t)(size_t)new_argve[0];
    i += AUX_ARRAY_ITEMS_NR * 2;
    new_argve[i] = 0;

    lwp->args = args;

    return aux;
}
#endif

#define check_off(voff, vlen)           \
    do                                  \
    {                                   \
        if (voff > vlen)                \
        {                               \
            result = -RT_ERROR;         \
            goto _exit;                 \
        }                               \
    } while (0)

#define check_read(vrlen, vrlen_want)   \
    do                                  \
    {                                   \
        if (vrlen < vrlen_want)         \
        {                               \
            result = -RT_ERROR;         \
            goto _exit;                 \
        }                               \
    } while (0)

static size_t load_fread(void *ptr, size_t size, size_t nmemb, int fd)
{
    size_t read_block = 0;

    while (nmemb)
    {
        size_t count;

        count = read(fd, ptr, size * nmemb) / size;
        if (count < nmemb)
        {
            LOG_E("ERROR: file size error!");
            break;
        }

        ptr = (void *)((uint8_t *)ptr + (count * size));
        nmemb -= count;
        read_block += count;
    }

    return read_block;
}

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
void lwp_elf_reloc(rt_mmu_info *m_info, void *text_start, void *rel_dyn_start, size_t rel_dyn_size, void *got_start, size_t got_size, Elf32_sym *dynsym);
#else
void lwp_elf_reloc(void *text_start, void *rel_dyn_start, size_t rel_dyn_size, void *got_start, size_t got_size, Elf32_sym *dynsym);
#endif

static int load_elf(int fd, int len, struct rt_lwp *lwp, uint8_t *load_addr, struct process_aux *aux)
{
    uint32_t i;
    uint32_t off = 0;
    char *p_section_str = 0;
    Elf32_sym *dynsym = 0;
    Elf32_Ehdr eheader;
    Elf32_Phdr pheader;
    Elf32_Shdr sheader;
    int result = RT_EOK;
    uint32_t magic;
    size_t read_len;
    void *got_start = 0;
    size_t got_size = 0;
    void *rel_dyn_start = 0;
    size_t rel_dyn_size = 0;
    size_t dynsym_off = 0;
    size_t dynsym_size = 0;

#ifdef RT_USING_USERSPACE
    rt_mmu_info *m_info = &lwp->mmu_info;
#endif

    if (len < sizeof eheader)
    {
        return -RT_ERROR;
    }

    lseek(fd, 0, SEEK_SET);
    read_len = load_fread(&magic, 1, sizeof magic, fd);
    check_read(read_len, sizeof magic);

    if (memcmp(elf_magic, &magic, 4) != 0)
    {
        return -RT_ERROR;
    }

    lseek(fd, off, SEEK_SET);
    read_len = load_fread(&eheader, 1, sizeof eheader, fd);
    check_read(read_len, sizeof eheader);

    if (eheader.e_ident[4] != 1)
    { /* not 32bit */
        return -RT_ERROR;
    }
    if (eheader.e_ident[6] != 1)
    { /* ver not 1 */
        return -RT_ERROR;
    }

    if ((eheader.e_type != ET_DYN)
#ifdef RT_USING_USERSPACE
        && (eheader.e_type != ET_EXEC)
#endif
    )
    {
        /* not pie or exec elf */
        return -RT_ERROR;
    }

    { /* load aux */
#ifdef RT_USING_USERSPACE
        void *pa, *va;
#endif
        uint8_t *process_header;
        size_t process_header_size;

        off = eheader.e_phoff;
        process_header_size = eheader.e_phnum * sizeof pheader;
        if (process_header_size > ARCH_PAGE_SIZE)
            return -RT_ERROR;
#ifdef RT_USING_USERSPACE
        va = (uint8_t *)lwp_map_user(lwp, (void *)(KERNEL_VADDR_START - ARCH_PAGE_SIZE * 2), process_header_size);
        if (!va)
            return -RT_ERROR;
        pa = rt_hw_mmu_v2p(m_info, va);
        process_header = (uint8_t*)pa - PV_OFFSET;
#else
        process_header = (uint8_t *)rt_malloc(process_header_size);
        if (!process_header)
            return -RT_ERROR;
#endif
        check_off(off, len);
        lseek(fd, off, SEEK_SET);
        read_len = load_fread(process_header, 1, process_header_size, fd);
        check_read(read_len, process_header_size);
#ifdef RT_USING_USERSPACE
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, process_header, process_header_size);
#endif

        aux->item[1].key = AT_PAGESZ;
        aux->item[1].value = ARCH_PAGE_SIZE;
        aux->item[2].key = AT_RANDOM;
        aux->item[2].value = rt_tick_get();
        aux->item[3].key = AT_PHDR;
#ifdef RT_USING_USERSPACE
        aux->item[3].value = (uint32_t)(size_t)va;
#else
        aux->item[3].value = (uint32_t)(size_t)process_header;
#endif
        aux->item[4].key = AT_PHNUM;
        aux->item[4].value = eheader.e_phnum;
        aux->item[5].key = AT_PHENT;
        aux->item[5].value = sizeof pheader;
#ifdef RT_USING_USERSPACE
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, aux, sizeof *aux);
#endif
    }

    off = eheader.e_phoff;
    for (i = 0; i < eheader.e_phnum; i++, off += sizeof pheader)
    {
        check_off(off, len);
        lseek(fd, off, SEEK_SET);
        read_len = load_fread(&pheader, 1, sizeof pheader, fd);
        check_read(read_len, sizeof pheader);

        if (pheader.p_type == PT_LOAD)
        {
            if (pheader.p_filesz > pheader.p_memsz)
            {
                return -RT_ERROR;
            }
            if (load_addr)
            {
                if (eheader.e_type == ET_EXEC)
                {
                    result = -RT_ERROR;
                    goto _exit;
                }
                lwp->text_entry = load_addr;
            }
            else
            {
#ifdef RT_USING_USERSPACE
                void *va;

                if (eheader.e_type == ET_EXEC)
                {
                    if (pheader.p_vaddr != USER_LOAD_VADDR)
                    {
                        result = -RT_ERROR;
                        goto _exit;
                    }
                    va = lwp_map_user(lwp, (void *)pheader.p_vaddr, pheader.p_memsz);
                }
                else
                {
                    va = lwp_map_user(lwp, 0, pheader.p_memsz);
                }
                if (va)
                {
                    lwp->text_entry = va;
                    lwp->text_size = pheader.p_memsz;
                }
                else
                {
                    lwp->text_entry = RT_NULL;
                }
#else
#ifdef RT_USING_CACHE
                lwp->text_entry = (rt_uint8_t *)rt_malloc_align(pheader.p_memsz, RT_CPU_CACHE_LINE_SZ);
#else
                lwp->text_entry = (rt_uint8_t *)rt_malloc(pheader.p_memsz);
#endif
#endif
                if (lwp->text_entry == RT_NULL)
                {
                    LOG_E("alloc text memory faild!");
                    result = -RT_ENOMEM;
                    goto _exit;
                }
                else
                {
                    LOG_D("lwp text malloc : %p, size: %d!", lwp->text_entry, lwp->text_size);
                }
                check_off(pheader.p_offset, len);
                lseek(fd, pheader.p_offset, SEEK_SET);
#ifdef RT_USING_USERSPACE
                {
                    uint32_t size = pheader.p_filesz;
                    void *va_self;
                    void *pa;
                    size_t tmp_len = 0;

                    read_len = 0;
                    while (size)
                    {
                        pa = rt_hw_mmu_v2p(m_info, va);
                        va_self = (void*)((char*)pa - PV_OFFSET);
                        LOG_D("va_self = %p pa = %p", va_self, pa);
                        tmp_len = (size < ARCH_PAGE_SIZE) ? size : ARCH_PAGE_SIZE;
                        tmp_len = load_fread(va_self, 1, tmp_len, fd);
                        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, va_self, tmp_len);
                        read_len += tmp_len;
                        size -= tmp_len;
                        va = (void*)((char*)va + ARCH_PAGE_SIZE);
                    }
                }
#else
                read_len = load_fread(lwp->text_entry, 1, pheader.p_filesz, fd);
#endif
                check_read(read_len, pheader.p_filesz);
            }
            if (pheader.p_filesz < pheader.p_memsz)
            {
#ifdef RT_USING_USERSPACE
                void *va = (void*)((char*)lwp->text_entry + pheader.p_filesz);
                void *va_self;
                void *pa;
                uint32_t size = pheader.p_memsz - pheader.p_filesz;
                uint32_t size_s;
                uint32_t off;

                off = pheader.p_filesz & ARCH_PAGE_MASK;
                va = (void *)(((size_t)lwp->text_entry + pheader.p_filesz) & ~ARCH_PAGE_MASK);
                while (size)
                {
                    size_s = (size < ARCH_PAGE_SIZE - off) ? size : ARCH_PAGE_SIZE - off;
                    pa = rt_hw_mmu_v2p(m_info, va);
                    va_self = (void*)((char*)pa - PV_OFFSET);
                    memset((void*)((char*)va_self + off), 0, size_s);
                    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void*)((char*)va_self + off), size_s);
                    off = 0;
                    size -= size_s;
                    va = (void*)((char*)va + ARCH_PAGE_SIZE);
                }
#else
                memset((uint8_t *)lwp->text_entry + pheader.p_filesz, 0, (size_t)(pheader.p_memsz - pheader.p_filesz));
#endif
            }
            break;
        }
    }

    if (eheader.e_type == ET_DYN)
    {
        /* section info */
        off = eheader.e_shoff;
        /* find section string table */
        check_off(off, len);
        lseek(fd, off + (sizeof sheader) * eheader.e_shstrndx, SEEK_SET);
        read_len = load_fread(&sheader, 1, sizeof sheader, fd);
        check_read(read_len, sizeof sheader);

        p_section_str = (char *)rt_malloc(sheader.sh_size);
        if (!p_section_str)
        {
            LOG_E("out of memory!");
            result = -ENOMEM;
            goto _exit;
        }

        check_off(sheader.sh_offset, len);
        lseek(fd, sheader.sh_offset, SEEK_SET);
        read_len = load_fread(p_section_str, 1, sheader.sh_size, fd);
        check_read(read_len, sheader.sh_size);

        check_off(off, len);
        lseek(fd, off, SEEK_SET);
        for (i = 0; i < eheader.e_shnum; i++, off += sizeof sheader)
        {
            read_len = load_fread(&sheader, 1, sizeof sheader, fd);
            check_read(read_len, sizeof sheader);

            if (strcmp(p_section_str + sheader.sh_name, "text") == 0)
            {
                lwp->text_size = sheader.sh_size;
            }
            else if (strcmp(p_section_str + sheader.sh_name, ".got") == 0)
            {
                got_start = (void *)((uint8_t *)lwp->text_entry + sheader.sh_addr);
                got_size = (size_t)sheader.sh_size;
            }
            else if (strcmp(p_section_str + sheader.sh_name, ".rel.dyn") == 0)
            {
                rel_dyn_start = (void *)((uint8_t *)lwp->text_entry + sheader.sh_addr);
                rel_dyn_size = (size_t)sheader.sh_size;
            }
            else if (strcmp(p_section_str + sheader.sh_name, ".dynsym") == 0)
            {
                dynsym_off = (size_t)sheader.sh_offset;
                dynsym_size = (size_t)sheader.sh_size;
            }
        }
        /* reloc */
        if (dynsym_size)
        {
            dynsym = rt_malloc(dynsym_size);
            if (!dynsym)
            {
                LOG_E("ERROR: Malloc error!");
                result = -ENOMEM;
                goto _exit;
            }
            check_off(dynsym_off, len);
            lseek(fd, dynsym_off, SEEK_SET);
            read_len = load_fread(dynsym, 1, dynsym_size, fd);
            check_read(read_len, dynsym_size);
        }
#ifdef RT_USING_USERSPACE
        lwp_elf_reloc(m_info, (void *)lwp->text_entry, rel_dyn_start, rel_dyn_size, got_start, got_size, dynsym);
#else
        lwp_elf_reloc((void *)lwp->text_entry, rel_dyn_start, rel_dyn_size, got_start, got_size, dynsym);

        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, lwp->text_entry, lwp->text_size);
        rt_hw_cpu_icache_ops(RT_HW_CACHE_INVALIDATE, lwp->text_entry, lwp->text_size);
#endif
    }
    LOG_D("lwp->text_entry = 0x%p", lwp->text_entry);
    LOG_D("lwp->text_size  = 0x%p", lwp->text_size);

_exit:
    if (dynsym)
    {
        rt_free(dynsym);
    }
    if (p_section_str)
    {
        rt_free(p_section_str);
    }
    if (result != RT_EOK)
    {
        LOG_E("lwp dynamic load faild, %d", result);
        lwp_ref_dec(lwp);
    }
    return result;
}

int lwp_load(const char *filename, struct rt_lwp *lwp, uint8_t *load_addr, size_t addr_size, struct process_aux *aux);

RT_WEAK int lwp_load(const char *filename, struct rt_lwp *lwp, uint8_t *load_addr, size_t addr_size, struct process_aux *aux)
{
    uint8_t *ptr;
    int ret = -1;
    int len;
    int fd = -1;

    /* check file name */
    RT_ASSERT(filename != RT_NULL);
    /* check lwp control block */
    RT_ASSERT(lwp != RT_NULL);

    /* copy file name to process name */
    rt_strncpy(lwp->cmd, filename, RT_NAME_MAX);

    if (load_addr != RT_NULL)
    {
        lwp->lwp_type = LWP_TYPE_FIX_ADDR;
        ptr = load_addr;
    }
    else
    {
        lwp->lwp_type = LWP_TYPE_DYN_ADDR;
        ptr = RT_NULL;
    }

    fd = open(filename, O_BINARY | O_RDONLY, 0);
    if (fd < 0)
    {
        LOG_E("ERROR: Can't open elf file %s!", filename);
        goto out;
    }
    len = lseek(fd, 0, SEEK_END);
    if (len < 0)
    {
        LOG_E("ERROR: File %s size error!", filename);
        goto out;
    }

    lseek(fd, 0, SEEK_SET);

    ret = load_elf(fd, len, lwp, ptr, aux);
    if (ret != RT_EOK)
    {
        LOG_E("lwp load ret = %d", ret);
    }

out:
    if (fd > 0)
    {
        close(fd);
    }
    return ret;
}

void lwp_cleanup(struct rt_thread *tid)
{
    rt_base_t level;
    struct rt_lwp *lwp;

    if (tid == NULL) return;

    LOG_I("cleanup thread: %s, stack_addr: %08X", tid->name, tid->stack_addr);

#ifndef RT_USING_USERSPACE
    if (tid->user_stack != RT_NULL)
    {
        rt_free(tid->user_stack);
    }
#endif

    level = rt_hw_interrupt_disable();
    lwp = (struct rt_lwp *)tid->lwp;

    lwp_tid_put(tid->tid);
    rt_list_remove(&tid->sibling);
    lwp_ref_dec(lwp);
    rt_hw_interrupt_enable(level);

    return;
}

static void lwp_copy_stdio_fdt(struct rt_lwp *lwp)
{
    int fd;
    struct dfs_fd *d;
    struct dfs_fdtable *lwp_fdt;

    fd = libc_stdio_get_console();
    d = fd_get(fd);
    fd_put(d);

    fd = fd - DFS_FD_OFFSET;
    if (d == NULL)
    {
        return;
    }

    lwp_fdt = &lwp->fdt;
    lwp_fdt->fds = rt_malloc(sizeof(void *) * (fd + 1));
    rt_memset(lwp_fdt->fds, 0, sizeof(void *) * (fd + 1));
    lwp_fdt->fds[fd] = d;
    lwp_fdt->maxfd = fd + 1;

    return;
}

static void lwp_thread_entry(void *parameter)
{
    rt_thread_t tid;
    struct rt_lwp *lwp;

    tid = rt_thread_self();
    lwp = (struct rt_lwp *)tid->lwp;
    tid->cleanup = lwp_cleanup;
    tid->user_stack = RT_NULL;

#ifdef RT_USING_GDBSERVER
    if (lwp->debug)
    {
        lwp->bak_first_ins = *(uint32_t *)lwp->text_entry;
        *(uint32_t *)lwp->text_entry = INS_BREAK_CONNECT;
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, lwp->text_entry, sizeof(uint32_t));
        icache_invalid_all();
    }
#endif

    lwp_user_entry(lwp->args, lwp->text_entry, lwp->data_entry, RT_NULL);
}

struct rt_lwp *lwp_self(void)
{
    rt_thread_t tid;

    tid = rt_thread_self();
    if (tid)
    {
        return (struct rt_lwp *)tid->lwp;
    }

    return RT_NULL;
}

#ifdef RT_USING_GDBSERVER
pid_t lwp_execve(char *filename, int debug, int argc, char **argv, char **envp)
#else
pid_t lwp_execve(char *filename, int argc, char **argv, char **envp)
#endif
{
    int result;
    rt_base_t level;
    struct rt_lwp *lwp;
    char *thread_name;
    char *argv_last = argv[argc - 1];
    int bg = 0;
    struct process_aux *aux;
    int tid = 0;

    if (filename == RT_NULL)
        return -RT_ERROR;

    lwp = lwp_new();

    if (lwp == RT_NULL)
    {
        dbg_log(DBG_ERROR, "lwp struct out of memory!\n");
        return -RT_ENOMEM;
    }
    LOG_D("lwp malloc : %p, size: %d!", lwp, sizeof(struct rt_lwp));

    if ((tid = lwp_tid_get()) == 0)
    {
        lwp_ref_dec(lwp);
        return -ENOMEM;
    }
#ifdef RT_USING_USERSPACE
    if (lwp_user_space_init(lwp) != 0)
    {
        lwp_tid_put(tid);
        lwp_ref_dec(lwp);
        return -ENOMEM;
    }
#endif

    if (argv_last[0] == '&' && argv_last[1] == '\0')
    {
        argc--;
        bg = 1;
    }

    if ((aux = lwp_argscopy(lwp, argc, argv, envp)) == RT_NULL)
    {
        lwp_tid_put(tid);
        lwp_ref_dec(lwp);
        return -ENOMEM;
    }

    result = lwp_load(filename, lwp, RT_NULL, 0, aux);
    if (result == RT_EOK)
    {
        rt_thread_t thread = RT_NULL;

        lwp_copy_stdio_fdt(lwp);

        /* obtain the base name */
        thread_name = strrchr(filename, '/');
        thread_name = thread_name ? thread_name + 1 : filename;

        thread = rt_thread_create(thread_name, lwp_thread_entry, RT_NULL,
                               1024 * 4, 25, 200);
        if (thread != RT_NULL)
        {
            struct rt_lwp *lwp_self;

            thread->tid = tid;
            lwp_tid_set_thread(tid, thread);
            LOG_D("lwp kernel => (0x%08x, 0x%08x)\n", (rt_uint32_t)thread->stack_addr, (rt_uint32_t)thread->stack_addr + thread->stack_size);
            level = rt_hw_interrupt_disable();
            lwp_self = (struct rt_lwp *)rt_thread_self()->lwp;
            if (lwp_self)
            {
                /* lwp add to children link */
                lwp->sibling = lwp_self->first_child;
                lwp_self->first_child = lwp;
                lwp->parent = lwp_self;
            }
            thread->lwp = lwp;
            rt_list_insert_after(&lwp->t_grp, &thread->sibling);

#ifdef RT_USING_GDBSERVER
            if (debug)
            {
                lwp->debug = debug;
            }
#endif

            if ((rt_console_get_foreground() == lwp_self) && !bg)
            {
                rt_console_set_foreground(lwp);
            }
            rt_hw_interrupt_enable(level);

            rt_thread_startup(thread);
            return lwp_to_pid(lwp);
        }
    }

    lwp_tid_put(tid);
    lwp_ref_dec(lwp);

    return -RT_ERROR;
}

#ifdef RT_USING_GDBSERVER
pid_t exec(char *filename, int debug, int argc, char **argv)
{
    return lwp_execve(filename, debug, argc, argv, 0);
}
#else
pid_t exec(char *filename, int argc, char **argv)
{
    return lwp_execve(filename, argc, argv, 0);
}
#endif
