/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "drv_uart.h"
#include "interrupt.h"

#include "drv_gpio.h"
#include "drv_clock.h"

#define readl(addr)           (*(volatile unsigned int *)(addr))
#define writel(value,addr)    (*(volatile unsigned int *)(addr) = (value))

#ifdef RT_USING_SERIAL

struct device_uart
{
    rt_uint32_t hw_base;
    rt_uint32_t irqno;
    char name[RT_NAME_MAX];
    rt_uint32_t gpio_rx_port;
    rt_uint32_t gpio_tx_port;
    rt_uint32_t gpio_rx_pin;
    rt_uint32_t gpio_tx_pin;
    rt_uint32_t gpio_rx_fun;
    rt_uint32_t gpio_tx_fun;
};

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg);
static int      uart_putc(struct rt_serial_device *serial, char c);
static int      uart_getc(struct rt_serial_device *serial);
static rt_size_t uart_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction);

void     uart_irq_handler(int irqno, void *param);

const struct rt_uart_ops _uart_ops =
{
    uart_configure,
    uart_control,
    uart_putc,
    uart_getc,
    uart_dma_transmit
};

/*
 * UART Initiation
 */
int rt_hw_uart_init(void)
{
    struct rt_serial_device *serial;
    struct device_uart      *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef TINA_USING_UART0
    {
        static struct rt_serial_device  serial0;
        static struct device_uart       uart0;

        serial  = &serial0;
        uart    = &uart0;

        serial->ops              = &_uart_ops;
        serial->config           = config;
        serial->config.baud_rate = 115200;

        uart->hw_base      = UART0_BASE_ADDR; // UART0_BASE;
        uart->irqno        = UART0_INTERRUPT; // IRQ_UART0;
        uart->gpio_rx_port = GPIO_PORT_E;
        uart->gpio_tx_port = GPIO_PORT_E;
        uart->gpio_rx_pin  = GPIO_PIN_0;
        uart->gpio_tx_pin  = GPIO_PIN_1;
        uart->gpio_rx_fun  = IO_FUN_4;
        uart->gpio_tx_fun  = IO_FUN_4;

        rt_hw_serial_register(serial,
                              "uart0",
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              uart);
    }
#endif

#ifdef TINA_USING_UART1
    {
        static struct rt_serial_device  serial1;
        static struct device_uart       uart1;

        serial  = &serial1;
        uart    = &uart1;

        serial->ops              = &_uart_ops;
        serial->config           = config;
        serial->config.baud_rate = 115200;

        uart->hw_base      = UART1_BASE_ADDR; // UART1_BASE;
        uart->irqno        = UART1_INTERRUPT; // IRQ_UART1;
        uart->gpio_rx_port = GPIO_PORT_A;
        uart->gpio_tx_port = GPIO_PORT_A;
        uart->gpio_rx_pin  = GPIO_PIN_2;
        uart->gpio_tx_pin  = GPIO_PIN_3;
        uart->gpio_rx_fun  = IO_FUN_4;
        uart->gpio_tx_fun  = IO_FUN_4;

        rt_hw_serial_register(serial,
                              "uart1",
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              uart);
    }
#endif

#ifdef TINA_USING_UART2
    {
        static struct rt_serial_device  serial2;
        static struct device_uart       uart2;

        serial  = &serial2;
        uart    = &uart2;

        serial->ops              = &_uart_ops;
        serial->config           = config;
        serial->config.baud_rate = 115200;

        uart->hw_base      = UART2_BASE_ADDR; // UART1_BASE;
        uart->irqno        = UART2_INTERRUPT; // IRQ_UART1;
        uart->gpio_rx_port = GPIO_PORT_E;
        uart->gpio_tx_port = GPIO_PORT_E;
        uart->gpio_rx_pin  = GPIO_PIN_8;
        uart->gpio_tx_pin  = GPIO_PIN_7;
        uart->gpio_rx_fun  = IO_FUN_2;
        uart->gpio_tx_fun  = IO_FUN_2;

        rt_hw_serial_register(serial,
                              "uart2",
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              uart);
    }
#endif

    return 0;
}

/*
 * UART interface
 */
static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    rt_uint32_t addr, val;
    struct device_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    serial->config = *cfg;

    uart = serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);
    /* config gpio port */
    gpio_set_func(uart->gpio_rx_port, uart->gpio_rx_pin, uart->gpio_rx_fun);
    gpio_set_func(uart->gpio_tx_port, uart->gpio_tx_pin, uart->gpio_tx_fun);
    /* Enable UART clock */
    /* Open the clock gate for uart */
    if ((rt_uint32_t)(uart->hw_base) == UART0_BASE_ADDR)
    {
        bus_gate_clk_enalbe(UART0_GATING);
        bus_software_reset_enalbe(UART0_GATING);
        bus_software_reset_disalbe(UART0_GATING);
    }
    else if ((rt_uint32_t)(uart->hw_base) == UART1_BASE_ADDR)
    {
        bus_gate_clk_enalbe(UART1_GATING);
        bus_software_reset_enalbe(UART1_GATING);
        bus_software_reset_disalbe(UART1_GATING);
    }
    else if ((rt_uint32_t)(uart->hw_base) == UART2_BASE_ADDR)
    {
        bus_gate_clk_enalbe(UART2_GATING);
        bus_software_reset_enalbe(UART2_GATING);
        bus_software_reset_disalbe(UART2_GATING);
    }
    else
        RT_ASSERT(0);
    /* Config uart0 to 115200-8-1-0 */
    addr = uart->hw_base;
    /* close uart irq */
    writel(0x0, addr + UART_IER);
    /* config fifo */
    writel(0x37, addr + UART_FCR);
    /* config modem */
    writel(0x0, addr + UART_MCR);
    /* config baud */
    val = readl(addr + UART_LCR);
    val |= (1 << 7);
    writel(val, addr + UART_LCR);
    val = apb_get_clk() / 16 / serial->config.baud_rate;
    writel(val & 0xff, addr + UART_DLL);
    writel((val >> 8) & 0xff, addr + UART_DLH);
    val = readl(addr + UART_LCR);
    val &= ~(1 << 7);
    writel(val, addr + UART_LCR);

    val = readl(addr + UART_LCR);
    val &= ~0x1f;
    val |= ((serial->config.data_bits - DATA_BITS_5) << 0) | (0 << 2) | (0x0 << 3);
    writel(val, addr + UART_LCR);

    writel(0xf, addr + UART_TFL);
    writel(0x3F, addr + UART_RFL);

    writel(0x1, addr + UART_IER);
    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct device_uart *uart;

    uart = serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* Disable the UART Interrupt */
        rt_hw_interrupt_mask(uart->irqno);
        writel(0x00, uart->hw_base + UART_IER);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* install interrupt */
        rt_hw_interrupt_install(uart->irqno, uart_irq_handler,
                                serial, uart->name);
        rt_hw_interrupt_umask(uart->irqno);
        writel(0x01, uart->hw_base + UART_IER);
        /* Enable the UART Interrupt */
        break;
    }

    return (RT_EOK);
}


static int uart_putc(struct rt_serial_device *serial, char c)
{
    struct device_uart *uart;
    volatile rt_uint32_t *sed_buf;
    volatile rt_uint32_t *sta;

    uart = serial->parent.user_data;
    sed_buf = (rt_uint32_t *)(uart->hw_base + UART_THR);
    sta = (rt_uint32_t *)(uart->hw_base + UART_USR);
    /* FIFO status, contain valid data */
    while (!(*sta & 0x02));
    *sed_buf = c;

    return (1);
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    volatile rt_uint32_t *rec_buf;
    volatile rt_uint32_t *sta;
    struct device_uart *uart = serial->parent.user_data;

    RT_ASSERT(serial != RT_NULL);

    rec_buf = (rt_uint32_t *)(uart->hw_base + UART_RHB);
    sta = (rt_uint32_t *)(uart->hw_base + UART_USR);
    /* Receive Data Available */
    if (*sta & 0x08)
    {
        ch = *rec_buf & 0xff;
    }

    return ch;
}

static rt_size_t uart_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    return (0);
}

/* UART ISR */
void uart_irq_handler(int irqno, void *param)
{
    rt_uint32_t val;
    struct rt_serial_device *serial = (struct rt_serial_device *)param;
    struct device_uart *uart = serial->parent.user_data;

    val = readl(uart->hw_base + 0x08) & 0x0F;
    /* read interrupt status and clear it */
    if (val & 0x4) /* rx ind */
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }

    if (0) /* tx done */
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);
    }

}

#endif
