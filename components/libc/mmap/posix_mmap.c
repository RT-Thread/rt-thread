/*
 * File      : posix_mmap.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
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
 * 2017/11/30     Bernard      The first version.
 */

#include <stdint.h>
#include <stdio.h>

#include <rtthread.h>
#include <dfs_posix.h>

#include <sys/mman.h>

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
        read_bytes = read(fd, addr, length);
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

int munmap(void *addr, size_t length)
{
    if (addr)
    {
        free(addr);
        return 0;
    }

    return -1;
}
