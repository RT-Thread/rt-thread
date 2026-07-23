/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-09-04     Yilin Sun    Initial version
 */

#include <rtdevice.h>

#include "fsl_spi.h"

#include "drv_spi.h"

#define BSP_DEFAULT_SPI_FREQUENCY (500000U)

typedef struct
{
    struct rt_spi_bus parent;
    SPI_Type *instance;
    uint32_t input_frequency;
} mcx_spi_obj_t;

typedef struct
{
    SPI_Type *instance;
    uint8_t id;
} mcx_spi_instance_t;

static const mcx_spi_instance_t mcx_spi_instances[] =
{
#ifdef BSP_USING_SPI0
    {SPI0, 0},
#endif
#ifdef BSP_USING_SPI1
    {SPI1, 1},
#endif
};

static mcx_spi_obj_t mcx_spi_list[ARRAY_SIZE(mcx_spi_instances)];

static rt_ssize_t mcx_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    spi_transfer_t xfer =
    {
        .txData = message->send_buf,
        .rxData = message->recv_buf,
        .dataSize = message->length,
        .flags = 0UL,
    };

    mcx_spi_obj_t *spi = device->bus->parent.user_data;

    if (message->cs_take)
    {
        rt_pin_write(device->cs_pin, PIN_LOW);
    }

    SPI_MasterTransferBlocking(spi->instance, &xfer);

    if (message->cs_release)
    {
        rt_pin_write(device->cs_pin, PIN_HIGH);
    }

    return message->length;
}

static rt_err_t mcx_spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg)
{
    mcx_spi_obj_t *spi = device->bus->parent.user_data;

    SPI_MasterSetBaudRate(spi->instance, cfg->max_hz, spi->input_frequency);

    return RT_EOK;
}

static struct rt_spi_ops mcx_spi_ops =
{
    .configure = mcx_spi_configure,
    .xfer = mcx_spi_xfer,
};

rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_uint32_t pin)
{
    struct rt_spi_device *spi_device = rt_malloc(sizeof(struct rt_spi_device));
    if (!spi_device)
    {
        return -RT_ENOMEM;
    }

    return rt_spi_bus_attach_device_cspin(spi_device, device_name, bus_name, pin, NULL);
}

int rt_hw_spi_init(void)
{
    for (size_t i = 0; i < ARRAY_SIZE(mcx_spi_instances); i++)
    {
        char name_buf[16];

        /* TODO: Initialize SPI interface here. */

        mcx_spi_list[i].instance = mcx_spi_instances[i].instance;
        mcx_spi_list[i].input_frequency = CLOCK_GetCoreSysClkFreq();

        mcx_spi_list[i].parent.parent.user_data = &mcx_spi_list[i];

        spi_master_config_t cfg;
        SPI_MasterGetDefaultConfig(&cfg);

        SPI_MasterInit(mcx_spi_list[i].instance, &cfg, mcx_spi_list[i].input_frequency);

        rt_snprintf(name_buf, sizeof(name_buf), "spi%d", mcx_spi_instances[i].id);
        rt_spi_bus_register(&mcx_spi_list[i].parent, name_buf, &mcx_spi_ops);
    }

    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_spi_init);
