/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
   2018-09-10     heyuanjie87   first version

 */

#ifndef __MTDNOR_H__
#define __MTDNOR_H__

#include <drivers/mtd.h>

struct nor_ops;

typedef struct
{
    rt_mtd_t parent;

    const struct nor_ops *ops; /* operations interface */
}rt_nor_t;

struct nor_ops
{
    int (*erase)(rt_nor_t *nor, loff_t addr, size_t len);                     /* return success erased len or error code */
    int (*read)(rt_nor_t *nor, loff_t addr, uint8_t *buf, size_t len);        /* return success data size or error code */
    int (*write)(rt_nor_t *nor, loff_t addr, const uint8_t *buf, size_t len); /* return success data size or error code */
};

int rt_mtd_nor_init(rt_nor_t *nor, int blksize);

#endif
