/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     BruceOu      first implementation
 */

#include "drv_usart.h"

#ifdef RT_USING_SERIAL

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1) && \
    !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && \
    !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5) && \
    !defined(BSP_USING_UART6) && !defined(BSP_USING_UART7)
#error "Please define at least one UARTx"

#endif

#include <rtdevice.h>

static void GD32_UART_IRQHandler(struct rt_serial_device *serial);

#if defined(BSP_USING_UART0)
struct rt_serial_device serial0;

void USART0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    GD32_UART_IRQHandler(&serial0);

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

    GD32_UART_IRQHandler(&serial1);

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

    GD32_UART_IRQHandler(&serial2);

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

    GD32_UART_IRQHandler(&serial3);

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

    GD32_UART_IRQHandler(&serial4);

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

    GD32_UART_IRQHandler(&serial5);

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

    GD32_UART_IRQHandler(&serial6);

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

    GD32_UART_IRQHandler(&serial7);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART7 */

static const struct gd32_uart uart_obj[] = {
    #ifdef BSP_USING_UART0
    {
        USART0,                                // uart peripheral index
        USART0_IRQn,                           // uart iqrn
        RCU_USART0,                            // uart periph clock
#if defined SOC_SERIES_GD32F4xx
        RCU_GPIOA, RCU_GPIOA,                  // tx gpio clock, rx gpio clock
        GPIOA, GPIO_AF_7, GPIO_PIN_9,          // tx port, tx alternate, tx pin
        GPIOA, GPIO_AF_7, GPIO_PIN_10,         // rx port, rx alternate, rx pin
#elif defined SOC_SERIES_GD32H7xx
        RCU_GPIOF,                             // periph clock, tx gpio clock
        RCU_GPIOF,                             // periph clock, rx gpio clock
        GPIOF, GPIO_AF_4, GPIO_PIN_4,          // tx port, tx alternate, tx pin
        GPIOF, GPIO_AF_4, GPIO_PIN_5,          // rx port, rx alternate, rx pin
#elif defined SOC_SERIES_GD32E50x
        RCU_GPIOA, RCU_GPIOA,                  // tx gpio clock, rx gpio clock
        GPIOA, 0, GPIO_PIN_9,                  // tx port, tx alternate, tx pin
        GPIOA, 0, GPIO_PIN_10,                 // rx port, rx alternate, rx pin
        0,                                     // afio remap cfg
#else
        RCU_GPIOA, RCU_GPIOA,                  // tx gpio clock, rx gpio clock
        GPIOA, GPIO_PIN_9,                     // tx port, tx pin
        GPIOA, GPIO_PIN_10,                    // rx port, rx pin
#endif
        &serial0,
        "uart0",
    },
    #endif

    #ifdef BSP_USING_UART1
    {
        USART1,                                 // uart peripheral index
        USART1_IRQn,                            // uart iqrn
        RCU_USART1,                             // uart periph clock
#if defined SOC_SERIES_GD32F4xx || defined SOC_SERIES_GD32H7xx
        RCU_GPIOA, RCU_GPIOA,                   // tx gpio clock, rx gpio clock
        GPIOA, GPIO_AF_7, GPIO_PIN_2,           // tx port, tx alternate, tx pin
        GPIOA, GPIO_AF_7, GPIO_PIN_3,           // rx port, rx alternate, rx pin
#elif defined SOC_SERIES_GD32E50x
        RCU_GPIOA, RCU_GPIOA,                   // tx gpio clock, rx gpio clock
        GPIOA, 0, GPIO_PIN_2,                   // tx port, tx alternate, tx pin
        GPIOA, 0, GPIO_PIN_3,                   // rx port, rx alternate, rx pin
        0,                                      // afio remap cfg
#else
        RCU_GPIOA, RCU_GPIOA,                   // periph clock, tx gpio clock, rt gpio clock
        GPIOA, GPIO_PIN_2,                      // tx port, tx pin
        GPIOA, GPIO_PIN_3,                      // rx port, rx pin
#endif
        &serial1,
        "uart1",
    },
    #endif

    #ifdef BSP_USING_UART2
    {
        USART2,                                 // uart peripheral index
        USART2_IRQn,                            // uart iqrn
        RCU_USART2,                                    // uart periph clock
#if defined SOC_SERIES_GD32F4xx || defined SOC_SERIES_GD32H7xx
        RCU_GPIOB, RCU_GPIOB,                   // tx gpio clock, rt gpio clock
        GPIOB, GPIO_AF_7, GPIO_PIN_10,          // tx port, tx alternate, tx pin
        GPIOB, GPIO_AF_7, GPIO_PIN_11,          // rx port, rx alternate, rx pin
#elif defined SOC_SERIES_GD32E50x
        RCU_GPIOB, RCU_GPIOB,                   // tx gpio clock, rx gpio clock
        GPIOB, 0, GPIO_PIN_10,                  // tx port, tx alternate, tx pin
        GPIOB, 0, GPIO_PIN_11,                  // rx port, rx alternate, rx pin
        0,                                      // afio remap cfg
#else
        RCU_GPIOB, RCU_GPIOB,                   // tx gpio clock, rt gpio clock
        GPIOB, GPIO_PIN_10,                     // tx port, tx pin
        GPIOB, GPIO_PIN_11,                     // rx port, rx pin
#endif
        &serial2,
        "uart2",
    },
    #endif

    #ifdef BSP_USING_UART3
    {
        UART3,                                 // uart peripheral index
        UART3_IRQn,                            // uart iqrn
        RCU_UART3,                             // uart periph clock
#if defined SOC_SERIES_GD32F4xx
        RCU_GPIOC, RCU_GPIOC,                  // tx gpio clock, rt gpio clock
        GPIOC, GPIO_AF_8, GPIO_PIN_10,         // tx port, tx alternate, tx pin
        GPIOC, GPIO_AF_8, GPIO_PIN_11,         // rx port, rx alternate, rx pin
#elif defined SOC_SERIES_GD32E50x
        RCU_GPIOC, RCU_GPIOC,                   // tx gpio clock, rx gpio clock
        GPIOC, 0, GPIO_PIN_10,                  // tx port, tx alternate, tx pin
        GPIOC, 0, GPIO_PIN_11,                  // rx port, rx alternate, rx pin
        0,                                      // afio remap cfg
#else
        RCU_GPIOC, RCU_GPIOC,                  // periph clock, tx gpio clock, rt gpio clock
        GPIOC, GPIO_PIN_10,                    // tx port, tx pin
        GPIOC, GPIO_PIN_11,                    // rx port, rx pin
#endif
        &serial3,
        "uart3",
    },
    #endif

    #ifdef BSP_USING_UART4
    {
        UART4,                                 // uart peripheral index
        UART4_IRQn,                            // uart iqrn
        RCU_UART4, RCU_GPIOC, RCU_GPIOD,       // periph clock, tx gpio clock, rt gpio clock
#if defined SOC_SERIES_GD32F4xx
        GPIOC, GPIO_AF_8, GPIO_PIN_12,         // tx port, tx alternate, tx pin
        GPIOD, GPIO_AF_8, GPIO_PIN_2,          // rx port, rx alternate, rx pin
#elif defined SOC_SERIES_GD32E50x
        GPIOC, 0, GPIO_PIN_12,                 // tx port, tx alternate, tx pin
        GPIOD, 0, GPIO_PIN_2,                  // rx port, rx alternate, rx pin
        0,                                     // afio remap cfg
#else
        GPIOC, GPIO_PIN_12,                    // tx port, tx pin
        GPIOD, GPIO_PIN_2,                     // rx port, rx pin
#endif
        &serial4,
        "uart4",
    },
    #endif

    #ifdef BSP_USING_UART5
    {
        USART5,                                 // uart peripheral index
        USART5_IRQn,                            // uart iqrn
        RCU_USART5, RCU_GPIOC, RCU_GPIOC,       // periph clock, tx gpio clock, rt gpio clock
#if defined SOC_SERIES_GD32F4xx
        GPIOC, GPIO_AF_8, GPIO_PIN_6,           // tx port, tx alternate, tx pin
        GPIOC, GPIO_AF_8, GPIO_PIN_7,           // rx port, rx alternate, rx pin
#elif defined SOC_SERIES_GD32E50x
        GPIOC, AFIO_PC6_USART5_CFG, GPIO_PIN_6, // tx port, tx alternate, tx pin
        GPIOC, AFIO_PC7_USART5_CFG, GPIO_PIN_7, // rx port, rx alternate, rx pin
        0,                                      // afio remap cfg
#else
        GPIOC, GPIO_PIN_6,                      // tx port, tx pin
        GPIOC, GPIO_PIN_7,                      // rx port, rx pin
#endif
        &serial5,
        "uart5",
    },
    #endif

    #ifdef BSP_USING_UART6
    {
        UART6,                                 // uart peripheral index
        UART6_IRQn,                            // uart iqrn
        RCU_UART6, RCU_GPIOE, RCU_GPIOE,       // periph clock, tx gpio clock, rt gpio clock
#if defined SOC_SERIES_GD32F4xx
        GPIOE, GPIO_AF_8, GPIO_PIN_7,          // tx port, tx alternate, tx pin
        GPIOE, GPIO_AF_8, GPIO_PIN_8,          // rx port, rx alternate, rx pin
#else
        GPIOE, GPIO_PIN_7,                     // tx port, tx pin
        GPIOE, GPIO_PIN_8,                     // rx port, rx pin
#endif
        &serial6,
        "uart6",
    },
    #endif

    #ifdef BSP_USING_UART7
    {
        UART7,                                 // uart peripheral index
        UART7_IRQn,                            // uart iqrn
        RCU_UART7, RCU_GPIOE, RCU_GPIOE,       // periph clock, tx gpio clock, rt gpio clock
#if defined SOC_SERIES_GD32F4xx
        GPIOE, GPIO_AF_8, GPIO_PIN_0,          // tx port, tx alternate, tx pin
        GPIOE, GPIO_AF_8, GPIO_PIN_1,          // rx port, rx alternate, rx pin
#else
        GPIOE, GPIO_PIN_0,                     // tx port, tx pin
        GPIOE, GPIO_PIN_1,                     // rx port, rx pin
#endif
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

#if defined SOC_SERIES_GD32F4xx
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

#elif defined SOC_SERIES_GD32H7xx
    /* connect port to USARTx_Tx */
    gpio_af_set(uart->tx_port, uart->tx_af, uart->tx_pin);

    /* connect port to USARTx_Rx */
    gpio_af_set(uart->rx_port, uart->rx_af, uart->rx_pin);

    /* configure USART Tx as alternate function push-pull */
    gpio_mode_set(uart->tx_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, uart->tx_pin);
    gpio_output_options_set(uart->tx_port, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, uart->tx_pin);

    /* configure USART Rx as alternate function push-pull */
    gpio_mode_set(uart->rx_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, uart->rx_pin);
    gpio_output_options_set(uart->rx_port, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, uart->rx_pin);

#elif defined SOC_SERIES_GD32E50x
    /* configure remap function */
    if (uart->uart_remap != 0 || uart->tx_af != 0 || uart->rx_af != 0)
    {
        rcu_periph_clock_enable(RCU_AF);
        gpio_pin_remap_config(uart->uart_remap, ENABLE);
    }

    /* connect port to USARTx_Tx */
    gpio_init(uart->tx_port, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, uart->tx_pin);

    /* connect port to USARTx_Rx */
    gpio_init(uart->rx_port, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, uart->rx_pin);

    /* configure alternate1 function */
    if (uart->tx_af != 0 || uart->rx_af != 0)
    {
        rcu_periph_clock_enable(RCU_AF);
        gpio_afio_port_config(uart->tx_af, ENABLE);
        gpio_afio_port_config(uart->rx_af, ENABLE);
    }

#else
    /* connect port to USARTx_Tx */
    gpio_init(uart->tx_port, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, uart->tx_pin);

    /* connect port to USARTx_Rx */
    gpio_init(uart->rx_port, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, uart->rx_pin);
#endif

    NVIC_SetPriority(uart->irqn, 0);
    NVIC_EnableIRQ(uart->irqn);
}

/**
  * @brief  uart configure
  * @param  serial, cfg
  * @retval None
  */
static rt_err_t gd32_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
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

/**
  * @brief  uart control
  * @param  serial, arg
  * @retval None
  */
static rt_err_t gd32_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
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
        usart_interrupt_disable(uart->uart_periph, USART_INT_RBNE);

        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irqn);
        /* enable interrupt */
        usart_interrupt_enable(uart->uart_periph, USART_INT_RBNE);
        break;
    }

    return RT_EOK;
}

/**
  * @brief  uart put char
  * @param  serial, ch
  * @retval None
  */
static int gd32_uart_putc(struct rt_serial_device *serial, char ch)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct gd32_uart *)serial->parent.user_data;

    usart_data_transmit(uart->uart_periph, ch);
    while((usart_flag_get(uart->uart_periph, USART_FLAG_TBE) == RESET));

    return RT_EOK;
}

/**
  * @brief  uart get char
  * @param  serial
  * @retval None
  */
static int gd32_uart_getc(struct rt_serial_device *serial)
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
static void GD32_UART_IRQHandler(struct rt_serial_device *serial)
{
    struct gd32_uart *uart = (struct gd32_uart *) serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);

    /* UART in mode Receiver -------------------------------------------------*/
    if ((usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_RBNE) != RESET) &&
            (usart_flag_get(uart->uart_periph, USART_FLAG_RBNE) != RESET))
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        /* Clear RXNE interrupt flag */
        usart_flag_clear(uart->uart_periph, USART_FLAG_RBNE);
    }
}

static const struct rt_uart_ops gd32_uart_ops =
{
    .configure = gd32_uart_configure,
    .control = gd32_uart_control,
    .putc = gd32_uart_putc,
    .getc = gd32_uart_getc,
    RT_NULL,
};

/**
  * @brief  uart init
  * @param  None
  * @retval None
  */
int rt_hw_usart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    int i;

    int result;

    for (i = 0; i < sizeof(uart_obj) / sizeof(uart_obj[0]); i++)
    {
        uart_obj[i].serial->ops    = &gd32_uart_ops;
        uart_obj[i].serial->config = config;

        /* register UART1 device */
        result = rt_hw_serial_register(uart_obj[i].serial,
                              uart_obj[i].device_name,
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              (void *)&uart_obj[i]);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif
