/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-05     Bernard      The first version
 * 2022-08-24     GuEe-GUI     add OFW support
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <cpuport.h>

#include <ioremap.h>

#include <drivers/serial_dm.h>

#define PL011_OEIM          RT_BIT(10)  /* overrun error interrupt mask */
#define PL011_BEIM          RT_BIT(9)   /* break error interrupt mask */
#define PL011_PEIM          RT_BIT(8)   /* parity error interrupt mask */
#define PL011_FEIM          RT_BIT(7)   /* framing error interrupt mask */
#define PL011_RTIM          RT_BIT(6)   /* receive timeout interrupt mask */
#define PL011_TXIM          RT_BIT(5)   /* transmit interrupt mask */
#define PL011_RXIM          RT_BIT(4)   /* receive interrupt mask */
#define PL011_DSRMIM        RT_BIT(3)   /* DSR interrupt mask */
#define PL011_DCDMIM        RT_BIT(2)   /* DCD interrupt mask */
#define PL011_CTSMIM        RT_BIT(1)   /* CTS interrupt mask */
#define PL011_RIMIM         RT_BIT(0)   /* RI interrupt mask */

#define PL011_DR            0x000
#define PL011_FR            0x018
#define PL011_IBRD          0x024
#define PL011_FBRD          0x028
#define PL011_LCR           0x02c
#define PL011_CR            0x030
#define PL011_IMSC          0x038
#define PL011_RIS           0x03c
#define PL011_DMACR         0x048

#define PL011_LCRH_SPS      (1 << 7)
#define PL011_LCRH_WLEN_8   (3 << 5)
#define PL011_LCRH_WLEN_7   (2 << 5)
#define PL011_LCRH_WLEN_6   (1 << 5)
#define PL011_LCRH_WLEN_5   (0 << 5)
#define PL011_LCRH_FEN      (1 << 4)
#define PL011_LCRH_STP2     (1 << 3)
#define PL011_LCRH_EPS      (1 << 2)
#define PL011_LCRH_PEN      (1 << 1)
#define PL011_LCRH_BRK      (1 << 0)

#define PL011_LCRH_WLEN(n)  ((n - 5) << 5)

#define PL011_CR_CTSEN      RT_BIT(15)
#define PL011_CR_RTSEN      RT_BIT(14)
#define PL011_CR_RTS        RT_BIT(11)
#define PL011_CR_DTR        RT_BIT(10)
#define PL011_CR_RXE        RT_BIT(9)
#define PL011_CR_TXE        RT_BIT(8)
#define PL011_CR_LBE        RT_BIT(7)
#define PL011_CR_SIRLP      RT_BIT(2)
#define PL011_CR_SIREN      RT_BIT(1)
#define PL011_CR_UARTEN     RT_BIT(0)

struct pl011
{
    struct rt_serial_device parent;

    int irq;
    void *base;
    rt_ubase_t freq;
    struct rt_clk *clk;
    struct rt_clk *pclk;

    struct rt_spinlock spinlock;
};

#define raw_to_pl011(raw) rt_container_of(raw, struct pl011, parent)

rt_inline rt_uint32_t pl011_read(struct pl011 *pl011, int offset)
{
    return HWREG32(pl011->base + offset);
}

rt_inline void pl011_write(struct pl011 *pl011, int offset, rt_uint32_t value)
{
    HWREG32(pl011->base + offset) = value;
}

static void pl011_isr(int irqno, void *param)
{
    struct pl011 *pl011 = param;

    /* Check irq */
    if (pl011_read(pl011, PL011_RIS) & PL011_RXIM)
    {
        rt_base_t level = rt_spin_lock_irqsave(&pl011->spinlock);

        rt_hw_serial_isr(&pl011->parent, RT_SERIAL_EVENT_RX_IND);

        rt_spin_unlock_irqrestore(&pl011->spinlock, level);
    }
}

static rt_err_t pl011_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    rt_ubase_t quot;
    struct pl011 *pl011 = raw_to_pl011(serial);

    /* Clear UART setting */
    pl011_write(pl011, PL011_CR, 0);
    /* Disable FIFO */
    pl011_write(pl011, PL011_LCR, 0);

    if (cfg->baud_rate > pl011->freq / 16)
    {
        quot = RT_DIV_ROUND_CLOSEST(pl011->freq * 8, cfg->baud_rate);
    }
    else
    {
        quot = RT_DIV_ROUND_CLOSEST(pl011->freq * 4, cfg->baud_rate);
    }

    pl011_write(pl011, PL011_IBRD, quot >> 6);
    pl011_write(pl011, PL011_FBRD, quot & 0x3f);
    /* FIFO */
    pl011_write(pl011, PL011_LCR, PL011_LCRH_WLEN(cfg->data_bits));

    /* Art enable, TX/RX enable */
    pl011_write(pl011, PL011_CR, PL011_CR_UARTEN | PL011_CR_TXE | PL011_CR_RXE);

    return RT_EOK;
}

static rt_err_t pl011_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct pl011 *pl011 = raw_to_pl011(serial);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* Disable rx irq */
        pl011_write(pl011, PL011_IMSC, pl011_read(pl011, PL011_IMSC) & ~PL011_RXIM);

        rt_hw_interrupt_mask(pl011->irq);

        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* Enable rx irq */
        pl011_write(pl011, PL011_IMSC, pl011_read(pl011, PL011_IMSC) | PL011_RXIM);

        rt_hw_interrupt_umask(pl011->irq);

        break;
    }

    return RT_EOK;
}

static int pl011_uart_putc(struct rt_serial_device *serial, char c)
{
    struct pl011 *pl011 = raw_to_pl011(serial);

    while (pl011_read(pl011, PL011_FR) & PL011_TXIM)
    {
        rt_hw_cpu_relax();
    }

    pl011_write(pl011, PL011_DR, c);

    return 1;
}

static int pl011_uart_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    struct pl011 *pl011 = raw_to_pl011(serial);

    if (!(pl011_read(pl011, PL011_FR) & PL011_RXIM))
    {
        ch = pl011_read(pl011, PL011_DR);
    }

    return ch;
}

static const struct rt_uart_ops pl011_uart_ops =
{
    .configure = pl011_uart_configure,
    .control = pl011_uart_control,
    .putc = pl011_uart_putc,
    .getc = pl011_uart_getc,
};

static void pl011_early_kick(struct rt_fdt_earlycon *con, int why)
{
    struct pl011 *pl011 = raw_to_pl011(con->data);

    switch (why)
    {
    case FDT_EARLYCON_KICK_UPDATE:
        pl011->base = rt_ioremap((void *)con->mmio, con->size);
        break;

    case FDT_EARLYCON_KICK_COMPLETED:
        rt_iounmap(pl011->base);
        break;

    default:
        break;
    }
}

static rt_err_t pl011_early_setup(struct rt_fdt_earlycon *con, const char *options)
{
    rt_err_t err = RT_EOK;
    static struct pl011 pl011 = { };

    if (options && !con->mmio)
    {
        char *arg;

        con->mmio = RT_NULL;

        /*
         *  The pl011 serial port must already be setup and configured in early.
         *  Options are not yet supported.
         *  pl011,<addr>
         *  pl011,mmio32,<addr>
         */
        serial_for_each_args(arg, options)
        {
            if (!rt_strcmp(arg, "pl011") || !rt_strcmp(arg, "mmio32"))
            {
                continue;
            }
            if (!con->mmio)
            {
                con->mmio = (rt_ubase_t)serial_base_from_args(arg);
                break;
            }
        }
    }

    if (!con->size)
    {
        con->size = 0x1000;
    }

    if (con->mmio)
    {
        pl011.base = rt_ioremap_early((void *)con->mmio, con->size);
    }

    if (pl011.base)
    {
        con->console_putc = (typeof(con->console_putc))&pl011_uart_putc;
        con->console_kick = pl011_early_kick;
        con->data = &pl011.parent;
        pl011.parent.config = (typeof(pl011.parent.config))RT_SERIAL_CONFIG_DEFAULT;
    }
    else
    {
        err = -RT_ERROR;
    }

    return err;
}
RT_FDT_EARLYCON_EXPORT(pl011, "pl011", "arm,pl011", pl011_early_setup);

static void pl011_free(struct pl011 *pl011)
{
    if (pl011->base)
    {
        rt_iounmap(pl011->base);
    }

    /* if (!rt_is_err_or_null(pl011->clk))*/
    /* {*/
    /*     rt_clk_disable(pl011->clk);*/
    /*     rt_clk_put(pl011->clk);*/
    /* }*/

    /* if (!rt_is_err_or_null(pl011->pclk))*/
    /* {*/
    /*     rt_clk_disable_unprepare(pl011->pclk);*/
    /*     rt_clk_put(pl011->pclk);*/
    /* }*/

    rt_free(pl011);
}

static rt_err_t pl011_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *name;
    char isr_name[RT_NAME_MAX];
    struct rt_device *dev = &pdev->parent;
    struct pl011 *pl011 = rt_calloc(1, sizeof(*pl011));
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    if (!pl011)
    {
        return -RT_ENOMEM;
    }

    pl011->base = rt_dm_dev_iomap(dev, 0);

    if (!pl011->base)
    {
        err = -RT_EIO;

        goto _fail;
    }

    pl011->irq = rt_dm_dev_get_irq(dev, 0);

    if (pl011->irq < 0)
    {
        err = pl011->irq;

        goto _fail;
    }

    /* pl011->clk = rt_clk_get_by_index(dev, 0);*/

    /* if (rt_is_err(pl011->clk))*/
    /* {*/
    /*     err = rt_ptr_err(pl011->clk);*/

    /*     goto _fail;*/
    /* }*/

    /* pl011->pclk = rt_clk_get_by_name(dev, "apb_pclk");*/

    /* if (rt_is_err(pl011->pclk))*/
    /* {*/
    /*     err = rt_ptr_err(pl011->pclk);*/

    /*     goto _fail;*/
    /* }*/

    /* if ((err = rt_clk_prepare_enable(pl011->pclk)))*/
    /* {*/
    /*     goto _fail;*/
    /* }*/

    rt_dm_dev_bind_fwdata(&pl011->parent.parent, dev->ofw_node, &pl011->parent);

    /* rt_clk_enable(pl011->clk);*/
    /* pl011->freq = rt_clk_get_rate(pl011->clk);*/

    dev->user_data = pl011;

    pl011->parent.ops = &pl011_uart_ops;
    pl011->parent.config = config;

    rt_spin_lock_init(&pl011->spinlock);

    serial_dev_set_name(&pl011->parent);
    name = rt_dm_dev_get_name(&pl011->parent.parent);

    rt_hw_serial_register(&pl011->parent, name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, pl011);
    rt_snprintf(isr_name, RT_NAME_MAX, "%s-pl011", name);
    rt_hw_interrupt_install(pl011->irq, pl011_isr, pl011, isr_name);

    return RT_EOK;

_fail:
    pl011_free(pl011);

    return err;
}

static rt_err_t pl011_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct pl011 *pl011 = dev->user_data;

    rt_dm_dev_unbind_fwdata(dev, RT_NULL);

    rt_hw_interrupt_mask(pl011->irq);
    rt_pic_detach_irq(pl011->irq, pl011);

    rt_device_unregister(&pl011->parent.parent);

    pl011_free(pl011);

    return RT_EOK;
}

static const struct rt_ofw_node_id pl011_ofw_ids[] =
{
    { .type = "ttyAMA", .compatible = "arm,pl011" },
    { .type = "ttyAMA", .compatible = "arm,pl011-axi" },
    { /* sentinel */ }
};

static struct rt_platform_driver pl011_driver =
{
    .name = "serial-pl011",
    .ids = pl011_ofw_ids,

    .probe = pl011_probe,
    .remove = pl011_remove,
};

static int pl011_drv_register(void)
{
    rt_platform_driver_register(&pl011_driver);

    return 0;
}
INIT_DRIVER_EARLY_EXPORT(pl011_drv_register);
