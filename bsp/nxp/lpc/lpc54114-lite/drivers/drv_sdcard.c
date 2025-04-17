/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "drv_sdcard.h"
#include "drv_spi.h"
#include "dev_spi_msd.h"

#define RT_SDCARD_CS_PIN (3)

int rt_hw_sdcard_init(void)
{
    rt_err_t ret;

    ret = lpc_spi_bus_attach_device("spi2", "spi21", RT_SDCARD_CS_PIN);
    if(ret != RT_EOK)
    {
        return ret;
    }

    ret = msd_init("sd0", "spi21");

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_sdcard_init);
