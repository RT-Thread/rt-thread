/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author          Notes
 * 2020-05-19       Sherman         first version
 * 2023-01-28       Andrew          add Nrf5340 support
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>

#ifndef __DRV_SPI_H_
#define __DRV_SPI_H_

#ifdef BSP_USING_SPI
#if defined(SOC_NRF5340)
#include "nrfx_spim.h"

/**
 * @brief Attach the spi device to SPI bus, this function must be used after initialization.
 * @param bus_name     spi bus name  "spi0"/"spi1"/"spi2"
 * @param device_name  spi device name "spi0x"/"spi1x"/"spi2x"
 * @param ss_pin       spi ss pin number
 * @retval  -RT_ERROR / RT_EOK
*/
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint32_t ss_pin);

//SPI bus config
#ifdef BSP_USING_SPI0
#define NRFX_SPI0_CONFIG         \
{                                \
    .bus_name = "spi0",          \
    .spi = NRFX_SPIM_INSTANCE(0)  \
}
#endif
#ifdef BSP_USING_SPI1
#define NRFX_SPI1_CONFIG         \
{                                \
    .bus_name = "spi1",          \
    .spi = NRFX_SPIM_INSTANCE(1)  \
}
#endif

#ifdef BSP_USING_SPI2
#define NRFX_SPI2_CONFIG         \
{                                \
    .bus_name = "spi2",          \
    .spi = NRFX_SPIM_INSTANCE(2)  \
}
#endif

#ifdef BSP_USING_SPI3
#define NRFX_SPI3_CONFIG         \
{                                \
    .bus_name = "spi3",          \
    .spi = NRFX_SPIM_INSTANCE(3)  \
}
#endif
#ifdef BSP_USING_SPI4
#define NRFX_SPI4_CONFIG         \
{                                \
    .bus_name = "spi4",          \
    .spi = NRFX_SPIM_INSTANCE(4)  \
}
#endif

struct nrfx_drv_spi_config
{
    char *bus_name;
    nrfx_spim_t spi;
};

struct nrfx_drv_spi
{
    nrfx_spim_t spi;    /* nrfx spi driver instance. */
    nrfx_spim_config_t   spi_config; /* nrfx spi config Configuration */
    struct rt_spi_configuration *cfg;
    struct rt_spi_bus spi_bus;
};

struct nrfx_drv_spi_pin_config
{
    rt_uint8_t sck_pin;
    rt_uint8_t mosi_pin;
    rt_uint8_t miso_pin;
    rt_uint8_t ss_pin;
};
#else
#include "nrfx_spi.h"

/**
 * @brief Attach the spi device to SPI bus, this function must be used after initialization.
 * @param bus_name     spi bus name  "spi0"/"spi1"/"spi2"
 * @param device_name  spi device name "spi0x"/"spi1x"/"spi2x"
 * @param ss_pin       spi ss pin number
 * @retval  -RT_ERROR / RT_EOK
*/
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint32_t ss_pin);

//SPI bus config
#ifdef BSP_USING_SPI0
#define NRFX_SPI0_CONFIG         \
{                                \
    .bus_name = "spi0",          \
    .spi = NRFX_SPI_INSTANCE(0)  \
}
#endif
#ifdef BSP_USING_SPI1
#define NRFX_SPI1_CONFIG         \
{                                \
    .bus_name = "spi1",          \
    .spi = NRFX_SPI_INSTANCE(1)  \
}
#endif

#ifdef BSP_USING_SPI2
#define NRFX_SPI2_CONFIG         \
{                                \
    .bus_name = "spi2",          \
    .spi = NRFX_SPI_INSTANCE(2)  \
}
#endif

struct nrfx_drv_spi_config
{
    char *bus_name;
    nrfx_spi_t spi;
};

struct nrfx_drv_spi
{
    nrfx_spi_t spi;    /* nrfx spi driver instance. */
    nrfx_spi_config_t   spi_config; /* nrfx spi config Configuration */
    struct rt_spi_configuration *cfg;
    struct rt_spi_bus spi_bus;
};

struct nrfx_drv_spi_pin_config
{
    rt_uint8_t sck_pin;
    rt_uint8_t mosi_pin;
    rt_uint8_t miso_pin;
    rt_uint8_t ss_pin;
};
#endif
#endif /* BSP_USING_SPI */
#endif  /*__DRV_SPI_H_*/
