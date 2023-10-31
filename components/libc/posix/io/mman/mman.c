/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/11/30     Bernard      The first version.
 */

#include <stdint.h>
#include <stdio.h>

#include <rtthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/errno.h>

#include "sys/mman.h"

/**
 * @brief Map a file into memory.
 *
 * This function maps a file into memory, creating a new memory mapping in the address space
 * of the calling process. It allocates memory of the specified length and reads data from
 * the file descriptor 'fd' into the memory region. The 'offset' parameter specifies the
 * starting offset in the file.
 *
 * @param addr    The starting address of the mapping (ignored in this implementation).
 * @param length  The length of the memory region to map.
 * @param prot    The protection (permissions) of the mapped memory (ignored in this implementation).
 * @param flags   Flags for mapping type and options (ignored in this implementation).
 * @param fd      The file descriptor of the file to be mapped.
 * @param offset  The offset in the file where the mapping starts.
 *
 * @return On success, a pointer to the newly mapped memory is returned. On failure, MAP_FAILED is returned.
 */
void *mmap(void *addr, size_t length, int prot, int flags,
           int fd, off_t offset)
{
    uint8_t *mem;

    if (addr)
    {
        mem = addr;
    }
    else
        mem = (uint8_t *)malloc(length);

    if (mem)
    {
        off_t cur;
        size_t read_bytes;

        cur = lseek(fd, 0, SEEK_SET);

        lseek(fd, offset, SEEK_SET);
        read_bytes = read(fd, mem, length);
        if (read_bytes != length)
        {
            if (addr == RT_NULL)
            {
                /* read failed */
                free(mem);
                mem = RT_NULL;
            }
        }
        lseek(fd, cur, SEEK_SET);

        return mem;
    }

    errno = ENOMEM;

    return MAP_FAILED;
}

/**
 * @brief Unmap a memory region.
 *
 * This function unmaps a memory region previously mapped with the mmap function.
 * It deallocates the memory region.
 *
 * @param addr    The starting address of the memory region to unmap.
 * @param length  The length of the memory region to unmap.
 *
 * @return 0 on success, -1 on failure.
 */
int munmap(void *addr, size_t length)
{
    if (addr)
    {
        free(addr);
        return 0;
    }

    return -1;
}
