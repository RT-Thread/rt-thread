/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <board.h>

/*
 * The Synopsys DesignWare 8250 has an extra feature whereby it detects if the
 * LCR is written whilst busy. If it is, then a busy detect interrupt is
 * raised, the LCR needs to be rewritten and the uart status register read.
 */

#define UART_RX             0    /* In: Receive buffer */
#define UART_TX             0    /* Out: Transmit buffer */

#define UART_DLL            0    /* Out: Divisor Latch Low */
#define UART_DLM            1    /* Out: Divisor Latch High */

#define UART_IER            1    /* Out: Interrupt Enable Register */
#define UART_IER_RDI        0x01 /* Enable receiver data interrupt */

#define UART_SSR            0x22 /* In: Software Reset Register */
#define UART_USR            0x1f /* UART Status Register */

#define UART_LCR            3    /* Out: Line Control Register */
#define UART_LCR_DLAB       0x80 /* Divisor latch access bit */
#define UART_LCR_SPAR       0x20 /* Stick parity (?) */
#define UART_LCR_PARITY     0x8  /* Parity Enable */
#define UART_LCR_STOP       0x4  /* Stop bits: 0=1 bit, 1=2 bits */
#define UART_LCR_WLEN8      0x3  /* Wordlength: 8 bits */

#define UART_MCR            4    /* Out: Modem Control Register */
#define UART_MCR_RTS        0x02 /* RTS complement */

#define UART_LSR            5    /* In: Line Status Register */
#define UART_LSR_BI         0x10 /* Break interrupt indicator */
#define UART_LSR_DR         0x01 /* Receiver data ready */

#define UART_IIR            2    /* In: Interrupt ID Register */
#define UART_IIR_NO_INT     0x01 /* No interrupts pending */
#define UART_IIR_BUSY       0x07 /* DesignWare APB Busy Detect */
#define UART_IIR_RX_TIMEOUT 0x0c /* OMAP RX Timeout interrupt */

#define UART_FCR            2    /* Out: FIFO Control Register */
#define UART_FCR_EN_FIFO    0x01 /* Enable the FIFO */
#define UART_FCR_CLEAR_RCVR 0x02 /* Clear the RCVR FIFO */
#define UART_FCR_CLEAR_XMIT 0x04 /* Clear the XMIT FIFO */

#define UART_REG_SHIFT      0x2  /* Register Shift*/
#define UART_INPUT_CLK      24000000

struct hw_uart_device
{
    rt_ubase_t hw_base;
    rt_uint32_t irqno;
#ifdef RT_USING_SMP
    struct rt_spinlock spinlock;
#endif
};

#define BSP_DEFINE_UART_DEVICE(no)                  \
static struct hw_uart_device _uart##no##_device =   \
{                                                   \
    UART##no##_MMIO_BASE,                           \
    UART##no##_IRQ                                  \
};                                                  \
static struct rt_serial_device _serial##no;

#ifdef RT_USING_UART0
BSP_DEFINE_UART_DEVICE(0);
#endif

#ifdef RT_USING_UART1
BSP_DEFINE_UART_DEVICE(1);
#endif

#ifdef RT_USING_UART2
BSP_DEFINE_UART_DEVICE(2);
#endif

#ifdef RT_USING_UART3
BSP_DEFINE_UART_DEVICE(3);
#endif

#ifdef RT_USING_UART4
BSP_DEFINE_UART_DEVICE(4);
#endif

#ifdef RT_USING_UART5
BSP_DEFINE_UART_DEVICE(5);
#endif

#ifdef RT_USING_UART6
BSP_DEFINE_UART_DEVICE(6);
#endif

#ifdef RT_USING_UART7
BSP_DEFINE_UART_DEVICE(7);
#endif

#ifdef RT_USING_UART8
BSP_DEFINE_UART_DEVICE(8);
#endif

#ifdef RT_USING_UART9
BSP_DEFINE_UART_DEVICE(9);
#endif

rt_inline rt_uint32_t dw8250_read32(rt_ubase_t addr, rt_ubase_t offset)
{
    return *((volatile rt_uint32_t *)(addr + (offset << UART_REG_SHIFT)));
}

rt_inline void dw8250_write32(rt_ubase_t addr, rt_ubase_t offset, rt_uint32_t value)
{
    *((volatile rt_uint32_t *)(addr + (offset << UART_REG_SHIFT))) = value;

    if (offset == UART_LCR)
    {
        int tries = 1000;

        /* Make sure LCR write wasn't ignored */
        while (tries--)
        {
            unsigned int lcr = dw8250_read32(addr, UART_LCR);

            if ((value & ~UART_LCR_SPAR) == (lcr & ~UART_LCR_SPAR))
            {
                return;
            }

            dw8250_write32(addr, UART_FCR, UART_FCR_EN_FIFO | UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);
            dw8250_read32(addr, UART_RX);

            *((volatile rt_uint32_t *)(addr + (offset << UART_REG_SHIFT))) = value;
        }
    }
}

static rt_err_t dw8250_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    rt_base_t base, rate;
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;
    base = uart->hw_base;

#ifdef RT_USING_SMP
    rt_spin_lock_init(&uart->spinlock);
#endif

    /* Resset UART */
    dw8250_write32(base, UART_SSR, 1);
    dw8250_write32(base, UART_SSR, 0);

    dw8250_write32(base, UART_IER, !UART_IER_RDI);
    dw8250_write32(base, UART_FCR, UART_FCR_EN_FIFO | UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);

    /* Disable flow ctrl */
    dw8250_write32(base, UART_MCR, 0);
    /* Clear RTS */
    dw8250_write32(base, UART_MCR, dw8250_read32(base, UART_MCR) | UART_MCR_RTS);

    rate = UART_INPUT_CLK / 16 / serial->config.baud_rate;

    /* Enable access DLL & DLH */
    dw8250_write32(base, UART_LCR, dw8250_read32(base, UART_LCR) | UART_LCR_DLAB);
    dw8250_write32(base, UART_DLL, (rate & 0xff));
    dw8250_write32(base, UART_DLM, (rate & 0xff00) >> 8);
    /* Clear DLAB bit */
    dw8250_write32(base, UART_LCR, dw8250_read32(base, UART_LCR) & (~UART_LCR_DLAB));

    dw8250_write32(base, UART_LCR, (dw8250_read32(base, UART_LCR) & (~UART_LCR_WLEN8)) | UART_LCR_WLEN8);
    dw8250_write32(base, UART_LCR, dw8250_read32(base, UART_LCR) & (~UART_LCR_STOP));
    dw8250_write32(base, UART_LCR, dw8250_read32(base, UART_LCR) & (~UART_LCR_PARITY));

    dw8250_write32(base, UART_IER, UART_IER_RDI);

    return RT_EOK;
}

static rt_err_t dw8250_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;

    switch (cmd)
    {
        case RT_DEVICE_CTRL_CLR_INT:
            /* Disable rx irq */
            dw8250_write32(uart->hw_base, UART_IER, !UART_IER_RDI);
            rt_hw_interrupt_mask(uart->irqno);
            break;

        case RT_DEVICE_CTRL_SET_INT:
            /* Enable rx irq */
            dw8250_write32(uart->hw_base, UART_IER, UART_IER_RDI);
            rt_hw_interrupt_umask(uart->irqno);
            break;
    }

    return RT_EOK;
}

static int dw8250_uart_putc(struct rt_serial_device *serial, char c)
{
    rt_base_t base;
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;
    base = uart->hw_base;

    while ((dw8250_read32(base, UART_USR) & 0x2) == 0)
    {
    }

    dw8250_write32(base, UART_TX, c);

    return 1;
}

static int dw8250_uart_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    rt_base_t base;
    struct hw_uart_device *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;
    base = uart->hw_base;

    if ((dw8250_read32(base, UART_LSR) & 0x1))
    {
        ch = dw8250_read32(base, UART_RX) & 0xff;
    }

    return ch;
}

static const struct rt_uart_ops _uart_ops =
{
    dw8250_uart_configure,
    dw8250_uart_control,
    dw8250_uart_putc,
    dw8250_uart_getc,
};

static void rt_hw_uart_isr(int irqno, void *param)
{
    unsigned int iir, status;
    struct rt_serial_device *serial = (struct rt_serial_device *)param;
    struct hw_uart_device *uart = (struct hw_uart_device *)serial->parent.user_data;

    iir = dw8250_read32(uart->hw_base, UART_IIR);

    /* If don't do this in non-DMA mode then the "RX TIMEOUT" interrupt will fire forever. */
    if ((iir & 0x3f) == UART_IIR_RX_TIMEOUT)
    {
#ifdef RT_USING_SMP
        rt_base_t level = rt_spin_lock_irqsave(&uart->spinlock);
#endif

        status = dw8250_read32(uart->hw_base, UART_LSR);

        if (!(status & (UART_LSR_DR | UART_LSR_BI)))
        {
            dw8250_read32(uart->hw_base, UART_RX);
        }

#ifdef RT_USING_SMP
        rt_spin_unlock_irqrestore(&uart->spinlock, level);
#endif
    }

    if (!(iir & UART_IIR_NO_INT))
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }

    if ((iir & UART_IIR_BUSY) == UART_IIR_BUSY)
    {
        /* Clear the USR */
        dw8250_read32(uart->hw_base, UART_USR);

        return;
    }
}

int rt_hw_uart_init(void)
{
    rt_uint32_t value;
    struct hw_uart_device* uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    RT_UNUSED(value);

    config.baud_rate = 1500000;

#define BSP_INSTALL_UART_DEVICE(no)     \
    uart = &_uart##no##_device;         \
    _serial##no.ops    = &_uart_ops;    \
    _serial##no.config = config;        \
    rt_hw_serial_register(&_serial##no, "uart" #no, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart); \
    rt_hw_interrupt_install(uart->irqno, rt_hw_uart_isr, &_serial##no, "uart" #no);

#ifdef RT_USING_UART0
    BSP_INSTALL_UART_DEVICE(0);
#endif

#ifdef RT_USING_UART1
    BSP_INSTALL_UART_DEVICE(1);
#endif

#ifdef RT_USING_UART2
    BSP_INSTALL_UART_DEVICE(2);
#endif

#ifdef RT_USING_UART3
    BSP_INSTALL_UART_DEVICE(3);
#endif

#ifdef RT_USING_UART4
    HWREG32(CRU_BASE + 0x370) = 0xFFFF0000 | (0x600) |(HWREG32(CRU_BASE + 0x370) & 0xF0FF);
    value = HWREG32(0xFDC60000 + 0x48);
    value &= ~((7 << 8) | (7 << 4));
    value |= 0xFFFF0000 | (4 << 8) | (4 << 4);
    HWREG32(0xFDC60000 + 0x48) = value;
    HWREG32(0xFDC60000 + 0x30C) = 0xFFFF0000 | (1 << 14) | HWREG32(0xFDC60000 + 0x30C);
    BSP_INSTALL_UART_DEVICE(4);
#endif

#ifdef RT_USING_UART5
    BSP_INSTALL_UART_DEVICE(5);
#endif

#ifdef RT_USING_UART6
    BSP_INSTALL_UART_DEVICE(6);
#endif

#ifdef RT_USING_UART7
    BSP_INSTALL_UART_DEVICE(7);
#endif

#ifdef RT_USING_UART8
    BSP_INSTALL_UART_DEVICE(8);
#endif

#ifdef RT_USING_UART9
    BSP_INSTALL_UART_DEVICE(9);
#endif

    return 0;
}
