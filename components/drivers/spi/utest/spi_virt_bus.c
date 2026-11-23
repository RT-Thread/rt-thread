/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-02                      add SPI virtual loopback bus for utest
 *
 * A pure-software SPI bus that feeds MOSI data back to MISO. It lets the
 * SPI loopback utest run on BSPs (such as qemu-vexpress-a9) which have no
 * real SPI controller wired to external pins.
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/dev_spi.h>

#ifdef RT_UTEST_SPI_VIRT_BUS

#ifndef RT_UTEST_SPI_VIRT_BUS_NAME
#define RT_UTEST_SPI_VIRT_BUS_NAME "spi_virt"
#endif

#define SPI_VIRT_BUS_NAME       RT_UTEST_SPI_VIRT_BUS_NAME
#define SPI_VIRT_BUS_MAX_HZ     10000000
#define SPI_VIRT_BUS_DEFAULT_HZ 1000000

static struct rt_spi_bus spi_virt_bus;

static rt_err_t spi_virt_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration)
{
    if (configuration->max_hz == 0)
    {
        configuration->max_hz = SPI_VIRT_BUS_DEFAULT_HZ;
    }

    if (configuration->max_hz > SPI_VIRT_BUS_MAX_HZ)
    {
        configuration->max_hz = SPI_VIRT_BUS_MAX_HZ;
    }

    device->config = *configuration;
    device->config.usage_freq = configuration->max_hz;

    return RT_EOK;
}

static rt_ssize_t spi_virt_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    rt_size_t i;

    if (message == RT_NULL)
    {
        return 0;
    }

    if (message->send_buf != RT_NULL && message->recv_buf != RT_NULL)
    {
        rt_memcpy(message->recv_buf, message->send_buf, message->length);
    }
    else if (message->send_buf != RT_NULL)
    {
        /* TX-only: drop the data, nothing to verify. */
    }
    else if (message->recv_buf != RT_NULL)
    {
        /* RX-only: fill with a deterministic pattern. */
        rt_uint8_t *rx = (rt_uint8_t *)message->recv_buf;

        for (i = 0; i < message->length; i++)
        {
            rx[i] = (rt_uint8_t)(0xA5 + i);
        }
    }

    return (rt_ssize_t)message->length;
}

static const struct rt_spi_ops spi_virt_ops = {
    .configure = spi_virt_configure,
    .xfer = spi_virt_xfer,
};

static int spi_virt_bus_init(void)
{
    return rt_spi_bus_register(&spi_virt_bus, SPI_VIRT_BUS_NAME, &spi_virt_ops);
}
INIT_BOARD_EXPORT(spi_virt_bus_init);

#endif /* RT_UTEST_SPI_VIRT_BUS */
