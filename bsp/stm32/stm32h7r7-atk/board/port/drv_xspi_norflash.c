/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-11     stackyuan  the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <fal.h>
static int rt_norflash_init(void)
{
//    extern rt_spi_flash_device_t rt_sfud_flash_probe(const char *spi_flash_dev_name, const char *spi_dev_name);
//    extern int fal_init(void);

//    rt_hw_spi_device_attach("spi1", "spi10", GPIOA, GPIO_PIN_4);

    /* initialize SPI Flash device */
//    rt_sfud_flash_probe("norflash0", "spi10");

    fal_init();

    return 0;
}
#ifndef FIRMWARE_EXEC_USING_QEMU
INIT_ENV_EXPORT(rt_norflash_init);
#endif
