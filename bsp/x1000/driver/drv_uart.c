/*
 * File      : drv_uart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-11-19     Urey         the first version
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_uart.h"

struct jz_uart_s
{
    rt_uint32_t hw_base;

    rt_uint32_t irqno;
    char name[RT_NAME_MAX];
};

static rt_err_t uart_configure          (struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t uart_control            (struct rt_serial_device *serial, int cmd, void *arg);
static int      uart_putc               (struct rt_serial_device *serial, char c);
static int      uart_getc               (struct rt_serial_device *serial);
static rt_size_t uart_dma_transmit      (struct rt_serial_device *serial, const rt_uint8_t *buf, rt_size_t size, int direction);

static void     uart_irq_handler        (int irqno, void *param);

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
void rt_hw_uart_init(void)
{
    struct rt_serial_device *serial;
    struct jz_uart_s        *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef RT_USING_UART1
    {
        static struct rt_serial_device  serial1;
        static struct jz_uart_s         uart1;

        serial  = &serial1;
        uart    = &uart1;

        serial->ops              = &_uart_ops;
        serial->config           = config;
        serial->config.baud_rate = 115200;

        uart->hw_base   = UART0_BASE;
        uart->irqno     = IRQ_UART0;

        rt_hw_serial_register(serial,
                              "uart1",
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              uart);
    }
#endif

#ifdef RT_USING_UART2
    {
        static struct rt_serial_device  serial2;
        static struct jz_uart_s         uart2;

        serial  = &serial2;
        uart    = &uart2;

        serial->ops              = &_uart_ops;
        serial->config           = config;
        serial->config.baud_rate = 115200;

        uart->hw_base   = UART2_BASE;
        uart->irqno     = IRQ_UART2;

        rt_hw_serial_register(serial,
                              "uart2",
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              uart);
    }
#endif

#ifdef RT_USING_UART3
    {
        static struct rt_serial_device  serial3;
        static struct jz_uart_s         uart3;

        serial  = &serial3;
        uart    = &uart3;

        serial->ops              = &_uart_ops;
        serial->config           = config;
        serial->config.baud_rate = 115200;

        uart->hw_base   = UART3_BASE;
        uart->irqno     = IRQ_UART3;

        rt_hw_serial_register(serial,
                              "uart3",
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              uart);
    }
#endif
}

/*
 * UART interface
 */
static rt_err_t uart_configure (struct rt_serial_device *serial, struct serial_configure *cfg)
{
    rt_uint32_t baud_div;
    struct jz_uart_s * uart;

    RT_ASSERT(serial != RT_NULL);
    serial->config = *cfg;

    uart = serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    /* Init UART Hardware */
     UART_IER(uart->hw_base) = 0; /* clear interrupt */
     UART_FCR(uart->hw_base) = ~UARTFCR_UUE; /* disable UART unite */

     /* Enable UART clock */

     /* Set both receiver and transmitter in UART mode (not SIR) */
     UART_SIRCR(uart->hw_base) = ~(SIRCR_RSIRE | SIRCR_TSIRE);

     /* Set databits, stopbits and parity. (8-bit data, 1 stopbit, no parity) */
     UART_LCR(uart->hw_base) = UARTLCR_WLEN_8;

     /* set baudrate */
 #if defined(RT_USING_JZ4750) || defined(RT_USING_JZ4755) || defined(RT_USING_JZ4760)
     if(REG_CPM_CPCCR & (1UL << 30))
     {
         /* CPCCR.ECS = 1: clock source is EXCLK/2 */
         baud_div = BOARD_EXTAL_CLK / 2 / 16 / cfg->baud_rate;
     }
     else
 #endif
     {
         /* CPCCR.ECS = 0: clock source is EXCLK */
         baud_div = BOARD_EXTAL_CLK / 16 / cfg->baud_rate;
     }

     UART_LCR(uart->hw_base) |= UARTLCR_DLAB;
     UART_DLHR(uart->hw_base) = (baud_div >> 8) & 0xff;
     UART_DLLR(uart->hw_base) = baud_div & 0xff;

     UART_LCR(uart->hw_base) &= ~UARTLCR_DLAB;

     /* Enable UART unit, enable and clear FIFO */
     UART_FCR(uart->hw_base) = UARTFCR_UUE | UARTFCR_FE | UARTFCR_TFLS | UARTFCR_RFLS;

     return (RT_EOK);
}

static rt_err_t uart_control (struct rt_serial_device *serial, int cmd, void *arg)
{
    struct jz_uart_s * uart;

    uart = serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* Disable the UART Interrupt */
        UART_IER(uart->hw_base) &= ~(UARTIER_RIE | UARTIER_RTIE);
        rt_hw_interrupt_mask(uart->irqno);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* install interrupt */
        rt_hw_interrupt_install(uart->irqno, uart_irq_handler,
                                serial, uart->name);
        rt_hw_interrupt_umask(uart->irqno);

        /* Enable the UART Interrupt */
        UART_IER(uart->hw_base) |= (UARTIER_RIE | UARTIER_RTIE);
        break;
    }

    return (RT_EOK);
}

static int uart_putc (struct rt_serial_device *serial, char c)
{
    struct jz_uart_s* uart;

    uart = serial->parent.user_data;

    /* FIFO status, contain valid data */
    while (!((UART_LSR(uart->hw_base) & (UARTLSR_TDRQ | UARTLSR_TEMT)) == 0x60));
    /* write data */
    UART_TDR(uart->hw_base) = c;

    return (1);
}

static int uart_getc (struct rt_serial_device *serial)
{
    struct jz_uart_s* uart = serial->parent.user_data;

    /* Receive Data Available */
    if (UART_LSR(uart->hw_base) & UARTLSR_DR)
    {
        return UART_RDR(uart->hw_base);
    }

    return (-1);
}

static rt_size_t uart_dma_transmit (struct rt_serial_device *serial, const rt_uint8_t *buf, rt_size_t size, int direction)
{
    return (0);
}

/* UART ISR */
static void uart_irq_handler(int irqno, void *param)
{
    rt_ubase_t isr;
    struct rt_serial_device *serial = (struct rt_serial_device*)param;
    struct jz_uart_s* uart = serial->parent.user_data;

    /* read interrupt status and clear it */
    isr = UART_ISR(uart->hw_base);
    if (isr & UARTISR_IID_RDI)      /* Receive Data Available */
    {
        rt_hw_serial_isr(serial,RT_SERIAL_EVENT_RX_IND);
    }

    if(isr & UARTISR_IID_THRI)
    {
        rt_hw_serial_isr(serial,RT_SERIAL_EVENT_TX_DONE);
    }
}
