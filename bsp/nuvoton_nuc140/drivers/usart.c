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
 * 2020-04-04     Yangxin      the first version
 */

#include "NUC100Series.h"
#include <rtdevice.h>
#include "usart.h"


static rt_err_t nuc140_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    UART_T* uart;
		uint32_t module;
		uint32_t reset_index;
		
    uart = (UART_T *)serial->parent.user_data;
		if(uart == UART0)
		{
				module =  UART0_MODULE;
				reset_index = UART0_RST;
			
				/* Set GPB multi-function pins for UART0 RXD and TXD */
				SYS->GPB_MFP &= ~(SYS_GPB_MFP_PB0_Msk | SYS_GPB_MFP_PB1_Msk);
				SYS->GPB_MFP |= SYS_GPB_MFP_PB0_UART0_RXD | SYS_GPB_MFP_PB1_UART0_TXD;
		}
		else if(uart == UART1)
		{
				module =  UART1_MODULE;
				reset_index = UART1_RST;
			
				/* Set GPB multi-function pins for UART1 RXD and TXD */
				SYS->GPB_MFP &= ~(SYS_GPB_MFP_PB4_Msk | SYS_GPB_MFP_PB4_Msk);
				SYS->GPB_MFP |= SYS_GPB_MFP_PB4_UART1_RXD | SYS_GPB_MFP_PB5_UART1_TXD;
		}
		else
		{
				/**/
		}
	
		/* Enable UART module clock */
		CLK_EnableModuleClock(module);
		/* Select UART module clock source */
		CLK_SetModuleClock(module, CLK_CLKSEL1_UART_S_PLL, CLK_CLKDIV_UART(1));

		/* Reset IP */
		SYS_ResetModule(reset_index);
		/* Configure UART0 and set UART0 Baudrate */
		UART_Open(uart, cfg->baud_rate);
		
		/* Enable Interrupt */
		UART_EnableInt(uart, UART_IER_RDA_IEN_Msk);
    
    return RT_EOK;
}

static rt_err_t nuc140_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    UART_T* uart;
    uart = (UART_T *)serial->parent.user_data;

    switch (cmd)
    {
        case RT_DEVICE_CTRL_CLR_INT: {
                /* Disable Interrupt */
                UART_DisableInt(uart, UART_IER_RDA_IEN_Msk);
            break;
        }
        case RT_DEVICE_CTRL_SET_INT: {
                UART_EnableInt(uart, UART_IER_RDA_IEN_Msk);
            break;
        }
    }

    return RT_EOK;
}

static int nuc140_putc(struct rt_serial_device *serial, char c)
{
    UART_T* uart;
    uart = (UART_T *)serial->parent.user_data;
    if (UART_IS_TX_FULL(uart)) {
        UART_WAIT_TX_EMPTY(uart);
        
    }
    UART_WRITE(uart, c);
    return 1;
}

static int nuc140_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    UART_T* uart;
    uart = (UART_T *)serial->parent.user_data;

    if (UART_IS_RX_READY(uart))
        ch = UART_READ(uart);
    return ch;
}

static const struct rt_uart_ops nuc140_uart_ops =
{
    nuc140_configure,
    nuc140_control,
    nuc140_putc,
    nuc140_getc,
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

#if defined(RT_USING_UART1)
struct rt_serial_device serial1;

void UART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (UART_IS_RX_READY(UART1)) {
        rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* RT_USING_UART1 */

void rt_hw_usart_init(void)
{
#ifdef RT_USING_UART0
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    config.baud_rate = BAUD_RATE_115200;
    serial0.ops    = &nuc140_uart_ops;
    serial0.config = config;

    /* register UART0 device */
    rt_hw_serial_register(&serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          UART0);
#endif /* RT_USING_UART0 */
#ifdef RT_USING_UART1
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    config.baud_rate = BAUD_RATE_115200;
    serial1.ops    = &nuc140_uart_ops;
    serial1.config = config;

    /* register UART0 device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          UART1);
#endif /* RT_USING_UART1 */

}
