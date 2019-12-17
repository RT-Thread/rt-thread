/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-3-30      bluebear233  first version
 */

#include <rtdevice.h>

#ifdef RT_USING_SPI

#if defined(RT_USING_SFUD)
    static struct rt_spi_device spi_device;
    #include "spi_flash.h"
    #include "spi_flash_sfud.h"
#endif


static int rt_hw_spi_flash_init(void)
{
    rt_spi_bus_attach_device(&spi_device, "qspi01", "qspi0", RT_NULL);

#if defined(RT_USING_SFUD)

    if (rt_sfud_flash_probe("flash0", "qspi01") == RT_NULL)
    {
        return -RT_ERROR;
    }
#endif
    return 0;
}
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_init);


#endif /* RT_USING_SPI */

