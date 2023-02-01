/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-27     zylx         first version
 */

#include <board.h>
#include <drv_spi.h>
#include <rtdevice.h>
#include <rthw.h>
#include <finsh.h>

#ifdef BSP_USING_SPI_LCD

static int rt_hw_spi_lcd_init(void)
{
    rt_hw_spi_device_attach("spi1", "spi10", GET_PIN(A, 4));

    return RT_EOK;
}
INIT_PREV_EXPORT(rt_hw_spi_lcd_init);

#endif/* BSP_USING_SPI_LCD */
