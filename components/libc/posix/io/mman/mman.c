/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017/11/30     Bernard           The first version.
 * 2024/03/29     TroyMitchelle     Add all function comments
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
 * @brief   Maps a region of memory into the calling process's address space.
 * @param   addr    Desired starting address of the mapping.
 * @param   length  Length of the mapping.
 * @param   prot    Protection of the mapped memory region.
 * @param   flags   Type of the mapped memory region.
 * @param   fd      File descriptor of the file to be mapped.
 * @param   offset  Offset within the file to start the mapping.
 * @return  Upon success, returns a pointer to the mapped region; otherwise, MAP_FAILED is returned.
 */
void *mmap(void *addr, size_t length, int prot, int flags,
    int fd, off_t offset)
{
    uint8_t *mem;

    if (addr)
    {
        mem = addr;
    }
    else mem = (uint8_t *)malloc(length);

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
 * @brief   Unmaps a mapped region of memory.
 * @param   addr    Starting address of the mapping to be unmapped.
 * @param   length  Length of the mapping.
 * @return  Upon success, returns 0; otherwise, -1 is returned.
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
