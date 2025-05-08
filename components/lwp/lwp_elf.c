/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-08-23     zhangsz      first version
 */

#include <rtthread.h>

#ifdef RT_USING_LDSO

#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <lwp_elf.h>

#include "lwp.h"
#include "lwp_arch.h"

#ifdef ARCH_MM_MMU
#include <lwp_user_mm.h>
#endif

#ifdef RT_USING_VDSO
#include <vdso.h>
#endif

#define DBG_TAG "load.elf"
#ifdef ELF_DEBUG_ENABLE
#define DBG_LVL DBG_LOG
#else
#define DBG_LVL DBG_INFO
#endif
#include <rtdbg.h>

#define ELF_INVALID_FD -1
#define ELF_PHDR_NUM_MAX 128
#define FILE_LENGTH_MAX 0xC0000000
#define MEM_SIZE_MAX 0xC0000000
#define ELF_PATH_MAX 256
#define FLF_PATH_MIN 1

#define ELF_PAGESTART(_v) ((_v) & ~(rt_ubase_t)(ARCH_PAGE_SIZE - 1))
#define ELF_PAGEOFFSET(_v) ((_v) & (ARCH_PAGE_SIZE - 1))
#define ELF_PAGEALIGN(_v) (((_v) + ARCH_PAGE_SIZE - 1) & ~(ARCH_PAGE_SIZE - 1))

#define ELF_EXEC_LOAD_ADDR  USER_VADDR_START
#define ELF_INTERP_LOAD_ADDR LDSO_LOAD_VADDR

#define ELF_AUX_ENT(aux, id, val)                           \
    do                                                      \
    {                                                       \
        rt_base_t a = id;                                   \
        lwp_data_put(lwp, aux++, &a, sizeof(rt_ubase_t));   \
        a = val;                                            \
        lwp_data_put(lwp, aux++, &a, sizeof(rt_ubase_t));   \
    } while (0)

/**
 * @brief Structure to hold information about an ELF file.
 *
 */
typedef struct
{
    int fd;                      /* File descriptor for the ELF file */
    char *filename;              /* Path to the ELF file */
    rt_size_t file_len;          /* Length of the ELF file */
    Elf_Ehdr ehdr;               /* ELF header */
    Elf_Phdr *phdr;              /* Pointer to the program header table */
    rt_ubase_t map_size;         /* Total size required for memory mapping */
} elf_info_t;

/**
 * @brief Structure to hold information about an ELF executable and its interpreter.
 */
typedef struct
{
    struct rt_lwp *lwp;             /* Pointer to the Light Weight Process (LWP) structure */
    struct process_aux *aux;        /* Pointer to auxiliary process information */
    elf_info_t exec_info;           /* Information about the main ELF executable */
    elf_info_t interp_info;         /* Information about the ELF interpreter (if any) */
    rt_ubase_t load_addr;           /* Base address where the ELF is loaded */
    rt_ubase_t e_entry;             /* Entry point address of the ELF */
    rt_ubase_t interp_base;         /* Base address of the interpreter */
} elf_load_info_t;

/**
 * @brief Dump the contents of a user-space memory region for debugging.
 *
 * This function reads and prints the contents of a specified user-space memory region
 * in hexadecimal format. It is primarily used for debugging ELF loading and execution.
 *
 * @param lwp Pointer to the Light Weight Process (LWP) structure.
 * @param va Virtual address of the memory region to dump.
 * @param len Length of the memory region to dump.
 */
static void elf_user_dump(struct rt_lwp *lwp, void *va, size_t len)
{
#ifdef ELF_DEBUG_DUMP
    uint8_t *k_va;
    int ret;

    if (len < 16)
        len = 16;
    rt_kprintf("\r\n");
    rt_kprintf("%s : user va : %p, len : 0x%x(%d)\n", __func__, va, len, len);
    k_va = rt_malloc(len);
    if (k_va == RT_NULL)
    {
        rt_kprintf("%s : malloc failed\n", __func__);
        return;
    }
    rt_memset(k_va, 0, len);

    ret = lwp_data_get(lwp, k_va, va, len);
    if (ret != len)
    {
        rt_kprintf("%s : lwp_get_from_user failed, ret = %d\n", __func__, ret);
        return;
    }

    rt_kprintf("%s : k_va : %p\n", __func__, k_va);

    for (size_t i = 0; i < len; i += 16)
    {
        rt_kprintf("  %02x %02x %02x %02x %02x %02x %02x %02x ", k_va[i], k_va[i+1], k_va[i+2], k_va[i+3],
            k_va[i+4], k_va[i+5], k_va[i+6], k_va[i+7]);
        rt_kprintf("  %02x %02x %02x %02x %02x %02x %02x %02x \n", k_va[i+8], k_va[i+9], k_va[i+10], k_va[i+11],
            k_va[i+12], k_va[i+13], k_va[i+14], k_va[i+15]);
    }
    rt_kprintf("\r\n");
    rt_free(k_va);
#endif
}

/**
 * @brief Generate a random offset for ELF loading.
 *
 * @return Random offset aligned to page size.
 */
rt_ubase_t elf_random_offset(void)
{
#ifdef ELF_LOAD_RANDOMIZE
    return (rt_tick_get() % 65535) * ARCH_PAGE_SIZE;
#else
    return ELF_PAGEALIGN(0);
#endif
}

/**
 * @brief Map a file into the process's address space.
 *
 * This function maps a file into the process's virtual memory using the specified
 * address, size, protection flags, and offset. It ensures the mapping is properly
 * aligned and verifies the mapping operation.
 *
 * @param lwp Pointer to the Light Weight Process (LWP) structure.
 * @param fd File descriptor of the file to map.
 * @param load_addr Desired virtual address for mapping.
 * @param map_size Size of the memory mapping.
 * @param prot Memory protection flags (e.g., PROT_READ, PROT_WRITE).
 * @param flags Mapping flags (e.g., MAP_FIXED, MAP_PRIVATE).
 * @param offset File offset where mapping should begin.
 *
 * @return Virtual address where the file is mapped on success, NULL on failure.
 */
static void *file_mmap(struct rt_lwp *lwp, int fd, rt_ubase_t load_addr,
        rt_ubase_t map_size, size_t prot, size_t flags, rt_ubase_t offset)
{
    uint8_t *map_va;

    map_va = (uint8_t *)lwp_mmap2(lwp, (void *)load_addr, map_size, prot, flags, fd, offset >> ARCH_PAGE_SHIFT);
    if (!map_va || (map_va != (uint8_t *)load_addr))
    {
        LOG_E("%s : lwp map user failed!", __func__);
        return RT_NULL;
    }
    LOG_D("  %s : map va = %p load_addr : %p size : 0x%x", __func__, map_va, load_addr, map_size);

    return map_va;
}

static int elf_file_open(const char *filename)
{
    int fd = -1;

    fd = open(filename, O_BINARY | O_RDONLY, 0);
    if (fd < 0)
    {
        LOG_E("%s : elf file [%s] open failed!", __func__, filename);
    }

    return fd;
}

static int elf_file_close(int fd)
{
    return close(fd);
}

/**
 * @brief Get the length of an ELF file.
 *
 * @param filename Path to the ELF file.
 * @param file_len Pointer to store the file length.
 * @return RT_EOK on success, -RT_ERROR on failure.
 */
static int elf_file_length(char *filename, rt_size_t *file_len)
{
    int ret;
    struct stat s = { 0 };

    ret = stat(filename, &s);
    if (ret != 0)
    {
        LOG_E("%s : error", __func__);
        return -RT_ERROR;
    }
    *file_len = (rt_size_t)s.st_size;

    return RT_EOK;
}

/**
 * @brief Read data from an ELF file at a specific offset.
 *
 * @param fd File descriptor of the ELF file.
 * @param buffer Pointer to the buffer where the read data will be stored.
 * @param size Number of bytes to read.
 * @param offset File offset where reading should begin.
 * @return RT_EOK on success, -RT_ERROR if seek or read operations fail.
 */
static int elf_file_read(rt_int32_t fd, rt_uint8_t *buffer, size_t size, off_t offset)
{
    ssize_t read_len;
    off_t pos;

    if (size > 0)
    {
        pos = lseek(fd, offset, SEEK_SET);
        if (pos != offset)
        {
            LOG_E("%s : seek file offset: 0x%x failed", __func__, offset);
            return -RT_ERROR;
        }

        read_len = read(fd, buffer, size);
        if (read_len != size)
        {
            LOG_E("%s : read from offset: 0x%x error", __func__, offset);
            return -RT_ERROR;
        }
    }

    return RT_EOK;
}

/**
 * @brief Validate an ELF header.
 *
 * @param ehdr Pointer to the ELF header to validate.
 * @param file_len Length of the ELF file.
 * @return RT_EOK if valid, -RT_ERROR if invalid.
 */
static rt_int32_t elf_check_ehdr(const Elf_Ehdr *ehdr, rt_uint32_t file_len)
{
    if (memcmp(ehdr->e_ident, ELFMAG, SELFMAG) != 0)
    {
        LOG_E("%s : e_ident error", __func__);
        return -RT_ERROR;
    }

    if ((ehdr->e_type != ET_EXEC) && (ehdr->e_type != ET_DYN))
    {
        LOG_E("%s : e_type error", __func__);
        return -RT_ERROR;
    }

    if (ehdr->e_machine == EM_NONE)
    {
        LOG_E("%s : e_machine is EM_NONE", __func__);
        return -RT_ERROR;
    }

    if (ehdr->e_phnum > ELF_PHDR_NUM_MAX)
    {
        LOG_E("%s : e_phnum error", __func__);
        return -RT_ERROR;
    }

    if (ehdr->e_phoff > file_len)
    {
        LOG_E("%s : e_phoff error", __func__);
        return -RT_ERROR;
    }

    LOG_D("%s : e_entry : 0x%x", __func__, ehdr->e_entry);

    return RT_EOK;
}

/**
 * @brief Validate an ELF program header.
 *
 * @param phdr Pointer to the ELF program header to validate.
 * @return RT_EOK if valid, -RT_ERROR if invalid.
 */
static int elf_check_phdr(const Elf_Phdr *phdr)
{
    if (phdr->p_filesz > FILE_LENGTH_MAX)
    {
        LOG_E("%s : phdr p_filesz 0x%x error", __func__, phdr->p_filesz);
        return -RT_ERROR;
    }

    if (phdr->p_offset > FILE_LENGTH_MAX)
    {
        LOG_E("%s : phdr p_offset 0x%x error", __func__, phdr->p_offset);
        return -RT_ERROR;
    }

    if (phdr->p_memsz > MEM_SIZE_MAX)
    {
        LOG_E("%s[%d], phdr p_memsz 0x%x error", __func__, phdr->p_memsz);
        return -RT_ERROR;
    }

    LOG_D("%s : phdr p_vaddr : 0x%x", __func__, phdr->p_vaddr);

    return RT_EOK;
}

/**
 * @brief Load and validate the ELF header from a file.
 *
 * This function opens the ELF file, reads its  elf header, and performs basic validation
 * to ensure it's a valid ELF file. It also retrieves the file size and stores the
 * file descriptor for subsequent operations.
 *
 * @param elf_info Pointer to the ELF file information structure.
 * @return RT_EOK on success, -RT_ERROR on failure.
 */
static int elf_load_ehdr(elf_info_t *elf_info)
{
    int ret;

    ret = elf_file_open(elf_info->filename);
    if (ret < 0)
    {
        LOG_E("%s : elf_file_open %s failed", __func__, elf_info->filename);
        return ret;
    }

    elf_info->fd = ret;

    ret = elf_file_length(elf_info->filename, &elf_info->file_len);
    if (ret != RT_EOK)
    {
        return -RT_ERROR;
    }

    ret = elf_file_read(elf_info->fd, (rt_uint8_t *)&elf_info->ehdr, sizeof(Elf_Ehdr), 0);
    if (ret != RT_EOK)
    {
        LOG_E("%s : elf_file_read failed, ret : %d", __func__, ret);
        return -RT_ERROR;
    }

    ret = elf_check_ehdr(&elf_info->ehdr, elf_info->file_len);
    if (ret != RT_EOK)
    {
        LOG_E("%s : elf_check_ehdr failed, ret : %d", __func__, ret);
        return -RT_ERROR;
    }

    return RT_EOK;
}

/**
 * @brief Load the program header table from an ELF file.
 *
 * This function reads and validates the program header table from the ELF file.
 * It ensures the program header table is properly aligned and within the file bounds.
 *
 * @param elf_info Pointer to the ELF file information structure.
 * @return RT_EOK on success, -RT_ERROR on failure.
 */
static int elf_load_phdr(elf_info_t *elf_info)
{
    Elf_Ehdr *ehdr = &elf_info->ehdr;
    uint32_t size;
    int ret;

    if (ehdr->e_phnum < 1)
    {
        return -RT_ERROR;
    }

    if (ehdr->e_phentsize != sizeof(Elf_Phdr))
    {
        return -RT_ERROR;
    }

    size = sizeof(Elf_Phdr) * ehdr->e_phnum;
    if ((ehdr->e_phoff + size) > elf_info->file_len)
    {
        return -RT_ERROR;
    }

    elf_info->phdr = rt_malloc(size);
    if (elf_info->phdr == RT_NULL)
    {
        LOG_E("%s : alloc phdr failed", __func__);
        return -RT_ENOMEM;
    }

    ret = elf_file_read(elf_info->fd, (rt_uint8_t *)elf_info->phdr, size, ehdr->e_phoff);
    if (ret != RT_EOK)
    {
        rt_free(elf_info->phdr);
        elf_info->phdr = RT_NULL;
        LOG_E("%s : elf_file_read failed, ret = %d", __func__, ret);
        return -RT_ERROR;
    }

    return RT_EOK;
}

/**
 * @brief Load the ELF interpreter specified in the program header.
 *
 * This function searches for the PT_INTERP segment in the program headers,
 * validates its properties, and loads the interpreter's filename and
 * associated ELF information.
 *
 * @param load_info Pointer to the ELF loading context structure.
 * @return RT_EOK on success, -RT_ERROR on failure.
 */
static int elf_load_interp(elf_load_info_t *load_info)
{
    Elf_Phdr *phdr = load_info->exec_info.phdr;
    int ret;
    int i;

    for (i = 0; i < load_info->exec_info.ehdr.e_phnum; ++i, ++phdr)
    {
        if (phdr->p_type != PT_INTERP)
        {
            continue;
        }

        if (elf_check_phdr(phdr) != RT_EOK)
        {
            return -RT_ERROR;
        }

        if ((phdr->p_filesz > ELF_PATH_MAX) || (phdr->p_filesz < FLF_PATH_MIN))
        {
            LOG_E("%s : phdr p_filesz error", __func__, phdr->p_filesz);
            return -RT_ERROR;
        }

        if (phdr->p_offset + phdr->p_filesz > load_info->exec_info.file_len)
        {
            LOG_E("%s : phdr p_offset error", __func__, phdr->p_offset);
            return -RT_ERROR;
        }

        load_info->interp_info.filename = rt_malloc(phdr->p_filesz);
        if (load_info->interp_info.filename == RT_NULL)
        {
            LOG_E("%s : alloc elf interpreter failed", __func__);
            return -RT_ENOMEM;
        }

        ret = elf_file_read(load_info->exec_info.fd, (rt_uint8_t *)load_info->interp_info.filename,
            phdr->p_filesz, phdr->p_offset);
        if (ret != RT_EOK)
        {
            LOG_E("%s : elf_file_read failed, ret = %d", __func__, ret);
            ret = -RT_ERROR;
            goto error_exit;
        }

        if (load_info->interp_info.filename[phdr->p_filesz - 1] != '\0')
        {
            LOG_E("%s : elf interpreter is invalid", __func__);
            ret = -RT_ERROR;
            goto error_exit;
        }

        LOG_D("%s : elf interpreter : %s", __func__, load_info->interp_info.filename);

        ret = elf_load_ehdr(&load_info->interp_info);
        if (ret != RT_EOK)
        {
            LOG_E("%s : elf_load_ehdr failed, ret = %d", __func__, ret);
            goto error_exit;
        }

        ret = elf_load_phdr(&load_info->interp_info);
        if (ret != RT_EOK)
        {
            LOG_E("%s : elf_load_phdr failed, ret = %d", __func__, ret);
            goto error_exit;
        }
        break;
    }

    return RT_EOK;

error_exit:
    return ret;
}

/**
 * @brief Calculate the total size required to map all loadable ELF segments.
 *
 * @param elf_info Pointer to the ELF file information structure.
 * @return 0 on success, -1 if no loadable segments are found.
 */
static int total_mapping_size(elf_info_t *elf_info)
{
    int i;
    int first_idx = -1;
    int last_idx = -1;

    for (i = 0; i < elf_info->ehdr.e_phnum; i++)
    {
        if (elf_info->phdr[i].p_type == PT_LOAD)
        {
            last_idx = i;
            if (first_idx == -1)
                first_idx = i;
        }
    }

    if (first_idx == -1)
        return -1;

    elf_info->map_size = elf_info->phdr[last_idx].p_vaddr + elf_info->phdr[last_idx].p_memsz -
        ELF_PAGESTART(elf_info->phdr[first_idx].p_vaddr);

    return 0;
}

/**
 * @brief Map an ELF segment into the process's address space.
 *
 * This function maps a specific ELF segment into the process's virtual memory space.
 * It handles page alignment, calculates the correct offset, and performs the actual
 * memory mapping operation.
 *
 * @param lwp Pointer to the Light Weight Process (LWP) structure.
 * @param elf_phdr Pointer to the ELF program header describing the segment.
 * @param fd File descriptor of the ELF file.
 * @param addr Desired virtual address for mapping.
 * @param prot Memory protection flags (e.g., PROT_READ, PROT_WRITE).
 * @param flags Mapping flags (e.g., MAP_FIXED, MAP_PRIVATE).
 * @param map_size Size of the memory mapping (0 for automatic calculation).
 *
 * @return Virtual address where the segment is mapped on success.
 * @return 0 on failure.
 */
static rt_ubase_t elf_map(struct rt_lwp *lwp, const Elf_Phdr *elf_phdr, int fd, rt_ubase_t addr, size_t prot, size_t flags, rt_ubase_t map_size)
{
    rt_ubase_t map_va = 0;
    rt_ubase_t va_offset;
    addr = ELF_PAGESTART(addr);
    va_offset = elf_phdr->p_offset - ELF_PAGEOFFSET(elf_phdr->p_vaddr);
    rt_ubase_t size;

    if (map_size != 0)
    {
        size = map_size;
    }
    else
    {
        size = elf_phdr->p_memsz + ELF_PAGEOFFSET(elf_phdr->p_vaddr);
        if (size == 0)
        {
            return addr;
        }
    }
    map_va = (rt_ubase_t)file_mmap(lwp, fd, addr, size, prot, flags, va_offset);

    return map_va;
}

static int elf_zero_bss(struct rt_lwp *lwp, int fd, const Elf_Phdr *phdr, rt_ubase_t bss_start,
    rt_ubase_t bss_end)
{
    lwp_data_set(lwp, (void *)bss_start, 0, bss_end - bss_start);

    return RT_EOK;
}

/**
 * @brief Map ELF segments into memory.
 *
 * This function maps the loadable segments of an ELF file into the process's address space.
 * It handles both executable and shared library files, manages BSS sections, and sets up
 * the load address and base address for dynamic libraries.
 *
 * @param load_info Pointer to the structure containing ELF loading context.
 * @param elf_info Pointer to the structure containing ELF file information.
 * @param elfload_addr Pointer to store the final load address of the ELF file.
 * @param map_size Size of the memory mapping (0 for automatic calculation).
 * @param load_base Base address for loading (used for position-independent code).
 *
 * @return RT_EOK on success.
 * @return -RT_ERROR if memory mapping fails.
 * @return -ENOMEM if memory allocation fails.
 */
static int elf_file_mmap(elf_load_info_t *load_info, elf_info_t *elf_info, rt_ubase_t *elfload_addr,
    rt_uint32_t map_size, rt_ubase_t *load_base)
{
    int ret, i;
    rt_ubase_t map_va, bss_start, bss_end;
    Elf_Ehdr *ehdr = &elf_info->ehdr; /* ELF header */
    Elf_Phdr *phdr = elf_info->phdr;  /* Program header array */
    const Elf_Phdr *tmp_phdr = phdr;  /* Current program header */
    int fd = elf_info->fd; /* File descriptor for ELF file */
    rt_ubase_t load_addr;  /* Calculated load address */
    size_t prot = PROT_READ | PROT_WRITE; /* Memory protection flags */
    size_t flags = MAP_FIXED | MAP_PRIVATE; /* Memory mapping flags */

    /* Iterate through all program headers */
    for (i = 0; i < ehdr->e_phnum; ++i, ++tmp_phdr)
    {
        /* Only process PT_LOAD segments (loadable segments) */
        if (tmp_phdr->p_type != PT_LOAD)
        {
            continue;
        }

        /* For executable files, validate the program header */
        if (ehdr->e_type == ET_EXEC)
        {
            if (elf_check_phdr(tmp_phdr) != RT_EOK)
            {
                LOG_E("%s : elf_check_phdr failed", __func__);
                return -RT_ERROR;
            }
        }

        load_addr = tmp_phdr->p_vaddr + *load_base;
        LOG_D("%s : p_vaddr : 0x%x, load_addr : 0x%x", __func__, tmp_phdr->p_vaddr, load_addr);

        /* When both the segment's virtual address and the load base are 0, the segment is loaded at any available
         address rather than a fixed one. This behavior is particularly useful for Position-Independent Code (PIC)
         or shared libraries. */
        if ((tmp_phdr->p_vaddr == 0) && (*load_base == 0))
        {
            flags &= ~MAP_FIXED;
        }

        /* Map the segment into memory */
        map_va = elf_map(load_info->lwp, tmp_phdr, fd, load_addr, prot, flags, map_size);
        if (!map_va)
        {
            LOG_E("%s : elf_map failed", __func__);
            return -ENOMEM;
        }

        map_size = 0;

        elf_user_dump(load_info->lwp, (void *)load_addr, 64);

        /* Handle BSS section (zero-initialized data) */
        if ((tmp_phdr->p_memsz > tmp_phdr->p_filesz) && (tmp_phdr->p_flags & PF_W))
        {
            bss_start = load_addr + tmp_phdr->p_filesz;
            bss_end = load_addr + tmp_phdr->p_memsz;
            ret = elf_zero_bss(load_info->lwp, fd, tmp_phdr, bss_start, bss_end);
            if (ret)
            {
                LOG_E("%s : elf_zero_bss error", __func__);
                return ret;
            }
        }

        if (*elfload_addr == 0)
        {
            *elfload_addr = map_va + ELF_PAGEOFFSET(tmp_phdr->p_vaddr);
            LOG_D("%s elf_load_addr : %p, vAddr : %p, load_base : %p, map_va : %p", __func__,
                *elfload_addr, tmp_phdr->p_vaddr, *load_base, map_va);
        }

        if ((*load_base == 0) && (ehdr->e_type == ET_DYN))
        {
            *load_base = map_va;
        }
    }

    return RT_EOK;
}

/**
 * @brief Load the ELF interpreter into memory.
 *
 * @param load_info Pointer to the ELF loading context.
 * @param interp_base Pointer to store the interpreter's base address.
 *
 * @return RT_EOK on success, -RT_ERROR on failure.
 */
static int load_elf_interp(elf_load_info_t *load_info, rt_ubase_t *interp_base)
{
    int ret;
    rt_ubase_t load_base = ELF_INTERP_LOAD_ADDR + elf_random_offset();

    ret = total_mapping_size(&load_info->interp_info);
    if (ret)
    {
        LOG_E("%s : total_mapping_size failed", __func__);
        return -RT_ERROR;
    }
    LOG_D("%s : total_mapping_size 0x%x", __func__, load_info->interp_info.map_size);

    return elf_file_mmap(load_info, &load_info->interp_info, interp_base,
        load_info->interp_info.map_size, &load_base);
}

/**
 * @brief Populate the auxiliary vector for an ELF-loaded process.
 *
 * This function sets up the auxiliary vector that provides essential information
 * to the ELF executable about the runtime environment. It includes information
 * about page size, program headers, entry point, and other system-specific details.
 *
 * @param load_info Pointer to the structure containing ELF loading information.
 *
 * @return 0 on success, -1 if the auxiliary structure is invalid, or -RT_ERROR
 *         if memory mapping fails.
 *
 * @note The auxiliary vector is crucial for proper initialization of the ELF
 *       executable and its interaction with the runtime environment.
 */
static int elf_aux_fill(elf_load_info_t *load_info)
{
    uint8_t *random;
    struct process_aux *aux = load_info->aux;
    elf_addr_t *aux_info;
    uint32_t random_value = rt_tick_get();
    size_t prot = PROT_READ | PROT_WRITE;
    size_t flags = MAP_FIXED | MAP_PRIVATE;
    rt_lwp_t lwp = load_info->lwp;
    void *va;

    if (!aux)
    {
        LOG_E("%s : aux is null", __func__);
        return -1;
    }
    aux_info = (elf_addr_t *)aux->item;
    ELF_AUX_ENT(aux_info, AT_PAGESZ, ARCH_PAGE_SIZE);

    va = lwp_mmap2(lwp, (void *)(USER_VADDR_TOP - ARCH_PAGE_SIZE * 2), ARCH_PAGE_SIZE, prot, flags, -1, 0);
    if (!va)
    {
        LOG_E("lwp map user failed!");
        return -RT_ERROR;
    }
    random = (uint8_t *)(USER_VADDR_TOP - ARCH_PAGE_SIZE - sizeof(char[16]));
    lwp_data_put(load_info->lwp, random, &random_value, sizeof(random_value));
    ELF_AUX_ENT(aux_info, AT_RANDOM, (size_t)random);
    ELF_AUX_ENT(aux_info, AT_PHDR, (size_t)load_info->load_addr + load_info->exec_info.ehdr.e_phoff);
    ELF_AUX_ENT(aux_info, AT_PHNUM, (size_t)load_info->exec_info.ehdr.e_phnum);
    ELF_AUX_ENT(aux_info, AT_PHENT, sizeof(Elf_Phdr));
    ELF_AUX_ENT(aux_info, AT_BASE, load_info->interp_base);
    ELF_AUX_ENT(aux_info, AT_FLAGS, 0);
    ELF_AUX_ENT(aux_info, AT_ENTRY, load_info->exec_info.ehdr.e_entry);
    ELF_AUX_ENT(aux_info, AT_UID, 0);
    ELF_AUX_ENT(aux_info, AT_EUID, 0);
    ELF_AUX_ENT(aux_info, AT_GID, 0);
    ELF_AUX_ENT(aux_info, AT_EGID, 0);
    ELF_AUX_ENT(aux_info, AT_HWCAP, 0);
    ELF_AUX_ENT(aux_info, AT_CLKTCK, 0);
    ELF_AUX_ENT(aux_info, AT_SECURE, 0);

#ifdef RT_USING_VDSO
    if(RT_EOK == arch_setup_additional_pages(load_info->lwp))
    {
        ELF_AUX_ENT(aux_info, AT_SYSINFO_EHDR, (size_t)load_info->lwp->vdso_vbase);
    }
    else
    {
        LOG_W("vdso map error,VDSO currently only supports aarch64 architecture!");
    }
#endif

    return 0;
}

/**
 * @brief Load the segments of an ELF file into memory.
 *
 * This function is responsible for loading the segments of an ELF file into memory,
 * including handling dynamic libraries and setting up the entry point for execution.
 *
 * @param load_info Pointer to the structure containing ELF loading information.
 * @return RT_EOK if the segments are successfully loaded and prepared for execution.
 * @return -RT_ERROR if any error occurs during the loading process, including:
 *         - Memory allocation failure
 *         - File mapping errors
 *         - Interpreter loading errors
 */
static int elf_load_segment(elf_load_info_t *load_info)
{
    int ret;
    rt_ubase_t app_load_base = 0; /* Base address for loading the application. */
    load_info->load_addr = 0; /* Load address for the ELF file. */
    load_info->interp_base = 0; /* Base address for loading the interpreter. */
    load_info->exec_info.map_size = 0; /* Total size of the mapped segments. */

    if (load_info->exec_info.ehdr.e_type == ET_DYN)
    {
        ret = total_mapping_size(&load_info->exec_info);
        if (ret)
        {
            LOG_E("%s : total_mapping_size failed", __func__);
            return -RT_ERROR;
        }
        LOG_D("%s : map_size : 0x%x", __func__, load_info->exec_info.map_size);

        /* Calculate the base address for loading the ELF file by adding a random offset to the default load address.
           This randomization enhances security by making it harder for attackers to predict the memory layout. */
        app_load_base = ELF_EXEC_LOAD_ADDR + elf_random_offset();
    }

    /* Map the segments of the ELF file into memory */
    ret = elf_file_mmap(load_info, &load_info->exec_info, &load_info->load_addr,
        load_info->exec_info.map_size, &app_load_base);
    elf_file_close(load_info->exec_info.fd);
    if (ret != RT_EOK)
    {
        LOG_W("%s : elf_file_close exec failed", __func__);
    }
    load_info->exec_info.fd = ELF_INVALID_FD;

    if (load_info->interp_info.fd != ELF_INVALID_FD)
    {
        ret = load_elf_interp(load_info, &load_info->interp_base); /* load the interpreter */
        if (ret)
        {
            LOG_E("%s : load_elf_interp failed, ret = %d", __func__, ret);
            return ret;
        }
        elf_file_close(load_info->interp_info.fd);
        if (ret != RT_EOK)
        {
            LOG_W("%s : elf_file_close interp failed, ret = %d", __func__, ret);
        }
        load_info->interp_info.fd = ELF_INVALID_FD;

        /* if a interpreter exist, first jump to the interpreter's entry to handle dynamic libs' loading. */
        load_info->e_entry = load_info->interp_info.ehdr.e_entry + load_info->interp_base;
        load_info->exec_info.ehdr.e_entry = load_info->exec_info.ehdr.e_entry + app_load_base; /* Update the ELF file's entry address by adding the base address. */
    }
    else
    {
        /* If there is no interpreter, use the ELF file's entry address directly. */
        load_info->e_entry = load_info->exec_info.ehdr.e_entry;
    }

    load_info->lwp->text_entry = (void *)load_info->e_entry;
    LOG_D("%s : lwp->text_entry : %p loadaddr : %p", __func__, load_info->lwp->text_entry, app_load_base);

    /* Debug information: dump user space data. */
    elf_user_dump(load_info->lwp, load_info->lwp->text_entry, 64);

    /* Fill auxiliary information. */
    ret = elf_aux_fill(load_info);
    if (ret)
    {
        LOG_E("%s : elf_aux_fill failed", __func__);
        return ret;
    }

    return RT_EOK;
}

/**
 * @brief Clean up resources allocated during ELF loading.
 *
 * This function releases all resources (file descriptors, memory, etc.) that were
 * allocated during the ELF loading process. It ensures that no memory leaks occur
 * and all file descriptors are properly closed.
 *
 * @param load_info Pointer to the structure containing ELF loading information.
 */
static void elf_load_deinit(elf_load_info_t *load_info)
{
    if (load_info->exec_info.fd != ELF_INVALID_FD)
    {
        elf_file_close(load_info->exec_info.fd);
    }

    if (load_info->interp_info.fd != ELF_INVALID_FD)
    {
        elf_file_close(load_info->interp_info.fd);
    }

    if (load_info->exec_info.phdr != RT_NULL)
    {
        rt_free(load_info->exec_info.phdr);
    }

    if (load_info->exec_info.filename != RT_NULL)
    {
        rt_free(load_info->exec_info.filename);
    }

    if (load_info->interp_info.phdr != RT_NULL)
    {
        rt_free(load_info->interp_info.phdr);
    }

    if (load_info->interp_info.filename != RT_NULL)
    {
        rt_free(load_info->interp_info.filename);
    }
}

/**
 * @brief Load the ELF header and program header information.
 *
 * @param exec_info Pointer to the elf_info_t structure containing elf file information.
 *
 * @return RT_EOK if the ELF header and program header information are successfully loaded.
 * @return -RT_ERROR if any error occurs during the loading process.
 */
static int elf_load_app(elf_info_t *exec_info)
{
    int ret;

    /* load elf header */
    ret = elf_load_ehdr(exec_info);
    if (ret != RT_EOK)
    {
        return ret;
    }

    /* load the ELF program header */
    ret = elf_load_phdr(exec_info);
    if (ret != RT_EOK)
    {
        return ret;
    }

    return ret;
}

/**
 * @brief Load an ELF file into memory.
 *
 * @param load_info Pointer to the elf_load_info_t structure containing information about the ELF file.
 *
 * @return RT_EOK if the ELF file is successfully loaded.
 * @return -RT_ERROR if any error occurs during the loading process.
 */
static int elf_file_load(elf_load_info_t *load_info)
{
    int ret;

    /* Load basic information of the ELF application (ELF header and program header) */
    ret = elf_load_app(&load_info->exec_info);
    if (ret != RT_EOK)
    {
        goto OUT;
    }

    /* Load the interpreter (if any) */
    ret = elf_load_interp(load_info);
    if (ret != RT_EOK)
    {
        goto OUT;
    }

    /* Load each segment of the ELF file into memory */
    ret = elf_load_segment(load_info);
    if (ret != RT_EOK)
    {
        goto OUT;
    }

OUT:
    /* Perform resource cleanup regardless of success or failure */
    elf_load_deinit(load_info);
    return ret;
}

/**
 * @brief Load an ELF executable file into memory and prepare it for execution.
 *
 * This function is responsible for loading an ELF format executable file into memory,
 * setting up the necessary process structures, and preparing it for execution.
 *
 * @param filename The path to the ELF file to be loaded.
 * @param lwp Pointer to the Light Weight Process (LWP) structure that will execute the program.
 * @param load_addr The memory address where the ELF should be loaded.
 * @param addr_size The size of the memory area available for loading.
 * @param aux_ua Pointer to the auxiliary information structure for process initialization.
 *
 * @return RT_EOK if the ELF file is successfully loaded and prepared for execution.
 * @return -RT_ERROR if any error occurs during the loading process, including:
 *         - Invalid filename or path
 *         - Memory allocation failure
 *         - ELF file format errors
 *
 * @see dfs_normalize_path, elf_file_load
 */
int lwp_load(const char *filename, struct rt_lwp *lwp, uint8_t *load_addr, size_t addr_size,
    struct process_aux *aux_ua)
{
    elf_load_info_t load_info = { 0 };
    int len;
    int ret;

    /* Validate input filename */
    if (filename == RT_NULL)
    {
        LOG_E("%s : file is NULL", __func__);
        return -RT_ERROR;
    }

    /* Check filename length constraints */
    len = rt_strlen(filename);
    if (len < FLF_PATH_MIN || len > ELF_PATH_MAX)
    {
        LOG_E("%s : file length (%d) invalid", __func__, len);
        return -RT_ERROR;
    }

    /* Allocate memory for filename and copy it */
    load_info.exec_info.filename = rt_malloc(len + 1);
    if (!load_info.exec_info.filename)
    {
        LOG_E("%s : alloc filename failed", __func__, len);
        return -RT_ERROR;
    }
    else
    {
        rt_memset(load_info.exec_info.filename, 0, len + 1);
        rt_strncpy(load_info.exec_info.filename, filename, len);
    }

    /* Initialize load information structure */
    load_info.lwp = lwp;
    load_info.aux = aux_ua;

    load_info.exec_info.fd = ELF_INVALID_FD;
    load_info.interp_info.fd = ELF_INVALID_FD;
    load_info.load_addr = (rt_ubase_t)load_addr;

    /* copy file name to process name */
    rt_strncpy(lwp->cmd, filename, RT_NAME_MAX);
    lwp->exe_file = dfs_normalize_path(NULL, filename); /* malloc */

    /* Load and process the ELF file */
    ret = elf_file_load(&load_info);
    if (ret != RT_EOK)
    {
        LOG_E("%s : elf_file_load error, ret : %d", __func__, ret);
        return ret;
    }

    return RT_EOK;
}

#endif