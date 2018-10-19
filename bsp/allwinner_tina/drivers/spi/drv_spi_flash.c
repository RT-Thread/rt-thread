/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

#define DBG_ENABLE
#define DBG_SECTION_NAME  "FLASH"
#define DBG_LEVEL         DBG_LOG
#define DBG_COLOR
#include <rtdbg.h>

#define SPI_FLASH_DEVICE_NAME       "spi00"
#define SPI_FLASH_CHIP              "gd25qxx"

//#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINTF(...)   rt_kprintf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...)
#endif

#ifdef TINA_USING_SPI_FLASH

#include "spi_flash.h"

#if defined(RT_USING_SFUD)
#include "spi_flash_sfud.h"
rt_spi_flash_device_t spi_device;
int rt_hw_spi_flash_with_sfud_init(void)
{
    DEBUG_PRINTF("%s -> %d\n", __FUNCTION__, __LINE__);
    spi_device = rt_sfud_flash_probe(SPI_FLASH_CHIP, SPI_FLASH_DEVICE_NAME);
    if (spi_device == NULL)
    {
        DEBUG_PRINTF("%s -> %d\n", __FUNCTION__, __LINE__);
        return RT_ERROR;
    };

    DEBUG_PRINTF("%s -> %d\n", __FUNCTION__, __LINE__);
    return RT_EOK;
}
INIT_PREV_EXPORT(rt_hw_spi_flash_with_sfud_init);

#elif defined(RT_USING_W25QXX)
#include "spi_flash_w25qxx.h"

int rt_hw_spi_flash_init(void)
{
    DEBUG_PRINTF("%s -> %d\n", __FUNCTION__, __LINE__);
    return w25qxx_init(SPI_FLASH_CHIP, SPI_FLASH_DEVICE_NAME);
}
INIT_DEVICE_EXPORT(rt_hw_spi_flash_init);

#endif

#endif