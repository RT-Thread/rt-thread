/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-08     Carl        the first version
 */

#include <board.h>
#include <drv_qspi.h>
#include <rtdevice.h>
#include <rthw.h>
#include <finsh.h>

#ifdef BSP_USE_QSPI

#include "dev_spi_flash.h"
#include "dev_spi_flash_sfud.h"
#define _QSPI_DEVICE_NAME "qspiflash"

static int
rt_hw_qspi_flash_with_sfud_init(void)
{
    ft2004_qspi_bus_attach_device(FT2004_QSPI_NAME, _QSPI_DEVICE_NAME, 1, RT_NULL, RT_NULL);

    /* init gd */
    rt_kprintf("start rt_sfud_flash_probe \r\n");
    if (RT_NULL == rt_sfud_flash_probe("GD25LQ256D", _QSPI_DEVICE_NAME))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_qspi_flash_with_sfud_init);

#endif /* BSP_USING_QSPI_FLASH */
