/*
 * File      : mtdnor.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, Shanghai Real-Thread Technology Co., Ltd
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
 * 2018-8-30     heyuanjie      the first version
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
