/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file drv_usart.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */

#include <drv_usart.h>
#include "board.h"

#ifdef RT_USING_SERIAL

#if defined(BSP_USING_USART1) || defined(BSP_USING_USART2) || \
    defined(BSP_USING_USART3) || defined(BSP_USING_UART4) || \
    defined(BSP_USING_UART5) ||  defined(BSP_USING_UART6) || \
    defined(BSP_USING_UART7)


#include <rtdevice.h>

/* n32 uart driver */
// Todo: compress uart info
struct n32_uart
{
    USART_Module* uart_periph;       //Todo: 3bits
    IRQn_Type irqn;                 //Todo: 7bits    
    uint32_t per_clk;               //Todo: 5bits
    uint32_t tx_gpio_clk;           //Todo: 5bits
    uint32_t rx_gpio_clk;           //Todo: 5bits
    GPIO_Module* tx_port;            //Todo: 4bits
    GPIO_ModeType tx_af;                 //Todo: 4bits
    uint16_t tx_pin;                //Todo: 4bits
    GPIO_Module* rx_port;            //Todo: 4bits
    GPIO_ModeType rx_af;                 //Todo: 4bits
    uint16_t rx_pin;                //Todo: 4bits

    struct rt_serial_device * serial;    
    char *device_name;
};

static void uart_isr(struct rt_serial_device *serial);

#if defined(BSP_USING_USART1)
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

#if defined(BSP_USING_USART2)
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

#if defined(BSP_USING_USART3)
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

void UART5_IRQHandler(void)
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

static const struct n32_uart uarts[] = {
#ifdef BSP_USING_USART1
    {
        USART1,                                 // uart peripheral index
        USART1_IRQn,                            // uart iqrn
        RCC_APB2_PERIPH_USART1, RCC_APB2_PERIPH_GPIOA, RCC_APB2_PERIPH_GPIOA,       // periph clock, tx gpio clock, rt gpio clock
        GPIOA, GPIO_Mode_AF_PP, GPIO_PIN_9,           // tx port, tx alternate, tx pin
        GPIOA, GPIO_Mode_IN_FLOATING, GPIO_PIN_10,    // rx port, rx alternate, rx pin
        &serial1,
        "usart1",
    },
#endif
    
#ifdef BSP_USING_USART2
    {
        USART2,                                 // uart peripheral index
        USART2_IRQn,                            // uart iqrn
        RCC_APB1_PERIPH_USART2, RCC_APB2_PERIPH_GPIOA, RCC_APB2_PERIPH_GPIOA,       // periph clock, tx gpio clock, rt gpio clock
        GPIOA, GPIO_Mode_AF_PP, GPIO_PIN_2,           // tx port, tx alternate, tx pin
        GPIOA, GPIO_Mode_IN_FLOATING, GPIO_PIN_3,     // rx port, rx alternate, rx pin
        &serial2,
        "usart2",
    },
#endif
    
#ifdef BSP_USING_USART3
    {
        USART3,                                 // uart peripheral index
        USART3_IRQn,                            // uart iqrn
        RCC_APB1_PERIPH_USART3, RCC_APB2_PERIPH_GPIOB, RCC_APB2_PERIPH_GPIOB,       // periph clock, tx gpio clock, rt gpio clock
        GPIOB, GPIO_Mode_AF_PP, GPIO_PIN_10,          // tx port, tx alternate, tx pin
        GPIOB, GPIO_Mode_IN_FLOATING, GPIO_PIN_11,    // rx port, rx alternate, rx pin
        &serial3,
        "usart3",
    },
#endif

#ifdef BSP_USING_UART4
    {
        UART4,                                 // uart peripheral index
        UART4_IRQn,                            // uart iqrn
        RCC_APB1_PERIPH_UART4, RCC_APB2_PERIPH_GPIOC, RCC_APB2_PERIPH_GPIOC,       // periph clock, tx gpio clock, rt gpio clock
        GPIOC, GPIO_Mode_AF_PP, GPIO_PIN_10,         // tx port, tx alternate, tx pin
        GPIOC, GPIO_Mode_IN_FLOATING, GPIO_PIN_11,   // rx port, rx alternate, rx pin
        &serial4,
        "uart4",
    },
#endif
    
#ifdef BSP_USING_UART5
    {
        UART5,                                 // uart peripheral index
        UART5_IRQn,                            // uart iqrn
        RCC_APB1_PERIPH_UART5, RCC_APB2_PERIPH_GPIOC, RCC_APB2_PERIPH_GPIOD,       // periph clock, tx gpio clock, rt gpio clock
        GPIOC, GPIO_Mode_AF_PP, GPIO_PIN_12,         // tx port, tx alternate, tx pin
        GPIOD, GPIO_Mode_IN_FLOATING, GPIO_PIN_2,    // rx port, rx alternate, rx pin
        &serial5,
        "uart5",
    },
#endif

#ifdef BSP_USING_UART6
    {
        UART6,                                 // uart peripheral index
        UART6_IRQn,                            // uart iqrn
        RCC_APB2_PERIPH_UART6, RCC_APB2_PERIPH_GPIOE, RCC_APB2_PERIPH_GPIOE,       // periph clock, tx gpio clock, rt gpio clock
        GPIOE, GPIO_Mode_AF_PP, GPIO_PIN_2,           // tx port, tx alternate, tx pin
        GPIOE, GPIO_Mode_IN_FLOATING, GPIO_PIN_3,     // rx port, rx alternate, rx pin
        &serial6,
        "uart6",
    },
#endif
    
#ifdef BSP_USING_UART7
    {
        UART7,                                 // uart peripheral index
        UART7_IRQn,                            // uart iqrn
        RCC_APB2_PERIPH_UART7, RCC_APB2_PERIPH_GPIOC, RCC_APB2_PERIPH_GPIOC,       // periph clock, tx gpio clock, rt gpio clock
        GPIOC, GPIO_Mode_AF_PP, GPIO_PIN_4,             // tx port, tx alternate, tx pin
        GPIOC, GPIO_Mode_IN_FLOATING, GPIO_PIN_5,       // rx port, rx alternate, rx pin
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
void n32_uart_gpio_init(struct n32_uart *uart, struct serial_configure *cfg)
{
    /* enable USART clock */
    RCC_EnableAPB2PeriphClk(uart->tx_gpio_clk | uart->rx_gpio_clk | RCC_APB2_PERIPH_AFIO, ENABLE);
    
    if(uart->uart_periph == USART1 || uart->uart_periph == UART6 || uart->uart_periph == UART7)
    {
        RCC_EnableAPB2PeriphClk(uart->per_clk, ENABLE);
    }    
    else
    {
        RCC_EnableAPB1PeriphClk(uart->per_clk, ENABLE);
    }
    
    /* connect port to USARTx_Tx */
    GPIOInit(uart->tx_port, uart->tx_af, GPIO_Speed_50MHz, uart->tx_pin);
    /* connect port to USARTx_Rx */
    GPIOInit(uart->tx_port, uart->rx_af, GPIO_Speed_50MHz, uart->rx_pin);
    
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
    }

    return RT_EOK;
}

static int n32_putc(struct rt_serial_device *serial, char ch)
{
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct n32_uart *)serial->parent.user_data;

    USART_SendData(uart->uart_periph, ch);
    while((USART_GetFlagStatus(uart->uart_periph, USART_FLAG_TXDE) == RESET));
    
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
        ch = USART_ReceiveData(uart->uart_periph);
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
