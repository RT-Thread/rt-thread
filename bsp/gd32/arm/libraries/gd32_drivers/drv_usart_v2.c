/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2024-03-19   Evlers      first implementation
 */

#include "drv_usart_v2.h"

#ifdef RT_USING_SERIAL_V2

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1) && \
    !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && \
    !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5) && \
    !defined(BSP_USING_UART6) && !defined(BSP_USING_UART7)
#error "Please define at least one UARTx"

#endif

#include <rtdevice.h>

enum {
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
#ifdef BSP_USING_UART6
    UART6_INDEX,
#endif
#ifdef BSP_USING_UART7
    UART7_INDEX,
#endif
};

static struct gd32_uart uart_obj[] = {
    #ifdef BSP_USING_UART0
    {
        "uart0",
        USART0,                                 // uart peripheral index
        USART0_IRQn,                            // uart iqrn
        RCU_USART0, RCU_GPIOA, RCU_GPIOA,       // periph clock, tx gpio clock, rt gpio clock
#if defined SOC_SERIES_GD32F4xx
        GPIOA, GPIO_AF_7, GPIO_PIN_9,           // tx port, tx alternate, tx pin
        GPIOA, GPIO_AF_7, GPIO_PIN_10,          // rx port, rx alternate, rx pin
#else
        GPIOA, GPIO_PIN_9,           // tx port, tx pin
        GPIOA, GPIO_PIN_10,          // rx port, rx pin
#endif
#ifdef BSP_UART0_RX_USING_DMA
        .dma.rx = DRV_DMA_CONFIG(1, 5, 4),
#endif
#ifdef BSP_UART0_TX_USING_DMA
        .dma.tx = DRV_DMA_CONFIG(1, 7, 4),
#endif
    },
    #endif

    #ifdef BSP_USING_UART1
    {
        "uart1",
        USART1,                                 // uart peripheral index
        USART1_IRQn,                            // uart iqrn
        RCU_USART1, RCU_GPIOA, RCU_GPIOA,       // periph clock, tx gpio clock, rt gpio clock
#if defined SOC_SERIES_GD32F4xx
        GPIOA, GPIO_AF_7, GPIO_PIN_2,           // tx port, tx alternate, tx pin
        GPIOA, GPIO_AF_7, GPIO_PIN_3,           // rx port, rx alternate, rx pin
#else
        GPIOA, GPIO_PIN_2,                      // tx port, tx pin
        GPIOA, GPIO_PIN_3,                      // rx port, rx pin
#endif
#ifdef BSP_UART1_RX_USING_DMA
        .dma.rx = DRV_DMA_CONFIG(0, 5, 4),
#endif
#ifdef BSP_UART1_TX_USING_DMA
        .dma.tx = DRV_DMA_CONFIG(0, 6, 4),
#endif
    },
    #endif

    #ifdef BSP_USING_UART2
    {
        "uart2",
        USART2,                                 // uart peripheral index
        USART2_IRQn,                            // uart iqrn
        RCU_USART2, RCU_GPIOB, RCU_GPIOB,       // periph clock, tx gpio clock, rt gpio clock
#if defined SOC_SERIES_GD32F4xx
        GPIOB, GPIO_AF_7, GPIO_PIN_10,          // tx port, tx alternate, tx pin
        GPIOB, GPIO_AF_7, GPIO_PIN_11,          // rx port, rx alternate, rx pin
#else
        GPIOB, GPIO_PIN_10,          // tx port, tx pin
        GPIOB, GPIO_PIN_11,          // rx port, rx pin
#endif
#ifdef BSP_UART2_RX_USING_DMA
        .dma.rx = DRV_DMA_CONFIG(0, 1, 4),
#endif
#ifdef BSP_UART2_TX_USING_DMA
        .dma.tx = DRV_DMA_CONFIG(0, 3, 4),
#endif
    },
    #endif

    #ifdef BSP_USING_UART3
    {
        "uart3",
        UART3,                                 // uart peripheral index
        UART3_IRQn,                            // uart iqrn
        RCU_UART3, RCU_GPIOC, RCU_GPIOC,       // periph clock, tx gpio clock, rt gpio clock
#if defined SOC_SERIES_GD32F4xx
        GPIOC, GPIO_AF_8, GPIO_PIN_10,         // tx port, tx alternate, tx pin
        GPIOC, GPIO_AF_8, GPIO_PIN_11,         // rx port, rx alternate, rx pin
#else
        GPIOC, GPIO_PIN_10,         // tx port, tx pin
        GPIOC, GPIO_PIN_11,         // rx port, rx pin
#endif
#ifdef BSP_UART3_RX_USING_DMA
        .dma.rx = DRV_DMA_CONFIG(0, 2, 4),
#endif
#ifdef BSP_UART3_TX_USING_DMA
        .dma.tx = DRV_DMA_CONFIG(0, 4, 4),
#endif
    },
    #endif

    #ifdef BSP_USING_UART4
    {
        "uart4",
        UART4,                                 // uart peripheral index
        UART4_IRQn,                            // uart iqrn
        RCU_UART4, RCU_GPIOC, RCU_GPIOD,       // periph clock, tx gpio clock, rt gpio clock
#if defined SOC_SERIES_GD32F4xx
        GPIOC, GPIO_AF_8, GPIO_PIN_12,         // tx port, tx alternate, tx pin
        GPIOD, GPIO_AF_8, GPIO_PIN_2,          // rx port, rx alternate, rx pin
#else
        GPIOC, GPIO_PIN_12,         // tx port, tx pin
        GPIOD, GPIO_PIN_2,          // rx port, rx pin
#endif
#ifdef BSP_UART4_RX_USING_DMA
        .dma.rx = DRV_DMA_CONFIG(0, 0, 4),
#endif
#ifdef BSP_UART4_TX_USING_DMA
        .dma.tx = DRV_DMA_CONFIG(0, 7, 4),
#endif
    },
    #endif

    #ifdef BSP_USING_UART5
    {
        "uart5",
        USART5,                                 // uart peripheral index
        USART5_IRQn,                            // uart iqrn
        RCU_USART5, RCU_GPIOC, RCU_GPIOC,       // periph clock, tx gpio clock, rt gpio clock
#if defined SOC_SERIES_GD32F4xx
        GPIOC, GPIO_AF_8, GPIO_PIN_6,           // tx port, tx alternate, tx pin
        GPIOC, GPIO_AF_8, GPIO_PIN_7,           // rx port, rx alternate, rx pin
#else
        GPIOC, GPIO_PIN_6,           // tx port, tx pin
        GPIOC, GPIO_PIN_7,           // rx port, rx pin
#endif
#ifdef BSP_UART5_RX_USING_DMA
        .dma.rx = DRV_DMA_CONFIG(1, 1, 5),
#endif
#ifdef BSP_UART5_TX_USING_DMA
        .dma.tx = DRV_DMA_CONFIG(1, 7, 5),
#endif
    },
    #endif

    #ifdef BSP_USING_UART6
    {
        "uart6",
        UART6,                                 // uart peripheral index
        UART6_IRQn,                            // uart iqrn
        RCU_UART6, RCU_GPIOE, RCU_GPIOE,       // periph clock, tx gpio clock, rt gpio clock
#if defined SOC_SERIES_GD32F4xx
        GPIOE, GPIO_AF_8, GPIO_PIN_7,          // tx port, tx alternate, tx pin
        GPIOE, GPIO_AF_8, GPIO_PIN_8,          // rx port, rx alternate, rx pin
#else
        GPIOE, GPIO_PIN_7,          // tx port, tx pin
        GPIOE, GPIO_PIN_8,          // rx port, rx pin
#endif
#ifdef BSP_UART6_RX_USING_DMA
        .dma.rx = DRV_DMA_CONFIG(0, 3, 5),
#endif
#ifdef BSP_UART6_TX_USING_DMA
        .dma.tx = DRV_DMA_CONFIG(0, 1, 5),
#endif
    },
    #endif

    #ifdef BSP_USING_UART7
    {
        "uart7",
        UART7,                                 // uart peripheral index
        UART7_IRQn,                            // uart iqrn
        RCU_UART7, RCU_GPIOE, RCU_GPIOE,       // periph clock, tx gpio clock, rt gpio clock
#if defined SOC_SERIES_GD32F4xx
        GPIOE, GPIO_AF_8, GPIO_PIN_0,          // tx port, tx alternate, tx pin
        GPIOE, GPIO_AF_8, GPIO_PIN_1,          // rx port, rx alternate, rx pin
#else
        GPIOE, GPIO_PIN_0,          // tx port, tx pin
        GPIOE, GPIO_PIN_1,          // rx port, rx pin
#endif
#ifdef BSP_UART7_RX_USING_DMA
        .dma.rx = DRV_DMA_CONFIG(0, 6, 5),
#endif
#ifdef BSP_UART7_TX_USING_DMA
        .dma.tx = DRV_DMA_CONFIG(0, 0, 5),
#endif
    },
    #endif
};


#ifdef RT_SERIAL_USING_DMA
static void dma_recv_isr (struct rt_serial_device *serial)
{
    struct gd32_uart *uart;
    rt_size_t recv_len, counter;
    rt_base_t level;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    recv_len = 0;
    level = rt_hw_interrupt_disable();
    counter = dma_transfer_number_get(uart->dma.rx.periph, uart->dma.rx.channel);
    if (counter <= uart->dma.last_index)
    {
        recv_len = uart->dma.last_index - counter;
    }
    else
    {
        recv_len = serial->config.rx_bufsz + uart->dma.last_index - counter;
    }
    uart->dma.last_index = counter;
    rt_hw_interrupt_enable(level);

    if (recv_len)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
    }
}
#endif

static void usart_isr (struct rt_serial_device *serial)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    if (usart_interrupt_flag_get(uart->periph, USART_INT_FLAG_RBNE) != RESET)
    {
        struct rt_serial_rx_fifo *rx_fifo;
        rx_fifo = (struct rt_serial_rx_fifo *) serial->serial_rx;
        RT_ASSERT(rx_fifo != RT_NULL);

        rt_ringbuffer_putchar(&(rx_fifo->rb), usart_data_receive(uart->periph));

        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);

        /* Clear RXNE interrupt flag */
        usart_interrupt_flag_clear(uart->periph, USART_INT_FLAG_RBNE);
    }
    else if (usart_interrupt_flag_get(uart->periph, USART_INT_FLAG_TBE) != RESET)
    {
        struct rt_serial_tx_fifo *tx_fifo;
        tx_fifo = (struct rt_serial_tx_fifo *) serial->serial_tx;
        RT_ASSERT(tx_fifo != RT_NULL);

        rt_uint8_t put_char = 0;
        if (rt_ringbuffer_getchar(&(tx_fifo->rb), &put_char))
        {
            usart_data_transmit(uart->periph, put_char);
        }
        else
        {
            usart_interrupt_disable(uart->periph, USART_INT_TBE);
            usart_interrupt_enable(uart->periph, USART_INT_TC);
        }
        usart_interrupt_flag_clear(uart->periph, USART_INT_FLAG_TBE);
    }
    else if (usart_interrupt_flag_get(uart->periph, USART_INT_FLAG_TC) != RESET)
    {
        usart_interrupt_disable(uart->periph, USART_INT_TC);

        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);

        usart_interrupt_flag_clear(uart->periph, USART_INT_FLAG_TC);
    }

#ifdef RT_SERIAL_USING_DMA
    else if (usart_interrupt_flag_get(uart->periph, USART_INT_FLAG_IDLE) != RESET)
    {
        volatile uint8_t data = (uint8_t)usart_data_receive(uart->periph);

        dma_recv_isr(serial);

        usart_interrupt_flag_clear(uart->periph, USART_INT_FLAG_IDLE);
    }
#endif
    else
    {
        if (usart_interrupt_flag_get(uart->periph, USART_INT_FLAG_ERR_ORERR) != RESET)
        {
            usart_interrupt_flag_clear(uart->periph, USART_INT_FLAG_ERR_ORERR);
        }

        if (usart_interrupt_flag_get(uart->periph, USART_INT_FLAG_ERR_NERR) != RESET)
        {
            usart_interrupt_flag_clear(uart->periph, USART_INT_FLAG_ERR_NERR);
        }

        if (usart_interrupt_flag_get(uart->periph, USART_INT_FLAG_ERR_FERR) != RESET)
        {
            usart_interrupt_flag_clear(uart->periph, USART_INT_FLAG_ERR_FERR);
        }

        if (usart_interrupt_flag_get(uart->periph, USART_INT_FLAG_RBNE_ORERR) != RESET)
        {
            usart_interrupt_flag_clear(uart->periph, USART_INT_FLAG_RBNE_ORERR);
        }

        if (usart_interrupt_flag_get(uart->periph, USART_INT_FLAG_PERR) != RESET)
        {
            usart_interrupt_flag_clear(uart->periph, USART_INT_FLAG_PERR);
        }

        if (usart_interrupt_flag_get(uart->periph, USART_INT_FLAG_CTS) != RESET)
        {
            usart_interrupt_flag_clear(uart->periph, USART_INT_FLAG_CTS);
        }

        if (usart_interrupt_flag_get(uart->periph, USART_INT_FLAG_LBD) != RESET)
        {
            usart_interrupt_flag_clear(uart->periph, USART_INT_FLAG_LBD);
        }

        if (usart_interrupt_flag_get(uart->periph, USART_INT_FLAG_EB) != RESET)
        {
            usart_interrupt_flag_clear(uart->periph, USART_INT_FLAG_EB);
        }

        if (usart_interrupt_flag_get(uart->periph, USART_INT_FLAG_RT) != RESET)
        {
            usart_interrupt_flag_clear(uart->periph, USART_INT_FLAG_RT);
        }
    }
}

#if defined(BSP_UART0_RX_USING_DMA) || \
    defined(BSP_UART1_RX_USING_DMA) || \
    defined(BSP_UART2_RX_USING_DMA) || \
    defined(BSP_UART3_RX_USING_DMA) || \
    defined(BSP_UART4_RX_USING_DMA) || \
    defined(BSP_UART5_RX_USING_DMA) || \
    defined(BSP_UART6_RX_USING_DMA) || \
    defined(BSP_UART7_RX_USING_DMA)

static void dma_rx_isr (struct rt_serial_device *serial)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    if ((dma_interrupt_flag_get(uart->dma.rx.periph, uart->dma.rx.channel, DMA_INT_FLAG_HTF) != RESET) ||
        (dma_interrupt_flag_get(uart->dma.rx.periph, uart->dma.rx.channel, DMA_INT_FLAG_FTF) != RESET))
    {
        dma_recv_isr(serial);

        /* clear dma flag */
        dma_interrupt_flag_clear(uart->dma.rx.periph, uart->dma.rx.channel, DMA_INT_FLAG_HTF);
        dma_interrupt_flag_clear(uart->dma.rx.periph, uart->dma.rx.channel, DMA_INT_FLAG_FTF);
    }
}

#endif

#if defined(BSP_UART0_TX_USING_DMA) || \
    defined(BSP_UART1_TX_USING_DMA) || \
    defined(BSP_UART2_TX_USING_DMA) || \
    defined(BSP_UART3_TX_USING_DMA) || \
    defined(BSP_UART4_TX_USING_DMA) || \
    defined(BSP_UART5_TX_USING_DMA) || \
    defined(BSP_UART6_TX_USING_DMA) || \
    defined(BSP_UART7_TX_USING_DMA)
static void dma_tx_isr (struct rt_serial_device *serial)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    if (dma_interrupt_flag_get(uart->dma.tx.periph, uart->dma.tx.channel, DMA_INT_FLAG_FTF) != RESET)
    {
        rt_size_t trans_total_index;

        /* clear dma flag */
        dma_interrupt_flag_clear(uart->dma.tx.periph, uart->dma.tx.channel, DMA_INT_FLAG_FTF);

        /* disable dma tx channel */
        dma_channel_disable(uart->dma.tx.periph, uart->dma.tx.channel);

        trans_total_index = dma_transfer_number_get(uart->dma.tx.periph, uart->dma.tx.channel);

        if (trans_total_index == 0)
        {
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DMADONE);
        }
    }
}
#endif

#if defined(BSP_USING_UART0)
void USART0_IRQHandler (void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&uart_obj[UART0_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)
void USART1_IRQHandler (void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&uart_obj[UART1_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
void USART2_IRQHandler (void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&uart_obj[UART2_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
void UART3_IRQHandler (void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&uart_obj[UART3_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
void UART4_IRQHandler (void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&uart_obj[UART4_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
void USART5_IRQHandler (void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&uart_obj[UART5_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)
void UART6_IRQHandler (void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&uart_obj[UART6_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_UART7)
void UART7_IRQHandler (void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&uart_obj[UART7_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART7 */

#ifdef BSP_UART0_RX_USING_DMA
void DMA1_Channel5_IRQHandler (void)
{
    dma_rx_isr(&uart_obj[UART0_INDEX].serial);
}
#endif

#ifdef BSP_UART0_TX_USING_DMA
void DMA1_Channel7_IRQHandler (void)
{
    dma_tx_isr(&uart_obj[UART0_INDEX].serial);
}
#endif

#ifdef BSP_UART1_RX_USING_DMA
void DMA0_Channel5_IRQHandler (void)
{
    dma_rx_isr(&uart_obj[UART1_INDEX].serial);
}
#endif

#ifdef BSP_UART1_TX_USING_DMA
void DMA0_Channel6_IRQHandler (void)
{
    dma_tx_isr(&uart_obj[UART1_INDEX].serial);
}
#endif

#ifdef BSP_UART2_RX_USING_DMA
void DMA0_Channel1_IRQHandler (void)
{
    dma_rx_isr(&uart_obj[UART2_INDEX].serial);
}
#endif

#ifdef BSP_UART2_TX_USING_DMA
void DMA0_Channel3_IRQHandler (void)
{
    dma_tx_isr(&uart_obj[UART2_INDEX].serial);
}
#endif

#ifdef BSP_UART3_RX_USING_DMA
void DMA0_Channel2_IRQHandler (void)
{
    dma_rx_isr(&uart_obj[UART3_INDEX].serial);
}
#endif

#ifdef BSP_UART3_TX_USING_DMA
void DMA0_Channel4_IRQHandler (void)
{
    dma_tx_isr(&uart_obj[UART3_INDEX].serial);
}
#endif

#ifdef BSP_UART4_RX_USING_DMA
void DMA0_Channel0_IRQHandler (void)
{
    dma_rx_isr(&uart_obj[UART4_INDEX].serial);
}
#endif

#ifdef BSP_UART4_TX_USING_DMA
void DMA0_Channel7_IRQHandler (void)
{
    dma_tx_isr(&uart_obj[UART4_INDEX].serial);
}
#endif

#ifdef BSP_UART5_RX_USING_DMA
void DMA1_Channel1_IRQHandler (void)
{
    dma_rx_isr(&uart_obj[UART5_INDEX].serial);
}
#endif

#ifdef BSP_UART5_TX_USING_DMA
void DMA1_Channel7_IRQHandler (void)
{
    dma_tx_isr(&uart_obj[UART5_INDEX].serial);
}
#endif

#ifdef BSP_UART6_RX_USING_DMA
void DMA0_Channel3_IRQHandler (void)
{
    dma_rx_isr(&uart_obj[UART6_INDEX].serial);
}
#endif

#ifdef BSP_UART6_TX_USING_DMA
void DMA0_Channel1_IRQHandler (void)
{
    dma_tx_isr(&uart_obj[UART6_INDEX].serial);
}
#endif

#ifdef BSP_UART7_RX_USING_DMA
void DMA0_Channel6_IRQHandler (void)
{
    dma_rx_isr(&uart_obj[UART7_INDEX].serial);
}
#endif

#ifdef BSP_UART7_TX_USING_DMA
void DMA0_Channel0_IRQHandler (void)
{
    dma_tx_isr(&uart_obj[UART7_INDEX].serial);
}
#endif

/**
* @brief UART MSP Initialization
*        This function configures the hardware resources used in this example:
*           - Peripheral's clock enable
*           - Peripheral's GPIO Configuration
*           - NVIC configuration for UART interrupt request enable
* @param huart: UART handle pointer
* @retval None
*/
void gd32_uart_gpio_init (struct gd32_uart *uart)
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
static rt_err_t gd32_uart_configure (struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

#ifdef RT_SERIAL_USING_DMA
    uart->dma.last_index = serial->config.rx_bufsz;
#endif

    gd32_uart_gpio_init(uart);

    usart_baudrate_set(uart->periph, cfg->baud_rate);

    switch (cfg->data_bits)
    {
    case DATA_BITS_9:
        usart_word_length_set(uart->periph, USART_WL_9BIT);
        break;

    default:
        usart_word_length_set(uart->periph, USART_WL_8BIT);
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_2:
        usart_stop_bit_set(uart->periph, USART_STB_2BIT);
        break;
    default:
        usart_stop_bit_set(uart->periph, USART_STB_1BIT);
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_ODD:
        usart_parity_config(uart->periph, USART_PM_ODD);
        break;
    case PARITY_EVEN:
        usart_parity_config(uart->periph, USART_PM_EVEN);
        break;
    default:
        usart_parity_config(uart->periph, USART_PM_NONE);
        break;
    }

    usart_receive_config(uart->periph, USART_RECEIVE_ENABLE);
    usart_transmit_config(uart->periph, USART_TRANSMIT_ENABLE);
    usart_enable(uart->periph);

    return RT_EOK;
}

#ifdef RT_SERIAL_USING_DMA
static void _uart_dma_receive (struct gd32_uart *uart, rt_uint8_t *buffer, rt_uint32_t size)
{
    dma_single_data_parameter_struct dma_init_struct = { 0 };

    /* clear all the interrupt flags */
    dma_flag_clear(uart->dma.rx.periph, uart->dma.rx.channel, DMA_FLAG_FEE);
    dma_flag_clear(uart->dma.rx.periph, uart->dma.rx.channel, DMA_FLAG_SDE);
    dma_flag_clear(uart->dma.rx.periph, uart->dma.rx.channel, DMA_FLAG_TAE);
    dma_flag_clear(uart->dma.rx.periph, uart->dma.rx.channel, DMA_FLAG_HTF);
    dma_flag_clear(uart->dma.rx.periph, uart->dma.rx.channel, DMA_FLAG_FTF);
    dma_channel_disable(uart->dma.rx.periph, uart->dma.rx.channel);
    dma_deinit(uart->dma.rx.periph, uart->dma.rx.channel);

    /* configure receive DMA */
    rcu_periph_clock_enable(uart->dma.rx.rcu);
    dma_deinit(uart->dma.rx.periph, uart->dma.rx.channel);

    dma_init_struct.number              = size;
    dma_init_struct.memory0_addr        = (uint32_t)buffer;
    dma_init_struct.periph_addr         = (uint32_t)&USART_DATA(uart->periph);
    dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
    dma_init_struct.periph_inc          = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.memory_inc          = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.circular_mode       = DMA_CIRCULAR_MODE_ENABLE;
    dma_init_struct.direction           = DMA_PERIPH_TO_MEMORY;
    dma_init_struct.priority            = DMA_PRIORITY_HIGH;
    dma_single_data_mode_init(uart->dma.rx.periph, uart->dma.rx.channel, &dma_init_struct);
    dma_channel_subperipheral_select(uart->dma.rx.periph, uart->dma.rx.channel, uart->dma.rx.subperiph);

    /* enable transmit complete interrupt */
    nvic_irq_enable(uart->dma.rx.irq, 2, 0);
    dma_interrupt_enable(uart->dma.rx.periph, uart->dma.rx.channel, DMA_CHXCTL_HTFIE);
    dma_interrupt_enable(uart->dma.rx.periph, uart->dma.rx.channel, DMA_CHXCTL_FTFIE);

    /* enable dma channel */
    dma_channel_enable(uart->dma.rx.periph, uart->dma.rx.channel);

    /* enable usart idle interrupt */
    usart_interrupt_enable(uart->periph, USART_INT_IDLE);

    /* enable dma receive */
    usart_dma_receive_config(uart->periph, USART_RECEIVE_DMA_ENABLE);
}

static void _uart_dma_transmit (struct gd32_uart *uart, rt_uint8_t *buffer, rt_uint32_t size)
{
    /* Set the data length and data pointer */
    DMA_CHM0ADDR(uart->dma.tx.periph, uart->dma.tx.channel) = (uint32_t)buffer;
    DMA_CHCNT(uart->dma.tx.periph, uart->dma.tx.channel) = size;

    /* enable dma transmit */
    usart_dma_transmit_config(uart->periph, USART_TRANSMIT_DMA_ENABLE);

    /* enable dma channel */
    dma_channel_enable(uart->dma.tx.periph, uart->dma.tx.channel);
}

static void gd32_dma_config (struct rt_serial_device *serial, rt_ubase_t flag)
{
    struct gd32_uart *uart;
    struct rt_serial_rx_fifo *rx_fifo;
    dma_single_data_parameter_struct dma_init_struct = { 0 };

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    RT_ASSERT(flag == RT_DEVICE_FLAG_DMA_TX || flag == RT_DEVICE_FLAG_DMA_RX);

    /* enable rx dma */
    if (flag == RT_DEVICE_FLAG_DMA_TX)
    {
        /* clear all the interrupt flags */
        dma_flag_clear(uart->dma.tx.periph, uart->dma.tx.channel, DMA_FLAG_FEE);
        dma_flag_clear(uart->dma.tx.periph, uart->dma.tx.channel, DMA_FLAG_SDE);
        dma_flag_clear(uart->dma.tx.periph, uart->dma.tx.channel, DMA_FLAG_TAE);
        dma_flag_clear(uart->dma.tx.periph, uart->dma.tx.channel, DMA_FLAG_HTF);
        dma_flag_clear(uart->dma.tx.periph, uart->dma.tx.channel, DMA_FLAG_FTF);
        dma_channel_disable(uart->dma.tx.periph, uart->dma.tx.channel);
        dma_deinit(uart->dma.tx.periph, uart->dma.tx.channel);

        /* configure receive DMA */
        rcu_periph_clock_enable(uart->dma.tx.rcu);
        dma_deinit(uart->dma.tx.periph, uart->dma.tx.channel);

        dma_init_struct.periph_addr         = (uint32_t)&USART_DATA(uart->periph);
        dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
        dma_init_struct.periph_inc          = DMA_PERIPH_INCREASE_DISABLE;
        dma_init_struct.memory_inc          = DMA_MEMORY_INCREASE_ENABLE;
        dma_init_struct.circular_mode       = DMA_CIRCULAR_MODE_DISABLE;
        dma_init_struct.direction           = DMA_MEMORY_TO_PERIPH;
        dma_init_struct.priority            = DMA_PRIORITY_HIGH;
        dma_single_data_mode_init(uart->dma.tx.periph, uart->dma.tx.channel, &dma_init_struct);
        dma_channel_subperipheral_select(uart->dma.tx.periph, uart->dma.tx.channel, uart->dma.tx.subperiph);

        /* enable tx dma interrupt */
        nvic_irq_enable(uart->dma.tx.irq, 2, 0);

        /* enable transmit complete interrupt */
        dma_interrupt_enable(uart->dma.tx.periph, uart->dma.tx.channel, DMA_CHXCTL_FTFIE);
    }

    /* enable rx dma */
    if (flag == RT_DEVICE_FLAG_DMA_RX)
    {
        rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
        /* start dma transfer */
        _uart_dma_receive(uart, rx_fifo->buffer, serial->config.rx_bufsz);
    }
}

#endif

/**
  * @brief  uart control
  * @param  serial, arg
  * @retval None
  */
static rt_err_t gd32_uart_control (struct rt_serial_device *serial, int cmd, void *arg)
{
    struct gd32_uart *uart;

    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    if (ctrl_arg & (RT_DEVICE_FLAG_RX_BLOCKING | RT_DEVICE_FLAG_RX_NON_BLOCKING))
    {
        if (uart->uart_dma_flag & RT_DEVICE_FLAG_DMA_RX)
            ctrl_arg = RT_DEVICE_FLAG_DMA_RX;
        else
            ctrl_arg = RT_DEVICE_FLAG_INT_RX;
    }
    else if (ctrl_arg & (RT_DEVICE_FLAG_TX_BLOCKING | RT_DEVICE_FLAG_TX_NON_BLOCKING))
    {
        if (uart->uart_dma_flag & RT_DEVICE_FLAG_DMA_TX)
            ctrl_arg = RT_DEVICE_FLAG_DMA_TX;
        else
            ctrl_arg = RT_DEVICE_FLAG_INT_TX;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->irqn);

        /* disable interrupt */
        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX)
        {
            usart_interrupt_disable(uart->periph, USART_INT_RBNE);
        }
        else if (ctrl_arg == RT_DEVICE_FLAG_INT_TX)
        {
            usart_interrupt_disable(uart->periph, USART_INT_TBE);
        }

#ifdef RT_SERIAL_USING_DMA
        /* disable DMA */
        else if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX)
        {
            usart_interrupt_disable(uart->periph, USART_INT_RBNE);
            NVIC_DisableIRQ(uart->dma.rx.irq);
            dma_deinit(uart->dma.rx.periph, uart->dma.rx.channel);
        }
        else if(ctrl_arg == RT_DEVICE_FLAG_DMA_TX)
        {
            usart_interrupt_disable(uart->periph, USART_INT_TBE);
            NVIC_DisableIRQ(uart->dma.tx.irq);
            dma_deinit(uart->dma.tx.periph, uart->dma.tx.channel);
        }
#endif
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irqn);

        /* enable interrupt */
        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX)
        {
            usart_interrupt_enable(uart->periph, USART_INT_RBNE);
        }
        else if (ctrl_arg == RT_DEVICE_FLAG_INT_TX)
        {
            usart_interrupt_enable(uart->periph, USART_INT_TBE);
        }
        break;

    case RT_DEVICE_CTRL_CONFIG:
        if(ctrl_arg & (RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX))
        {
#ifdef RT_SERIAL_USING_DMA
        gd32_dma_config(serial, ctrl_arg);
#endif
        }
        else
        {
            gd32_uart_control(serial, RT_DEVICE_CTRL_SET_INT, (void *)ctrl_arg);
        }
        break;

    case RT_DEVICE_CHECK_OPTMODE:
        if(ctrl_arg & RT_DEVICE_FLAG_DMA_TX)
            return RT_SERIAL_TX_BLOCKING_NO_BUFFER;
        else
            return RT_SERIAL_TX_BLOCKING_BUFFER;

    case RT_DEVICE_CTRL_CLOSE:
        usart_deinit(uart->periph);
        break;
    }

    return RT_EOK;
}

/**
  * @brief  uart put char
  * @param  serial, ch
  * @retval None
  */
static int gd32_uart_putc (struct rt_serial_device *serial, char ch)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    usart_data_transmit(uart->periph, ch);
    while((usart_flag_get(uart->periph, USART_FLAG_TBE) == RESET));

    return RT_EOK;
}

/**
  * @brief  uart get char
  * @param  serial
  * @retval None
  */
static int gd32_uart_getc (struct rt_serial_device *serial)
{
    int ch;
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    ch = -1;
    if (usart_flag_get(uart->periph, USART_FLAG_RBNE) != RESET)
        ch = usart_data_receive(uart->periph);
    return ch;
}

static rt_ssize_t gd32_transmit (struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, rt_uint32_t tx_flag)
{
    struct gd32_uart *uart;

    RT_ASSERT(buf != RT_NULL);
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    if (size == 0)
    {
        return 0;
    }

    if (uart->uart_dma_flag & RT_DEVICE_FLAG_DMA_TX)
    {
#ifdef RT_SERIAL_USING_DMA
        _uart_dma_transmit(uart, buf, size);
        return size;
#endif
    }

    gd32_uart_control(serial, RT_DEVICE_CTRL_SET_INT, (void *)tx_flag);
    return size;
}

static const struct rt_uart_ops gd32_uart_ops =
{
    .configure = gd32_uart_configure,
    .control = gd32_uart_control,
    .putc = gd32_uart_putc,
    .getc = gd32_uart_getc,
    .transmit = gd32_transmit,
};

static void gd32_uart_get_config (void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef BSP_USING_UART0
    uart_obj[UART0_INDEX].uart_dma_flag = 0;
    uart_obj[UART0_INDEX].serial.config = config;
    uart_obj[UART0_INDEX].serial.config.rx_bufsz = BSP_UART0_RX_BUFSIZE;
    uart_obj[UART0_INDEX].serial.config.tx_bufsz = BSP_UART0_TX_BUFSIZE;
#ifdef BSP_UART0_RX_USING_DMA
    uart_obj[UART0_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_UART0_TX_USING_DMA
    uart_obj[UART0_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif
#endif

#ifdef BSP_USING_UART1
    uart_obj[UART1_INDEX].uart_dma_flag = 0;
    uart_obj[UART1_INDEX].serial.config = config;
    uart_obj[UART1_INDEX].serial.config.rx_bufsz = BSP_UART1_RX_BUFSIZE;
    uart_obj[UART1_INDEX].serial.config.tx_bufsz = BSP_UART1_TX_BUFSIZE;
#ifdef BSP_UART1_RX_USING_DMA
    uart_obj[UART1_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_UART1_TX_USING_DMA
    uart_obj[UART1_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif
#endif

#ifdef BSP_USING_UART2
    uart_obj[UART2_INDEX].uart_dma_flag = 0;
    uart_obj[UART2_INDEX].serial.config = config;
    uart_obj[UART2_INDEX].serial.config.rx_bufsz = BSP_UART2_RX_BUFSIZE;
    uart_obj[UART2_INDEX].serial.config.tx_bufsz = BSP_UART2_TX_BUFSIZE;
#ifdef BSP_UART2_RX_USING_DMA
    uart_obj[UART2_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_UART2_TX_USING_DMA
    uart_obj[UART2_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif
#endif

#ifdef BSP_USING_UART3
    uart_obj[UART3_INDEX].uart_dma_flag = 0;
    uart_obj[UART3_INDEX].serial.config = config;
    uart_obj[UART3_INDEX].serial.config.rx_bufsz = BSP_UART3_RX_BUFSIZE;
    uart_obj[UART3_INDEX].serial.config.tx_bufsz = BSP_UART3_TX_BUFSIZE;
#ifdef BSP_UART3_RX_USING_DMA
    uart_obj[UART3_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_UART3_TX_USING_DMA
    uart_obj[UART3_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif
#endif

#ifdef BSP_USING_UART4
    uart_obj[UART4_INDEX].uart_dma_flag = 0;
    uart_obj[UART4_INDEX].serial.config = config;
    uart_obj[UART4_INDEX].serial.config.rx_bufsz = BSP_UART4_RX_BUFSIZE;
    uart_obj[UART4_INDEX].serial.config.tx_bufsz = BSP_UART4_TX_BUFSIZE;
#ifdef BSP_UART4_RX_USING_DMA
    uart_obj[UART4_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_UART4_TX_USING_DMA
    uart_obj[UART4_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif
#endif

#ifdef BSP_USING_UART5
    uart_obj[UART5_INDEX].uart_dma_flag = 0;
    uart_obj[UART5_INDEX].serial.config = config;
    uart_obj[UART5_INDEX].serial.config.rx_bufsz = BSP_UART5_RX_BUFSIZE;
    uart_obj[UART5_INDEX].serial.config.tx_bufsz = BSP_UART5_TX_BUFSIZE;
#ifdef BSP_UART5_RX_USING_DMA
    uart_obj[UART5_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_UART5_TX_USING_DMA
    uart_obj[UART5_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif
#endif

#ifdef BSP_USING_UART6
    uart_obj[UART6_INDEX].uart_dma_flag = 0;
    uart_obj[UART6_INDEX].serial.config = config;
    uart_obj[UART6_INDEX].serial.config.rx_bufsz = BSP_UART6_RX_BUFSIZE;
    uart_obj[UART6_INDEX].serial.config.tx_bufsz = BSP_UART6_TX_BUFSIZE;
#ifdef BSP_UART6_RX_USING_DMA
    uart_obj[UART6_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_UART6_TX_USING_DMA
    uart_obj[UART6_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif
#endif

#ifdef BSP_USING_UART7
    uart_obj[UART7_INDEX].uart_dma_flag = 0;
    uart_obj[UART7_INDEX].serial.config = config;
    uart_obj[UART7_INDEX].serial.config.rx_bufsz = BSP_UART7_RX_BUFSIZE;
    uart_obj[UART7_INDEX].serial.config.tx_bufsz = BSP_UART7_TX_BUFSIZE;
#ifdef BSP_UART7_RX_USING_DMA
    uart_obj[UART7_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
#endif
#ifdef BSP_UART7_TX_USING_DMA
    uart_obj[UART7_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#endif
#endif
}

/**
  * @brief  uart init
  * @param  None
  * @retval None
  */
int rt_hw_usart_init (void)
{
    int i;
    int result;

    gd32_uart_get_config();

    for (i = 0; i < sizeof(uart_obj) / sizeof(uart_obj[0]); i++)
    {
        uart_obj[i].serial.ops    = &gd32_uart_ops;

        /* register UART1 device */
        result = rt_hw_serial_register(&uart_obj[i].serial,
                              uart_obj[i].device_name,
                              RT_DEVICE_FLAG_RDWR |
                              RT_DEVICE_FLAG_INT_RX |
                              uart_obj[i].uart_dma_flag,
                              (void *)&uart_obj[i]);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif
