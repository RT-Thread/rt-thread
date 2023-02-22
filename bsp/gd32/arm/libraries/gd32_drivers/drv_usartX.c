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
 * 2022-06-09     THEWON       first version for serialX
 */

#include <gd32f4xx.h>
#include <drv_usartX.h>
#include <board.h>

#ifdef RT_USING_SERIAL

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1) && \
    !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && \
    !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5) && \
    !defined(BSP_USING_UART6) && !defined(BSP_USING_UART7)
#error "Please define at least one UARTx"

#endif

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
#ifdef BSP_USING_UART6
    UART6_INDEX,
#endif
#ifdef BSP_USING_UART7
    UART7_INDEX,
#endif
};

/* GD32 uart driver */

static void uart_isr(struct rt_serial_device *serial);

#ifdef RT_SERIAL_USING_DMA
static void DMA_RX_Configuration(struct rt_serial_device *serial);
static void DMA_TX_Configuration(struct rt_serial_device *serial);
#endif

static struct gd32_uart uarts[] = {
    #ifdef BSP_USING_UART0
    {
        .uart_periph = USART0,                                 // uart peripheral index
        .uart_config = {
            .name = "uart0",
            .irqn = USART0_IRQn,                            // uart iqrn
            RCU_USART0, RCU_GPIOA, RCU_GPIOA,       // periph clock, tx gpio clock, rt gpio clock
            GPIOA, GPIO_AF_7, GPIO_PIN_9,           // tx port, tx alternate, tx pin
            GPIOA, GPIO_AF_7, GPIO_PIN_10,          // rx port, rx alternate, rx pin
        },
#ifdef RT_SERIAL_USING_DMA
        .dmaTxing = RT_FALSE,
        .dma_rx = {
            .dma_periph = DMA1,
            .dma_channel = DMA_CH2,
            .dma_subperi = DMA_SUBPERI4,
            .dma_irq = DMA1_Channel2_IRQn,
        },
        .dma_tx = {
            .dma_periph = DMA1,
            .dma_channel = DMA_CH7,
            .dma_subperi = DMA_SUBPERI4,
            .dma_irq = DMA1_Channel7_IRQn,
        },
#endif
    },
    #endif

    #ifdef BSP_USING_UART1
    {
        .uart_periph = USART1,                                 // uart peripheral index
        .uart_config = {
            .name = "uart1",
            .irqn = USART1_IRQn,                            // uart iqrn
            RCU_USART1, RCU_GPIOA, RCU_GPIOA,       // periph clock, tx gpio clock, rt gpio clock
            GPIOA, GPIO_AF_7, GPIO_PIN_2,           // tx port, tx alternate, tx pin
            GPIOA, GPIO_AF_7, GPIO_PIN_3,           // rx port, rx alternate, rx pin
        }
    },
    #endif

    #ifdef BSP_USING_UART2
    {
        .uart_periph = USART2,                                 // uart peripheral index
        .uart_config = {
            .name = "uart2",
            .irqn = USART2_IRQn,                            // uart iqrn
            RCU_USART2, RCU_GPIOB, RCU_GPIOB,       // periph clock, tx gpio clock, rt gpio clock
            GPIOB, GPIO_AF_7, GPIO_PIN_10,          // tx port, tx alternate, tx pin
            GPIOB, GPIO_AF_7, GPIO_PIN_11,          // rx port, rx alternate, rx pin
        }
    },
    #endif

    #ifdef BSP_USING_UART3
    {
        .uart_periph = UART3,                                 // uart peripheral index
        .uart_config = {
            .name = "uart3",
            .irqn = UART3_IRQn,                            // uart iqrn
            RCU_UART3, RCU_GPIOC, RCU_GPIOC,       // periph clock, tx gpio clock, rt gpio clock
            GPIOC, GPIO_AF_8, GPIO_PIN_10,         // tx port, tx alternate, tx pin
            GPIOC, GPIO_AF_8, GPIO_PIN_11,         // rx port, rx alternate, rx pin
        }
    },
    #endif

    #ifdef BSP_USING_UART4
    {
        .uart_periph = UART4,                                 // uart peripheral index
        .uart_config = {
            .name = "uart4",
            .irqn = UART4_IRQn,                            // uart iqrn
            RCU_UART4, RCU_GPIOC, RCU_GPIOD,       // periph clock, tx gpio clock, rt gpio clock
            GPIOC, GPIO_AF_8, GPIO_PIN_12,         // tx port, tx alternate, tx pin
            GPIOD, GPIO_AF_8, GPIO_PIN_2,          // rx port, rx alternate, rx pin
        }
    },
    #endif

    #ifdef BSP_USING_UART5
    {
        .uart_periph = USART5,                                 // uart peripheral index
        .uart_config = {
            .name = "uart5",
            .irqn = USART5_IRQn,                            // uart iqrn
            RCU_USART5, RCU_GPIOC, RCU_GPIOC,       // periph clock, tx gpio clock, rt gpio clock
            GPIOC, GPIO_AF_8, GPIO_PIN_6,           // tx port, tx alternate, tx pin
            GPIOC, GPIO_AF_8, GPIO_PIN_7,           // rx port, rx alternate, rx pin
        }
    },
    #endif

    #ifdef BSP_USING_UART6
    {
        .uart_periph = UART6,                                 // uart peripheral index
        .uart_config = {
            .name = "uart6",
            .irqn = UART6_IRQn,                            // uart iqrn
            RCU_UART6, RCU_GPIOE, RCU_GPIOE,       // periph clock, tx gpio clock, rt gpio clock
            GPIOE, GPIO_AF_8, GPIO_PIN_7,          // tx port, tx alternate, tx pin
            GPIOE, GPIO_AF_8, GPIO_PIN_8,          // rx port, rx alternate, rx pin
        }
    },
    #endif

    #ifdef BSP_USING_UART7
    {
        .uart_periph = UART7,                                 // uart peripheral index
        .uart_config = {
            .name = "uart7",
            .irqn = UART7_IRQn,                            // uart iqrn
            RCU_UART7, RCU_GPIOE, RCU_GPIOE,       // periph clock, tx gpio clock, rt gpio clock
            GPIOE, GPIO_AF_8, GPIO_PIN_0,          // tx port, tx alternate, tx pin
            GPIOE, GPIO_AF_8, GPIO_PIN_1,          // rx port, rx alternate, rx pin
        }
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
    rcu_periph_clock_enable(uart->uart_config.tx_gpio_clk);
    rcu_periph_clock_enable(uart->uart_config.rx_gpio_clk);
    rcu_periph_clock_enable(uart->uart_config.per_clk);

    /* connect port to USARTx_Tx */
    gpio_af_set(uart->uart_config.tx_port, uart->uart_config.tx_af, uart->uart_config.tx_pin);

    /* connect port to USARTx_Rx */
    gpio_af_set(uart->uart_config.rx_port, uart->uart_config.rx_af, uart->uart_config.rx_pin);

    /* configure USART Tx as alternate function push-pull */
    gpio_mode_set(uart->uart_config.tx_port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, uart->uart_config.tx_pin);
    gpio_output_options_set(uart->uart_config.tx_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, uart->uart_config.tx_pin);

    /* configure USART Rx as alternate function push-pull */
    gpio_mode_set(uart->uart_config.rx_port, GPIO_MODE_AF, GPIO_PUPD_NONE, uart->uart_config.rx_pin);
    gpio_output_options_set(uart->uart_config.rx_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, uart->uart_config.rx_pin);
}

static rt_err_t gd32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = rt_container_of(serial, struct gd32_uart, serial);

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

    return RT_EOK;
}

static rt_err_t gd32_init(struct rt_serial_device *serial)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct gd32_uart, serial);

    gd32_uart_gpio_init(uart);

    if (gd32_configure(serial, &serial->config) != RT_EOK)
    {
        return -RT_ERROR;
    }

    usart_receive_config(uart->uart_periph, USART_RECEIVE_ENABLE);
    usart_transmit_config(uart->uart_periph, USART_TRANSMIT_ENABLE);

    return RT_EOK;
}

static rt_err_t gd32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct gd32_uart *uart;
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    switch (cmd) {
    case RT_DEVICE_CTRL_OPEN:
        usart_interrupt_disable(uart->uart_periph, USART_INT_TBE);
        usart_interrupt_disable(uart->uart_periph, USART_INT_TC);
        usart_flag_clear(uart->uart_periph, USART_FLAG_RBNE);
        usart_flag_clear(uart->uart_periph, USART_FLAG_TBE);
        usart_flag_clear(uart->uart_periph, USART_FLAG_TC);
        /* enable rx irq */
        NVIC_SetPriority(uart->uart_config.irqn, 0);
        NVIC_EnableIRQ(uart->uart_config.irqn);
        usart_enable(uart->uart_periph);
#ifdef RT_SERIAL_USING_DMA
        uart->dmaTxing = RT_FALSE;
#endif
    break;
    case RT_DEVICE_CTRL_CLOSE:
        NVIC_DisableIRQ(uart->uart_config.irqn);
        usart_interrupt_disable(uart->uart_periph, USART_INT_RBNE);
        usart_interrupt_disable(uart->uart_periph, USART_INT_TBE);
        usart_interrupt_disable(uart->uart_periph, USART_INT_IDLE);
        usart_interrupt_disable(uart->uart_periph, USART_INT_TC);
        usart_disable(uart->uart_periph);
        usart_deinit(uart->uart_periph);
#ifdef RT_SERIAL_USING_DMA
        NVIC_DisableIRQ(uart->dma_rx.dma_irq);
        dma_interrupt_disable(uart->dma_rx.dma_periph, uart->dma_rx.dma_channel, DMA_CHXCTL_HTFIE);
        dma_interrupt_disable(uart->dma_rx.dma_periph, uart->dma_rx.dma_channel, DMA_CHXCTL_FTFIE);
        dma_channel_disable(uart->dma_rx.dma_periph, uart->dma_rx.dma_channel);
        dma_deinit(uart->dma_rx.dma_periph, uart->dma_rx.dma_channel);

        NVIC_DisableIRQ(uart->dma_tx.dma_irq);
        dma_interrupt_disable(uart->dma_tx.dma_periph, uart->dma_tx.dma_channel, DMA_CHXCTL_FTFIE);
        dma_channel_disable(uart->dma_tx.dma_periph, uart->dma_tx.dma_channel);
        dma_deinit(uart->dma_tx.dma_periph, uart->dma_tx.dma_channel);
#endif
    break;
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable interrupt */
        if (ctrl_arg & RT_DEVICE_FLAG_INT_RX) {
            usart_interrupt_disable(uart->uart_periph, USART_INT_RBNE);
        }
#ifdef RT_SERIAL_USING_DMA
        /* disable DMA */
        if (ctrl_arg & RT_DEVICE_FLAG_DMA_RX) {
            NVIC_DisableIRQ(uart->dma_rx.dma_irq);
            dma_interrupt_disable(uart->dma_rx.dma_periph, uart->dma_rx.dma_channel, DMA_CHXCTL_HTFIE);
            dma_interrupt_disable(uart->dma_rx.dma_periph, uart->dma_rx.dma_channel, DMA_CHXCTL_FTFIE);
        }
        if(ctrl_arg & RT_DEVICE_FLAG_DMA_TX) {
            NVIC_DisableIRQ(uart->dma_tx.dma_irq);
            dma_interrupt_disable(uart->dma_tx.dma_periph, uart->dma_tx.dma_channel, DMA_CHXCTL_FTFIE);
        }
#endif
    break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable interrupt */
        if (ctrl_arg & RT_DEVICE_FLAG_INT_RX) {
            usart_interrupt_enable(uart->uart_periph, USART_INT_RBNE);
        }
    break;
    /* USART config */
    case RT_DEVICE_CTRL_CONFIG :
#ifdef RT_SERIAL_USING_DMA
        if (ctrl_arg & RT_DEVICE_FLAG_DMA_RX) {
            DMA_RX_Configuration(serial);
        } else if (ctrl_arg & RT_DEVICE_FLAG_DMA_TX) {
            DMA_TX_Configuration(serial);
        }
#endif
    break;
    default :
    break;
    }

    return RT_EOK;
}

static int gd32_putc(struct rt_serial_device *serial, char ch)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    while((usart_flag_get(uart->uart_periph, USART_FLAG_TBE) == RESET));
    usart_data_transmit(uart->uart_periph, ch);

    return 1;
}

static int gd32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    ch = -1;
    if (usart_flag_get(uart->uart_periph, USART_FLAG_RBNE) != RESET) {
        ch = usart_data_receive(uart->uart_periph);
    }
    return ch;
}

static int gd32_flush(struct rt_serial_device *serial)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct gd32_uart, serial);
    while (!(usart_flag_get(uart->uart_periph, USART_FLAG_TBE) == SET && usart_flag_get(uart->uart_periph, USART_FLAG_TC) == SET));

    return 1;
}

static void gd32_start_tx(struct rt_serial_device *serial)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct gd32_uart, serial);
    usart_interrupt_enable(uart->uart_periph, USART_INT_TBE);
}

static void gd32_stop_tx(struct rt_serial_device *serial)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct gd32_uart, serial);
    usart_interrupt_disable(uart->uart_periph, USART_INT_TBE);
}

#ifdef RT_SERIAL_USING_DMA
static rt_bool_t gd32_is_dma_txing(struct rt_serial_device *serial)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct gd32_uart, serial);

    return uart->dmaTxing;  //RT_FALSE;
}

static void gd32_start_dma_tx(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct gd32_uart, serial);

    // TODO: 启用 DMA 发送
    DMA_CHM0ADDR(uart->dma_tx.dma_periph, uart->dma_tx.dma_channel) = (uint32_t)(buf);
    DMA_CHCNT(uart->dma_tx.dma_periph, uart->dma_tx.dma_channel) = (uint32_t)(size);
    dma_channel_enable(uart->dma_tx.dma_periph, uart->dma_tx.dma_channel);

    uart->dmaTxing = RT_TRUE;
}

static void gd32_stop_dma_tx(struct rt_serial_device *serial)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct gd32_uart, serial);

    // TODO: 禁用 DMA 发送
    dma_channel_disable(uart->dma_tx.dma_periph, uart->dma_tx.dma_channel);
    uart->dmaTxing = RT_FALSE;
}
#endif

static void gd32_enable_interrupt(struct rt_serial_device *serial)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct gd32_uart, serial);

    NVIC_EnableIRQ(uart->uart_config.irqn);
}

static void gd32_disable_interrupt(struct rt_serial_device *serial)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct gd32_uart, serial);

    NVIC_DisableIRQ(uart->uart_config.irqn);
}

#ifdef RT_SERIAL_USING_DMA
/**
 * DMA receive done process. This need add to DMA receive done ISR.
 *
 * @param serial serial device
 */
static void dma_rx_done_isr(struct rt_serial_device *serial)
{
    struct gd32_uart *uart;
    rt_size_t dma_cnt;

    uart = rt_container_of(serial, struct gd32_uart, serial);

    dma_cnt = RT_SERIAL_DMA_BUFSZ - DMA_CHCNT(uart->dma_rx.dma_periph, uart->dma_rx.dma_channel);

    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (dma_cnt << 8));

    dma_interrupt_flag_clear(uart->dma_rx.dma_periph, uart->dma_rx.dma_channel, DMA_INT_FLAG_HTF);
    dma_interrupt_flag_clear(uart->dma_rx.dma_periph, uart->dma_rx.dma_channel, DMA_INT_FLAG_FTF);
}
/**
 * DMA transmit done process. This need add to DMA transmit done ISR.
 *
 * @param serial serial device
 */
static void dma_tx_done_isr(struct rt_serial_device *serial)
{
    struct gd32_uart *uart;
    rt_size_t dma_cnt;

    uart = rt_container_of(serial, struct gd32_uart, serial);

    dma_cnt = DMA_CHCNT(uart->dma_tx.dma_periph, uart->dma_tx.dma_channel);

    if (dma_cnt == 0)
    {
        rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_TX_DMADONE);
    }
    dma_interrupt_flag_clear(uart->dma_tx.dma_periph, uart->dma_tx.dma_channel, DMA_INT_FLAG_FTF);
}
#endif

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial)
{
    struct gd32_uart *uart;
#ifdef RT_SERIAL_USING_DMA
    rt_size_t dma_cnt;
#endif

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct gd32_uart, serial);

    /* UART in mode Receiver -------------------------------------------------*/
    if ((usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_RBNE) != RESET))
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        /* Clear RXNE interrupt flag */
        usart_interrupt_flag_clear(uart->uart_periph, USART_INT_FLAG_RBNE);
    }
    if ((usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_RBNE_ORERR) != RESET))
    {
        usart_data_receive(uart->uart_periph);
    }
    if ((usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_TBE) != RESET))
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);
        usart_interrupt_flag_clear(uart->uart_periph, USART_INT_FLAG_TBE);
    }
#ifdef RT_SERIAL_USING_DMA
    if ((usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_IDLE) != RESET))
    {
        usart_data_receive(uart->uart_periph);
        dma_cnt = RT_SERIAL_DMA_BUFSZ - DMA_CHCNT(uart->dma_rx.dma_periph, uart->dma_rx.dma_channel);
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (dma_cnt << 8));
    }
    if ((usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_TC) != RESET))
    {
        usart_interrupt_flag_clear(uart->uart_periph, USART_INT_FLAG_TC);
    }
#endif
    if ((usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_PERR) != RESET))
    {
        usart_data_receive(uart->uart_periph);
    }
    if ((usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_EB) != RESET))
    {
        usart_interrupt_flag_clear(uart->uart_periph, USART_INT_FLAG_EB);
    }
    if ((usart_interrupt_flag_get(uart->uart_periph, USART_INT_FLAG_RT) != RESET))
    {
        usart_interrupt_flag_clear(uart->uart_periph, USART_INT_FLAG_RT);
    }
}

#if defined(BSP_USING_UART0)

void USART0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uarts[UART0_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#ifdef RT_SERIAL_USING_DMA
void DMA1_Channel2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    dma_rx_done_isr(&uarts[UART0_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
void DMA1_Channel7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    dma_tx_done_isr(&uarts[UART0_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)

void USART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uarts[UART1_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)

void USART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uarts[UART2_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)

void UART3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uarts[UART3_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)

void UART4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uarts[UART4_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)

void USART5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uarts[UART5_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)

void UART6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uarts[UART6_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_UART7)

void UART7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uarts[UART7_INDEX].serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART7 */

#ifdef RT_SERIAL_USING_DMA
// TODO: 添加发送 DMA 配置，添加接收 DMA 配置
static void DMA_RX_Configuration(struct rt_serial_device *serial)
{
    dma_single_data_parameter_struct dma_init_struct;
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    /* enable DMA1 */
    rcu_periph_clock_enable(RCU_DMA1);

    /* deinitialize DMA channel3(USART0 tx) */
    dma_deinit(uart->dma_rx.dma_periph, uart->dma_rx.dma_channel);
    dma_init_struct.direction = DMA_PERIPH_TO_MEMORY;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.memory0_addr = (uint32_t)(serial->serial_dma_rx);
    dma_init_struct.number = RT_SERIAL_DMA_BUFSZ;
    dma_init_struct.periph_addr = (uint32_t)(uart->uart_periph + 0x04);
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
    dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_init_struct.circular_mode = DMA_CIRCULAR_MODE_ENABLE;

    dma_single_data_mode_init(uart->dma_rx.dma_periph, uart->dma_rx.dma_channel, &dma_init_struct);
    dma_channel_subperipheral_select(uart->dma_rx.dma_periph, uart->dma_rx.dma_channel, uart->dma_rx.dma_subperi);

    dma_interrupt_enable(uart->dma_rx.dma_periph, uart->dma_rx.dma_channel, DMA_CHXCTL_HTFIE);
    dma_interrupt_enable(uart->dma_rx.dma_periph, uart->dma_rx.dma_channel, DMA_CHXCTL_FTFIE);
    NVIC_SetPriority(uart->dma_rx.dma_irq, 0);
    NVIC_EnableIRQ(uart->dma_rx.dma_irq);
    dma_channel_enable(uart->dma_rx.dma_periph, uart->dma_rx.dma_channel);
    usart_dma_receive_config(uart->uart_periph, USART_DENR_ENABLE);
}
static void DMA_TX_Configuration(struct rt_serial_device *serial)
{
    dma_single_data_parameter_struct dma_init_struct;
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct gd32_uart, serial);

    /* enable DMA1 */
    rcu_periph_clock_enable(RCU_DMA1);
    /* deinitialize DMA channel3(USART0 tx) */
    dma_deinit(uart->dma_tx.dma_periph, uart->dma_tx.dma_channel);
    dma_init_struct.direction = DMA_MEMORY_TO_PERIPH;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
//    dma_init_struct.memory0_addr = (uint32_t)tx_buffer;
//    dma_init_struct.number = ARRAYNUM(tx_buffer);
    dma_init_struct.periph_addr = (uint32_t)(uart->uart_periph + 0x04);
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
    dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_init_struct.circular_mode = DMA_CIRCULAR_MODE_DISABLE;

    dma_single_data_mode_init(uart->dma_tx.dma_periph, uart->dma_tx.dma_channel, &dma_init_struct);
    dma_channel_subperipheral_select(uart->dma_tx.dma_periph, uart->dma_tx.dma_channel, uart->dma_tx.dma_subperi);

    dma_interrupt_enable(uart->dma_tx.dma_periph, uart->dma_tx.dma_channel, DMA_CHXCTL_FTFIE);
    NVIC_SetPriority(uart->dma_tx.dma_irq, 0);
    NVIC_EnableIRQ(uart->dma_tx.dma_irq);

    usart_interrupt_enable(uart->uart_periph, USART_INT_IDLE);
    usart_interrupt_enable(uart->uart_periph, USART_INT_TC);
    usart_dma_transmit_config(uart->uart_periph, USART_DENT_ENABLE);
}
#endif
static const struct rt_uart_ops gd32_uart_ops =
{
    .init = gd32_init,
    .configure = gd32_configure,
    .control = gd32_control,
    .putc = gd32_putc,
    .getc = gd32_getc,
    .flush = gd32_flush,
    .start_tx = gd32_start_tx,
    .stop_tx = gd32_stop_tx,
#ifdef RT_SERIAL_USING_DMA
    .is_dma_txing = gd32_is_dma_txing,
    .start_dma_tx = gd32_start_dma_tx,
    .stop_dma_tx = gd32_stop_dma_tx,
#endif
    .enable_interrupt = gd32_enable_interrupt,
    .disable_interrupt = gd32_disable_interrupt,
};

int rt_hw_usart_init(void)
{
    int i;

    for (i = 0; i < sizeof(uarts) / sizeof(uarts[0]); i++)
    {
        uarts[i].serial.ops    = &gd32_uart_ops;

        /* register UART1 device */
        rt_hw_serial_register(&uarts[i].serial,
                              uarts[i].uart_config.name,
                              RT_DEVICE_FLAG_RDWR | 
                              RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX
#ifdef RT_SERIAL_USING_DMA
                            | RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX
#endif
                              , RT_NULL);
    }

    return 0;
}
#endif // RT_USING_SERIAL
