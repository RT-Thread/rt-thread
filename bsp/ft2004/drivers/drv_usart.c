/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-03-04     Carl      the first version
 */

#include "board.h"
#include "drv_usart.h"
#include "interrupt.h"
#include "serial.h"
#include "rtconfig.h"

#ifdef RT_USING_SERIAL

extern u32 FUart_GetInterruptMask(Ft_Uart *uart_ptr);

static void Ft_Os_Uart_Callback(void *Args, u32 Event, u32 EventData);

static void rt_hw_uart_isr(int irqno, void *param)
{
    Ft_Uart *uart_ptr = (Ft_Uart *)param;
    FUart_InterruptHandler(uart_ptr);
}

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct drv_usart *uart = RT_NULL;
    Ft_Uart *uart_ptr = RT_NULL;
    u32 RegTemp;
    u32 ret;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = rt_container_of(serial, struct drv_usart, serial);
    uart_ptr = uart->handle;

    RT_ASSERT(FUart_CfgInitialize(uart_ptr, FUart_LookupConfig(uart_ptr->Config.InstanceId)) == FST_SUCCESS);
    FUart_SetHandler(uart_ptr, Ft_Os_Uart_Callback, serial);
    rt_hw_interrupt_install(uart_ptr->Config.IsrNum, rt_hw_uart_isr, uart_ptr, "uart");
    rt_hw_interrupt_umask(uart_ptr->Config.IsrNum);

    //<! 设置波特率
    ret = FUart_SetBaudRate(uart_ptr, cfg->baud_rate);
    RT_ASSERT(ret == FST_SUCCESS);

    //<! 打开接收中断
    RegTemp = FUart_GetInterruptMask(uart_ptr);
    RegTemp |= UARTMIS_RTMIS;
    FUart_SetInterruptMask(uart_ptr, RegTemp);
    FUart_SetOptions(uart_ptr, FUART_OPTION_UARTEN | FUART_OPTION_RXEN | FUART_OPTION_TXEN | FUART_OPTION_FIFOEN);
    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct drv_usart *uart = RT_NULL;
    Ft_Uart *uart_ptr = RT_NULL;
    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct drv_usart, serial);
    uart_ptr = uart->handle;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        rt_hw_interrupt_mask(uart_ptr->Config.IsrNum);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        rt_hw_interrupt_umask(uart_ptr->Config.IsrNum);
        break;
    }

    return RT_EOK;
}

static void Ft_Os_Uart_Callback(void *Args, u32 Event, u32 EventData)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)Args;

    if (FUART_EVENT_RECV_DATA == Event || FUART_EVENT_RECV_TOUT == Event)
    {
        if (serial->serial_rx)
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
    else if (FUART_EVENT_RECV_ERROR == Event)
    {
    }
    else if (FUART_EVENT_SENT_DATA == Event)
    {
    }
    else if (FUART_EVENT_PARE_FRAME_BRKE == Event)
    {
    }
    else if (FUART_EVENT_RECV_ORERR == Event)
    {
    }

    if (FUART_EVENT_SENT_DATA == Event)
    {
    }
    else
    {
    }
}

static int uart_putc(struct rt_serial_device *serial, char c)
{
    struct drv_usart *uart = RT_NULL;
    Ft_Uart *uart_ptr = RT_NULL;
    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct drv_usart, serial);
    uart_ptr = uart->handle;

    FUart_SendByte(uart_ptr->Config.BaseAddress, c);

    return 1;
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct drv_usart *uart = RT_NULL;
    Ft_Uart *uart_ptr = RT_NULL;
    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct drv_usart, serial);
    uart_ptr = uart->handle;

    ch = FUart_GetChar(uart_ptr->Config.BaseAddress);
    if (ch == 0xff)
        ch = -1;

    return ch;
}

static const struct rt_uart_ops _uart_ops =
    {
        uart_configure,
        uart_control,
        uart_putc,
        uart_getc,
};

#ifdef RT_USING_UART0
static Ft_Uart Ft_Uart0;
static struct drv_usart _RtUart0;
#endif

#ifdef RT_USING_UART1
static Ft_Uart Ft_Uart1;
static struct drv_usart _RtUart1;
#endif

int rt_hw_uart_init(void)
{

    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef RT_USING_UART0
    config.bufsz = RT_SERIAL_RB_BUFSZ;
    _RtUart0.serial.ops = &_uart_ops;
    _RtUart0.serial.config = config;
    Ft_Uart0.Config.InstanceId = FT_UART0_ID;
    _RtUart0.Handle = &Ft_Uart0;

    rt_hw_serial_register(&_RtUart0.serial, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          &_RtUart0);
#endif

#ifdef RT_USING_UART1
    config.bufsz = RT_SERIAL_RB_BUFSZ;
    _RtUart1.serial.ops = &_uart_ops;
    _RtUart1.serial.config = config;
    Ft_Uart1.Config.InstanceId = FT_UART1_ID;
    _RtUart1.handle = &Ft_Uart1;
    rt_hw_serial_register(&_RtUart1.serial, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          &_RtUart1);
#endif

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif /* RT_USING_SERIAL */
