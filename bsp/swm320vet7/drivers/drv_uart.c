/*
 * File      : drv_uart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
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
 * 2018-05-31     ZYH          first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <SWM320_port.h>
#include <SWM320_uart.h>

struct drv_uart
{
    UART_TypeDef *uart;
    IRQn_Type irq;
};

static rt_err_t drv_configure(struct rt_serial_device *serial,
                              struct serial_configure *cfg)
{
    struct drv_uart *uart;
    UART_InitStructure UART_initStruct;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = (struct drv_uart *)serial->parent.user_data;
    NVIC_DisableIRQ(uart->irq);
    UART_initStruct.Baudrate = cfg->baud_rate;
    UART_initStruct.RXThreshold = 1;
	UART_initStruct.RXThresholdIEn = 1;
	UART_initStruct.TXThresholdIEn = 0;
	UART_initStruct.TimeoutTime = 10;		
	UART_initStruct.TimeoutIEn = 0;
    switch (cfg->data_bits)
    {
    case DATA_BITS_9:
        UART_initStruct.DataBits = UART_DATA_9BIT;
        break;
    default:
        UART_initStruct.DataBits = UART_DATA_8BIT;
        break;
    }
    switch (cfg->stop_bits)
    {
    case STOP_BITS_2:
        UART_initStruct.StopBits = UART_STOP_2BIT;
        break;
    default:
        UART_initStruct.StopBits = UART_STOP_1BIT;
        break;
    }
    switch (cfg->parity)
    {
    case PARITY_ODD:
        UART_initStruct.Parity = UART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        UART_initStruct.Parity = UART_PARITY_EVEN;
        break;
    default:
        UART_initStruct.Parity = UART_PARITY_NONE;
        break;
    }
    UART_Init(uart->uart, &UART_initStruct);
	UART_Open(uart->uart);
    return RT_EOK;
}

static rt_err_t drv_control(struct rt_serial_device *serial,
                            int cmd, void *arg)
{
    struct drv_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct drv_uart *)serial->parent.user_data;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->irq);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irq);
        break;
    }
    return RT_EOK;
}

static int drv_putc(struct rt_serial_device *serial, char c)
{
    struct drv_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct drv_uart *)serial->parent.user_data;
    while (UART_IsTXBusy(uart->uart));
    uart->uart->DATA = c;
    return 1;
}

static int drv_getc(struct rt_serial_device *serial)
{
    int ch;
    struct drv_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct drv_uart *)serial->parent.user_data;
    ch = -1;
    if (UART_IsRXFIFOEmpty(uart->uart) == 0)
        UART_ReadByte(uart->uart, (uint32_t *)&ch);
    return ch;
}

static const struct rt_uart_ops drv_uart_ops =
{
    drv_configure,
    drv_control,
    drv_putc,
    drv_getc,
};

#if defined(BSP_USING_UART0)
/* UART0 device driver structure */
static struct drv_uart uart0;
struct rt_serial_device serial0;
void UART0_Handler(void)
{
    struct drv_uart *uart;
    /* enter interrupt */
    rt_interrupt_enter();

    uart = &uart0;
    /* UART in mode Receiver -------------------------------------------------*/
    if(UART_INTRXThresholdStat(uart->uart) || UART_INTTimeoutStat(uart->uart))
    {
        rt_hw_serial_isr(&serial0, RT_SERIAL_EVENT_RX_IND);
        //rt_kprintf("1\n");
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)
/* UART1 device driver structure */
static struct drv_uart uart1;
struct rt_serial_device serial1;
void UART1_Handler(void)
{
    struct drv_uart *uart;
    /* enter interrupt */
    rt_interrupt_enter();

    uart = &uart1;
    /* UART in mode Receiver -------------------------------------------------*/
    if(UART_INTRXThresholdStat(uart->uart) || UART_INTTimeoutStat(uart->uart))
    {
        rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
/* UART2 device driver structure */
static struct drv_uart uart2;
struct rt_serial_device serial2;
void UART2_Handler(void)
{
    struct drv_uart *uart;
    /* enter interrupt */
    rt_interrupt_enter();

    uart = &uart2;
    /* UART in mode Receiver -------------------------------------------------*/
    if(UART_INTRXThresholdStat(uart->uart) || UART_INTTimeoutStat(uart->uart))
    {
        rt_hw_serial_isr(&serial2, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
/* UART3 device driver structure */
static struct drv_uart uart3;
struct rt_serial_device serial3;
void UART3_Handler(void)
{
    struct drv_uart *uart;
    /* enter interrupt */
    rt_interrupt_enter();

    uart = &uart3;
    /* UART in mode Receiver -------------------------------------------------*/
    if(UART_INTRXThresholdStat(uart->uart) || UART_INTTimeoutStat(uart->uart))
    {
        rt_hw_serial_isr(&serial3, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART3 */

int hw_usart_init(void)
{
    struct drv_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
#ifdef BSP_USING_UART0
    PORT_Init(PORTA, PIN2, FUNMUX0_UART0_RXD, 1);	
	PORT_Init(PORTA, PIN3, FUNMUX1_UART0_TXD, 0);	
    uart = &uart0;
    uart->uart = UART0;
    uart->irq = UART0_IRQn;
    serial0.ops    = &drv_uart_ops;
    serial0.config = config;
    /* register UART0 device */
    rt_hw_serial_register(&serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART0 */
#ifdef BSP_USING_UART1
    PORT_Init(PORTC, PIN2, FUNMUX0_UART1_RXD, 1);	
	PORT_Init(PORTC, PIN3, FUNMUX1_UART1_TXD, 0);	
    uart = &uart1;
    uart->uart = UART1;
    uart->irq = UART1_IRQn;
    serial1.ops    = &drv_uart_ops;
    serial1.config = config;
    /* register UART1 device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART1 */
#ifdef BSP_USING_UART2
    PORT_Init(PORTC, PIN4, FUNMUX0_UART2_RXD, 1);	
	PORT_Init(PORTC, PIN5, FUNMUX1_UART2_TXD, 0);	
    uart = &uart2;
    uart->uart = UART2;
    uart->irq = UART2_IRQn;
    serial2.ops    = &drv_uart_ops;
    serial2.config = config;
    /* register UART2 device */
    rt_hw_serial_register(&serial2, "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART2 */
#ifdef BSP_USING_UART3
    PORT_Init(PORTC, PIN6, FUNMUX0_UART3_RXD, 1);	
	PORT_Init(PORTC, PIN7, FUNMUX1_UART3_TXD, 0);	
    uart = &uart3;
    uart->uart = UART3;
    uart->irq = UART3_IRQn;
    serial3.ops    = &drv_uart_ops;
    serial3.config = config;
    /* register UART3 device */
    rt_hw_serial_register(&serial3, "uart3",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART3 */
    return 0;
}
INIT_BOARD_EXPORT(hw_usart_init);
