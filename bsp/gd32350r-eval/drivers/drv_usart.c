/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-06-21     RiceChen          the first version
 */


#include <rthw.h>

#ifdef RT_USING_SERIAL

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1)
#error "Please define at least one UARTx"
#endif

#include "drv_usart.h"

static struct gd32_usart_config usart_config[] =
{
#ifdef BSP_USING_UART0
    UART0_BUS_CONFIG,
#endif
#ifdef BSP_USING_UART1
    UART1_BUS_CONFIG,
#endif
};

static struct gd32_usart_bus usart_obj[sizeof(usart_config) / sizeof(usart_config[0])];

void gd32_usart_gpio_init(struct gd32_usart_bus *bus)
{
    rcu_periph_clock_enable(bus->config->per_clk);
    rcu_periph_clock_enable(bus->config->tx_gpio_clk);
    rcu_periph_clock_enable(bus->config->rx_gpio_clk);

    gpio_af_set(bus->config->tx_port, GPIO_AF_1, bus->config->tx_pin);
    gpio_af_set(bus->config->rx_port, GPIO_AF_1, bus->config->rx_pin);

    gpio_mode_set(bus->config->tx_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, bus->config->tx_pin);
    gpio_output_options_set(bus->config->tx_port, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, bus->config->tx_pin);

    gpio_mode_set(bus->config->rx_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, bus->config->rx_pin);
    gpio_output_options_set(bus->config->rx_port, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, bus->config->rx_pin);

    NVIC_SetPriority(bus->config->irqn, 0);
    NVIC_EnableIRQ(bus->config->irqn);
    usart_deinit(bus->config->periph);
}

rt_err_t gd32_usart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct gd32_usart_bus *bus = RT_NULL;

    bus = (struct gd32_usart_bus *)serial->parent.user_data;

    gd32_usart_gpio_init(bus);

    usart_baudrate_set(bus->config->periph, cfg->baud_rate);

    switch (cfg->data_bits)
    {
        case DATA_BITS_9:
            usart_word_length_set(bus->config->periph, USART_WL_9BIT);
            break;

        default:
            usart_word_length_set(bus->config->periph, USART_WL_8BIT);
            break;
    }

    switch (cfg->stop_bits)
    {
        case STOP_BITS_2:
            usart_stop_bit_set(bus->config->periph, USART_STB_2BIT);
            break;
        default:
            usart_stop_bit_set(bus->config->periph, USART_STB_1BIT);
            break;
    }

    switch (cfg->parity)
    {
        case PARITY_ODD:
            usart_parity_config(bus->config->periph, USART_PM_ODD);
            break;
        case PARITY_EVEN:
            usart_parity_config(bus->config->periph, USART_PM_EVEN);
            break;
        default:
            usart_parity_config(bus->config->periph, USART_PM_NONE);
            break;
    }

    usart_receive_config(bus->config->periph, USART_RECEIVE_ENABLE);
    usart_transmit_config(bus->config->periph, USART_TRANSMIT_ENABLE);
    usart_enable(bus->config->periph);

    return RT_EOK;
}

rt_err_t gd32_usart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct gd32_usart_bus *bus = RT_NULL;

    bus = (struct gd32_usart_bus *)serial->parent.user_data;

    switch (cmd)
    {
        case RT_DEVICE_CTRL_CLR_INT:
            /* disable rx irq */
            NVIC_DisableIRQ(bus->config->irqn);
            /* disable interrupt */
            usart_interrupt_disable(bus->config->periph, USART_INT_RBNE);

            break;
        case RT_DEVICE_CTRL_SET_INT:
            /* enable rx irq */
            NVIC_EnableIRQ(bus->config->irqn);
            /* enable interrupt */
            usart_interrupt_enable(bus->config->periph, USART_INT_RBNE);
            break;
    }

    return RT_EOK;
}

int gd32_usart_putc(struct rt_serial_device *serial, char c)
{
    struct gd32_usart_bus *bus = RT_NULL;

    bus = (struct gd32_usart_bus *)serial->parent.user_data;

    usart_data_transmit(bus->config->periph, c);
    while((usart_flag_get(bus->config->periph, USART_FLAG_TC) == RESET));

    return 1;
}

int gd32_usart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct gd32_usart_bus *bus = RT_NULL;

    bus = (struct gd32_usart_bus *)serial->parent.user_data;

    ch = -1;
    if (usart_flag_get(bus->config->periph, USART_FLAG_RBNE) != RESET)
        ch = usart_data_receive(bus->config->periph);
    return ch;
}

rt_size_t gd32_usart_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
	return RT_EOK;
}

static struct rt_uart_ops usart_ops =
{
    gd32_usart_configure,
    gd32_usart_control,
    gd32_usart_putc,
    gd32_usart_getc,
    gd32_usart_dma_transmit,
};

static void uart_isr(rt_uint32_t periph)
{
    int obj_num = 0;
    struct gd32_usart_bus *bus = RT_NULL;

    obj_num = sizeof(usart_config) / sizeof(usart_config[0]);

    for(int i = 0; i < obj_num; i++)
    {
        if(usart_obj[i].config->periph == periph)
        {
            bus = &usart_obj[i];
            break;
        }
    }

    if(bus != RT_NULL)
    {
         if ((usart_interrupt_flag_get(bus->config->periph, USART_INT_FLAG_RBNE) != RESET) &&
            (usart_flag_get(bus->config->periph, USART_FLAG_RBNE) != RESET))
        {
            rt_hw_serial_isr(&bus->serial, RT_SERIAL_EVENT_RX_IND);
            /* Clear RXNE interrupt flag */
            usart_flag_clear(bus->config->periph, USART_FLAG_RBNE);
        }
    }
}

#ifdef BSP_USING_UART0
void USART0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(USART0);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_UART1
void USART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(USART1);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

int rt_hw_usart_init(void)
{
    int obj_num = 0;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    obj_num = sizeof(usart_config) / sizeof(usart_config[0]);

    for(int i = 0; i < obj_num; i++)
    {
        usart_obj[i].serial.ops = &usart_ops;
        usart_obj[i].serial.config = config;
        usart_obj[i].config = &usart_config[i];

        /* register UART device */
        rt_hw_serial_register(&usart_obj[i].serial,
                              usart_obj[i].config->dev_name,
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              (void *)&usart_obj[i]);
    }

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_usart_init);

#endif
