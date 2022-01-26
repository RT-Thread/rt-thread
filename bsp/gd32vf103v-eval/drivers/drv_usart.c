/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-23     tyustli      first version
 */

#include <drv_usart.h>

#ifdef RT_USING_SERIAL

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) \
    && !defined(BSP_USING_UART3) && !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5)
    #error "Please define at least one BSP_USING_UARTx"
    /* this driver can be disabled at menuconfig → RT-Thread Components → Device Drivers */
#endif

struct gd32_usart {
    char *name;
    rt_uint32_t usart_base;
    rt_uint32_t usart_clk;
    rt_uint32_t gpio_clk;
    rt_uint32_t gpio_port;
    rt_uint32_t tx_pin;
    rt_uint32_t rx_pin;
    IRQn_Type irqn;
    struct rt_serial_device serial;
};

enum {
#ifdef BSP_USING_UART0
    GDUSART0_INDEX,
#endif
};

static struct gd32_usart usart_config[] = {
#ifdef BSP_USING_UART0
        { "uart0",
        USART0,
        RCU_USART0,
        RCU_GPIOA,
        GPIOA,
        GPIO_PIN_9,
        GPIO_PIN_10,
        USART0_IRQn, },
#endif
};

static rt_err_t gd32_configure(struct rt_serial_device *serial,
        struct serial_configure *cfg) {
    struct gd32_usart *usart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    usart = (struct gd32_usart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    /* enable GPIO clock */
    rcu_periph_clock_enable(usart->gpio_clk);
    /* enable USART clock */
    rcu_periph_clock_enable(usart->usart_clk);
    /* connect port to USARTx_Tx */
    gpio_init(usart->gpio_port, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ,
            usart->tx_pin);
    /* connect port to USARTx_Rx */
    gpio_init(usart->gpio_port, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ,
            usart->rx_pin);

    usart_deinit(usart->usart_base);
    usart_baudrate_set(usart->usart_base, cfg->baud_rate);

    switch (cfg->data_bits) {
    case DATA_BITS_8:
        usart_word_length_set(usart->usart_base, USART_WL_8BIT);
        break;

    case DATA_BITS_9:
        usart_word_length_set(usart->usart_base, USART_WL_9BIT);
        break;
    default:
        usart_word_length_set(usart->usart_base, USART_WL_8BIT);
        break;
    }

    switch (cfg->stop_bits) {
    case STOP_BITS_1:
        usart_stop_bit_set(usart->usart_base, USART_STB_1BIT);
        break;
    case STOP_BITS_2:
        usart_stop_bit_set(usart->usart_base, USART_STB_2BIT);
        break;
    default:
        usart_stop_bit_set(usart->usart_base, USART_STB_1BIT);
        break;
    }

    switch (cfg->parity) {
    case PARITY_NONE:
        usart_parity_config(usart->usart_base, USART_PM_NONE);
        break;
    case PARITY_ODD:
        usart_parity_config(usart->usart_base, USART_PM_ODD);
        break;
    case PARITY_EVEN:
        usart_parity_config(usart->usart_base, USART_PM_EVEN);
        break;
    default:
        usart_parity_config(usart->usart_base, USART_PM_NONE);
        break;
    }
    usart_hardware_flow_rts_config(usart->usart_base, USART_RTS_DISABLE);
    usart_hardware_flow_cts_config(usart->usart_base, USART_RTS_DISABLE);
    usart_receive_config(usart->usart_base, USART_RECEIVE_ENABLE);
    usart_transmit_config(usart->usart_base, USART_TRANSMIT_ENABLE);
    usart_enable(usart->usart_base);

    return RT_EOK;
}

static rt_err_t gd32_control(struct rt_serial_device *serial, int cmd,
        void *arg) {
    struct gd32_usart *usart;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct gd32_usart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    switch (cmd) {
    case RT_DEVICE_CTRL_CLR_INT:
        eclic_irq_disable(usart->usart_base);
        usart_interrupt_disable(usart->usart_base, USART_INT_RBNE);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        eclic_set_nlbits(ECLIC_GROUP_LEVEL3_PRIO1);
        eclic_irq_enable(usart->irqn, 1, 0);
        /* enable USART0 receive interrupt */
        usart_interrupt_enable(usart->usart_base, USART_INT_RBNE);
        break;
    }

    return RT_EOK;
}

static int gd32_putc(struct rt_serial_device *serial, char ch) {
    struct gd32_usart *usart;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct gd32_usart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    usart_data_transmit(usart->usart_base, (uint8_t) ch);
    while (usart_flag_get(usart->usart_base, USART_FLAG_TBE) == RESET)
        ;

    return 1;
}

static int gd32_getc(struct rt_serial_device *serial) {
    int ch;
    struct gd32_usart *usart;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct gd32_usart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    ch = -1;
    if (RESET != usart_flag_get(usart->usart_base, USART_FLAG_RBNE)) {
        ch = usart_data_receive(usart->usart_base) & 0xff;
    }

    return ch;
}

static const struct rt_uart_ops gd32_usart_ops = { gd32_configure, gd32_control,
        gd32_putc, gd32_getc,
        RT_NULL };

static void usart_isr(struct rt_serial_device *serial) {
    struct gd32_usart *usart;

    RT_ASSERT(serial != RT_NULL);

    usart = (struct gd32_usart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    if ((usart_interrupt_flag_get(usart->usart_base, USART_INT_FLAG_RBNE)
            != RESET)
            && (RESET != usart_flag_get(usart->usart_base, USART_FLAG_RBNE))) {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        usart_interrupt_flag_clear(usart->usart_base, USART_INT_FLAG_RBNE);
        usart_flag_clear(usart->usart_base, USART_FLAG_RBNE);
    } else {
        if (usart_flag_get(usart->usart_base, USART_FLAG_CTSF) != RESET) {
            usart_flag_clear(usart->usart_base, USART_FLAG_CTSF);
        }

        if (usart_flag_get(usart->usart_base, USART_FLAG_LBDF) != RESET) {
            usart_flag_clear(usart->usart_base, USART_FLAG_LBDF);
        }

        if (usart_flag_get(usart->usart_base, USART_FLAG_TC) != RESET) {
            usart_flag_clear(usart->usart_base, USART_FLAG_TC);
        }
    }
}
#ifdef BSP_USING_UART0

void USART0_IRQHandler(void) {
    rt_interrupt_enter();

    usart_isr(&usart_config[GDUSART0_INDEX].serial);

    rt_interrupt_leave();
}

#endif

int rt_hw_usart_init(void) {
    rt_size_t obj_num;
    int index;

    obj_num = sizeof(usart_config) / sizeof(struct gd32_usart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    for (index = 0; index < obj_num; index++) {
        usart_config[index].serial.ops = &gd32_usart_ops;
        usart_config[index].serial.config = config;

        /* register UART device */
        result = rt_hw_serial_register(&usart_config[index].serial,
                usart_config[index].name,
                RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX
                        | RT_DEVICE_FLAG_INT_TX, &usart_config[index]);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif /* RT_USING_SERIAL */

/******************** end of file *******************/
