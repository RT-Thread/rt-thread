/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-01-04     iysheng           first version
 */

#include <gd32f10x.h>
#include <drv_usart.h>
#include <board.h>

#ifdef RT_USING_SERIAL

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1) && \
    !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && \
    !defined(BSP_USING_UART4)
    #error "Please define at least one UARTx"

#endif

#include <rtdevice.h>

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

static const struct gd32_uart uarts[] = {
#ifdef BSP_USING_UART0
    {
        USART0,                             /* uart peripheral index */
        USART0_IRQn,                        /* uart iqrn */
        RCU_USART0, RCU_GPIOA, RCU_GPIOA,   /* periph clock, tx gpio clock, rt gpio clock */
        GPIOA, GPIOA,                       /* tx port, tx alternate, tx pin */
        GPIO_PIN_9, GPIO_PIN_10,            /* rx port, rx alternate, rx pin */
        &serial0,
        "uart0",
    },
#endif

#ifdef BSP_USING_UART1
    {
        USART1,                             /* uart peripheral index */
        USART1_IRQn,                        /* uart iqrn */
        RCU_USART1, RCU_GPIOA, RCU_GPIOA,   /* periph clock, tx gpio clock, rt gpio clock */
        GPIOA, GPIOA,                       /* tx port, tx alternate, tx pin */
        GPIO_PIN_2, GPIO_PIN_3,             /* rx port, rx alternate, rx pin */
        &serial1,
        "uart1",
    },
#endif

#ifdef BSP_USING_UART2
    {
        USART2,                             /* uart peripheral index */
        USART2_IRQn,                        /* uart iqrn */
        RCU_USART2, RCU_GPIOB, RCU_GPIOB,   /* periph clock, tx gpio clock, rt gpio clock */
        GPIOB, GPIOB,                       /* tx port, tx alternate, tx pin */
        GPIO_PIN_10, GPIO_PIN_11,           /* rx port, rx alternate, rx pin */
        &serial2,
        "uart2",
    },
#endif

#ifdef BSP_USING_UART3
    {
        UART3,                              /* uart peripheral index */
        UART3_IRQn,                         /* uart iqrn */
        RCU_UART3, RCU_GPIOC, RCU_GPIOC,    /* periph clock, tx gpio clock, rt gpio clock */
        GPIOC, GPIOC,                       /* tx port, tx alternate, tx pin */
        GPIO_PIN_10, GPIO_PIN_11,           /* rx port, rx alternate, rx pin */
        &serial3,
        "uart3",
    },
#endif

#ifdef BSP_USING_UART4
    {
        UART4,                              /* uart peripheral index */
        UART4_IRQn,                         /* uart iqrn */
        RCU_UART4, RCU_GPIOC, RCU_GPIOD,    /* periph clock, tx gpio clock, rt gpio clock */
        GPIOC, GPIOD,                       /* tx port, tx alternate, tx pin */
        GPIO_PIN_12, GPIO_PIN_2,            /* rx port, rx alternate, rx pin */
        &serial4,
        "uart4",
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
    GPIO_TypeDef *GPIOx;
    GPIO_InitPara GPIO_InitStructure = {0};
    /* enable USART clock */
    rcu_periph_clock_enable(uart->tx_gpio_clk);
    rcu_periph_clock_enable(uart->rx_gpio_clk);
    rcu_periph_clock_enable(uart->per_clk);

    GPIOx = (GPIO_TypeDef *)uart->tx_port;
    GPIO_InitStructure.GPIO_Pin = uart->tx_pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_10MHZ;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
    /* TODO 初始化 RX */
    GPIOx = (GPIO_TypeDef *)uart->rx_port;
    GPIO_InitStructure.GPIO_Pin = uart->rx_pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_10MHZ;
    GPIO_Init(GPIOx, &GPIO_InitStructure);

    NVIC_SetPriority(uart->irqn, 0);
    NVIC_EnableIRQ(uart->irqn);
}

static rt_err_t gd32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct gd32_uart *uart;
    USART_TypeDef *USARTx;
    USART_InitPara USART_InitParaStruct = {0};

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = (struct gd32_uart *)serial->parent.user_data;
    gd32_uart_gpio_init(uart);

    USARTx = (USART_TypeDef *)uart->uart_periph;
    USART_InitParaStruct.USART_BRR = cfg->baud_rate;

    switch (cfg->data_bits) {
    case DATA_BITS_9:
        USART_InitParaStruct.USART_WL = USART_WL_9B;
        break;

    default:
        USART_InitParaStruct.USART_WL = USART_WL_8B;
        break;
    }

    switch (cfg->stop_bits) {
    case STOP_BITS_2:
        USART_InitParaStruct.USART_STBits = USART_STBITS_2;
        break;
    default:
        USART_InitParaStruct.USART_STBits = USART_STBITS_1;
        break;
    }

    switch (cfg->parity) {
    case PARITY_ODD:
        USART_InitParaStruct.USART_Parity = USART_PARITY_SETODD;
        break;
    case PARITY_EVEN:
        USART_InitParaStruct.USART_Parity = USART_PARITY_SETEVEN;
        break;
    default:
        USART_InitParaStruct.USART_Parity = USART_PARITY_RESET;
        break;
    }

    USART_InitParaStruct.USART_HardwareFlowControl = USART_HARDWAREFLOWCONTROL_NONE;
    USART_InitParaStruct.USART_RxorTx = USART_RXORTX_RX | USART_RXORTX_TX;
    USART_Init(USARTx, &USART_InitParaStruct);
    USART_Enable(USARTx, ENABLE);

    return RT_EOK;
}

static rt_err_t gd32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct gd32_uart *uart;
    USART_TypeDef *USARTx;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct gd32_uart *)serial->parent.user_data;
    USARTx = (USART_TypeDef *)uart->uart_periph;

    switch (cmd) {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->irqn);
        /* disable interrupt */
        USART_INT_Set(USARTx, USART_INT_RBNE, DISABLE);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irqn);
        /* enable interrupt */
        USART_INT_Set(USARTx, USART_INT_RBNE, ENABLE);
        break;
    }

    return RT_EOK;
}

static int gd32_putc(struct rt_serial_device *serial, char ch)
{
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct gd32_uart *)serial->parent.user_data;


    USART_DataSend((USART_TypeDef *)uart->uart_periph, ch);
    while ((USART_GetBitState(uart->uart_periph, USART_FLAG_TC) == RESET));

    return 1;
}

static int gd32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct gd32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct gd32_uart *)serial->parent.user_data;

    ch = -1;
    if (USART_GetBitState(uart->uart_periph, USART_FLAG_RBNE) != RESET)
        ch = USART_DataReceive(uart->uart_periph);
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

    if ((USART_GetIntBitState((USART_TypeDef *)uart->uart_periph, USART_INT_RBNE) != RESET) &&
            (USART_GetBitState((USART_TypeDef *)uart->uart_periph, USART_FLAG_RBNE) != RESET)) {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        /* Clear RXNE interrupt flag */
        USART_ClearBitState(uart->uart_periph, USART_FLAG_RBNE);
    }
}

static const struct rt_uart_ops gd32_uart_ops = {
    gd32_configure,
    gd32_control,
    gd32_putc,
    gd32_getc,
};

int gd32_hw_usart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    int i;


    for (i = 0; i < sizeof(uarts) / sizeof(uarts[0]); i++) {
        uarts[i].serial->ops    = &gd32_uart_ops;
        uarts[i].serial->config = config;

        /* register UART device */
        rt_hw_serial_register(uarts[i].serial,
                              uarts[i].device_name,
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              (void *)&uarts[i]);
    }

    return 0;
}
INIT_BOARD_EXPORT(gd32_hw_usart_init);
#endif
