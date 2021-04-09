/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-01-01     aozima       first implementation.
 * 2018-03-30     misonyo      porting to gd32f30x
 */
#include <board.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "spi_flash.h"
#include "spi_flash_sfud.h"

#define SPI_BUS_NAME                "spi0"
#define SPI_DEVICE_NAME             "spi01"
#define SPI_FLASH_DEVICE_NAME       "gd25q"
#define GD25Q_SPI_CS_PIN             2          //PE3，在 drv_gpio.c 文件 pin_index pins[]中查到 PE3 编号为 2

static int rt_hw_gd25q40_init(void)
{
    rt_err_t res;
    static struct rt_spi_device spi_dev_gd25q;           /* SPI设备对象 */
    static rt_base_t gd25q_cs_pin;                       /* SPI设备CS片选引脚 */

    gd25q_cs_pin = GD25Q_SPI_CS_PIN;

    rt_pin_mode(GD25Q_SPI_CS_PIN, GPIO_MODE_OUT_PP);

    res = rt_spi_bus_attach_device(&spi_dev_gd25q, SPI_DEVICE_NAME, SPI_BUS_NAME, (void*)gd25q_cs_pin);
    if (res != RT_EOK)
    {
        rt_kprintf("rt_spi_bus_attach_device() run failed!\n");
        return res;
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_gd25q40_init);

static int rt_hw_spi_flash_with_sfud_init(void)
{
    if (RT_NULL == rt_sfud_flash_probe(SPI_FLASH_DEVICE_NAME, SPI_DEVICE_NAME))
    {
        return RT_ERROR;
    }

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_spi_flash_with_sfud_init);

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
