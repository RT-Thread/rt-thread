/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-30     Emuzit            first version
 */
#include <rthw.h>
#include <drivers/spi.h>
#include <drivers/pin.h>
#include "ch56x_spi.h"
#include "ch56x_sys.h"

#if !defined(BSP_USING_SPI0) && !defined(BSP_USING_SPI1)
    #error "Please define at least one SPIx"
#endif

struct spi_bus
{
    struct rt_spi_bus parent;
    volatile struct spi_registers *reg_base;
    irq_number_t irqn;
    char *name;
    rt_base_t sck_pin;
    rt_base_t mosi_pin;
    rt_base_t miso_pin;
};

#ifdef BSP_USING_SPI0
static struct spi_bus spi_bus_0 =
{
    .reg_base = (struct spi_registers *)SPI0_REG_BASE,
    .irqn = SPI0_IRQn,
    .name = SPI0_BUS_NAME,
    .sck_pin = SPI0_SCK_PIN,
    .mosi_pin = SPI0_MOSI_PIN,
    .miso_pin = SPI0_MISO_PIN,
};
#endif
#ifdef BSP_USING_SPI1
static struct spi_bus spi_bus_1 =
{
    .reg_base = (struct spi_registers *)SPI1_REG_BASE,
    .irqn = SPI1_IRQn,
    .name = SPI1_BUS_NAME,
    .sck_pin = SPI1_SCK_PIN,
    .mosi_pin = SPI1_MOSI_PIN,
    .miso_pin = SPI1_MISO_PIN,
};
#endif

static uint8_t _spi_pin_config(struct rt_spi_device *device, struct rt_spi_configuration *config)
{
    struct spi_bus *spi_bus = (struct spi_bus *)device->bus;

    uint8_t mode;

    /* RT_SPI_3WIRE means SI/SO pin shared */
    mode = config->mode & (RT_SPI_MASTER | RT_SPI_SLAVE | RT_SPI_3WIRE);
    if (mode == RT_SPI_MASTER)
    {
        mode = RB_SPI_MOSI_OE | RB_SPI_SCK_OE;
        rt_pin_mode(spi_bus->mosi_pin, PIN_MODE_OUTPUT);
        rt_pin_mode(spi_bus->sck_pin, PIN_MODE_OUTPUT);
    }
    else if (mode == RT_SPI_SLAVE)
    {
        mode = RB_SPI_MISO_OE | RB_SPI_MODE_SLAVE;
        rt_pin_mode(spi_bus->miso_pin, PIN_MODE_OUTPUT);
    }
    else if (mode == RT_SPI_MASTER | RT_SPI_3WIRE)
    {
        mode = RB_SPI_2WIRE_MOD | RB_SPI_MISO_OE | RB_SPI_SCK_OE;
        rt_pin_mode(spi_bus->miso_pin, PIN_MODE_INPUT);
        rt_pin_mode(spi_bus->sck_pin, PIN_MODE_OUTPUT);
    }
    else
    {
        mode = RB_SPI_2WIRE_MOD | RB_SPI_MISO_OE | RB_SPI_MODE_SLAVE;
        rt_pin_mode(spi_bus->miso_pin, PIN_MODE_INPUT);
    }

    return mode;
}

static rt_err_t spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *config)
{
    volatile struct spi_registers *sxreg;
    struct rt_spi_device *owner;

    union _spi_ctrl_mod ctrl_mod;
    uint8_t mode;
    uint32_t Fsys;
    uint32_t div;

    rt_base_t cs_pin;
    int inactive;

    RT_ASSERT(device != RT_NULL);

    /* ch56x SPI supports only 8-bit data */
    if (config->data_width != 8)
        return -RT_EINVAL;

    ctrl_mod.reg = _spi_pin_config(device, config);

    /* ch56x SPI supports only mode 0 & mode 3 */
    mode = config->mode & (RT_SPI_CPOL | RT_SPI_CPHA);
    if (mode == RT_SPI_MODE_0)
        ctrl_mod.mst_sck_mod = MST_SCK_MOD_0;
    else if (mode == RT_SPI_MODE_3)
        ctrl_mod.mst_sck_mod = MST_SCK_MOD_3;
    else
        return -RT_EINVAL;

    /* CLOCK_DIV is 8-bit, reject excessively low max_hz */
    Fsys = sys_hclk_get();
    if (config->max_hz < Fsys / 255)
        return -RT_EINVAL;

    /* minimum allowable CLOCK_DIV is 2 */
    div = (Fsys + config->max_hz - 1) / config->max_hz;
    if (div < 2)
        div = 2;

    sxreg = ((struct spi_bus *)device->bus)->reg_base;
    sxreg->CLOCK_DIV = div;

    mode = config->mode & (RT_SPI_MSB | RT_SPI_LSB);
    sxreg->CTRL_CFG.reg = (mode == RT_SPI_MSB) ? 0 : RB_SPI_BIT_ORDER;
    sxreg->INTER_EN.reg = 0;

    ctrl_mod.all_clear = 1;
    sxreg->CTRL_MOD.reg = ctrl_mod.reg;
    ctrl_mod.all_clear = 0;
    sxreg->CTRL_MOD.reg = ctrl_mod.reg;

    mode = config->mode & (RT_SPI_MASTER | RT_SPI_SLAVE);
    if (mode == RT_SPI_MASTER)
    {
        /* get bus owner before this configure */
        owner = device->bus->owner;
        if (owner && owner != device)
        {
            /* make sure predecessor's CS is deactived */
            inactive = (owner->config.mode & RT_SPI_CS_HIGH) ? PIN_LOW : PIN_HIGH;
            cs_pin = (rt_base_t)owner->parent.user_data;
            rt_pin_write(cs_pin, inactive);
        }
        /* bus owner is maintained by upper layer, do not update here */

        inactive = (config->mode & RT_SPI_CS_HIGH) ? PIN_LOW : PIN_HIGH;
        cs_pin = (rt_base_t)device->parent.user_data;
        rt_pin_write(cs_pin, inactive);
        rt_pin_mode(cs_pin, PIN_MODE_OUTPUT);
    }

    /* `config` is actually `device->config` : spi_core.c */
    //device->config = *config;

    return RT_EOK;
}

/**
 * @brief   Transfer SPI data for single message.
 *          Message traversing is done by rt_spi_message().
 *
 * @param   device is pointer to the rt_spi_device device.
 *
 * @param   message is a link list for data/control information,
 *          only the first entry is processed.
 *          Note: ch56x can't do SPI send & recv at the same time.
 *
 * @return  `message->length1 if successful, 0 otherwise.
 */
static rt_uint32_t spi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    struct spi_bus *spi_bus = (struct spi_bus *)device->bus;
    volatile struct spi_registers *sxreg = spi_bus->reg_base;

    union _spi_ctrl_mod ctrl_mod;

    uint8_t *data;
    uint32_t size;

    rt_base_t cs_pin;
    int cs_high;

    size = message->length;
    if (size == 0 || size > 4095)
        return 0;

    ctrl_mod.reg = sxreg->CTRL_MOD.reg | RB_SPI_ALL_CLEAR;

    /* ch56x can't do SPI send & recv at the same time */
    if (message->send_buf && !message->recv_buf)
    {
        data = (uint8_t *)message->send_buf;
        ctrl_mod.fifo_dir = SPI_FIFO_DIR_OUTPUT;
    }
    else if (!message->send_buf && message->recv_buf)
    {
        data = (uint8_t *)message->recv_buf;
        ctrl_mod.fifo_dir = SPI_FIFO_DIR_INPUT;
    }
    else
    {
        return 0;
    }

    sxreg->CTRL_MOD.reg = ctrl_mod.reg;
    ctrl_mod.all_clear = 0;
    sxreg->CTRL_MOD.reg = ctrl_mod.reg;

    /* set MISO pin direction to match xfer if shared SI/SO pin */
    if (device->config.mode & RT_SPI_3WIRE)
    {
        rt_base_t mode = message->send_buf ? PIN_MODE_OUTPUT : PIN_MODE_INPUT;
        rt_pin_mode(spi_bus->miso_pin, mode);
    }

    cs_pin = (rt_base_t)device->parent.user_data;
    cs_high = device->config.mode & RT_SPI_CS_HIGH;

    if (message->cs_take)
    {
        /* take/activate CS */
        rt_pin_write(cs_pin, cs_high ? PIN_HIGH : PIN_LOW);
    }

    sxreg->TOTAL_COUNT = size;

    if (size > SPI_FIFO_SIZE)
    {
        sxreg->DMA_BIG = (uint32_t)data;
        sxreg->DMA_END = (uint32_t)(data + size);
        sxreg->CTRL_CFG.dma_enable = 1;
        /* mark no need to read FIFO */
        size = 0;
    }
    else
    {
        if (message->send_buf)
        {
            /* keep sending, won't overflow */
            while (size)
            {
                sxreg->FIFO = *data++;
                size--;
            }
        }
    }

    /* wait for transfer done */
    while (sxreg->TOTAL_COUNT > 0);
    /* disable DMA, anyway */
    sxreg->CTRL_CFG.dma_enable = 0;

    /* non-DMA recv => read data from FIFO */
    if (size > 0)
    {
        while (size--)
            *data++ = sxreg->FIFO;
    }

    /* set MISO as input after xfer if shared SI/SO pin */
    if (device->config.mode & RT_SPI_3WIRE)
    {
        rt_pin_mode(spi_bus->miso_pin, PIN_MODE_INPUT);
    }

    if (message->cs_release)
    {
        /* release/deactivate CS */
        rt_pin_write(cs_pin, cs_high ? PIN_LOW : PIN_HIGH);
    }

    return message->length;
}

static const struct rt_spi_ops spi_ops =
{
    .configure = spi_configure,
    .xfer = spi_xfer,
};

static int rt_hw_spi_init(void)
{
    struct spi_bus *devices[2];

    rt_err_t res, ret = RT_EOK;

    int n = 0;

#ifdef BSP_USING_SPI1
    devices[n++] = &spi_bus_1;
#endif
#ifdef BSP_USING_SPI0
    devices[n++] = &spi_bus_0;
#endif

    while (--n >= 0)
    {
        struct spi_bus *spi_bus = devices[n];

        sys_clk_off_by_irqn(spi_bus->irqn, SYS_SLP_CLK_ON);

        res = rt_spi_bus_register(&spi_bus->parent, spi_bus->name, &spi_ops);
        if (res != RT_EOK)
        {
            ret = res;
        }
    };

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_spi_init);
