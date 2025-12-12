/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-16     GuEe-GUI     first version
 */

#include "8250.h"

rt_err_t serial8250_config(struct serial8250 *serial, const char *options)
{
    rt_err_t ret = -RT_EINVAL;

    if (serial)
    {
        char *arg;
        rt_bool_t has_iotype = RT_FALSE;

        /*
         *  uart8250,io,<addr>[,options]
         *  uart8250,mmio,<addr>[,options]
         *  uart8250,mmio16,<addr>[,options]
         *  uart8250,mmio32,<addr>[,options]
         *  uart8250,mmio32be,<addr>[,options]
         *  uart8250,0x<addr>[,options]
         */
        serial_for_each_args(arg, options)
        {
            if (!rt_strcmp(arg, "uart8250"))
            {
                ret = RT_EOK;
                continue;
            }
            /* User call error */
            if (ret)
            {
                break;
            }
            if (!rt_strncmp(arg, "0x", 2))
            {
                serial->base = serial_base_from_args(arg);
                continue;
            }
            if (!has_iotype)
            {
                const struct
                {
                    char *param;
                    int type;
                } iotype_table[] =
                {
                    { "io", PORT_IO },
                    { "mmio", PORT_MMIO },
                    { "mmio16", PORT_MMIO16 },
                    { "mmio32", PORT_MMIO32 },
                    { "mmio32be", PORT_MMIO32BE },
                };

                serial->iotype = PORT_MMIO32;

                for (int i = 0; i < RT_ARRAY_SIZE(iotype_table); ++i)
                {
                    if (!rt_strcmp(arg, iotype_table[i].param))
                    {
                        serial->iotype = iotype_table[i].type;
                        break;
                    }
                }

                has_iotype = RT_TRUE;
                continue;
            }

            serial->parent.config = serial_cfg_from_args(arg);
            break;
        }

        if (!serial->size)
        {
            serial->size = 0x1000;
        }
    }

    return ret;
}

static void serial8250_isr(int irqno, void *param)
{
    struct serial8250 *serial = (struct serial8250 *)param;

    if (serial->handle_irq)
    {
        serial->handle_irq(serial, irqno);
    }
    else
    {
        rt_hw_serial_isr(&serial->parent, RT_SERIAL_EVENT_RX_IND);
    }
}

static rt_err_t serial8250_dma_enable_dummy(struct serial8250 *serial, rt_bool_t enabled)
{
    return RT_EOK;
}

static rt_ssize_t serial8250_dma_tx_dummy(struct serial8250 *serial,
        const rt_uint8_t *buf, rt_size_t size)
{
    return 0;
}

static rt_ssize_t serial8250_dma_rx_dummy(struct serial8250 *serial,
        rt_uint8_t *buf, rt_size_t size)
{
    return 0;
}

rt_err_t serial8250_setup(struct serial8250 *serial)
{
    rt_uint32_t flags;
    rt_err_t err = RT_EOK;
    const char *uart_name;
    char dev_name[RT_NAME_MAX];

    if (serial)
    {
        struct rt_device *dev = &serial->parent.parent;

        rt_spin_lock_init(&serial->spinlock);
        flags = RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX;

        if (!serial->regshift)
        {
            rt_dm_dev_prop_read_u32(dev, "reg-shift", &serial->regshift);
        }

        if (serial->iotype == PORT_UNKNOWN)
        {
            rt_uint32_t width = sizeof(rt_uint32_t);

            rt_dm_dev_prop_read_u32(dev, "reg-io-width", &width);

            switch (width)
            {
            case sizeof(rt_uint8_t):
                serial->iotype = PORT_MMIO;
                break;

            case sizeof(rt_uint16_t):
                serial->iotype = PORT_MMIO16;
                break;

            case sizeof(rt_uint32_t):
            default:
                serial->iotype = rt_dm_dev_is_big_endian(dev) ? PORT_MMIO32BE : PORT_MMIO32;
                break;
            }
        }

        serial->serial_in = serial->serial_in ? : &serial8250_in;
        serial->serial_out = serial->serial_out ? : &serial8250_out;
        serial->serial_dma_enable = serial->serial_dma_enable ? : &serial8250_dma_enable_dummy;

        if (serial->serial_dma_tx)
        {
            flags |= RT_DEVICE_FLAG_DMA_TX;
        }
        else
        {
            serial->serial_dma_tx = &serial8250_dma_tx_dummy;
        }

        if (serial->serial_dma_rx)
        {
            flags |= RT_DEVICE_FLAG_DMA_RX;
        }
        else
        {
            serial->serial_dma_rx = &serial8250_dma_rx_dummy;
        }

        serial_dev_set_name(&serial->parent);
        uart_name = rt_dm_dev_get_name(&serial->parent.parent);

        rt_hw_serial_register(&serial->parent, uart_name, flags, serial->data);

        rt_snprintf(dev_name, sizeof(dev_name), "%s-8250", uart_name);
        rt_hw_interrupt_install(serial->irq, serial8250_isr, serial, dev_name);
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

rt_err_t serial8250_remove(struct serial8250 *serial)
{
    rt_err_t err;

    rt_iounmap((void *)serial->base);
    serial->base = RT_NULL;

    rt_hw_interrupt_mask(serial->irq);
    rt_pic_detach_irq(serial->irq, serial);

    err = rt_device_unregister(&serial->parent.parent);

    if (!err && serial->remove)
    {
        serial->remove(serial);
    }

    return err;
}

rt_uint32_t serial8250_in(struct serial8250 *serial, int offset)
{
    rt_uint32_t ret = 0;
    offset <<= serial->regshift;

    switch (serial->iotype)
    {
    case PORT_MMIO:
        ret = HWREG8(serial->base + offset);
        break;
    case PORT_MMIO16:
        ret = HWREG16(serial->base + offset);
        break;
    case PORT_MMIO32:
        ret = HWREG32(serial->base + offset);
        break;
    case PORT_MMIO32BE:
        ret = rt_cpu_to_be32(HWREG32(serial->base + offset));
        break;
#ifdef ARCH_SUPPORT_PIO
    case PORT_IO:
        ret = inb(serial->base + offset);
        break;
#endif
    default:
        break;
    }

    return ret;
}

void serial8250_out(struct serial8250 *serial, int offset, int value)
{
    offset <<= serial->regshift;

    switch (serial->iotype)
    {
    case PORT_MMIO:
        HWREG8(serial->base + offset) = value;
        break;
    case PORT_MMIO16:
        HWREG16(serial->base + offset) = value;
        break;
    case PORT_MMIO32:
        HWREG32(serial->base + offset) = value;
        break;
    case PORT_MMIO32BE:
        HWREG32(serial->base + offset) = rt_cpu_to_be32(value);
        break;
#ifdef ARCH_SUPPORT_PIO
    case PORT_IO:
        outb(serial->base + offset, value);
        break;
#endif
    default:
        break;
    }
}

void serial8250_dma_tx_done(struct serial8250 *serial)
{
    rt_hw_serial_isr(&serial->parent, RT_SERIAL_EVENT_TX_DMADONE);
}

void serial8250_dma_rx_done(struct serial8250 *serial, int recv_len)
{
    rt_hw_serial_isr(&serial->parent, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
}

rt_inline rt_ubase_t baudrate_to_divisor(rt_ubase_t freq, rt_ubase_t baudrate)
{
    return (freq + baudrate * 8) / (16 * baudrate);
}

static void serial8250_hw_ios(struct serial8250 *serial, struct serial_configure *cfg)
{
    rt_uint32_t ier;

    /* Disable RX interrupt */
    ier = serial->serial_in(serial, UART_IER);
    ier &= ~UART_IER_RDI;
    ier |= UART_IER_UUE;
    serial->serial_out(serial, UART_IER, ier);

    /* Enable FIFO, Clear FIFO */
    serial->serial_out(serial, UART_FCR, UART_FCR_ENABLE_FIFO | UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);

    /* DTR + RTS */
    serial->serial_out(serial, UART_MCR, UART_MCR_OUT1 | UART_MCR_OUT2 | UART_MCR_DTR | UART_MCR_RTS);

    if (serial->freq)
    {
        rt_uint32_t wlen = cfg->data_bits - DATA_BITS_5 + UART_LCR_WLEN5;
        rt_uint32_t divisor = baudrate_to_divisor(serial->freq, cfg->baud_rate);

        /* Enable access DLL & DLH */
        serial->serial_out(serial, UART_LCR, serial->serial_in(serial, UART_LCR) | UART_LCR_DLAB);
        serial->serial_out(serial, UART_DLL, (divisor & 0xff));
        serial->serial_out(serial, UART_DLM, (divisor >> 8) & 0xff);
        /* Clear DLAB bit */
        serial->serial_out(serial, UART_LCR, serial->serial_in(serial, UART_LCR) & (~UART_LCR_DLAB));

        serial->serial_out(serial, UART_LCR, (serial->serial_in(serial, UART_LCR) & (~wlen)) | wlen);
        serial->serial_out(serial, UART_LCR, serial->serial_in(serial, UART_LCR) & (~UART_LCR_STOP));
        serial->serial_out(serial, UART_LCR, serial->serial_in(serial, UART_LCR) & (~UART_LCR_PARITY));
    }

    /* Enable RX interrupt */
    ier |= UART_IER_RDI;
    serial->serial_out(serial, UART_IER, ier);
}

rt_err_t serial8250_ios(struct serial8250 *serial, struct serial_configure *cfg)
{
    rt_err_t err = RT_EOK;
    rt_uint32_t count = 10000;
    rt_uint32_t divisor = baudrate_to_divisor(serial->freq, cfg->baud_rate);

    /* Flush FIFO */
    while (!(serial->serial_in(serial, UART_LSR) & UART_LSR_TEMT) && count--)
    {
        rt_hw_cpu_relax();
    }

    /* Need to increase CLK frequency */
    if (divisor == 0 && serial->freq)
    {
        if (serial->clk)
        {
            for (rt_ubase_t round = serial->freq, freq = 0; ; round += round)
            {
                if (baudrate_to_divisor(round, cfg->baud_rate))
                {
                    freq = rt_clk_round_rate(serial->clk, freq);

                    if (freq < 0)
                    {
                        continue;
                    }

                    rt_clk_disable_unprepare(serial->clk);

                    err = rt_clk_set_rate(serial->clk, freq);

                    if (!err)
                    {
                        serial->freq = rt_clk_get_rate(serial->clk);
                    }

                    rt_clk_prepare_enable(serial->clk);

                    break;
                }
            }
        }
        else
        {
            err = -RT_ENOSYS;
        }
    }

    if (!err)
    {
        serial8250_hw_ios(serial, cfg);
    }

    return err;
}

rt_err_t serial8250_uart_configure(struct rt_serial_device *raw_serial, struct serial_configure *cfg)
{
    rt_err_t err;
    struct serial8250 *serial = raw_to_serial8250(raw_serial);

    if (serial->serial_ios)
    {
        err = serial->serial_ios(serial, cfg);
    }
    else
    {
        err = serial8250_ios(serial, cfg);
    }

    return err;
}

rt_err_t serial8250_uart_control(struct rt_serial_device *raw_serial, int cmd, void *arg)
{
    rt_uint32_t value;
    rt_err_t err = RT_EOK;
    rt_ubase_t ctrl = (rt_ubase_t)arg;
    struct serial8250 *serial = raw_to_serial8250(raw_serial);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        if (ctrl == RT_DEVICE_FLAG_INT_RX)
        {
            /* Disable RX irq */
            value = serial->serial_in(serial, UART_IER);
            value &= ~UART_IER_RDI;
            value |= UART_IER_UUE;
            serial->serial_out(serial, UART_IER, value);
            rt_hw_interrupt_mask(serial->irq);
        }
        else if (ctrl == RT_DEVICE_FLAG_DMA_RX)
        {
            err = serial->serial_dma_enable(serial, RT_FALSE);
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:
        if (ctrl == RT_DEVICE_FLAG_INT_RX)
        {
            /* Enable RX irq */
            value = serial->serial_in(serial, UART_IER);
            serial->serial_out(serial, UART_IER, value | UART_IER_RDI);
            rt_hw_interrupt_umask(serial->irq);
        }
        else if (ctrl == RT_DEVICE_FLAG_DMA_RX)
        {
            err = serial->serial_dma_enable(serial, RT_TRUE);
        }
        break;

    case RT_DEVICE_CTRL_CLOSE:
        err = serial->serial_dma_enable(serial, RT_FALSE);
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

int serial8250_uart_putc(struct rt_serial_device *raw_serial, char c)
{
    struct serial8250 *serial = raw_to_serial8250(raw_serial);

    while (!(serial->serial_in(serial, UART_LSR) & UART_LSR_THRE))
    {
        rt_hw_cpu_relax();
    }

    serial->serial_out(serial, UART_TX, c);

    return 1;
}

int serial8250_uart_getc(struct rt_serial_device *raw_serial)
{
    int ch = -1;
    struct serial8250 *serial = raw_to_serial8250(raw_serial);

    if ((serial->serial_in(serial, UART_LSR) & UART_LSR_DR))
    {
        ch = serial->serial_in(serial, UART_RX) & 0xff;
    }

    return ch;
}

rt_ssize_t serial8250_uart_dma_transmit(struct rt_serial_device *raw_serial,
        rt_uint8_t *buf, rt_size_t size, int direction)
{
    rt_ssize_t res = 0;
    struct serial8250 *serial = raw_to_serial8250(raw_serial);

    if (direction == RT_SERIAL_DMA_TX)
    {
        res = serial->serial_dma_tx(serial, (const rt_uint8_t *)buf, size);
    }
    else if (direction == RT_SERIAL_DMA_RX)
    {
        res = serial->serial_dma_rx(serial, buf, size);
    }

    return res;
}

const struct rt_uart_ops serial8250_uart_ops =
{
    .configure = serial8250_uart_configure,
    .control = serial8250_uart_control,
    .putc = serial8250_uart_putc,
    .getc = serial8250_uart_getc,
    .dma_transmit = serial8250_uart_dma_transmit,
};
