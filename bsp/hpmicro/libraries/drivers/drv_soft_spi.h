/*
 * Copyright (c) 2026 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __DRV_SOFT_SPI__
#define __DRV_SOFT_SPI__

#include <rtthread.h>
#ifdef BSP_USING_SOFT_SPI
#include <rthw.h>
#include <rtdevice.h>
/* rt_spi_bit_ops is defined in dev_spi_bit_ops.h */
#include <dev_spi_bit_ops.h>

/* HPM config class */
struct hpm_soft_spi_config
{
    const char  *sck_pin_name;
    const char  *mosi_pin_name;
    const char  *miso_pin_name;
    const char  *bus_name;
};

/* HPM spi driver class */
struct hpm_soft_spi
{
    struct rt_spi_bit_obj spi;    /* bit-banged spi object (contains rt_spi_bus inside) */
    struct rt_spi_bit_ops ops;   /* local copy of bit ops */
    void *cfg;                   /* pointer to hpm_soft_spi_config */
};

int rt_hw_spi_init(void);
rt_err_t rt_hw_soft_spi_device_attach(const char *bus_name, const char *device_name, const char *pin_name);
#endif /* BSP_USING_SOFT_SPI */

#endif /* __DRV_SOFT_SPI__ */
