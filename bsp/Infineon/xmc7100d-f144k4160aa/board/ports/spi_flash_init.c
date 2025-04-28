/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-27      Hydevcode    first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_spi.h"
#include "dev_spi_msd.h"
#include <dfs_fs.h>

#ifdef BSP_USING_SPI_FLASH
static int rt_spi_flash_init(void)
{
    rt_hw_spi_device_attach("spi5", "spi30", GET_PIN(7, 3));
    if (RT_NULL == msd_init("sd0", "spi30"))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_spi_flash_init);
#endif /* BSP_USING_SPI_FLASH */
