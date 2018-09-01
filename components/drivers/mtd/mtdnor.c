/*
 * File      : mtdnor.c
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
 * 2018-8-30      heyuanjie    the first version
 */

#include <drivers/mtdnor.h>

#ifdef MTD_USING_NOR
static int _nor_erase(rt_mtd_t *mtd, loff_t addr, size_t len)
{
    rt_nor_t *nor;

    nor = (rt_nor_t *)mtd;
    return nor->ops->erase(nor, addr, len);
}

static int _nor_read(rt_mtd_t *mtd, loff_t from, struct mtd_io_desc *desc)
{
    rt_nor_t *nor;
    int ret;

    nor = (rt_nor_t *)mtd;
    ret = nor->ops->read(nor, from, desc->datbuf, desc->datlen);
    if (ret > 0)
    {
        desc->datretlen = ret;
        ret = 0;
    }

    return ret;
}

static int _nor_write(rt_mtd_t *mtd, loff_t to, struct mtd_io_desc *desc)
{
    rt_nor_t *nor;
    int ret;

    nor = (rt_nor_t *)mtd;
    ret = nor->ops->write(nor, to, desc->datbuf, desc->datlen);
    if (ret > 0)
    {
        desc->datretlen = ret;
        ret = 0;
    }

    return ret; 
}

static const struct mtd_ops _ops =
{
    _nor_erase,
    _nor_read,
    _nor_write,
    0,
    0
};

int rt_mtd_nor_init(rt_nor_t *nor, int blksize)
{
    nor->parent.sector_size = 1;
    nor->parent.block_size = blksize;
    nor->parent.ops = &_ops;
    nor->parent.type = MTD_TYPE_NOR;

    return 0;
}
#endif
