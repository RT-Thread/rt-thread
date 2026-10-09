/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-09-20     Bernard      the first version
 */

#ifndef PARTITION_H__
#define PARTITION_H__

#define PARTITION_RDONLY          0x000
#define PARTITION_WRITEABLE       0x100     /* Device is writable */
#define PARTITION_POWERUP_LOCK    0x200     /* Always locked after reset */

struct rt_partition
{
    char name[8];

    rt_uint32_t offset;
    rt_uint32_t size;

    rt_uint32_t flags;
};

int rt_partition_init(const char* flash_device, const struct rt_partition* parts, rt_size_t num);

#endif
