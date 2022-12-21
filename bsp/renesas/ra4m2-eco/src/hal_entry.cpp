/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-7      Vandoul      first version.
 */
#include "rtthread.h"
#include "drivers/pin.h"
#include "hal_data.h"
#include "drivers/spi.h"
#ifdef __cplusplus
extern "C"{
#endif
#include "bsp_api.h"
#include "spi_msd.h"
#ifdef __cplusplus
}
#endif

static struct rt_spi_device sd_device;

void hal_entry(void)
{
    rt_kprintf("hal_entry run.\r\n");
    rt_pin_mode(BSP_IO_PORT_04_PIN_04, PIN_MODE_OUTPUT);
    rt_kprintf("init spi sdcard.\r\n");
    rt_pin_mode(BSP_IO_PORT_06_PIN_03, PIN_MODE_OUTPUT);
    if(RT_EOK == rt_spi_bus_attach_device(&sd_device, "scpi9-0", "scpi9", (void *)BSP_IO_PORT_06_PIN_03)) {
        if(RT_EOK != msd_init("sd0", "scpi9-0")) {
            rt_kprintf("msd init failed!\r\n");
        }
    } else {
        rt_kprintf("spi bus attach failed!\r\n");
    }
    
    while (1)
    {
        rt_pin_write(BSP_IO_PORT_04_PIN_04, !rt_pin_read(BSP_IO_PORT_04_PIN_04));
        rt_thread_mdelay(1000);
    }
}

