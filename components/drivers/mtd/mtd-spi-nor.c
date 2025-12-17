/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "dev_spi_flash_sfud.h"

extern rt_err_t rt_spidev_device_init(struct rt_spi_device *dev, const char *name);

static rt_err_t spi_nor_flash_probe(struct rt_spi_device *spi_dev)
{
    rt_spi_flash_device_t flash;
    const char *dev_name = rt_dm_dev_get_name(&spi_dev->parent);
    const char *vendor = spi_dev->id ? spi_dev->id->name : "spi-nor";

    rt_spidev_device_init(spi_dev, dev_name);

    if (!(flash = rt_sfud_flash_probe(vendor, dev_name)))
    {
        /* Maybe is not support by SFUD now, user could access it later */
        return -RT_ENOSYS;
    }

    rt_dm_dev_set_name_auto(&flash->flash_device, "nor");

    return RT_EOK;
}

static const struct rt_spi_device_id spi_nor_flash_ids[] =
{
    /*
     * Allow non-DT platform devices to bind to the "spi-nor" modalias, and
     * hack around the fact that the SPI core does not provide uevent
     * matching for .ofw_ids
     */
    { "spi-nor" },

    /*
     * Entries not used in DTs that should be safe to drop after replacing
     * them with "spi-nor" in platform data.
     */
    { "s25sl064a" }, { "w25x16" }, { "m25p10" }, { "m25px64" },

    /*
     * Entries that were used in DTs without "jedec,spi-nor" fallback and
     * should be kept for backward compatibility.
     */
    { "at25df321a" }, { "at25df641" }, { "at26df081a" },
    { "mx25l4005a" }, { "mx25l1606e" }, { "mx25l6405d" }, { "mx25l12805d" },
    { "mx25l25635e" }, { "mx66l51235l" },
    { "n25q064" }, { "n25q128a11" }, { "n25q128a13" }, { "n25q512a" },
    { "s25fl256s1" }, { "s25fl512s" }, { "s25sl12801" }, { "s25fl008k" },
    { "s25fl064k" },
    { "sst25vf040b" }, { "sst25vf016b" }, { "sst25vf032b" }, { "sst25wf040" },
    { "m25p40" }, { "m25p80" }, { "m25p16" }, { "m25p32" },
    { "m25p64" }, { "m25p128" },
    { "w25x80" }, { "w25x32" }, { "w25q32" }, { "w25q32dw" },
    { "w25q80bl" }, { "w25q128" }, { "w25q256" },

    /* Flashes that can't be detected using JEDEC */
    { "m25p05-nonjedec" }, { "m25p10-nonjedec" }, { "m25p20-nonjedec" },
    { "m25p40-nonjedec" }, { "m25p80-nonjedec" }, { "m25p16-nonjedec" },
    { "m25p32-nonjedec" }, { "m25p64-nonjedec" }, { "m25p128-nonjedec" },

    /* Everspin MRAMs (non-JEDEC) */
    { "mr25h128" }, /* 128 Kib, 40 MHz */
    { "mr25h256" }, /* 256 Kib, 40 MHz */
    { "mr25h10" },  /*   1 Mib, 40 MHz */
    { "mr25h40" },  /*   4 Mib, 40 MHz */
    { /* sentinel */ },
};

static const struct rt_ofw_node_id spi_nor_flash_ofw_ids[] =
{
    /*
     * Generic compatibility for SPI NOR that can be identified by the
     * JEDEC READ ID opcode (0x9F). Use this, if possible.
     */
    { .compatible = "jedec,spi-nor" },
    { /* sentinel */ }
};

static struct rt_spi_driver spi_nor_flash_driver =
{
    .ids = spi_nor_flash_ids,
    .ofw_ids = spi_nor_flash_ofw_ids,

    .probe = spi_nor_flash_probe,
};
RT_SPI_DRIVER_EXPORT(spi_nor_flash_driver);
