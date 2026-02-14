/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-02-17     yeml           the first version
 */

#include "drv_uart_v2.h"
#ifdef RT_USING_SERIAL_V2

#if !defined(BSP_USING_UART0) && \
    !defined(BSP_USING_UART1) && \
    !defined(BSP_USING_UART2) && \
    !defined(BSP_USING_UART3) && \
    !defined(BSP_USING_UART4)
    #error "Please define at least one UARTx"
#endif

enum
{
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
#ifdef BSP_USING_UART4
    UART4_INDEX,
#endif
};

static struct tae32_uart_config uart_config[] =
{
#ifdef BSP_USING_UART0
    UART0_CONFIG,
#endif

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
};

static struct tae32_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};

static void uart_isr(struct rt_serial_device *serial)
{
    struct tae32_uart *uart;
    uint32_t int_en, int_pending;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct tae32_uart, serial);

    // All Interrupt Enalbe and Pending Get
    int_en = __LL_UART_AllIntEn_Get(uart->Instance);
    int_pending = __LL_UART_AllIntPnd_Get(uart->Instance);
    bool rx_9bits_en;
    // Rx Full Interrupt Handler
    if ((int_en & UART0_INTEN_RFIE_Msk) && (int_pending & UART0_INT_RXFI_Msk))
    {
        // interrupt pending auto clear
        struct rt_serial_rx_fifo *rx_fifo;
        rx_fifo = (struct rt_serial_rx_fifo *)serial->serial_rx;
        RT_ASSERT(rx_fifo != RT_NULL);

        rx_9bits_en = (bool)(__LL_UART_IsExtBitEn(uart->Instance) && !__LL_UART_IsRxExtAddrMatchMode(uart->Instance) &&
                             (UART_DatLenETypeDef)__LL_UART_DatLen_Get(uart->Instance) >= UART_DAT_LEN_8b);

        if (rx_9bits_en)
        {
            rt_ringbuffer_putchar(&(rx_fifo->rb), __LL_UART_RxDat9bits_Read(uart->Instance));
        }
        else
        {
            rt_ringbuffer_putchar(&(rx_fifo->rb), __LL_UART_RxDat8bits_Read(uart->Instance));
        }

        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }
    // Tx Empty Interrupt Handler
    else if ((int_en & UART0_INTEN_TEIE_Msk) && (int_pending & UART0_INT_TXEI_Msk))
    {
        struct rt_serial_tx_fifo *tx_fifo;
        tx_fifo = (struct rt_serial_tx_fifo *)serial->serial_tx;
        RT_ASSERT(tx_fifo != RT_NULL);

        rt_uint8_t put_char = 0;
        if (rt_ringbuffer_getchar(&(tx_fifo->rb), &put_char))
        {
            __LL_UART_TxDat9bits_Write(uart->Instance, put_char);
        }
        else
        {
            __LL_UART_TxEmpty_INT_Dis(uart->Instance);
            __LL_UART_TxDone_INT_En(uart->Instance);
        }
    }
    // Tx Done Interrupt Handler
    else if ((int_en & UART0_INTEN_TDIE_Msk) && (int_pending & UART0_INT_TDIF_Msk))
    {

        __LL_UART_TxDone_INT_Dis(uart->Instance);
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);
        __LL_UART_TxDoneIntPnd_Clr(uart->Instance);
    }
}

#if defined(BSP_USING_UART0)

void UART0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART0_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

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

#if defined(BSP_USING_UART4)
void UART4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&(uart_obj[UART4_INDEX].serial));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

static const UART_LLCfgTypeDef uart_ll_cfg_def = {
    .tx_rx_swap_en = false,
    .rx_timeout_en = false,
    .one_wire_en = false,
    .tx_pol = UART_PIN_POL_INACT_HIGH,
    .rx_pol = UART_PIN_POL_INACT_HIGH,
    .bit_order = UART_BIT_ORDER_LSB,
    .tx_fifo_empty_thres = 0,   // 0~15
    .rx_fifo_full_thres  = 1,   // 1~16
    .rx_timeout = 0,
    .rx_timeout_mode = UART_RTO_MODE_FNE_RXIDEL,
};


LL_StatusETypeDef ll_uart_Init(UART_TypeDef *Instance, UART_InitTypeDef *init)
{
    uint32_t baud_rate = 1;
    UART_LLCfgTypeDef *ll_cfg;
    UART_HandleTypeDef *uart_hdl;

    assert_param(IS_UART_ALL_INSTANCE(Instance));
    assert_param(init != NULL);
    assert_param(init->baudrate);

    if (!IS_UART_ALL_INSTANCE(Instance) || init == NULL || !init->baudrate) {
        return LL_INVALID;
    }
    
    /* It must disable the UART while configuring certain registers */
    __LL_UART_Dis(Instance);

    LL_FUNC_ALTER(init->ll_cfg == NULL, ll_cfg = (UART_LLCfgTypeDef *)&uart_ll_cfg_def, ll_cfg = init->ll_cfg);
    
    /* init the low level hardware eg. Clock, NVIC */
    LL_UART_MspInit(Instance);

    /* Reset UART FIFO */
    __LL_UART_TxFIFO_Reset(Instance);
    __LL_UART_RxFIFO_Reset(Instance);

    __LL_UART_TxPinPol_Set(Instance, ll_cfg->tx_pol);
    __LL_UART_RxPinPol_Set(Instance, ll_cfg->rx_pol);
    __LL_UART_BitOrder_Set(Instance, ll_cfg->bit_order);
    __LL_UART_RxFIFOFullThres_Set(Instance, ll_cfg->rx_fifo_full_thres);
    __LL_UART_TxFIFOEmptyThres_Set(Instance, ll_cfg->tx_fifo_empty_thres);
    __LL_UART_RxTimeoutTime_Set(Instance, ll_cfg->rx_timeout);
    LL_FUNC_ALTER(ll_cfg->tx_rx_swap_en, __LL_UART_TxRxPinSwap_En(Instance), __LL_UART_TxRxPinSwap_Dis(Instance));
    LL_FUNC_ALTER(ll_cfg->one_wire_en, __LL_UART_OneWire_En(Instance), __LL_UART_OneWire_Dis(Instance));
    LL_FUNC_ALTER(ll_cfg->rx_timeout_en, __LL_UART_RxTimeout_En(Instance), __LL_UART_RxTimeout_Dis(Instance));

    if ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) && (LL_IsExtCfgEnGrp(LL_EXT_CFG_GRP_MASK_UART))) {
        __LL_UART_RTOMode_Set(Instance, ll_cfg->rx_timeout_mode);
    }

    if (init->parity == UART_PARITY_NO) {
        __LL_UART_Parity_Dis(Instance);
    } else {
        __LL_UART_Parity_En(Instance);
        __LL_UART_Parity_Set(Instance, init->parity);
    }

    __LL_UART_StopLen_Set(Instance, init->stop_len);
    __LL_UART_DatLen_Set(Instance, init->dat_len);

    if (init->ext_bit_en) {
        __LL_UART_ExtBit_En(Instance);

        __LL_UART_RxExtMode_Set(Instance, init->rx_ext_mode);
        __LL_UART_RxExtAddr_Set(Instance, init->rx_addr_ext);
    } else {
        __LL_UART_ExtBit_Dis(Instance);
    }

    /* Baudrate Config */
    if (Instance == UART0 || Instance == UART1 || Instance == UART2) {
        baud_rate = (LL_RCU_APB0ClkGet() + init->baudrate / 2) / init->baudrate;
    } else if (Instance == UART3 || Instance == UART4) {
        baud_rate = (LL_RCU_APB1ClkGet() + init->baudrate / 2) / init->baudrate;
    }

    __LL_UART_Baudrate_Set(Instance, baud_rate);
    __LL_UART_OverSampleMode_Set(Instance, init->over_samp);

    __LL_UART_AllIntPnd_Clr(Instance);

    __LL_UART_Tx_En(Instance);
    __LL_UART_Rx_En(Instance);

    __LL_UART_En(Instance);

    return LL_OK;
}


static rt_err_t tae32_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct tae32_uart *uart;
    UART_InitTypeDef uart_init;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    rt_memset(&uart_init, 0, sizeof(uart_init));

    uart = rt_container_of(serial, struct tae32_uart, serial);
    uart_init.baudrate = cfg->baud_rate;

#ifdef BSP_UART_USING_OVER_SAMP16X
    uart_init.over_samp = UART_OVER_SAMP_16X;
#else
    uart_init.over_samp = UART_OVER_SAMP_8X;
#endif
    switch (cfg->data_bits)
    {
    case DATA_BITS_5:
        uart_init.dat_len = UART_DAT_LEN_5b;
        break;
    case DATA_BITS_6:
        uart_init.dat_len = UART_DAT_LEN_6b;
        break;
    case DATA_BITS_7:
        uart_init.dat_len = UART_DAT_LEN_7b;
        break;
    case DATA_BITS_8:
        uart_init.dat_len = UART_DAT_LEN_8b;
        break;
    default:
        uart_init.dat_len = UART_DAT_LEN_8b;
        break;
    }
    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        uart_init.stop_len = UART_STOP_LEN_1b;
        break;
    case STOP_BITS_2:
        uart_init.stop_len = UART_STOP_LEN_2b;
        break;
    default:
        uart_init.stop_len = UART_STOP_LEN_1b;
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_NONE:
        uart_init.parity = UART_PARITY_NO;
        break;
    case PARITY_ODD:
        uart_init.parity = UART_PARITY_ODD;
        break;
    case PARITY_EVEN:
        uart_init.parity = UART_PARITY_EVEN;
        break;
    default:
        uart_init.parity = UART_PARITY_NO;
        break;
    }
    if (ll_uart_Init(uart->Instance, &uart_init) != LL_OK)
    {
        return -RT_ERROR;
    }
    return RT_EOK;
}


static rt_err_t tae32_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct tae32_uart *uart;
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct tae32_uart, serial);

    if (ctrl_arg & (RT_DEVICE_FLAG_RX_BLOCKING | RT_DEVICE_FLAG_RX_NON_BLOCKING))
    {
        if (uart->dma_flag & RT_DEVICE_FLAG_DMA_RX)
            ctrl_arg = RT_DEVICE_FLAG_DMA_RX;
        else
            ctrl_arg = RT_DEVICE_FLAG_INT_RX;
    }
    else if (ctrl_arg & (RT_DEVICE_FLAG_TX_BLOCKING | RT_DEVICE_FLAG_TX_NON_BLOCKING))
    {
        if (uart->dma_flag & RT_DEVICE_FLAG_DMA_TX)
            ctrl_arg = RT_DEVICE_FLAG_DMA_TX;
        else
            ctrl_arg = RT_DEVICE_FLAG_INT_TX;
    }

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->config->irq_type);

        /* disable interrupt */
        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX)
        {
            __LL_UART_RxFull_INT_Dis(uart->Instance);
        }
        else if (ctrl_arg == RT_DEVICE_FLAG_INT_TX)
        {
            __LL_UART_TxEmpty_INT_Dis(uart->Instance);
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->config->irq_type);

        /* enable interrupt */
        if (ctrl_arg == RT_DEVICE_FLAG_INT_RX)
        {
            __LL_UART_RxFIFO_Reset(uart->Instance);
            __LL_UART_RxFull_INT_En(uart->Instance);
        }
        else if (ctrl_arg == RT_DEVICE_FLAG_INT_TX)
        {
            __LL_UART_TxFIFO_Reset(uart->Instance);
            __LL_UART_TxDoneIntPnd_Clr(uart->Instance);
            __LL_UART_TxEmpty_INT_En(uart->Instance);
            __LL_UART_TxDone_INT_En(uart->Instance);
        }
        break;

    case RT_DEVICE_CTRL_CONFIG:
        if (ctrl_arg & (RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX))
        {
#ifdef RT_SERIAL_USING_DMA
            ;
#endif
        }
        else
        {
            tae32_uart_control(serial, RT_DEVICE_CTRL_SET_INT, (void *)ctrl_arg);
        }
        break;

    case RT_DEVICE_CHECK_OPTMODE:
        if (ctrl_arg & RT_DEVICE_FLAG_DMA_TX)
            return RT_SERIAL_TX_BLOCKING_NO_BUFFER;
        else
            return RT_SERIAL_TX_BLOCKING_BUFFER;

    case RT_DEVICE_CTRL_CLOSE:
        LL_UART_DeInit(uart->Instance);
        break;
    }

    return RT_EOK;
}

int tae32_uart_putc(struct rt_serial_device *serial, char ch)
{
    struct tae32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct tae32_uart, serial);
    __LL_UART_TxDoneIntPnd_Clr(uart->Instance);
    __LL_UART_TxDat9bits_Write(uart->Instance, ch);
    while (!__LL_UART_IsTxDoneIntPnd(uart->Instance))
        ;
    return RT_EOK;
}

int tae32_uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct tae32_uart *uart;
    bool rx_9bits_en;
    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct tae32_uart, serial);

    ch = -1;
    rx_9bits_en = (bool)(__LL_UART_IsExtBitEn(uart->Instance) && !__LL_UART_IsRxExtAddrMatchMode(uart->Instance) &&
                         (UART_DatLenETypeDef)__LL_UART_DatLen_Get(uart->Instance) >= UART_DAT_LEN_8b);

    if (!(__LL_UART_IsRxFIFOEmpty(uart->Instance)))
    {
        if (rx_9bits_en)
        {
            ch = (uint16_t)(__LL_UART_RxDat9bits_Read(uart->Instance));
        }
        else
        {
            ch = (uint8_t)(__LL_UART_RxDat8bits_Read(uart->Instance));
        }
    }
    return ch;
}

rt_ssize_t tae32_uart_transmit(struct rt_serial_device *serial,
                         rt_uint8_t *buf,
                         rt_size_t size,
                         rt_uint32_t tx_flag)
{
    struct tae32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(buf != RT_NULL);
    uart = rt_container_of(serial, struct tae32_uart, serial);
#ifdef RT_SERIAL_USING_DMA
    if (uart->dma_flag & RT_DEVICE_FLAG_DMA_TX)
    {
        /*DMA设置发送*/
        return size;
    }
#endif
    tae32_uart_control(serial, RT_DEVICE_CTRL_SET_INT, (void *)tx_flag);

    return size;
}

static void tae32_uart_get_config(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
#ifdef BSP_USING_UART0
    uart_obj[UART0_INDEX].Instance = UART0;
    uart_obj[UART0_INDEX].serial.config = config;

    uart_obj[UART0_INDEX].serial.config.rx_bufsz = BSP_UART0_RX_BUFSIZE;
    uart_obj[UART0_INDEX].serial.config.tx_bufsz = BSP_UART0_TX_BUFSIZE;

#endif

#ifdef BSP_USING_UART1
    uart_obj[UART1_INDEX].Instance = UART1;
    uart_obj[UART1_INDEX].serial.config = config;

    uart_obj[UART1_INDEX].serial.config.rx_bufsz = BSP_UART1_RX_BUFSIZE;
    uart_obj[UART1_INDEX].serial.config.tx_bufsz = BSP_UART1_TX_BUFSIZE;

#endif

#ifdef BSP_USING_UART2
    uart_obj[UART2_INDEX].Instance = UART2;
    uart_obj[UART2_INDEX].serial.config = config;

    uart_obj[UART2_INDEX].serial.config.rx_bufsz = BSP_UART2_RX_BUFSIZE;
    uart_obj[UART2_INDEX].serial.config.tx_bufsz = BSP_UART2_TX_BUFSIZE;

#endif

#ifdef BSP_USING_UART3
    uart_obj[UART3_INDEX].Instance = UART3;
    uart_obj[UART3_INDEX].serial.config = config;

    uart_obj[UART3_INDEX].serial.config.rx_bufsz = BSP_UART3_RX_BUFSIZE;
    uart_obj[UART3_INDEX].serial.config.tx_bufsz = BSP_UART3_TX_BUFSIZE;

#endif

#ifdef BSP_USING_UART4
    uart_obj[UART4_INDEX].Instance = UART4;
    uart_obj[UART4_INDEX].serial.config = config;

    uart_obj[UART4_INDEX].serial.config.rx_bufsz = BSP_UART4_RX_BUFSIZE;
    uart_obj[UART4_INDEX].serial.config.tx_bufsz = BSP_UART4_TX_BUFSIZE;

#endif
}

static const struct rt_uart_ops tae32_uart_ops =
{
    .configure = tae32_uart_configure,
    .control = tae32_uart_control,
    .putc = tae32_uart_putc,
    .getc = tae32_uart_getc,
    .transmit = tae32_uart_transmit
};

int rt_hw_usart_init(void)
{
    rt_err_t result = 0;
    rt_size_t obj_num = sizeof(uart_obj) / sizeof(struct tae32_uart);

    tae32_uart_get_config();
    for (int i = 0; i < obj_num; i++)
    {
        /* init UART object */
        uart_obj[i].config = &uart_config[i];
        uart_obj[i].serial.ops = &tae32_uart_ops;
        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial,
                                       uart_obj[i].config->name,
                                       RT_DEVICE_FLAG_RDWR,
                                       NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif
