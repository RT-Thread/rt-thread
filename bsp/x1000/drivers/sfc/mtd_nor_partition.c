/**
  ******************************************************************************
  * @file    rt_mtd_nor_partition.c
  * @author  Urey
  * @version V1.0.0
  * @date    2017Äê2ÔÂ11ÈÕ
  * @brief   TODO
  ******************************************************************************         
**/ 



#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/mtd_nor.h>

#include "mtd_nor_partition.h"


// #define MTD_DEBUG   1
#ifdef MTD_DEBUG
#define MTD_DBG(...)     rt_kprintf("[MTD]"),rt_kprintf(__VA_ARGS__)
#else
#define MTD_DBG(...)
#endif

/* RT-Thread device interface */
static rt_err_t mtd_part_blk_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t mtd_part_blk_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t mtd_part_blk_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t mtd_part_blk_control(rt_device_t dev, int cmd, void *args)
{
    struct rt_mtd_nor_partition *mtd_part;
    struct rt_mtd_nor_device *mtd_nor;

    RT_ASSERT(dev != RT_NULL);

    mtd_part    = (struct rt_mtd_nor_partition *)dev;
    mtd_nor = (struct rt_mtd_nor_device *)mtd_part->user_data;

    switch (cmd)
    {
        case RT_DEVICE_CTRL_BLK_GETGEOME:
        {
            struct rt_device_blk_geometry *geometry;

            geometry = (struct rt_device_blk_geometry *)args;
            if (geometry == RT_NULL)
                return -RT_ERROR;

            geometry->bytes_per_sector  = mtd_nor->block_size;
            geometry->sector_count      = mtd_part->size / mtd_nor->block_size;
            geometry->block_size        = mtd_nor->block_size;
            
            break;
        }
        default:
            break;
    }

    return RT_EOK;
}

static rt_size_t mtd_part_blk_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    struct rt_mtd_nor_partition *mtd_part;
    struct rt_mtd_nor_device *mtd_nor;
    rt_size_t   read_count = 0;
    rt_uint8_t *ptr = (rt_uint8_t *)buffer;

    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(size != 0);

    mtd_part    = (struct rt_mtd_nor_partition *)dev;
    mtd_nor = (struct rt_mtd_nor_device *)mtd_part->user_data;

    MTD_DBG("%s name = %s,position = %08x,size = %08x\n",__func__,mtd_part->name,pos,size);

    if(!(mtd_part->mask_flags & PART_FLAG_RDONLY))
    {
        MTD_DBG("ERROR: this device is unreadable,mask_flags = %04x\n", mtd_part->mask_flags);
        return 0;
    }

    while(read_count < size)
    {/* It'a BLOCK device */
        if(((pos + 1) * mtd_nor->block_size) > (mtd_part->offset + mtd_part->size))
        {
            MTD_DBG("ERROR: read overrun!\n");
            break;
        }
        rt_mtd_nor_read(mtd_nor,pos * mtd_nor->block_size + mtd_part->offset,ptr,mtd_nor->block_size);

        pos++;
        ptr += mtd_nor->block_size;
        read_count++;
    }

    return read_count;
}

static rt_size_t mtd_part_blk_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    struct rt_mtd_nor_partition *mtd_part;
    struct rt_mtd_nor_device *mtd_nor;
    rt_size_t   write_count = 0;
    rt_uint8_t *ptr = (rt_uint8_t *)buffer;

    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(size != 0);

    mtd_part    = (struct rt_mtd_nor_partition *)dev;
    mtd_nor = (struct rt_mtd_nor_device *)mtd_part->user_data;
    MTD_DBG("%s name = %s,position = %08x,size = %08x\n",__func__,mtd_part->name,pos,size);
    if(!(mtd_part->mask_flags & PART_FLAG_WRONLY))
    {
        MTD_DBG("ERROR: this device is unwritable,mask_flags = %04x\n", mtd_part->mask_flags);
        /* read only partition, ignore this data */
        return size;
    }

    while(write_count < size)
    {/* It'a BLOCK device */
        if((pos + 1) * mtd_nor->block_size > (mtd_part->offset + mtd_part->size))
        {
            MTD_DBG("ERROR: write overrun!\n");
            break;
        }
        rt_mtd_nor_erase_block(mtd_nor,(pos * mtd_nor->block_size + mtd_part->offset),mtd_nor->block_size);
        rt_mtd_nor_write(mtd_nor,(pos * mtd_nor->block_size + mtd_part->offset),ptr,mtd_nor->block_size);

        pos++;
        ptr += mtd_nor->block_size;
        write_count++;
    }

    return write_count;
}

static rt_base_t mtd_part_mtd_read_id(struct rt_mtd_nor_device *dev)
{
    struct rt_mtd_nor_partition *mtd_part;
    struct rt_mtd_nor_device *mtd_nor;

    RT_ASSERT(dev != RT_NULL);

    mtd_part    = (struct rt_mtd_nor_partition *)dev;
    mtd_nor = (struct rt_mtd_nor_device *)mtd_part->user_data;

    return rt_mtd_nor_read_id(mtd_nor);
}

static rt_size_t mtd_part_mtd_read(struct rt_mtd_nor_device *dev, rt_off_t offset, rt_uint8_t *buffer, rt_uint32_t length)
{
    struct rt_mtd_nor_partition *mtd_part;
    struct rt_mtd_nor_device *mtd_nor;

    RT_ASSERT(dev != RT_NULL);

    mtd_part    = (struct rt_mtd_nor_partition *)dev;
    mtd_nor = (struct rt_mtd_nor_device *)mtd_part->user_data;

    MTD_DBG("%s offset = %08x,size = %08x\n",__func__,offset,length);
    if(!(mtd_part->mask_flags & PART_FLAG_RDONLY))
    {
        MTD_DBG("ERROR: this device is unreadable,mask_flags = %04x\n", mtd_part->mask_flags);
        return 0;
    }

    if(mtd_part->mask_flags & PART_TYPE_MTD)
    {/* It'a MTD device */
        if((offset + length) > mtd_part->size)
        {
            MTD_DBG("ERROR: read size > partition size, pos=%d, size=%d, partition_size=%d\n", offset, length, mtd_part->size);
            return 0;
        }

        rt_mtd_nor_read(mtd_nor,(mtd_part->offset + offset),buffer,length);

        return length;
    }

    MTD_DBG("ERROR: unknown device type..\n");
    return 0;
}

static rt_size_t mtd_part_mtd_write(struct rt_mtd_nor_device *dev, rt_off_t offset, const rt_uint8_t *buffer, rt_uint32_t length)
{
    struct rt_mtd_nor_partition *mtd_part;
    struct rt_mtd_nor_device *mtd_nor;

    RT_ASSERT(dev != RT_NULL);

    mtd_part    = (struct rt_mtd_nor_partition *)dev;
    mtd_nor = (struct rt_mtd_nor_device *)mtd_part->user_data;

    MTD_DBG("%s offset = %08x,size = %08x\n",__func__,offset,length);

    if(!(mtd_part->mask_flags & PART_FLAG_WRONLY))
    {
        MTD_DBG("ERROR: this device is unwritable,mask_flags = %04x\n", mtd_part->mask_flags);
        /* read only partition, ignore this data */
        return length;
    }

    if(mtd_part->mask_flags & PART_TYPE_MTD)
    { /* It'a MTD device */
        if((offset + length) > mtd_part->size)
        {
            MTD_DBG("ERROR: write size > partition size, pos=%d, size=%d, partition_size=%d\n", offset, length, mtd_part->size);
            return 0;
        }

        /* MTD device skip erase,user do it by himself */
        rt_mtd_nor_write(mtd_nor,(mtd_part->offset + offset),buffer,length);
        return length;
    }

    MTD_DBG("ERROR: unknown device type..\n");
    return 0;
}

static rt_err_t mtd_part_mtd_erase_block(struct rt_mtd_nor_device* dev, rt_off_t offset, rt_uint32_t length)
{
    struct rt_mtd_nor_partition *mtd_part;
    struct rt_mtd_nor_device *mtd_nor;

    RT_ASSERT(dev != RT_NULL);

    mtd_part    = (struct rt_mtd_nor_partition *)dev;
    mtd_nor = (struct rt_mtd_nor_device *)mtd_part->user_data;

    MTD_DBG("%s offset = %08x,size = %08x\n",__func__,offset,length);

    if(mtd_part->mask_flags & PART_TYPE_MTD)
    { /* It'a MTD device */
        if((offset + length) > mtd_part->size)
        {
            MTD_DBG("ERROR: erase size > partition size, pos=%d, size=%d, partition_size=%d\n", offset, length, mtd_part->size);
            return 0;
        }

        if(length % mtd_nor->block_size != 0)
        {
            MTD_DBG("ERROR: erase size must align to BLOCK SIZE\n");
            return 0;
        }

        rt_mtd_nor_erase_block(mtd_nor,(mtd_part->offset + offset),length);

        return length;
    }

    MTD_DBG("ERROR: unknown device type..\n");
    return 0;
}


const static struct rt_mtd_nor_driver_ops mtd_part_mtd_ops =
{
    mtd_part_mtd_read_id,
    mtd_part_mtd_read,
    mtd_part_mtd_write,
    mtd_part_mtd_erase_block,
};


rt_err_t mtd_nor_init_partition(const char *mtd_name,struct rt_mtd_nor_partition *parts)
{
    struct rt_mtd_nor_partition *mtd_part;
    struct rt_mtd_nor_device *mtd_nor;

    mtd_nor = (struct rt_mtd_nor_device *)rt_device_find(mtd_name);
    if(mtd_nor == RT_NULL)
        return -RT_EIO;
    
    for (mtd_part = parts; mtd_part->name != RT_NULL; mtd_part++)
    {
        MTD_DBG("part name: %s\n",mtd_part->name);
        /* get partition type */
        if(mtd_part->mask_flags & PART_TYPE_BLK)
        { /* It'a a BLOCK device */

            /* set device interface */
            mtd_part->blk.type      = RT_Device_Class_Block;
            mtd_part->blk.init      = mtd_part_blk_init;
            mtd_part->blk.open      = mtd_part_blk_open;
            mtd_part->blk.read      = mtd_part_blk_read;
            mtd_part->blk.write     = mtd_part_blk_write;
            mtd_part->blk.close     = mtd_part_blk_close;
            mtd_part->blk.control   = mtd_part_blk_control;

            mtd_part->user_data = mtd_nor;

            /* register device */
            rt_device_register(&mtd_part->blk,mtd_part->name,RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);
        }
        else if(mtd_part->mask_flags & PART_TYPE_MTD)
        { /* It's a MTD device */
            MTD_DBG("part name: %s\n",mtd_part->name);

            mtd_part->user_data = mtd_nor;

            /* Init MTD NOR device interface ... */
            mtd_part->mtd.block_size         = mtd_nor->block_size;
            mtd_part->mtd.block_start        = 0;
            mtd_part->mtd.block_end          = mtd_part->size / mtd_nor->block_size;
            mtd_part->mtd.ops                = &mtd_part_mtd_ops;

            rt_mtd_nor_register_device(mtd_part->name,&mtd_part->mtd);
        }
        else
        {
            MTD_DBG("ERROR: unknown device type..\n");
        }
    }

    return RT_EOK;
}


