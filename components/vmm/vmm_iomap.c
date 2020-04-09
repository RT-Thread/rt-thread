/*
 *  VMM IO map table
 *
 * COPYRIGHT (C) 2013-2014, Real-Thread Information Technology Ltd
 * All rights reserved
 * 
 * SPDX-License-Identifier: Apache-2.0
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
