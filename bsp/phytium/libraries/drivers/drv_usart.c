/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2022-10-26  huanghe      first commit
 * 2023-04-27  huanghe      support RT-Smart
 */

#include "board.h"

#include <mmu.h>

#include "drv_usart.h"
#include "interrupt.h"
#include "fpl011.h"
#include "rtconfig.h"
#include "fprintk.h"

#ifdef RT_USING_SERIAL

extern u32 FUart_GetInterruptMask(FPl011 *uart_ptr);

static void Ft_Os_Uart_Callback(void *Args, u32 Event, u32 EventData);

static void rt_hw_uart_isr(int irqno, void *param)
{
    FPl011InterruptHandler(irqno, param);
}

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct drv_usart *uart = RT_NULL;
    FPl011 *uart_hw = RT_NULL;
    u32 intr_mask;
    FPl011Config config;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = rt_container_of(serial, struct drv_usart, serial);
    uart_hw = uart->handle;
    config = *(const FPl011Config *)FPl011LookupConfig(uart->config.uart_instance);

#ifdef RT_USING_SMART
    config.base_address = (uintptr)rt_ioremap((void*)config.base_address, 0x1000);
#endif

    RT_ASSERT(FPl011CfgInitialize(uart_hw, &config) == FT_SUCCESS);
    FPl011SetHandler(uart_hw, Ft_Os_Uart_Callback, serial);

    FPl011SetRxFifoThreadhold(uart_hw, FPL011IFLS_RXIFLSEL_1_4);
    FPl011SetTxFifoThreadHold(uart_hw, FPL011IFLS_TXIFLSEL_1_2);

    //<! 打开接收中断
    intr_mask = uart->config.isr_event_mask;
    FPl011SetInterruptMask(uart_hw, intr_mask);
    FPl011SetOptions(uart_hw, FPL011_OPTION_UARTEN | FPL011_OPTION_RXEN | FPL011_OPTION_TXEN | FPL011_OPTION_FIFOEN);

    rt_hw_interrupt_set_priority(uart_hw->config.irq_num, uart->config.isr_priority);
    rt_hw_interrupt_install(uart_hw->config.irq_num, rt_hw_uart_isr, uart_hw, "uart");
    rt_hw_interrupt_umask(uart_hw->config.irq_num);

    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct drv_usart *uart = RT_NULL;
    FPl011 *uart_ptr = RT_NULL;
    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct drv_usart, serial);
    uart_ptr = uart->handle;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        rt_hw_interrupt_mask(uart_ptr->config.irq_num);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        rt_hw_interrupt_umask(uart_ptr->config.irq_num);
        break;
    }

    return RT_EOK;
}

static void Ft_Os_Uart_Callback(void *Args, u32 Event, u32 EventData)
{
    struct rt_serial_device *serial = (struct rt_serial_device *)Args;

    if (FPL011_EVENT_RECV_DATA == Event || FPL011_EVENT_RECV_TOUT == Event)
    {
        if (serial->serial_rx)
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
    else if (FPL011_EVENT_RECV_ERROR == Event)
    {
    }
    else if (FPL011_EVENT_SENT_DATA == Event)
    {
    }
    else if (FPL011_EVENT_PARE_FRAME_BRKE == Event)
    {
    }
    else if (FPL011_EVENT_RECV_ORERR == Event)
    {
    }

    if (FPL011_EVENT_SENT_DATA == Event)
    {
    }
    else
    {
    }
}

static int uart_putc(struct rt_serial_device *serial, char c)
{
    struct drv_usart *uart = RT_NULL;
    FPl011 *uart_ptr = RT_NULL;
    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct drv_usart, serial);
    uart_ptr = uart->handle;

    FPl011SendByte(uart_ptr->config.base_address, c);

    return 1;
}

u32 FPl011RecvByteNoBlocking(uintptr addr)
{
    u32 recieved_byte;

    while (FUART_RECEIVEDATAEMPTY(addr))
    {
        return 0xffff;
    }
    recieved_byte = FUART_READREG32(addr, FPL011DR_OFFSET);
    return recieved_byte;
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct drv_usart *uart = RT_NULL;
    FPl011 *uart_ptr = RT_NULL;
    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct drv_usart, serial);
    uart_ptr = uart->handle;

    ch = FPl011RecvByteNoBlocking(uart_ptr->config.base_address);
    if (ch == 0xffff)
    {
        ch = -1;
    }
    else
    {
        ch &= 0xff;
    }

    return ch;
}

static const struct rt_uart_ops _uart_ops =
{
    uart_configure,
    uart_control,
    uart_putc,
    uart_getc,
    NULL
};

#define RT_USING_UART0
#define RT_USING_UART1
#define RT_USING_UART2


#ifdef RT_USING_UART0
    static FPl011 Ft_Uart0;
    static struct drv_usart _RtUart0;
#endif

#ifdef RT_USING_UART1
    static FPl011 Ft_Uart1;
    static struct drv_usart _RtUart1;
#endif

#ifdef RT_USING_UART2
    static FPl011 Ft_Uart2;
    static struct drv_usart _RtUart2;
#endif

int rt_hw_uart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef RT_USING_UART0
    config.bufsz = RT_SERIAL_RB_BUFSZ;
    _RtUart0.serial.ops = &_uart_ops;
    _RtUart0.serial.config = config;

    _RtUart0.handle = &Ft_Uart0;
    _RtUart0.config.uart_instance = FUART0_ID;
    _RtUart0.config.isr_priority = 0xd0;
    _RtUart0.config.isr_event_mask = (RTOS_UART_ISR_OEIM_MASK | RTOS_UART_ISR_BEIM_MASK | RTOS_UART_ISR_PEIM_MASK | RTOS_UART_ISR_FEIM_MASK | RTOS_UART_ISR_RTIM_MASK | RTOS_UART_ISR_RXIM_MASK);
    _RtUart0.config.uart_baudrate = 115200;

    rt_hw_serial_register(&_RtUart0.serial, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          &_RtUart0);
#endif

#ifdef RT_USING_UART1
    config.bufsz = RT_SERIAL_RB_BUFSZ;
    _RtUart1.serial.ops = &_uart_ops;
    _RtUart1.serial.config = config;
    _RtUart1.handle = &Ft_Uart1;

    _RtUart1.config.uart_instance = FUART1_ID;
    _RtUart1.config.isr_priority = 0xd0;
    _RtUart1.config.isr_event_mask = (RTOS_UART_ISR_OEIM_MASK | RTOS_UART_ISR_BEIM_MASK | RTOS_UART_ISR_PEIM_MASK | RTOS_UART_ISR_FEIM_MASK | RTOS_UART_ISR_RTIM_MASK | RTOS_UART_ISR_RXIM_MASK);
    _RtUart1.config.uart_baudrate = 115200;

    rt_hw_serial_register(&_RtUart1.serial, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          &_RtUart1);
#endif


#ifdef RT_USING_UART2
    config.bufsz = RT_SERIAL_RB_BUFSZ;
    _RtUart2.serial.ops = &_uart_ops;
    _RtUart2.serial.config = config;
    _RtUart2.handle = &Ft_Uart2;

    _RtUart2.config.uart_instance = FUART2_ID;
    _RtUart2.config.isr_priority = 0xd0;
    _RtUart2.config.isr_event_mask = (RTOS_UART_ISR_OEIM_MASK | RTOS_UART_ISR_BEIM_MASK | RTOS_UART_ISR_PEIM_MASK | RTOS_UART_ISR_FEIM_MASK | RTOS_UART_ISR_RTIM_MASK | RTOS_UART_ISR_RXIM_MASK);
    _RtUart2.config.uart_baudrate = 115200;

    rt_hw_serial_register(&_RtUart2.serial, "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          &_RtUart2);
#endif


    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif /* RT_USING_SERIAL */
