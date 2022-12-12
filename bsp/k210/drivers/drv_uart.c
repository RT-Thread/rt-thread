/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_uart.h"

#include <stdio.h>
#include <sysctl.h>

#include "uart.h"
#include "uarths.h"
#include "plic.h"

#define UART_DEFAULT_BAUDRATE               115200

static volatile uarths_t *const _uarths = (volatile uarths_t *)UARTHS_BASE_ADDR;

struct device_uart
{
    rt_uint32_t hw_base;
    rt_uint32_t irqno;
};

static rt_err_t  rt_uarths_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t  uarths_control(struct rt_serial_device *serial, int cmd, void *arg);
static int       drv_uarths_putc(struct rt_serial_device *serial, char c);
static int       drv_uarths_getc(struct rt_serial_device *serial);

static void     uarths_irq_handler(int irqno, void *param);

static rt_err_t  rt_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t  uart_control(struct rt_serial_device *serial, int cmd, void *arg);
static int       drv_uart_putc(struct rt_serial_device *serial, char c);
static int       drv_uart_getc(struct rt_serial_device *serial);

static void     uart_irq_handler(int irqno, void *param);

const struct rt_uart_ops _uart_hs_ops =
{
    rt_uarths_configure,
    uarths_control,
    drv_uarths_putc,
    drv_uarths_getc,
    RT_NULL
};

const struct rt_uart_ops _uart_ops =
{
    rt_uart_configure,
    uart_control,
    drv_uart_putc,
    drv_uart_getc,
    //TODO: add DMA support
    RT_NULL
};

/* START ported from kendryte standalone sdk uart.c */
#define __UART_BRATE_CONST  16

volatile uart_t* const  _uart[3] =
{
    (volatile uart_t*)UART1_BASE_ADDR,
    (volatile uart_t*)UART2_BASE_ADDR,
    (volatile uart_t*)UART3_BASE_ADDR
};

void _uart_init(uart_device_number_t channel)
{
    sysctl_clock_enable(SYSCTL_CLOCK_UART1 + channel);
    sysctl_reset(SYSCTL_RESET_UART1 + channel);
}

/* END ported from kendryte standalone sdk uart.c */
static inline uart_device_number_t _get_uart_channel(rt_uint32_t addr)
{
    switch (addr)
    {
        case UART1_BASE_ADDR:
            return UART_DEVICE_1;
        case UART2_BASE_ADDR:
            return UART_DEVICE_2;
        case UART3_BASE_ADDR:
            return UART_DEVICE_3;
        default:
            return UART_DEVICE_MAX;
    }
}

/*
 * UART Initiation
 */
int rt_hw_uart_init(void)
{
    struct rt_serial_device *serial;
    struct device_uart      *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef BSP_USING_UART_HS
    {
        static struct rt_serial_device  serial_hs;
        static struct device_uart       uart_hs;

        serial  = &serial_hs;
        uart    = &uart_hs;

        serial->ops              = &_uart_hs_ops;
        serial->config           = config;
        serial->config.baud_rate = 115200;

        uart->hw_base   = UARTHS_BASE_ADDR;
        uart->irqno     = IRQN_UARTHS_INTERRUPT;

        rt_hw_serial_register(serial,
                              "uarths",
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              uart);
    }
#endif

#ifdef BSP_USING_UART1
    {
        static struct rt_serial_device  serial1;
        static struct device_uart       uart1;

        serial  = &serial1;
        uart    = &uart1;

        serial->ops              = &_uart_ops;
        serial->config           = config;
        serial->config.baud_rate = UART_DEFAULT_BAUDRATE;

        uart->hw_base   = UART1_BASE_ADDR;
        uart->irqno     = IRQN_UART1_INTERRUPT;

        _uart_init(UART_DEVICE_1);

        rt_hw_serial_register(serial,
                              "uart1",
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              uart);
    }
#endif

#ifdef BSP_USING_UART2
    {
        static struct rt_serial_device  serial2;
        static struct device_uart       uart2;

        serial  = &serial2;
        uart    = &uart2;

        serial->ops              = &_uart_ops;
        serial->config           = config;
        serial->config.baud_rate = UART_DEFAULT_BAUDRATE;

        uart->hw_base   = UART2_BASE_ADDR;
        uart->irqno     = IRQN_UART2_INTERRUPT;

        _uart_init(UART_DEVICE_2);

        rt_hw_serial_register(serial,
                              "uart2",
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              uart);
    }
#endif

#ifdef BSP_USING_UART3
    {
        static struct rt_serial_device  serial3;
        static struct device_uart       uart3;

        serial  = &serial3;
        uart    = &uart3;

        serial->ops              = &_uart_ops;
        serial->config           = config;
        serial->config.baud_rate = UART_DEFAULT_BAUDRATE;

        uart->hw_base   = UART3_BASE_ADDR;
        uart->irqno     = IRQN_UART3_INTERRUPT;

        _uart_init(UART_DEVICE_3);

        rt_hw_serial_register(serial,
                              "uart3",
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              uart);
    }
#endif

    return 0;
}

/*
 * UARTHS interface
 */
static rt_err_t rt_uarths_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct device_uart *uart;
    uint32_t freq_hs = sysctl_clock_get_freq(SYSCTL_CLOCK_CPU);
    uint16_t div_hs = freq_hs / cfg->baud_rate - 1;

    RT_ASSERT(serial != RT_NULL);
    serial->config = *cfg;

    uart = serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    if (uart->hw_base == UARTHS_BASE_ADDR)
    {
        _uarths->div.div = div_hs;
        _uarths->txctrl.txen = 1;
        _uarths->rxctrl.rxen = 1;
        _uarths->txctrl.txcnt = 0;
        _uarths->rxctrl.rxcnt = 0;
        _uarths->ip.txwm = 1;
        _uarths->ip.rxwm = 1;
        _uarths->ie.txwm = 0;
        _uarths->ie.rxwm = 1;
    }
    else
    {
        return (-1);
        /* other uart */
    }

    return (RT_EOK);
}

static rt_err_t uarths_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct device_uart *uart;

    uart = serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* Disable the UART Interrupt */
        rt_hw_interrupt_mask(uart->irqno);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* install interrupt */
        rt_hw_interrupt_install(uart->irqno, uarths_irq_handler,
                                serial, serial->parent.parent.name);
        rt_hw_interrupt_umask(uart->irqno);
        break;
    }

    return (RT_EOK);
}


static int drv_uarths_putc(struct rt_serial_device *serial, char c)
{
    struct device_uart *uart = serial->parent.user_data;
    RT_ASSERT(uart->hw_base == UARTHS_BASE_ADDR);

    while (_uarths->txdata.full);
    _uarths->txdata.data = (uint8_t)c;

    return (1);
}

static int drv_uarths_getc(struct rt_serial_device *serial)
{
    struct device_uart *uart = serial->parent.user_data;
    RT_ASSERT(uart->hw_base == UARTHS_BASE_ADDR);

    uarths_rxdata_t recv = _uarths->rxdata;
    if (recv.empty)
        return EOF;
    else
        return (recv.data & 0xff);
    /* Receive Data Available */

    return (-1);
}

/* UARTHS ISR */
static void uarths_irq_handler(int irqno, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;
    struct device_uart *uart = serial->parent.user_data;
    RT_ASSERT(uart->hw_base == UARTHS_BASE_ADDR);

    /* read interrupt status and clear it */
    if (_uarths->ip.rxwm)
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
}

/*
 * UART interface
 */
static rt_err_t rt_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct device_uart *uart;
    uart_bitwidth_t data_width = (uart_bitwidth_t)cfg->data_bits ;
    uart_stopbit_t stopbit = (uart_stopbit_t)cfg->stop_bits;
    uart_parity_t parity = (uart_parity_t)cfg->parity;

    uint32_t freq = sysctl_clock_get_freq(SYSCTL_CLOCK_APB0);
    uint32_t divisor = freq / (uint32_t)cfg->baud_rate;
    uint8_t dlh = divisor >> 12;
    uint8_t dll = (divisor - (dlh << 12)) / __UART_BRATE_CONST;
    uint8_t dlf = divisor - (dlh << 12) - dll * __UART_BRATE_CONST;

    RT_ASSERT(serial != RT_NULL);
    serial->config = *cfg;

    uart = serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    uart_device_number_t channel = _get_uart_channel(uart->hw_base);
    RT_ASSERT(channel != UART_DEVICE_MAX);

    RT_ASSERT(data_width >= 5 && data_width <= 8);
    if (data_width == 5)
    {
        RT_ASSERT(stopbit != UART_STOP_2);
    }
    else
    {
        RT_ASSERT(stopbit != UART_STOP_1_5);
    }

    uint32_t stopbit_val = stopbit == UART_STOP_1 ? 0 : 1;
    uint32_t parity_val;
    switch (parity)
    {
        case UART_PARITY_NONE:
            parity_val = 0;
            break;
        case UART_PARITY_ODD:
            parity_val = 1;
            break;
        case UART_PARITY_EVEN:
            parity_val = 3;
            break;
        default:
            RT_ASSERT(!"Invalid parity");
            break;
    }

    _uart[channel]->LCR |= 1u << 7;
    _uart[channel]->DLH = dlh;
    _uart[channel]->DLL = dll;
    _uart[channel]->DLF = dlf;
    _uart[channel]->LCR = 0;
    _uart[channel]->LCR = (data_width - 5) |
                          (stopbit_val << 2) |
                          (parity_val << 3);
    _uart[channel]->LCR &= ~(1u << 7);
    _uart[channel]->IER |= 0x80; /* THRE */
    _uart[channel]->FCR = UART_RECEIVE_FIFO_1 << 6 |
                          UART_SEND_FIFO_8 << 4 |
                          0x1 << 3 |
                          0x1;

    return (RT_EOK);
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct device_uart *uart;

    uart = serial->parent.user_data;
    uart_device_number_t channel = _get_uart_channel(uart->hw_base);

    RT_ASSERT(uart != RT_NULL);
    RT_ASSERT(channel != UART_DEVICE_MAX);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* Disable the UART Interrupt */
        rt_hw_interrupt_mask(uart->irqno);
        _uart[channel]->IER &= ~0x1;
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* install interrupt */
        rt_hw_interrupt_install(uart->irqno, uart_irq_handler,
                                serial, serial->parent.parent.name);
        rt_hw_interrupt_umask(uart->irqno);
        _uart[channel]->IER |= 0x1;
        break;
    }

    return (RT_EOK);
}

static int drv_uart_putc(struct rt_serial_device *serial, char c)
{
    struct device_uart *uart = serial->parent.user_data;
    uart_device_number_t channel = _get_uart_channel(uart->hw_base);
    RT_ASSERT(channel != UART_DEVICE_MAX);

    while (_uart[channel]->LSR & (1u << 5));
    _uart[channel]->THR = c;

    return (1);
}

static int drv_uart_getc(struct rt_serial_device *serial)
{
    struct device_uart *uart = serial->parent.user_data;
    uart_device_number_t channel = _get_uart_channel(uart->hw_base);
    RT_ASSERT(channel != UART_DEVICE_MAX);

    if (_uart[channel]->LSR & 1)
        return (char)(_uart[channel]->RBR & 0xff);
    else
        return EOF;
    /* Receive Data Available */

    return (-1);
}

/* UART ISR */
static void uart_irq_handler(int irqno, void *param)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)param;
    struct device_uart *uart = serial->parent.user_data;
    uart_device_number_t channel = _get_uart_channel(uart->hw_base);
    RT_ASSERT(channel != UART_DEVICE_MAX);

    /* read interrupt status and clear it */
    if (_uart[channel]->LSR)
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
}

/* WEAK for SDK 0.5.6 */

rt_weak void uart_debug_init(uart_device_number_t uart_channel)
{

}

