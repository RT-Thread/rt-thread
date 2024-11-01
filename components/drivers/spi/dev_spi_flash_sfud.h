/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-09-28     armink       first version.
 */

#ifndef __DEV_SPI_FLASH_SFUD_H__
#define __DEV_SPI_FLASH_SFUD_H__

#include <rtthread.h>
#include <rtdevice.h>
#include "./sfud/inc/sfud.h"
#include "dev_spi_flash.h"

/**
 * Probe SPI flash by SFUD(Serial Flash Universal Driver) driver library and though SPI device.
 *
 * @param spi_flash_dev_name the name which will create SPI flash device
 * @param spi_dev_name using SPI device name
 *
 * @return probed SPI flash device, probe failed will return RT_NULL
 */
rt_spi_flash_device_t rt_sfud_flash_probe(const char *spi_flash_dev_name, const char *spi_dev_name);

/**
 * Probe SPI flash by SFUD (Serial Flash Universal Driver) driver library and though SPI device by specified configuration.
 *
 * @param spi_flash_dev_name the name which will create SPI flash device
 * @param spi_dev_name using SPI device name
 * @param spi_cfg SPI device configuration
 * @param qspi_cfg QSPI device configuration
 *
 * @return probed SPI flash device, probe failed will return RT_NULL
 */
rt_spi_flash_device_t rt_sfud_flash_probe_ex(const char *spi_flash_dev_name, const char *spi_dev_name,
        struct rt_spi_configuration *spi_cfg, struct rt_qspi_configuration *qspi_cfg);

/**
 * Delete SPI flash device
 *
 * @param spi_flash_dev SPI flash device
 *
 * @return the operation status, RT_EOK on successful
 */
rt_err_t rt_sfud_flash_delete(rt_spi_flash_device_t spi_flash_dev);

/**
 * Find sfud flash device by SPI device name
 *
 * @param spi_dev_name using SPI device name
 *
 * @return sfud flash device if success, otherwise return RT_NULL
 */
sfud_flash_t rt_sfud_flash_find(const char *spi_dev_name);

/**
 * Find sfud flash device by flash device name
 *
 * @param flash_dev_name using flash device name
 *
 * @return sfud flash device if success, otherwise return RT_NULL
 */
sfud_flash_t rt_sfud_flash_find_by_dev_name(const char *flash_dev_name);

#endif /* __DEV_SPI_FLASH_SFUD_H__ */
