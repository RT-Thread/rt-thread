/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-03-28      qiujingbao   first version
 */

#include "drv_spi.h"

#define DBG_TAG "drv.spi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static struct cv1800_spi cv1800_spi_obj[] =
{
#ifdef BSP_USING_SPI
    {
        .spi_id = SPI2,
        .device_name = "spi2",
        .fifo_len = SPI_TXFTLR,
    },
#endif
};

static struct spi_regs *get_spi_base(uint8_t spi_id)
{
    struct spi_regs *spi_base = NULL;

    switch (spi_id)
    {
    case SPI0:
        spi_base = (struct spi_regs *)SPI0_BASE;
        break;
    case SPI1:
        spi_base = (struct spi_regs *)SPI1_BASE;
        break;
    case SPI2:
        spi_base = (struct spi_regs *)SPI2_BASE;
        break;
    case SPI3:
        spi_base = (struct spi_regs *)SPI3_BASE;
        break;
    }

    return spi_base;
}

static rt_err_t drv_spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration)
{
    rt_err_t ret = RT_EOK;
    struct cv1800_spi *spi_dev = RT_NULL;
    uint32_t mode;

    spi_dev = (struct cv1800_spi *)(device->bus->parent.user_data);

    spi_dev->data_width = configuration->data_width;

    /* disable spi */
    spi_enable(spi_dev->reg, 0);

    /* clear irq */
    spi_clear_irq(spi_dev->reg, SPI_IRQ_MSAK);

    /* set clk */
    ret = spi_set_frequency(spi_dev->reg, configuration->max_hz);
    if (ret)
        return ret;

    /* set mode */
    ret = gen_spi_mode(configuration, &mode);
    if (ret)
        return ret;

    spi_set_mode(spi_dev->reg, mode);

    /* set cs */
    spi_enable_cs(spi_dev->reg, 0x1);

    spi_enable(spi_dev->reg, 0x1);

    mode = mmio_read_32((uintptr_t)&spi_dev->reg->spi_ctrl0);
    LOG_D("mode: %x", mode);
    mode = mmio_read_32((uintptr_t)&spi_dev->reg->spi_baudr);
    LOG_D("spi_baudr: %x", mode);

    return ret;
}

int hw_spi_recv(struct cv1800_spi *dev) {
    uint32_t rever;
    uint32_t tem;
    int ret;

    rever = mmio_read_32((uintptr_t)&dev->reg->spi_rxflr);
    ret = (int)rever;

    while (rever)
    {
        tem = mmio_read_32((uintptr_t)&dev->reg->spi_dr);

        if (dev->recv_buf < dev->recv_end)
        {
            if (dev->data_width == 8)
                *(uint8_t *)(dev->recv_buf) = tem;
            else
                *(uint16_t *)(dev->recv_buf) = tem;
        }
        else
        {
            return 0;
        }

        rever--;
        dev->recv_buf += dev->data_width >> 3;
    }
    return ret;
}

int hw_spi_send(struct cv1800_spi *dev) {
    uint32_t txflr;
    uint32_t max;
    uint16_t value;

    txflr = mmio_read_32((uintptr_t)&dev->reg->spi_txflr);
    max = dev->fifo_len - txflr;

    while (max)
    {
        if (dev->send_end - dev->send_buf)
        {
            if (dev->data_width == 8)
                value = *(uint8_t *)(dev->send_buf);
            else
                value = *(uint16_t *)(dev->send_buf);
        }
        else
        {
            return 0;
        }

        mmio_write_32((uintptr_t)&dev->reg->spi_dr, value);
        dev->send_buf += dev->data_width >> 3;
        max--;
    }

    return 0;
}
static rt_ssize_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message) {
    int ret = 0;
    struct cv1800_spi *spi_dev;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    spi_dev = (struct cv1800_spi *)(device->bus->parent.user_data);

    if (message->send_buf != RT_NULL)
    {
        spi_dev->send_buf = message->send_buf;
        spi_dev->send_end = (void *)((uint8_t *)spi_dev->send_buf + message->length);
    }

    if (message->recv_buf != RT_NULL)
    {
        spi_dev->recv_buf = message->recv_buf;
        spi_dev->recv_end = (void *)((uint8_t *)spi_dev->recv_buf + message->length);
    }

    /* if user use their cs */
    if (message->cs_take && device->cs_pin != PIN_NONE)
        rt_pin_write(device->cs_pin, PIN_LOW);

    if (message->send_buf)
    {
        while (spi_dev->send_buf != spi_dev->send_end)
        {
            hw_spi_send(spi_dev);
        }

        /* wait for complete */
        while (mmio_read_32((uintptr_t)&spi_dev->reg->spi_txflr)) {}

        ret = message->length;
    }

    if (message->recv_buf)
    {
        while (spi_dev->recv_buf != spi_dev->recv_end)
        {
            hw_spi_recv(spi_dev);
        }

        ret = message->length;
    }

    if (message->cs_release && device->cs_pin != PIN_NONE)
        rt_pin_write(device->cs_pin, PIN_HIGH);

    return ret;
}

const static struct rt_spi_ops drv_spi_ops =
{
    drv_spi_configure,
    spixfer,
};

int rt_hw_spi_init(void)
{
    rt_err_t ret = RT_EOK;
    struct spi_regs *reg = NULL;

    for (rt_size_t i = 0; i < sizeof(cv1800_spi_obj) / sizeof(struct cv1800_spi); i++) {
        /* set reg base addr */
        reg = get_spi_base(cv1800_spi_obj[i].spi_id);
        if (!reg)
            return -RT_ERROR;

        cv1800_spi_obj[i].reg = reg;
        cv1800_spi_obj[i].spi_bus.parent.user_data = &cv1800_spi_obj[i];

        /* register spix bus */
        ret = rt_spi_bus_register(&cv1800_spi_obj[i].spi_bus, cv1800_spi_obj[i].device_name, &drv_spi_ops);
    }

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_spi_init);
