/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

#include <fal.h>
#include <sfud.h>
#ifdef RT_USING_SFUD
    #include <dev_spi_flash_sfud.h>
#endif

#ifndef FAL_USING_NOR_FLASH_DEV_NAME
    #define FAL_USING_NOR_FLASH_DEV_NAME        "w25q64"
#endif

#define EXT_NOR_FLASH_START_ADDR        0
#define EXT_NOR_FLASH_CHIP_SIZE         8 * 1024 * 1024
#define EXT_NOR_FLASH_BLOCK_SIZE        4096
#define EXT_NOR_FLASH_WR_MIN_GRAN       1


static int init(void);
static int read(long offset, rt_uint8_t *buf, rt_size_t size);
static int write(long offset, const rt_uint8_t *buf, rt_size_t size);
static int erase(long offset, rt_size_t size);


static sfud_flash_t sfud_dev = NULL;
struct fal_flash_dev ext_nor_flash0 =
{
    .name       = FAL_USING_NOR_FLASH_DEV_NAME,
    .addr       = EXT_NOR_FLASH_START_ADDR,
    .len        = EXT_NOR_FLASH_CHIP_SIZE,
    .blk_size   = EXT_NOR_FLASH_BLOCK_SIZE,
    .ops        = {init, read, write, erase},
    .write_gran = EXT_NOR_FLASH_WR_MIN_GRAN,
};


static int init(void)
{
    /* RT-Thread RTOS platform */
    sfud_dev = rt_sfud_flash_find_by_dev_name(FAL_USING_NOR_FLASH_DEV_NAME);
    if (NULL == sfud_dev)
    {
        return -1;
    }
    /* update the flash chip information */
    ext_nor_flash0.blk_size = sfud_dev->chip.erase_gran;
    ext_nor_flash0.len      = sfud_dev->chip.capacity;

    return 0;
}

static int read(long offset, rt_uint8_t *buf, rt_size_t size)
{
    RT_ASSERT(sfud_dev);
    RT_ASSERT(sfud_dev->init_ok);
    sfud_read(sfud_dev, ext_nor_flash0.addr + offset, size, buf);

    return size;
}

static int write(long offset, const rt_uint8_t *buf, rt_size_t size)
{
    RT_ASSERT(sfud_dev);
    RT_ASSERT(sfud_dev->init_ok);
    if (sfud_write(sfud_dev, ext_nor_flash0.addr + offset, size, buf) != SFUD_SUCCESS)
    {
        return -1;
    }

    return size;
}

static int erase(long offset, rt_size_t size)
{
    RT_ASSERT(sfud_dev);
    RT_ASSERT(sfud_dev->init_ok);
    if (sfud_erase(sfud_dev, ext_nor_flash0.addr + offset, size) != SFUD_SUCCESS)
    {
        return -1;
    }

    return size;
}
