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
#endif

#ifndef RT_UART_RX_BUFFER_SIZE
#define RT_UART_RX_BUFFER_SIZE 16
#endif

/* uart driver */
struct fvp_uart
{
    struct rt_device parent;
    CMSDK_UART_TypeDef * uart_base;

    CMSDK_GPIO_TypeDef * rx_pingpio;   // Pin GPIO
    CMSDK_GPIO_TypeDef * tx_pingpio;
    uint8_t              rx_pinnum;    // Pin Number
    uint8_t              tx_pinnum;

    IRQn_Type            uart_irq_rx;
    IRQn_Type            uart_irq_tx;

    /* buffer for reception */
    rt_uint8_t read_index, save_index;
    rt_uint8_t rx_buffer[RT_UART_RX_BUFFER_SIZE];
};

#ifdef RT_USING_UART0
struct fvp_uart uart0_device;
#endif

#ifdef RT_USING_UART1
struct fvp_uart uart1_device;
#endif

#ifdef RT_USING_UART2
struct fvp_uart uart2_device;
#endif

#ifdef RT_USING_UART3
struct fvp_uart uart3_device;
#endif

static void uart_irq_handler(struct fvp_uart* uart)
{
    rt_ubase_t level;
    uint32_t status;
    uint8_t data;

    status = uart->uart_base->INTSTATUS;
    data = uart->uart_base->DATA;

    /* enter interrupt */
    rt_interrupt_enter();

    level = rt_hw_interrupt_disable();
    uart->rx_buffer[uart->save_index] = data;
    uart->save_index ++;
    if (uart->save_index >= RT_UART_RX_BUFFER_SIZE)
    {
        uart->save_index = 0;
    }
    rt_hw_interrupt_enable(level);

    /* invoke callback */
    if (uart->parent.rx_indicate != RT_NULL)
    {
        rt_size_t length;
        if (uart->read_index > uart->save_index)
            length = RT_UART_RX_BUFFER_SIZE - uart->read_index + uart->save_index;
        else
            length = uart->save_index - uart->read_index;

        uart->parent.rx_indicate(&uart->parent, length);
    }

    uart->uart_base->INTCLEAR = status;

    /* leave interrupt */
    rt_interrupt_leave();
}

#ifdef RT_USING_UART0
void UART0RX_Handler(void)
{
    uart_irq_handler(&uart0_device);
}
#endif

#ifdef RT_USING_UART1
void UART1RX_Handler(void)
{
    uart_irq_handler(&uart1_device);
}
#endif

#ifdef RT_USING_UART2
void UART2RX_Handler(void)
{
    uart_irq_handler(&uart2_device);
}
#endif

#ifdef RT_USING_UART3
void UART3RX_Handler(void)
{
    uart_irq_handler(&uart3_device);
}
#endif

static rt_err_t rt_uart_init (rt_device_t dev)
{
    struct fvp_uart* uart;
    RT_ASSERT(dev != RT_NULL);
    uart = (struct fvp_uart *)dev;

    uart->rx_pingpio->ALTFUNCSET |= (1u << uart->rx_pinnum);
    uart->tx_pingpio->ALTFUNCSET |= (1u << uart->tx_pinnum);

    uart->uart_base->CTRL = CMSDK_UART_CTRL_TXEN_Msk | CMSDK_UART_CTRL_RXEN_Msk | CMSDK_UART_CTRL_RXIRQEN_Msk;
    uart->uart_base->BAUDDIV = SystemCoreClock / 115200;

    return RT_EOK;
}

static rt_err_t rt_uart_open(rt_device_t dev, rt_uint16_t oflag)
{
    struct fvp_uart* uart;
    RT_ASSERT(dev != RT_NULL);
    uart = (struct fvp_uart *)dev;

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* Enable the UART Interrupt */
        NVIC_EnableIRQ(uart->uart_irq_rx);
    }

    return RT_EOK;
}

static rt_err_t rt_uart_close(rt_device_t dev)
{
    struct fvp_uart* uart;
    RT_ASSERT(dev != RT_NULL);
    uart = (struct fvp_uart *)dev;

    if (dev->flag & RT_DEVICE_FLAG_INT_RX)
    {
        /* Disable the UART Interrupt */
        NVIC_DisableIRQ(uart->uart_irq_rx);
    }

    return RT_EOK;
}

static rt_size_t rt_uart_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    struct fvp_uart* uart = (struct fvp_uart *)dev;
    rt_uint8_t *ptr;
    rt_size_t length;

    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);

    ptr = (rt_uint8_t *) buffer;
    while (size)
    {
        /* interrupt receive */
        rt_base_t level;

        /* disable interrupt */
        level = rt_hw_interrupt_disable();
        if (uart->read_index != uart->save_index)
        {
            *ptr = uart->rx_buffer[uart->read_index];

            uart->read_index ++;
            if (uart->read_index >= RT_UART_RX_BUFFER_SIZE)
                uart->read_index = 0;
        }
        else
        {
            /* no data in rx buffer */

            /* enable interrupt */
            rt_hw_interrupt_enable(level);
            break;
        }

        /* enable interrupt */
        rt_hw_interrupt_enable(level);

        ptr ++;
        size --;
    }

    length = (rt_uint32_t)ptr - (rt_uint32_t)buffer;
    return length;
}

static rt_size_t rt_uart_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    char *ptr = (char*) buffer;
    struct fvp_uart* uart = (struct fvp_uart *)dev;

    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);

    if (dev->open_flag & RT_DEVICE_FLAG_STREAM)
    {
        /* stream mode */
        while (size)
        {
            if (*ptr == '\n')
            {
                while (uart->uart_base->STATE & CMSDK_UART_STATE_TXBF_Msk);
                uart->uart_base->DATA = '\r';
            }

            while (uart->uart_base->STATE & CMSDK_UART_STATE_TXBF_Msk);
            uart->uart_base->DATA = *ptr;

            ptr++;
            size--;
        }
    }
    else
    {
        while (size)
        {
            while (uart->uart_base->STATE & CMSDK_UART_STATE_TXBF_Msk);
            uart->uart_base->DATA = *ptr;

            ptr++;
            size--;
        }
    }

    return (rt_size_t)ptr - (rt_size_t)buffer;
}

int rt_hw_usart_init(void)
{
#ifdef RT_USING_UART0
    {
        struct fvp_uart* uart;

        /* get uart device */
        uart = &uart0_device;

        /* device initialization */
        uart->parent.type = RT_Device_Class_Char;
        uart->uart_base   = CMSDK_UART0;
        uart->uart_irq_rx = UART0RX_IRQn;
        uart->read_index  = 0;
        uart->save_index  = 0;
        rt_memset(uart->rx_buffer, 0, sizeof(uart->rx_buffer));

        /* device interface */
        uart->parent.init 	    = rt_uart_init;
        uart->parent.open 	    = rt_uart_open;
        uart->parent.close      = rt_uart_close;
        uart->parent.read 	    = rt_uart_read;
        uart->parent.write      = rt_uart_write;
        uart->parent.control    = RT_NULL;
        uart->parent.user_data  = RT_NULL;

        rt_device_register(&uart->parent, "uart0", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
    }
#endif /* RT_USING_UART1 */

#ifdef RT_USING_UART1
    {
        struct fvp_uart* uart;

        /* get uart device */
        uart = &uart1_device;

        /* device initialization */
        uart->parent.type = RT_Device_Class_Char;
        uart->uart_base   = CMSDK_UART1;
        uart->uart_irq_rx = UART1RX_IRQn;
        uart->read_index  = 0;
        uart->save_index  = 0;
        rt_memset(uart->rx_buffer, 0, sizeof(uart->rx_buffer));

        /* device interface */
        uart->parent.init 	    = rt_uart_init;
        uart->parent.open 	    = rt_uart_open;
        uart->parent.close      = rt_uart_close;
        uart->parent.read 	    = rt_uart_read;
        uart->parent.write      = rt_uart_write;
        uart->parent.control    = RT_NULL;
        uart->parent.user_data  = RT_NULL;

        rt_device_register(&uart->parent, "uart1", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
    }
#endif /* RT_USING_UART1 */

#ifdef RT_USING_UART2
    {
        struct fvp_uart* uart;

        /* get uart device */
        uart = &uart2_device;

        /* device initialization */
        uart->uart_base   = CMSDK_UART2;
        uart->uart_irq_rx = UART2RX_IRQn;
        uart->read_index  = 0;
        uart->save_index  = 0;
        rt_memset(uart->rx_buffer, 0, sizeof(uart->rx_buffer));

        /* device interface */
        uart->parent.type       = RT_Device_Class_Char;
        uart->parent.init 	    = rt_uart_init;
        uart->parent.open 	    = rt_uart_open;
        uart->parent.close      = rt_uart_close;
        uart->parent.read 	    = rt_uart_read;
        uart->parent.write      = rt_uart_write;
        uart->parent.control    = RT_NULL;
        uart->parent.user_data  = RT_NULL;

        rt_device_register(&uart->parent, "uart2", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
    }
#endif /* RT_USING_UART2 */
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_usart_init);

#endif /*RT_USING_UART*/
