/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2025-05-23  liyilun      first commit
 */

#include "rtconfig.h"

#include <rtdevice.h>
#include "board.h"
#include <mmu.h>
#include "drv_usart_msg.h"
#include "interrupt.h"
#include "fio_mux.h"
#include "fparameters.h"

#ifdef RT_USING_SMART
    #include <ioremap.h>
#endif

#define RING_BUFFER_WAIT_TIMEOUT              10000
#define RING_BUFFER_SIZE                      64

struct rt_ringbuffer *recv_ringbuffer = NULL;


rt_inline enum rt_ringbuffer_state rt_ringbuffer_status(struct rt_ringbuffer *rb)
{
    if (rb->read_index == rb->write_index)
    {
        if (rb->read_mirror == rb->write_mirror)
            return RT_RINGBUFFER_EMPTY;
        else
            return RT_RINGBUFFER_FULL;
    }
    return RT_RINGBUFFER_HALFFULL;
}

static void Ft_Os_Uart_Msg_Callback(void *Args, u32 Event, u32 EventData);

static void rt_hw_uart_msg_isr(int irqno, void *param)
{
    FUartMsgInterruptHandler(irqno, param);
}

static rt_err_t uart_msg_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct drv_usart_msg *uart_msg = RT_NULL;
    FUartMsg *uart_msg_hw = RT_NULL;

    FUartMsgConfig config;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart_msg = rt_container_of(serial, struct drv_usart_msg, serial);
    uart_msg_hw = uart_msg->handle;
    config = *(const FUartMsgConfig *)FUartMsgLookupConfig(uart_msg->config.uart_instance);

#ifdef RT_USING_SMART
    config.msg.regfile = (uintptr)rt_ioremap((void *)config.msg.regfile,  0x1000);
    config.msg.shmem = (uintptr)rt_ioremap((void *)config.msg.shmem,  0x1000);
#endif


    FIOPadSetUartMux(uart_msg->config.uart_instance);

    RT_ASSERT(FUartMsgCfgInitialize(uart_msg_hw, &config) == FT_SUCCESS);

    FUartMsgSetStartUp(uart_msg_hw);

    FUartMsgSetHandler(uart_msg_hw, Ft_Os_Uart_Msg_Callback, serial);


    //<! 打开接收中断

    rt_hw_interrupt_set_priority(uart_msg_hw->config.irq_num, uart_msg->config.isr_priority);
    rt_hw_interrupt_install(uart_msg_hw->config.irq_num, rt_hw_uart_msg_isr, uart_msg_hw, "uart");
    rt_hw_interrupt_umask(uart_msg_hw->config.irq_num);
    FUartMsgEnableInterrups(uart_msg_hw);

    return RT_EOK;
}

static rt_err_t uart_msg_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct drv_usart_msg *uart_msg = RT_NULL;
    FUartMsg *uart_msg_ptr = RT_NULL;
    RT_ASSERT(serial != RT_NULL);

    uart_msg = rt_container_of(serial, struct drv_usart_msg, serial);
    uart_msg_ptr = uart_msg->handle;

    switch (cmd)
    {
        case RT_DEVICE_CTRL_CLR_INT:
            /* disable rx irq */
            rt_hw_interrupt_mask(uart_msg_ptr->config.irq_num);
            break;

        case RT_DEVICE_CTRL_SET_INT:
            /* enable rx irq */
            rt_hw_interrupt_umask(uart_msg_ptr->config.irq_num);
            break;
    }

    return RT_EOK;
}

static int uart_msg_putc(struct rt_serial_device *serial, char c)
{
    struct drv_usart_msg *uart_msg = RT_NULL;
    FUartMsg *uart_msg_ptr = RT_NULL;
    RT_ASSERT(serial != RT_NULL);

    uart_msg = rt_container_of(serial, struct drv_usart_msg, serial);
    uart_msg_ptr = uart_msg->handle;

    while(-1 == FUartMsgTxChar(&(uart_msg_ptr->config.msg), (u8)c))
    {
    }

    return 1;
}

void FUartMsgRecvBufferNoBlocking(FUartMsg *uart_p)
{
    u8 data[16] = {0};
    rt_size_t write_length = 0;
    u32 received_count = 0;

    while (!FUartMsgRxRingBufferIsEmpty(uart_p->config.msg.regfile))
    {
        received_count += FUartMsgRxChars(&(uart_p->config.msg), data, 16);
    }

    if(received_count > 0)
    {
        write_length = rt_ringbuffer_put(recv_ringbuffer, data, received_count);
        RT_ASSERT(write_length == received_count);
    }

}

static int uart_msg_getc(struct rt_serial_device *serial)
{
    int ch;
    struct drv_usart_msg *uart_msg = RT_NULL;
    FUartMsg *uart_msg_ptr = RT_NULL;
    RT_ASSERT(serial != RT_NULL);

    uart_msg = rt_container_of(serial, struct drv_usart_msg, serial);
    uart_msg_ptr = uart_msg->handle;


    if(RT_RINGBUFFER_EMPTY == rt_ringbuffer_status(recv_ringbuffer))
    {
        FUartMsgRecvBufferNoBlocking(uart_msg_ptr);
    }

    if(0 == rt_ringbuffer_getchar(recv_ringbuffer, (rt_uint8_t *)&ch))
    {
        return -1;
    }

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

static void Ft_Os_Uart_Msg_Callback(void *Args, u32 Event, u32 EventData)
{

    struct rt_serial_device *serial = (struct rt_serial_device *)Args;
    if(FUART_EVENT_RECV_DATA == Event)
    {
        if(serial->serial_rx)
        {
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        }
    }
    else if(FUART_EVENT_SENT_DATA == Event)
    {

    }
    else
    {

    }
}


static const struct rt_uart_ops _uart_ops =
{
    uart_msg_configure,
    uart_msg_control,
    uart_msg_putc,
    uart_msg_getc,
    NULL
};

static int uart_msg_init(struct drv_usart_msg *uart_msg_dev)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    config.bufsz = RT_SERIAL_RB_BUFSZ;
    uart_msg_dev->serial.ops = &_uart_ops;
    uart_msg_dev->serial.config = config;

    uart_msg_dev->config.isr_priority = 0xd0;
    uart_msg_dev->config.isr_event_mask = RTOS_UART_MSG_RX_ISR_MASK | RTOS_UART_MSG_TX_ISR_MASK;
    uart_msg_dev->config.uart_baudrate = BAUD_RATE_115200;

    recv_ringbuffer = rt_ringbuffer_create(RING_BUFFER_SIZE);

    RT_ASSERT(recv_ringbuffer != RT_NULL);

    rt_hw_serial_register(&uart_msg_dev->serial, uart_msg_dev->name,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart_msg_dev);

    return 0;
}

#ifdef RT_USING_UART0_MSG
    static FUartMsg Ft_Uart0_Msg;
    static struct drv_usart_msg drv_uart0_msg;
#endif
#ifdef RT_USING_UART1_MSG
    static FUartMsg Ft_Uart1_Msg;
    static struct drv_usart_msg drv_uart1_msg;
#endif
#ifdef RT_USING_UART2_MSG
    static FUartMsg Ft_Uart2_Msg;
    static struct drv_usart_msg drv_uart2_msg;
#endif

int rt_hw_uart_init(void)
{

#ifdef RT_USING_UART0_MSG
    drv_uart0_msg.name = "uart0";
    drv_uart0_msg.handle = &Ft_Uart0_Msg;
    drv_uart0_msg.config.uart_instance = FUART0_MSG_ID;
    uart_msg_init(&drv_uart0_msg);
#endif
#ifdef RT_USING_UART1_MSG
    drv_uart1_msg.name = "uart1";
    drv_uart1_msg.handle = &Ft_Uart1_Msg;
    drv_uart1_msg.config.uart_instance = FUART1_MSG_ID;
    uart_msg_init(&drv_uart1_msg);
#endif
#ifdef RT_USING_UART2_MSG
    drv_uart2_msg.name = "uart2";
    drv_uart2_msg.handle = &Ft_Uart2_Msg;
    drv_uart2_msg.config.uart_instance = FUART2_MSG_ID;
    uart_msg_init(&drv_uart2_msg);
#endif

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);
