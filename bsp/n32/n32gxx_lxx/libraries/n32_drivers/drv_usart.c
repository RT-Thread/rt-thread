/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-19     Nations      first version
 */

#include <drv_usart.h>

#ifdef RT_USING_SERIAL

#if defined(BSP_USING_USART1) || defined(BSP_USING_USART2) || \
    defined(BSP_USING_USART3) || defined(BSP_USING_UART4)  || \
    defined(BSP_USING_UART5)  ||  defined(BSP_USING_UART6) || \
    defined(BSP_USING_UART7)

#include <rtdevice.h>

/* n32 uart driver */
// Todo: compress uart info
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
struct n32_uart
{
    USART_Module* uart_periph;      //Todo: 3bits
    IRQn_Type     irqn;             //Todo: 7bits
    uint32_t      per_clk;          //Todo: 5bits
    uint32_t      tx_gpio_clk;      //Todo: 5bits
    uint32_t      rx_gpio_clk;      //Todo: 5bits
    GPIO_Module*  tx_port;          //Todo: 4bits
    GPIO_ModeType tx_af;            //Todo: 4bits
    uint16_t      tx_pin;           //Todo: 4bits
    GPIO_Module*  rx_port;          //Todo: 4bits
    GPIO_ModeType rx_af;            //Todo: 4bits
    uint16_t      rx_pin;           //Todo: 4bits

    struct rt_serial_device * serial;
    char *device_name;
};
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
struct n32_uart
{
    USART_Module* uart_periph;       // Todo: 3bits
    IRQn_Type     irqn;              // Todo: 7bits
    uint32_t      per_clk;           // Todo: 5bits
    uint32_t      tx_gpio_clk;       // Todo: 5bits
    uint32_t      rx_gpio_clk;       // Todo: 5bits
    GPIO_Module*  tx_port;           // Todo: 4bits
    uint32_t      tx_af;             // Todo: 4bits
    uint16_t      tx_pin;            // Todo: 4bits
    GPIO_Module*  rx_port;           // Todo: 4bits
    uint32_t      rx_af;             // Todo: 4bits
    uint16_t      rx_pin;            // Todo: 4bits

    struct rt_serial_device * serial;
    char *device_name;
};
#endif

static void uart_isr(struct rt_serial_device *serial);

#ifdef BSP_USING_USART1
struct rt_serial_device serial1;

void USART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial1);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_USART1 */

#ifdef BSP_USING_USART2
struct rt_serial_device serial2;

void USART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial2);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_USART2 */

#ifdef BSP_USING_USART3
struct rt_serial_device serial3;

void USART3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial3);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_USART3 */

#ifdef BSP_USING_UART4
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

#ifdef BSP_USING_UART5
struct rt_serial_device serial5;

void UART5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial5);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART5 */

#ifdef BSP_USING_UART6
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

#ifdef BSP_USING_UART7
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

static const struct n32_uart uarts[] = {
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
#ifdef BSP_USING_USART1
    {
        USART1,                                                               // uart peripheral index
        USART1_IRQn,                                                          // uart iqrn
        RCC_APB2_PERIPH_USART1, RCC_APB2_PERIPH_GPIOA, RCC_APB2_PERIPH_GPIOA, // periph clock, tx gpio clock, rt gpio clock
        GPIOA, GPIO_Mode_AF_PP, GPIO_PIN_9,                                   // tx port, tx alternate, tx pin
        GPIOA, GPIO_Mode_IN_FLOATING, GPIO_PIN_10,                            // rx port, rx alternate, rx pin
        &serial1,
        "usart1",
    },
#endif

#ifdef BSP_USING_USART2
    {
        USART2,                                                               // uart peripheral index
        USART2_IRQn,                                                          // uart iqrn
        RCC_APB1_PERIPH_USART2, RCC_APB2_PERIPH_GPIOA, RCC_APB2_PERIPH_GPIOA, // periph clock, tx gpio clock, rt gpio clock
        GPIOA, GPIO_Mode_AF_PP, GPIO_PIN_2,                                   // tx port, tx alternate, tx pin
        GPIOA, GPIO_Mode_IN_FLOATING, GPIO_PIN_3,                             // rx port, rx alternate, rx pin
        &serial2,
        "usart2",
    },
#endif

#ifdef BSP_USING_USART3
    {
        USART3,                                                               // uart peripheral index
        USART3_IRQn,                                                          // uart iqrn
        RCC_APB1_PERIPH_USART3, RCC_APB2_PERIPH_GPIOB, RCC_APB2_PERIPH_GPIOB, // periph clock, tx gpio clock, rt gpio clock
        GPIOB, GPIO_Mode_AF_PP, GPIO_PIN_10,                                  // tx port, tx alternate, tx pin
        GPIOB, GPIO_Mode_IN_FLOATING, GPIO_PIN_11,                            // rx port, rx alternate, rx pin
        &serial3,
        "usart3",
    },
#endif

#ifdef BSP_USING_UART4
    {
              UART4,                                                                // uart peripheral index
        UART4_IRQn,                                                           // uart iqrn
        RCC_APB1_PERIPH_UART4, RCC_APB2_PERIPH_GPIOA, RCC_APB2_PERIPH_GPIOA,  // periph clock, tx gpio clock, rt gpio clock
        GPIOA, GPIO_Mode_AF_PP, GPIO_PIN_13,                                  // tx port, tx alternate, tx pin
        GPIOA, GPIO_Mode_IN_FLOATING, GPIO_PIN_14,                            // rx port, rx alternate, rx pin
        &serial4,
        "uart4",
    },
#endif

#ifdef BSP_USING_UART5
    {
        UART5,                                                                // uart peripheral index
        UART5_IRQn,                                                           // uart iqrn
        RCC_APB1_PERIPH_UART5, RCC_APB2_PERIPH_GPIOB, RCC_APB2_PERIPH_GPIOB,  // periph clock, tx gpio clock, rt gpio clock
        GPIOB, GPIO_Mode_AF_PP, GPIO_PIN_13,                                  // tx port, tx alternate, tx pin
        GPIOB, GPIO_Mode_IN_FLOATING, GPIO_PIN_14,                            // rx port, rx alternate, rx pin
        &serial5,
        "uart5",
    },
#endif

#ifdef BSP_USING_UART6
    {
        UART6,                                                                // uart peripheral index
        UART6_IRQn,                                                           // uart iqrn
        RCC_APB2_PERIPH_UART6, RCC_APB2_PERIPH_GPIOB, RCC_APB2_PERIPH_GPIOB,  // periph clock, tx gpio clock, rt gpio clock
        GPIOB, GPIO_Mode_AF_PP, GPIO_PIN_0,                                   // tx port, tx alternate, tx pin
        GPIOB, GPIO_Mode_IN_FLOATING, GPIO_PIN_1,                             // rx port, rx alternate, rx pin
        &serial6,
        "uart6",
    },
#endif

#ifdef BSP_USING_UART7
    {
        UART7,                                                                // uart peripheral index
        UART7_IRQn,                                                           // uart iqrn
        RCC_APB2_PERIPH_UART7, RCC_APB2_PERIPH_GPIOC, RCC_APB2_PERIPH_GPIOC,  // periph clock, tx gpio clock, rt gpio clock
        GPIOC, GPIO_Mode_AF_PP, GPIO_PIN_2,                                   // tx port, tx alternate, tx pin
        GPIOC, GPIO_Mode_IN_FLOATING, GPIO_PIN_3,                             // rx port, rx alternate, rx pin
        &serial7,
        "uart7",
    },
#endif

#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)

#ifdef BSP_USING_USART1
    {
        USART1,                                                                                             // uart peripheral index
        USART1_IRQn,                                                                                        // uart iqrn
        RCC_APB2_PERIPH_USART1, RCC_APB2_PERIPH_GPIOA, RCC_APB2_PERIPH_GPIOA, // periph clock, tx gpio clock, rt gpio clock
        GPIOA, GPIO_AF4_USART1, GPIO_PIN_9,                                   // tx port, tx alternate, tx pin
        GPIOA, GPIO_AF4_USART1, GPIO_PIN_10,                                                                // rx port, rx alternate, rx pin
        &serial1,
        "usart1",
    },
#endif

#ifdef BSP_USING_USART2
    {
        USART2,                                                                                             // uart peripheral index
        USART2_IRQn,                                                                                        // uart iqrn
        RCC_APB1_PERIPH_USART2, RCC_APB2_PERIPH_GPIOA, RCC_APB2_PERIPH_GPIOA, // periph clock, tx gpio clock, rt gpio clock
        GPIOA, GPIO_AF4_USART2, GPIO_PIN_2,                                                         // tx port, tx alternate, tx pin
        GPIOA, GPIO_AF4_USART2, GPIO_PIN_3,                                                               // rx port, rx alternate, rx pin
        &serial2,
        "usart2",
    },
#endif

#ifdef BSP_USING_USART3
    {
        USART3,                                                                                             // uart peripheral index
        USART3_IRQn,                                                                                        // uart iqrn
        RCC_APB1_PERIPH_USART3, RCC_APB2_PERIPH_GPIOB, RCC_APB2_PERIPH_GPIOB, // periph clock, tx gpio clock, rt gpio clock
        GPIOB, GPIO_AF0_USART3, GPIO_PIN_10,                                                        // tx port, tx alternate, tx pin
        GPIOB, GPIO_AF5_USART3, GPIO_PIN_11,                                                              // rx port, rx alternate, rx pin
        &serial3,
        "usart3",
    },
#endif

#ifdef BSP_USING_UART4
    {
        UART4,                                                                                            // uart peripheral index
        UART4_IRQn,                                                                                         // uart iqrn
        RCC_APB2_PERIPH_UART4, RCC_APB2_PERIPH_GPIOB, RCC_APB2_PERIPH_GPIOB,  // periph clock, tx gpio clock, rt gpio clock
        GPIOB, GPIO_AF6_UART4, GPIO_PIN_0,                                                              // tx port, tx alternate, tx pin
        GPIOB, GPIO_AF6_UART4, GPIO_PIN_1,                                                                    // rx port, rx alternate, rx pin
        &serial4,
        "uart4",
    },
#endif

#ifdef BSP_USING_UART5
    {
        UART5,                                                                                              // uart peripheral index
        UART5_IRQn,                                                                                         // uart iqrn
        RCC_APB2_PERIPH_UART5, RCC_APB2_PERIPH_GPIOB, RCC_APB2_PERIPH_GPIOB,  // periph clock, tx gpio clock, rt gpio clock
        GPIOB, GPIO_AF6_UART5, GPIO_PIN_8,                                                            // tx port, tx alternate, tx pin
        GPIOB, GPIO_AF6_UART5, GPIO_PIN_9,                                                                    // rx port, rx alternate, rx pin
        &serial5,
        "uart5",
    },
#endif
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
void n32_uart_gpio_init(struct n32_uart *uart, struct serial_configure *cfg)
{
    GPIO_InitType GPIO_InitStructure;

#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    /* enable USART clock */
    RCC_EnableAPB2PeriphClk(uart->tx_gpio_clk | uart->rx_gpio_clk | RCC_APB2_PERIPH_AFIO, ENABLE);

    if (uart->uart_periph == USART1 || uart->uart_periph == UART6 || uart->uart_periph == UART7)
    {
        RCC_EnableAPB2PeriphClk(uart->per_clk, ENABLE);
    }
    else
    {
        RCC_EnableAPB1PeriphClk(uart->per_clk, ENABLE);
    }

#ifdef BSP_USING_UART4
    GPIO_ConfigPinRemap(GPIO_RMP_SW_JTAG_DISABLE, ENABLE);
    GPIO_ConfigPinRemap(GPIO_RMP2_UART4, ENABLE);
#endif /* BSP_USING_UART4 */

#ifdef BSP_USING_UART5
    GPIO_ConfigPinRemap(GPIO_RMP1_UART5, ENABLE);
#endif /* BSP_USING_UART5 */

#ifdef BSP_USING_UART6
    GPIO_ConfigPinRemap(GPIO_RMP3_UART6, ENABLE);
#endif /* BSP_USING_UART6 */

#ifdef BSP_USING_UART7
    GPIO_ConfigPinRemap(GPIO_RMP1_UART7, ENABLE);
#endif /* BSP_USING_UART7 */

    GPIO_InitStruct(&GPIO_InitStructure);

    /* Config USARTx_TX I/O */
    GPIO_InitStructure.Pin        = uart->tx_pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = uart->tx_af;
    GPIO_InitPeripheral(uart->tx_port, &GPIO_InitStructure);

    /* Config USARTx_RX I/O */
    GPIO_InitStructure.Pin        = uart->rx_pin;
    GPIO_InitStructure.GPIO_Mode  = uart->rx_af;
    GPIO_InitPeripheral(uart->rx_port, &GPIO_InitStructure);
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    /* enable USART clock */
    RCC_EnableAPB2PeriphClk(uart->tx_gpio_clk | uart->rx_gpio_clk | RCC_APB2_PERIPH_AFIO, ENABLE);

    if (uart->uart_periph == USART1 || uart->uart_periph == UART4 || uart->uart_periph == UART5)
    {
        RCC_EnableAPB2PeriphClk(uart->per_clk, ENABLE);
    }
    else
    {
        RCC_EnableAPB1PeriphClk(uart->per_clk, ENABLE);
    }

    GPIO_InitStruct(&GPIO_InitStructure);

    /* connect port to USARTx_Tx */
    GPIO_InitStructure.Pin            = uart->tx_pin;
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = uart->tx_af;
    GPIO_InitPeripheral(uart->tx_port, &GPIO_InitStructure);

    /* connect port to USARTx_Rx */
    GPIO_InitStructure.Pin            = uart->rx_pin;
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = uart->rx_af;
    GPIO_InitPeripheral(uart->rx_port, &GPIO_InitStructure);
#endif

    NVIC_SetPriority(uart->irqn, 0);
    NVIC_EnableIRQ(uart->irqn);
}

static rt_err_t n32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct n32_uart *uart;
    USART_InitType USART_InitStructure;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = (struct n32_uart *)serial->parent.user_data;

    n32_uart_gpio_init(uart, cfg);

    USART_InitStructure.BaudRate = cfg->baud_rate;

    switch (cfg->data_bits)
    {
        case DATA_BITS_9:
            USART_InitStructure.WordLength = USART_WL_9B;
            break;

        default:
            USART_InitStructure.WordLength = USART_WL_8B;;
            break;
    }

    switch (cfg->stop_bits)
    {
        case STOP_BITS_1:
            USART_InitStructure.StopBits = USART_STPB_1;
            break;
        case STOP_BITS_2:
            USART_InitStructure.StopBits = USART_STPB_0_5;
            break;
        case STOP_BITS_3:
            USART_InitStructure.StopBits = USART_STPB_2;
            break;
        case STOP_BITS_4:
            USART_InitStructure.StopBits = USART_STPB_1_5;
            break;
        default:
            break;
    }

    switch (cfg->parity)
    {
        case PARITY_ODD:
            USART_InitStructure.Parity = USART_PE_ODD;
            break;
        case PARITY_EVEN:
            USART_InitStructure.Parity = USART_PE_EVEN;
            break;
        case PARITY_NONE:
            USART_InitStructure.Parity = USART_PE_NO;
            break;
        default:
            break;
    }

    switch (cfg->flowcontrol)
    {
        case RT_SERIAL_FLOWCONTROL_NONE:
            USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
            break;

        case RT_SERIAL_FLOWCONTROL_CTSRTS:
            USART_InitStructure.HardwareFlowControl = USART_HFCTRL_RTS_CTS;
            break;

        default:
            USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
            break;
    }

    USART_InitStructure.Mode = USART_MODE_TX | USART_MODE_RX;

    USART_Init(uart->uart_periph, &USART_InitStructure);

    USART_Enable(uart->uart_periph, ENABLE);

    return RT_EOK;
}

static rt_err_t n32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct n32_uart *uart;
    NVIC_InitType NVIC_InitStructure;

    /* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    RT_ASSERT(serial != RT_NULL);
    uart = (struct n32_uart *)serial->parent.user_data;

    switch (cmd)
    {
        case RT_DEVICE_CTRL_CLR_INT:
            /* disable rx irq */
            NVIC_InitStructure.NVIC_IRQChannel            = uart->irqn;
            NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
            NVIC_InitStructure.NVIC_IRQChannelCmd         = DISABLE;
            NVIC_Init(&NVIC_InitStructure);
            /* disable interrupt */
            USART_ConfigInt(uart->uart_periph, USART_INT_RXDNE, DISABLE);
            break;

        case RT_DEVICE_CTRL_SET_INT:
            /* enable rx irq */
            NVIC_InitStructure.NVIC_IRQChannel            = uart->irqn;
            NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
            NVIC_InitStructure.NVIC_IRQChannelCmd         = ENABLE;
            NVIC_Init(&NVIC_InitStructure);

            /* enable interrupt */
            USART_ConfigInt(uart->uart_periph, USART_INT_RXDNE, ENABLE);
            break;

        default:
            break;

    }

    return RT_EOK;
}

static int n32_putc(struct rt_serial_device *serial, char ch)
{
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct n32_uart *)serial->parent.user_data;

    USART_SendData(uart->uart_periph, ch);
    while ((USART_GetFlagStatus(uart->uart_periph, USART_FLAG_TXDE) == RESET));

    return 1;
}

static int n32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct n32_uart *)serial->parent.user_data;

    ch = -1;
    if (USART_GetFlagStatus(uart->uart_periph, USART_FLAG_RXDNE) != RESET)
    {
        ch = USART_ReceiveData(uart->uart_periph);
    }

    return ch;
}

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial)
{
    struct n32_uart *uart = (struct n32_uart *) serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);

    /* UART in mode Receiver -------------------------------------------------*/
    if (USART_GetIntStatus(uart->uart_periph, USART_INT_RXDNE) != RESET &&
        USART_GetFlagStatus(uart->uart_periph, USART_FLAG_RXDNE) != RESET)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }

    if (USART_GetIntStatus(uart->uart_periph, USART_INT_TXDE) != RESET &&
        USART_GetFlagStatus(uart->uart_periph, USART_FLAG_TXDE) != RESET)
    {
        /* Write one byte to the transmit data register */
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);

    }
}

static const struct rt_uart_ops n32_uart_ops =
{
    n32_configure,
    n32_control,
    n32_putc,
    n32_getc,
};

int rt_hw_usart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    int i;

    for (i = 0; i < sizeof(uarts) / sizeof(uarts[0]); i++)
    {
        uarts[i].serial->ops    = &n32_uart_ops;
        uarts[i].serial->config = config;

        /* register UART device */
        rt_hw_serial_register(uarts[i].serial,
                              uarts[i].device_name,
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              (void *)&uarts[i]);
    }

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_usart_init);

#endif /* defined(BSP_USING_USARTx) */
#endif  /* BSP_USING_SERIAL */
