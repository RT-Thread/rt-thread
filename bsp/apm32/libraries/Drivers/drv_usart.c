/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     Abbcc        first version
 * 2022-12-26     luobeihai    add APM2F0 series MCU support
 * 2023-03-27     luobeihai    add APM32E1/S1 series MCU support
 */

#include "board.h"
#include "drv_usart.h"

#ifdef RT_USING_SERIAL
#if !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && \
    !defined(BSP_USING_UART3) && !defined(BSP_USING_UART4) && \
    !defined(BSP_USING_UART5) && !defined(BSP_USING_UART6)
    #error "Please define at least one BSP_USING_UARTx"
    /* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

struct apm32_usart
{
    const char *name;
    USART_T *usartx;
    IRQn_Type irq_type;
    struct rt_serial_device serial;
};

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
};

static struct apm32_usart usart_config[] =
{
#ifdef BSP_USING_UART1
    {
        "uart1",
        USART1,
        USART1_IRQn,
    },
#endif
#ifdef BSP_USING_UART2
    {
        "uart2",
        USART2,
        USART2_IRQn,
    },
#endif
#if defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
#ifdef BSP_USING_UART3
    {
        "uart3",
        USART3,
        USART3_IRQn,
    },
#endif
#ifdef BSP_USING_UART4
    {
        "uart4",
        UART4,
        UART4_IRQn,
    },
#endif
#ifdef BSP_USING_UART5
    {
        "uart5",
        UART5,
        UART5_IRQn,
    },
#endif
#ifdef BSP_USING_UART6
    {
        "uart6",
        USART6,
        USART6_IRQn,
    },
#endif
#endif /* SOC_SERIES_APM32F0 */
};

static rt_err_t apm32_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    USART_Config_T USART_ConfigStruct;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    struct apm32_usart *usart_instance = (struct apm32_usart *) serial->parent.user_data;

    apm32_usart_init();

    USART_ConfigStruct.baudRate = cfg->baud_rate;
    USART_ConfigStruct.mode = USART_MODE_TX_RX;
    USART_ConfigStruct.parity = USART_PARITY_NONE;

#if defined(SOC_SERIES_APM32F0)
    switch (cfg->flowcontrol)
    {
    case RT_SERIAL_FLOWCONTROL_NONE:

        USART_ConfigStruct.hardwareFlowCtrl = USART_FLOW_CTRL_NONE;
        break;
    case RT_SERIAL_FLOWCONTROL_CTSRTS:
        USART_ConfigStruct.hardwareFlowCtrl = USART_FLOW_CTRL_RTS_CTS;
        break;
    default:
        USART_ConfigStruct.hardwareFlowCtrl = USART_FLOW_CTRL_NONE;
        break;
    }
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
    switch (cfg->flowcontrol)
    {
    case RT_SERIAL_FLOWCONTROL_NONE:
        USART_ConfigStruct.hardwareFlow = USART_HARDWARE_FLOW_NONE;
        break;
    case RT_SERIAL_FLOWCONTROL_CTSRTS:
        USART_ConfigStruct.hardwareFlow = USART_HARDWARE_FLOW_RTS_CTS;
        break;
    default:
        USART_ConfigStruct.hardwareFlow = USART_HARDWARE_FLOW_NONE;
        break;
    }
#endif /* SOC_SERIES_APM32F0 */

    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        if (cfg->parity == PARITY_ODD || cfg->parity == PARITY_EVEN)
            USART_ConfigStruct.wordLength = USART_WORD_LEN_9B;
        else
            USART_ConfigStruct.wordLength = USART_WORD_LEN_8B;
        break;
    case DATA_BITS_9:
        USART_ConfigStruct.wordLength = USART_WORD_LEN_9B;
        break;
    default:
        USART_ConfigStruct.wordLength = USART_WORD_LEN_8B;
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        USART_ConfigStruct.stopBits = USART_STOP_BIT_1;
        break;
    case STOP_BITS_2:
        USART_ConfigStruct.stopBits = USART_STOP_BIT_2;
        break;
    default:
        USART_ConfigStruct.stopBits = USART_STOP_BIT_1;
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_NONE:
        USART_ConfigStruct.parity     = USART_PARITY_NONE;
        break;
    case PARITY_ODD:
        USART_ConfigStruct.parity     = USART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        USART_ConfigStruct.parity     = USART_PARITY_EVEN;
        break;
    default:
        USART_ConfigStruct.parity     = USART_PARITY_NONE;
        break;
    }

    USART_Config(usart_instance->usartx, &USART_ConfigStruct);
    USART_Enable(usart_instance->usartx);

    return RT_EOK;
}

static rt_err_t apm32_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct apm32_usart *usart;

    RT_ASSERT(serial != RT_NULL);

    usart = (struct apm32_usart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

#if defined(SOC_SERIES_APM32F0)
    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:

        /* disable rx irq */
        NVIC_DisableIRQRequest(usart->irq_type);

        /* disable interrupt */
        USART_DisableInterrupt(usart->usartx, USART_INT_RXBNEIE);

        break;

    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQRequest(usart->irq_type, 1);

        /* enable interrupt */
        USART_EnableInterrupt(usart->usartx, USART_INT_RXBNEIE);
        break;
    }
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:

        /* disable rx irq */
        NVIC_DisableIRQRequest(usart->irq_type);

        /* disable interrupt */
        USART_DisableInterrupt(usart->usartx, USART_INT_RXBNE);

        break;

    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQRequest(usart->irq_type, 1, 0);

        /* enable interrupt */
        USART_EnableInterrupt(usart->usartx, USART_INT_RXBNE);
        break;
    }
#endif /* SOC_SERIES_APM32F0 */
    return RT_EOK;
}

static int apm32_uart_putc(struct rt_serial_device *serial, char c)
{
    struct apm32_usart *usart;
    RT_ASSERT(serial != RT_NULL);

    usart = (struct apm32_usart *) serial->parent.user_data;

    RT_ASSERT(usart != RT_NULL);

    USART_TxData(usart->usartx, (uint8_t) c);

    while (USART_ReadStatusFlag(usart->usartx, USART_FLAG_TXC) == RESET);

    return 1;
}

static int apm32_uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct apm32_usart *usart;
    RT_ASSERT(serial != RT_NULL);
    usart = (struct apm32_usart *) serial->parent.user_data;

    RT_ASSERT(usart != RT_NULL);

    ch = -1;
    if (USART_ReadStatusFlag(usart->usartx, USART_FLAG_RXBNE) != RESET)
    {
        ch = USART_RxData(usart->usartx);
    }
    return ch;
}

/**
 * Uart common interrupt process. This need add to usart ISR.
 *
 * @param serial serial device
 */
static void usart_isr(struct rt_serial_device *serial)
{
    struct apm32_usart *usart;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct apm32_usart *) serial->parent.user_data;

    RT_ASSERT(usart != RT_NULL);

    /* UART in mode Receiver */
#if defined(SOC_SERIES_APM32F0)
    if ((USART_ReadStatusFlag(usart->usartx, USART_FLAG_RXBNE) != RESET) &&
            (USART_ReadIntFlag(usart->usartx, USART_INT_FLAG_RXBNE) != RESET))
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
    if ((USART_ReadStatusFlag(usart->usartx, USART_FLAG_RXBNE) != RESET) &&
            (USART_ReadIntFlag(usart->usartx, USART_INT_RXBNE) != RESET))
#endif
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
    else
    {
#if defined(SOC_SERIES_APM32F0)
        if (USART_ReadStatusFlag(usart->usartx, USART_FLAG_OVRE) != RESET)
        {
            USART_ClearStatusFlag(usart->usartx, USART_FLAG_OVRE);
        }
        if (USART_ReadStatusFlag(usart->usartx, USART_FLAG_NEF) != RESET)
        {
            USART_ClearStatusFlag(usart->usartx, USART_FLAG_NEF);
        }
        if (USART_ReadStatusFlag(usart->usartx, USART_FLAG_FEF) != RESET)
        {
            USART_ClearStatusFlag(usart->usartx, USART_FLAG_FEF);
        }
        if (USART_ReadStatusFlag(usart->usartx, USART_FLAG_PEF) != RESET)
        {
            USART_ClearStatusFlag(usart->usartx, USART_FLAG_PEF);
        }
        if (USART_ReadStatusFlag(usart->usartx, USART_FLAG_CTSF) != RESET)
        {
            USART_ClearStatusFlag(usart->usartx, USART_FLAG_CTSF);
        }
        if (USART_ReadStatusFlag(usart->usartx, USART_FLAG_LBDF) != RESET)
        {
            USART_ClearStatusFlag(usart->usartx, USART_FLAG_LBDF);
        }
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
        if (USART_ReadStatusFlag(usart->usartx, USART_FLAG_OVRE) != RESET)
        {
            USART_ClearStatusFlag(usart->usartx, USART_FLAG_OVRE);
        }
        if (USART_ReadStatusFlag(usart->usartx, USART_FLAG_NE) != RESET)
        {
            USART_ClearStatusFlag(usart->usartx, USART_FLAG_NE);
        }
        if (USART_ReadStatusFlag(usart->usartx, USART_FLAG_FE) != RESET)
        {
            USART_ClearStatusFlag(usart->usartx, USART_FLAG_FE);
        }
        if (USART_ReadStatusFlag(usart->usartx, USART_FLAG_PE) != RESET)
        {
            USART_ClearStatusFlag(usart->usartx, USART_FLAG_PE);
        }
        if (USART_ReadStatusFlag(usart->usartx, USART_FLAG_CTS) != RESET)
        {
            USART_ClearStatusFlag(usart->usartx, USART_FLAG_CTS);
        }
        if (USART_ReadStatusFlag(usart->usartx, USART_FLAG_LBD) != RESET)
        {
            USART_ClearStatusFlag(usart->usartx, USART_FLAG_LBD);
        }
#endif /* SOC_SERIES_APM32F0 */
        if (USART_ReadStatusFlag(usart->usartx, USART_FLAG_TXBE) != RESET)
        {
            USART_ClearStatusFlag(usart->usartx, USART_FLAG_TXBE);
        }
    }
}

#if defined(BSP_USING_UART1)
void USART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&(usart_config[UART1_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
void USART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&(usart_config[UART2_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
void USART3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&(usart_config[UART3_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
void UART4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&(usart_config[UART4_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
void UART5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&(usart_config[UART5_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)
void USART6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usart_isr(&(usart_config[UART6_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART6 */

static const struct rt_uart_ops apm32_usart_ops =
{
    .configure = apm32_uart_configure,
    .control = apm32_uart_control,
    .putc = apm32_uart_putc,
    .getc = apm32_uart_getc,
    .dma_transmit = RT_NULL
};

int rt_hw_usart_init(void)
{
    rt_size_t obj_num;
    int index;

    obj_num = sizeof(usart_config) / sizeof(struct apm32_usart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    for (index = 0; index < obj_num; index++)
    {
        usart_config[index].serial.ops = &apm32_usart_ops;
        usart_config[index].serial.config = config;

        /* register USART device */
        result = rt_hw_serial_register(&usart_config[index].serial,
                                       usart_config[index].name,
                                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX
                                       | RT_DEVICE_FLAG_INT_TX, &usart_config[index]);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif /* RT_USING_SERIAL */
