/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
   2018-09-10     heyuanjie87   first version

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
    nor->parent.oob_size = 0;

    return 0;
}
#endif
