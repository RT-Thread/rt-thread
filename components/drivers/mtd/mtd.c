/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
   2018-09-10     heyuanjie87   first version

 */

#include <drivers/mtd.h>

static rt_mtd_t* mtd_part_alloc(rt_mtd_t *master, const struct mtd_part *part)
{
    rt_mtd_t *slave;

    slave = rt_malloc(sizeof(rt_mtd_t));
    if (slave == RT_NULL)
        goto out;

    slave->master = master;

    *slave = *master;
    slave->size = part->size;
    slave->offset = part->offset;

out:

    return slave;
}

rt_mtd_t* rt_mtd_get(const char *name)
{
    rt_mtd_t *mtd;

    mtd = (rt_mtd_t *)rt_device_find(name);
    if (mtd == RT_NULL)
        return RT_NULL;

    if (mtd->parent.type != RT_Device_Class_MTD)
        return RT_NULL;

    return mtd;
}

/*
 * Register MTD driver
 *
 * @parts partion description
 * @np number of partitions
 * @return number of unregistered partitions
 *
*/
int rt_mtd_register(rt_mtd_t *master, const struct mtd_part *parts, int np)
{
    int ret;
    rt_mtd_t *slave;

    master->master = master;
    master->parent.type = RT_Device_Class_MTD;

    if (np > 0)
    {
        master->offset = parts->offset;
        master->size = parts->size;

        ret = rt_device_register((rt_device_t)master, parts->name, 0);
        if (ret != 0)
            goto _out;

        np --;
        parts ++;
    }

    while (np > 0)
    {
        slave = mtd_part_alloc(master, parts);
        if (!slave)
            break;
        ret = rt_device_register((rt_device_t)slave, parts->name, 0);
        if (ret)
            break;
        parts ++;
        np --;
    }

_out:
    return np;
}

int rt_mtd_block_erase(rt_mtd_t *mtd, uint32_t block)
{
    uint32_t total_blks;
    loff_t addr;

    total_blks = mtd->size/mtd->block_size;
    if (block >= total_blks)
        return -EINVAL;
    addr = mtd->offset + mtd->block_size * block;

    return mtd->ops->erase(mtd->master, addr, mtd->block_size);
}

int rt_mtd_block_isbad(rt_mtd_t *mtd, uint32_t block)
{
    uint32_t total_blks, offset_blk;

    if (!mtd->ops->isbad)
        return 0;

    total_blks = mtd->size / mtd->block_size;
    if (block >= total_blks)
        return -EINVAL;
    offset_blk = mtd->offset / mtd->block_size;

    return mtd->ops->isbad(mtd->master, block + offset_blk);
}

int rt_mtd_block_markbad(rt_mtd_t *mtd, uint32_t block)
{
    uint32_t total_blks, offset_blk;

    if (!mtd->ops->markbad)
        return -EOPNOTSUPP;

    total_blks = mtd->size / mtd->block_size;
    if (block >= total_blks)
        return -EINVAL;
    offset_blk = mtd->offset / mtd->block_size;

    return mtd->ops->markbad(mtd->master, block + offset_blk);
}

int rt_mtd_erase(rt_mtd_t *mtd, loff_t addr, size_t size)
{
    if (addr > mtd->size || (addr + size) > mtd->size)
        return -EINVAL;
    addr += mtd->offset;

    return mtd->ops->erase(mtd->master, addr, size);
}

/*
* Read data only
*
* @from offset to read from
* @return success size or error code
*/
int rt_mtd_read(rt_mtd_t *mtd, loff_t from, uint8_t *buf, size_t len)
{
    int ret;
    struct mtd_io_desc desc = {0};

    if (from < 0 || from >= (loff_t)mtd->size || len > mtd->size - from)
        return -EINVAL;
    if (!len)
        return 0;

    desc.datbuf = buf;
    desc.datlen = len;
    ret = mtd->ops->read(mtd->master, from + mtd->offset, &desc);
    if (ret)
        return ret;

    return desc.datretlen;
}

/**
* Write data only
*
* @to offset to write from
* @return success size or error code
*/
int rt_mtd_write(rt_mtd_t *mtd, loff_t to, const uint8_t *buf, size_t len)
{
    int ret;
    struct mtd_io_desc desc = {0};

    if (to < 0 || to >= (loff_t)mtd->size || len > mtd->size - to)
        return -EINVAL;
    if (!mtd->ops->write)
        return -EROFS;
    if (!len)
        return 0;

    desc.datbuf = (uint8_t*)buf;
    desc.datlen = len;
    ret = mtd->ops->write(mtd->master, to + mtd->offset, &desc);
    if (ret)
        return ret;

    return desc.datretlen;
}

/**
* Read data and/or out-of-band
*
* @from offset to read from
* @desc sector operation description structure
* @return error code, 0 success
*/
int rt_mtd_read_oob(rt_mtd_t *mtd, loff_t from, struct mtd_io_desc *desc)
{
    desc->datretlen = 0;
    desc->oobretlen = 0;

    if (from < 0 || from >= (loff_t)mtd->size)
        return -EINVAL;

    if (desc->datbuf && (desc->datlen > (mtd->size - from)))
        return -EINVAL;

    return mtd->ops->read(mtd->master, from + mtd->offset, desc);
}

/**
* Write data and/or out-of-band
*
* @to offset to read from
* @desc sector operation description structure
* @return error code, 0 success
*/
int rt_mtd_write_oob(rt_mtd_t *mtd, loff_t to, struct mtd_io_desc *desc)
{
    desc->datretlen = 0;
    desc->oobretlen = 0;

    if (to < 0 || to >= (loff_t)mtd->size)
        return -EINVAL;

    if (desc->datbuf && (desc->datlen >(mtd->size - to)))
        return -EINVAL;

    return mtd->ops->write(mtd->master, to + mtd->offset, desc);
}
