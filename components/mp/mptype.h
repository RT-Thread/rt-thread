/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-08-25     tangzz98     the first version
 */

#ifndef __MPTYPE_H__
#define __MPTYPE_H__

#include <mpporttype.h>

typedef struct
{
    void *start;
    rt_size_t size;
    rt_mem_attr_t attr;
} rt_mem_region_t;

#endif /* __MPTYPE_H__ */
