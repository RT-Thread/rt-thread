/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-12     Bernard      first version
 * 2018-11-02     heyuanjie    fix complie error in iar
 * 2021-02-03     lizhirui     add 64-bit arch support and riscv64 arch support
 * 2021-08-26     linzhenxing  add lwp_setcwd\lwp_getcwd
 * 2023-02-20     wangxiaoyao  inv icache before new app startup
 * 2023-02-20     wangxiaoyao  fix bug on foreground app switch
 * 2023-10-16     Shell        Support a new backtrace framework
 * 2023-11-17     xqyjlj       add process group and session support
 * 2023-11-30     Shell        add lwp_startup()
 */

#define DBG_TAG "lwp"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

#include <rthw.h>
#include <rtthread.h>

#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h> /* rename() */
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/statfs.h> /* statfs() */

#include <lwp_elf.h>

#ifndef RT_USING_DFS
#error "lwp need file system(RT_USING_DFS)"
#endif

#include "lwp_internal.h"
#include "lwp_arch.h"
#include "lwp_arch_comm.h"
#include "lwp_signal.h"
#include "lwp_dbg.h"
#include <terminal/terminal.h>

#ifdef ARCH_MM_MMU
#include <lwp_user_mm.h>
#endif /* end of ARCH_MM_MMU */


#ifndef O_DIRECTORY
#define O_DIRECTORY 0x200000
#endif

#ifndef O_BINARY
#define O_BINARY 0x10000
#endif


static const char elf_magic[] = {0x7f, 'E', 'L', 'F'};
#ifdef DFS_USING_WORKDIR
extern char working_directory[];
#endif

/**
 * @brief The default console is only a backup device with lowest priority.
 *        It's always recommended to scratch the console from the boot arguments.
 *        And dont forget to register the device with a higher priority.
 */
static rt_err_t lwp_default_console_setup(void)
{
    rt_device_t bakdev = rt_device_find("ttyS0");
    rt_err_t rc;

    if (bakdev)
    {
        lwp_console_register_backend(bakdev, LWP_CONSOLE_LOWEST_PRIOR);
        rc = RT_EOK;
    }
    else
    {
        rc = -RT_EINVAL;
    }

    return rc;
}

static int lwp_component_init(void)
{
    int rc;
    if ((rc = lwp_tid_init()) != RT_EOK)
    {
        LOG_E("%s: lwp_component_init() failed", __func__);
    }
    else if ((rc = lwp_pid_init()) != RT_EOK)
    {
        LOG_E("%s: lwp_pid_init() failed", __func__);
    }
    else if ((rc = rt_channel_component_init()) != RT_EOK)
    {
        LOG_E("%s: rt_channel_component_init failed", __func__);
    }
    else if ((rc = lwp_futex_init()) != RT_EOK)
    {
        LOG_E("%s: lwp_futex_init() failed", __func__);
    }
    else if ((rc = lwp_default_console_setup()) != RT_EOK)
    {
        LOG_E("%s: lwp_default_console_setup() failed", __func__);
    }
    return rc;
}
INIT_COMPONENT_EXPORT(lwp_component_init);

rt_weak int lwp_startup_debug_request(void)
{
    return 0;
}

#define LATENCY_TIMES (3)
#define LATENCY_IN_MSEC (128)
#define LWP_CONSOLE_PATH "CONSOLE=/dev/console"
const char *init_search_path[] = {
    "/sbin/init",
    "/bin/init",
};

/**
 * Startup process 0 and do the essential works
 * This is the "Hello World" point of RT-Smart
 */
static int lwp_startup(void)
{
    int error;

    const char *init_path;
    char *argv[] = {0, "&"};
    char *envp[] = {LWP_CONSOLE_PATH, 0};

#ifdef LWP_DEBUG_INIT
    int command;
    int countdown = LATENCY_TIMES;
    while (countdown)
    {
        command = lwp_startup_debug_request();
        if (command)
        {
            return 0;
        }
        rt_kprintf("Press any key to stop init process startup ... %d\n", countdown);
        countdown -= 1;
        rt_thread_mdelay(LATENCY_IN_MSEC);
    }
    rt_kprintf("Starting init ...\n");
#endif /* LWP_DEBUG_INIT */

    for (size_t i = 0; i < sizeof(init_search_path)/sizeof(init_search_path[0]); i++)
    {
        struct stat s;
        init_path = init_search_path[i];
        error = stat(init_path, &s);
        if (error == 0)
        {
            argv[0] = (void *)init_path;
            error = lwp_execve((void *)init_path, 0, sizeof(argv)/sizeof(argv[0]), argv, envp);
            if (error < 0)
            {
                LOG_E("%s: failed to startup process 0 (init)\n"
                    "Switching to legacy mode...", __func__);
            }
            else if (error != 1)
            {
                LOG_E("%s: pid 1 is already allocated", __func__);
                error = -EBUSY;
            }
            else
            {
                rt_lwp_t p = lwp_from_pid_locked(1);
                p->sig_protected = 1;

                error = 0;
            }
            break;
        }
    }

    if (error)
    {
        LOG_D("%s: init program not found\n"
            "Switching to legacy mode...", __func__);
    }
    return error;
}
INIT_APP_EXPORT(lwp_startup);

void lwp_setcwd(char *buf)
{
    struct rt_lwp *lwp = RT_NULL;

    if(strlen(buf) >= DFS_PATH_MAX)
    {
        rt_kprintf("buf too long!\n");
        return ;
    }

    lwp = (struct rt_lwp *)rt_thread_self()->lwp;
    if (lwp)
    {
        rt_strncpy(lwp->working_directory, buf, DFS_PATH_MAX - 1);
    }
    else
    {
        rt_strncpy(working_directory, buf, DFS_PATH_MAX - 1);
    }

    return ;
}

char *lwp_getcwd(void)
{
    char *dir_buf = RT_NULL;
    struct rt_lwp *lwp = RT_NULL;
    rt_thread_t thread = rt_thread_self();

    if (thread)
    {
        lwp = (struct rt_lwp *)thread->lwp;
    }

    if (lwp)
    {
        if(lwp->working_directory[0] != '/')
        {
            dir_buf = &working_directory[0];
        }
        else
        {
            dir_buf = &lwp->working_directory[0];
        }
    }
    else
        dir_buf = &working_directory[0];

    return dir_buf;
}

/**
 * RT-Thread light-weight process
 */
void lwp_set_kernel_sp(uint32_t *sp)
{
    rt_thread_self()->kernel_sp = (rt_uint32_t *)sp;
}

uint32_t *lwp_get_kernel_sp(void)
{
#ifdef ARCH_MM_MMU
    return (uint32_t *)rt_thread_self()->sp;
#else
    uint32_t* kernel_sp;
    extern rt_uint32_t rt_interrupt_from_thread;
    extern rt_uint32_t rt_thread_switch_interrupt_flag;
    if (rt_thread_switch_interrupt_flag)
    {
        kernel_sp = (uint32_t *)((rt_thread_t)rt_container_of(rt_interrupt_from_thread, struct rt_thread, sp))->kernel_sp;
    }
    else
    {
        kernel_sp = (uint32_t *)rt_thread_self()->kernel_sp;
    }
    return kernel_sp;
#endif
}

#ifdef ARCH_MM_MMU
struct process_aux *lwp_argscopy(struct rt_lwp *lwp, int argc, char **argv, char **envp)
{
    int size = sizeof(size_t) * 5; /* store argc, argv, envp, aux, NULL */
    int *args;
    char *str;
    char *str_k;
    char **new_argve;
    int i;
    int len;
    size_t *args_k;
    struct process_aux *aux;
    size_t prot = PROT_READ | PROT_WRITE;
    size_t flags = MAP_FIXED | MAP_PRIVATE;
    size_t zero = 0;

    for (i = 0; i < argc; i++)
    {
        size += (rt_strlen(argv[i]) + 1);
    }
    size += (sizeof(size_t) * argc);

    i = 0;
    if (envp)
    {
        while (envp[i] != 0)
        {
            size += (rt_strlen(envp[i]) + 1);
            size += sizeof(size_t);
            i++;
        }
    }

    /* for aux */
    size += sizeof(struct process_aux);

    if (size > ARCH_PAGE_SIZE)
    {
        return RT_NULL;
    }

    args = lwp_mmap2(lwp, (void *)(USER_STACK_VEND), size, prot, flags, -1, 0);
    if (args == RT_NULL || lwp_data_put(lwp, args, &zero, sizeof(zero)) != sizeof(zero))
    {
        return RT_NULL;
    }

    args_k = (size_t *)lwp_v2p(lwp, args);
    args_k = (size_t *)((size_t)args_k - PV_OFFSET);

    /* argc, argv[], 0, envp[], 0 , aux[] */
    str = (char *)((size_t)args + (argc + 2 + i + 1 + AUX_ARRAY_ITEMS_NR * 2 + 1) * sizeof(size_t));
    str_k = (char *)((size_t)args_k + (argc + 2 + i + 1 + AUX_ARRAY_ITEMS_NR * 2 + 1) * sizeof(size_t));

    new_argve = (char **)&args_k[1];
    args_k[0] = argc;

    for (i = 0; i < argc; i++)
    {
        len = rt_strlen(argv[i]) + 1;
        new_argve[i] = str;
        lwp_memcpy(str_k, argv[i], len);
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
            lwp_memcpy(str_k, envp[j], len);
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
    aux->item[0].value = (size_t)(size_t)new_argve[0];
    i += AUX_ARRAY_ITEMS_NR * 2;
    new_argve[i] = 0;

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, args_k, size);

    lwp->args = args;

    return aux;
}
#else
static struct process_aux *lwp_argscopy(struct rt_lwp *lwp, int argc, char **argv, char **envp)
{
#ifdef ARCH_MM_MMU
    int size = sizeof(int) * 5; /* store argc, argv, envp, aux, NULL */
    struct process_aux *aux;
#else
    int size = sizeof(int) * 4; /* store argc, argv, envp, NULL */
#endif /* ARCH_MM_MMU */
    int *args;
    char *str;
    char **new_argve;
    int i;
    int len;

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

#ifdef ARCH_MM_MMU
    /* for aux */
    size += sizeof(struct process_aux);

    args = (int *)rt_malloc(size);
    if (args == RT_NULL)
    {
        return RT_NULL;
    }

    /* argc, argv[], 0, envp[], 0 */
    str = (char *)((size_t)args + (argc + 2 + i + 1 + AUX_ARRAY_ITEMS_NR * 2 + 1) * sizeof(int));
#else
    args = (int *)rt_malloc(size);
    if (args == RT_NULL)
    {
        return RT_NULL;
    }
    str = (char*)((int)args + (argc + 2 + i + 1) * sizeof(int));
#endif /* ARCH_MM_MMU */

    new_argve = (char **)&args[1];
    args[0] = argc;

    for (i = 0; i < argc; i++)
    {
        len = rt_strlen(argv[i]) + 1;
        new_argve[i] = str;
        lwp_memcpy(str, argv[i], len);
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
            lwp_memcpy(str, envp[j], len);
            str += len;
            i++;
        }
        new_argve[i] = 0;
    }
#ifdef ARCH_MM_MMU
    /* aux */
    aux = (struct process_aux *)(new_argve + i);
    aux->item[0].key = AT_EXECFN;
    aux->item[0].value = (uint32_t)(size_t)new_argve[0];
    i += AUX_ARRAY_ITEMS_NR * 2;
    new_argve[i] = 0;

    lwp->args = args;

    return aux;
#else
    lwp->args = args;
    lwp->args_length = size;

    return (struct process_aux *)(new_argve + i);
#endif /* ARCH_MM_MMU */
}
#endif

#ifdef ARCH_MM_MMU
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
    Elf_Word st_name;
    Elf_Addr st_value;
    Elf_Word st_size;
    unsigned char st_info;
    unsigned char st_other;
    Elf_Half st_shndx;
} Elf_sym;

#ifdef ARCH_MM_MMU
struct map_range
{
    void *start;
    size_t size;
};

static void expand_map_range(struct map_range *m, void *start, size_t size)
{
    if (!m->start)
    {
        m->start = start;
        m->size = size;
    }
    else
    {
        void *end = (void *)((char*)start + size);
        void *mend = (void *)((char*)m->start + m->size);

        if (m->start > start)
        {
            m->start = start;
        }
        if (mend < end)
        {
            mend = end;
        }
        m->size = (char *)mend - (char *)m->start;
    }
}

static int map_range_ckeck(struct map_range *m1, struct map_range *m2)
{
    void *m1_start = (void *)((size_t)m1->start & ~ARCH_PAGE_MASK);
    void *m1_end = (void *)((((size_t)m1->start + m1->size) + ARCH_PAGE_MASK) & ~ARCH_PAGE_MASK);
    void *m2_start = (void *)((size_t)m2->start & ~ARCH_PAGE_MASK);
    void *m2_end = (void *)((((size_t)m2->start + m2->size) + ARCH_PAGE_MASK) & ~ARCH_PAGE_MASK);

    if (m1->size)
    {
        if (m1_start < (void *)USER_LOAD_VADDR)
        {
            return -1;
        }
        if (m1_start > (void *)USER_STACK_VSTART)
        {
            return -1;
        }
        if (m1_end < (void *)USER_LOAD_VADDR)
        {
            return -1;
        }
        if (m1_end > (void *)USER_STACK_VSTART)
        {
            return -1;
        }
    }
    if (m2->size)
    {
        if (m2_start < (void *)USER_LOAD_VADDR)
        {
            return -1;
        }
        if (m2_start > (void *)USER_STACK_VSTART)
        {
            return -1;
        }
        if (m2_end < (void *)USER_LOAD_VADDR)
        {
            return -1;
        }
        if (m2_end > (void *)USER_STACK_VSTART)
        {
            return -1;
        }
    }

    if ((m1->size != 0) && (m2->size != 0))
    {
        if (m1_start < m2_start)
        {
            if (m1_end > m2_start)
            {
                return -1;
            }
        }
        else /* m2_start <= m1_start */
        {
            if (m2_end > m1_start)
            {
                return -1;
            }
        }
    }
    return 0;
}
#endif

static int load_elf(int fd, int len, struct rt_lwp *lwp, uint8_t *load_addr, struct process_aux *aux)
{
    uint32_t i;
    uint32_t off = 0;
    size_t load_off = 0;
    char *p_section_str = 0;
    Elf_sym *dynsym = 0;
    Elf_Ehdr eheader;
    Elf_Phdr pheader;
    Elf_Shdr sheader;
    int result = RT_EOK;
    uint32_t magic;
    size_t read_len;
    void *got_start = 0;
    size_t got_size = 0;
    void *rel_dyn_start = 0;
    size_t rel_dyn_size = 0;
    size_t dynsym_off = 0;
    size_t dynsym_size = 0;
#ifdef ARCH_MM_MMU
    struct map_range user_area[2] = {{NULL, 0}, {NULL, 0}}; /* 0 is text, 1 is data */
    void *pa, *va;
    void *va_self;

#endif

    if (len < sizeof eheader)
    {
        LOG_E("len < sizeof eheader!");
        return -RT_ERROR;
    }

    lseek(fd, 0, SEEK_SET);
    read_len = load_fread(&magic, 1, sizeof magic, fd);
    check_read(read_len, sizeof magic);

    if (memcmp(elf_magic, &magic, 4) != 0)
    {
        LOG_E("elf_magic not same, magic:0x%x!", magic);
        return -RT_ERROR;
    }

    lseek(fd, off, SEEK_SET);
    read_len = load_fread(&eheader, 1, sizeof eheader, fd);
    check_read(read_len, sizeof eheader);

#ifndef ARCH_CPU_64BIT
    if (eheader.e_ident[4] != 1)
    { /* not 32bit */
        LOG_E("elf not 32bit, %d!", eheader.e_ident[4]);
        return -RT_ERROR;
    }
#else
    if (eheader.e_ident[4] != 2)
    { /* not 64bit */
        LOG_E("elf not 64bit, %d!", eheader.e_ident[4]);
        return -RT_ERROR;
    }
#endif

    if (eheader.e_ident[6] != 1)
    { /* ver not 1 */
        LOG_E("elf Version not 1,ver:%d!", eheader.e_ident[6]);
        return -RT_ERROR;
    }

    if ((eheader.e_type != ET_DYN)
#ifdef ARCH_MM_MMU
        && (eheader.e_type != ET_EXEC)
#endif
    )
    {
        /* not pie or exec elf */
        LOG_E("elf type not pie or exec, type:%d!", eheader.e_type);
        return -RT_ERROR;
    }

#ifdef ARCH_MM_MMU
    {
        off = eheader.e_phoff;
        for (i = 0; i < eheader.e_phnum; i++, off += sizeof pheader)
        {
            check_off(off, len);
            lseek(fd, off, SEEK_SET);
            read_len = load_fread(&pheader, 1, sizeof pheader, fd);
            check_read(read_len, sizeof pheader);

            if (pheader.p_type == PT_DYNAMIC)
            {
                /* load ld.so */
                return 1; /* 1 means dynamic */
            }
        }
    }
#endif

    if (eheader.e_entry != 0)
    {
        if ((eheader.e_entry != USER_LOAD_VADDR)
                && (eheader.e_entry != LDSO_LOAD_VADDR))
        {
            /* the entry is invalidate */
            LOG_E("elf entry is invalidate, entry:0x%x!", eheader.e_entry);
            return -RT_ERROR;
        }
    }

    { /* load aux */
        uint8_t *process_header;
        size_t process_header_size;

        off = eheader.e_phoff;
        process_header_size = eheader.e_phnum * sizeof pheader;
#ifdef ARCH_MM_MMU
        if (process_header_size > ARCH_PAGE_SIZE - sizeof(char[16]))
        {
            LOG_E("process_header_size too big, size:0x%x!", process_header_size);
            return -RT_ERROR;
        }
        va = (uint8_t *)lwp_map_user(lwp, (void *)(USER_VADDR_TOP - ARCH_PAGE_SIZE * 2), process_header_size, 0);
        if (!va)
        {
            LOG_E("lwp map user failed!");
            return -RT_ERROR;
        }
        pa = lwp_v2p(lwp, va);
        process_header = (uint8_t *)pa - PV_OFFSET;
#else
        process_header = (uint8_t *)rt_malloc(process_header_size + sizeof(char[16]));
        if (!process_header)
        {
            LOG_E("process_header malloc failed, size:0x%x!", process_header_size + sizeof(char[16]));
            return -RT_ERROR;
        }
#endif
        check_off(off, len);
        lseek(fd, off, SEEK_SET);
        read_len = load_fread(process_header, 1, process_header_size, fd);
        check_read(read_len, process_header_size);
#ifdef ARCH_MM_MMU
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, process_header, process_header_size);
#endif

        aux->item[1].key = AT_PAGESZ;
#ifdef ARCH_MM_MMU
        aux->item[1].value = ARCH_PAGE_SIZE;
#else
        aux->item[1].value = RT_MM_PAGE_SIZE;
#endif
        aux->item[2].key = AT_RANDOM;
        {
            uint32_t random_value = rt_tick_get();
            uint8_t *random;
#ifdef ARCH_MM_MMU
            uint8_t *krandom;

            random = (uint8_t *)(USER_VADDR_TOP - ARCH_PAGE_SIZE - sizeof(char[16]));

            krandom = (uint8_t *)lwp_v2p(lwp, random);
            krandom = (uint8_t *)krandom - PV_OFFSET;
            rt_memcpy(krandom, &random_value, sizeof random_value);
#else
            random = (uint8_t *)(process_header + process_header_size);
            rt_memcpy(random, &random_value, sizeof random_value);
#endif
            aux->item[2].value = (size_t)random;
        }
        aux->item[3].key = AT_PHDR;
#ifdef ARCH_MM_MMU
        aux->item[3].value = (size_t)va;
#else
        aux->item[3].value = (size_t)process_header;
#endif
        aux->item[4].key = AT_PHNUM;
        aux->item[4].value = eheader.e_phnum;
        aux->item[5].key = AT_PHENT;
        aux->item[5].value = sizeof pheader;
#ifdef ARCH_MM_MMU
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, aux, sizeof *aux);
#endif
    }

    if (load_addr)
    {
        load_off = (size_t)load_addr;
    }
#ifdef ARCH_MM_MMU
    else
    {
        /* map user */
        off = eheader.e_shoff;
        for (i = 0; i < eheader.e_shnum; i++, off += sizeof sheader)
        {
            check_off(off, len);
            lseek(fd, off, SEEK_SET);
            read_len = load_fread(&sheader, 1, sizeof sheader, fd);
            check_read(read_len, sizeof sheader);

            if ((sheader.sh_flags & SHF_ALLOC) == 0)
            {
                continue;
            }

            switch (sheader.sh_type)
            {
            case SHT_PROGBITS:
                if ((sheader.sh_flags & SHF_WRITE) == 0)
                {
                    expand_map_range(&user_area[0], (void *)sheader.sh_addr, sheader.sh_size);
                }
                else
                {
                    expand_map_range(&user_area[1], (void *)sheader.sh_addr, sheader.sh_size);
                }
                break;
            case SHT_NOBITS:
                expand_map_range(&user_area[1], (void *)sheader.sh_addr, sheader.sh_size);
                break;
            default:
                expand_map_range(&user_area[1], (void *)sheader.sh_addr, sheader.sh_size);
                break;
            }
        }

        if (user_area[0].size == 0)
        {
            /* no code */
            result = -RT_ERROR;
            goto _exit;
        }

        if (user_area[0].start == NULL)
        {
            /* DYN */
            load_off = USER_LOAD_VADDR;
            user_area[0].start = (void *)((char*)user_area[0].start + load_off);
            user_area[1].start = (void *)((char*)user_area[1].start + load_off);
        }

        if (map_range_ckeck(&user_area[0], &user_area[1]) != 0)
        {
            result = -RT_ERROR;
            goto _exit;
        }

        /* text and data */
        for (i = 0; i < 2; i++)
        {
            if (user_area[i].size != 0)
            {
                va = lwp_map_user(lwp, user_area[i].start, user_area[i].size, (i == 0));
                if (!va || (va != user_area[i].start))
                {
                    result = -RT_ERROR;
                    goto _exit;
                }
            }
        }
        lwp->text_size = user_area[0].size;
    }
#else
    else
    {
        size_t start = -1UL;
        size_t end = 0UL;
        size_t total_size;

        off = eheader.e_shoff;
        for (i = 0; i < eheader.e_shnum; i++, off += sizeof sheader)
        {
            check_off(off, len);
            lseek(fd, off, SEEK_SET);
            read_len = load_fread(&sheader, 1, sizeof sheader, fd);
            check_read(read_len, sizeof sheader);

            if ((sheader.sh_flags & SHF_ALLOC) == 0)
            {
                continue;
            }

            switch (sheader.sh_type)
            {
            case SHT_PROGBITS:
            case SHT_NOBITS:
                if (start > sheader.sh_addr)
                {
                    start = sheader.sh_addr;
                }
                if (sheader.sh_addr + sheader.sh_size > end)
                {
                    end = sheader.sh_addr + sheader.sh_size;
                }
                break;
            default:
                break;
            }
        }

        total_size = end - start;

#ifdef RT_USING_CACHE
        load_off = (size_t)rt_malloc_align(total_size, RT_CPU_CACHE_LINE_SZ);
#else
        load_off = (size_t)rt_malloc(total_size);
#endif
        if (load_off == 0)
        {
            LOG_E("alloc text memory faild!");
            result = -RT_ENOMEM;
            goto _exit;
        }
        else
        {
            LOG_D("lwp text malloc : %p, size: %d!", (void *)load_off, lwp->text_size);
        }
        lwp->load_off = load_off; /* for free */
        lwp->text_size = total_size;
    }
#endif
    lwp->text_entry = (void *)(eheader.e_entry + load_off);

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
                LOG_E("pheader.p_filesz > pheader.p_memsz, p_filesz:0x%x;p_memsz:0x%x!", pheader.p_filesz, pheader.p_memsz);
                return -RT_ERROR;
            }

            check_off(pheader.p_offset, len);
            lseek(fd, pheader.p_offset, SEEK_SET);
#ifdef ARCH_MM_MMU
            {
                uint32_t size = pheader.p_filesz;
                size_t tmp_len = 0;

                va = (void *)(pheader.p_vaddr + load_addr);
                read_len = 0;
                while (size)
                {
                    pa = lwp_v2p(lwp, va);
                    va_self = (void *)((char *)pa - PV_OFFSET);
                    LOG_D("va_self = %p pa = %p", va_self, pa);
                    tmp_len = (size < ARCH_PAGE_SIZE) ? size : ARCH_PAGE_SIZE;
                    tmp_len = load_fread(va_self, 1, tmp_len, fd);
                    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, va_self, tmp_len);
                    read_len += tmp_len;
                    size -= tmp_len;
                    va = (void *)((char *)va + ARCH_PAGE_SIZE);
                }
            }
#else
            read_len = load_fread((void*)(pheader.p_vaddr + load_off), 1, pheader.p_filesz, fd);
#endif
            check_read(read_len, pheader.p_filesz);

            if (pheader.p_filesz < pheader.p_memsz)
            {
#ifdef ARCH_MM_MMU
                uint32_t size = pheader.p_memsz - pheader.p_filesz;
                uint32_t size_s;
                uint32_t off;

                off = pheader.p_filesz & ARCH_PAGE_MASK;
                va = (void *)((pheader.p_vaddr + pheader.p_filesz + load_off) & ~ARCH_PAGE_MASK);
                while (size)
                {
                    size_s = (size < ARCH_PAGE_SIZE - off) ? size : ARCH_PAGE_SIZE - off;
                    pa = lwp_v2p(lwp, va);
                    va_self = (void *)((char *)pa - PV_OFFSET);
                    memset((void *)((char *)va_self + off), 0, size_s);
                    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)((char *)va_self + off), size_s);
                    off = 0;
                    size -= size_s;
                    va = (void *)((char *)va + ARCH_PAGE_SIZE);
                }
#else
                memset((uint8_t *)pheader.p_vaddr + pheader.p_filesz + load_off, 0, (size_t)(pheader.p_memsz - pheader.p_filesz));
#endif
            }
        }
    }

    /* relocate */
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

            if (strcmp(p_section_str + sheader.sh_name, ".got") == 0)
            {
                got_start = (void *)((uint8_t *)sheader.sh_addr + load_off);
                got_size = (size_t)sheader.sh_size;
            }
            else if (strcmp(p_section_str + sheader.sh_name, ".rel.dyn") == 0)
            {
                rel_dyn_start = (void *)((uint8_t *)sheader.sh_addr + load_off);
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
#ifdef ARCH_MM_MMU
        arch_elf_reloc(lwp->aspace, (void *)load_off, rel_dyn_start, rel_dyn_size, got_start, got_size, dynsym);
#else
        arch_elf_reloc((void *)load_off, rel_dyn_start, rel_dyn_size, got_start, got_size, dynsym);

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
        LOG_E("lwp load faild, %d", result);
    }
    return result;
}
#endif /* ARCH_MM_MMU */

rt_weak int lwp_load(const char *filename, struct rt_lwp *lwp, uint8_t *load_addr, size_t addr_size, struct process_aux *aux)
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
    if ((ret != RT_EOK) && (ret != 1))
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

/* lwp-thread clean up routine */
void lwp_cleanup(struct rt_thread *tid)
{
    struct rt_lwp *lwp;

    if (tid == NULL)
    {
        LOG_I("%s: invalid parameter tid == NULL", __func__);
        return;
    }
    else
        LOG_D("cleanup thread: %s, stack_addr: 0x%x", tid->parent.name, tid->stack_addr);

    /**
     * Brief: lwp thread cleanup
     *
     * Note: Critical Section
     * - thread control block (RW. It's ensured that no one else can access tcb
     *   other than itself)
     */
    lwp = (struct rt_lwp *)tid->lwp;
    lwp_thread_signal_detach(&tid->signal);

    /* tty will be release in lwp_ref_dec() if ref is cleared */
    lwp_ref_dec(lwp);
    return;
}

static void lwp_execve_setup_stdio(struct rt_lwp *lwp)
{
    struct dfs_fdtable *lwp_fdt;
    struct dfs_file *cons_file;
    int cons_fd;

    lwp_fdt = &lwp->fdt;

    /* open console */
    cons_fd = open("/dev/console", O_RDWR);
    if (cons_fd < 0)
    {
        LOG_E("%s: Cannot open console tty", __func__);
        return ;
    }
    LOG_D("%s: open console as fd %d", __func__, cons_fd);

    /* init 4 fds */
    lwp_fdt->fds = rt_calloc(4, sizeof(void *));
    if (lwp_fdt->fds)
    {
        cons_file = fd_get(cons_fd);
        lwp_fdt->maxfd = 4;
        fdt_fd_associate_file(lwp_fdt, 0, cons_file);
        fdt_fd_associate_file(lwp_fdt, 1, cons_file);
        fdt_fd_associate_file(lwp_fdt, 2, cons_file);
    }

    close(cons_fd);
    return;
}

static void _lwp_thread_entry(void *parameter)
{
    rt_thread_t tid;
    struct rt_lwp *lwp;

    tid = rt_thread_self();
    lwp = (struct rt_lwp *)tid->lwp;
    tid->cleanup = lwp_cleanup;
    tid->user_stack = RT_NULL;

    if (lwp->debug)
    {
        lwp->bak_first_inst = *(uint32_t *)lwp->text_entry;
        *(uint32_t *)lwp->text_entry = dbg_get_ins();
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, lwp->text_entry, sizeof(uint32_t));
        icache_invalid_all();
    }

    /**
     * without ASID support, it will be a special case when trying to run application
     * and exit multiple times and a same page frame allocated to it bound to
     * different text segment. Then we are in a situation where icache contains
     * out-of-dated data and must be handle by the running core itself.
     * with ASID support, this should be a rare case that ASID & page frame both
     * identical to previous running application.
     *
     * For a new application loaded into memory, icache are seen as empty. And there
     * should be nothing in the icache entry to match. So this icache invalidation
     * operation should have barely influence.
     */
    rt_hw_icache_invalidate_all();

#ifdef ARCH_MM_MMU
    arch_start_umode(lwp->args, lwp->text_entry, (void *)USER_STACK_VEND, (char *)tid->stack_addr + tid->stack_size);
#else
    arch_start_umode(lwp->args, lwp->text_entry, lwp->data_entry, (void *)((uint32_t)lwp->data_entry + lwp->data_size));
#endif /* ARCH_MM_MMU */
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

rt_err_t lwp_children_register(struct rt_lwp *parent, struct rt_lwp *child)
{
    /* lwp add to children link */
    LWP_LOCK(parent);
    child->sibling = parent->first_child;
    parent->first_child = child;
    child->parent = parent;
    LWP_UNLOCK(parent);

    LOG_D("%s(parent=%p, child=%p)", __func__, parent, child);
    /* parent holds reference to child */
    lwp_ref_inc(parent);
    /* child holds reference to parent */
    lwp_ref_inc(child);

    return 0;
}

rt_err_t lwp_children_unregister(struct rt_lwp *parent, struct rt_lwp *child)
{
    struct rt_lwp **lwp_node;

    LWP_LOCK(parent);
    /* detach from children link */
    lwp_node = &parent->first_child;
    while (*lwp_node != child)
    {
        RT_ASSERT(*lwp_node != RT_NULL);
        lwp_node = &(*lwp_node)->sibling;
    }
    (*lwp_node) = child->sibling;
    child->parent = RT_NULL;
    LWP_UNLOCK(parent);

    LOG_D("%s(parent=%p, child=%p)", __func__, parent, child);
    lwp_ref_dec(child);
    lwp_ref_dec(parent);

    return 0;
}

pid_t lwp_execve(char *filename, int debug, int argc, char **argv, char **envp)
{
    int result;
    struct rt_lwp *lwp;
    char *thread_name;
    struct process_aux *aux;
    int tid = 0;

    if (filename == RT_NULL)
    {
        return -EINVAL;
    }

    if (access(filename, X_OK) != 0)
    {
        return -EACCES;
    }

    lwp = lwp_create(LWP_CREATE_FLAG_ALLOC_PID | LWP_CREATE_FLAG_NOTRACE_EXEC);

    if (lwp == RT_NULL)
    {
        dbg_log(DBG_ERROR, "lwp struct out of memory!\n");
        return -ENOMEM;
    }
    LOG_D("lwp malloc : %p, size: %d!", lwp, sizeof(struct rt_lwp));

    if ((tid = lwp_tid_get()) == 0)
    {
        lwp_ref_dec(lwp);
        return -ENOMEM;
    }
#ifdef ARCH_MM_MMU
    if (lwp_user_space_init(lwp, 0) != 0)
    {
        lwp_tid_put(tid);
        lwp_ref_dec(lwp);
        return -ENOMEM;
    }
#endif

    if ((aux = lwp_argscopy(lwp, argc, argv, envp)) == RT_NULL)
    {
        lwp_tid_put(tid);
        lwp_ref_dec(lwp);
        return -ENOMEM;
    }

    result = lwp_load(filename, lwp, RT_NULL, 0, aux);
#ifdef ARCH_MM_MMU
    if (result == 1)
    {
        /* dynmaic */
        lwp_unmap_user(lwp, (void *)(USER_VADDR_TOP - ARCH_PAGE_SIZE));
        result = load_ldso(lwp, filename, argv, envp);
    }
#endif /* ARCH_MM_MMU */
    if (result == RT_EOK)
    {
        rt_thread_t thread = RT_NULL;
        rt_uint32_t priority = 25, tick = 200;

        lwp_execve_setup_stdio(lwp);

        /* obtain the base name */
        thread_name = strrchr(filename, '/');
        thread_name = thread_name ? thread_name + 1 : filename;
#ifndef ARCH_MM_MMU
        struct lwp_app_head *app_head = lwp->text_entry;
        if (app_head->priority)
        {
            priority = app_head->priority;
        }
        if (app_head->tick)
        {
            tick = app_head->tick;
        }
#endif /* not defined ARCH_MM_MMU */
        thread = rt_thread_create(thread_name, _lwp_thread_entry, RT_NULL,
                LWP_TASK_STACK_SIZE, priority, tick);
        if (thread != RT_NULL)
        {
            struct rt_lwp *self_lwp;
            rt_session_t session;
            rt_processgroup_t group;

            thread->tid = tid;
            lwp_tid_set_thread(tid, thread);
            LOG_D("lwp kernel => (0x%08x, 0x%08x)\n", (rt_size_t)thread->stack_addr,
                    (rt_size_t)thread->stack_addr + thread->stack_size);
            self_lwp = lwp_self();

            /* when create init, self_lwp == null */
            if (self_lwp == RT_NULL && lwp_to_pid(lwp) != 1)
            {
                self_lwp = lwp_from_pid_and_lock(1);
            }

            if (self_lwp)
            {
                /* lwp add to children link */
                lwp_children_register(self_lwp, lwp);
            }

            session = RT_NULL;
            group = RT_NULL;

            group = lwp_pgrp_create(lwp);
            if (group)
            {
                lwp_pgrp_insert(group, lwp);
                if (self_lwp == RT_NULL)
                {
                    session = lwp_session_create(lwp);
                    lwp_session_insert(session, group);
                }
                else
                {
                    session = lwp_session_find(lwp_sid_get_byprocess(self_lwp));
                    lwp_session_insert(session, group);
                }
            }

            thread->lwp = lwp;
#ifndef ARCH_MM_MMU
            struct lwp_app_head *app_head = (struct lwp_app_head*)lwp->text_entry;
            thread->user_stack = app_head->stack_offset ?
                              (void *)(app_head->stack_offset -
                                       app_head->data_offset +
                                       (uint32_t)lwp->data_entry) : RT_NULL;
            thread->user_stack_size = app_head->stack_size;
            /* init data area */
            rt_memset(lwp->data_entry, 0, lwp->data_size);
            /* init user stack */
            rt_memset(thread->user_stack, '#', thread->user_stack_size);
#endif /* not defined ARCH_MM_MMU */
            rt_list_insert_after(&lwp->t_grp, &thread->sibling);

            lwp->did_exec = RT_TRUE;

            if (debug && rt_dbg_ops)
            {
                lwp->debug = debug;
                rt_thread_control(thread, RT_THREAD_CTRL_BIND_CPU, (void*)0);
            }

            rt_thread_startup(thread);
            return lwp_to_pid(lwp);
        }
    }

    lwp_tid_put(tid);
    lwp_ref_dec(lwp);

    return -RT_ERROR;
}

#ifdef RT_USING_MUSLLIBC
extern char **__environ;
#else
char **__environ = 0;
#endif

pid_t exec(char *filename, int debug, int argc, char **argv)
{
    setenv("OS", "RT-Thread", 1);
    return lwp_execve(filename, debug, argc, argv, __environ);
}

#ifdef ARCH_MM_MMU
void lwp_user_setting_save(rt_thread_t thread)
{
    if (thread)
    {
        thread->thread_idr = arch_get_tidr();
    }
}

void lwp_user_setting_restore(rt_thread_t thread)
{
    if (!thread)
    {
        return;
    }
#if !defined(ARCH_RISCV64)
    /* tidr will be set in RESTORE_ALL in risc-v */
    arch_set_tidr(thread->thread_idr);
#endif

    if (rt_dbg_ops)
    {
        struct rt_lwp *l = (struct rt_lwp *)thread->lwp;

        if (l != 0)
        {
            rt_hw_set_process_id((size_t)l->pid);
        }
        else
        {
            rt_hw_set_process_id(0);
        }
        if (l && l->debug)
        {
            uint32_t step_type = 0;

            step_type = dbg_step_type();

            if ((step_type == 2) || (thread->step_exec && (step_type == 1)))
            {
                dbg_activate_step();
            }
            else
            {
                dbg_deactivate_step();
            }
        }
    }
}
#endif /* ARCH_MM_MMU */

void lwp_uthread_ctx_save(void *ctx)
{
    rt_thread_t thread;
    thread = rt_thread_self();
    thread->user_ctx.ctx = ctx;
}

void lwp_uthread_ctx_restore(void)
{
    rt_thread_t thread;
    thread = rt_thread_self();
    thread->user_ctx.ctx = RT_NULL;
}

rt_err_t lwp_backtrace_frame(rt_thread_t uthread, struct rt_hw_backtrace_frame *frame)
{
    rt_err_t rc = -RT_ERROR;
    long nesting = 0;
    char **argv;
    rt_lwp_t lwp;

    if (uthread && uthread->lwp && rt_scheduler_is_available())
    {
        lwp = uthread->lwp;
        argv = lwp_get_command_line_args(lwp);
        if (argv)
        {
            rt_kprintf("please use: addr2line -e %s -a -f", argv[0]);
            lwp_free_command_line_args(argv);
        }
        else
        {
            rt_kprintf("please use: addr2line -e %s -a -f", lwp->cmd);
        }

        while (nesting < RT_BACKTRACE_LEVEL_MAX_NR)
        {
            rt_kprintf(" 0x%lx", frame->pc);
            if (rt_hw_backtrace_frame_unwind(uthread, frame))
            {
                break;
            }
            nesting++;
        }
        rt_kprintf("\n");
        rc = RT_EOK;
    }
    return rc;
}

void rt_update_process_times(void)
{
    struct rt_thread *thread;
#ifdef RT_USING_SMP
    struct rt_cpu* pcpu;

    pcpu = rt_cpu_self();
#endif

    thread = rt_thread_self();

    if (!IS_USER_MODE(thread))
    {
        thread->user_time += 1;
#ifdef RT_USING_SMP
        pcpu->cpu_stat.user += 1;
#endif
    }
    else
    {
        thread->system_time += 1;
#ifdef RT_USING_SMP
        if (thread == pcpu->idle_thread)
        {
            pcpu->cpu_stat.idle += 1;
        }
        else
        {
            pcpu->cpu_stat.system += 1;
        }
#endif
    }
}
