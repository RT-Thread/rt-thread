/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author              Notes
 * 2022-04-18     Dozingfiretruck     first version
 */

#include "board.h"
#include "drv_usart.h"
#include "drv_config.h"
#include "at32_msp.h"

#ifdef RT_USING_SERIAL
#if !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && !defined(BSP_USING_UART4) && \
    !defined(BSP_USING_UART5) && !defined(BSP_USING_UART6) && !defined(BSP_USING_UART7) && !defined(BSP_USING_UART8)
    #error "Please define at least one BSP_USING_UARTx"
    /* this driver can be disabled at menuconfig → RT-Thread Components → Device Drivers */
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

static struct at32_uart_config uart_config[] = {
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
#ifdef BSP_USING_UART6
    UART6_CONFIG,
#endif
#ifdef BSP_USING_UART7
    UART7_CONFIG,
#endif
#ifdef BSP_USING_UART8
    UART8_CONFIG,
#endif
};

static struct at32_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

static rt_err_t at32_configure(struct rt_serial_device *serial, struct serial_configure *cfg) {
    struct at32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = rt_container_of(serial, struct at32_uart, serial);

    at32_msp_usart_init((void *)(uart->config->Instance));

    rt_uint8_t data_bit_type;
    rt_uint8_t stop_bit_type;
    rt_uint8_t hardware_flow_control_type;
    rt_uint8_t parity_selection_type;
    switch (cfg->flowcontrol)
    {
    case RT_SERIAL_FLOWCONTROL_NONE:
        hardware_flow_control_type = USART_HARDWARE_FLOW_NONE;
        break;
    case RT_SERIAL_FLOWCONTROL_CTSRTS:
        hardware_flow_control_type = USART_HARDWARE_FLOW_RTS_CTS;
        break;
    default:
        hardware_flow_control_type = USART_HARDWARE_FLOW_NONE;
        break;
    }

    switch (cfg->data_bits) {
    case DATA_BITS_7:
        data_bit_type = USART_DATA_7BITS;
        break;
    case DATA_BITS_8:
        data_bit_type = USART_DATA_8BITS;
        break;
    case DATA_BITS_9:
        data_bit_type = USART_DATA_9BITS;
        break;
    default:
        data_bit_type = USART_DATA_8BITS;
        break;
    }

    switch (cfg->stop_bits) {
    case STOP_BITS_1:
        stop_bit_type = USART_STOP_1_BIT;
        break;
    case STOP_BITS_2:
        stop_bit_type = USART_STOP_2_BIT;
        break;
    default:
        stop_bit_type = USART_STOP_1_BIT;
        break;
    }

    switch (cfg->parity) {
    case PARITY_NONE:
        parity_selection_type = USART_PARITY_NONE;
        break;
    case PARITY_ODD:
        parity_selection_type = USART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        parity_selection_type = USART_PARITY_EVEN;
        break;
    default:
        parity_selection_type = USART_PARITY_NONE;
        break;
    }

    usart_init(uart->config->Instance, cfg->baud_rate, (usart_data_bit_num_type)data_bit_type, (usart_stop_bit_num_type)stop_bit_type);
    usart_hardware_flow_control_set(uart->config->Instance, (usart_hardware_flow_control_type)hardware_flow_control_type);
    usart_parity_selection_config(uart->config->Instance, (usart_parity_selection_type)parity_selection_type);
    usart_transmitter_enable(uart->config->Instance, TRUE);
    usart_receiver_enable(uart->config->Instance, TRUE);
    usart_enable(uart->config->Instance, TRUE);
    return RT_EOK;
}

static rt_err_t at32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct at32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct at32_uart, serial);

    switch (cmd) {
    case RT_DEVICE_CTRL_CLR_INT:
        nvic_irq_enable(uart->config->irq_type, 1, 0);
        usart_interrupt_enable(uart->config->Instance, USART_RDBF_INT, FALSE);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        nvic_irq_enable(uart->config->irq_type, 1, 0);
        usart_interrupt_enable(uart->config->Instance, USART_RDBF_INT, TRUE);

        break;
    }

    return RT_EOK;
}

static int at32_putc(struct rt_serial_device *serial, char c) {
    struct at32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct at32_uart, serial);

    while(usart_flag_get(uart->config->Instance, USART_TDBE_FLAG) == RESET);
    usart_data_transmit(uart->config->Instance, (uint16_t)c);

    return 1;
}

static int at32_getc(struct rt_serial_device *serial) {
    int ch;
    struct at32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct at32_uart, serial);

    ch = -1;
    if (RESET != usart_flag_get(uart->config->Instance, USART_RDBF_FLAG)) {
        ch = usart_data_receive(uart->config->Instance) & 0xff;
    }

    return ch;
}

static const struct rt_uart_ops at32_uart_ops =
{
    .configure = at32_configure,
    .control = at32_control,
    .putc = at32_putc,
    .getc = at32_getc,
    .dma_transmit = RT_NULL
};

static void usart_isr(struct rt_serial_device *serial) {
    struct at32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct at32_uart, serial);

    if (usart_flag_get(uart->config->Instance, USART_RDBF_FLAG) != RESET) {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        usart_flag_clear(uart->config->Instance, USART_RDBF_FLAG);
    } else {
        if (usart_flag_get(uart->config->Instance, USART_CTSCF_FLAG) != RESET) {
            usart_flag_clear(uart->config->Instance, USART_CTSCF_FLAG);
        }

        if (usart_flag_get(uart->config->Instance, USART_BFF_FLAG) != RESET) {
            usart_flag_clear(uart->config->Instance, USART_BFF_FLAG);
        }

        if (usart_flag_get(uart->config->Instance, USART_TDC_FLAG) != RESET) {
            usart_flag_clear(uart->config->Instance, USART_TDC_FLAG);
        }
    }
}

#ifdef BSP_USING_UART1
void USART1_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&(uart_obj[UART1_INDEX].serial));

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART2
void USART2_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&(uart_obj[UART2_INDEX].serial));

    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART3
void USART3_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&(uart_obj[UART3_INDEX].serial));

    rt_interrupt_leave();
}
#endif

int rt_hw_usart_init(void) {
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct at32_uart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    // at32_uart_get_dma_config();

    for (int i = 0; i < obj_num; i++)
    {
        /* init UART object */
        uart_obj[i].config = &uart_config[i];
        uart_obj[i].serial.ops    = &at32_uart_ops;
        uart_obj[i].serial.config = config;

        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial, uart_obj[i].config->name,
                                       RT_DEVICE_FLAG_RDWR
                                       | RT_DEVICE_FLAG_INT_RX
                                       | RT_DEVICE_FLAG_INT_TX
                                       | uart_obj[i].uart_dma_flag
                                       , RT_NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif /* BSP_USING_SERIAL */

/******************** end of file *******************/
