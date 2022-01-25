/*
 * Copyright (C) 2021, lizhengyang
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2021-09-02      lizhengyang     first version
 */
#include <rtdevice.h>
#include <rthw.h>
#include "drv_usart.h"
#include "board_config.h"


#ifdef RT_USING_SERIAL
#if !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && !defined(BSP_USING_UART4)
    #error "Please define at least one BSP_USING_UARTx"
    /* UART instance can be selected at menuconfig -> Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable UART */
#endif

/* HC32 config uart class */
struct hc32_uart_config
{
    struct hc32_irq_config  rxerr_irq_config;
    struct hc32_irq_config  rx_irq_config;
};
/* HC32 UART index */
struct uart_index
{
    rt_uint32_t      index;
    M4_USART_TypeDef *Instance;
};

/* HC32 UART irq handler */
struct uart_irq_handler
{
    void (*rxerr_irq_handler)(void);
    void (*rx_irq_handler)(void);
};

/* HC32 uart dirver class */
struct hc32_uart
{
    const char *name;
    M4_USART_TypeDef *Instance;
    struct hc32_uart_config config;
    struct rt_serial_device serial;
};
#ifndef UART_CONFIG
#define UART_CONFIG(uart_name, USART)                                          \
    {                                                                          \
        .name = uart_name,                                                     \
        .Instance = M4_##USART,                                                \
         .config = {                                                           \
            .rxerr_irq_config = {                                              \
                .irq = USART##_RXERR_INT_IRQn,                                 \
                .irq_prio = USART##_RXERR_INT_PRIO,                            \
                .int_src = INT_##USART##_EI,                                   \
            },                                                                 \
            .rx_irq_config = {                                                 \
                .irq = USART##_RX_INT_IRQn,                                    \
                .irq_prio = USART##_RX_INT_PRIO,                               \
                .int_src = INT_##USART##_RI,                                   \
            },                                                                 \
         },                                                                    \
    }
#endif /* UART_CONFIG */


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
    UART_INDEX_MAX,
};

static const struct uart_index uart_map[] =
{
#ifdef BSP_USING_UART1
    {UART1_INDEX, M4_USART1},
#endif
#ifdef BSP_USING_UART2
    {UART2_INDEX, M4_USART2},
#endif
#ifdef BSP_USING_UART3
    {UART3_INDEX, M4_USART3},
#endif
#ifdef BSP_USING_UART4
    {UART4_INDEX, M4_USART4},
#endif
};
static const struct uart_index uart_clock_map[] =
{
#ifdef BSP_USING_UART1
    {0, M4_USART1},
#endif
#ifdef BSP_USING_UART2
    {1, M4_USART2},
#endif
#ifdef BSP_USING_UART3
    {2, M4_USART3},
#endif
#ifdef BSP_USING_UART4
    {3, M4_USART4},
#endif
};

static struct hc32_uart uart_obj[] =
{
#ifdef BSP_USING_UART1
    UART_CONFIG("uart1", USART1),
#endif
#ifdef BSP_USING_UART2
    UART_CONFIG("uart2", USART2),
#endif
#ifdef BSP_USING_UART3
    UART_CONFIG("uart3", USART3),
#endif
#ifdef BSP_USING_UART4
    UART_CONFIG("uart4", USART4),
#endif
};

static const struct uart_irq_handler uart_irq_handlers[sizeof(uart_obj) / sizeof(uart_obj[0])];

static uint32_t hc32_get_uart_index(M4_USART_TypeDef *Instance)
{
    uint32_t index = UART_INDEX_MAX;

    for (uint8_t i = 0U; i < ARRAY_SZ(uart_map); i++)
    {
        if (uart_map[i].Instance == Instance)
        {
            index = uart_map[i].index;
            RT_ASSERT(index < UART_INDEX_MAX)
            break;
        }
    }

    return index;
}
static uint32_t hc32_get_uart_clock_index(M4_USART_TypeDef *Instance)
{
    uint32_t index = 4;

    for (uint8_t i = 0U; i < ARRAY_SZ(uart_clock_map); i++)
    {
        if (uart_clock_map[i].Instance == Instance)
        {
            index = uart_clock_map[i].index;
            RT_ASSERT(index < 4)
            break;
        }
    }

    return index;
}
static uint32_t hc32_get_usart_fcg(M4_USART_TypeDef *Instance)
{
    return (PWC_FCG1_PERIPH_USART1 << hc32_get_uart_clock_index(Instance));
}

static rt_err_t hc32_configure(struct rt_serial_device *serial,
                               struct serial_configure *cfg)
{
    struct hc32_uart *uart;
    stc_usart_uart_init_t uart_init;

    RT_ASSERT(RT_NULL != cfg);
    RT_ASSERT(RT_NULL != serial);

    uart = rt_container_of(serial, struct hc32_uart, serial);
    RT_ASSERT(RT_NULL != uart->Instance);

    /* Configure USART initialization structure */
    MEM_ZERO_STRUCT(uart_init);
    uart_init.enSampleMode = UsartSampleBit8;
    uart_init.enSampleMode = UsartSampleBit8;
    uart_init.enDetectMode = UsartStartBitFallEdge;
    uart_init.enHwFlow = UsartRtsEnable;
    uart_init.enClkMode = UsartIntClkCkNoOutput;
    uart_init.enClkDiv = UsartClkDiv_1;
    if (BIT_ORDER_LSB == cfg->bit_order)
    {
        uart_init.enDirection = UsartDataLsbFirst;
    }
    else
    {
        uart_init.enDirection = UsartDataMsbFirst;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        uart_init.enStopBit = UsartOneStopBit;
        break;
    case STOP_BITS_2:
        uart_init.enStopBit = UsartTwoStopBit;
        break;
    default:
        uart_init.enStopBit = UsartOneStopBit;
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_NONE:
        uart_init.enParity = UsartParityNone;
        break;
    case PARITY_EVEN:
        uart_init.enParity = UsartParityEven;
        break;
    case PARITY_ODD:
        uart_init.enParity = UsartParityOdd;
        break;
    default:
        uart_init.enParity = UsartParityNone;
        break;
    }

    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        uart_init.enDataLength = UsartDataBits8;
        break;
    default:
        return -RT_ERROR;
    }

    /* Enable USART clock */
    PWC_Fcg1PeriphClockCmd(hc32_get_usart_fcg(uart->Instance), Enable);

    rt_err_t rt_hw_board_uart_init(M4_USART_TypeDef * USARTx);
    if (RT_EOK != rt_hw_board_uart_init(uart->Instance))
    {
        return -RT_ERROR;
    }

    USART_DeInit(uart->Instance);
    if (Error == USART_UART_Init(uart->Instance, &uart_init))
    {
        return -RT_ERROR;
    }
    USART_SetBaudrate(uart->Instance,  cfg->baud_rate);
    if (RT_EOK != USART_SetBaudrate(uart->Instance, cfg->baud_rate))
    {
        return -RT_ERROR;
    }
    /* Register RX error interrupt */
    hc32_install_irq_handler(&uart->config.rxerr_irq_config,
                             uart_irq_handlers[hc32_get_uart_index(uart->Instance)].rxerr_irq_handler,
                             RT_TRUE);

    USART_FuncCmd(uart->Instance, UsartRxInt, Enable);

    if ((serial->parent.flag & RT_DEVICE_FLAG_RDWR) || \
            (serial->parent.flag & RT_DEVICE_FLAG_RDONLY))
    {
        USART_FuncCmd(uart->Instance, UsartRx, Enable);
    }

    if ((serial->parent.flag & RT_DEVICE_FLAG_RDWR) || \
            (serial->parent.flag & RT_DEVICE_FLAG_WRONLY))
    {
        USART_FuncCmd(uart->Instance, UsartTx, Enable);
    }

    return RT_EOK;
}


static rt_err_t hc32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct hc32_uart *uart;
    uint32_t uart_index;
    RT_ASSERT(RT_NULL != serial);
    uart = rt_container_of(serial, struct hc32_uart, serial);
    RT_ASSERT(RT_NULL != uart->Instance);

    switch (cmd)
    {
    /* Disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        /* Disable RX irq */
        NVIC_DisableIRQ(uart->config.rx_irq_config.irq);
        enIrqResign(uart->config.rx_irq_config.irq);
        break;

    /* Enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        uart_index = hc32_get_uart_index(uart->Instance);
        /* Install RX irq handler */
        hc32_install_irq_handler(&uart->config.rx_irq_config,
                                 uart_irq_handlers[uart_index].rx_irq_handler,
                                 RT_TRUE);
        break;
    }
    return RT_EOK;
}

static int hc32_putc(struct rt_serial_device *serial, char c)
{
    struct hc32_uart *uart;

    RT_ASSERT(RT_NULL != serial);

    uart = rt_container_of(serial, struct hc32_uart, serial);
    RT_ASSERT(RT_NULL != uart->Instance);

    USART_SendData(uart->Instance, c);
    /* Polling mode. */
    while (USART_GetStatus(uart->Instance, UsartTxEmpty) != Set);
    return 1;
}

static int hc32_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    struct hc32_uart *uart;

    RT_ASSERT(RT_NULL != serial);

    uart = rt_container_of(serial, struct hc32_uart, serial);
    RT_ASSERT(RT_NULL != uart->Instance);

    if (Set == USART_GetStatus(uart->Instance, UsartRxNoEmpty))
    {
        ch = (rt_uint8_t)USART_RecData(uart->Instance);
    }

    return ch;
}

static void hc32_uart_rx_irq_handler(struct hc32_uart *uart)
{
    RT_ASSERT(RT_NULL != uart);

    rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_RX_IND);
}

static void hc32_uart_rxerr_irq_handler(struct hc32_uart *uart)
{
    RT_ASSERT(RT_NULL != uart);
    RT_ASSERT(RT_NULL != uart->Instance);

    if (Set == USART_GetStatus(uart->Instance, UsartParityErr) ||  \
            Set == USART_GetStatus(uart->Instance, UsartFrameErr))
    {
        USART_RecData(uart->Instance);
    }
    USART_ClearStatus(uart->Instance, UsartParityErr);
    USART_ClearStatus(uart->Instance, UsartFrameErr);
    USART_ClearStatus(uart->Instance, UsartOverrunErr);
}
#if defined(BSP_USING_UART1)
static void hc32_uart1_rx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rx_irq_handler(&uart_obj[UART1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart1_rxerr_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxerr_irq_handler(&uart_obj[UART1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
static void hc32_uart2_rx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rx_irq_handler(&uart_obj[UART2_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
static void hc32_uart2_rxerr_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxerr_irq_handler(&uart_obj[UART2_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
static void hc32_uart3_rx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rx_irq_handler(&uart_obj[UART3_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart3_rxerr_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxerr_irq_handler(&uart_obj[UART3_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
static void hc32_uart4_rx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rx_irq_handler(&uart_obj[UART4_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
static void hc32_uart4_rxerr_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxerr_irq_handler(&uart_obj[UART4_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART4 */

static const struct uart_irq_handler uart_irq_handlers[] =
{
#ifdef BSP_USING_UART1
    {hc32_uart1_rxerr_irq_handler, hc32_uart1_rx_irq_handler},
#endif
#ifdef BSP_USING_UART2
    {hc32_uart2_rxerr_irq_handler, hc32_uart2_rx_irq_handler},
#endif
#ifdef BSP_USING_UART3
    {hc32_uart3_rxerr_irq_handler, hc32_uart3_rx_irq_handler},
#endif
#ifdef BSP_USING_UART4
    {hc32_uart4_rxerr_irq_handler, hc32_uart4_rx_irq_handler},
#endif
};
static const struct rt_uart_ops hc32_uart_ops =
{
    .configure = hc32_configure,
    .control = hc32_control,
    .putc = hc32_putc,
    .getc = hc32_getc,
};

int hc32_hw_uart_init(void)
{
    rt_err_t result = RT_EOK;
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct hc32_uart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    for (int i = 0; i < obj_num; i++)
    {
        /* init UART object */
        uart_obj[i].serial.ops    = &hc32_uart_ops;
        uart_obj[i].serial.config = config;

        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial,
                                       uart_obj[i].name,
                                       (RT_DEVICE_FLAG_RDWR   |
                                        RT_DEVICE_FLAG_INT_RX |
                                        RT_DEVICE_FLAG_INT_TX),
                                       &uart_obj[i]);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}
INIT_BOARD_EXPORT(hc32_hw_uart_init);

#endif


















