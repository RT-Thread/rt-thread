/*
 * Copyright (c) 2020-2022, CQ 100ask Development Team
 *
 * Change Logs:
 *   Date           Author          Notes
 * 2022-05-29        Alen       first version
 */

#include "board.h"
#include "drv_uart.h"
#include "drv_config.h"

#ifdef RT_USING_SERIAL

//#define DRV_DEBUG
#define LOG_TAG             "drv.usart"

#if !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && \
    !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5) && !defined(BSP_USING_UART6) && \
    !defined(BSP_USING_UART7) && !defined(BSP_USING_UART8)
#error "Please define at least one BSP_USING_UARTx"
/* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

#define __HAL_UART_GET_FLAG(__HANDLE__, __FLAG__)       (((__HANDLE__)->CSR & (__FLAG__)) == (__FLAG__))
#define __HAL_UART_CLEAR_FLAG(__HANDLE__, __FLAG__)     ((__HANDLE__)->CSR = ~(__FLAG__))
#define __HAL_UART_GET_INT_FLAG(__HANDLE__, __FLAG__)   (((__HANDLE__)->ISR & (__FLAG__)) == (__FLAG__))
#define __HAL_UART_CLEAR_INT_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->ICR &= (__FLAG__))

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
#ifdef BSP_USING_UART7
    UART7_INDEX,
#endif
#ifdef BSP_USING_UART8
    UART8_INDEX,
#endif
#ifdef BSP_USING_LPUART1
    LPUART1_INDEX,
#endif
};

static struct mm32_uart_config uart_config[] =
{
#ifdef BSP_USING_UART1
    UART1_CONFIG,
#endif
#ifdef BSP_USING_UART2
    UART2_CONFIG,
#endif
#ifdef BSP_USING_UART3
    UART3_CONFIG,
#endif
#ifdef BSP_USING_UART4
    UART4_CONFIG,
#endif
#ifdef BSP_USING_UART5
    UART5_CONFIG,
#endif
#ifdef BSP_USING_UART6
    UART6_CONFIG,
#endif
#ifdef BSP_USING_UART7
    UART7_CONFIG,
#endif
#ifdef BSP_USING_UART8
    UART8_CONFIG,
#endif
#ifdef BSP_USING_LPUART1
    LPUART1_CONFIG,
#endif
};

static struct mm32_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

static rt_err_t mm32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct mm32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = rt_container_of(serial, struct mm32_uart, serial);
    uart->handle.ClockFreqHz    = HAL_Get_APB2_Clock();
    uart->handle.BaudRate       = cfg->baud_rate;
    uart->handle.XferMode       = UART_XferMode_RxTx;

    switch (cfg->flowcontrol)
    {
    case RT_SERIAL_FLOWCONTROL_NONE:
        uart->handle.HwFlowControl = UART_HwFlowControl_None;
        break;
    case RT_SERIAL_FLOWCONTROL_CTSRTS:
        uart->handle.HwFlowControl = UART_HwFlowControl_RTS_CTS;
        break;
    default:
        uart->handle.HwFlowControl = UART_HwFlowControl_None;
        break;
    }

    switch (cfg->data_bits)
    {
        case DATA_BITS_5:
            uart->handle.WordLength    = UART_WordLength_5b;
            break;
        case DATA_BITS_6:
            uart->handle.WordLength    = UART_WordLength_6b;
            break;
        case DATA_BITS_7:
            uart->handle.WordLength    = UART_WordLength_7b;
            break;
        case DATA_BITS_8:
            uart->handle.WordLength    = UART_WordLength_8b;
            break;
        default:
            uart->handle.WordLength    = UART_WordLength_8b;
            break;
    }

    switch (cfg->stop_bits)
    {
        case STOP_BITS_1:
            uart->handle.StopBits      = UART_StopBits_1;
            break;
        case STOP_BITS_2:
            uart->handle.StopBits      = UART_StopBits_2;
            break;
        default:
            uart->handle.StopBits      = UART_StopBits_1;
            break;
    }

    switch (cfg->parity)
    {
        case PARITY_NONE:
            uart->handle.Parity        = UART_Parity_None;
            break;
        case PARITY_ODD:
            uart->handle.Parity        = UART_Parity_Odd;
            break;
        case PARITY_EVEN:
            uart->handle.Parity        = UART_Parity_Even;
            break;
        default:
            uart->handle.Parity        = UART_Parity_None;
            break;
    }

#ifdef RT_SERIAL_USING_DMA
    if (!(serial->parent.open_flag & RT_DEVICE_OFLAG_OPEN)) {
        uart->dma_rx.last_index = 0;
    }
#endif
    extern void UART_MspInit(UART_Type *muart);
    UART_MspInit(uart->config->Instance);
    UART_Init(uart->config->Instance, &uart->handle);
    UART_Enable(uart->config->Instance, true);

    return RT_EOK;
}

static rt_err_t mm32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct mm32_uart *uart;
    rt_uint32_t prioritygroup = 0x00U;
#ifdef RT_SERIAL_USING_DMA
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;
#endif

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct mm32_uart, serial);

    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->config->irq_type);

#ifdef RT_SERIAL_USING_DMA
        /* disable DMA */
        if (ctrl_arg == RT_DEVICE_FLAG_DMA_RX)
        {

        }
        else if(ctrl_arg == RT_DEVICE_FLAG_DMA_TX)
        {

        }
#endif
        break;

    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        UART_EnableInterrupts(uart->config->Instance, UART_INT_RX_DONE, true);
        prioritygroup = NVIC_GetPriorityGrouping();
        NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(prioritygroup, 1, 0));
        NVIC_EnableIRQ(uart->config->irq_type);
        break;

#ifdef RT_SERIAL_USING_DMA
    case RT_DEVICE_CTRL_CONFIG:

        break;
#endif

    case RT_DEVICE_CTRL_CLOSE:

        break;

    }
    return RT_EOK;
}

rt_uint32_t mm32_uart_get_mask(rt_uint32_t word_length, rt_uint32_t parity)
{
    rt_uint32_t mask;
    if (word_length == UART_WordLength_8b)
    {
        if (parity == UART_Parity_None)
        {
            mask = 0x00FFU ;
        }
        else
        {
            mask = 0x007FU ;
        }
    }

#ifdef UART_WORDLENGTH_7B
    else if (word_length == UART_WordLength_7b)
    {
        if (parity == UART_Parity_None)
        {
            mask = 0x007FU ;
        }
        else
        {
            mask = 0x003FU ;
        }
    }
    else
    {
        mask = 0x0000U;
    }
#endif
    return mask;
}

static int mm32_putc(struct rt_serial_device *serial, char c)
{
    struct mm32_uart *uart;
    RT_ASSERT(serial != RT_NULL);

    uart = rt_container_of(serial, struct mm32_uart, serial);

    uart->config->Instance->TDR = c;

    while ( 0u == (UART_STATUS_TX_EMPTY & UART_GetStatus(uart->config->Instance)) )
    {}
    return 1;
}

static int mm32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct mm32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct mm32_uart, serial);

    ch = -1;
    if ((UART_STATUS_RX_DONE & UART_GetStatus(uart->config->Instance)) != 0)
    {

        ch = uart->config->Instance->RDR & mm32_uart_get_mask(uart->handle.WordLength, uart->handle.Parity);
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
    struct mm32_uart *uart;
#ifdef RT_SERIAL_USING_DMA
    rt_size_t recv_total_index, recv_len;
    rt_base_t level;
#endif

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct mm32_uart, serial);

    /* UART in mode Receiver -------------------------------------------------*/
    if (   (0u != __HAL_UART_GET_INT_FLAG(uart->config->Instance, UART_INT_RX_DONE))
        && (0u != __HAL_UART_GET_FLAG(uart->config->Instance, UART_STATUS_RX_DONE)) )
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
#ifdef RT_SERIAL_USING_DMA

#endif
    else
    {
        if (__HAL_UART_GET_FLAG(uart->config->Instance, UART_STATUS_RX_DONE) != 0)
        {
            __HAL_UART_CLEAR_FLAG(uart->config->Instance, UART_STATUS_RX_DONE);
        }
        if (__HAL_UART_GET_FLAG(uart->config->Instance, UART_STATUS_TX_DONE) != 0)
        {
            __HAL_UART_CLEAR_FLAG(uart->config->Instance, UART_STATUS_TX_DONE);
        }
        if (__HAL_UART_GET_FLAG(uart->config->Instance, UART_STATUS_TX_FULL) != 0)
        {
            __HAL_UART_CLEAR_FLAG(uart->config->Instance, UART_STATUS_TX_FULL);
        }
        if (__HAL_UART_GET_FLAG(uart->config->Instance, UART_STATUS_TX_EMPTY) != 0)
        {
            __HAL_UART_CLEAR_FLAG(uart->config->Instance, UART_STATUS_TX_EMPTY);
        }

        if (__HAL_UART_GET_INT_FLAG(uart->config->Instance, UART_INT_RX_DONE) != 0)
        {
            __HAL_UART_CLEAR_INT_FLAG(uart->config->Instance, UART_INT_RX_DONE);
        }
        if (__HAL_UART_GET_INT_FLAG(uart->config->Instance, UART_INT_TX_DONE) != 0)
        {
            __HAL_UART_CLEAR_INT_FLAG(uart->config->Instance, UART_INT_TX_DONE);
        }
        if (__HAL_UART_GET_INT_FLAG(uart->config->Instance, UART_INT_TX_EMPTY) != 0)
        {
            __HAL_UART_CLEAR_INT_FLAG(uart->config->Instance, UART_INT_TX_EMPTY);
        }
    }
}

#if defined(BSP_USING_UART1)
void UART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART1_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif


#if defined(BSP_USING_UART2)
void UART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART2_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_UART3)
void UART3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART3_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

static const struct rt_uart_ops mm32_uart_ops =
{
    .configure = mm32_configure,
    .control = mm32_control,
    .putc = mm32_putc,
    .getc = mm32_getc,
    .dma_transmit = RT_NULL
};

int rt_hw_uart_init(void)
{
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct mm32_uart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_err_t result = 0;

    for (int i = 0; i < obj_num; i++)
    {
        /* init UART object */
        uart_obj[i].config = &uart_config[i];
        uart_obj[i].serial.ops    = &mm32_uart_ops;
        uart_obj[i].serial.config = config;

        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial, uart_obj[i].config->name,
                                       RT_DEVICE_FLAG_RDWR
                                       | RT_DEVICE_FLAG_INT_RX
                                       | RT_DEVICE_FLAG_INT_TX
                                       | uart_obj[i].uart_dma_flag
                                       , NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif /* RT_USING_SERIAL */
