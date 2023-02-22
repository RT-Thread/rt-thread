/*
 * File      : usart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2022, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
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
 * 2022-06-01     THEWON       first version for serialX
 */

#include <rtdevice.h>
#include <rthw.h>
#include <board.h>
#include "drv_usartX.h"

#define UART_ENABLE_IRQ(n)            NVIC_EnableIRQ((n))
#define UART_DISABLE_IRQ(n)           NVIC_DisableIRQ((n))

#ifdef RT_SERIAL_USING_DMA
static void DMA_RX_Configuration(struct rt_serial_device *serial);
static void DMA_TX_Configuration(struct rt_serial_device *serial);
#endif

static rt_err_t n32_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct n32_uart *uart;
    USART_InitType USART_InitStructure;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = rt_container_of(serial, struct n32_uart, serial);

    USART_InitStructure.BaudRate = cfg->baud_rate;

    switch (cfg->data_bits)
    {
    case DATA_BITS_8 :
        USART_InitStructure.WordLength = USART_WL_8B;
    break;
    case DATA_BITS_9 :
        USART_InitStructure.WordLength = USART_WL_9B;
    break;
    default:
        USART_InitStructure.WordLength = USART_WL_8B;
    break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_1 :
        USART_InitStructure.StopBits = USART_STPB_1;
    break;
    case STOP_BITS_2 :
        USART_InitStructure.StopBits = USART_STPB_2;
    break;
    default:
        USART_InitStructure.StopBits = USART_STPB_1;
    break;
    }

    switch (cfg->parity)
    case PARITY_NONE :
        USART_InitStructure.Parity = USART_PE_NO;
    break;
    case PARITY_ODD :
        USART_InitStructure.Parity = USART_PE_ODD;
    break;
    case PARITY_EVEN :
        USART_InitStructure.Parity = USART_PE_EVEN;
    break;
    default:
        USART_InitStructure.Parity = USART_PE_NO;
    break;
    }

    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode = USART_MODE_RX | USART_MODE_TX;
    USART_Init(uart->uart_device, &USART_InitStructure);

    return RT_EOK;
}

static rt_err_t n32_uart_init(struct rt_serial_device *serial)
{
    struct n32_uart *uart;
    USART_InitType USART_InitStructure;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct n32_uart, serial);

    n32_msp_usart_init(uart->uart_device);

    if (n32_uart_configure(serial, &serial->config) != RT_EOK)
    {
        return -RT_ERROR;
    }

    /* Enable USART */
    USART_Enable(uart->uart_device, ENABLE);

    USART_ClrFlag(uart->uart_device, USART_FLAG_TXDE|USART_FLAG_TXC);

    return RT_EOK;
}

static rt_err_t n32_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct n32_uart *uart;
    rt_uint32_t ctrl_arg = (rt_uint32_t)(arg);
    NVIC_InitType NVIC_InitStructure;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct n32_uart, serial);

    switch (cmd) {
    case RT_DEVICE_CTRL_OPEN:
        USART_ConfigInt(uart->uart_device, USART_INT_TXDE, DISABLE);
        USART_ClrIntPendingBit(uart->uart_device, USART_INT_RXDNE);
        USART_ClrIntPendingBit(uart->uart_device, USART_INT_TXDE);
        USART_ClrIntPendingBit(uart->uart_device, USART_INT_TXC);
        /* enable rx irq */
        UART_ENABLE_IRQ(uart->irq);
#ifdef RT_SERIAL_USING_DMA
        uart->dmaTxing = RT_FALSE;
#endif
    break;
    case RT_DEVICE_CTRL_CLOSE:
        /* disable rx irq */
        UART_DISABLE_IRQ(uart->irq);
        USART_ConfigInt(uart->uart_device, USART_INT_RXDNE, DISABLE);
        USART_ConfigInt(uart->uart_device, USART_INT_TXDE, DISABLE);
        USART_ConfigInt(uart->uart_device, USART_INT_TXC, DISABLE);
        USART_ClrIntPendingBit(uart->uart_device, USART_INT_RXDNE);
        USART_ClrIntPendingBit(uart->uart_device, USART_INT_TXDE);
        USART_ClrIntPendingBit(uart->uart_device, USART_INT_TXC);

#ifdef RT_SERIAL_USING_DMA
        NVIC_InitStructure.NVIC_IRQChannel = uart->dma_rx.dma_irq;
        NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
        NVIC_Init(&NVIC_InitStructure);
        DMA_EnableChannel(uart->dma_rx.dma_ch, DISABLE);
        DMA_ConfigInt(uart->dma_rx.dma_ch, DMA_INT_HTX, DISABLE);
        DMA_ConfigInt(uart->dma_rx.dma_ch, DMA_INT_TXC, DISABLE);
        DMA_DeInit(uart->dma_rx.dma_ch);
        NVIC_InitStructure.NVIC_IRQChannel = uart->dma_tx.dma_irq;
        NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
        NVIC_Init(&NVIC_InitStructure);
        DMA_EnableChannel(uart->dma_tx.dma_ch, DISABLE);
        DMA_ConfigInt(uart->dma_tx.dma_ch, DMA_INT_TXC, DISABLE);
        DMA_DeInit(uart->dma_tx.dma_ch);
#endif
    break;
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable interrupt */
        if (ctrl_arg & RT_DEVICE_FLAG_INT_RX) {
            USART_ConfigInt(uart->uart_device, USART_INT_RXDNE, DISABLE);
        }

#ifdef RT_SERIAL_USING_DMA
        /* disable DMA */
        if (ctrl_arg & RT_DEVICE_FLAG_DMA_RX) {
            NVIC_InitStructure.NVIC_IRQChannel = uart->dma_rx.dma_irq;
            NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
            NVIC_Init(&NVIC_InitStructure);
            DMA_ConfigInt(uart->dma_rx.dma_ch, DMA_INT_HTX, DISABLE);
            DMA_ConfigInt(uart->dma_rx.dma_ch, DMA_INT_TXC, DISABLE);
        }
        if(ctrl_arg & RT_DEVICE_FLAG_DMA_TX) {
            NVIC_InitStructure.NVIC_IRQChannel = uart->dma_tx.dma_irq;
            NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
            NVIC_Init(&NVIC_InitStructure);
            DMA_ConfigInt(uart->dma_tx.dma_ch, DMA_INT_TXC, DISABLE);
        }
#endif
    break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable interrupt */
        if (ctrl_arg & RT_DEVICE_FLAG_INT_RX) {
            USART_ConfigInt(uart->uart_device, USART_INT_RXDNE, ENABLE);
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

static int n32_uart_putc(struct rt_serial_device *serial, char c)
{
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct n32_uart, serial);

    while (!(uart->uart_device->STS & USART_FLAG_TXDE));
    uart->uart_device->DAT = c;

    return 1;
}

static int n32_uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct n32_uart, serial);

    ch = -1;
    if (uart->uart_device->STS & USART_FLAG_RXDNE)
    {
        ch = uart->uart_device->DAT & 0xff;
    }

    return ch;
}

static int n32_uart_flush(struct rt_serial_device *serial)
{
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct n32_uart, serial);
    while(!((uart->uart_device->STS & USART_FLAG_TXDE) && (uart->uart_device->STS & USART_FLAG_TXC)));

    return 0;
}

static void n32_start_tx(struct rt_serial_device *serial)
{
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct n32_uart, serial);

    USART_ConfigInt(uart->uart_device, USART_INT_TXDE, ENABLE);
}

static void n32_stop_tx(struct rt_serial_device *serial)
{
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct n32_uart, serial);

    USART_ConfigInt(uart->uart_device, USART_INT_TXDE, DISABLE);
}

#ifdef RT_SERIAL_USING_DMA
static rt_bool_t n32_is_dma_txing(struct rt_serial_device *serial)
{
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct n32_uart, serial);

//    return uart->dmaTxing;  //RT_FALSE;
    return (DMA_GetFlagStatus(uart->dma_tx.dma_flag, uart->dma_tx.dma_module) == SET);
}

static void n32_start_dma_tx(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size)
{
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct n32_uart, serial);

    // TODO: 启用 DMA 发送
    uart->dma_tx.dma_ch->MADDR = (uint32_t)(buf);
    uart->dma_tx.dma_ch->TXNUM = (uint32_t)(size);
    DMA_EnableChannel(uart->dma_tx.dma_ch, ENABLE);

    uart->dmaTxing = RT_TRUE;
}

static void n32_stop_dma_tx(struct rt_serial_device *serial)
{
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct n32_uart, serial);

    // TODO: 禁用 DMA 发送
    DMA_EnableChannel(uart->dma_tx.dma_ch, DISABLE);
    uart->dmaTxing = RT_FALSE;
}
#endif

static void n32_enable_interrupt(struct rt_serial_device *serial)
{
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct n32_uart, serial);

    UART_ENABLE_IRQ(uart->irq);
}

static void n32_disable_interrupt(struct rt_serial_device *serial)
{
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct n32_uart, serial);

    UART_DISABLE_IRQ(uart->irq);
}

#ifdef RT_SERIAL_USING_DMA
/**
 * DMA receive done process. This need add to DMA receive done ISR.
 *
 * @param serial serial device
 */
static void dma_rx_done_isr(struct rt_serial_device *serial)
{
    struct n32_uart *uart;
    rt_size_t dma_cnt;

    uart = rt_container_of(serial, struct n32_uart, serial);

    dma_cnt = RT_SERIAL_DMA_BUFSZ - DMA_GetCurrDataCounter(uart->dma_rx.dma_ch);

    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (dma_cnt << 8));

    DMA_ClearFlag(uart->dma_rx.dma_flag, uart->dma_rx.dma_module);
    DMA_ClrIntPendingBit(uart->dma_rx.dma_flag, uart->dma_rx.dma_module);
}
/**
 * DMA transmit done process. This need add to DMA transmit done ISR.
 *
 * @param serial serial device
 */
static void dma_tx_done_isr(struct rt_serial_device *serial)
{
    struct n32_uart *uart;
    rt_size_t dma_cnt;

    uart = rt_container_of(serial, struct n32_uart, serial);

    dma_cnt = DMA_GetCurrDataCounter(uart->dma_tx.dma_ch);

    if (dma_cnt == 0)
    {
        rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_TX_DMADONE);
    }
    DMA_ClrIntPendingBit(uart->dma_tx.dma_flag, uart->dma_rx.dma_module);
}
#endif

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial)
{
    struct n32_uart *uart;
#ifdef RT_SERIAL_USING_DMA
    rt_size_t dma_cnt;
#endif

    RT_ASSERT(uart != RT_NULL);

    uart = rt_container_of(serial, struct n32_uart, serial);

    if(USART_GetIntStatus(uart->uart_device, USART_INT_RXDNE) != RESET)
    {
        if(USART_GetFlagStatus(uart->uart_device, USART_FLAG_PEF) == RESET)
        {
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        }
        /* clear interrupt */
        USART_ClrIntPendingBit(uart->uart_device, USART_INT_RXDNE);
    }
    if(USART_GetIntStatus(uart->uart_device, USART_INT_TXDE) != RESET)
    {
        if(USART_GetFlagStatus(uart->uart_device, USART_FLAG_PEF) == RESET)
        {
            rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);
        }
        /* clear interrupt */
        USART_ClrIntPendingBit(uart->uart_device, USART_INT_TXDE);
    }

#ifdef RT_SERIAL_USING_DMA
    if(USART_GetIntStatus(uart->uart_device, USART_INT_IDLEF) != RESET)
    {
        /* read a data for clear receive idle interrupt flag */
        USART_ReceiveData(uart->uart_device);

        dma_cnt = RT_SERIAL_DMA_BUFSZ - DMA_GetCurrDataCounter(uart->dma_rx.dma_ch);

        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (dma_cnt << 8));
    }
#endif
    if (USART_GetFlagStatus(uart->uart_device, USART_FLAG_OREF) == SET)
    {
        n32_uart_getc(serial);
    }
}

static const struct rt_uart_ops n32_uart_ops =
{
    .configure = n32_uart_configure,
    .control = n32_uart_control,
    .putc = n32_uart_putc,
    .getc = n32_uart_getc,
    .flush = n32_uart_flush,
    .start_tx = n32_start_tx,
    .stop_tx = n32_stop_tx,
#ifdef RT_SERIAL_USING_DMA
    .is_dma_txing = n32_is_dma_txing,
    .start_dma_tx = n32_start_dma_tx,
    .stop_dma_tx = n32_stop_dma_tx,
#endif
    .enable_interrupt = n32_enable_interrupt,
    .disable_interrupt = n32_disable_interrupt,
};

#if defined(BSP_USING_UART1)
/* UART1 device driver structure */
struct n32_uart uart1 =
{
    .uart_device = USART1,
    .irq = USART1_IRQn,
#ifdef RT_SERIAL_USING_DMA
    .dmaTxing = RT_FALSE,
    .dma_rx = {
        DMA1_CH5,
        DMA1,
        DMA1_FLAG_TC5 | DMA1_FLAG_HT5,
        DMA1_Channel5_IRQn,
    },
    .dma_tx = {
        DMA1_CH4,
        DMA1,
        DMA1_FLAG_TC4,
        DMA1_Channel4_IRQn,
    },
#endif
};

void USART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uart1.serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#ifdef RT_SERIAL_USING_DMA
void DMA1_Channel5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    dma_rx_done_isr(&uart1.serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
void DMA1_Channel4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    dma_tx_done_isr(&uart1.serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
/* UART2 device driver structure */
struct n32_uart uart2 =
{
    .uart_device = USART2,
    .irq = USART2_IRQn,
#ifdef RT_SERIAL_USING_DMA
    .dmaTxing = RT_FALSE,
    .dma_rx = {
        DMA1_CH6,
        DMA1,
        DMA1_FLAG_TC6 | DMA1_FLAG_HT6,
        DMA1_Channel6_IRQn,
    },
    .dma_tx = {
        DMA1_CH7,
        DMA1,
        DMA1_FLAG_TC7,
        DMA1_Channel7_IRQn,
    },
#endif
};

void USART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uart2.serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#ifdef RT_SERIAL_USING_DMA
void DMA1_Channel6_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    dma_rx_done_isr(&uart2.serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
/* UART3 device driver structure */
struct n32_uart uart3 =
{
    .uart_device = USART3,
    .irq = USART3_IRQn,
#ifdef RT_SERIAL_USING_DMA
    .dmaTxing = RT_FALSE,
    .dma_rx = {
        DMA1_CH3,
        DMA1,
        DMA1_FLAG_TC3 | DMA1_FLAG_HT3,
        DMA1_Channel3_IRQn,
    },
    .dma_tx = {
        DMA1_CH2,
        DMA1,
        DMA1_FLAG_TC2,
        DMA1_Channel2_IRQn,
    },
#endif
};

void USART3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uart3.serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#ifdef RT_SERIAL_USING_DMA
void DMA1_Channel3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    dma_rx_done_isr(&uart3.serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
/* UART4 device driver structure */
struct n32_uart uart4 =
{
    .uart_device = UART4,
    .irq = UART4_IRQn,
#ifdef RT_SERIAL_USING_DMA
    .dmaTxing = RT_FALSE,
    .dma_rx = {
        DMA2_CH3,
        DMA2,
        DMA2_FLAG_TC3 | DMA2_FLAG_HT3,
        DMA2_Channel3_IRQn,
    },
    .dma_tx = {
        DMA2_CH5,
        DMA2,
        DMA2_FLAG_TC5,
        DMA2_Channel5_IRQn,
    },
#endif
};

void UART4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&uart4.serial);

    /* leave interrupt */
    rt_interrupt_leave();
}

#ifdef RT_SERIAL_USING_DMA
void DMA2_Channel3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    dma_rx_done_isr(&uart4.serial);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif
#endif /* BSP_USING_UART4 */

static void NVIC_Configuration(struct n32_uart *uart)
{
    NVIC_InitType NVIC_InitStructure;

    /* Enable the USART1 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = uart->irq;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStructure);
}

#ifdef RT_SERIAL_USING_DMA
// TODO: 添加发送 DMA 配置，添加接收 DMA 配置
static void DMA_RX_Configuration(struct rt_serial_device *serial)
{
    DMA_InitType DMA_InitStructure;
    NVIC_InitType NVIC_InitStructure;
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct n32_uart, serial);

    /* enable transmit idle interrupt */
    USART_ConfigInt(uart->uart_device, USART_INT_IDLEF, ENABLE);

    /* DMA clock enable */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA1, ENABLE);
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA2, ENABLE);

    /* rx dma config */
    DMA_InitStructure.PeriphAddr = (uint32_t)&(uart->uart_device->DAT);
    DMA_InitStructure.MemAddr = (uint32_t)(serial->serial_dma_rx);
    DMA_InitStructure.Direction = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize = RT_SERIAL_DMA_BUFSZ;
    DMA_InitStructure.PeriphInc = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_BYTE;
    DMA_InitStructure.MemDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.CircularMode = DMA_MODE_CIRCULAR;
    DMA_InitStructure.Priority = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem = DMA_M2M_DISABLE;

    DMA_DeInit(uart->dma_rx.dma_ch);
    DMA_Init(uart->dma_rx.dma_ch, &DMA_InitStructure);

    DMA_ClearFlag(uart->dma_rx.dma_flag, uart->dma_rx.dma_module);
    DMA_ConfigInt(uart->dma_rx.dma_ch, DMA_INT_HTX, ENABLE);
    DMA_ConfigInt(uart->dma_rx.dma_ch, DMA_INT_TXC, ENABLE);

    USART_EnableDMA(uart->uart_device, USART_DMAREQ_RX, ENABLE);
    DMA_EnableChannel(uart->dma_rx.dma_ch, ENABLE);

    /* rx dma interrupt config */
    NVIC_InitStructure.NVIC_IRQChannel = uart->dma_rx.dma_irq;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
static void DMA_TX_Configuration(struct rt_serial_device *serial)
{
    DMA_InitType DMA_InitStructure;
    NVIC_InitType NVIC_InitStructure;
    struct n32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct n32_uart, serial);

    /* enable transmit idle interrupt */
//    USART_ConfigInt(uart->uart_device, USART_INT_IDLEF, ENABLE);

    /* DMA clock enable */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA1, ENABLE);
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA2, ENABLE);

    /* tx dma config */
    DMA_InitStructure.PeriphAddr = (uint32_t)&(uart->uart_device->DAT);
//    DMA_InitStructure.MemAddr = (uint32_t)(serial->serial_dma_tx);
    DMA_InitStructure.Direction = DMA_DIR_PERIPH_DST;
//    DMA_InitStructure.BufSize = serial->config.bufsz;
    DMA_InitStructure.PeriphInc = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_BYTE;
    DMA_InitStructure.MemDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.CircularMode = DMA_MODE_NORMAL;
    DMA_InitStructure.Priority = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem = DMA_M2M_DISABLE;

    DMA_DeInit(uart->dma_tx.dma_ch);
    DMA_Init(uart->dma_tx.dma_ch, &DMA_InitStructure);

    DMA_ClearFlag(uart->dma_tx.dma_flag, uart->dma_tx.dma_module);
    DMA_ConfigInt(uart->dma_tx.dma_ch, DMA_INT_TXC, ENABLE);
    USART_EnableDMA(uart->uart_device, USART_DMAREQ_TX, ENABLE);
//    DMA_EnableChannel(uart->dma_tx.dma_ch, ENABLE);

    /* rx dma interrupt config */
    NVIC_InitStructure.NVIC_IRQChannel = uart->dma_tx.dma_irq;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
#endif

int rt_hw_usart_init(void)
{
    struct n32_uart *uart;

#if defined(BSP_USING_UART1)
    uart = &uart1;

    uart->serial.ops = &n32_uart_ops;

    NVIC_Configuration(uart);

    /* register UART1 device */
    rt_hw_serial_register(&uart->serial, "uart1",
                          RT_DEVICE_FLAG_RDWR |
                          RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX
#ifdef RT_SERIAL_USING_DMA
                          | RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX
#endif
                          , uart);
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
    uart = &uart2;

    uart->serial.ops    = &n32_uart_ops;

    NVIC_Configuration(uart);

    /* register UART2 device */
    rt_hw_serial_register(&uart->serial, "uart2",
                          RT_DEVICE_FLAG_RDWR |
                          RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX
#ifdef RT_SERIAL_USING_DMA
                          | RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX
#endif
                          , uart);
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
    uart = &uart3;

    uart->serial.ops    = &n32_uart_ops;

    NVIC_Configuration(uart);

    /* register UART3 device */
    rt_hw_serial_register(&uart->serial, "uart3",
                          RT_DEVICE_FLAG_RDWR |
                          RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX
#ifdef RT_SERIAL_USING_DMA
                          | RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX
#endif
                          , uart);
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
    uart = &uart4;

    uart->serial.ops    = &n32_uart_ops;

    NVIC_Configuration(uart);

    /* register UART4 device */
    rt_hw_serial_register(&uart->serial, "uart4",
                          RT_DEVICE_FLAG_RDWR |
                          RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_INT_TX
#ifdef RT_SERIAL_USING_DMA
                          | RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX
#endif
                          , uart);
#endif /* BSP_USING_UART4 */

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_usart_init);

