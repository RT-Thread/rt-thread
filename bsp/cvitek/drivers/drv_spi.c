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
#include "drv_pinmux.h"

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

#if defined(BOARD_TYPE_MILKV_DUO) || defined(BOARD_TYPE_MILKV_DUO_SPINOR) || defined(BOARD_TYPE_MILKV_DUO256M) || defined(BOARD_TYPE_MILKV_DUO256M_SPINOR)

#ifdef BSP_USING_SPI0
static const char *pinname_whitelist_spi0_sck[] = {
    NULL,
};
static const char *pinname_whitelist_spi0_sdo[] = {
    NULL,
};
static const char *pinname_whitelist_spi0_sdi[] = {
    NULL,
};
static const char *pinname_whitelist_spi0_cs[] = {
    NULL,
};
#endif

#ifdef BSP_USING_SPI1
static const char *pinname_whitelist_spi1_sck[] = {
    NULL,
};
static const char *pinname_whitelist_spi1_sdo[] = {
    NULL,
};
static const char *pinname_whitelist_spi1_sdi[] = {
    NULL,
};
static const char *pinname_whitelist_spi1_cs[] = {
    NULL,
};
#endif

#ifdef BSP_USING_SPI2
static const char *pinname_whitelist_spi2_sck[] = {
    "SD1_CLK",
    NULL,
};
static const char *pinname_whitelist_spi2_sdo[] = {
    "SD1_CMD",
    NULL,
};
static const char *pinname_whitelist_spi2_sdi[] = {
    "SD1_D0",
    NULL,
};
static const char *pinname_whitelist_spi2_cs[] = {
    "SD1_D3",
    NULL,
};
#endif

#ifdef BSP_USING_SPI3
static const char *pinname_whitelist_spi3_sck[] = {
    NULL,
};
static const char *pinname_whitelist_spi3_sdo[] = {
    NULL,
};
static const char *pinname_whitelist_spi3_sdi[] = {
    NULL,
};
static const char *pinname_whitelist_spi3_cs[] = {
    NULL,
};
#endif

#else
    #error "Unsupported board type!"
#endif

static void rt_hw_spi_pinmux_config()
{
#ifdef BSP_USING_SPI0
    pinmux_config(BSP_SPI0_SCK_PINNAME, SPI0_SCK,  pinname_whitelist_spi0_sck);
    pinmux_config(BSP_SPI0_SDO_PINNAME, SPI0_SDO,  pinname_whitelist_spi0_sdo);
    pinmux_config(BSP_SPI0_SDI_PINNAME, SPI0_SDI,  pinname_whitelist_spi0_sdi);
    pinmux_config(BSP_SPI0_CS_PINNAME,  SPI0_CS_X, pinname_whitelist_spi0_cs);
#endif /* BSP_USING_SPI0 */

#ifdef BSP_USING_SPI1
    pinmux_config(BSP_SPI1_SCK_PINNAME, SPI1_SCK,  pinname_whitelist_spi1_sck);
    pinmux_config(BSP_SPI1_SDO_PINNAME, SPI1_SDO,  pinname_whitelist_spi1_sdo);
    pinmux_config(BSP_SPI1_SDI_PINNAME, SPI1_SDI,  pinname_whitelist_spi1_sdi);
    pinmux_config(BSP_SPI1_CS_PINNAME,  SPI1_CS_X, pinname_whitelist_spi1_cs);
#endif /* BSP_USING_SPI1 */

#ifdef BSP_USING_SPI2
    pinmux_config(BSP_SPI2_SCK_PINNAME, SPI2_SCK,  pinname_whitelist_spi2_sck);
    pinmux_config(BSP_SPI2_SDO_PINNAME, SPI2_SDO,  pinname_whitelist_spi2_sdo);
    pinmux_config(BSP_SPI2_SDI_PINNAME, SPI2_SDI,  pinname_whitelist_spi2_sdi);
    pinmux_config(BSP_SPI2_CS_PINNAME,  SPI2_CS_X, pinname_whitelist_spi2_cs);
#endif /* BSP_USING_SPI2 */

#ifdef BSP_USING_SPI3
    pinmux_config(BSP_SPI3_SCK_PINNAME, SPI3_SCK,  pinname_whitelist_spi3_sck);
    pinmux_config(BSP_SPI3_SDO_PINNAME, SPI3_SDO,  pinname_whitelist_spi3_sdo);
    pinmux_config(BSP_SPI3_SDI_PINNAME, SPI3_SDI,  pinname_whitelist_spi3_sdi);
    pinmux_config(BSP_SPI3_CS_PINNAME,  SPI3_CS_X, pinname_whitelist_spi3_cs);
#endif /* BSP_USING_SPI3 */
}

int rt_hw_spi_init(void)
{
    rt_err_t ret = RT_EOK;
    struct spi_regs *reg = NULL;

    rt_hw_spi_pinmux_config();

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
