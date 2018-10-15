/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-05     Bernard      the first version
 * 2011-04-02     prife        add mark_badblock and check_block
 */

/*
 * COPYRIGHT (C) 2012, Shanghai Real Thread
 */

#ifndef __MTD_NAND_H__
#define __MTD_NAND_H__

#include <rtdevice.h>

struct rt_mtd_nand_driver_ops;
#define RT_MTD_NAND_DEVICE(device)  ((struct rt_mtd_nand_device*)(device))

#define RT_MTD_EOK          0   /* NO error */
#define RT_MTD_EECC         1   /* ECC error */
#define RT_MTD_EBUSY        2   /* hardware busy */
#define RT_MTD_EIO          3   /* generic IO issue */
#define RT_MTD_ENOMEM       4   /* out of memory */
#define RT_MTD_ESRC         5   /* source issue */
#define RT_MTD_EECC_CORRECT 6   /* ECC error but correct */

struct rt_mtd_nand_device
{
    struct rt_device parent;

    rt_uint16_t page_size;          /* The Page size in the flash */
    rt_uint16_t oob_size;           /* Out of bank size */
    rt_uint16_t oob_free;           /* the free area in oob that flash driver not use */
    rt_uint16_t plane_num;          /* the number of plane in the NAND Flash */

    rt_uint32_t pages_per_block;    /* The number of page a block */
    rt_uint16_t block_total;

    rt_uint32_t block_start;        /* The start of available block*/
    rt_uint32_t block_end;          /* The end of available block */

    /* operations interface */
    const struct rt_mtd_nand_driver_ops* ops;
};

struct rt_mtd_nand_driver_ops
{
    rt_err_t (*read_id) (struct rt_mtd_nand_device* device);

    rt_err_t (*read_page)(struct rt_mtd_nand_device* device,
                          rt_off_t page,
                          rt_uint8_t* data, rt_uint32_t data_len,
                          rt_uint8_t * spare, rt_uint32_t spare_len);

    rt_err_t (*write_page)(struct rt_mtd_nand_device * device,
                           rt_off_t page,
                           const rt_uint8_t * data, rt_uint32_t data_len,
                           const rt_uint8_t * spare, rt_uint32_t spare_len);
    rt_err_t (*move_page) (struct rt_mtd_nand_device *device, rt_off_t src_page, rt_off_t dst_page);

    rt_err_t (*erase_block)(struct rt_mtd_nand_device* device, rt_uint32_t block);
    rt_err_t (*check_block)(struct rt_mtd_nand_device* device, rt_uint32_t block);
    rt_err_t (*mark_badblock)(struct rt_mtd_nand_device* device, rt_uint32_t block);
};

rt_err_t rt_mtd_nand_register_device(const char* name, struct rt_mtd_nand_device* device);

rt_inline rt_uint32_t rt_mtd_nand_read_id(struct rt_mtd_nand_device* device)
{
    return device->ops->read_id(device);
}

rt_inline rt_err_t rt_mtd_nand_read(
    struct rt_mtd_nand_device* device,
    rt_off_t page,
    rt_uint8_t* data, rt_uint32_t data_len,
    rt_uint8_t * spare, rt_uint32_t spare_len)
{
    return device->ops->read_page(device, page, data, data_len, spare, spare_len);
}

rt_inline rt_err_t rt_mtd_nand_write(
    struct rt_mtd_nand_device* device,
    rt_off_t page,
    const rt_uint8_t* data, rt_uint32_t data_len,
    const rt_uint8_t * spare, rt_uint32_t spare_len)
{
    return device->ops->write_page(device, page, data, data_len, spare, spare_len);
}

rt_inline rt_err_t rt_mtd_nand_move_page(struct rt_mtd_nand_device* device,
                                         rt_off_t src_page, rt_off_t dst_page)
{
    return device->ops->move_page(device, src_page, dst_page);
}

rt_inline rt_err_t rt_mtd_nand_erase_block(struct rt_mtd_nand_device* device, rt_uint32_t block)
{
    return device->ops->erase_block(device, block);
}

rt_inline rt_err_t rt_mtd_nand_check_block(struct rt_mtd_nand_device* device, rt_uint32_t block)
{
    return device->ops->check_block(device, block);
}

rt_inline rt_err_t rt_mtd_nand_mark_badblock(struct rt_mtd_nand_device* device, rt_uint32_t block)
{
    return device->ops->mark_badblock(device, block);
}

#endif /* MTD_NAND_H_ */
