/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2010-03-29     Bernard      remove interrupt Tx and DMA Rx mode
 * 2013-05-13     aozima       update for kehong-lingtai.
 * 2015-01-31     armink       make sure the serial transmit complete in putc()
 * 2016-05-13     armink       add DMA Rx mode
 * 2017-01-19     aubr.cool    add interrupt Tx mode
 * 2017-04-13     aubr.cool    correct Rx parity err
 * 2021-08-20     breo.com     first version
 */

#include <rtdevice.h>
#include <rthw.h>
#include <board.h>
#include "drv_usart.h"

#define UART_ENABLE_IRQ(n)            NVIC_EnableIRQ((n))
#define UART_DISABLE_IRQ(n)           NVIC_DisableIRQ((n))

struct n32_uart
{
    USART_Module *uart_device;
    IRQn_Type irq;
    struct n32_uart_dma
    {
        /* dma channel */
        DMA_ChannelType *rx_ch;
        DMA_Module *rx_dma_type;
        /* dma global flag */
        uint32_t rx_gl_flag;
        /* dma irq channel */
        uint8_t rx_irq_ch;
        /* setting receive len */
        rt_size_t setting_recv_len;
        /* last receive index */
        rt_size_t last_recv_index;
    } dma;
};

static void DMA_Configuration(struct rt_serial_device *serial);

static rt_err_t n32_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct n32_uart *uart;
    USART_InitType USART_InitStructure;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = (struct n32_uart *)serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);
    RT_ASSERT((uart->uart_device) != RT_NULL);
    n32_msp_usart_init(uart->uart_device);

    USART_InitStructure.BaudRate = cfg->baud_rate;

    if (cfg->data_bits == DATA_BITS_8)
    {
        USART_InitStructure.WordLength = USART_WL_8B;
    }
    else if (cfg->data_bits == DATA_BITS_9)
    {
        USART_InitStructure.WordLength = USART_WL_9B;
    }

    if (cfg->stop_bits == STOP_BITS_1)
    {
        USART_InitStructure.StopBits = USART_STPB_1;
    }
    else if (cfg->stop_bits == STOP_BITS_2)
    {
        USART_InitStructure.StopBits = USART_STPB_2;
    }

    if (cfg->parity == PARITY_NONE)
    {
        USART_InitStructure.Parity = USART_PE_NO;
    }
    else if (cfg->parity == PARITY_ODD)
    {
        USART_InitStructure.Parity = USART_PE_ODD;
    }
    else if (cfg->parity == PARITY_EVEN)
    {
        USART_InitStructure.Parity = USART_PE_EVEN;
    }

    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode = USART_MODE_RX | USART_MODE_TX;
    USART_Init(uart->uart_device, &USART_InitStructure);

    /* Enable USART */
    USART_Enable(uart->uart_device, ENABLE);

    USART_ClrFlag(uart->uart_device, USART_FLAG_TXDE | USART_FLAG_TXC);

    return RT_EOK;
}

static rt_err_t n32_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct n32_uart *uart;
    rt_uint32_t ctrl_arg = (rt_uint32_t)(arg);

    RT_ASSERT(serial != RT_NULL);
    uart = (struct n32_uart *)serial->parent.user_data;

    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        UART_DISABLE_IRQ(uart->irq);
        /* disable interrupt */
        USART_ConfigInt(uart->uart_device, USART_INT_RXDNE, DISABLE);
        break;
    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        UART_ENABLE_IRQ(uart->irq);
        /* enable interrupt */
        USART_ConfigInt(uart->uart_device, USART_INT_RXDNE, ENABLE);
        break;
    /* USART config */
    case RT_DEVICE_CTRL_CONFIG :
        if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX)
        {
            DMA_Configuration(serial);
        }
        break;
    }
    return RT_EOK;
}

static int n32_uart_putc(struct rt_serial_device *serial, char c)
{
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct n32_uart *)serial->parent.user_data;

    if (serial->parent.open_flag & RT_DEVICE_FLAG_INT_TX)
    {
        if (!(uart->uart_device->STS & USART_FLAG_TXDE))
        {
            USART_ConfigInt(uart->uart_device, USART_INT_TXC, ENABLE);
            return -1;
        }
        uart->uart_device->DAT = c;
        USART_ConfigInt(uart->uart_device, USART_INT_TXC, ENABLE);
    }
    else
    {
        uart->uart_device->DAT = c;
        while (!(uart->uart_device->STS & USART_FLAG_TXC));
    }

    return 1;
}

static int n32_uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct n32_uart *)serial->parent.user_data;

    ch = -1;
    if (uart->uart_device->STS & USART_FLAG_RXDNE)
    {
        ch = uart->uart_device->DAT & 0xff;
    }

    return ch;
}

/**
 * Serial port receive idle process. This need add to uart idle ISR.
 *
 * @param serial serial device
 */
static void dma_uart_rx_idle_isr(struct rt_serial_device *serial)
{
    struct n32_uart *uart = (struct n32_uart *) serial->parent.user_data;
    rt_size_t recv_total_index, recv_len;
    rt_base_t level;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    recv_total_index = uart->dma.setting_recv_len - DMA_GetCurrDataCounter(uart->dma.rx_ch);
    recv_len = recv_total_index - uart->dma.last_recv_index;
    uart->dma.last_recv_index = recv_total_index;
    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    if (recv_len)
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));

    /* read a data for clear receive idle interrupt flag */
    USART_ReceiveData(uart->uart_device);
    DMA_ClearFlag(uart->dma.rx_gl_flag, uart->dma.rx_dma_type);
}

/**
 * DMA receive done process. This need add to DMA receive done ISR.
 *
 * @param serial serial device
 */
static void dma_rx_done_isr(struct rt_serial_device *serial)
{
    struct n32_uart *uart = (struct n32_uart *) serial->parent.user_data;
    rt_size_t recv_len;
    rt_base_t level;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    recv_len = uart->dma.setting_recv_len - uart->dma.last_recv_index;
    /* reset last recv index */
    uart->dma.last_recv_index = 0;
    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    if (recv_len)
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));

    DMA_ClearFlag(uart->dma.rx_gl_flag, uart->dma.rx_dma_type);
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

    if (USART_GetIntStatus(uart->uart_device, USART_INT_RXDNE) != RESET)
    {
        if (USART_GetFlagStatus(uart->uart_device, USART_FLAG_PEF) == RESET)
        {
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        }
        /* clear interrupt */
        USART_ClrIntPendingBit(uart->uart_device, USART_INT_RXDNE);
    }
    if (USART_GetIntStatus(uart->uart_device, USART_INT_IDLEF) != RESET)
    {
        dma_uart_rx_idle_isr(serial);
    }
    if (USART_GetIntStatus(uart->uart_device, USART_INT_TXC) != RESET)
    {
        /* clear interrupt */
        if (serial->parent.open_flag & RT_DEVICE_FLAG_INT_TX)
        {
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);
        }
        USART_ConfigInt(uart->uart_device, USART_INT_TXC, DISABLE);
        USART_ClrIntPendingBit(uart->uart_device, USART_INT_TXC);
    }
    if (USART_GetFlagStatus(uart->uart_device, USART_FLAG_OREF) == SET)
    {
        n32_uart_getc(serial);
    }
}

static const struct rt_uart_ops n32_uart_ops =
{
    n32_uart_configure,
    n32_uart_control,
    n32_uart_putc,
    n32_uart_getc,
};

#if defined(BSP_USING_UART1)
/* UART1 device driver structure */
struct n32_uart uart1 =
{
    USART1,
    USART1_IRQn,
    {
        DMA1_CH5,
        DMA1,
        DMA1_FLAG_GL5,
        DMA1_Channel5_IRQn,
        0,
    },
};
struct rt_serial_device serial1;

void USART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial1);

    /* leave interrupt */
    rt_interrupt_leave();
}

void DMA1_Channel5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    dma_rx_done_isr(&serial1);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
/* UART2 device driver structure */
struct n32_uart uart2 =
{
    USART2,
    USART2_IRQn,
    {
        DMA1_CH6,
        DMA1,
        DMA1_FLAG_GL6,
        DMA1_Channel6_IRQn,
        0,
    },
};
struct rt_serial_device serial2;

void USART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial2);

    /* leave interrupt */
    rt_interrupt_leave();
}

void DMA1_Channel6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    dma_rx_done_isr(&serial2);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
/* UART3 device driver structure */
struct n32_uart uart3 =
{
    USART3,
    USART3_IRQn,
    {
        DMA1_CH3,
        DMA1,
        DMA1_FLAG_GL3,
        DMA1_Channel3_IRQn,
        0,
    },
};
struct rt_serial_device serial3;

void USART3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial3);

    /* leave interrupt */
    rt_interrupt_leave();
}

void DMA1_Channel3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    dma_rx_done_isr(&serial3);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
/* UART4 device driver structure */
struct n32_uart uart4 =
{
    UART4,
    UART4_IRQn,
    {
        DMA2_CH3,
        DMA2,
        DMA2_FLAG_GL3,
        DMA2_Channel3_IRQn,
        0,
    },
};
struct rt_serial_device serial4;

void UART4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial4);

    /* leave interrupt */
    rt_interrupt_leave();
}

void DMA2_Channel3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    dma_rx_done_isr(&serial4);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
/* UART5 device driver structure */
struct n32_uart uart5 =
{
    UART5,
    UART5_IRQn,
    {
        DMA1_CH8,
        DMA1,
        DMA1_FLAG_GL8,
        DMA1_Channel8_IRQn,
        0,
    },
};
struct rt_serial_device serial5;

void UART5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    uart_isr(&serial5);
    /* leave interrupt */
    rt_interrupt_leave();
}

void DMA1_Channel8_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    dma_rx_done_isr(&serial5);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)
/* UART6 device driver structure */
struct n32_uart uart6 =
{
    UART6,
    UART6_IRQn,
    {
        DMA2_CH1,
        DMA2,
        DMA2_FLAG_GL1,
        DMA2_Channel1_IRQn,
        0,
    },
};
struct rt_serial_device serial6;

void UART6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    uart_isr(&serial6);
    /* leave interrupt */
    rt_interrupt_leave();
}

void DMA2_Channel1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    dma_rx_done_isr(&serial6);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_UART7)
/* UART7 device driver structure */
struct n32_uart uart7 =
{
    UART7,
    UART7_IRQn,
    {
        DMA2_CH6,
        DMA2,
        DMA2_FLAG_GL6,
        DMA2_Channel6_IRQn,
        0,
    },
};
struct rt_serial_device serial7;

void UART7_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    uart_isr(&serial7);
    /* leave interrupt */
    rt_interrupt_leave();
}

void DMA2_Channel6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    dma_rx_done_isr(&serial7);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART7 */

static void NVIC_Configuration(struct n32_uart *uart)
{
    NVIC_InitType NVIC_InitStructure;

    /* Enable the USART1 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = uart->irq;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void DMA_Configuration(struct rt_serial_device *serial)
{
    struct n32_uart *uart = (struct n32_uart *) serial->parent.user_data;
    struct rt_serial_rx_fifo *rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
    DMA_InitType DMA_InitStructure;
    NVIC_InitType NVIC_InitStructure;

    uart->dma.setting_recv_len = serial->config.bufsz;

    /* enable transmit idle interrupt */
    USART_ConfigInt(uart->uart_device, USART_INT_IDLEF, ENABLE);

    /* DMA clock enable */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA1, ENABLE);
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA2, ENABLE);

    /* rx dma config */
    DMA_DeInit(uart->dma.rx_ch);
    DMA_InitStructure.PeriphAddr = (uint32_t) & (uart->uart_device->DAT);
    DMA_InitStructure.MemAddr = (uint32_t)(rx_fifo->buffer);
    DMA_InitStructure.Direction = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize = serial->config.bufsz;
    DMA_InitStructure.PeriphInc = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_BYTE;
    DMA_InitStructure.MemDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.CircularMode = DMA_MODE_CIRCULAR;
    DMA_InitStructure.Priority = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem = DMA_M2M_DISABLE;
    DMA_Init(uart->dma.rx_ch, &DMA_InitStructure);
    DMA_ClearFlag(uart->dma.rx_gl_flag, uart->dma.rx_dma_type);
    DMA_ConfigInt(uart->dma.rx_ch, DMA_INT_TXC, ENABLE);
    USART_EnableDMA(uart->uart_device, USART_DMAREQ_RX, ENABLE);
    DMA_EnableChannel(uart->dma.rx_ch, ENABLE);

    /* rx dma interrupt config */
    NVIC_InitStructure.NVIC_IRQChannel = uart->dma.rx_irq_ch;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

int rt_hw_usart_init(void)
{
    struct n32_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#if defined(BSP_USING_UART1)
    uart = &uart1;
    config.baud_rate = BAUD_RATE_115200;

    serial1.ops    = &n32_uart_ops;
    serial1.config = config;

    NVIC_Configuration(uart);

    /* register UART1 device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          RT_DEVICE_FLAG_INT_TX |   RT_DEVICE_FLAG_DMA_RX,
                          uart);
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
    uart = &uart2;

    config.baud_rate = BAUD_RATE_115200;
    serial2.ops    = &n32_uart_ops;
    serial2.config = config;

    NVIC_Configuration(uart);

    /* register UART2 device */
    rt_hw_serial_register(&serial2, "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          RT_DEVICE_FLAG_INT_TX |   RT_DEVICE_FLAG_DMA_RX,
                          uart);
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
    uart = &uart3;

    config.baud_rate = BAUD_RATE_115200;

    serial3.ops    = &n32_uart_ops;
    serial3.config = config;

    NVIC_Configuration(uart);

    /* register UART3 device */
    rt_hw_serial_register(&serial3, "uart3",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_DMA_RX,
                          uart);
#endif /* BSP_USING_UART3 */

    #if defined(BSP_USING_UART4)
    uart = &uart4;
    config.baud_rate = BAUD_RATE_115200;
    serial4.ops    = &n32_uart_ops;
    serial4.config = config;
    NVIC_Configuration(uart);
    /* register UART4 device */
    rt_hw_serial_register(&serial4, "uart4",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_DMA_RX,
                          uart);
    #endif /* BSP_USING_UART4 */

    #if defined(BSP_USING_UART5)
    uart = &uart5;
    config.baud_rate = BAUD_RATE_115200;
    serial5.ops    = &n32_uart_ops;
    serial5.config = config;
    NVIC_Configuration(uart);
    /* register UART5 device */
    rt_hw_serial_register(&serial5, "uart5",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_DMA_RX,
                          uart);
    #endif /* BSP_USING_UART5 */

    #if defined(BSP_USING_UART6)
    uart = &uart6;
    config.baud_rate = BAUD_RATE_115200;
    serial6.ops    = &n32_uart_ops;
    serial6.config = config;
    NVIC_Configuration(uart);
    /* register UART6 device */
    rt_hw_serial_register(&serial6, "uart6",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_DMA_RX,
                          uart);
    #endif /* BSP_USING_UART6 */

    #if defined(BSP_USING_UART7)
    uart = &uart7;
    config.baud_rate = BAUD_RATE_115200;
    serial7.ops    = &n32_uart_ops;
    serial7.config = config;
    NVIC_Configuration(uart);
    /* register UART7 device */
    rt_hw_serial_register(&serial7, "uart7",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_DMA_RX,
                          uart);
    #endif /* BSP_USING_UART7 */


    return RT_EOK;
}

