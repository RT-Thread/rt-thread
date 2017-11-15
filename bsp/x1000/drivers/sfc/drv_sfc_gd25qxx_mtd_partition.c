/*
 * File      : drv_sfc_gd25qxx_mtd_partition.c
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017Äê4ÔÂ19ÈÕ     Urey         the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/mtd_nor.h>

#include "board.h"
#include "drv_clock.h"
#include "drv_gpio.h"
#include "drv_sfc.h"
#include "mtd_nor_partition.h"

static struct rt_mtd_nor_partition _sf_gd25_parts[] =
{
    {
        /* sf01 u-boot 512K */
        .name       = "uboot",
        .offset     = 0x0,
        .size       = (0x80000),
        .mask_flags = PART_FLAG_RDONLY | PART_TYPE_BLK,     /* force read-only */
    },

    {
        /* kernel */
        .name       = "kernel",
        .offset     = 0x80000,
        .size       = 0x380000,
        .mask_flags = PART_FLAG_RDONLY | PART_TYPE_BLK,     /* force read-only */
    },

    {
        /* rootfs */
        .name       = "rootfs",
        .offset     = 0x400000,
        .size       = 0x800000,
        .mask_flags = PART_FLAG_RDONLY | PART_TYPE_BLK,     /* force read-only & Block device */
    },

    {
        /* sf04 appfs 2M*/
        .name       = "appfs",
        .offset     = 0xE00000,
        .size       = 0x200000,
        .mask_flags = PART_FLAG_RDWR | PART_TYPE_BLK,     /* force read-only & Block device */
    },

    //end
    {
        .name = (char *)0
    }
};


int rt_hw_gd25qxx_mtd_part_init(const char *mtd_name)
{
    mtd_nor_init_partition(mtd_name,_sf_gd25_parts);

    return 0;
}
