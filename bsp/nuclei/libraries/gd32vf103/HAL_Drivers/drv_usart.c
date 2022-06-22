/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-23     tyustli      first version
 * 2020-04-02     hqfang       modified for Nuclei
 */

#include <drv_usart.h>

#ifdef RT_USING_SERIAL

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) \
    && !defined(BSP_USING_UART3) && !defined(BSP_USING_UART4)
    #error "Please define at least one BSP_USING_UARTx"
    /* this driver can be disabled at menuconfig -> Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable UART */
#endif

enum
{
#ifdef BSP_USING_UART0
    GDUART0_INDEX,
#endif
#ifdef BSP_USING_UART1
    GDUART1_INDEX,
#endif
#ifdef BSP_USING_UART2
    GDUART2_INDEX,
#endif
#ifdef BSP_USING_UART3
    GDUART3_INDEX,
#endif
#ifdef BSP_USING_UART4
    GDUART4_INDEX,
#endif
};

static struct gd32_uart_config uart_config[] =
{
#ifdef BSP_USING_UART0
    {
        "uart0",
        USART0,
        USART0_IRQn,
    },
#endif
#ifdef BSP_USING_UART1
    {
        "uart1",
        USART1,
        USART1_IRQn,
    },
#endif
#ifdef BSP_USING_UART2
    {
        "uart2",
        USART2,
        USART2_IRQn,
    },
#endif
#ifdef BSP_USING_UART3
    {
        "uart3",
        UART3,
        UART3_IRQn,
    },
#endif
#ifdef BSP_USING_UART4
    {
        "uart4",
        UART4,
        UART4_IRQn,
    },
#endif
};

static struct gd32_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

static rt_err_t gd32_configure(struct rt_serial_device *serial,
                               struct serial_configure *cfg)
{
    struct gd32_uart *usart_obj;
    struct gd32_uart_config *usart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    usart_obj = (struct gd32_uart *) serial->parent.user_data;
    usart = usart_obj->config;
    RT_ASSERT(usart != RT_NULL);

    usart_deinit(usart->uart_base);
    usart_baudrate_set(usart->uart_base, cfg->baud_rate);

    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        usart_word_length_set(usart->uart_base, USART_WL_8BIT);
        break;

    case DATA_BITS_9:
        usart_word_length_set(usart->uart_base, USART_WL_9BIT);
        break;
    default:
        usart_word_length_set(usart->uart_base, USART_WL_8BIT);
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        usart_stop_bit_set(usart->uart_base, USART_STB_1BIT);
        break;
    case STOP_BITS_2:
        usart_stop_bit_set(usart->uart_base, USART_STB_2BIT);
        break;
    default:
        usart_stop_bit_set(usart->uart_base, USART_STB_1BIT);
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_NONE:
        usart_parity_config(usart->uart_base, USART_PM_NONE);
        break;
    case PARITY_ODD:
        usart_parity_config(usart->uart_base, USART_PM_ODD);
        break;
    case PARITY_EVEN:
        usart_parity_config(usart->uart_base, USART_PM_EVEN);
        break;
    default:
        usart_parity_config(usart->uart_base, USART_PM_NONE);
        break;
    }
    usart_hardware_flow_rts_config(usart->uart_base, USART_RTS_DISABLE);
    usart_hardware_flow_cts_config(usart->uart_base, USART_CTS_DISABLE);
    usart_receive_config(usart->uart_base, USART_RECEIVE_ENABLE);
    usart_transmit_config(usart->uart_base, USART_TRANSMIT_ENABLE);
    usart_enable(usart->uart_base);

    return RT_EOK;
}

static rt_err_t gd32_control(struct rt_serial_device *serial, int cmd,
                             void *arg)
{
    struct gd32_uart *usart_obj;
    struct gd32_uart_config *usart;

    RT_ASSERT(serial != RT_NULL);
    usart_obj = (struct gd32_uart *) serial->parent.user_data;
    usart = usart_obj->config;
    RT_ASSERT(usart != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        ECLIC_DisableIRQ(usart->irqn);
        usart_interrupt_disable(usart->uart_base, USART_INT_RBNE);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        ECLIC_EnableIRQ(usart->irqn);
        /* enable USART0 receive interrupt */
        usart_interrupt_enable(usart->uart_base, USART_INT_RBNE);
        break;
    }

    return RT_EOK;
}

static int gd32_putc(struct rt_serial_device *serial, char ch)
{
    struct gd32_uart *usart_obj;
    struct gd32_uart_config *usart;

    RT_ASSERT(serial != RT_NULL);
    usart_obj = (struct gd32_uart *) serial->parent.user_data;
    usart = usart_obj->config;
    RT_ASSERT(usart != RT_NULL);

    usart_data_transmit(usart->uart_base, (uint8_t) ch);
    while (usart_flag_get(usart->uart_base, USART_FLAG_TBE) == RESET);

    return 1;
}

static int gd32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct gd32_uart *usart_obj;
    struct gd32_uart_config *usart;

    RT_ASSERT(serial != RT_NULL);
    usart_obj = (struct gd32_uart *) serial->parent.user_data;
    usart = usart_obj->config;
    RT_ASSERT(usart != RT_NULL);

    ch = -1;
    if (RESET != usart_flag_get(usart->uart_base, USART_FLAG_RBNE))
    {
        ch = usart_data_receive(usart->uart_base) & 0xff;
    }

    return ch;
}

static const struct rt_uart_ops gd32_uart_ops = { gd32_configure, gd32_control,
           gd32_putc, gd32_getc,
           RT_NULL
};

static void usart_isr(struct rt_serial_device *serial)
{
    struct gd32_uart *usart_obj;
    struct gd32_uart_config *usart;

    RT_ASSERT(serial != RT_NULL);
    usart_obj = (struct gd32_uart *) serial->parent.user_data;
    usart = usart_obj->config;
    RT_ASSERT(usart != RT_NULL);

    if ((usart_interrupt_flag_get(usart->uart_base, USART_INT_FLAG_RBNE)
            != RESET)
            && (RESET != usart_flag_get(usart->uart_base, USART_FLAG_RBNE)))
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        usart_interrupt_flag_clear(usart->uart_base, USART_INT_FLAG_RBNE);
        usart_flag_clear(usart->uart_base, USART_FLAG_RBNE);
    }
    else
    {
        if (usart_flag_get(usart->uart_base, USART_FLAG_CTSF) != RESET)
        {
            usart_flag_clear(usart->uart_base, USART_FLAG_CTSF);
        }

        if (usart_flag_get(usart->uart_base, USART_FLAG_LBDF) != RESET)
        {
            usart_flag_clear(usart->uart_base, USART_FLAG_LBDF);
        }

        if (usart_flag_get(usart->uart_base, USART_FLAG_TC) != RESET)
        {
            usart_flag_clear(usart->uart_base, USART_FLAG_TC);
        }
    }
}

#ifdef BSP_USING_UART0

void USART0_IRQHandler(void)
{
    rt_interrupt_enter();

    usart_isr(&uart_obj[GDUART0_INDEX].serial);

    rt_interrupt_leave();
}

#endif

#ifdef BSP_USING_UART1

void USART1_IRQHandler(void)
{
    rt_interrupt_enter();

    usart_isr(&uart_obj[GDUART1_INDEX].serial);

    rt_interrupt_leave();
}

#endif

#ifdef BSP_USING_UART2

void USART2_IRQHandler(void)
{
    rt_interrupt_enter();

    usart_isr(&uart_obj[GDUART2_INDEX].serial);

    rt_interrupt_leave();
}

#endif

#ifdef BSP_USING_UART3

void UART3_IRQHandler(void)
{
    rt_interrupt_enter();

    usart_isr(&uart_obj[GDUART3_INDEX].serial);

    rt_interrupt_leave();
}

#endif

#ifdef BSP_USING_UART4

void UART4_IRQHandler(void)
{
    rt_interrupt_enter();

    usart_isr(&uart_obj[GDUART4_INDEX].serial);

    rt_interrupt_leave();
}

#endif

int rt_hw_usart_init(void)
{
    rt_size_t obj_num;
    int index;

#ifdef BSP_USING_UART0
    rcu_periph_clock_enable(RCU_USART0);
#endif
#ifdef BSP_USING_UART1
    rcu_periph_clock_enable(RCU_USART1);
#endif
#ifdef BSP_USING_UART2
    rcu_periph_clock_enable(RCU_USART2);
#endif
#ifdef BSP_USING_UART3
    rcu_periph_clock_enable(RCU_UART3);
#endif
#ifdef BSP_USING_UART4
    rcu_periph_clock_enable(RCU_UART4);
#endif

    obj_num = sizeof(uart_obj) / sizeof(struct gd32_uart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    for (index = 0; index < obj_num; index++)
    {
        /* init UART object */
        uart_obj[index].config = &uart_config[index];
        uart_obj[index].serial.ops = &gd32_uart_ops;
        uart_obj[index].serial.config = config;

        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[index].serial,
                                       uart_obj[index].config->name,
                                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX
                                       | RT_DEVICE_FLAG_INT_TX, &uart_obj[index]);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif /* RT_USING_SERIAL */

/******************** end of file *******************/
