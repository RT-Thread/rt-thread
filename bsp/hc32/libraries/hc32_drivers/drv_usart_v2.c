/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 * 2024-02-06     CDT          support HC32F448
 * 2024-04-15     CDT          support HC32F472
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtdevice.h>
#include <rthw.h>


#ifdef RT_USING_SERIAL_V2

#if defined (BSP_USING_UART1) || defined (BSP_USING_UART2) || defined (BSP_USING_UART3) || \
    defined (BSP_USING_UART4) || defined (BSP_USING_UART5) || defined (BSP_USING_UART6) || \
    defined (BSP_USING_UART7) || defined (BSP_USING_UART8) || defined (BSP_USING_UART9) || \
    defined (BSP_USING_UART10)

#include "drv_usart_v2.h"
#include "board_config.h"

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define DMA_CH_REG(reg_base, ch)                                               \
    (*(volatile uint32_t *)((uint32_t)(&(reg_base)) + ((ch) * 0x40UL)))

#define DMA_TRANS_SET_CNT(unit, ch)                                            \
    (READ_REG32(DMA_CH_REG((unit)->DTCTL0,(ch))) >> DMA_DTCTL_CNT_POS)

#define DMA_TRANS_CNT(unit, ch)                                                \
    (READ_REG32(DMA_CH_REG((unit)->MONDTCTL0, (ch))) >> DMA_DTCTL_CNT_POS)

#define UART_BAUDRATE_ERR_MAX           (0.025F)

#if defined (HC32F460)
    #define FCG_USART_CLK               FCG_Fcg1PeriphClockCmd

#elif defined (HC32F4A0) || defined (HC32F448) || defined (HC32F472)
    #define FCG_USART_CLK               FCG_Fcg3PeriphClockCmd

#endif

#define FCG_TMR0_CLK                    FCG_Fcg2PeriphClockCmd
#define FCG_DMA_CLK                     FCG_Fcg0PeriphClockCmd

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
extern rt_err_t rt_hw_board_uart_init(CM_USART_TypeDef *USARTx);

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
};

static struct hc32_uart_config uart_config[] =
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
#ifdef BSP_USING_UART9
    UART9_CONFIG,
#endif
#ifdef BSP_USING_UART10
    UART10_CONFIG,
#endif
};

static struct hc32_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
static rt_err_t hc32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct hc32_uart *uart;
    stc_usart_uart_init_t uart_init;

    RT_ASSERT(RT_NULL != cfg);
    RT_ASSERT(RT_NULL != serial);

    uart = rt_container_of(serial, struct hc32_uart, serial);
    USART_UART_StructInit(&uart_init);
    uart_init.u32OverSampleBit = USART_OVER_SAMPLE_8BIT;
    uart_init.u32Baudrate = cfg->baud_rate;
    uart_init.u32ClockSrc = USART_CLK_SRC_INTERNCLK;
#if defined (HC32F4A0)
    if ((CM_USART1 == uart->config->Instance) || (CM_USART2 == uart->config->Instance) || \
            (CM_USART6 == uart->config->Instance) || (CM_USART7 == uart->config->Instance))
#elif defined (HC32F460)
    if ((CM_USART1 == uart->config->Instance) || (CM_USART2 == uart->config->Instance) || \
            (CM_USART3 == uart->config->Instance) || (CM_USART4 == uart->config->Instance))
#elif defined (HC32F448) || defined (HC32F472)
    if ((CM_USART1 == uart->config->Instance) || (CM_USART2 == uart->config->Instance) || \
            (CM_USART4 == uart->config->Instance) || (CM_USART5 == uart->config->Instance))
#endif
    {
        uart_init.u32CKOutput = USART_CK_OUTPUT_ENABLE;
    }

    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        uart_init.u32DataWidth = USART_DATA_WIDTH_8BIT;
        break;
    case DATA_BITS_9:
        uart_init.u32DataWidth = USART_DATA_WIDTH_9BIT;
        break;
    default:
        uart_init.u32DataWidth = USART_DATA_WIDTH_8BIT;
        break;
    }

    switch (cfg->stop_bits)
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

    switch (cfg->parity)
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

    if (BIT_ORDER_LSB == cfg->bit_order)
    {
        uart_init.u32FirstBit = USART_FIRST_BIT_LSB;
    }
    else
    {
        uart_init.u32FirstBit = USART_FIRST_BIT_MSB;
    }
#if defined (HC32F4A0) || defined (HC32F448) || defined (HC32F472)
    switch (cfg->flowcontrol)
    {
    case RT_SERIAL_FLOWCONTROL_NONE:
        uart_init.u32HWFlowControl = USART_HW_FLOWCTRL_NONE;
        break;
    case RT_SERIAL_FLOWCONTROL_CTSRTS:
        uart_init.u32HWFlowControl = USART_HW_FLOWCTRL_RTS_CTS;
        break;
    default:
        uart_init.u32HWFlowControl = USART_HW_FLOWCTRL_NONE;
        break;
    }
#endif

#ifdef RT_SERIAL_USING_DMA
    uart->dma_rx_remaining_cnt = (serial->config.rx_bufsz <= 1UL) ? serial->config.rx_bufsz : serial->config.rx_bufsz / 2UL;
#endif
    /* Enable USART clock */
    FCG_USART_CLK(uart->config->clock, ENABLE);
    if (RT_EOK != rt_hw_board_uart_init(uart->config->Instance))
    {
        return -RT_ERROR;
    }
    /* Configure UART */
    uint32_t u32Div;
    float32_t f32Error;
    int32_t i32Ret = LL_ERR;
    USART_DeInit(uart->config->Instance);
    USART_UART_Init(uart->config->Instance, &uart_init, NULL);
    for (u32Div = 0UL; u32Div <= USART_CLK_DIV64; u32Div++)
    {
        USART_SetClockDiv(uart->config->Instance, u32Div);
        if ((LL_OK == USART_SetBaudrate(uart->config->Instance, uart_init.u32Baudrate, &f32Error)) &&
                ((-UART_BAUDRATE_ERR_MAX <= f32Error) && (f32Error <= UART_BAUDRATE_ERR_MAX)))
        {
            i32Ret = LL_OK;
            break;
        }
    }
    if (i32Ret != LL_OK)
    {
        return -RT_ERROR;
    }

    /* Enable error interrupt */
#if defined (HC32F460) || defined (HC32F4A0)
    NVIC_EnableIRQ(uart->config->rxerr_irq.irq_config.irq_num);
#elif defined (HC32F448) || defined (HC32F472)
    INTC_IntSrcCmd(uart->config->tx_int_src, ENABLE);
    INTC_IntSrcCmd(uart->config->rx_int_src, DISABLE);
    INTC_IntSrcCmd(uart->config->rxerr_int_src, ENABLE);
    NVIC_EnableIRQ(uart->config->irq_num);
    INTC_IntSrcCmd(uart->config->tc_irq.irq_config.int_src, ENABLE);
#endif
    USART_FuncCmd(uart->config->Instance, USART_TX | USART_RX | USART_INT_RX, ENABLE);

    return RT_EOK;
}

static rt_err_t hc32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct hc32_uart *uart;
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;

    RT_ASSERT(RT_NULL != serial);
    uart = rt_container_of(serial, struct hc32_uart, serial);
    RT_ASSERT(RT_NULL != uart->config->Instance);

    if (ctrl_arg & (RT_DEVICE_FLAG_RX_BLOCKING | RT_DEVICE_FLAG_RX_NON_BLOCKING))
    {
        if (uart->uart_dma_flag & RT_DEVICE_FLAG_DMA_RX)
        {
            ctrl_arg = RT_DEVICE_FLAG_DMA_RX;
        }
        else
        {
            ctrl_arg = RT_DEVICE_FLAG_INT_RX;
        }
    }
    else if (ctrl_arg & (RT_DEVICE_FLAG_TX_BLOCKING | RT_DEVICE_FLAG_TX_NON_BLOCKING))
    {
        if (uart->uart_dma_flag & RT_DEVICE_FLAG_DMA_TX)
        {
            ctrl_arg = RT_DEVICE_FLAG_DMA_TX;
        }
        else
        {
            ctrl_arg = RT_DEVICE_FLAG_INT_TX;
        }
    }

    switch (cmd)
    {
    /* Disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        if (RT_DEVICE_FLAG_INT_RX == ctrl_arg)
        {
#if defined (HC32F460) || defined (HC32F4A0)
            NVIC_DisableIRQ(uart->config->rx_irq.irq_config.irq_num);
            INTC_IrqSignOut(uart->config->rx_irq.irq_config.irq_num);
#elif defined (HC32F448) || defined (HC32F472)
            INTC_IntSrcCmd(uart->config->rx_int_src, DISABLE);
#endif
        }
        else if (RT_DEVICE_FLAG_INT_TX == ctrl_arg)
        {
#if defined (HC32F460) || defined (HC32F4A0)
            NVIC_DisableIRQ(uart->config->tx_irq.irq_config.irq_num);
            NVIC_DisableIRQ(uart->config->tc_irq.irq_config.irq_num);
            USART_FuncCmd(uart->config->Instance, (USART_INT_TX_EMPTY | USART_INT_TX_CPLT), DISABLE);
            INTC_IrqSignOut(uart->config->tx_irq.irq_config.irq_num);
            INTC_IrqSignOut(uart->config->tc_irq.irq_config.irq_num);
#elif defined (HC32F448) || defined (HC32F472)
            NVIC_DisableIRQ(uart->config->tc_irq.irq_config.irq_num);
            INTC_IrqSignOut(uart->config->tc_irq.irq_config.irq_num);
            USART_FuncCmd(uart->config->Instance, (USART_INT_TX_EMPTY | USART_INT_TX_CPLT), DISABLE);
#endif
        }
#ifdef RT_SERIAL_USING_DMA
        else if (RT_DEVICE_FLAG_DMA_RX == ctrl_arg)
        {
            NVIC_DisableIRQ(uart->config->dma_rx->irq_config.irq_num);
        }
        else if (RT_DEVICE_FLAG_DMA_TX == ctrl_arg)
        {
            USART_FuncCmd(uart->config->Instance, USART_INT_TX_CPLT, DISABLE);
            NVIC_DisableIRQ(uart->config->dma_tx->irq_config.irq_num);
        }
#endif
        break;
    /* Enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
#if defined (HC32F460) || defined (HC32F4A0)
        if (RT_DEVICE_FLAG_INT_RX == ctrl_arg)
        {
            hc32_install_irq_handler(&uart->config->rx_irq.irq_config, uart->config->rx_irq.irq_callback, RT_TRUE);
            USART_FuncCmd(uart->config->Instance, USART_INT_RX, ENABLE);
        }
        else if (RT_DEVICE_FLAG_INT_TX == ctrl_arg)
        {
            INTC_IrqSignOut(uart->config->tx_irq.irq_config.irq_num);
            INTC_IrqSignOut(uart->config->tc_irq.irq_config.irq_num);
            hc32_install_irq_handler(&uart->config->tx_irq.irq_config, uart->config->tx_irq.irq_callback, RT_TRUE);
            hc32_install_irq_handler(&uart->config->tc_irq.irq_config, uart->config->tc_irq.irq_callback, RT_TRUE);
            USART_FuncCmd(uart->config->Instance, USART_TX, DISABLE);
            USART_FuncCmd(uart->config->Instance, USART_TX | USART_INT_TX_EMPTY, ENABLE);
        }
#elif defined (HC32F448) || defined (HC32F472)
        /* NVIC config */
        if (RT_DEVICE_FLAG_INT_RX == ctrl_arg)
        {
            /* intsrc enable */
            INTC_IntSrcCmd(uart->config->rx_int_src, ENABLE);
            USART_FuncCmd(uart->config->Instance, USART_INT_RX, ENABLE);
        }
        else if (RT_DEVICE_FLAG_INT_TX == ctrl_arg)
        {
            NVIC_ClearPendingIRQ(uart->config->tc_irq.irq_config.irq_num);
            NVIC_EnableIRQ(uart->config->tc_irq.irq_config.irq_num);
            USART_FuncCmd(uart->config->Instance, USART_TX | USART_INT_TX_EMPTY, ENABLE);
        }
#endif
        break;
    case RT_DEVICE_CTRL_CONFIG:
        if (ctrl_arg & (RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX))
        {
#ifdef RT_SERIAL_USING_DMA
            hc32_dma_config(serial, ctrl_arg);
#endif
        }
        else
        {
            hc32_control(serial, RT_DEVICE_CTRL_SET_INT, (void *)ctrl_arg);
        }
        break;
    case RT_DEVICE_CHECK_OPTMODE:
        if (ctrl_arg & RT_DEVICE_FLAG_DMA_TX)
        {
            return RT_SERIAL_TX_BLOCKING_NO_BUFFER;
        }
        else
        {
            return RT_SERIAL_TX_BLOCKING_BUFFER;
        }
    case RT_DEVICE_CTRL_CLOSE:
        USART_DeInit(uart->config->Instance);
        break;
    }

    return RT_EOK;
}

static int hc32_putc(struct rt_serial_device *serial, char c)
{
    struct hc32_uart *uart;

    RT_ASSERT(RT_NULL != serial);
    uart = rt_container_of(serial, struct hc32_uart, serial);
    RT_ASSERT(RT_NULL != uart->config->Instance);

    /* Polling mode. */
    while (USART_GetStatus(uart->config->Instance, USART_FLAG_TX_CPLT) != SET);
    USART_WriteData(uart->config->Instance, c);

    return 1;
}

static int hc32_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    struct hc32_uart *uart;

    RT_ASSERT(RT_NULL != serial);

    uart = rt_container_of(serial, struct hc32_uart, serial);
    RT_ASSERT(RT_NULL != uart->config->Instance);
    if (SET == USART_GetStatus(uart->config->Instance, USART_FLAG_RX_FULL))
    {
        ch = (rt_uint8_t)USART_ReadData(uart->config->Instance);
    }

    return ch;
}

static rt_ssize_t hc32_transmit(struct rt_serial_device  *serial,
                                rt_uint8_t               *buf,
                                rt_size_t                 size,
                                rt_uint32_t               tx_flag)
{
    struct hc32_uart *uart;
#ifdef RT_SERIAL_USING_DMA
    struct dma_config *uart_dma;
#endif

    RT_ASSERT(RT_NULL != serial);
    RT_ASSERT(RT_NULL != buf);

    if (0 == size)
    {
        return 0;
    }

    uart = rt_container_of(serial, struct hc32_uart, serial);
    if (uart->uart_dma_flag & RT_DEVICE_FLAG_DMA_TX)
    {
#ifdef RT_SERIAL_USING_DMA
        uart_dma = uart->config->dma_tx;
        if (RESET == USART_GetStatus(uart->config->Instance, USART_FLAG_TX_CPLT))
        {
            RT_ASSERT(0);
        }
        DMA_SetSrcAddr(uart_dma->Instance, uart_dma->channel, (uint32_t)buf);
        DMA_SetTransCount(uart_dma->Instance, uart_dma->channel, size);
        DMA_ChCmd(uart_dma->Instance, uart_dma->channel, ENABLE);
        USART_FuncCmd(uart->config->Instance, USART_TX, ENABLE);
        USART_FuncCmd(uart->config->Instance, USART_INT_TX_CPLT, ENABLE);
        return size;
#endif
    }
    hc32_control(serial, RT_DEVICE_CTRL_SET_INT, (void *)tx_flag);

    return size;
}

static void hc32_uart_rx_irq_handler(struct hc32_uart *uart)
{
    RT_ASSERT(RT_NULL != uart);
    struct rt_serial_rx_fifo *rx_fifo;
    rx_fifo = (struct rt_serial_rx_fifo *)uart->serial.serial_rx;
    RT_ASSERT(rx_fifo != RT_NULL);
    rt_ringbuffer_putchar(&(rx_fifo->rb), (rt_uint8_t)USART_ReadData(uart->config->Instance));
    rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_RX_IND);
}

static void hc32_uart_tx_irq_handler(struct hc32_uart *uart)
{
    RT_ASSERT(RT_NULL != uart);
    struct rt_serial_tx_fifo *tx_fifo;
    tx_fifo = (struct rt_serial_tx_fifo *)uart->serial.serial_tx;
    RT_ASSERT(tx_fifo != RT_NULL);

    rt_uint8_t put_char = 0;
    if (rt_ringbuffer_getchar(&(tx_fifo->rb), &put_char))
    {
        USART_WriteData(uart->config->Instance, put_char);
    }
    else
    {
        USART_FuncCmd(uart->config->Instance, USART_INT_TX_EMPTY, DISABLE);
        USART_FuncCmd(uart->config->Instance, USART_INT_TX_CPLT, ENABLE);
    }
}

static void hc32_uart_rxerr_irq_handler(struct hc32_uart *uart)
{
    RT_ASSERT(RT_NULL != uart);
    RT_ASSERT(RT_NULL != uart->config->Instance);

    if (SET == USART_GetStatus(uart->config->Instance, (USART_FLAG_OVERRUN | USART_FLAG_PARITY_ERR | USART_FLAG_FRAME_ERR)))
    {
        USART_ReadData(uart->config->Instance);
    }
    USART_ClearStatus(uart->config->Instance, (USART_FLAG_PARITY_ERR | USART_FLAG_FRAME_ERR | USART_FLAG_OVERRUN));
}

static void hc32_uart_tc_irq_handler(struct hc32_uart *uart)
{
    RT_ASSERT(RT_NULL != uart);

    USART_FuncCmd(uart->config->Instance, (USART_TX | USART_INT_TX_CPLT), DISABLE);

    if (uart->uart_dma_flag & RT_DEVICE_FLAG_DMA_TX)
    {
#ifdef RT_SERIAL_USING_DMA
        DMA_ClearTransCompleteStatus(uart->config->dma_tx->Instance, (DMA_FLAG_TC_CH0 | DMA_FLAG_BTC_CH0) << uart->config->dma_tx->channel);
#endif
        rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_TX_DMADONE);
    }
    else
    {
        rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_TX_DONE);
    }
}

#ifdef RT_SERIAL_USING_DMA
static void hc32_uart_rx_timeout(struct rt_serial_device *serial)
{
    struct hc32_uart *uart;
    CM_TMR0_TypeDef *TMR0_Instance;
    uint8_t ch;
    uint32_t rtb;
    uint32_t alpha;
    uint32_t ckdiv;
    uint32_t cmp_val;
    stc_tmr0_init_t stcTmr0Init;

    RT_ASSERT(RT_NULL != serial);
    uart = rt_container_of(serial, struct hc32_uart, serial);
    RT_ASSERT(RT_NULL != uart->config->Instance);

    TMR0_Instance = uart->config->rx_timeout->TMR0_Instance;
    ch            = uart->config->rx_timeout->channel;
    rtb           = uart->config->rx_timeout->timeout_bits;
#if defined (HC32F460)
    if ((CM_USART1 == uart->config->Instance) || (CM_USART3 == uart->config->Instance))
    {
        RT_ASSERT(TMR0_CH_A == ch);
    }
    else if ((CM_USART2 == uart->config->Instance) || (CM_USART4 == uart->config->Instance))
    {
        RT_ASSERT(TMR0_CH_B == ch);
    }
#elif defined (HC32F4A0)
    if ((CM_USART1 == uart->config->Instance) || (CM_USART6 == uart->config->Instance))
    {
        RT_ASSERT(TMR0_CH_A == ch);
    }
    else if ((CM_USART2 == uart->config->Instance) || (CM_USART7 == uart->config->Instance))
    {
        RT_ASSERT(TMR0_CH_B == ch);
    }
#elif defined (HC32F448) || defined (HC32F472)
    if ((CM_USART1 == uart->config->Instance) || (CM_USART4 == uart->config->Instance))
    {
        RT_ASSERT(TMR0_CH_A == ch);
    }
    else if ((CM_USART2 == uart->config->Instance) || (CM_USART5 == uart->config->Instance))
    {
        RT_ASSERT(TMR0_CH_B == ch);
    }
#endif

    FCG_TMR0_CLK(uart->config->rx_timeout->clock, ENABLE);

    /* TIMER0 basetimer function initialize */
    TMR0_SetCountValue(TMR0_Instance, ch, 0U);
    TMR0_StructInit(&stcTmr0Init);
    stcTmr0Init.u32ClockDiv = TMR0_CLK_DIV1;
    stcTmr0Init.u32ClockSrc = TMR0_CLK_SRC_XTAL32;
    if (TMR0_CLK_DIV1 == stcTmr0Init.u32ClockDiv)
    {
        alpha = 7UL;
    }
    else if (TMR0_CLK_DIV2 == stcTmr0Init.u32ClockDiv)
    {
        alpha = 5UL;
    }
    else if ((TMR0_CLK_DIV4 == stcTmr0Init.u32ClockDiv) || \
             (TMR0_CLK_DIV8 == stcTmr0Init.u32ClockDiv) || \
             (TMR0_CLK_DIV16 == stcTmr0Init.u32ClockDiv))
    {
        alpha = 3UL;
    }
    else
    {
        alpha = 2UL;
    }
    /* TMR0_CMPA<B>R calculation formula: CMPA<B>R = (RTB / (2 ^ CKDIVA<B>)) - alpha */
    ckdiv   = 1UL << (stcTmr0Init.u32ClockDiv >> TMR0_BCONR_CKDIVA_POS);
    cmp_val = ((rtb + ckdiv - 1UL) / ckdiv) - alpha;
    DDL_ASSERT(cmp_val <= 0xFFFFUL);
    stcTmr0Init.u16CompareValue = (uint16_t)(cmp_val);
    TMR0_Init(TMR0_Instance, ch, &stcTmr0Init);
    TMR0_HWStartCondCmd(TMR0_Instance, ch, ENABLE);
    TMR0_HWClearCondCmd(TMR0_Instance, ch, ENABLE);
    /* Clear compare flag */
    TMR0_ClearStatus(TMR0_Instance, (uint32_t)(0x1UL << (ch * TMR0_STFLR_CMFB_POS)));

#if defined (HC32F460) || defined (HC32F4A0)
    NVIC_EnableIRQ(uart->config->rx_timeout->irq_config.irq_num);
#endif
    USART_ClearStatus(uart->config->Instance, USART_FLAG_RX_TIMEOUT);
    USART_FuncCmd(uart->config->Instance, (USART_RX_TIMEOUT | USART_INT_RX_TIMEOUT), ENABLE);
}

static void hc32_dma_config(struct rt_serial_device *serial, rt_ubase_t flag)
{
    rt_uint32_t trans_count = (serial->config.rx_bufsz <= 1UL) ? serial->config.rx_bufsz : serial->config.rx_bufsz / 2UL;
    struct hc32_uart *uart;
    stc_dma_init_t dma_init;
    struct dma_config *uart_dma;

    RT_ASSERT(RT_NULL != serial);
    RT_ASSERT(RT_NULL == ((serial->config.rx_bufsz) & ((RT_ALIGN_SIZE) - 1)));

    uart = rt_container_of(serial, struct hc32_uart, serial);
    RT_ASSERT(RT_NULL != uart->config->Instance);
    if (RT_DEVICE_FLAG_DMA_RX == flag)
    {
        stc_dma_llp_init_t llp_init;
        struct rt_serial_rx_fifo *rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;

        RT_ASSERT(RT_NULL != uart->config->rx_timeout->TMR0_Instance);
        RT_ASSERT(RT_NULL != uart->config->dma_rx->Instance);
        RT_ASSERT(RT_NULL != rx_fifo);

#if defined (HC32F448) || defined (HC32F472)
        INTC_IntSrcCmd(uart->config->rx_int_src, DISABLE);
#endif

        uart_dma = uart->config->dma_rx;
        /* Initialization uart rx timeout for DMA */
        hc32_uart_rx_timeout(serial);
        /* Enable DMA clock */
        FCG_DMA_CLK(uart_dma->clock, ENABLE);
        DMA_ChCmd(uart_dma->Instance, uart_dma->channel, DISABLE);

        /* Initialize DMA */
        DMA_StructInit(&dma_init);
        dma_init.u32IntEn       = DMA_INT_ENABLE;
        dma_init.u32SrcAddr     = (uint32_t)(&uart->config->Instance->RDR);
        dma_init.u32DestAddr    = (uint32_t)rx_fifo->buffer;
        dma_init.u32DataWidth   = DMA_DATAWIDTH_8BIT;
        dma_init.u32BlockSize   = 1UL;
        dma_init.u32TransCount  = trans_count;
        dma_init.u32SrcAddrInc  = DMA_SRC_ADDR_FIX;
        dma_init.u32DestAddrInc = DMA_DEST_ADDR_INC;
        DMA_Init(uart_dma->Instance, uart_dma->channel, &dma_init);

        /* Initialize LLP */
        llp_init.u32State   = DMA_LLP_ENABLE;
        llp_init.u32Mode    = DMA_LLP_WAIT;
        llp_init.u32Addr    = (uint32_t)&uart->config->llp_desc;
        DMA_LlpInit(uart_dma->Instance, uart_dma->channel, &llp_init);

        /* Configure LLP descriptor */
        uart->config->llp_desc[0U].SARx  = dma_init.u32SrcAddr;
        uart->config->llp_desc[0U].DARx  = dma_init.u32DestAddr + ((serial->config.rx_bufsz <= 1UL) ? 0UL : dma_init.u32TransCount);
        uart->config->llp_desc[0U].DTCTLx = (((serial->config.rx_bufsz <= 1U) ? dma_init.u32TransCount : (serial->config.rx_bufsz - dma_init.u32TransCount)) << DMA_DTCTL_CNT_POS) | \
                                            (dma_init.u32BlockSize << DMA_DTCTL_BLKSIZE_POS);
        uart->config->llp_desc[0U].LLPx  = (serial->config.rx_bufsz <= 1U) ? (uint32_t)&uart->config->llp_desc[0U] : (uint32_t)&uart->config->llp_desc[1U];
        uart->config->llp_desc[0U].CHCTLx = (dma_init.u32SrcAddrInc | dma_init.u32DestAddrInc | dma_init.u32DataWidth | \
                                             llp_init.u32State      | llp_init.u32Mode        | dma_init.u32IntEn);

        if (serial->config.rx_bufsz > 1UL)
        {
            uart->config->llp_desc[1U].SARx  = dma_init.u32SrcAddr;
            uart->config->llp_desc[1U].DARx  = dma_init.u32DestAddr;
            uart->config->llp_desc[1U].DTCTLx = (dma_init.u32TransCount << DMA_DTCTL_CNT_POS) | (dma_init.u32BlockSize << DMA_DTCTL_BLKSIZE_POS);
            uart->config->llp_desc[1U].LLPx  = (uint32_t)&uart->config->llp_desc[0U];
            uart->config->llp_desc[1U].CHCTLx = (dma_init.u32SrcAddrInc | dma_init.u32DestAddrInc | dma_init.u32DataWidth | \
                                                 llp_init.u32State      | llp_init.u32Mode        | dma_init.u32IntEn);
        }

        /* Enable DMA interrupt */
        NVIC_EnableIRQ(uart->config->dma_rx->irq_config.irq_num);
        /* Enable DMA module */
        DMA_Cmd(uart_dma->Instance, ENABLE);
        AOS_SetTriggerEventSrc(uart_dma->trigger_select, uart_dma->trigger_event);
        DMA_ChCmd(uart_dma->Instance, uart_dma->channel, ENABLE);
    }
    else if (RT_DEVICE_FLAG_DMA_TX == flag)
    {
        RT_ASSERT(RT_NULL != uart->config->dma_tx->Instance);

        uart_dma = uart->config->dma_tx;
        /* Enable DMA clock */
        FCG_DMA_CLK(uart_dma->clock, ENABLE);
        DMA_ChCmd(uart_dma->Instance, uart_dma->channel, DISABLE);

        /* Initialize DMA */
        DMA_StructInit(&dma_init);
        dma_init.u32IntEn       = DMA_INT_DISABLE;
        dma_init.u32SrcAddr     = 0UL;
        dma_init.u32DestAddr    = (uint32_t)(&uart->config->Instance->TDR);
        dma_init.u32DataWidth   = DMA_DATAWIDTH_8BIT;
        dma_init.u32BlockSize   = 1UL;
        dma_init.u32TransCount  = 0UL;
        dma_init.u32SrcAddrInc  = DMA_SRC_ADDR_INC;
        dma_init.u32DestAddrInc = DMA_DEST_ADDR_FIX;
        DMA_Init(uart_dma->Instance, uart_dma->channel, &dma_init);

        /* Enable DMA module */
        DMA_Cmd(uart_dma->Instance, ENABLE);
        AOS_SetTriggerEventSrc(uart_dma->trigger_select, uart_dma->trigger_event);
        USART_FuncCmd(uart->config->Instance, (USART_TX | USART_INT_TX_EMPTY | USART_INT_TX_CPLT), DISABLE);
        NVIC_EnableIRQ(uart->config->tc_irq.irq_config.irq_num);
    }
}

#if defined (BSP_UART1_RX_USING_DMA) || defined (BSP_UART2_RX_USING_DMA) || defined (BSP_UART3_RX_USING_DMA) || \
    defined (BSP_UART4_RX_USING_DMA) || defined (BSP_UART5_RX_USING_DMA) || defined (BSP_UART6_RX_USING_DMA) || \
    defined (BSP_UART7_RX_USING_DMA)
static void hc32_uart_dma_rx_irq_handler(struct hc32_uart *uart)
{
    rt_base_t level;
    rt_size_t recv_len;
    struct rt_serial_device *serial;

    RT_ASSERT(RT_NULL != uart);
    RT_ASSERT(RT_NULL != uart->config->Instance);

    serial = &uart->serial;
    RT_ASSERT(RT_NULL != serial);
    level = rt_hw_interrupt_disable();
    recv_len = uart->dma_rx_remaining_cnt;
    uart->dma_rx_remaining_cnt = DMA_TRANS_SET_CNT(uart->config->dma_rx->Instance, uart->config->dma_rx->channel);

    if (recv_len)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
    }
    rt_hw_interrupt_enable(level);
}

static void hc32_uart_rxto_irq_handler(struct hc32_uart *uart)
{
    rt_base_t level;
    rt_size_t dma_set_cnt, cnt;
    rt_size_t recv_len;
    struct rt_serial_device *serial;

    serial = &uart->serial;
    RT_ASSERT(serial != RT_NULL);

    cnt = DMA_TRANS_CNT(uart->config->dma_rx->Instance, uart->config->dma_rx->channel);
    dma_set_cnt = DMA_TRANS_SET_CNT(uart->config->dma_rx->Instance, uart->config->dma_rx->channel);

    level = rt_hw_interrupt_disable();
    if (cnt <= uart->dma_rx_remaining_cnt)
    {
        recv_len = uart->dma_rx_remaining_cnt - cnt;
    }
    else
    {
        recv_len = uart->dma_rx_remaining_cnt + dma_set_cnt - cnt;
    }

    if (recv_len)
    {
        uart->dma_rx_remaining_cnt = cnt;
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));
    }
    rt_hw_interrupt_enable(level);
    TMR0_Stop(uart->config->rx_timeout->TMR0_Instance, uart->config->rx_timeout->channel);
    USART_ClearStatus(uart->config->Instance, USART_FLAG_RX_TIMEOUT);
}
#endif
#endif

#if defined (HC32F448) || defined (HC32F472)
static void hc32_usart_handler(struct hc32_uart *uart)
{
    RT_ASSERT(RT_NULL != uart);

#if defined (RT_SERIAL_USING_DMA)
    if ((SET == USART_GetStatus(uart->config->Instance, USART_FLAG_RX_TIMEOUT)) && \
            (ENABLE == USART_GetFuncState(uart->config->Instance, USART_RX_TIMEOUT)) && \
            (ENABLE == INTC_GetIntSrcState(uart->config->rxto_int_src)))
    {
#if defined (BSP_UART1_RX_USING_DMA) || defined (BSP_UART2_RX_USING_DMA) || \
    defined (BSP_UART4_RX_USING_DMA) || defined (BSP_UART5_RX_USING_DMA)
        hc32_uart_rxto_irq_handler(uart);
#endif
    }
#endif

    if ((SET == USART_GetStatus(uart->config->Instance, USART_FLAG_RX_FULL)) && \
            (ENABLE == USART_GetFuncState(uart->config->Instance, USART_INT_RX)) && \
            (ENABLE == INTC_GetIntSrcState(uart->config->rx_int_src)))
    {
        hc32_uart_rx_irq_handler(uart);
    }

    if ((SET == USART_GetStatus(uart->config->Instance, USART_FLAG_TX_EMPTY)) && \
            (ENABLE == USART_GetFuncState(uart->config->Instance, USART_INT_TX_EMPTY)) && \
            (ENABLE == INTC_GetIntSrcState(uart->config->tx_int_src)))
    {
        hc32_uart_tx_irq_handler(uart);
    }

    if ((SET == USART_GetStatus(uart->config->Instance, (USART_FLAG_OVERRUN | \
                                USART_FLAG_FRAME_ERR | USART_FLAG_PARITY_ERR))) && \
            (ENABLE == USART_GetFuncState(uart->config->Instance, USART_INT_RX))  && \
            (ENABLE == INTC_GetIntSrcState(uart->config->rxerr_int_src)))
    {
        hc32_uart_rxerr_irq_handler(uart);
    }
}
#endif

#if defined (BSP_USING_UART1)
#if defined (HC32F460) || defined (HC32F4A0)
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
#endif /* HC32F460, HC32F4A0 */

static void hc32_uart1_tc_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tc_irq_handler(&uart_obj[UART1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

#if defined (RT_SERIAL_USING_DMA)
#if defined (BSP_UART1_RX_USING_DMA)
#if defined (HC32F460) || defined (HC32F4A0)
static void hc32_uart1_rxto_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxto_irq_handler(&uart_obj[UART1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* HC32F460, HC32F4A0 */

static void hc32_uart1_dma_rx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_dma_rx_irq_handler(&uart_obj[UART1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_UART1_RX_USING_DMA */
#endif /* RT_SERIAL_USING_DMA */

#if defined (HC32F448) || defined (HC32F472)
void USART1_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_usart_handler(&uart_obj[UART1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

void USART1_TxComplete_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart1_tc_irq_handler();

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* HC32F448, HC32F472 */
#endif /* BSP_USING_UART1 */

#if defined (BSP_USING_UART2)
#if defined (HC32F460) || defined (HC32F4A0)
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
#endif /* HC32F460, HC32F4A0 */

static void hc32_uart2_tc_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tc_irq_handler(&uart_obj[UART2_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

#if defined (RT_SERIAL_USING_DMA)
#if defined (BSP_UART2_RX_USING_DMA)
#if defined (HC32F460) || defined (HC32F4A0)
static void hc32_uart2_rxto_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxto_irq_handler(&uart_obj[UART2_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* HC32F460, HC32F4A0 */

static void hc32_uart2_dma_rx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_dma_rx_irq_handler(&uart_obj[UART2_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_UART2_RX_USING_DMA */
#endif /* RT_SERIAL_USING_DMA */

#if defined (HC32F448) || defined (HC32F472)
void USART2_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_usart_handler(&uart_obj[UART2_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

void USART2_TxComplete_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart2_tc_irq_handler();

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* HC32F448, HC32F472 */
#endif /* BSP_USING_UART2 */

#if defined (BSP_USING_UART3)
#if defined (HC32F460) || defined (HC32F4A0)
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
#endif /* HC32F460, HC32F4A0 */

static void hc32_uart3_tc_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tc_irq_handler(&uart_obj[UART3_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

#if defined (RT_SERIAL_USING_DMA)
#if defined (BSP_UART3_RX_USING_DMA)
#if defined (HC32F460) || defined (HC32F4A0)
static void hc32_uart3_rxto_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxto_irq_handler(&uart_obj[UART3_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart3_dma_rx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_dma_rx_irq_handler(&uart_obj[UART3_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();

}
#endif /* HC32F460, HC32F4A0 */
#endif /* BSP_UART3_RX_USING_DMA */
#endif /* RT_SERIAL_USING_DMA */

#if defined (HC32F448) || defined (HC32F472)
void USART3_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_usart_handler(&uart_obj[UART3_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

void USART3_TxComplete_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart3_tc_irq_handler();

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* HC32F448, HC32F472 */
#endif /* BSP_USING_UART3 */

#if defined (BSP_USING_UART4)
#if defined (HC32F460) || defined (HC32F4A0)
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
#endif /* HC32F460, HC32F4A0 */

static void hc32_uart4_tc_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tc_irq_handler(&uart_obj[UART4_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

#if defined (RT_SERIAL_USING_DMA)
#if defined (BSP_UART4_RX_USING_DMA)
#if defined (HC32F460) || defined (HC32F4A0)
static void hc32_uart4_rxto_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxto_irq_handler(&uart_obj[UART4_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* HC32F460, HC32F4A0 */

static void hc32_uart4_dma_rx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_dma_rx_irq_handler(&uart_obj[UART4_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_UART4_RX_USING_DMA */
#endif /* RT_SERIAL_USING_DMA */

#if defined (HC32F448) || defined (HC32F472)
void USART4_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_usart_handler(&uart_obj[UART4_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

void USART4_TxComplete_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart4_tc_irq_handler();

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* HC32F448, HC32F472 */
#endif /* BSP_USING_UART4 */

#if defined (BSP_USING_UART5)
#if defined (HC32F460) || defined (HC32F4A0)
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
#endif /* HC32F460, HC32F4A0 */

static void hc32_uart5_tc_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tc_irq_handler(&uart_obj[UART5_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

#if defined (HC32F448) || defined (HC32F472)
#if defined (RT_SERIAL_USING_DMA)
#if defined (BSP_UART5_RX_USING_DMA)
static void hc32_uart5_dma_rx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_dma_rx_irq_handler(&uart_obj[UART5_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_UART5_RX_USING_DMA */
#endif /* RT_SERIAL_USING_DMA */

void USART5_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_usart_handler(&uart_obj[UART5_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

void USART5_TxComplete_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart5_tc_irq_handler();

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* HC32F448, HC32F472 */
#endif /* BSP_USING_UART5 */

#if defined (BSP_USING_UART6)
#if defined (HC32F460) || defined (HC32F4A0)
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
#endif /* HC32F460, HC32F4A0 */

static void hc32_uart6_tc_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tc_irq_handler(&uart_obj[UART6_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

#if defined (RT_SERIAL_USING_DMA)
#if defined (BSP_UART6_RX_USING_DMA)
#if defined (HC32F460) || defined (HC32F4A0)
static void hc32_uart6_rxto_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxto_irq_handler(&uart_obj[UART6_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart6_dma_rx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_dma_rx_irq_handler(&uart_obj[UART6_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* HC32F460, HC32F4A0 */
#endif /* BSP_UART6_RX_USING_DMA */
#endif /* RT_SERIAL_USING_DMA */

#if defined (HC32F448) || defined (HC32F472)
void USART6_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_usart_handler(&uart_obj[UART6_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

void USART6_TxComplete_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart6_tc_irq_handler();

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* HC32F448, HC32F472 */
#endif /* BSP_USING_UART6 */

#if defined (BSP_USING_UART7)
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

static void hc32_uart7_tc_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tc_irq_handler(&uart_obj[UART7_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

#if defined (RT_SERIAL_USING_DMA)
#if defined (BSP_UART7_RX_USING_DMA)
static void hc32_uart7_rxto_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxto_irq_handler(&uart_obj[UART7_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart7_dma_rx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_dma_rx_irq_handler(&uart_obj[UART7_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_UART7_RX_USING_DMA */
#endif /* RT_SERIAL_USING_DMA */
#endif /* BSP_USING_UART7 */

#if defined (BSP_USING_UART8)
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

static void hc32_uart8_tc_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tc_irq_handler(&uart_obj[UART8_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART8 */

#if defined (BSP_USING_UART9)
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

static void hc32_uart9_tc_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tc_irq_handler(&uart_obj[UART9_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART9 */

#if defined (BSP_USING_UART10)
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

static void hc32_uart10_tc_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tc_irq_handler(&uart_obj[UART10_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART10 */

/**
  * @brief  This function gets dma witch uart used infomation include unit,
  *         channel, interrupt etc.
  * @param  None
  * @retval None
  */
static void hc32_uart_get_info(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef BSP_USING_UART1
    uart_obj[UART1_INDEX].uart_dma_flag = 0;
    uart_obj[UART1_INDEX].serial.config = config;
    uart_obj[UART1_INDEX].serial.config.rx_bufsz = BSP_UART1_RX_BUFSIZE;
    uart_obj[UART1_INDEX].serial.config.tx_bufsz = BSP_UART1_TX_BUFSIZE;
#ifdef BSP_UART1_RX_USING_DMA
    uart_obj[UART1_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart1_dma_rx = UART1_DMA_RX_CONFIG;
    static struct hc32_uart_rxto uart1_rx_timeout = UART1_RXTO_CONFIG;
    uart1_dma_rx.irq_callback = hc32_uart1_dma_rx_irq_handler;
#if defined (HC32F460) || defined (HC32F4A0)
    uart1_rx_timeout.irq_callback = hc32_uart1_rxto_irq_handler;
#endif
    uart_config[UART1_INDEX].rx_timeout = &uart1_rx_timeout;
    uart_config[UART1_INDEX].dma_rx = &uart1_dma_rx;
#endif
#ifdef BSP_UART1_TX_USING_DMA
    uart_obj[UART1_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart1_dma_tx = UART1_DMA_TX_CONFIG;
    uart_config[UART1_INDEX].dma_tx = &uart1_dma_tx;
#endif
#endif

#ifdef BSP_USING_UART2
    uart_obj[UART2_INDEX].uart_dma_flag = 0;
    uart_obj[UART2_INDEX].serial.config = config;
    uart_obj[UART2_INDEX].serial.config.rx_bufsz = BSP_UART2_RX_BUFSIZE;
    uart_obj[UART2_INDEX].serial.config.tx_bufsz = BSP_UART2_TX_BUFSIZE;
#ifdef BSP_UART2_RX_USING_DMA
    uart_obj[UART2_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart2_dma_rx = UART2_DMA_RX_CONFIG;
    static struct hc32_uart_rxto uart2_rx_timeout = UART2_RXTO_CONFIG;
    uart2_dma_rx.irq_callback = hc32_uart2_dma_rx_irq_handler;
#if defined (HC32F460) || defined (HC32F4A0)
    uart2_rx_timeout.irq_callback = hc32_uart2_rxto_irq_handler;
#endif
    uart_config[UART2_INDEX].rx_timeout = &uart2_rx_timeout;
    uart_config[UART2_INDEX].dma_rx = &uart2_dma_rx;
#endif
#ifdef BSP_UART2_TX_USING_DMA
    uart_obj[UART2_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart2_dma_tx = UART2_DMA_TX_CONFIG;
    uart_config[UART2_INDEX].dma_tx = &uart2_dma_tx;
#endif
#endif

#ifdef BSP_USING_UART3
    uart_obj[UART3_INDEX].uart_dma_flag = 0;
    uart_obj[UART3_INDEX].serial.config = config;
    uart_obj[UART3_INDEX].serial.config.rx_bufsz = BSP_UART3_RX_BUFSIZE;
    uart_obj[UART3_INDEX].serial.config.tx_bufsz = BSP_UART3_TX_BUFSIZE;
#if defined (HC32F460)
#ifdef BSP_UART3_RX_USING_DMA
    uart_obj[UART3_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart3_dma_rx = UART3_DMA_RX_CONFIG;
    static struct hc32_uart_rxto uart3_rx_timeout = UART3_RXTO_CONFIG;
    uart3_dma_rx.irq_callback = hc32_uart3_dma_rx_irq_handler;
    uart3_rx_timeout.irq_callback = hc32_uart3_rxto_irq_handler;
    uart_config[UART3_INDEX].rx_timeout = &uart3_rx_timeout;
    uart_config[UART3_INDEX].dma_rx = &uart3_dma_rx;
#endif
#ifdef BSP_UART3_TX_USING_DMA
    uart_obj[UART3_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart3_dma_tx = UART3_DMA_TX_CONFIG;
    uart_config[UART3_INDEX].dma_tx = &uart3_dma_tx;
#endif
#endif
#endif

#ifdef BSP_USING_UART4
    uart_obj[UART4_INDEX].uart_dma_flag = 0;
    uart_obj[UART4_INDEX].serial.config = config;
    uart_obj[UART4_INDEX].serial.config.rx_bufsz = BSP_UART4_RX_BUFSIZE;
    uart_obj[UART4_INDEX].serial.config.tx_bufsz = BSP_UART4_TX_BUFSIZE;
#if defined (HC32F460) || defined (HC32F448) || defined (HC32F472)
#ifdef BSP_UART4_RX_USING_DMA
    uart_obj[UART4_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart4_dma_rx = UART4_DMA_RX_CONFIG;
    static struct hc32_uart_rxto uart4_rx_timeout = UART4_RXTO_CONFIG;
    uart4_dma_rx.irq_callback = hc32_uart4_dma_rx_irq_handler;
#if defined (HC32F460)
    uart4_rx_timeout.irq_callback = hc32_uart4_rxto_irq_handler;
#endif
    uart_config[UART4_INDEX].rx_timeout = &uart4_rx_timeout;
    uart_config[UART4_INDEX].dma_rx = &uart4_dma_rx;
#endif
#ifdef BSP_UART4_TX_USING_DMA
    uart_obj[UART4_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart4_dma_tx = UART4_DMA_TX_CONFIG;
    uart_config[UART4_INDEX].dma_tx = &uart4_dma_tx;
#endif
#endif
#endif

#ifdef BSP_USING_UART5
    uart_obj[UART5_INDEX].uart_dma_flag = 0;
    uart_obj[UART5_INDEX].serial.config = config;
    uart_obj[UART5_INDEX].serial.config.rx_bufsz = BSP_UART5_RX_BUFSIZE;
    uart_obj[UART5_INDEX].serial.config.tx_bufsz = BSP_UART5_TX_BUFSIZE;
#if defined (HC32F448) || defined (HC32F472)
#ifdef BSP_UART5_RX_USING_DMA
    uart_obj[UART5_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart5_dma_rx = UART5_DMA_RX_CONFIG;
    static struct hc32_uart_rxto uart5_rx_timeout = UART5_RXTO_CONFIG;
    uart5_dma_rx.irq_callback = hc32_uart5_dma_rx_irq_handler;
    uart_config[UART5_INDEX].rx_timeout = &uart5_rx_timeout;
    uart_config[UART5_INDEX].dma_rx = &uart5_dma_rx;
#endif
#ifdef BSP_UART5_TX_USING_DMA
    uart_obj[UART5_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart5_dma_tx = UART5_DMA_TX_CONFIG;
    uart_config[UART5_INDEX].dma_tx = &uart5_dma_tx;
#endif
#endif
#endif

#ifdef BSP_USING_UART6
    uart_obj[UART6_INDEX].uart_dma_flag = 0;
    uart_obj[UART6_INDEX].serial.config = config;
    uart_obj[UART6_INDEX].serial.config.rx_bufsz = BSP_UART6_RX_BUFSIZE;
    uart_obj[UART6_INDEX].serial.config.tx_bufsz = BSP_UART6_TX_BUFSIZE;
#if defined (HC32F4A0)
#ifdef BSP_UART6_RX_USING_DMA
    uart_obj[UART6_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart6_dma_rx = UART6_DMA_RX_CONFIG;
    static struct hc32_uart_rxto uart6_rx_timeout = UART6_RXTO_CONFIG;
    uart6_dma_rx.irq_callback = hc32_uart6_dma_rx_irq_handler;
    uart6_rx_timeout.irq_callback = hc32_uart6_rxto_irq_handler;
    uart_config[UART6_INDEX].rx_timeout = &uart6_rx_timeout;
    uart_config[UART6_INDEX].dma_rx = &uart6_dma_rx;
#endif
#ifdef BSP_UART6_TX_USING_DMA
    uart_obj[UART6_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart6_dma_tx = UART6_DMA_TX_CONFIG;
    uart_config[UART6_INDEX].dma_tx = &uart6_dma_tx;
#endif
#endif
#endif

#ifdef BSP_USING_UART7
    uart_obj[UART7_INDEX].uart_dma_flag = 0;
    uart_obj[UART7_INDEX].serial.config = config;
    uart_obj[UART7_INDEX].serial.config.rx_bufsz = BSP_UART7_RX_BUFSIZE;
    uart_obj[UART7_INDEX].serial.config.tx_bufsz = BSP_UART7_TX_BUFSIZE;
#if defined (HC32F4A0)
#ifdef BSP_UART7_RX_USING_DMA
    uart_obj[UART7_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config uart7_dma_rx = UART7_DMA_RX_CONFIG;
    static struct hc32_uart_rxto uart7_rx_timeout = UART7_RXTO_CONFIG;
    uart7_dma_rx.irq_callback = hc32_uart7_dma_rx_irq_handler;
    uart7_rx_timeout.irq_callback = hc32_uart7_rxto_irq_handler;
    uart_config[UART7_INDEX].rx_timeout = &uart7_rx_timeout;
    uart_config[UART7_INDEX].dma_rx = &uart7_dma_rx;
#endif
#ifdef BSP_UART7_TX_USING_DMA
    uart_obj[UART7_INDEX].uart_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config uart7_dma_tx = UART7_DMA_TX_CONFIG;
    uart_config[UART7_INDEX].dma_tx = &uart7_dma_tx;
#endif
#endif
#endif

#ifdef BSP_USING_UART8
    uart_obj[UART8_INDEX].uart_dma_flag = 0;
    uart_obj[UART8_INDEX].serial.config = config;
    uart_obj[UART8_INDEX].serial.config.rx_bufsz = BSP_UART8_RX_BUFSIZE;
    uart_obj[UART8_INDEX].serial.config.tx_bufsz = BSP_UART8_TX_BUFSIZE;
#endif

#ifdef BSP_USING_UART9
    uart_obj[UART9_INDEX].uart_dma_flag = 0;
    uart_obj[UART9_INDEX].serial.config = config;
    uart_obj[UART9_INDEX].serial.config.rx_bufsz = BSP_UART9_RX_BUFSIZE;
    uart_obj[UART9_INDEX].serial.config.tx_bufsz = BSP_UART9_TX_BUFSIZE;
#endif

#ifdef BSP_USING_UART10
    uart_obj[UART10_INDEX].uart_dma_flag = 0;
    uart_obj[UART10_INDEX].serial.config = config;
    uart_obj[UART10_INDEX].serial.config.rx_bufsz = BSP_UART10_RX_BUFSIZE;
    uart_obj[UART10_INDEX].serial.config.tx_bufsz = BSP_UART10_TX_BUFSIZE;
#endif
}

#if defined (HC32F460) || defined (HC32F4A0)
/**
  * @brief  This function gets uart irq handle.
  * @param  None
  * @retval None
  */
static void hc32_get_uart_callback(void)
{
#ifdef BSP_USING_UART1
    uart_config[UART1_INDEX].rxerr_irq.irq_callback = hc32_uart1_rxerr_irq_handler;
    uart_config[UART1_INDEX].rx_irq.irq_callback = hc32_uart1_rx_irq_handler;
    uart_config[UART1_INDEX].tx_irq.irq_callback = hc32_uart1_tx_irq_handler;
    struct hc32_uart_irq_config uart1_tc_irq = UART1_TX_CPLT_CONFIG;
    uart_config[UART1_INDEX].tc_irq = uart1_tc_irq;
    uart_config[UART1_INDEX].tc_irq.irq_callback = hc32_uart1_tc_irq_handler;
#endif
#ifdef BSP_USING_UART2
    uart_config[UART2_INDEX].rxerr_irq.irq_callback = hc32_uart2_rxerr_irq_handler;
    uart_config[UART2_INDEX].rx_irq.irq_callback = hc32_uart2_rx_irq_handler;
    uart_config[UART2_INDEX].tx_irq.irq_callback = hc32_uart2_tx_irq_handler;
    struct hc32_uart_irq_config uart2_tc_irq = UART2_TX_CPLT_CONFIG;
    uart_config[UART2_INDEX].tc_irq = uart2_tc_irq;
    uart_config[UART2_INDEX].tc_irq.irq_callback = hc32_uart2_tc_irq_handler;
#endif
#ifdef BSP_USING_UART3
    uart_config[UART3_INDEX].rxerr_irq.irq_callback = hc32_uart3_rxerr_irq_handler;
    uart_config[UART3_INDEX].rx_irq.irq_callback = hc32_uart3_rx_irq_handler;
    uart_config[UART3_INDEX].tx_irq.irq_callback = hc32_uart3_tx_irq_handler;
    struct hc32_uart_irq_config uart3_tc_irq = UART3_TX_CPLT_CONFIG;
    uart_config[UART3_INDEX].tc_irq = uart3_tc_irq;
    uart_config[UART3_INDEX].tc_irq.irq_callback = hc32_uart3_tc_irq_handler;
#endif
#ifdef BSP_USING_UART4
    uart_config[UART4_INDEX].rxerr_irq.irq_callback = hc32_uart4_rxerr_irq_handler;
    uart_config[UART4_INDEX].rx_irq.irq_callback = hc32_uart4_rx_irq_handler;
    uart_config[UART4_INDEX].tx_irq.irq_callback = hc32_uart4_tx_irq_handler;
    struct hc32_uart_irq_config uart4_tc_irq = UART4_TX_CPLT_CONFIG;
    uart_config[UART4_INDEX].tc_irq = uart4_tc_irq;
    uart_config[UART4_INDEX].tc_irq.irq_callback = hc32_uart4_tc_irq_handler;
#endif
#ifdef BSP_USING_UART5
    uart_config[UART5_INDEX].rxerr_irq.irq_callback = hc32_uart5_rxerr_irq_handler;
    uart_config[UART5_INDEX].rx_irq.irq_callback = hc32_uart5_rx_irq_handler;
    uart_config[UART5_INDEX].tx_irq.irq_callback = hc32_uart5_tx_irq_handler;
    struct hc32_uart_irq_config uart5_tc_irq = UART5_TX_CPLT_CONFIG;
    uart_config[UART5_INDEX].tc_irq = uart5_tc_irq;
    uart_config[UART5_INDEX].tc_irq.irq_callback = hc32_uart5_tc_irq_handler;
#endif
#ifdef BSP_USING_UART6
    uart_config[UART6_INDEX].rxerr_irq.irq_callback = hc32_uart6_rxerr_irq_handler;
    uart_config[UART6_INDEX].rx_irq.irq_callback = hc32_uart6_rx_irq_handler;
    uart_config[UART6_INDEX].tx_irq.irq_callback = hc32_uart6_tx_irq_handler;
    struct hc32_uart_irq_config uart6_tc_irq = UART6_TX_CPLT_CONFIG;
    uart_config[UART6_INDEX].tc_irq = uart6_tc_irq;
    uart_config[UART6_INDEX].tc_irq.irq_callback = hc32_uart6_tc_irq_handler;
#endif
#ifdef BSP_USING_UART7
    uart_config[UART7_INDEX].rxerr_irq.irq_callback = hc32_uart7_rxerr_irq_handler;
    uart_config[UART7_INDEX].rx_irq.irq_callback = hc32_uart7_rx_irq_handler;
    uart_config[UART7_INDEX].tx_irq.irq_callback = hc32_uart7_tx_irq_handler;
    struct hc32_uart_irq_config uart7_tc_irq = UART7_TX_CPLT_CONFIG;
    uart_config[UART7_INDEX].tc_irq = uart7_tc_irq;
    uart_config[UART7_INDEX].tc_irq.irq_callback = hc32_uart7_tc_irq_handler;
#endif
#ifdef BSP_USING_UART8
    uart_config[UART8_INDEX].rxerr_irq.irq_callback = hc32_uart8_rxerr_irq_handler;
    uart_config[UART8_INDEX].rx_irq.irq_callback = hc32_uart8_rx_irq_handler;
    uart_config[UART8_INDEX].tx_irq.irq_callback = hc32_uart8_tx_irq_handler;
    struct hc32_uart_irq_config uart8_tc_irq = UART8_TX_CPLT_CONFIG;
    uart_config[UART8_INDEX].tc_irq = uart8_tc_irq;
    uart_config[UART8_INDEX].tc_irq.irq_callback = hc32_uart8_tc_irq_handler;
#endif
#ifdef BSP_USING_UART9
    uart_config[UART9_INDEX].rxerr_irq.irq_callback = hc32_uart9_rxerr_irq_handler;
    uart_config[UART9_INDEX].rx_irq.irq_callback = hc32_uart9_rx_irq_handler;
    uart_config[UART9_INDEX].tx_irq.irq_callback = hc32_uart9_tx_irq_handler;
    struct hc32_uart_irq_config uart9_tc_irq = UART9_TX_CPLT_CONFIG;
    uart_config[UART9_INDEX].tc_irq = uart9_tc_irq;
    uart_config[UART9_INDEX].tc_irq.irq_callback = hc32_uart9_tc_irq_handler;
#endif
#ifdef BSP_USING_UART10
    uart_config[UART10_INDEX].rxerr_irq.irq_callback = hc32_uart10_rxerr_irq_handler;
    uart_config[UART10_INDEX].rx_irq.irq_callback = hc32_uart10_rx_irq_handler;
    uart_config[UART10_INDEX].tx_irq.irq_callback = hc32_uart10_tx_irq_handler;
    struct hc32_uart_irq_config uart10_tc_irq = UART10_TX_CPLT_CONFIG;
    uart_config[UART10_INDEX].tc_irq = uart10_tc_irq;
    uart_config[UART10_INDEX].tc_irq.irq_callback = hc32_uart10_tc_irq_handler;
#endif
}
#elif defined (HC32F448) || defined (HC32F472)
/**
  * @brief  This function gets uart irq handle.
  * @param  None
  * @retval None
  */
static void hc32_get_uart_callback(void)
{
#ifdef BSP_USING_UART1
    struct hc32_uart_irq_config uart1_tc_irq = UART1_TX_CPLT_CONFIG;
    uart_config[UART1_INDEX].tc_irq = uart1_tc_irq;
    uart_config[UART1_INDEX].tc_irq.irq_callback = hc32_uart1_tc_irq_handler;
#endif
#ifdef BSP_USING_UART2
    struct hc32_uart_irq_config uart2_tc_irq = UART2_TX_CPLT_CONFIG;
    uart_config[UART2_INDEX].tc_irq = uart2_tc_irq;
    uart_config[UART2_INDEX].tc_irq.irq_callback = hc32_uart2_tc_irq_handler;
#endif
#ifdef BSP_USING_UART3
    struct hc32_uart_irq_config uart3_tc_irq = UART3_TX_CPLT_CONFIG;
    uart_config[UART3_INDEX].tc_irq = uart3_tc_irq;
    uart_config[UART3_INDEX].tc_irq.irq_callback = hc32_uart3_tc_irq_handler;
#endif
#ifdef BSP_USING_UART4
    struct hc32_uart_irq_config uart4_tc_irq = UART4_TX_CPLT_CONFIG;
    uart_config[UART4_INDEX].tc_irq = uart4_tc_irq;
    uart_config[UART4_INDEX].tc_irq.irq_callback = hc32_uart4_tc_irq_handler;
#endif
#ifdef BSP_USING_UART5
    struct hc32_uart_irq_config uart5_tc_irq = UART5_TX_CPLT_CONFIG;
    uart_config[UART5_INDEX].tc_irq = uart5_tc_irq;
    uart_config[UART5_INDEX].tc_irq.irq_callback = hc32_uart5_tc_irq_handler;
#endif
#ifdef BSP_USING_UART6
    struct hc32_uart_irq_config uart6_tc_irq = UART6_TX_CPLT_CONFIG;
    uart_config[UART6_INDEX].tc_irq = uart6_tc_irq;
    uart_config[UART6_INDEX].tc_irq.irq_callback = hc32_uart6_tc_irq_handler;
#endif
}
#endif /* HC32F448, HC32F472 */

static const struct rt_uart_ops hc32_uart_ops =
{
    .configure = hc32_configure,
    .control = hc32_control,
    .putc = hc32_putc,
    .getc = hc32_getc,
    .transmit = hc32_transmit
};

int rt_hw_usart_init(void)
{
    rt_err_t result = RT_EOK;
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct hc32_uart);

    hc32_uart_get_info();
    hc32_get_uart_callback();

    for (int i = 0; i < obj_num; i++)
    {
        /* init UART object */
        uart_obj[i].serial.ops  = &hc32_uart_ops;
        uart_obj[i].config      = &uart_config[i];
#if defined (HC32F460) || defined (HC32F4A0)
        /* register the handle */
        hc32_install_irq_handler(&uart_config[i].rxerr_irq.irq_config, uart_config[i].rxerr_irq.irq_callback, RT_FALSE);
#endif
#ifdef RT_SERIAL_USING_DMA
        if (uart_obj[i].uart_dma_flag & RT_DEVICE_FLAG_DMA_RX)
        {
            hc32_install_irq_handler(&uart_config[i].dma_rx->irq_config, uart_config[i].dma_rx->irq_callback, RT_FALSE);
#if defined (HC32F460) || defined (HC32F4A0)
            hc32_install_irq_handler(&uart_config[i].rx_timeout->irq_config, uart_config[i].rx_timeout->irq_callback, RT_FALSE);
#endif
        }
        if (uart_obj[i].uart_dma_flag & RT_DEVICE_FLAG_DMA_TX)
        {
            hc32_install_irq_handler(&uart_config[i].tc_irq.irq_config, uart_config[i].tc_irq.irq_callback, RT_FALSE);
        }
#endif
        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial,
                                       uart_obj[i].config->name,
                                       (RT_DEVICE_FLAG_RDWR   |
                                        uart_obj[i].uart_dma_flag),
                                       &uart_obj[i]);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif

#endif /* RT_USING_SERIAL_V2 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
