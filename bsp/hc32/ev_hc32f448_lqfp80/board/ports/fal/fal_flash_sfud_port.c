/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-20     CDT          first version
 */

#include <fal.h>

#include <sfud.h>
#ifdef RT_USING_SFUD
    #include <dev_spi_flash_sfud.h>
#endif

#ifndef FAL_USING_NOR_FLASH_DEV_NAME
    #define FAL_USING_NOR_FLASH_DEV_NAME            "w25q64"
#endif

static int init(void);
static int read(long offset, rt_uint8_t *buf, rt_size_t size);
static int write(long offset, const rt_uint8_t *buf, rt_size_t size);
static int erase(long offset, rt_size_t size);

static sfud_flash_t sfud_dev = NULL;
struct fal_flash_dev ext_nor_flash0 =
{
    .name       = FAL_USING_NOR_FLASH_DEV_NAME,
    .addr       = 0,
    .len        = 8 * 1024 * 1024,
    .blk_size   = 4096,
    .ops        = {init, read, write, erase},
    .write_gran = 1
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
