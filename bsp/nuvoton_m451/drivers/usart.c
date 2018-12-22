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
 * 2016-12-05     Pluto        first implementation
 */

#include "usart.h"


static rt_err_t m451_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    UART_T* uart;

    uart = (UART_T *)serial->parent.user_data;
#if defined(RT_USING_UART0)
    if (uart == UART0) {
        /* Enable UART module clock */
        CLK_EnableModuleClock(UART0_MODULE);
        
        /* Select UART module clock source as HXT and UART module clock divider as 1 */
        CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UARTSEL_HXT, CLK_CLKDIV0_UART(1));
        
        /* Set PD multi-function pins for UART0 RXD(PD.0) and TXD(PD.1) */
        SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD0MFP_Msk | SYS_GPD_MFPL_PD1MFP_Msk);
        SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD0MFP_UART0_RXD | SYS_GPD_MFPL_PD1MFP_UART0_TXD);
        
        /* Reset UART module */
        SYS_ResetModule(UART0_RST);
        
        /* Configure UART0 and set UART0 Baudrate */
        UART_Open(UART0, cfg->baud_rate);
        
        /* Enable Interrupt */
        UART_EnableInt(UART0, UART_INTEN_RDAIEN_Msk);
    }
#endif /* RT_USING_UART0 */

#if defined(RT_USING_UART1)
#endif /* RT_USING_UART1 */
    return RT_EOK;
}

static rt_err_t m451_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    UART_T* uart;
    uart = (UART_T *)serial->parent.user_data;

    switch (cmd)
    {
        case RT_DEVICE_CTRL_CLR_INT: {
                /* Disable Interrupt */
                UART_DisableInt(uart, UART_INTEN_RDAIEN_Msk);
            break;
        }
        case RT_DEVICE_CTRL_SET_INT: {
                UART_EnableInt(UART0, UART_INTEN_RDAIEN_Msk);
            break;
        }
    }

    return RT_EOK;
}

static int m451_putc(struct rt_serial_device *serial, char c)
{
    UART_T* uart;
    uart = (UART_T *)serial->parent.user_data;
    if (UART_IS_TX_FULL(uart)) {
        UART_WAIT_TX_EMPTY(uart);
    }
    UART_WRITE(uart, c);
    return 1;
}

static int m451_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    UART_T* uart;
    uart = (UART_T *)serial->parent.user_data;

    if (UART_IS_RX_READY(uart))
        ch = UART_READ(uart);
    return ch;
}

static const struct rt_uart_ops m451_uart_ops =
{
    m451_configure,
    m451_control,
    m451_putc,
    m451_getc,
};

#if defined(RT_USING_UART0)
struct rt_serial_device serial0;

void UART0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (UART_IS_RX_READY(UART0)) {
        rt_hw_serial_isr(&serial0, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* RT_USING_UART0 */

void rt_hw_usart_init(void)
{
#ifdef RT_USING_UART0
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    config.baud_rate = BAUD_RATE_115200;
    serial0.ops    = &m451_uart_ops;
    serial0.config = config;

    /* register UART0 device */
    rt_hw_serial_register(&serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          UART0);
#endif /* RT_USING_UART0 */

}
