/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023/06/25     flyingcys    first version
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_uart.h"

#define DBG_TAG "DRV.UART"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

/*
 * Divide positive or negative dividend by positive divisor and round
 * to closest integer. Result is undefined for negative divisors and
 * for negative dividends if the divisor variable type is unsigned.
 */
#define DIV_ROUND_CLOSEST(x, divisor)(          \
{                           \
    typeof(x) __x = x;              \
    typeof(divisor) __d = divisor;          \
    (((typeof(x))-1) > 0 ||             \
     ((typeof(divisor))-1) > 0 || (__x) > 0) ?  \
        (((__x) + ((__d) / 2)) / (__d)) :   \
        (((__x) - ((__d) / 2)) / (__d));    \
}                           \
)

#define BOTH_EMPTY (UART_LSR_TEMT | UART_LSR_THRE)

struct hw_uart_device
{
    rt_ubase_t hw_base;
    rt_uint32_t irqno;
};

#define BSP_DEFINE_UART_DEVICE(no)                  \
static struct hw_uart_device _uart##no##_device =   \
{                                                   \
    UART##no##_BASE,                           \
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

            if ((value & ~UART_LCR_STKP) == (lcr & ~UART_LCR_STKP))
            {
                return;
            }

            dw8250_write32(addr, UART_FCR, UART_FCR_DEFVAL);
            dw8250_read32(addr, UART_RX);

            *((volatile rt_uint32_t *)(addr + (offset << UART_REG_SHIFT))) = value;
        }
    }
}

static void dw8250_uart_setbrg(rt_ubase_t addr, int baud_divisor)
{
    /* to keep serial format, read lcr before writing BKSE */
    int lcr_val = dw8250_read32(addr, UART_LCR) & ~UART_LCR_BKSE;

    dw8250_write32(addr, UART_LCR, UART_LCR_BKSE | lcr_val);
    dw8250_write32(addr, UART_DLL, baud_divisor & 0xff);

    dw8250_write32(addr, UART_DLM, (baud_divisor >> 8) & 0xff);
    dw8250_write32(addr, UART_LCR, lcr_val);
}

static rt_err_t dw8250_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    rt_base_t base;
    struct hw_uart_device *uart;
    int clock_divisor;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;
    base = uart->hw_base;

    while (!(dw8250_read32(base, UART_LSR) & UART_LSR_TEMT));

    dw8250_write32(base, UART_IER, 0);
    dw8250_write32(base, UART_MCR, UART_MCRVAL);
    dw8250_write32(base, UART_FCR, UART_FCR_DEFVAL);

    /* initialize serial config to 8N1 before writing baudrate */
    dw8250_write32(base, UART_LCR, UART_LCR_8N1);

    clock_divisor = DIV_ROUND_CLOSEST(UART_INPUT_CLK, 16 * serial->config.baud_rate);
    dw8250_uart_setbrg(base, clock_divisor);

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

    while ((dw8250_read32(base, UART_LSR) & BOTH_EMPTY) != BOTH_EMPTY);

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

    if (dw8250_read32(base, UART_LSR) & UART_LSR_DR)
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
        status = dw8250_read32(uart->hw_base, UART_LSR);

        if (!(status & (UART_LSR_DR | UART_LSR_BI)))
        {
            dw8250_read32(uart->hw_base, UART_RX);
        }
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
    struct hw_uart_device* uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    config.baud_rate = 115200;

#define BSP_INSTALL_UART_DEVICE(no)     \
    uart = &_uart##no##_device;         \
    _serial##no.ops    = &_uart_ops;    \
    _serial##no.config = config;        \
    rt_hw_serial_register(&_serial##no, "uart" #no, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart); \
    rt_hw_interrupt_install(uart->irqno, rt_hw_uart_isr, &_serial##no, "uart" #no);

#ifdef RT_USING_UART0
    PINMUX_CONFIG(UART0_RX, UART0_RX);
    PINMUX_CONFIG(UART0_TX, UART0_TX);
    BSP_INSTALL_UART_DEVICE(0);
#if defined(ARCH_ARM)
    uart->hw_base = (rt_size_t)rt_ioremap((void*)uart->hw_base, 0x10000);
#endif /* defined(ARCH_ARM) */
#endif

#ifdef RT_USING_UART1
    PINMUX_CONFIG(IIC0_SDA, UART1_RX);
    PINMUX_CONFIG(IIC0_SCL, UART1_TX);
    BSP_INSTALL_UART_DEVICE(1);
#if defined(ARCH_ARM)
    uart->hw_base = (rt_size_t)rt_ioremap((void*)uart->hw_base, 0x10000);
#endif /* defined(ARCH_ARM) */
#endif

#ifdef RT_USING_UART2
    PINMUX_CONFIG(SD1_D1, UART2_RX);
    PINMUX_CONFIG(SD1_D2, UART2_TX);
    BSP_INSTALL_UART_DEVICE(2);
#if defined(ARCH_ARM)
    uart->hw_base = (rt_size_t)rt_ioremap((void*)uart->hw_base, 0x10000);
#endif /* defined(ARCH_ARM) */
#endif

#ifdef RT_USING_UART3
    PINMUX_CONFIG(SD1_D1, UART3_RX);
    PINMUX_CONFIG(SD1_D2, UART3_TX);
    BSP_INSTALL_UART_DEVICE(3);
#if defined(ARCH_ARM)
    uart->hw_base = (rt_size_t)rt_ioremap((void*)uart->hw_base, 0x10000);
#endif /* defined(ARCH_ARM) */
#endif

#ifdef RT_USING_UART4
    PINMUX_CONFIG(SD1_GP0, UART4_RX);
    PINMUX_CONFIG(SD1_GP1, UART4_TX);
    BSP_INSTALL_UART_DEVICE(4);
#if defined(ARCH_ARM)
    uart->hw_base = (rt_size_t)rt_ioremap((void*)uart->hw_base, 0x10000);
#endif /* defined(ARCH_ARM) */
#endif

    return 0;
}
