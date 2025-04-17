/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-31     BruceOu      first implementation
 * 2023-06-03     CX           fixed sf probe error bug
 */
#include <board.h>
#include "drv_spi.h"
#include "dev_spi_flash.h"

#ifdef RT_USING_SFUD
#include "dev_spi_flash_sfud.h"
#endif

#include <rthw.h>
#include <finsh.h>

#define SPI_BUS_NAME                "spi0"
#define SPI_DEVICE_NAME             "spi01"
#define SPI_FLASH_DEVICE_NAME       "gd25q"

#define GD25Q_SPI_CS_GPIOX_CLK   RCU_GPIOE
#define GD25Q_SPI_CS_GPIOX       GPIOE
#define GD25Q_SPI_CS_GPIOX_PIN_X GPIO_PIN_3

static int rt_hw_spi_flash_init(void)
{
    rt_err_t res;
    static struct rt_spi_device spi_dev_gd25q;           /* SPI device */
    static struct gd32_spi_cs  spi_cs;
    spi_cs.GPIOx = GD25Q_SPI_CS_GPIOX;
    spi_cs.GPIO_Pin = GD25Q_SPI_CS_GPIOX_PIN_X;

    rcu_periph_clock_enable(GD25Q_SPI_CS_GPIOX_CLK);
#if defined SOC_SERIES_GD32F4xx
    gpio_mode_set(spi_cs.GPIOx, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, spi_cs.GPIO_Pin);
    gpio_output_options_set(spi_cs.GPIOx, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, spi_cs.GPIO_Pin);

    gpio_bit_set(spi_cs.GPIOx, spi_cs.GPIO_Pin);
#else
    gpio_init(spi_cs.GPIOx, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, spi_cs.GPIO_Pin);

#endif
    res = rt_spi_bus_attach_device(&spi_dev_gd25q, SPI_FLASH_DEVICE_NAME, SPI_BUS_NAME, (void*)&spi_cs);

    if (res != RT_EOK)
    {
        rt_kprintf("rt_spi_bus_attach_device() run failed!\n");
        return res;
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_spi_flash_init);

#ifdef RT_USING_SFUD
static int rt_hw_spi_flash_with_sfud_init(void)
{
    if (RT_NULL == rt_sfud_flash_probe(SPI_FLASH_DEVICE_NAME, SPI_DEVICE_NAME))
    {
        return -RT_ERROR;
    };

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_with_sfud_init)
#endif

#ifdef RT_USING_DFS
#include <dfs_fs.h>

int mnt_init(void)
{
    if (dfs_mount(SPI_FLASH_DEVICE_NAME, "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("spi flash mount success !\n");
    }
    else
    {
        rt_kprintf("spi flash mount failed!\n");
    }

    return 0;
}
MSH_CMD_EXPORT(mnt_init, mount spi flash to file system);
#endif
