/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-23     Jonas        first version
 */

#include "drv_usart_v2.h"

#ifdef RT_USING_SERIAL_V2
#if !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && \
    !defined(BSP_USING_UART3) && !defined(BSP_USING_UART4) && \
    !defined(BSP_USING_UART5) && !defined(BSP_USING_UART6) && \
    !defined(BSP_USING_UART7) && !defined(BSP_USING_UART8)
    #error "Please define at least one BSP_USING_UARTx"
#endif

enum
{
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
#ifdef BSP_USING_UART6
    UART6_INDEX,
#endif
#ifdef BSP_USING_UART7
    UART7_INDEX,
#endif
#ifdef BSP_USING_UART8
    UART8_INDEX,
#endif
};

static struct at32_usart usart_config[] =
{
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
        USART3,
        USART3_IRQn,
    },
#endif
#ifdef BSP_USING_UART4
    {
        "uart4",
        UART4,
        UART4_IRQn,
    },
#endif
#ifdef BSP_USING_UART5
    {
        "uart5",
        UART5,
        UART5_IRQn,
    },
#endif
#ifdef BSP_USING_UART6
    {
        "uart6",
        USART6,
        USART6_IRQn,
    },
#endif
#ifdef BSP_USING_UART7
    {
        "uart7",
        UART7,
        UART7_IRQn,
    },
#endif
#ifdef BSP_USING_UART8
    {
        "uart8",
        UART8,
        UART8_IRQn,
    },
#endif
};

static rt_err_t at32_configure(struct rt_serial_device *serial,
                               struct serial_configure *cfg)
{
    struct at32_usart *usart_instance = (struct at32_usart *) serial->parent.user_data;
    usart_data_bit_num_type data_bit;
    usart_stop_bit_num_type stop_bit;
    usart_parity_selection_type parity_mode;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    RT_ASSERT(usart_instance != RT_NULL);

    at32_msp_usart_init((void *)usart_instance->usart_x);

    usart_receiver_enable(usart_instance->usart_x, TRUE);
    usart_transmitter_enable(usart_instance->usart_x, TRUE);

    usart_hardware_flow_control_set(usart_instance->usart_x, USART_HARDWARE_FLOW_NONE);

    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        data_bit = USART_DATA_8BITS;
        break;
    case DATA_BITS_9:
        data_bit = USART_DATA_9BITS;
        break;
    default:
        data_bit = USART_DATA_8BITS;
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        stop_bit = USART_STOP_1_BIT;
        break;
    case STOP_BITS_2:
        stop_bit = USART_STOP_2_BIT;
        break;
    default:
        stop_bit = USART_STOP_1_BIT;
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_NONE:
        parity_mode = USART_PARITY_NONE;
        break;
    case PARITY_ODD:
        parity_mode = USART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        parity_mode = USART_PARITY_EVEN;
        break;
    default:
        parity_mode = USART_PARITY_NONE;
        break;
    }
    usart_parity_selection_config(usart_instance->usart_x, parity_mode);
    usart_init(usart_instance->usart_x, cfg->baud_rate, data_bit, stop_bit);
    usart_enable(usart_instance->usart_x, TRUE);

    return RT_EOK;
}

static rt_err_t at32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct at32_usart *usart;

    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct at32_usart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    if (ctrl_arg & (RT_DEVICE_FLAG_RX_BLOCKING | RT_DEVICE_FLAG_RX_NON_BLOCKING))
    {
        ctrl_arg = RT_DEVICE_FLAG_INT_RX;
    }
    else if (ctrl_arg & (RT_DEVICE_FLAG_TX_BLOCKING | RT_DEVICE_FLAG_TX_NON_BLOCKING))
    {
        ctrl_arg = RT_DEVICE_FLAG_INT_TX;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        nvic_irq_disable(usart->irqn);
        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX)
            usart_interrupt_enable(usart->usart_x, USART_RDBF_INT, FALSE);
        else if (ctrl_arg == RT_DEVICE_FLAG_INT_TX)
            usart_interrupt_enable(usart->usart_x, USART_TDBE_INT, FALSE);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        nvic_irq_enable(usart->irqn, 4, 1);
        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX)
            usart_interrupt_enable(usart->usart_x, USART_RDBF_INT, TRUE);
        else if (ctrl_arg == RT_DEVICE_FLAG_INT_TX)
            usart_interrupt_enable(usart->usart_x, USART_TDBE_INT, TRUE);
        break;
    case RT_DEVICE_CTRL_CONFIG:
        at32_control(serial, RT_DEVICE_CTRL_SET_INT, (void *)ctrl_arg);
        break;
    case RT_DEVICE_CHECK_OPTMODE:
    {
        return RT_SERIAL_TX_BLOCKING_BUFFER;
    }
    case RT_DEVICE_CTRL_CLOSE:
        usart_reset(usart->usart_x);
        break;
    }

    return RT_EOK;
}

static int at32_putc(struct rt_serial_device *serial, char ch)
{
    struct at32_usart *usart;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct at32_usart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    usart_data_transmit(usart->usart_x, (uint8_t)ch);
    while (usart_flag_get(usart->usart_x, USART_TDC_FLAG) == RESET);

    return 1;
}

static int at32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct at32_usart *usart;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct at32_usart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    ch = -1;
    if (usart_flag_get(usart->usart_x, USART_RDBF_FLAG) != RESET)
    {
        ch = usart_data_receive(usart->usart_x) & 0xff;
    }

    return ch;
}

static rt_size_t at32_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, rt_uint32_t tx_flag)
{
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    at32_control(serial, RT_DEVICE_CTRL_SET_INT, (void *)tx_flag);

    return size;
}

static const struct rt_uart_ops at32_usart_ops =
{
    at32_configure,
    at32_control,
    at32_putc,
    at32_getc,
    at32_transmit
};

static void usart_isr(struct rt_serial_device *serial)
{
    struct at32_usart *usart_instance;

    RT_ASSERT(serial != RT_NULL);

    usart_instance = (struct at32_usart *) serial->parent.user_data;
    RT_ASSERT(usart_instance != RT_NULL);

    if (usart_flag_get(usart_instance->usart_x, USART_RDBF_FLAG) != RESET)
    {
        struct rt_serial_rx_fifo *rx_fifo;
        rx_fifo = (struct rt_serial_rx_fifo *) serial->serial_rx;
        RT_ASSERT(rx_fifo != RT_NULL);

        rt_ringbuffer_putchar(&(rx_fifo->rb), usart_data_receive(usart_instance->usart_x));

        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
    else
    {
        if ((usart_flag_get(usart_instance->usart_x, USART_TDBE_FLAG) != RESET) && usart_instance->usart_x->ctrl1_bit.tdbeien)
        {
            struct rt_serial_tx_fifo *tx_fifo;
            tx_fifo = (struct rt_serial_tx_fifo *) serial->serial_tx;
            RT_ASSERT(tx_fifo != RT_NULL);

            rt_uint8_t put_char = 0;
            if (rt_ringbuffer_getchar(&(tx_fifo->rb), &put_char))
            {
                usart_data_transmit(usart_instance->usart_x, put_char);
            }
            else
            {
                usart_interrupt_enable(usart_instance->usart_x, USART_TDBE_INT, FALSE);
                usart_interrupt_enable(usart_instance->usart_x, USART_TDC_INT, TRUE);
            }
            usart_flag_clear(usart_instance->usart_x, USART_TDBE_FLAG);
        }
        else if (usart_flag_get(usart_instance->usart_x, USART_TDC_FLAG) != RESET)
        {

            usart_interrupt_enable(usart_instance->usart_x, USART_TDC_INT, FALSE);

            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);

            usart_flag_clear(usart_instance->usart_x, USART_TDC_FLAG);
        }
        if (usart_flag_get(usart_instance->usart_x, USART_CTSCF_FLAG) != RESET)
        {
            usart_flag_clear(usart_instance->usart_x, USART_CTSCF_FLAG);
        }

        if (usart_flag_get(usart_instance->usart_x, USART_BFF_FLAG) != RESET)
        {
            usart_flag_clear(usart_instance->usart_x, USART_BFF_FLAG);
        }

    }
}

#ifdef BSP_USING_UART1
void USART1_IRQHandler(void)
{
    rt_interrupt_enter();

    usart_isr(&usart_config[UART1_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART2
void USART2_IRQHandler(void)
{
    rt_interrupt_enter();

    usart_isr(&usart_config[UART2_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART3
void USART3_IRQHandler(void)
{
    rt_interrupt_enter();

    usart_isr(&usart_config[UART3_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART4
void UART4_IRQHandler(void)
{
    rt_interrupt_enter();

    usart_isr(&usart_config[UART4_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART5
void UART5_IRQHandler(void)
{
    rt_interrupt_enter();

    usart_isr(&usart_config[UART5_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART6
void USART6_IRQHandler(void)
{
    rt_interrupt_enter();

    usart_isr(&usart_config[UART6_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART7
void UART7_IRQHandler(void)
{
    rt_interrupt_enter();

    usart_isr(&usart_config[UART7_INDEX].serial);

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART8
void UART8_IRQHandler(void)
{
    rt_interrupt_enter();

    usart_isr(&usart_config[UART8_INDEX].serial);

    rt_interrupt_leave();
}
#endif

int rt_hw_usart_init(void)
{
    rt_size_t obj_num;
    int index;

    obj_num = sizeof(usart_config) / sizeof(struct at32_usart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    for (index = 0; index < obj_num; index++)
    {
        usart_config[index].serial.config = config;
        usart_config[index].serial.ops = &at32_usart_ops;

        /* register uart device */
        result = rt_hw_serial_register(&usart_config[index].serial,
                                       usart_config[index].name,
                                       RT_DEVICE_FLAG_RDWR |
                                       RT_DEVICE_FLAG_INT_RX |
                                       RT_DEVICE_FLAG_INT_TX,
                                       &usart_config[index]);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif /* RT_USING_SERIAL_V2 */
