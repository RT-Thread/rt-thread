/*
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-30     CDT          first version
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtdevice.h>
#include <rthw.h>

#include "drv_usart.h"
#include "board_config.h"

#ifdef RT_USING_SERIAL

#if !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && \
    !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5) && !defined(BSP_USING_UART6) && \
    !defined(BSP_USING_UART7) && !defined(BSP_USING_UART8) && !defined(BSP_USING_UART9) && \
    !defined(BSP_USING_UART10)
#error "Please define at least one BSP_USING_UARTx"
/* UART instance can be selected at menuconfig -> Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable UART */
#endif

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/* HC32 config Rx timeout */
struct hc32_uart_rxto
{
    M4_TMR0_TypeDef *TMR0_Instance;
    rt_uint32_t     channel;

    rt_size_t       timeout_bits;

    struct hc32_irq_config irq_config;
};

/* HC32 config uart class */
struct hc32_uart_config
{
    struct hc32_irq_config  rxerr_irq_config;

    struct hc32_irq_config  rx_irq_config;

    struct hc32_irq_config  tx_irq_config;

#ifdef RT_SERIAL_USING_DMA
    struct hc32_uart_rxto   *rx_timeout;
    struct dma_config       *dma_rx;

    struct dma_config       *dma_tx;
#endif
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
    void (*tx_irq_handler)(void);
    void (*tc_irq_handler)(void);
    void (*rxto_irq_handler)(void);
    void (*dma_rx_irq_handler)(void);
};

/* HC32 uart dirver class */
struct hc32_uart
{
    struct rt_serial_device serial;

    const char *name;

    M4_USART_TypeDef *Instance;

    struct hc32_uart_config config;

#ifdef RT_SERIAL_USING_DMA
    rt_size_t   dma_rx_last_index;
#endif

    rt_uint16_t uart_dma_flag;
};

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
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
            .tx_irq_config = {                                                 \
                .irq = USART##_TX_INT_IRQn,                                    \
                .irq_prio = USART##_TX_INT_PRIO,                               \
                .int_src = INT_##USART##_TI,                                   \
            },                                                                 \
         },                                                                    \
    }
#endif /* UART_CONFIG */

#ifndef UART_RXTO_CONFIG
#define UART_RXTO_CONFIG(USART)                                                \
    {                                                                          \
        .TMR0_Instance = USART##_RXTO_TMR0_UNIT,                               \
        .channel  = USART##_RXTO_TMR0_CH,                                      \
        .timeout_bits = 20UL,                                                  \
        .irq_config = {                                                        \
            .irq      = USART##_RXTO_INT_IRQn,                                 \
            .irq_prio = USART##_RXTO_INT_PRIO,                                 \
            .int_src  = INT_##USART##_RTO,                                     \
        }                                                                      \
    }
#endif /* UART_RXTO_CONFIG */

#ifndef UART_DMA_RX_CONFIG
#define UART_DMA_RX_CONFIG(USART)                                              \
    {                                                                          \
        .Instance = USART##_RX_DMA_UNIT,                                       \
        .channel  = USART##_RX_DMA_CH,                                         \
        .trigger_evt_src = EVT_##USART##_RI,                                   \
        .irq_config = {                                                        \
            .irq      = USART##_RX_DMA_INT_IRQn,                               \
            .irq_prio = USART##_RX_DMA_INT_PRIO,                               \
            .int_src  = USART##_RX_DMA_INT_SRC,                                \
        }                                                                      \
    }
#endif /* UART_DMA_RX_CONFIG */

#ifndef UART_DMA_TX_CONFIG
#define UART_DMA_TX_CONFIG(USART)                                              \
    {                                                                          \
        .Instance = USART##_TX_DMA_UNIT,                                       \
        .channel  = USART##_TX_DMA_CH,                                         \
        .trigger_evt_src = EVT_##USART##_TI,                                   \
        .irq_config = {                                                        \
            .irq      = USART##_TC_INT_IRQn,                                   \
            .irq_prio = USART##_TC_INT_PRIO,                                   \
            .int_src  = INT_##USART##_TCI,                                     \
        }                                                                      \
    }
#endif /* UART_DMA_TX_CONFIG */

#define DMA_CH_REG(reg_base, ch)                                               \
    (*(uint32_t *)((uint32_t)(&(reg_base)) + ((ch) * 0x40UL)))

#define DMA_TRANS_CNT(unit, ch)                                                \
    (READ_REG32(DMA_CH_REG((unit)->MONDTCTL0, (ch))) >> DMA_DTCTL_CNT_POS)

#define USART_TCI_ENABLE(unit)                                                 \
    SET_REG32_BIT(unit->CR1, USART_INT_TC)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
#ifdef RT_SERIAL_USING_DMA
static void hc32_dma_config(struct rt_serial_device *serial, rt_ubase_t flag);
#endif

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
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
#ifdef BSP_USING_UART9
    UART9_INDEX,
#endif
#ifdef BSP_USING_UART10
    UART10_INDEX,
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
#ifdef BSP_USING_UART5
    {UART5_INDEX, M4_USART5},
#endif
#ifdef BSP_USING_UART6
    {UART6_INDEX, M4_USART6},
#endif
#ifdef BSP_USING_UART7
    {UART7_INDEX, M4_USART7},
#endif
#ifdef BSP_USING_UART8
    {UART8_INDEX, M4_USART8},
#endif
#ifdef BSP_USING_UART9
    {UART9_INDEX, M4_USART9},
#endif
#ifdef BSP_USING_UART10
    {UART10_INDEX, M4_USART10},
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
#ifdef BSP_USING_UART5
    UART_CONFIG("uart5", USART5),
#endif
#ifdef BSP_USING_UART6
    UART_CONFIG("uart6", USART6),
#endif
#ifdef BSP_USING_UART7
    UART_CONFIG("uart7", USART7),
#endif
#ifdef BSP_USING_UART8
    UART_CONFIG("uart8", USART8),
#endif
#ifdef BSP_USING_UART9
    UART_CONFIG("uart9", USART9),
#endif
#ifdef BSP_USING_UART10
    UART_CONFIG("uart10", USART10),
#endif
};

static const struct uart_irq_handler uart_irq_handlers[sizeof(uart_obj) / sizeof(uart_obj[0])];

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

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

static uint32_t hc32_get_usart_fcg(M4_USART_TypeDef *Instance)
{
    return (PWC_FCG3_USART1 << hc32_get_uart_index(Instance));
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
    USART_UartStructInit(&uart_init);
    uart_init.u32OversamplingBits = USART_OVERSAMPLING_8BIT;
    uart_init.u32Baudrate = cfg->baud_rate;
    if ((M4_USART1 == uart->Instance) || \
        (M4_USART2 == uart->Instance) || \
        (M4_USART6 == uart->Instance) || \
        (M4_USART7 == uart->Instance))
    {
        uart_init.u32ClkMode = USART_INTERNCLK_OUTPUT;
    }

    if(BIT_ORDER_LSB == cfg->bit_order)
    {
        uart_init.u32BitDirection = USART_LSB;
    }
    else
    {
        uart_init.u32BitDirection = USART_MSB;
    }

    switch(cfg->stop_bits)
    {
    case STOP_BITS_1:
        uart_init.u32StopBit = USART_STOPBIT_1BIT;
        break;
    case STOP_BITS_2:
        uart_init.u32StopBit = USART_STOPBIT_2BIT;
        break;
    default:
        uart_init.u32StopBit = USART_STOPBIT_1BIT;
        break;
    }

    switch(cfg->parity)
    {
    case PARITY_NONE:
        uart_init.u32Parity = USART_PARITY_NONE;
        break;
    case PARITY_EVEN:
        uart_init.u32Parity = USART_PARITY_EVEN;
        break;
    case PARITY_ODD:
        uart_init.u32Parity = USART_PARITY_ODD;
        break;
    default:
        uart_init.u32Parity = USART_PARITY_NONE;
        break;
    }

    switch(cfg->data_bits)
    {
    case DATA_BITS_8:
        uart_init.u32DataWidth = USART_DATA_LENGTH_8BIT;
        break;
    default:
        return -RT_ERROR;
    }

    /* Enable USART clock */
    PWC_Fcg3PeriphClockCmd(hc32_get_usart_fcg(uart->Instance), Enable);

    rt_err_t rt_hw_board_uart_init(M4_USART_TypeDef *USARTx);
    if (RT_EOK != rt_hw_board_uart_init(uart->Instance))
    {
        return -RT_ERROR;
    }

    USART_DeInit(uart->Instance);
    if (Error == USART_UartInit(uart->Instance, &uart_init))
    {
        return -RT_ERROR;
    }

    /* Register RX error interrupt */
    hc32_install_irq_handler(&uart->config.rxerr_irq_config,
            uart_irq_handlers[hc32_get_uart_index(uart->Instance)].rxerr_irq_handler,
            RT_TRUE);

    USART_FuncCmd(uart->Instance, USART_INT_RX, Enable);

    if ((serial->parent.flag & RT_DEVICE_FLAG_RDWR) || \
        (serial->parent.flag & RT_DEVICE_FLAG_RDONLY))
    {
        USART_FuncCmd(uart->Instance, USART_RX, Enable);
    }

    if ((serial->parent.flag & RT_DEVICE_FLAG_RDWR) || \
        (serial->parent.flag & RT_DEVICE_FLAG_WRONLY))
    {
        USART_FuncCmd(uart->Instance, USART_TX, Enable);
    }

    return RT_EOK;
}

static rt_err_t hc32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct hc32_uart *uart;
    uint32_t uart_index;
#ifdef RT_SERIAL_USING_DMA
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;
#endif

    RT_ASSERT(RT_NULL != serial);

    uart = rt_container_of(serial, struct hc32_uart, serial);
    RT_ASSERT(RT_NULL != uart->Instance);

    switch (cmd)
    {
    /* Disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        if(RT_DEVICE_FLAG_INT_RX == ctrl_arg)
        {
            /* Disable RX irq */
            NVIC_DisableIRQ(uart->config.rx_irq_config.irq);
            INTC_IrqSignOut(uart->config.rx_irq_config.irq);
        }
        else
        {
            /* Disable TX irq */
            NVIC_DisableIRQ(uart->config.tx_irq_config.irq);
            USART_FuncCmd(uart->Instance, USART_INT_TC, Disable);
            INTC_IrqSignOut(uart->config.tx_irq_config.irq);
        }
        break;

        /* Enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        uart_index = hc32_get_uart_index(uart->Instance);

        if(RT_DEVICE_FLAG_INT_RX == ctrl_arg)
        {
            /* Install RX irq handler */
            hc32_install_irq_handler(&uart->config.rx_irq_config,
                            uart_irq_handlers[uart_index].rx_irq_handler,
                            RT_TRUE);
        }
        else
        {
            /* Enable TX interrupt */
            USART_FuncCmd(uart->Instance, USART_INT_TXE, Enable);

            /* Install TX irq handler */
            hc32_install_irq_handler(&uart->config.tx_irq_config,
                            uart_irq_handlers[uart_index].tx_irq_handler,
                            RT_TRUE);
        }
        break;

#ifdef RT_SERIAL_USING_DMA
    case RT_DEVICE_CTRL_CONFIG:
        hc32_dma_config(serial, ctrl_arg);

        if (RT_DEVICE_FLAG_DMA_TX == ctrl_arg)
        {
            USART_FuncCmd(uart->Instance, (USART_TX | USART_INT_TC), Disable);

            /* Install TC irq handler */
            uart_index = hc32_get_uart_index(uart->Instance);
            hc32_install_irq_handler(&uart->config.dma_tx->irq_config,
                            uart_irq_handlers[uart_index].tc_irq_handler,
                            RT_TRUE);
        }
        break;
#endif

    case RT_DEVICE_CTRL_CLOSE:
        USART_DeInit(uart->Instance);
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

    if(serial->parent.open_flag & RT_DEVICE_FLAG_INT_TX)
    {
        if (USART_GetStatus(uart->Instance, USART_FLAG_TXE) != Set)
        {
            return -1;
        }
    }
    else
    {
        /* Polling mode. */
        while (USART_GetStatus(uart->Instance, USART_FLAG_TXE) != Set);
    }

    USART_SendData(uart->Instance, c);

    return 1;
}

static int hc32_getc(struct rt_serial_device *serial)
{
    int ch= -1;
    struct hc32_uart *uart;

    RT_ASSERT(RT_NULL != serial);

    uart = rt_container_of(serial, struct hc32_uart, serial);
    RT_ASSERT(RT_NULL != uart->Instance);

    if(Set == USART_GetStatus(uart->Instance, USART_FLAG_RXNE))
    {
        ch = (rt_uint8_t)USART_RecData(uart->Instance);
    }

    return ch;
}

static rt_size_t hc32_dma_transmit(struct rt_serial_device *serial,
                                rt_uint8_t *buf,
                                rt_size_t size,
                                int direction)
{
    struct hc32_uart *uart;
    M4_DMA_TypeDef *DMA_Instance;
    uint8_t ch;

    RT_ASSERT(RT_NULL != serial);
    RT_ASSERT(RT_NULL != buf);

    if (size == 0)
    {
        return 0;
    }

    uart = rt_container_of(serial, struct hc32_uart, serial);

    if (RT_SERIAL_DMA_TX == direction)
    {
        DMA_Instance = uart->config.dma_tx->Instance;
        ch = uart->config.dma_tx->channel;

        if (Reset == USART_GetStatus(uart->Instance, USART_FLAG_TC))
        {
           RT_ASSERT(0);
        }

        DMA_SetSrcAddr(DMA_Instance, ch, (uint32_t)buf);
        DMA_SetTransCnt(DMA_Instance, ch, size);
        DMA_ChannelCmd(DMA_Instance, ch, Enable);

        USART_FuncCmd(uart->Instance, USART_TX, Enable);
        USART_TCI_ENABLE(uart->Instance);
        return size;
    }
    return 0;
}

static void hc32_uart_rx_irq_handler(struct hc32_uart *uart)
{
    RT_ASSERT(RT_NULL != uart);

    rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_RX_IND);
}

static void hc32_uart_tx_irq_handler(struct hc32_uart *uart)
{
    RT_ASSERT(RT_NULL != uart);

    if (uart->serial.parent.open_flag & RT_DEVICE_FLAG_INT_TX)
    {
        rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_TX_DONE);
    }
}

static void hc32_uart_rxerr_irq_handler(struct hc32_uart *uart)
{
    RT_ASSERT(RT_NULL != uart);
    RT_ASSERT(RT_NULL != uart->Instance);

    if (Set == USART_GetStatus(uart->Instance, (USART_FLAG_PE | USART_FLAG_FE)))
    {
        USART_RecData(uart->Instance);
    }

    USART_ClearStatus(uart->Instance, (USART_CLEAR_FLAG_PE | \
                                       USART_CLEAR_FLAG_FE | \
                                       USART_CLEAR_FLAG_ORE));
}

#ifdef RT_SERIAL_USING_DMA
static void hc32_uart_rx_timeout(struct rt_serial_device *serial)
{
    struct hc32_uart *uart;
    uint32_t cmp_val;
    uint32_t timeout_bits;
    M4_TMR0_TypeDef* TMR0_Instance;
    uint8_t ch;
    stc_tmr0_init_t stcTmr0Init;

    RT_ASSERT(RT_NULL != serial);

    uart = rt_container_of(serial, struct hc32_uart, serial);
    RT_ASSERT(RT_NULL != uart->Instance);

    TMR0_Instance = uart->config.rx_timeout->TMR0_Instance;
    ch = uart->config.rx_timeout->channel;
    timeout_bits = uart->config.rx_timeout->timeout_bits;

    if ((M4_USART1 == uart->Instance) || (M4_USART6 == uart->Instance))
    {
        RT_ASSERT(TMR0_CH_A == ch);
    }
    else if ((M4_USART2 == uart->Instance) || (M4_USART7 == uart->Instance))
    {
        RT_ASSERT(TMR0_CH_B == ch);
    }

    if ((M4_USART1 == uart->Instance) || (M4_USART2 == uart->Instance))
    {
        RT_ASSERT(M4_TMR0_1 == TMR0_Instance);
        PWC_Fcg2PeriphClockCmd(PWC_FCG2_TMR0_1, Enable);
    }
    else if ((M4_USART6 == uart->Instance) || (M4_USART7 == uart->Instance))
    {
        RT_ASSERT(M4_TMR0_2 == TMR0_Instance);
        PWC_Fcg2PeriphClockCmd(PWC_FCG2_TMR0_2, Enable);
    }

    /* De-initialize TMR0 */
    TMR0_DeInit(TMR0_Instance);

    /* Clear CNTAR register */
    TMR0_SetCntVal(TMR0_Instance, ch, 0U);

    /* TIMER0 basetimer function initialize */
    TMR0_StructInit(&stcTmr0Init);
    stcTmr0Init.u32ClockDivision = TMR0_CLK_DIV1;
    stcTmr0Init.u32ClockSource = TMR0_CLK_SRC_XTAL32;
    stcTmr0Init.u32HwTrigFunc = (TMR0_BT_HWTRG_FUNC_START | TMR0_BT_HWTRG_FUNC_CLEAR);
    if (TMR0_CLK_DIV1 == stcTmr0Init.u32ClockDivision)
    {
        cmp_val = (timeout_bits - 4UL);
    }
    else if (TMR0_CLK_DIV2 == stcTmr0Init.u32ClockDivision)
    {
        cmp_val = (timeout_bits/2UL - 2UL);
    }
    else
    {
        cmp_val = (timeout_bits / (1UL << (stcTmr0Init.u32ClockDivision >> TMR0_BCONR_CKDIVA_POS)) - 1UL);
    }
    DDL_ASSERT(cmp_val <= 0xFFFFUL);
    stcTmr0Init.u16CmpValue =  (uint16_t)(cmp_val);
    TMR0_Init(TMR0_Instance, ch, &stcTmr0Init);

    /* Clear compare flag */
    TMR0_ClearStatus(TMR0_Instance, ch);

    /* Register RTO interrupt */
    hc32_install_irq_handler(&uart->config.rx_timeout->irq_config,
            uart_irq_handlers[hc32_get_uart_index(uart->Instance)].rxto_irq_handler,
            RT_TRUE);

    USART_ClearStatus(uart->Instance, USART_CLEAR_FLAG_RTOF);
    USART_FuncCmd(uart->Instance, (USART_RTO | USART_INT_RTO), Enable);
}

static void hc32_dma_config(struct rt_serial_device *serial, rt_ubase_t flag)
{
    struct hc32_uart *uart;
    stc_dma_init_t dma_init;
    M4_DMA_TypeDef *DMA_Instance;
    uint32_t DMA_ch;
    uint32_t u32Fcg0Periph = PWC_FCG0_AOS;

    RT_ASSERT(RT_NULL != serial);

    uart = rt_container_of(serial, struct hc32_uart, serial);
    RT_ASSERT(RT_NULL != uart->Instance);

    if (RT_DEVICE_FLAG_DMA_RX == flag)
    {
        stc_dma_llp_init_t llp_init;
        struct rt_serial_rx_fifo *rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;

        RT_ASSERT(RT_NULL != uart->config.rx_timeout->TMR0_Instance);
        RT_ASSERT(RT_NULL != uart->config.dma_rx->Instance);

        /* Initialization uart rx timeout for DMA */
        hc32_uart_rx_timeout(serial);

        uart->dma_rx_last_index = 0UL;

        /* Get DMA unit&channel */
        DMA_Instance = uart->config.dma_rx->Instance;
        DMA_ch = uart->config.dma_rx->channel;

        /* Enable DMA clock */
        u32Fcg0Periph |= (M4_DMA1 == DMA_Instance) ? PWC_FCG0_DMA1:PWC_FCG0_DMA2;
        PWC_Fcg0PeriphClockCmd(u32Fcg0Periph, Enable);

        /* Disable DMA */
        DMA_ChannelCmd(DMA_Instance, DMA_ch, Disable);

        /* Initialize DMA */
        DMA_StructInit(&dma_init);
        dma_init.u32IntEn     = DMA_INT_ENABLE;
        dma_init.u32SrcAddr   = ((uint32_t)(&uart->Instance->DR) + 2UL);
        dma_init.u32DestAddr  = (uint32_t)rx_fifo->buffer;
        dma_init.u32DataWidth = DMA_DATAWIDTH_8BIT;
        dma_init.u32BlockSize = 1UL;
        dma_init.u32TransCnt  = serial->config.bufsz;
        dma_init.u32SrcInc    = DMA_SRC_ADDR_FIX;
        dma_init.u32DestInc   = DMA_DEST_ADDR_INC;
        DMA_Init(DMA_Instance, DMA_ch, &dma_init);

        /* Initialize LLP */
        static stc_dma_llp_descriptor_t llp_desc;
        llp_init.u32LlpEn  = DMA_LLP_ENABLE;
        llp_init.u32LlpRun = DMA_LLP_WAIT;
        llp_init.u32LlpAddr= (uint32_t)&llp_desc;
        DMA_LlpInit(DMA_Instance, DMA_ch, &llp_init);

        /* Configure LLP descriptor */
        llp_desc.SARx  = dma_init.u32SrcAddr;
        llp_desc.DARx  = dma_init.u32DestAddr;
        llp_desc.DTCTLx= (dma_init.u32TransCnt << DMA_DTCTL_CNT_POS) | (dma_init.u32BlockSize << DMA_DTCTL_BLKSIZE_POS);
        llp_desc.LLPx  = (uint32_t)&llp_desc;
        llp_desc.CHCTLx= (dma_init.u32SrcInc | dma_init.u32DestInc | dma_init.u32DataWidth | \
                          llp_init.u32LlpEn  | llp_init.u32LlpRun  | dma_init.u32IntEn);

        /* Register DMA interrupt */
        hc32_install_irq_handler(&uart->config.dma_rx->irq_config,
                uart_irq_handlers[hc32_get_uart_index(uart->Instance)].dma_rx_irq_handler,
                RT_TRUE);

        /* Enable DMA module */
        DMA_Cmd(DMA_Instance, Enable);
        DMA_TransIntCmd(DMA_Instance, (DMA_TC_INT_CH0 << DMA_ch), Enable);
        DMA_SetTriggerSrc(DMA_Instance, DMA_ch, uart->config.dma_rx->trigger_evt_src);
        DMA_ChannelCmd(DMA_Instance, DMA_ch, Enable);
    }
    else if (RT_DEVICE_FLAG_DMA_TX == flag)
    {
        RT_ASSERT(RT_NULL != uart->config.dma_tx->Instance);

        DMA_Instance = uart->config.dma_tx->Instance;
        DMA_ch = uart->config.dma_tx->channel;

        /* Enable DMA clock */
        u32Fcg0Periph |= (M4_DMA1 == DMA_Instance) ? PWC_FCG0_DMA1:PWC_FCG0_DMA2;
        PWC_Fcg0PeriphClockCmd(u32Fcg0Periph, Enable);

        /* Disable DMA */
        DMA_ChannelCmd(DMA_Instance, DMA_ch, Disable);

        /* Initialize DMA */
        DMA_StructInit(&dma_init);
        dma_init.u32IntEn     = DMA_INT_DISABLE;
        dma_init.u32SrcAddr   = 0UL;
        dma_init.u32DestAddr  = (uint32_t)(&uart->Instance->DR);
        dma_init.u32DataWidth = DMA_DATAWIDTH_8BIT;
        dma_init.u32BlockSize = 1UL;
        dma_init.u32TransCnt  = 0UL;
        dma_init.u32SrcInc    = DMA_SRC_ADDR_INC;
        dma_init.u32DestInc   = DMA_DEST_ADDR_FIX;
        DMA_Init(DMA_Instance, DMA_ch, &dma_init);

        /* Enable DMA module */
        DMA_Cmd(DMA_Instance, Enable);
        DMA_SetTriggerSrc(DMA_Instance, DMA_ch, uart->config.dma_tx->trigger_evt_src);
    }
}

static void hc32_uart_tc_irq_handler(struct hc32_uart *uart)
{
    RT_ASSERT(uart != RT_NULL);

    USART_FuncCmd(uart->Instance, (USART_TX|USART_INT_TC), Disable);

    if (uart->serial.parent.open_flag & RT_DEVICE_FLAG_DMA_TX)
    {
        rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_TX_DMADONE);
    }
}

static void hc32_uart_dma_rx_irq_handler(struct hc32_uart *uart)
{
    struct rt_serial_device *serial;
    rt_size_t recv_len;
    rt_base_t level;

    RT_ASSERT(RT_NULL != uart);
    RT_ASSERT(RT_NULL != uart->Instance);

    serial = &uart->serial;

    level = rt_hw_interrupt_disable();
    recv_len = serial->config.bufsz - uart->dma_rx_last_index;
    uart->dma_rx_last_index = 0UL;
    rt_hw_interrupt_enable(level);

    if (recv_len)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
    }
}

static void hc32_uart_rxto_irq_handler(struct hc32_uart *uart)
{
    rt_base_t level;
    rt_size_t cnt;
    rt_size_t recv_len;
    rt_size_t recv_total_index;

    cnt = DMA_TRANS_CNT(uart->config.dma_rx->Instance , uart->config.dma_rx->channel);
    recv_total_index = uart->serial.config.bufsz - cnt;
    if (0UL != recv_total_index)
    {
        level = rt_hw_interrupt_disable();
        recv_len = recv_total_index - uart->dma_rx_last_index;
        uart->dma_rx_last_index = recv_total_index;
        rt_hw_interrupt_enable(level);

        if (recv_len)
        {
            rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
        }
    }

    TMR0_Cmd(uart->config.rx_timeout->TMR0_Instance, uart->config.rx_timeout->channel, Disable);
    USART_ClearStatus(uart->Instance, USART_CLEAR_FLAG_RTOF);
}
#endif

#if defined(BSP_USING_UART1)
static void hc32_uart1_rx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rx_irq_handler(&uart_obj[UART1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart1_tx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tx_irq_handler(&uart_obj[UART1_INDEX]);

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

#if defined(RT_SERIAL_USING_DMA)
static void hc32_uart1_tc_irq_handler(void)
{
#if defined(BSP_UART1_TX_USING_DMA)
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tc_irq_handler(&uart_obj[UART1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
#endif
}

static void hc32_uart1_rxto_irq_handler(void)
{
#if defined(BSP_UART1_RX_USING_DMA)
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxto_irq_handler(&uart_obj[UART1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
#endif
}

static void hc32_uart1_dma_rx_irq_handler(void)
{
#if defined(BSP_UART1_RX_USING_DMA)
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_dma_rx_irq_handler(&uart_obj[UART1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
#endif
}
#endif /* RT_SERIAL_USING_DMA */
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

static void hc32_uart2_tx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tx_irq_handler(&uart_obj[UART2_INDEX]);

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

#if defined(RT_SERIAL_USING_DMA)
static void hc32_uart2_tc_irq_handler(void)
{
#if defined(BSP_UART2_TX_USING_DMA)
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tc_irq_handler(&uart_obj[UART2_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
#endif
}

static void hc32_uart2_rxto_irq_handler(void)
{
#if defined(BSP_UART2_RX_USING_DMA)
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxto_irq_handler(&uart_obj[UART2_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
#endif
}

static void hc32_uart2_dma_rx_irq_handler(void)
{
#if defined(BSP_UART2_RX_USING_DMA)
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_dma_rx_irq_handler(&uart_obj[UART2_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
#endif
}
#endif /* RT_SERIAL_USING_DMA */
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

static void hc32_uart3_tx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tx_irq_handler(&uart_obj[UART3_INDEX]);

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

static void hc32_uart4_tx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tx_irq_handler(&uart_obj[UART4_INDEX]);

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

#if defined(BSP_USING_UART5)
static void hc32_uart5_rx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rx_irq_handler(&uart_obj[UART5_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart5_tx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tx_irq_handler(&uart_obj[UART5_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart5_rxerr_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxerr_irq_handler(&uart_obj[UART5_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)
static void hc32_uart6_rx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rx_irq_handler(&uart_obj[UART6_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart6_tx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tx_irq_handler(&uart_obj[UART6_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart6_rxerr_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxerr_irq_handler(&uart_obj[UART6_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

#if defined(RT_SERIAL_USING_DMA)
static void hc32_uart6_tc_irq_handler(void)
{
#if defined(BSP_UART6_TX_USING_DMA)
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tc_irq_handler(&uart_obj[UART6_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
#endif
}

static void hc32_uart6_rxto_irq_handler(void)
{
#if defined(BSP_UART6_RX_USING_DMA)
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxto_irq_handler(&uart_obj[UART6_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
#endif
}

static void hc32_uart6_dma_rx_irq_handler(void)
{
#if defined(BSP_UART6_RX_USING_DMA)
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_dma_rx_irq_handler(&uart_obj[UART6_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
#endif
}
#endif /* RT_SERIAL_USING_DMA */
#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_UART7)
static void hc32_uart7_rx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rx_irq_handler(&uart_obj[UART7_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart7_tx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tx_irq_handler(&uart_obj[UART7_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart7_rxerr_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxerr_irq_handler(&uart_obj[UART7_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

#if defined(RT_SERIAL_USING_DMA)
static void hc32_uart7_tc_irq_handler(void)
{
#if defined(BSP_UART7_TX_USING_DMA)
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tc_irq_handler(&uart_obj[UART7_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
#endif
}

static void hc32_uart7_rxto_irq_handler(void)
{
#if defined(BSP_UART7_RX_USING_DMA)
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxto_irq_handler(&uart_obj[UART7_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
#endif
}

static void hc32_uart7_dma_rx_irq_handler(void)
{
#if defined(BSP_UART7_RX_USING_DMA)
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_dma_rx_irq_handler(&uart_obj[UART7_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
#endif
}
#endif /* RT_SERIAL_USING_DMA */
#endif /* BSP_USING_UART7 */

#if defined(BSP_USING_UART8)
static void hc32_uart8_rx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rx_irq_handler(&uart_obj[UART8_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart8_tx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tx_irq_handler(&uart_obj[UART8_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart8_rxerr_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxerr_irq_handler(&uart_obj[UART8_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART8 */

#if defined(BSP_USING_UART9)
static void hc32_uart9_rx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rx_irq_handler(&uart_obj[UART9_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart9_tx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tx_irq_handler(&uart_obj[UART9_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart9_rxerr_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxerr_irq_handler(&uart_obj[UART9_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART9 */

#if defined(BSP_USING_UART10)
static void hc32_uart10_rx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rx_irq_handler(&uart_obj[UART10_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart10_tx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tx_irq_handler(&uart_obj[UART10_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart10_rxerr_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxerr_irq_handler(&uart_obj[UART10_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART10 */

static const struct uart_irq_handler uart_irq_handlers[] =
{
#ifdef BSP_USING_UART1
    {hc32_uart1_rxerr_irq_handler, hc32_uart1_rx_irq_handler, hc32_uart1_tx_irq_handler,
     hc32_uart1_tc_irq_handler, hc32_uart1_rxto_irq_handler,  hc32_uart1_dma_rx_irq_handler},
#endif
#ifdef BSP_USING_UART2
    {hc32_uart2_rxerr_irq_handler, hc32_uart2_rx_irq_handler, hc32_uart2_tx_irq_handler,
     hc32_uart2_tc_irq_handler, hc32_uart2_rxto_irq_handler,  hc32_uart2_dma_rx_irq_handler},
#endif
#ifdef BSP_USING_UART3
    {hc32_uart3_rxerr_irq_handler, hc32_uart3_rx_irq_handler, hc32_uart3_tx_irq_handler},
#endif
#ifdef BSP_USING_UART4
    {hc32_uart4_rxerr_irq_handler, hc32_uart4_rx_irq_handler, hc32_uart4_tx_irq_handler},
#endif
#ifdef BSP_USING_UART5
    {hc32_uart5_rxerr_irq_handler, hc32_uart5_rx_irq_handler, hc32_uart5_tx_irq_handler},
#endif
#ifdef BSP_USING_UART6
    {hc32_uart6_rxerr_irq_handler, hc32_uart6_rx_irq_handler, hc32_uart6_tx_irq_handler,
     hc32_uart6_tc_irq_handler, hc32_uart6_rxto_irq_handler,  hc32_uart6_dma_rx_irq_handler},
#endif
#ifdef BSP_USING_UART7
    {hc32_uart7_rxerr_irq_handler, hc32_uart7_rx_irq_handler, hc32_uart7_tx_irq_handler,
     hc32_uart7_tc_irq_handler, hc32_uart7_rxto_irq_handler,  hc32_uart7_dma_rx_irq_handler},
#endif
#ifdef BSP_USING_UART8
    {hc32_uart8_rxerr_irq_handler, hc32_uart8_rx_irq_handler, hc32_uart8_tx_irq_handler},
#endif
#ifdef BSP_USING_UART9
    {hc32_uart9_rxerr_irq_handler, hc32_uart9_rx_irq_handler, hc32_uart9_tx_irq_handler},
#endif
#ifdef BSP_USING_UART10
    {hc32_uart10_rxerr_irq_handler, hc32_uart10_rx_irq_handler, hc32_uart10_tx_irq_handler},
#endif
};

static void hc32_uart_get_dma_config(void)
{
#ifdef BSP_USING_UART1
    uart_obj[UART1_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART1_RX_USING_DMA
    uart_obj[UART1_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;

    static struct hc32_uart_rxto uart1_rx_timeout = UART_RXTO_CONFIG(USART1);
    uart_obj[UART1_INDEX].config.rx_timeout = &uart1_rx_timeout;

    static struct dma_config uart1_dma_rx = UART_DMA_RX_CONFIG(USART1);
    uart_obj[UART1_INDEX].config.dma_rx = &uart1_dma_rx;
#endif
#ifdef BSP_UART1_TX_USING_DMA
    uart_obj[UART1_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;

    static struct dma_config uart1_dma_tx = UART_DMA_TX_CONFIG(USART1);
    uart_obj[UART1_INDEX].config.dma_tx = &uart1_dma_tx;
#endif
#endif

#ifdef BSP_USING_UART2
    uart_obj[UART2_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART2_RX_USING_DMA
    uart_obj[UART2_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;

    static struct hc32_uart_rxto uart2_rx_timeout = UART_RXTO_CONFIG(USART2);
    uart_obj[UART2_INDEX].config.rx_timeout = &uart2_rx_timeout;

    static struct dma_config uart2_dma_rx = UART_DMA_RX_CONFIG(USART2);
    uart_obj[UART2_INDEX].config.dma_rx = &uart2_dma_rx;
#endif
#ifdef BSP_UART2_TX_USING_DMA
    uart_obj[UART2_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;

    static struct dma_config uart2_dma_tx = UART_DMA_TX_CONFIG(USART2);
    uart_obj[UART2_INDEX].config.dma_tx = &uart2_dma_tx;
#endif
#endif

#ifdef BSP_USING_UART6
    uart_obj[UART6_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART6_RX_USING_DMA
    uart_obj[UART6_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;

    static struct hc32_uart_rxto uart6_rx_timeout = UART_RXTO_CONFIG(USART6);
    uart_obj[UART6_INDEX].config.rx_timeout = &uart6_rx_timeout;

    static struct dma_config uart6_dma_rx = UART_DMA_RX_CONFIG(USART6);
    uart_obj[UART6_INDEX].config.dma_rx = &uart6_dma_rx;
#endif
#ifdef BSP_UART6_TX_USING_DMA
    uart_obj[UART6_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;

    static struct dma_config uart6_dma_tx = UART_DMA_TX_CONFIG(USART6);
    uart_obj[UART6_INDEX].config.dma_tx = &uart6_dma_tx;
#endif
#endif

#ifdef BSP_USING_UART7
    uart_obj[UART7_INDEX].uart_dma_flag = 0;
#ifdef BSP_UART7_RX_USING_DMA
    uart_obj[UART7_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;

    static struct hc32_uart_rxto uart7_rx_timeout = UART_RXTO_CONFIG(USART7);
    uart_obj[UART7_INDEX].config.rx_timeout = &uart7_rx_timeout;

    static struct dma_config uart7_dma_rx = UART_DMA_RX_CONFIG(USART7);
    uart_obj[UART7_INDEX].config.dma_rx = &uart7_dma_rx;
#endif
#ifdef BSP_UART7_TX_USING_DMA
    uart_obj[UART7_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;

    static struct dma_config uart7_dma_tx = UART_DMA_TX_CONFIG(USART7);
    uart_obj[UART7_INDEX].config.dma_tx = &uart7_dma_tx;
#endif
#endif
}

static const struct rt_uart_ops hc32_uart_ops =
{
    .configure = hc32_configure,
    .control = hc32_control,
    .putc = hc32_putc,
    .getc = hc32_getc,
    .dma_transmit = hc32_dma_transmit
};

int hc32_hw_uart_init(void)
{
    rt_err_t result = RT_EOK;
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct hc32_uart);
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    hc32_uart_get_dma_config();

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
                                        RT_DEVICE_FLAG_INT_TX |
                                        uart_obj[i].uart_dma_flag),
                                       &uart_obj[i]);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

INIT_BOARD_EXPORT(hc32_hw_uart_init);

#endif /* RT_USING_SERIAL */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
