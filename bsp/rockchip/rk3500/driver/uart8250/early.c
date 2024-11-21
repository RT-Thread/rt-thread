/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-16     GuEe-GUI     first version
 */

#include "8250.h"

struct serial8250 early_serial8250 = { 0 };

static rt_uint32_t serial8250_early_in(struct serial8250 *serial, int offset)
{
    return serial8250_in(serial, offset);
}

static void serial8250_early_out(struct serial8250 *serial, int offset, int value)
{
    serial8250_out(serial, offset, value);
}

int serial8250_early_putc(struct rt_serial_device *raw_serial, char c)
{
    if (raw_serial)
    {
        /* FIFO and shifting register empty */
        const int uart_lsr_both_empty = (UART_LSR_TEMT | UART_LSR_THRE);
        struct serial8250 *serial = rt_container_of(raw_serial, struct serial8250, parent);

        serial8250_early_out(serial, UART_TX, c);

        while ((serial8250_early_in(serial, UART_LSR) & uart_lsr_both_empty) != uart_lsr_both_empty)
        {
            rt_hw_cpu_relax();
        }
    }

    return 1;
}

static void init_serial(struct serial8250 *serial)
{
    unsigned char c;
    rt_uint32_t ier, divisor;

    serial8250_early_out(serial, UART_LCR, 0x3);    /* 8n1 */
    ier = serial8250_early_in(serial, UART_IER);
    serial8250_early_out(serial, UART_IER, ier & UART_IER_UUE); /* no interrupt */
    serial8250_early_out(serial, UART_FCR, 0);      /* no fifo */
    serial8250_early_out(serial, UART_MCR, 0x3);    /* DTR + RTS */

    if (serial->freq)
    {
        divisor = RT_DIV_ROUND_CLOSEST(serial->freq, 16 * serial->parent.config.baud_rate);
        c = serial8250_early_in(serial, UART_LCR);
        serial8250_early_out(serial, UART_LCR, c | UART_LCR_DLAB);
        serial8250_early_out(serial, UART_DLL, divisor & 0xff);
        serial8250_early_out(serial, UART_DLM, (divisor >> 8) & 0xff);
        serial8250_early_out(serial, UART_LCR, c & ~UART_LCR_DLAB);
    }
}

static void serial8250_early_kick(struct rt_fdt_earlycon *con, int why)
{
    struct serial8250 *serial = raw_to_serial8250(con->data);

    switch (why)
    {
    case FDT_EARLYCON_KICK_UPDATE:
        serial->base = rt_ioremap((void *)con->mmio, con->size);
        break;

    case FDT_EARLYCON_KICK_COMPLETED:
        rt_iounmap(serial->base);
        break;

    default:
        break;
    }
}

rt_err_t serial8250_early_fdt_setup(struct serial8250 *serial, struct rt_fdt_earlycon *con, const char *options)
{
    rt_err_t ret = RT_EOK;

    if (!serial->base && con)
    {
        serial8250_config(serial, options);
        con->mmio = (rt_ubase_t)serial->base;
        con->size = serial->size;
    }

    if (serial->base && con)
    {
        serial->base = rt_ioremap_early((void *)serial->base, serial->size);
    }

    if (serial->base && con)
    {
        con->console_putc = (typeof(con->console_putc))&serial8250_early_putc;
        con->console_kick = serial8250_early_kick;
        con->data = &serial->parent;

        if (!serial->parent.config.baud_rate)
        {
            /* assume the device was initialized, only mask interrupts */
            rt_uint32_t ier = serial8250_early_in(serial, UART_IER);
            serial8250_early_out(serial, UART_IER, ier & UART_IER_UUE);
        }
        else
        {
            init_serial(serial);
        }
    }
    else
    {
        ret = -RT_ERROR;
    }

    return ret;
}

static void common_init(struct serial8250 *serial, struct rt_fdt_earlycon *con)
{
    serial->base = (void *)con->mmio;
    serial->size = con->size;
    serial->iotype = PORT_MMIO32;
}

static rt_err_t common_early_setup(struct rt_fdt_earlycon *con, const char *options)
{
    struct serial8250 *serial = &early_serial8250;

    common_init(serial, con);
    serial->regshift = 2;
    fdt_getprop_u32(con->fdt, con->nodeoffset, "reg-shift", &serial->regshift, RT_NULL);

    return serial8250_early_fdt_setup(serial, con, options);
}
RT_FDT_EARLYCON_EXPORT(bcm2835aux, "uart8250", "brcm,bcm2835-aux-uart", common_early_setup);
RT_FDT_EARLYCON_EXPORT(tegra20, "uart8250", "nvidia,tegra20-uart", common_early_setup);
RT_FDT_EARLYCON_EXPORT(dw8250, "uart8250", "snps,dw-apb-uart", common_early_setup);
RT_FDT_EARLYCON_EXPORT(ns16550a, "uart8250", "ns16550a", common_early_setup);
RT_FDT_EARLYCON_EXPORT(ns16550, "uart8250", "ns16550", common_early_setup);

#ifdef RT_USING_8250_OMAP
static rt_err_t omap8250_early_setup(struct rt_fdt_earlycon *con, const char *options)
{
    struct serial8250 *serial = &early_serial8250;

    common_init(serial, con);
    serial->regshift = 2;

    return serial8250_early_fdt_setup(serial, con, options);
}
RT_FDT_EARLYCON_EXPORT(omap8250, "uart8250", "ti,omap2-uart", omap8250_early_setup);
RT_FDT_EARLYCON_EXPORT(omap8250, "uart8250", "ti,omap3-uart", omap8250_early_setup);
RT_FDT_EARLYCON_EXPORT(omap8250, "uart8250", "ti,omap4-uart", omap8250_early_setup);
#endif /* RT_USING_8250_OMAP */
