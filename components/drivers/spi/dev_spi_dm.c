/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-06     GuEe-GUI     first version
 */

#include "dev_spi_dm.h"

#define DBG_TAG "spi.dm"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_OFW
static void ofw_parse_delay(struct rt_ofw_node *np, struct rt_spi_delay *delay,
        const char *prop)
{
    rt_uint32_t value;

    if (!rt_ofw_prop_read_u32(np, prop, &value))
    {
        if (value > RT_UINT16_MAX)
        {
            delay->value = RT_DIV_ROUND_UP(value, 1000);
            delay->unit = RT_SPI_DELAY_UNIT_USECS;
        }
        else
        {
            delay->value = value;
            delay->unit = RT_SPI_DELAY_UNIT_NSECS;
        }
    }
}

rt_err_t spi_device_ofw_parse(struct rt_spi_device *spi_dev)
{
    rt_err_t err;
    rt_uint32_t value;
    struct rt_spi_bus *spi_bus = spi_dev->bus;
    struct rt_ofw_node *np = spi_dev->parent.ofw_node;
    struct rt_spi_configuration *conf = &spi_dev->config;

    if (rt_ofw_prop_read_bool(np, "spi-cpha"))
    {
        conf->mode |= RT_SPI_CPHA;
    }
    if (rt_ofw_prop_read_bool(np, "spi-cpol"))
    {
        conf->mode |= RT_SPI_CPOL;
    }
    if (rt_ofw_prop_read_bool(np, "spi-3wire"))
    {
        conf->mode |= RT_SPI_3WIRE;
    }
    if (rt_ofw_prop_read_bool(np, "spi-lsb-first"))
    {
        conf->mode |= RT_SPI_LSB;
    }
    if (rt_ofw_prop_read_bool(np, "spi-cs-high"))
    {
        conf->mode |= RT_SPI_CS_HIGH;
    }

    value = 1;
    rt_ofw_prop_read_u32(np, "spi-tx-bus-width", &value);
    conf->data_width_tx = value;

    value = 1;
    rt_ofw_prop_read_u32(np, "spi-rx-bus-width", &value);
    conf->data_width_rx = value;

    if (spi_bus->slave)
    {
        if (!rt_ofw_node_tag_equ(np, "slave"))
        {
            LOG_E("Invalid SPI device = %s", rt_ofw_node_full_name(np));

            return -RT_EINVAL;
        }

        return RT_EOK;
    }

    if ((err = rt_ofw_prop_read_u32(np, "reg", &value)))
    {
        LOG_E("Find 'reg' failed");

        return err;
    }
    spi_dev->chip_select = value;

    if (!rt_ofw_prop_read_u32(np, "spi-max-frequency", &value))
    {
        conf->max_hz = value;
    }

    ofw_parse_delay(np, &spi_dev->cs_setup, "spi-cs-setup-delay-ns");
    ofw_parse_delay(np, &spi_dev->cs_hold, "spi-cs-hold-delay-ns");
    ofw_parse_delay(np, &spi_dev->cs_inactive, "spi-cs-inactive-delay-ns");

    return RT_EOK;
}
#endif /* RT_USING_OFW */
