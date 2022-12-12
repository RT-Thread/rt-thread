/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
 */

#include "drv_spi.h"
#include "board.h"
int w5500_spi_device_init(void)
{
    return rt_hw_spi_device_attach(WIZ_SPI_BUS,WIZ_SPI_DEVICE, WIZ_SPI_CS);
}
INIT_DEVICE_EXPORT(w5500_spi_device_init);
