/*
 *  VMM IO map table
 *
 * COPYRIGHT (C) 2013, Shanghai Real-Thread Technology Co., Ltd
 *
 *  This file is part of RT-Thread (http://www.rt-thread.org)
 *  Maintainer: bernard.xiong <bernard.xiong at gmail.com>
 *
 *  All rights reserved.
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
 * 2013-06-15     Bernard      the first verion
 */
#include <rtthread.h>
#include "vmm.h"

static struct vmm_iomap _vmm_iomap[RT_VMM_IOMAP_MAXNR];

void vmm_iomap_init(struct vmm_iomap *iomap)
{
    rt_memcpy(_vmm_iomap, iomap, sizeof(_vmm_iomap));
}

/* find virtual address according to name */
unsigned long vmm_find_iomap(const char *name)
{
    int i;

    for (i = 0; i < ARRAY_SIZE(_vmm_iomap); i++)
    {
        if (rt_strcmp(_vmm_iomap[i].name, name) == 0)
            return (unsigned long)_vmm_iomap[i].va;
    }

    return 0;
}

/* find virtual address according to physcal address */
unsigned long vmm_find_iomap_by_pa(unsigned long pa)
{
    int i;

    for (i = 0; i < ARRAY_SIZE(_vmm_iomap); i++)
    {
        if (_vmm_iomap[i].pa == pa)
            return (unsigned long)_vmm_iomap[i].va;
    }

    return 0;
}
