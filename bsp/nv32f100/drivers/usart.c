/*
 * File      : usart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2014, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-11-29     Bright       the first version
 */

#include "nv32f100.h"
#include <rtdevice.h>
#include "usart.h"


static rt_err_t nv32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    UART_Type* uart;
    UART_ConfigType sConfig;

    uart = (UART_Type *)serial->parent.user_data;
#if defined(RT_USING_UART1)
    if (uart == UART1) {
        sConfig.u32SysClkHz = BUS_CLK_HZ;   //配置系统时钟和波特率
        sConfig.u32Baudrate = serial->config.baud_rate;
        UART_Init(UART1,&sConfig);          //初始化串口1
        UART_EnableInterrupt(UART1,UART_RxBuffFullInt); //打开接收中断
        NVIC_EnableIRQ(UART1_IRQn);//打开串口1中断
    }
#endif /* RT_USING_UART1 */

#if defined(RT_USING_UART1)
#endif /* RT_USING_UART1 */
    return RT_EOK;
}

static rt_err_t nv32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    UART_Type* uart;
    uart = (UART_Type *)serial->parent.user_data;

    switch (cmd)
    {
        case RT_DEVICE_CTRL_CLR_INT: {
                /* Disable Interrupt */
                UART_DisableInterrupt(uart,UART_RxBuffFullInt);
            break;
        }
        case RT_DEVICE_CTRL_SET_INT: {
                UART_EnableInterrupt(uart,UART_RxBuffFullInt);
            break;
        }
    }

    return RT_EOK;
}

static int nv32_putc(struct rt_serial_device *serial, char c)
{
    UART_Type* uart;
    uart = (UART_Type *)serial->parent.user_data;
    
    UART_PutChar(uart,c);
    
    return 1;
}

static int nv32_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    UART_Type* uart;
    uart = (UART_Type *)serial->parent.user_data;

    if (UART_CheckFlag(uart,UART_FlagRDRF))
        ch = UART_ReadDataReg(uart);
    
    return ch;
}

static const struct rt_uart_ops nv32_uart_ops =
{
    nv32_configure,
    nv32_control,
    nv32_putc,
    nv32_getc,
};

#if defined(RT_USING_UART1)
struct rt_serial_device serial0;

void UART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (UART_CheckFlag(UART1,UART_FlagRDRF)) {
        rt_hw_serial_isr(&serial0, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* RT_USING_UART1 */

void rt_hw_usart_init(void)
{
#ifdef RT_USING_UART1
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    config.baud_rate = BAUD_RATE_115200;
    serial0.ops    = &nv32_uart_ops;
    serial0.config = config;

    /* register UART1 device */
    rt_hw_serial_register(&serial0, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          UART1);
#endif /* RT_USING_UART1 */

}
