/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-31     BruceOu      first implementation
 * 2023-06-03     CX           fixed sf probe error bug
 * 2024-05-30     godmial      refactor driver for multi-SPI bus auto-mount
 */
#include <board.h>
#include "drv_spi.h"
#include "dev_spi_flash.h"

#ifdef RT_USING_SFUD
#include "dev_spi_flash_sfud.h"
#endif

#include <rthw.h>
#include <finsh.h>

#ifdef RT_USING_DFS
#include <dfs_fs.h>
#endif

struct spi_flash_config
{
    const char *bus_name;
    const char *device_name;
    const char *flash_name;
    rt_base_t   cs_pin;
};

static const struct spi_flash_config flash_configs[] =
{
#ifdef BSP_USING_SPI0
    {
        .bus_name    = "spi0",
        .device_name = "spi00",
        .flash_name  = "gd25q_spi0",
        .cs_pin      = GET_PIN(A, 4),
    },
#endif

#ifdef BSP_USING_SPI1
    {
        .bus_name    = "spi1",
        .device_name = "spi10",
        .flash_name  = "gd25q_spi1",
        .cs_pin      = GET_PIN(B, 9),
    },
#endif

#ifdef BSP_USING_SPI2
    {
        .bus_name    = "spi2",
        .device_name = "spi20",
        .flash_name  = "gd25q_spi2",
        .cs_pin      = GET_PIN(B, 12),
    },
#endif

#ifdef BSP_USING_SPI3
    {
        .bus_name    = "spi3",
        .device_name = "spi30",
        .flash_name  = "gd25q_spi3",
        .cs_pin      = GET_PIN(E, 4),
    },
#endif

#ifdef BSP_USING_SPI4
    {
        .bus_name    = "spi4",
        .device_name = "spi40",
        .flash_name  = "gd25q_spi4",
        .cs_pin      = GET_PIN(F, 6),
    },
#endif
};


static int spi_flash_init(void)
{
    int result = RT_EOK;

    for (size_t i = 0; i < sizeof(flash_configs) / sizeof(flash_configs[0]); i++)
    {
        const struct spi_flash_config *cfg = &flash_configs[i];

        result = rt_hw_spi_device_attach(cfg->bus_name, cfg->device_name, cfg->cs_pin);
        if (result != RT_EOK)
        {
            rt_kprintf("Failed to attach device %s on bus %s\n", cfg->device_name, cfg->bus_name);
            continue;
        }

#ifdef RT_USING_SFUD
        if (RT_NULL == rt_sfud_flash_probe(cfg->flash_name, cfg->device_name))
        {
            rt_kprintf("SFUD probe failed: %s\n", cfg->flash_name);
            continue;
        }
#endif
    }

    return result;
}
INIT_COMPONENT_EXPORT(spi_flash_init);
