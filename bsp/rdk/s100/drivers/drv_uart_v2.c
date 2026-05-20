/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-20     rcitach      first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "interrupt.h"

#ifdef RT_USING_SERIAL_V2

#if !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5) && !defined(BSP_USING_UART6)
#error "Please define at least one BSP_USING_UARTx"
#endif

#define UART_SYS_CLK                   (200000000u)
#define UART_CONFIG_TIMEOUT            (0xffu)
#define UART_BAUD_DIV_INT_MAX          (0xffffu)

#define SYS_REG_UART_CTRL              ((volatile rt_uint32_t *)0x23660084u)

#define UART_4_BASE                    (0x23400000u)
#define UART_5_BASE                    (0x23410000u)
#define UART_6_BASE                    (0x23420000u)

#define UART_CTRL_UART4_RX_IN_MASK     (0x00000001u)
#define UART_CTRL_UART5_RX_IN_MASK     (0x00000010u)
#define UART_CTRL_UART6_RX_IN_MASK     (0x00000100u)

#define UART4_IRQn                     (45)
#define UART5_IRQn                     (46)
#define UART6_IRQn                     (47)

#define UART_FCR_FIFO_DIS              (0x00u)
#define UART_FCR_FIFO_EN               (0x01u)
#define UART_FCR_CLEAR_RCVR            (0x02u)
#define UART_FCR_CLEAR_XMIT            (0x04u)
#define UART_FCR_RXSR                  (0x02u)
#define UART_FCR_TXSR                  (0x04u)
#define UART_FCR_DEFVAL                (UART_FCR_FIFO_EN | UART_FCR_RXSR | UART_FCR_TXSR)
#define UART_FCR_RX_TRIGGER_MASK       (0xC0u)
#define UART_FCR_RX_TRIGGER_8          (0x80u)

#define UART_LCR_WLS_MSK               (0x03u)
#define UART_LCR_WLS_BASE              (5u)
#define UART_LCR_STB                   (0x04u)
#define UART_LCR_PEN                   (0x08u)
#define UART_LCR_EPS                   (0x10u)
#define UART_LCR_DLAB                  (0x80u)

#define UART_LSR_THRE                  (0x20u)

#define UART_IIR_NO_INT                (0x01u)
#define UART_IIR_ID                    (0x0eu)
#define UART_IIR_THRI                  (0x02u)
#define UART_IIR_RDI                   (0x04u)
#define UART_IIR_RLSI                  (0x06u)
#define UART_IIR_BUSY_DETECT           (0x07u)
#define UART_IIR_CHAR_TIMEOUT          (0x0cu)

#define UART_IER_MSI                   (0x08u)
#define UART_IER_RLSI                  (0x04u)
#define UART_IER_THRI                  (0x02u)
#define UART_IER_RDI                   (0x01u)
#define UART_IER_ALL                   (UART_IER_RDI | UART_IER_THRI | UART_IER_RLSI | UART_IER_MSI)

#define UART_USR_BUSY                  (0x01u)
#define UART_USR_TFNF                  (0x02u)
#define UART_USR_RFNE                  (0x08u)

typedef struct
{
    volatile rt_uint32_t rbr;
    volatile rt_uint32_t ier;
    volatile rt_uint32_t fcr;
    volatile rt_uint32_t lcr;
    volatile rt_uint32_t mcr;
    volatile rt_uint32_t lsr;
    volatile rt_uint32_t msr;
    volatile rt_uint32_t reserved1[21];
    volatile rt_uint32_t far;
    volatile rt_uint32_t tfr;
    volatile rt_uint32_t rfw;
    volatile rt_uint32_t usr;
    volatile rt_uint32_t tfl;
    volatile rt_uint32_t rfl;
    volatile rt_uint32_t reserved2[7];
    volatile rt_uint32_t htx;
    volatile rt_uint32_t dmasa;
    volatile rt_uint32_t reserved3[5];
    volatile rt_uint32_t dlf;
} s100_uart_reg_t;

struct s100_uart_device
{
    rt_ubase_t hw_base;
    rt_uint32_t rx_mask;
    int irqno;
    struct rt_serial_device *serial;
    const char *device_name;
    rt_uint16_t rx_bufsz;
    rt_uint16_t tx_bufsz;
    rt_uint32_t fcr_shadow;
};

#if defined(BSP_USING_UART4)
static struct rt_serial_device serial4;
#endif

#if defined(BSP_USING_UART5)
static struct rt_serial_device serial5;
#endif

#if defined(BSP_USING_UART6)
static struct rt_serial_device serial6;
#endif

static struct s100_uart_device s100_uart_devices[] =
{
#if defined(BSP_USING_UART4)
    {
        .hw_base = UART_4_BASE,
        .rx_mask = UART_CTRL_UART4_RX_IN_MASK,
        .irqno = UART4_IRQn,
        .serial = &serial4,
        .device_name = "uart4",
        .rx_bufsz = BSP_UART4_RX_BUFSIZE,
        .tx_bufsz = BSP_UART4_TX_BUFSIZE,
    },
#endif
#if defined(BSP_USING_UART5)
    {
        .hw_base = UART_5_BASE,
        .rx_mask = UART_CTRL_UART5_RX_IN_MASK,
        .irqno = UART5_IRQn,
        .serial = &serial5,
        .device_name = "uart5",
        .rx_bufsz = BSP_UART5_RX_BUFSIZE,
        .tx_bufsz = BSP_UART5_TX_BUFSIZE,
    },
#endif
#if defined(BSP_USING_UART6)
    {
        .hw_base = UART_6_BASE,
        .rx_mask = UART_CTRL_UART6_RX_IN_MASK,
        .irqno = UART6_IRQn,
        .serial = &serial6,
        .device_name = "uart6",
        .rx_bufsz = BSP_UART6_RX_BUFSIZE,
        .tx_bufsz = BSP_UART6_TX_BUFSIZE,
    },
#endif
};

static s100_uart_reg_t *s100_uart_regs(struct s100_uart_device *uart)
{
    return (s100_uart_reg_t *)uart->hw_base;
}

static struct s100_uart_device *s100_uart_from_serial(struct rt_serial_device *serial)
{
    return (struct s100_uart_device *)serial->parent.user_data;
}

static rt_ubase_t s100_uart_ctrl_arg_translate(rt_ubase_t ctrl_arg)
{
    if (ctrl_arg & (RT_DEVICE_FLAG_RX_BLOCKING | RT_DEVICE_FLAG_RX_NON_BLOCKING))
    {
        return RT_DEVICE_FLAG_INT_RX;
    }

    if (ctrl_arg & (RT_DEVICE_FLAG_TX_BLOCKING | RT_DEVICE_FLAG_TX_NON_BLOCKING))
    {
        return RT_DEVICE_FLAG_INT_TX;
    }

    return ctrl_arg;
}

static void s100_uart_disable_irq(struct s100_uart_device *uart, rt_ubase_t ctrl_arg)
{
    s100_uart_reg_t *regs = s100_uart_regs(uart);

    if (ctrl_arg == RT_DEVICE_FLAG_INT_RX)
    {
        regs->ier &= ~(UART_IER_RDI | UART_IER_RLSI);
    }
    else if (ctrl_arg == RT_DEVICE_FLAG_INT_TX)
    {
        regs->ier &= ~UART_IER_THRI;
    }
}

static void s100_uart_enable_irq(struct s100_uart_device *uart, rt_ubase_t ctrl_arg)
{
    s100_uart_reg_t *regs = s100_uart_regs(uart);

    if (ctrl_arg == RT_DEVICE_FLAG_INT_RX)
    {
        regs->ier |= (UART_IER_RDI | UART_IER_RLSI);
        rt_hw_interrupt_umask(uart->irqno);
    }
    else if (ctrl_arg == RT_DEVICE_FLAG_INT_TX)
    {
        regs->ier |= UART_IER_THRI;
        rt_hw_interrupt_umask(uart->irqno);
    }
}

static void s100_uart_config_default(struct s100_uart_device *uart)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    config.baud_rate = BAUD_RATE_921600;
    config.rx_bufsz = uart->rx_bufsz;
    config.tx_bufsz = uart->tx_bufsz;
    uart->serial->config = config;
}

static void s100_uart_rx_drain(struct rt_serial_device *serial)
{
    struct s100_uart_device *uart;
    s100_uart_reg_t *regs;
    rt_bool_t rx_indicated = RT_FALSE;

    RT_ASSERT(serial != RT_NULL);

    uart = s100_uart_from_serial(serial);
    regs = s100_uart_regs(uart);

    while ((regs->usr & UART_USR_RFNE) != 0u)
    {
        rt_uint8_t ch = (rt_uint8_t)(regs->rbr & 0xffu);

        if (serial->serial_rx != RT_NULL)
        {
            rt_hw_serial_control_isr(serial, RT_HW_SERIAL_CTRL_PUTC, &ch);
            rx_indicated = RT_TRUE;
        }
    }

    if (rx_indicated != RT_FALSE)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
}

static void s100_uart_isr(int vector, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;
    struct s100_uart_device *uart;
    s100_uart_reg_t *regs;
    rt_uint32_t iir;

    RT_UNUSED(vector);
    RT_ASSERT(serial != RT_NULL);

    uart = s100_uart_from_serial(serial);
    regs = s100_uart_regs(uart);

    /* IIR shares the FCR offset; read it with IIR semantics here. */
    iir = *((volatile rt_uint32_t *)&regs->fcr) & 0x0fu;
    if ((iir & UART_IIR_NO_INT) != 0u)
    {
        return;
    }

    switch (iir & UART_IIR_ID)
    {
    case UART_IIR_RDI:
    case UART_IIR_CHAR_TIMEOUT:
        s100_uart_rx_drain(serial);
        break;
    case UART_IIR_RLSI:
        (void)regs->lsr;
        s100_uart_rx_drain(serial);
        break;
    case UART_IIR_BUSY_DETECT:
        (void)regs->usr;
        break;
    case UART_IIR_THRI:
    default:
        break;
    }
}

static void s100_uart_fcr_write(struct s100_uart_device *uart, rt_uint32_t val)
{
    s100_uart_reg_t *regs = s100_uart_regs(uart);

    uart->fcr_shadow = val;
    regs->fcr = uart->fcr_shadow;
}

static void s100_uart_set_rx_trigger(struct s100_uart_device *uart, rt_uint32_t trigger)
{
    s100_uart_reg_t *regs = s100_uart_regs(uart);

    uart->fcr_shadow &= ~UART_FCR_CLEAR_RCVR;
    uart->fcr_shadow &= ~UART_FCR_CLEAR_XMIT;
    uart->fcr_shadow &= ~UART_FCR_RX_TRIGGER_MASK;
    uart->fcr_shadow |= trigger;
    regs->fcr = uart->fcr_shadow;
}

static rt_err_t s100_uart_config_prepare(struct s100_uart_device *uart)
{
    s100_uart_reg_t *regs = s100_uart_regs(uart);
    rt_uint32_t timeout = UART_CONFIG_TIMEOUT;

    while (((regs->usr & UART_USR_BUSY) != 0u) && (timeout != 0u))
    {
        s100_uart_fcr_write(uart, UART_FCR_FIFO_DIS);
        s100_uart_fcr_write(uart, UART_FCR_CLEAR_RCVR);
        s100_uart_fcr_write(uart, UART_FCR_CLEAR_XMIT);
        timeout--;
    }

    return (timeout != 0u) ? RT_EOK : -RT_ETIMEOUT;
}

static rt_err_t s100_uart_set_baud(struct s100_uart_device *uart, rt_uint32_t baud_rate)
{
    s100_uart_reg_t *regs = s100_uart_regs(uart);
    rt_uint32_t baud_div_x64;
    rt_uint32_t baud_div_int;
    rt_uint32_t baud_div_fraction;

    baud_div_x64 = (UART_SYS_CLK * 4u) / baud_rate;
    baud_div_int = baud_div_x64 / 64u;
    if (baud_div_int == 0u)
    {
        baud_div_int = 1u;
    }

    if (baud_div_int > UART_BAUD_DIV_INT_MAX)
    {
        return -RT_EINVAL;
    }

    baud_div_fraction = baud_div_x64 - (baud_div_int * 64u);

    regs->lcr |= UART_LCR_DLAB;
    regs->ier = (baud_div_int >> 8) & 0xffu;
    regs->dlf = baud_div_fraction;
    regs->rbr = baud_div_int & 0xffu;
    regs->lcr &= ~UART_LCR_DLAB;

    return RT_EOK;
}

static rt_err_t s100_uart_set_lcr(struct s100_uart_device *uart, struct serial_configure *cfg)
{
    s100_uart_reg_t *regs = s100_uart_regs(uart);
    rt_uint32_t lcr = 0u;

    switch (cfg->data_bits)
    {
    case DATA_BITS_5:
    case DATA_BITS_6:
    case DATA_BITS_7:
    case DATA_BITS_8:
        lcr |= (cfg->data_bits - UART_LCR_WLS_BASE) & UART_LCR_WLS_MSK;
        break;
    default:
        return -RT_EINVAL;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        break;
    case STOP_BITS_2:
        lcr |= UART_LCR_STB;
        break;
    default:
        return -RT_EINVAL;
    }

    switch (cfg->parity)
    {
    case PARITY_NONE:
        break;
    case PARITY_ODD:
        lcr |= UART_LCR_PEN;
        break;
    case PARITY_EVEN:
        lcr |= UART_LCR_PEN | UART_LCR_EPS;
        break;
    default:
        return -RT_EINVAL;
    }

    regs->lcr &= ~(UART_LCR_WLS_MSK | UART_LCR_STB | UART_LCR_PEN | UART_LCR_EPS);
    regs->lcr |= lcr;

    return RT_EOK;
}

static void s100_uart_set_fifo(struct s100_uart_device *uart)
{
    s100_uart_reg_t *regs = s100_uart_regs(uart);
    rt_uint32_t irq_state = regs->ier & UART_IER_ALL;

    regs->ier &= ~UART_IER_ALL;
    s100_uart_fcr_write(uart, UART_FCR_DEFVAL);
    s100_uart_set_rx_trigger(uart, UART_FCR_RX_TRIGGER_8);
    regs->ier = irq_state;
}

static rt_err_t s100_uart_configure(struct rt_serial_device *serial,
                                    struct serial_configure *cfg)
{
    struct s100_uart_device *uart;
    s100_uart_reg_t *regs;
    rt_err_t ret;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    if ((cfg->baud_rate == 0u) || (cfg->flowcontrol != RT_SERIAL_FLOWCONTROL_NONE))
    {
        return -RT_EINVAL;
    }

    uart = s100_uart_from_serial(serial);
    regs = s100_uart_regs(uart);

    (*(uint32_t *)SYS_REG_UART_CTRL) |= uart->rx_mask;
    regs->mcr = 0u;

    ret = s100_uart_config_prepare(uart);
    if (ret == RT_EOK)
    {
        ret = s100_uart_set_baud(uart, cfg->baud_rate);
    }

    if (ret == RT_EOK)
    {
        ret = s100_uart_set_lcr(uart, cfg);
    }

    if (ret == RT_EOK)
    {
        s100_uart_set_fifo(uart);
    }

    (*(uint32_t *)SYS_REG_UART_CTRL) &= ~uart->rx_mask;
    return ret;
}

static rt_err_t s100_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct s100_uart_device *uart;
    rt_ubase_t ctrl_arg;

    RT_ASSERT(serial != RT_NULL);

    uart = s100_uart_from_serial(serial);
    ctrl_arg = s100_uart_ctrl_arg_translate((rt_ubase_t)arg);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        s100_uart_disable_irq(uart, ctrl_arg);
        break;

    case RT_DEVICE_CTRL_SET_INT:
    case RT_DEVICE_CTRL_CONFIG:
        if (ctrl_arg != RT_DEVICE_FLAG_INT_RX && ctrl_arg != RT_DEVICE_FLAG_INT_TX)
        {
            return -RT_EINVAL;
        }
        s100_uart_enable_irq(uart, ctrl_arg);
        break;

    case RT_DEVICE_CTRL_CLOSE:
        s100_uart_regs(uart)->ier &= ~UART_IER_ALL;
        rt_hw_interrupt_mask(uart->irqno);
        break;

    default:
        break;
    }

    return RT_EOK;
}

static int s100_uart_putc(struct rt_serial_device *serial, char ch)
{
    struct s100_uart_device *uart;
    s100_uart_reg_t *regs;

    RT_ASSERT(serial != RT_NULL);

    uart = s100_uart_from_serial(serial);
    regs = s100_uart_regs(uart);

    while ((regs->lsr & UART_LSR_THRE) == 0u)
    {
    }

    regs->rbr = (rt_uint8_t)ch;
    return 1;
}

static int s100_uart_getc(struct rt_serial_device *serial)
{
    struct s100_uart_device *uart;
    s100_uart_reg_t *regs;

    RT_ASSERT(serial != RT_NULL);

    uart = s100_uart_from_serial(serial);
    regs = s100_uart_regs(uart);

    if ((regs->usr & UART_USR_RFNE) == 0u)
    {
        return -1;
    }

    return (int)(regs->rbr & 0xffu);
}

static rt_ssize_t s100_uart_transmit(struct rt_serial_device *serial,
                                     rt_uint8_t *buf,
                                     rt_size_t size,
                                     rt_uint32_t tx_flag)
{
    struct s100_uart_device *uart;
    s100_uart_reg_t *regs;
    rt_size_t i;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(buf != RT_NULL);
    RT_UNUSED(tx_flag);

    uart = s100_uart_from_serial(serial);
    regs = s100_uart_regs(uart);

    for (i = 0; i < size; i++)
    {
        while ((regs->usr & UART_USR_TFNF) == 0u)
        {
        }
        regs->rbr = buf[i];
    }

    return size;
}

static const struct rt_uart_ops s100_uart_ops =
{
    .configure = s100_uart_configure,
    .control = s100_uart_control,
    .putc = s100_uart_putc,
    .getc = s100_uart_getc,
    .transmit = s100_uart_transmit,
};

int rt_hw_uart_init(void)
{
    rt_err_t ret = RT_EOK;
    rt_size_t i;

    for (i = 0; i < sizeof(s100_uart_devices) / sizeof(s100_uart_devices[0]); i++)
    {
        s100_uart_config_default(&s100_uart_devices[i]);
        s100_uart_devices[i].serial->ops = &s100_uart_ops;
        s100_uart_devices[i].serial->parent.user_data = &s100_uart_devices[i];

        ret = rt_hw_serial_register(s100_uart_devices[i].serial,
                                    s100_uart_devices[i].device_name,
                                    RT_DEVICE_FLAG_RDWR,
                                    (void *)&s100_uart_devices[i]);
        if (ret != RT_EOK)
        {
            return ret;
        }

        rt_hw_interrupt_install(s100_uart_devices[i].irqno,
                                s100_uart_isr,
                                s100_uart_devices[i].serial,
                                s100_uart_devices[i].device_name);
    }

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif /* RT_USING_SERIAL_V2 */

