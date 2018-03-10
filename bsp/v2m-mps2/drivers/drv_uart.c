/*
 * File      : drv_uart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
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
 * 2018-02-22     Tanek        first version.
 */

#include <rtthread.h>
#include <rthw.h>

#include <SMM_MPS2.h>

#ifdef RT_USING_UART

#ifndef RT_USING_DEVICE
#error "you must define RT_USING_DEVICE with uart device"
#else
#include <rtdevice.h>
#endif

/* uart driver */
struct v2m_uart
{
    struct rt_serial_device serial;
    CMSDK_UART_TypeDef * uart_base;

    CMSDK_GPIO_TypeDef * rx_pingpio;   // Pin GPIO
    CMSDK_GPIO_TypeDef * tx_pingpio;
    uint8_t              rx_pinnum;    // Pin Number
    uint8_t              tx_pinnum;

    IRQn_Type            uart_irq_rx;
    //IRQn_Type            uart_irq_tx;

};

#ifdef RT_USING_UART0
struct v2m_uart uart0_device;
#endif

#ifdef RT_USING_UART1
struct v2m_uart uart1_device;
#endif

#ifdef RT_USING_UART2
struct v2m_uart uart2_device;
#endif

static void uart_irq_handler(struct rt_serial_device *serial)
{
    uint32_t status;
    struct v2m_uart *uart;

    uart = (struct v2m_uart *)serial->parent.user_data;

    /* enter interrupt */
    rt_interrupt_enter();
    
    status = uart->uart_base->INTSTATUS;
    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    uart->uart_base->INTCLEAR = status;

    /* leave interrupt */
    rt_interrupt_leave();
}

#ifdef RT_USING_UART0
void UART0RX_Handler(void)
{
    uart_irq_handler(&uart0_device.serial);
}
#endif

#ifdef RT_USING_UART1
void UART1RX_Handler(void)
{
    uart_irq_handler(&uart1_device.serial);
}
#endif

#ifdef RT_USING_UART2
void UART2RX_Handler(void)
{
    uart_irq_handler(&uart2_device.serial);
}
#endif

static rt_err_t v2m_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct v2m_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = (struct v2m_uart *)serial->parent.user_data;

    uart->uart_base->BAUDDIV = SystemCoreClock / cfg->baud_rate;
    uart->uart_base->CTRL = CMSDK_UART_CTRL_TXEN_Msk | CMSDK_UART_CTRL_RXEN_Msk | CMSDK_UART_CTRL_RXIRQEN_Msk;

    uart->rx_pingpio->ALTFUNCSET |= (1u << uart->rx_pinnum);
    uart->tx_pingpio->ALTFUNCSET |= (1u << uart->tx_pinnum);

    return RT_EOK;
}

static rt_err_t v2m_control(struct rt_serial_device *serial, int cmd, void *arg)
{
  struct v2m_uart *uart;

  RT_ASSERT(serial != RT_NULL);
  uart = (struct v2m_uart *)serial->parent.user_data;

  switch (cmd)
  {
  case RT_DEVICE_CTRL_CLR_INT:
      /* disable rx irq */
      NVIC_DisableIRQ(uart->uart_irq_rx);
      break;
  case RT_DEVICE_CTRL_SET_INT:
      /* enable rx irq */
      NVIC_EnableIRQ(uart->uart_irq_rx);
      break;
  }

  return RT_EOK;
}

static int v2m_putc(struct rt_serial_device *serial, char c)
{
    struct v2m_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct v2m_uart *)serial->parent.user_data;
    
    while (uart->uart_base->STATE & CMSDK_UART_STATE_TXBF_Msk);
    uart->uart_base->DATA = c;
    
    return 1;
}

static int v2m_getc(struct rt_serial_device *serial)
{
    int ch;
    struct v2m_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct v2m_uart *)serial->parent.user_data;

    ch = -1;
    if (uart->uart_base->STATE & CMSDK_UART_STATE_RXBF_Msk)
        ch = uart->uart_base->DATA & 0xff;
    return ch;
}

static const struct rt_uart_ops v2m_uart_ops =
{
    v2m_configure,
    v2m_control,
    v2m_putc,
    v2m_getc,
};

int rt_hw_usart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
#ifdef RT_USING_UART0
    {
        struct v2m_uart* uart;

        /* get uart device */
        uart = &uart0_device;

        /* device initialization */
        uart->uart_base   = CMSDK_UART0;
        uart->uart_irq_rx = UART0RX_IRQn;
        
        uart->serial.ops = &v2m_uart_ops;
        uart->serial.config = config;

        rt_hw_serial_register(&uart->serial,
                          "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
    }
#endif /* RT_USING_UART0 */

#ifdef RT_USING_UART1
    {
        struct v2m_uart* uart;

        /* get uart device */
        uart = &uart1_device;

        /* device initialization */
        uart->uart_base   = CMSDK_UART1;
        uart->uart_irq_rx = UART1RX_IRQn;

        rt_hw_serial_register(&uart->serial,
                          "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
    }
#endif /* RT_USING_UART1 */

#ifdef RT_USING_UART2
    {
        struct v2m_uart* uart;

        /* get uart device */
        uart = &uart2_device;

        /* device initialization */
        uart->uart_base   = CMSDK_UART2;
        uart->uart_irq_rx = UART2RX_IRQn;

        rt_hw_serial_register(&uart->serial,
                          "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
    }
#endif /* RT_USING_UART2 */
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_usart_init);

#endif /*RT_USING_UART*/
