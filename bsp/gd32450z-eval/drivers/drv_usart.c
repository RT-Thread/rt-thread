/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2010-03-29     Bernard      remove interrupt Tx and DMA Rx mode
 * 2012-02-08     aozima       update for F4.
 * 2012-07-28     aozima       update for ART board.
 * 2016-05-28     armink       add DMA Rx mode
 */

#include <gd32f4xx.h>
#include <drv_usart.h>
#include <board.h>

#ifdef RT_USING_SERIAL

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1) && \
    !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && \
    !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5) && \
    !defined(BSP_USING_UART6) && !defined(BSP_USING_UART7)
#error "Please define at least one UARTx"

#endif

#include <rtdevice.h>

/* GD32 uart driver */
// Todo: compress uart info
struct gd32_uart
{
    uint32_t uart_periph;           //Todo: 3bits
    IRQn_Type irqn;                 //Todo: 7bits
    rcu_periph_enum per_clk;        //Todo: 5bits
    rcu_periph_enum tx_gpio_clk;    //Todo: 5bits
    rcu_periph_enum rx_gpio_clk;    //Todo: 5bits
    uint32_t tx_port;               //Todo: 4bits
    uint16_t tx_af;                 //Todo: 4bits
    uint16_t tx_pin;                //Todo: 4bits
    uint32_t rx_port;               //Todo: 4bits
    uint16_t rx_af;                 //Todo: 4bits
    uint16_t rx_pin;                //Todo: 4bits

    struct rt_serial_device * serial;
    char *device_name;
};

static void uart_isr(struct rt_serial_device *serial);

#if defined(BSP_USING_UART0)
struct rt_serial_device serial0;

void USART0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial0);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)
struct rt_serial_device serial1;

void USART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial1);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
struct rt_serial_device serial2;

void USART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial2);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
struct rt_serial_device serial3;

void UART3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial3);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
struct rt_serial_device serial4;

void UART4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial4);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
struct rt_serial_device serial5;

void USART5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial5);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)
struct rt_serial_device serial6;

void UART6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial6);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_UART7)
struct rt_serial_device serial7;

void UART7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial7);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART7 */

static const struct gd32_uart uarts[] = {
    #ifdef BSP_USING_UART0
    {
        USART0,                                 // uart peripheral index
        USART0_IRQn,                            // uart iqrn
        RCU_USART0, RCU_GPIOA, RCU_GPIOA,       // periph clock, tx gpio clock, rt gpio clock
        GPIOA, GPIO_AF_7, GPIO_PIN_9,           // tx port, tx alternate, tx pin
        GPIOA, GPIO_AF_7, GPIO_PIN_10,          // rx port, rx alternate, rx pin
        &serial0,
        "uart0",
    },
    #endif

    #ifdef BSP_USING_UART1
    {
        USART1,                                 // uart peripheral index
        USART1_IRQn,                            // uart iqrn
        RCU_USART1, RCU_GPIOA, RCU_GPIOA,       // periph clock, tx gpio clock, rt gpio clock
        GPIOA, GPIO_AF_7, GPIO_PIN_2,           // tx port, tx alternate, tx pin
        GPIOA, GPIO_AF_7, GPIO_PIN_3,           // rx port, rx alternate, rx pin
        &serial1,
        "uart1",
    },
    #endif

    #ifdef BSP_USING_UART2
    {
        USART2,                                 // uart peripheral index
        USART2_IRQn,                            // uart iqrn
        RCU_USART2, RCU_GPIOB, RCU_GPIOB,       // periph clock, tx gpio clock, rt gpio clock
        GPIOB, GPIO_AF_7, GPIO_PIN_10,          // tx port, tx alternate, tx pin
        GPIOB, GPIO_AF_7, GPIO_PIN_11,          // rx port, rx alternate, rx pin
        &serial2,
        "uart2",
    },
    #endif

    #ifdef BSP_USING_UART3
    {
        UART3,                                 // uart peripheral index
        UART3_IRQn,                            // uart iqrn
        RCU_UART3, RCU_GPIOC, RCU_GPIOC,       // periph clock, tx gpio clock, rt gpio clock
        GPIOC, GPIO_AF_8, GPIO_PIN_10,         // tx port, tx alternate, tx pin
        GPIOC, GPIO_AF_8, GPIO_PIN_11,         // rx port, rx alternate, rx pin
        &serial3,
        "uart3",
    },
    #endif

    #ifdef BSP_USING_UART4
    {
        UART4,                                 // uart peripheral index
        UART4_IRQn,                            // uart iqrn
        RCU_UART4, RCU_GPIOC, RCU_GPIOD,       // periph clock, tx gpio clock, rt gpio clock
        GPIOC, GPIO_AF_8, GPIO_PIN_12,         // tx port, tx alternate, tx pin
        GPIOD, GPIO_AF_8, GPIO_PIN_2,          // rx port, rx alternate, rx pin
        &serial4,
        "uart4",
    },
    #endif

    #ifdef BSP_USING_UART5
    {
        USART5,                                 // uart peripheral index
        USART5_IRQn,                            // uart iqrn
        RCU_USART5, RCU_GPIOC, RCU_GPIOC,       // periph clock, tx gpio clock, rt gpio clock
        GPIOC, GPIO_AF_8, GPIO_PIN_6,           // tx port, tx alternate, tx pin
        GPIOC, GPIO_AF_8, GPIO_PIN_7,           // rx port, rx alternate, rx pin
        &serial5,
        "uart5",
    },
    #endif

    #ifdef BSP_USING_UART6
    {
        UART6,                                 // uart peripheral index
        UART6_IRQn,                            // uart iqrn
        RCU_UART6, RCU_GPIOE, RCU_GPIOE,       // periph clock, tx gpio clock, rt gpio clock
        GPIOE, GPIO_AF_8, GPIO_PIN_7,          // tx port, tx alternate, tx pin
        GPIOE, GPIO_AF_8, GPIO_PIN_8,          // rx port, rx alternate, rx pin
        &serial6,
        "uart6",
    },
    #endif

    #ifdef BSP_USING_UART7
    {
        UART7,                                 // uart peripheral index
        UART7_IRQn,                            // uart iqrn
        RCU_UART7, RCU_GPIOE, RCU_GPIOE,       // periph clock, tx gpio clock, rt gpio clock
        GPIOE, GPIO_AF_8, GPIO_PIN_0,          // tx port, tx alternate, tx pin
        GPIOE, GPIO_AF_8, GPIO_PIN_1,          // rx port, rx alternate, rx pin
        &serial7,
        "uart7",
    },
    #endif
};


/**
* @brief UART MSP Initialization
*        This function configures the hardware resources used in this example:
*           - Peripheral's clock enable
*           - Peripheral's GPIO Configuration
*           - NVIC configuration for UART interrupt request enable
* @param huart: UART handle pointer
* @retval None
*/
void gd32_uart_gpio_init(struct gd32_uart *uart)
{
    /* enable USART clock */
    rcu_periph_clock_enable(uart->tx_gpio_clk);
    rcu_periph_clock_enable(uart->rx_gpio_clk);
    rcu_periph_clock_enable(uart->per_clk);

    /* connect port to USARTx_Tx */
    gpio_af_set(uart->tx_port, uart->tx_af, uart->tx_pin);

    /* connect port to USARTx_Rx */
    gpio_af_set(uart->rx_port, uart->rx_af, uart->rx_pin);

    /* configure USART Tx as alternate function push-pull */
    gpio_mode_set(uart->tx_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, uart->tx_pin);
    gpio_output_options_set(uart->tx_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, uart->tx_pin);

    /* configure USART Rx as alternate function push-pull */
    gpio_mode_set(uart->rx_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, uart->rx_pin);
    gpio_output_options_set(uart->rx_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, uart->rx_pin);

    NVIC_SetPriority(uart->irqn, 0);
    NVIC_EnableIRQ(uart->irqn);
}

static rt_err_t gd32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = (struct gd32_uart *)serial->parent.user_data;

    gd32_uart_gpio_init(uart);

    usart_baudrate_set(uart->uart_periph, cfg->baud_rate);

    switch (cfg->data_bits)
    {
    case DATA_BITS_9:
        usart_word_length_set(uart->uart_periph, USART_WL_9BIT);
        break;

    default:
        usart_word_length_set(uart->uart_periph, USART_WL_8BIT);
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_2:
        usart_stop_bit_set(uart->uart_periph, USART_STB_2BIT);
        break;
    default:
        usart_stop_bit_set(uart->uart_periph, USART_STB_1BIT);
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_ODD:
        usart_parity_config(uart->uart_periph, USART_PM_ODD);
        break;
    case PARITY_EVEN:
        usart_parity_config(uart->uart_periph, USART_PM_EVEN);
        break;
    default:
        usart_parity_config(uart->uart_periph, USART_PM_NONE);
        break;
    }

    usart_receive_config(uart->uart_periph, USART_RECEIVE_ENABLE);
    usart_transmit_config(uart->uart_periph, USART_TRANSMIT_ENABLE);
    usart_enable(uart->uart_periph);

    return RT_EOK;
}

static rt_err_t gd32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct gd32_uart *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->irqn);
        /* disable interrupt */
        usart_interrupt_disable(uart->uart_periph, USART_INTEN_RBNEIE);

        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irqn);
        /* enable interrupt */
        usart_interrupt_enable(uart->uart_periph, USART_INTEN_RBNEIE);
        break;
    }

    return RT_EOK;
}

static int gd32_putc(struct rt_serial_device *serial, char ch)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct gd32_uart *)serial->parent.user_data;

    usart_data_transmit(uart->uart_periph, ch);
    while((usart_flag_get(uart->uart_periph, USART_FLAG_TC) == RESET));

    return 1;
}

static int gd32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct gd32_uart *)serial->parent.user_data;

    ch = -1;
    if (usart_flag_get(uart->uart_periph, USART_FLAG_RBNE) != RESET)
        ch = usart_data_receive(uart->uart_periph);
    return ch;
}

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial)
{
    struct gd32_uart *uart = (struct gd32_uart *) serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);

    /* UART in mode Receiver -------------------------------------------------*/
    if ((usart_interrupt_flag_get(uart->uart_periph, USART_INT_RBNEIE) != RESET) &&
            (usart_flag_get(uart->uart_periph, USART_FLAG_RBNE) != RESET))
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        /* Clear RXNE interrupt flag */
        usart_flag_clear(uart->uart_periph, USART_FLAG_RBNE);
    }
}

static const struct rt_uart_ops gd32_uart_ops =
{
    gd32_configure,
    gd32_control,
    gd32_putc,
    gd32_getc,
};

int gd32_hw_usart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    int i;


    for (i = 0; i < sizeof(uarts) / sizeof(uarts[0]); i++)
    {
        uarts[i].serial->ops    = &gd32_uart_ops;
        uarts[i].serial->config = config;

        /* register UART1 device */
        rt_hw_serial_register(uarts[i].serial,
                              uarts[i].device_name,
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              (void *)&uarts[i]);
    }

    return 0;
}
INIT_BOARD_EXPORT(gd32_hw_usart_init);
#endif
