/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-29     Rbb666       first version
 */

#include <rtthread.h>
#include "drv_uart.h"

#include "uart_config.h"
#include "cyhal_scb_common.h"

enum
{
#ifdef BSP_USING_UART0
    UART0_INDEX,
#endif
#ifdef BSP_USING_UART1
    UART1_INDEX,
#endif
#ifdef BSP_USING_UART2
    UART2_INDEX,
#endif
#ifdef BSP_USING_UART3
    UART3_INDEX,
#endif
#ifdef BSP_USING_UART4
    UART4_INDEX,
#endif
#ifdef BSP_USING_UART5
    UART5_INDEX,
#endif
};

static struct ifx_uart_config uart_config[] =
{
#ifdef BSP_USING_UART0
    UART0_CONFIG,
#endif
#ifdef BSP_USING_UART1
    UART1_CONFIG,
#endif
#ifdef BSP_USING_UART2
    UART2_CONFIG,
#endif
#ifdef BSP_USING_UART3
    UART3_CONFIG,
#endif
#ifdef BSP_USING_UART4
    UART4_CONFIG,
#endif
#ifdef BSP_USING_UART5
    UART5_CONFIG,
#endif
};

static struct ifx_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

static void uart_isr(struct rt_serial_device *serial)
{
    RT_ASSERT(serial != RT_NULL);
    struct ifx_uart *uart = (struct ifx_uart *) serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    if ((uart->config->usart_x->INTR_RX_MASKED & SCB_INTR_RX_MASKED_NOT_EMPTY_Msk) != 0)
    {
        /* Clear UART "RX fifo not empty interrupt" */
        uart->config->usart_x->INTR_RX = uart->config->usart_x->INTR_RX & SCB_INTR_RX_NOT_EMPTY_Msk;

        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
}

#ifdef BSP_USING_UART0
/* UART0 Interrupt Hanlder */
void uart0_isr_callback(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uart_obj[UART0_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART1
/* UART1 Interrupt Hanlder */
void uart1_isr_callback(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uart_obj[UART1_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART2
/* UART2 Interrupt Hanlder */
void uart2_isr_callback(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uart_obj[UART2_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART3
/* UART3 Interrupt Hanlder */
void uart3_isr_callback(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uart_obj[UART3_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART4
/* UART4 Interrupt Hanlder */
void uart4_isr_callback(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uart_obj[UART4_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART5
/* UART5 Interrupt Hanlder */
void uart5_isr_callback(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uart_obj[UART5_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

/*
 * UARTHS interface
 */
static rt_err_t ifx_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    RT_ASSERT(serial != RT_NULL);
    struct ifx_uart *uart = (struct ifx_uart *) serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    cy_en_scb_uart_status_t result;

    const cyhal_uart_cfg_t uart_config =
    {
        .data_bits          = 8,
        .stop_bits          = 1,
        .parity             = CYHAL_UART_PARITY_NONE,
        .rx_buffer          = NULL,
        .rx_buffer_size     = 0
    };

    /* Initialize retarget-io to use the debug UART port */
    result = cyhal_uart_init(uart->config->uart_obj, uart->config->tx_pin, uart->config->rx_pin, NC, NC, NULL, &uart_config);

    if (result == CY_RSLT_SUCCESS)
    {
        result = cyhal_uart_set_baud(uart->config->uart_obj, cfg->baud_rate, NULL);
    }

    RT_ASSERT(result != RT_ERROR);

    return RT_EOK;
}

static rt_err_t ifx_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    RT_ASSERT(serial != RT_NULL);
    struct ifx_uart *uart = (struct ifx_uart *) serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:

        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* Unmasking only the RX fifo not empty interrupt bit */
        uart->config->usart_x->INTR_RX_MASK = SCB_INTR_RX_MASK_NOT_EMPTY_Msk;

        /* Interrupt Settings for UART */
        Cy_SysInt_Init(uart->config->UART_SCB_IRQ_cfg, uart->config->userIsr);

        /* Enable the interrupt */
        NVIC_EnableIRQ(uart->config->intrSrc);
        break;
    }

    return (RT_EOK);
}

static int ifx_uarths_putc(struct rt_serial_device *serial, char c)
{
    RT_ASSERT(serial != RT_NULL);

    struct ifx_uart *uart = (struct ifx_uart *) serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);

    if (_cyhal_scb_pm_transition_pending())
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;

    uint32_t count = 0;

    while (count == 0)
    {
        count = Cy_SCB_UART_Put(uart->config->usart_x, c);
    }

    return (1);
}

static int ifx_uarths_getc(struct rt_serial_device *serial)
{
    int ch;
    rt_uint8_t read_data;

    RT_ASSERT(serial != RT_NULL);
    struct ifx_uart *uart = (struct ifx_uart *) serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    ch = -1;

    if (RT_EOK == cyhal_uart_getc(uart->config->uart_obj, (uint8_t *)&read_data, 10))
    {
        ch = read_data & 0xff;
    }
    else
    {
        ch = -1;
    }

    return ch;
}

const struct rt_uart_ops _uart_ops =
{
    ifx_configure,
    ifx_control,
    ifx_uarths_putc,
    ifx_uarths_getc,
    RT_NULL
};

void rt_hw_uart_init(void)
{
    int index;

    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct ifx_uart);
    struct serial_configure serial_config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    for (index = 0; index < obj_num; index++)
    {
        uart_obj[index].config = &uart_config[index];
        uart_obj[index].serial.ops = &_uart_ops;
        uart_obj[index].serial.config = serial_config;

        uart_obj[index].config->uart_obj = rt_malloc(sizeof(cyhal_uart_t));
        RT_ASSERT(uart_obj[index].config->uart_obj != RT_NULL);
        /* register uart device */
        result = rt_hw_serial_register(&uart_obj[index].serial,
                                       uart_obj[index].config->name,
                                       RT_DEVICE_FLAG_RDWR |
                                       RT_DEVICE_FLAG_INT_RX,
                                       &uart_obj[index]);

        RT_ASSERT(result == RT_EOK);
    }
}
