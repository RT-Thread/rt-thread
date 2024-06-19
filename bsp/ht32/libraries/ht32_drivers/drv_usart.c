/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-08     QT-one       first version
 */

#include "drv_usart.h"

#ifdef RT_USING_SERIAL
#if !defined(BSP_USING_USART0) && !defined(BSP_USING_USART1) && \
    !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1) && \
    !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3)
    #error "Please define at least one BSP_USING_UARTx"
#endif

struct ht32_usart
{
    char *name;
    HT_USART_TypeDef *usart_x;
    IRQn_Type irq;
    struct rt_serial_device serial;
};

enum
{
#ifdef BSP_USING_USART0
    USART0_INDEX,
#endif
#ifdef BSP_USING_USART1
    USART1_INDEX,
#endif
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

};

static struct ht32_usart usart_config[] =
{
#ifdef BSP_USING_USART0
    {
    .name           = BSP_USING_USART0_NAME,
    .usart_x        = HT_USART0,
    .irq            = USART0_IRQn,
    .serial         = RT_NULL
    },
#endif
#ifdef BSP_USING_USART1
    {
    .name           = BSP_USING_USART1_NAME,
    .usart_x        = HT_USART1,
    .irq            = USART1_IRQn,
    .serial         = RT_NULL
    },
#endif
#ifdef BSP_USING_UART0
    {
    .name           = BSP_USING_UART0_NAME,
    .usart_x        = HT_UART0,
    .irq            = UART0_IRQn,
    .serial         = RT_NULL
    },
#endif
#ifdef BSP_USING_UART1
    {
    .name           = BSP_USING_UART1_NAME,
    .usart_x        = HT_UART1,
    .irq            = UART1_IRQn,
    .serial         = RT_NULL
    },
#endif
#ifdef BSP_USING_UART2
    {
    .name           = BSP_USING_UART2_NAME,
    .usart_x        = HT_UART2,
    .irq            = UART0_UART2_IRQn,
    .serial         = RT_NULL
    },
#endif
#ifdef BSP_USING_UART3
    {
    .name           = BSP_USING_UART3_NAME,
    .usart_x        = HT_UART3,
    .irq            = UART1_UART3_IRQn,
    .serial         = RT_NULL
    },
#endif
};

static rt_err_t ht32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{

    CKCU_PeripClockConfig_TypeDef   CKCUClock               = {{0}};
    USART_InitTypeDef               USART_InitStructure     = {0};

    struct ht32_usart *usart_instance = (struct ht32_usart *)serial->parent.user_data;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    CKCUClock.Bit.AFIO = 1;

    if ((usart_instance->usart_x) == HT_UART0)
        CKCUClock.Bit.UART0 = 1;
#if defined(HT_USART0)
    else if ((usart_instance->usart_x) == HT_USART0)
        CKCUClock.Bit.USART0 = 1;
#endif
#if defined(HT_USART1)
    else if ((usart_instance->usart_x) == HT_USART1)
        CKCUClock.Bit.USART1 = 1;
#endif
#if defined(HT_UART1)
    else if ((usart_instance->usart_x) == HT_UART1)
        CKCUClock.Bit.UART1 = 1;
#endif
#if defined(HT_UART2)
    else if ((usart_instance->usart_x) == HT_UART2)
        CKCUClock.Bit.UART2 = 1;
#endif
#if defined(HT_UART3)
    else if ((usart_instance->usart_x) == HT_UART3)
        CKCUClock.Bit.UART3 = 1;
#endif
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    /* UART gpio init */
    ht32_usart_gpio_init((void *)usart_instance->usart_x);

    /* baud rate */
    USART_InitStructure.USART_BaudRate = (cfg->baud_rate);

    /* data width */
    switch (cfg->data_bits)
    {
    case DATA_BITS_7:
        USART_InitStructure.USART_WordLength = USART_WORDLENGTH_7B;
        break;
    case DATA_BITS_8:
        USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
        break;
    case DATA_BITS_9:
        USART_InitStructure.USART_WordLength = USART_WORDLENGTH_9B;
        break;
    default:
        USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
        break;
    }

    /* stop bit */
    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
        break;
    case STOP_BITS_2:
        USART_InitStructure.USART_StopBits = USART_STOPBITS_2;
        break;
    default:
        USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_NONE:
        USART_InitStructure.USART_Parity = USART_PARITY_NO;
        break;
    case PARITY_ODD:
        USART_InitStructure.USART_Parity = USART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        USART_InitStructure.USART_Parity = USART_PARITY_EVEN;
        break;
    default:
        USART_InitStructure.USART_Parity = USART_PARITY_NO;
        break;
    }

    /* UART mode */
    USART_InitStructure.USART_Mode = USART_MODE_NORMAL;
    /* UART init */
    USART_Init((usart_instance->usart_x), &USART_InitStructure);
    /*UART enable */
    USART_TxCmd((usart_instance->usart_x), ENABLE);
    USART_RxCmd((usart_instance->usart_x), ENABLE);

    return RT_EOK;
}

static rt_err_t ht32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct ht32_usart *usart;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct ht32_usart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        NVIC_DisableIRQ(usart->irq);
        USART_IntConfig(usart->usart_x, USART_INT_RXDR, DISABLE);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        NVIC_EnableIRQ(usart->irq);
        USART_IntConfig(usart->usart_x, USART_INT_RXDR, ENABLE);
        break;
    }
    return RT_EOK;
}

static int ht32_putc(struct rt_serial_device *serial, char c)
{
    struct ht32_usart *usart;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct ht32_usart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    while ((usart->usart_x->SR & USART_FLAG_TXC) == 0);
    usart->usart_x->DR = (u8)c;

    return 1;
}

static int ht32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct ht32_usart *usart;

    RT_ASSERT(serial != RT_NULL);
    usart = (struct ht32_usart *) serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    ch = -1;
    if (USART_GetFlagStatus(usart->usart_x, USART_FLAG_RXDR) != RESET)
    {
        ch = USART_ReceiveData(usart->usart_x);
    }
    return ch;
}

static rt_ssize_t ht32_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    return -RT_ERROR;
}

static const struct rt_uart_ops ht32_usart_ops =
{
    .configure = ht32_configure,
    .control = ht32_control,
    .putc = ht32_putc,
    .getc = ht32_getc,
    .dma_transmit = ht32_dma_transmit,
};

int rt_hw_usart_init(void)
{
    rt_size_t obj_num;
    int index;

    obj_num = sizeof(usart_config) / sizeof(struct ht32_usart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    for (index = 0; index < obj_num; index++)
    {
        usart_config[index].serial.ops = &ht32_usart_ops;
        usart_config[index].serial.config = config;

        /* register uart device */
        result = rt_hw_serial_register(&usart_config[index].serial,
                                       usart_config[index].name,
                                       RT_DEVICE_FLAG_RDWR |
                                       RT_DEVICE_FLAG_INT_RX |
                                       RT_DEVICE_FLAG_INT_TX,
                                       &usart_config[index]);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_usart_init);

static void usart_isr(struct rt_serial_device *serial)
{

    struct ht32_usart *usart = (struct ht32_usart *)serial->parent.user_data;
    RT_ASSERT(usart != RT_NULL);

    if ((USART_GetFlagStatus(usart->usart_x, USART_FLAG_RXDR) != RESET) && ((usart->usart_x->IER & USART_INT_RXDR) != RESET))
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
}

#ifdef BSP_USING_USART0
void USART0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    usart_isr(&usart_config[USART0_INDEX].serial);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_USART1
void USART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    usart_isr(&usart_config[USART1_INDEX].serial);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART0
void UART0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    usart_isr(&usart_config[UART0_INDEX].serial);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART1
void UART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    usart_isr(&usart_config[UART1_INDEX].serial);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART2
void UART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    usart_isr(&usart_config[UART2_INDEX].serial);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#ifdef BSP_USING_UART3
void UART3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    usart_isr(&usart_config[UART3_INDEX].serial);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#endif /* RT_USING_SERIAL */
