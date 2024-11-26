/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-26     RT-Thread    the first version
 */

#include <rtconfig.h>
#ifdef RT_USING_FAL
#include <rthw.h>

#include <fal.h>
#include <sfud.h>

static int init(void);
static int read(long offset, rt_uint8_t *buf, rt_size_t size);
static int write(long offset, const rt_uint8_t *buf, rt_size_t size);
static int erase(long offset, rt_size_t size);

extern sfud_flash sfud_norflash0;
struct fal_flash_dev nor_flash0 =
{
    "norflash0",
     0,
     16 * 1024 * 1024,
     4096,
     {init, read, write, erase}
};

static int read(long offset, rt_uint8_t *buf, rt_size_t size)
{
    sfud_read(&sfud_norflash0, nor_flash0.addr + offset, size, buf);
    return size;
}

static int write(long offset, const rt_uint8_t *buf, rt_size_t size)
{
    if (sfud_write(&sfud_norflash0, nor_flash0.addr + offset, size, buf) != SFUD_SUCCESS)
    {
        return -1;
    }

    return size;
}

static int erase(long offset, rt_size_t size)
{
    if (sfud_erase(&sfud_norflash0, nor_flash0.addr + offset, size) != SFUD_SUCCESS)
    {
        return -1;
    }

    return size;
}

static int init(void)
{
    nor_flash0.len = sfud_norflash0.chip.capacity;
    nor_flash0.blk_size = sfud_norflash0.chip.erase_gran;

    return 0;
}

#endif
