/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-07     Meco Man     first version
 */

#include <fal.h>
#include <sfud.h>

#ifdef RT_USING_SFUD
#include <dev_spi_flash_sfud.h>
#endif

static int init(void);
static int read(long offset, rt_uint8_t *buf, rt_size_t size);
static int write(long offset, const rt_uint8_t *buf, rt_size_t size);
static int erase(long offset, rt_size_t size);

static sfud_flash_t sfud_dev = NULL;
struct fal_flash_dev w25q64 =
{
    .name       = "W25Q64",
    .addr       = 0,
    .len        = 8 * 1024 * 1024,
    .blk_size   = 4096,
    .ops        = {init, read, write, erase},
    .write_gran = 1
};

static int init(void)
{
    sfud_dev = rt_sfud_flash_find_by_dev_name("W25Q64");
    if (RT_NULL == sfud_dev)
    {
        return -1;
    }

    /* update the flash chip information */
    w25q64.blk_size = sfud_dev->chip.erase_gran;
    w25q64.len = sfud_dev->chip.capacity;

    return 0;
}

static int read(long offset, rt_uint8_t *buf, rt_size_t size)
{
    RT_ASSERT(sfud_dev);
    RT_ASSERT(sfud_dev->init_ok);
    sfud_read(sfud_dev, w25q64.addr + offset, size, buf);

    return size;
}

static int write(long offset, const rt_uint8_t *buf, rt_size_t size)
{
    RT_ASSERT(sfud_dev);
    RT_ASSERT(sfud_dev->init_ok);
    if (sfud_write(sfud_dev, w25q64.addr + offset, size, buf) != SFUD_SUCCESS)
    {
        return -1;
    }

    return size;
}

static int erase(long offset, rt_size_t size)
{
    RT_ASSERT(sfud_dev);
    RT_ASSERT(sfud_dev->init_ok);
    if (sfud_erase(sfud_dev, w25q64.addr + offset, size) != SFUD_SUCCESS)
    {
        return -1;
    }

    return size;
}
