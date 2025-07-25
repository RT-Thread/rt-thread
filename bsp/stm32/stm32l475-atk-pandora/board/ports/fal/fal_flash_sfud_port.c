/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-26     armink       the first version
 * 2018-08-21     MurphyZhao   update to stm32l4xx
 */

#include <fal.h>

#include <sfud.h>
#include <dev_spi_flash_sfud.h>

sfud_flash sfud_norflash0;

static int fal_sfud_init(void)
{
    sfud_flash_t sfud_flash0 = NULL;
    sfud_flash0 = (sfud_flash_t)rt_sfud_flash_find("qspi10");
    if (NULL == sfud_flash0)
    {
        return -1;
    }

    sfud_norflash0 = *sfud_flash0;
    return 0;
}

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
const struct fal_flash_dev nor_flash0 = { "nor_flash", 0, (16 * 1024 * 1024), 4096, {fal_sfud_init, read, write, erase} };
