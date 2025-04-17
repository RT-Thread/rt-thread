/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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

#define DBG_TAG  "FLASH"
#define DBG_LVL  DBG_LOG
#include <rtdbg.h>

#define SPI_FLASH_DEVICE_NAME       "spi00"
#define SPI_FLASH_CHIP              "gd25qxx"

//#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINTF(...)   rt_kprintf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...)
#endif

#if defined(TINA_USING_SPI_FLASH) && defined(RT_USING_SFUD)
#include "dev_spi_flash.h"
#include <dev_spi_flash_sfud.h>
rt_spi_flash_device_t spi_device;
int rt_hw_spi_flash_with_sfud_init(void)
{
    DEBUG_PRINTF("%s -> %d\n", __FUNCTION__, __LINE__);
    spi_device = rt_sfud_flash_probe(SPI_FLASH_CHIP, SPI_FLASH_DEVICE_NAME);
    if (spi_device == NULL)
    {
        DEBUG_PRINTF("%s -> %d\n", __FUNCTION__, __LINE__);
        return -RT_ERROR;
    };

    DEBUG_PRINTF("%s -> %d\n", __FUNCTION__, __LINE__);
    return RT_EOK;
}
INIT_PREV_EXPORT(rt_hw_spi_flash_with_sfud_init);
#endif /* defined(TINA_USING_SPI_FLASH) && defined(RT_USING_SFUD) */
