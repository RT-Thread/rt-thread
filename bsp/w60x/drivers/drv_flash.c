/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-04     tyx          1st version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "wm_flash_map.h"
#include "wm_internal_flash.h"
#include "drv_flash.h"

#define FLASH_SECTOR (4096)

#ifdef RT_USING_SPI
static void *_spi0;
#endif

extern unsigned int flashtotalsize;

rt_uint32_t wm_flash_total(void)
{
    rt_uint32_t total = 0x100000;

    if (flashtotalsize == 0x200000)
    {
        total = 0x200000;
    }

    return total;
}

rt_uint32_t wm_flash_addr(void)
{
    return FLASH_BASE_ADDR;
}

rt_uint32_t wm_flash_blksize(void)
{
    return FLASH_SECTOR;
}

int wm_flash_read(long offset, void *data, int size)
{
    offset += FLASH_BASE_ADDR;
#ifdef RT_USING_SPI
    if (_spi0)
    {
        rt_spi_take_bus(_spi0);
    }
#endif
    if (tls_fls_read(offset, data, size) != TLS_FLS_STATUS_OK)
    {
        size = -1;
    }
#ifdef RT_USING_SPI
    if (_spi0)
    {
        rt_spi_release_bus(_spi0);
    }
#endif

    return size;
}

int wm_flash_write(long offset, void *data, int size)
{
    offset += FLASH_BASE_ADDR;
#ifdef RT_USING_SPI
    if (_spi0)
    {
        rt_spi_take_bus(_spi0);
    }
#endif
    if (tls_fls_write(offset, data, size) != TLS_FLS_STATUS_OK)
    {
        size = -1;
    }
#ifdef RT_USING_SPI
    if (_spi0)
    {
        rt_spi_release_bus(_spi0);
    }
#endif

    return size;
}

int wm_flash_erase(long offset, int size)
{
    int count, sector;

    offset += FLASH_BASE_ADDR;
    count = size / FLASH_SECTOR;
    sector = offset / FLASH_SECTOR;
#ifdef RT_USING_SPI
    if (_spi0)
    {
        rt_spi_take_bus(_spi0);
    }
#endif
    while (count)
    {
        if (tls_fls_erase(sector) != TLS_FLS_STATUS_OK)
        {
            size = -1;
            break;
        }
        count--;
        sector++;
    }
#ifdef RT_USING_SPI
    if (_spi0)
    {
        rt_spi_release_bus(_spi0);
    }
#endif

    return size;
}

int wm_flash_init(void)
{
#ifdef RT_USING_SPI
    rt_err_t ret;

    if (_spi0 != RT_NULL)
    {
        return 0;
    }

    _spi0 = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(_spi0 != RT_NULL);

#ifdef WM_SPI_BUS_NAME
    ret = rt_spi_bus_attach_device(_spi0, "flash", WM_SPI_BUS_NAME, RT_NULL);
#else
    ret = rt_spi_bus_attach_device(_spi0, "flash", "spi0", RT_NULL);
#endif
    if (ret != RT_EOK)
    {
        rt_free(_spi0);
        _spi0 = RT_NULL;
    }

    if (_spi0)
    {
        ((struct rt_spi_device *)_spi0)->config.mode = RT_SPI_MODE_0;
        ((struct rt_spi_device *)_spi0)->config.data_width = 8;
        ((struct rt_spi_device *)_spi0)->config.max_hz = 20 * 1000 * 1000;
    }
#endif

    return 0;
}
