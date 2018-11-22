/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-11-08     ZYH            the first version
 */
#include <rtthread.h>
#if defined(RT_USING_W25QXX) || defined(RT_USING_SFUD)
    #include <drv_spi.h>
#ifdef RT_USING_W25QXX
    #include "spi_flash_w25qxx.h"
#elif defined(RT_USING_SFUD)
    #include "string.h"
    #include "spi_flash.h"
    #include "spi_flash_sfud.h"
    sfud_flash sfud_norflash0;
    rt_spi_flash_device_t spi_device;
#endif

int rt_nor_flash_init(void)
{
    stm32_spi_bus_attach_device(RT_FLASH_CS_PIN, RT_FLASH_SPI_BUS_NAME, "norspi");
#ifdef RT_USING_W25QXX
    return w25qxx_init("flash0", "norspi");
#elif defined(RT_USING_SFUD)
    spi_device = rt_sfud_flash_probe("flash0", "norspi");
    if (spi_device == RT_NULL)
    {
        return -RT_ERROR;
    }
    memcpy(&sfud_norflash0, spi_device->user_data, sizeof(sfud_flash));
    return 0;
#endif
}
INIT_DEVICE_EXPORT(rt_nor_flash_init);
#endif
