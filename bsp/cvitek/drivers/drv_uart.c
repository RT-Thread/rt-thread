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
#include "drv_pinmux.h"
#include "drv_ioremap.h"

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

#ifdef BSP_USING_UART0
BSP_DEFINE_UART_DEVICE(0);
#endif

#ifdef BSP_USING_UART1
BSP_DEFINE_UART_DEVICE(1);
#endif

#ifdef BSP_USING_UART2
BSP_DEFINE_UART_DEVICE(2);
#endif

#ifdef BSP_USING_UART3
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
    int last_ier_state;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct hw_uart_device *)serial->parent.user_data;
    base = uart->hw_base;

    while (!(dw8250_read32(base, UART_LSR) & UART_LSR_TEMT));

    last_ier_state = dw8250_read32(base, UART_IER);
    dw8250_write32(base, UART_IER, 0);
    dw8250_write32(base, UART_MCR, UART_MCRVAL);
    dw8250_write32(base, UART_FCR, UART_FCR_DEFVAL);

    /* initialize serial config to 8N1 before writing baudrate */
    dw8250_write32(base, UART_LCR, UART_LCR_8N1);

    clock_divisor = DIV_ROUND_CLOSEST(UART_INPUT_CLK, 16 * serial->config.baud_rate);
    dw8250_uart_setbrg(base, clock_divisor);

    dw8250_write32(base, UART_IER, last_ier_state);

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

#if defined(BOARD_TYPE_MILKV_DUO) || defined(BOARD_TYPE_MILKV_DUO_SPINOR)

#ifdef BSP_USING_UART0
static const char *pinname_whitelist_uart0_rx[] = {
    "UART0_RX",
    NULL,
};
static const char *pinname_whitelist_uart0_tx[] = {
    "UART0_TX",
    NULL,
};
#endif

#ifdef BSP_USING_UART1
static const char *pinname_whitelist_uart1_rx[] = {
    "IIC0_SDA",
    "UART0_RX",
    NULL,
};
static const char *pinname_whitelist_uart1_tx[] = {
    "IIC0_SCL",
    "UART0_TX",
    NULL,
};
#endif

#ifdef BSP_USING_UART2
static const char *pinname_whitelist_uart2_rx[] = {
    "IIC0_SDA",
    "SD1_D1",
    NULL,
};
static const char *pinname_whitelist_uart2_tx[] = {
    "IIC0_SCL",
    "SD1_D2",
    NULL,
};
#endif

#ifdef BSP_USING_UART3
static const char *pinname_whitelist_uart3_rx[] = {
    "SD1_D1",
    NULL,
};
static const char *pinname_whitelist_uart3_tx[] = {
    "SD1_D2",
    NULL,
};
#endif

#ifdef BSP_USING_UART4
static const char *pinname_whitelist_uart4_rx[] = {
    "SD1_GPIO0",
    NULL,
};
static const char *pinname_whitelist_uart4_tx[] = {
    "SD1_GPIO1",
    NULL,
};
#endif

#elif defined(BOARD_TYPE_MILKV_DUO256M) || defined(BOARD_TYPE_MILKV_DUO256M_SPINOR)

#ifdef BSP_USING_UART0
static const char *pinname_whitelist_uart0_rx[] = {
    "UART0_RX",
    NULL,
};
static const char *pinname_whitelist_uart0_tx[] = {
    "UART0_TX",
    NULL,
};
#endif

#ifdef BSP_USING_UART1
static const char *pinname_whitelist_uart1_rx[] = {
    "IIC0_SDA",
    "JTAG_CPU_TCK",
    "UART0_RX",
    NULL,
};
static const char *pinname_whitelist_uart1_tx[] = {
    "IIC0_SCL",
    "JTAG_CPU_TMS",
    "UART0_TX",
    NULL,
};
#endif

#ifdef BSP_USING_UART2
static const char *pinname_whitelist_uart2_rx[] = {
    "IIC0_SDA",
    "SD1_D1",
    NULL,
};
static const char *pinname_whitelist_uart2_tx[] = {
    "IIC0_SCL",
    "SD1_D2",
    NULL,
};
#endif

#ifdef BSP_USING_UART3
static const char *pinname_whitelist_uart3_rx[] = {
    "SD1_D1",
    NULL,
};
static const char *pinname_whitelist_uart3_tx[] = {
    "SD1_D2",
    NULL,
};
#endif

#ifdef BSP_USING_UART4
static const char *pinname_whitelist_uart4_rx[] = {
    NULL,
};
static const char *pinname_whitelist_uart4_tx[] = {
    NULL,
};
#endif

#elif defined(BOARD_TYPE_MILKV_DUOS)

#ifdef BSP_USING_UART0
static const char *pinname_whitelist_uart0_rx[] = {
    "UART0_RX",
    NULL,
};
static const char *pinname_whitelist_uart0_tx[] = {
    "UART0_TX",
    NULL,
};
#endif

#ifdef BSP_USING_UART1
static const char *pinname_whitelist_uart1_rx[] = {
    "JTAG_CPU_TCK",
    "UART0_RX",
    NULL,
};
static const char *pinname_whitelist_uart1_tx[] = {
    "JTAG_CPU_TMS",
    "UART0_TX",
    "IIC0_SCL",
    NULL,
};
#endif

#ifdef BSP_USING_UART2
static const char *pinname_whitelist_uart2_rx[] = {
    "VIVO_D9",
    "VIVO_D5",
    "VIVO_CLK",
    "PWR_GPIO1",
    NULL,
};
static const char *pinname_whitelist_uart2_tx[] = {
    "VIVO_D10",
    "VIVO_D6",
    "VIVO_D2",
    "IIC0_SCL",
    "PWR_GPIO0",
    NULL,
};
#endif

#ifdef BSP_USING_UART3
static const char *pinname_whitelist_uart3_rx[] = {
    "ADC2",
    NULL,
};
static const char *pinname_whitelist_uart3_tx[] = {
    "ADC3",
    NULL,
};
#endif

#ifdef BSP_USING_UART4
static const char *pinname_whitelist_uart4_rx[] = {
    NULL,
};
static const char *pinname_whitelist_uart4_tx[] = {
    NULL,
};
#endif

#else
    #error "Unsupported board type!"
#endif

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

#ifdef BSP_USING_UART0
    pinmux_config(BSP_UART0_RX_PINNAME, UART0_RX, pinname_whitelist_uart0_rx);
    pinmux_config(BSP_UART0_TX_PINNAME, UART0_TX, pinname_whitelist_uart0_tx);
    BSP_INSTALL_UART_DEVICE(0);

    uart->hw_base = (rt_ubase_t)DRV_IOREMAP((void*)uart->hw_base, 0x10000);
#endif

#ifdef BSP_USING_UART1
    pinmux_config(BSP_UART1_RX_PINNAME, UART1_RX, pinname_whitelist_uart1_rx);
    pinmux_config(BSP_UART1_TX_PINNAME, UART1_TX, pinname_whitelist_uart1_tx);
    BSP_INSTALL_UART_DEVICE(1);

    uart->hw_base = (rt_ubase_t)DRV_IOREMAP((void*)uart->hw_base, 0x10000);
#endif

#ifdef BSP_USING_UART2
    pinmux_config(BSP_UART2_RX_PINNAME, UART2_RX, pinname_whitelist_uart2_rx);
    pinmux_config(BSP_UART2_TX_PINNAME, UART2_TX, pinname_whitelist_uart2_tx);
    BSP_INSTALL_UART_DEVICE(2);

    uart->hw_base = (rt_ubase_t)DRV_IOREMAP((void*)uart->hw_base, 0x10000);
#endif

#ifdef BSP_USING_UART3
    pinmux_config(BSP_UART3_RX_PINNAME, UART3_RX, pinname_whitelist_uart3_rx);
    pinmux_config(BSP_UART3_TX_PINNAME, UART3_TX, pinname_whitelist_uart3_tx);
    BSP_INSTALL_UART_DEVICE(3);

    uart->hw_base = (rt_ubase_t)DRV_IOREMAP((void*)uart->hw_base, 0x10000);
#endif

#ifdef BSP_USING_UART4
    pinmux_config(BSP_UART4_RX_PINNAME, UART4_RX, pinname_whitelist_uart4_rx);
    pinmux_config(BSP_UART4_TX_PINNAME, UART4_TX, pinname_whitelist_uart4_tx);
    BSP_INSTALL_UART_DEVICE(4);

    uart->hw_base = (rt_ubase_t)DRV_IOREMAP((void*)uart->hw_base, 0x10000);
#endif

    return 0;
}
