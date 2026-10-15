/*
 * Copyright (c) 2022 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2026-07-02   hpmicro     First implementation
 *
 */
#include <rtconfig.h>
#if defined(RT_USING_SFUD) && defined(BSP_USING_SPI) && defined(RT_USING_FAL)
#include <fal.h>
#include <sfud.h>
#include <dev_spi_flash_sfud.h>

static int init(void);
static int read(long offset, rt_uint8_t *buf, rt_size_t size);
static int write(long offset, const rt_uint8_t *buf, rt_size_t size);
static int erase(long offset, rt_size_t size);

static sfud_flash_t sfud_dev = NULL;
struct fal_flash_dev spi_nor_flash0 =
{
    .name       = SPI_NOR_FLASH_DEV_NAME,
    .addr       = 0,
    .len        = 16 * 1024 * 1024,
    .blk_size   = 4096,
    .ops        = {init, read, write, erase},
    .write_gran = 1
};

static int init(void)
{

#ifdef RT_USING_SFUD
    /* RT-Thread RTOS platform */
    sfud_dev = rt_sfud_flash_find_by_dev_name(SPI_NOR_FLASH_DEV_NAME);
#endif

    if (NULL == sfud_dev)
    {
        return -1;
    }

    /* update the flash chip information */
    spi_nor_flash0.blk_size = sfud_dev->chip.erase_gran;
    spi_nor_flash0.len = sfud_dev->chip.capacity;

    return 0;
}

static int read(long offset, rt_uint8_t *buf, rt_size_t size)
{
    RT_ASSERT(sfud_dev);
    RT_ASSERT(sfud_dev->init_ok);
    sfud_read(sfud_dev, spi_nor_flash0.addr + offset, size, buf);

    return size;
}

static int write(long offset, const rt_uint8_t *buf, rt_size_t size)
{
    RT_ASSERT(sfud_dev);
    RT_ASSERT(sfud_dev->init_ok);
    if (sfud_write(sfud_dev, spi_nor_flash0.addr + offset, size, buf) != SFUD_SUCCESS)
    {
        return -1;
    }

    return size;
}

static int erase(long offset, rt_size_t size)
{
    RT_ASSERT(sfud_dev);
    RT_ASSERT(sfud_dev->init_ok);
    if (sfud_erase(sfud_dev, spi_nor_flash0.addr + offset, size) != SFUD_SUCCESS)
    {
        return -1;
    }

    return size;
}

#endif 