/*
 * Copyright (C) 2021, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-19     pjq          first version
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtdevice.h>
#include <rthw.h>
#include "gpio.h"
#include "uart.h"
#include "drv_usart.h"

#ifdef RT_USING_SERIAL

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1)
#error "Please define at least one BSP_USING_UARTx"
/* UART instance can be selected at menuconfig -> Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable UART */
#endif

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/* HC32 config Rx timeout */
struct hc32_uart_rxto
{
    rt_uint32_t     channel;
    rt_size_t       timeout_bits;
};

/* HC32 UART index */
struct uart_index
{
    rt_uint8_t index;
    rt_uint8_t idx;
};

/* HC32 UART irq handler */
struct uart_irq_handler
{
    void (*tx_irq_handler)(void);
    void (*rxerr_irq_handler)(void);
    void (*rx_irq_handler)(void);
    void (*cts_irq_handler)(void);
    void (*pei_irq_handler)(void);
};

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/


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
#ifdef BSP_USING_UART0
    UART0_INDEX,
#endif
#ifdef BSP_USING_UART1
    UART1_INDEX,
#endif
    UART_INDEX_MAX,
};

static const struct uart_index uart_map[] =
{
#ifdef BSP_USING_UART0
    {UART0_INDEX, UARTCH0},
#endif
#ifdef BSP_USING_UART1
    {UART1_INDEX, UARTCH1},
#endif
};

static struct hc32_uart_config uart_config[] =
{
#ifdef BSP_USING_UART0
    {                                                               \
        .name = "uart0",                                            \
        .idx = UARTCH0,                                             \
    },
#endif
#ifdef BSP_USING_UART1
    {                                                               \
        .name = "uart1",                                            \
        .idx = UARTCH1,                                             \
    }
#endif
};

#ifdef BSP_USING_UART0
static int uart0_rx_flag;
#endif
#ifdef BSP_USING_UART1
static int uart1_rx_flag;
#endif
static struct hc32_uart uart_obj[sizeof(uart_config) / sizeof(uart_config[0])] = {0};
static const struct uart_irq_handler uart_irq_handlers[sizeof(uart_obj) / sizeof(uart_obj[0])];

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

//static uint32_t hc32_get_uart_index(M0P_UART_TypeDef *Instance)
static uint32_t hc32_get_uart_index(uint8_t idx)
{
    uint32_t index = UART_INDEX_MAX;

    for (uint8_t i = 0U; i < ARRAY_SZ(uart_map); i++)
    {
        if (uart_map[i].idx == idx)
        {
            index = uart_map[i].index;
            RT_ASSERT(index < UART_INDEX_MAX)
            break;
        }
    }

    return index;
}

#if defined(BSP_USING_UART0)
void uart0_gpioinit(void)
{
    stc_gpio_config_t stcGpioCfg;
    DDL_ZERO_STRUCT(stcGpioCfg);
    stcGpioCfg.enDir = GpioDirOut;
    Gpio_Init(GpioPortA,GpioPin9,&stcGpioCfg);
    Gpio_SetAfMode(GpioPortA,GpioPin9,GpioAf1);//TX
    stcGpioCfg.enDir = GpioDirIn;
    Gpio_Init(GpioPortA,GpioPin10,&stcGpioCfg);
    Gpio_SetAfMode(GpioPortA,GpioPin10,GpioAf1);//RX
}
#endif

#if defined(BSP_USING_UART1)
void uart1_gpioinit(void)
{
    stc_gpio_config_t stcGpioCfg;

    DDL_ZERO_STRUCT(stcGpioCfg);
    stcGpioCfg.enDir = GpioDirOut;
    Gpio_Init(GpioPortA,GpioPin2,&stcGpioCfg);
    Gpio_SetAfMode(GpioPortA,GpioPin2,GpioAf1);//TX
    stcGpioCfg.enDir = GpioDirIn;
    Gpio_Init(GpioPortA,GpioPin3,&stcGpioCfg);
    Gpio_SetAfMode(GpioPortA,GpioPin3,GpioAf1);//RX
}
#endif

static rt_err_t hc32_configure(struct rt_serial_device *serial,
                               struct serial_configure *cfg)
{
    struct hc32_uart *uart;
    uint16_t u16Scnt = 0;
    stc_uart_config_t  stcConfig;
    stc_uart_irq_cb_t stcUartIrqCb;
    stc_uart_multimode_t stcMulti;
    stc_uart_baud_t stcBaud;
    uint8_t index;
    en_uart_mmdorck_t enTb8;

    DDL_ZERO_STRUCT(stcConfig);
    DDL_ZERO_STRUCT(stcUartIrqCb);
    DDL_ZERO_STRUCT(stcMulti);
    DDL_ZERO_STRUCT(stcBaud);

    RT_ASSERT(RT_NULL != cfg);
    RT_ASSERT(RT_NULL != serial);

    uart = rt_container_of(serial, struct hc32_uart, serial);
#if defined(BSP_USING_UART0)
    if (uart->config->idx == UARTCH0)
    {
        uart0_gpioinit();
    }
#endif

#if defined(BSP_USING_UART1)
    if (uart->config->idx == UARTCH1)
    {
        uart1_gpioinit();
    }
#endif

    /* Configure USART initialization structure */
    index = hc32_get_uart_index(uart->config->idx);
    stcUartIrqCb.pfnRxIrqCb   = uart_irq_handlers[index].rx_irq_handler;
    stcUartIrqCb.pfnTxIrqCb   = uart_irq_handlers[index].tx_irq_handler;
    stcUartIrqCb.pfnRxFEIrqCb = uart_irq_handlers[index].rxerr_irq_handler;
    stcUartIrqCb.pfnPEIrqCb   = uart_irq_handlers[index].pei_irq_handler;
    stcUartIrqCb.pfnCtsIrqCb  = uart_irq_handlers[index].cts_irq_handler;
    stcConfig.pstcIrqCb = &stcUartIrqCb;
    stcConfig.bTouchNvic = TRUE;

    stcConfig.enRunMode = UartMode3;
    stcMulti.enMulti_mode = UartNormal;

    if(BIT_ORDER_LSB == cfg->bit_order)
    {

    }
    else
    {

    }

    switch(cfg->stop_bits)
    {
    case STOP_BITS_1:
        stcConfig.enStopBit = Uart1bit;
        break;
    case STOP_BITS_2:
        stcConfig.enStopBit = Uart2bit;
        break;
    default:
        break;
    }

    switch(cfg->parity)
    {
    case PARITY_NONE:
        enTb8 = UartDataOrAddr;
        break;
    case PARITY_EVEN:
        enTb8 = UartEven;
        break;
    case PARITY_ODD:
        enTb8 = UartOdd;
        break;
    default:
        enTb8 = UartDataOrAddr;
        break;
    }

    switch(cfg->data_bits)
    {
    case DATA_BITS_8:
        break;
    default:
        return -RT_ERROR;
    }

    Uart_SetMMDOrCk(uart->config->idx, enTb8);
    stcConfig.pstcMultiMode = &stcMulti;
    Uart_Init(uart->config->idx, &stcConfig);

    Uart_SetClkDiv(uart->config->idx, Uart8Or16Div);
    stcBaud.u32Pclk = Sysctrl_GetPClkFreq();
    stcBaud.enRunMode = UartMode3;
    stcBaud.u32Baud = cfg->baud_rate;
    u16Scnt = Uart_CalScnt(uart->config->idx, &stcBaud);
    Uart_SetBaud(uart->config->idx, u16Scnt);
    
    Uart_ClrStatus(uart->config->idx, UartTC);
    Uart_ClrStatus(uart->config->idx, UartRC);
    Uart_DisableIrq(uart->config->idx, UartTxIrq);
    Uart_DisableIrq(uart->config->idx, UartRxIrq);
    Uart_EnableFunc(uart->config->idx, UartRx);

    return RT_EOK;
}

static rt_err_t hc32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct hc32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = rt_container_of(serial, struct hc32_uart, serial);

    switch (cmd)
    {
    /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        Uart_DisableIrq(uart->config->idx, UartRxIrq);
        break;

    /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        Uart_ClrStatus(uart->config->idx, UartRC);
        Uart_EnableIrq(uart->config->idx, UartRxIrq);
        break;

    case RT_DEVICE_CTRL_CLOSE:
        break;
    }

    return RT_EOK;
}

static int hc32_putc(struct rt_serial_device *serial, char c)
{
    struct hc32_uart *uart;

    RT_ASSERT(RT_NULL != serial);

    uart = rt_container_of(serial, struct hc32_uart, serial);
    
    if(serial->parent.open_flag & RT_DEVICE_FLAG_INT_TX)
    {
        if (Uart_GetStatus(uart->config->idx, UartTC) == FALSE)
        {
            return -1;
        }
    }
    Uart_SendData(uart->config->idx, c);

    return 1;
}

static int hc32_getc(struct rt_serial_device *serial)
{
    int ch= -1;
    struct hc32_uart *uart;

    RT_ASSERT(RT_NULL != serial);

    uart = rt_container_of(serial, struct hc32_uart, serial);

#if defined(BSP_USING_UART0)
    if (uart->config->idx == UARTCH0)
    {
        if (serial->parent.open_flag & RT_DEVICE_FLAG_INT_RX)
        {
            if (uart0_rx_flag)
            {
                ch = Uart_ReceiveData(uart->config->idx);
                uart0_rx_flag = 0;
            }
        }
        else
        {
            if(Uart_GetStatus(uart->config->idx, UartRC))
            {
                Uart_ClrStatus(uart->config->idx, UartRC);
                ch = Uart_ReceiveData(uart->config->idx);
            }
        }
    }
#endif
#if defined(BSP_USING_UART1)
    if (uart->config->idx == UARTCH1)
    {
        if (serial->parent.open_flag & RT_DEVICE_FLAG_INT_RX)
        {
            if (uart1_rx_flag)
            {
                ch = Uart_ReceiveData(uart->config->idx);
                uart1_rx_flag = 0;
            }
        }
        else
        {
            if(Uart_GetStatus(uart->config->idx, UartRC))
            {
                Uart_ClrStatus(uart->config->idx, UartRC);
                ch = Uart_ReceiveData(uart->config->idx);
            }
        }
    }
#endif

    return ch;
}

static rt_ssize_t hc32_dma_transmit(struct rt_serial_device *serial,
                                   rt_uint8_t *buf,
                                   rt_size_t size,
                                   int direction)
{

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
}

static void hc32_uart_cts_irq_handler(struct hc32_uart *uart)
{
    RT_ASSERT(RT_NULL != uart);
}

static void hc32_uart_pei_irq_handler(struct hc32_uart *uart)
{
    RT_ASSERT(RT_NULL != uart);
}

#ifdef RT_SERIAL_USING_DMA
static void hc32_dma_config(struct rt_serial_device *serial, rt_ubase_t flag)
{

}
#endif

#if defined(BSP_USING_UART0)
static void hc32_uart0_rx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart0_rx_flag = 1;
    hc32_uart_rx_irq_handler(&uart_obj[UART0_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart0_tx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_tx_irq_handler(&uart_obj[UART0_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart0_rxerr_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_rxerr_irq_handler(&uart_obj[UART0_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart0_cts_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_cts_irq_handler(&uart_obj[UART0_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart0_pei_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_pei_irq_handler(&uart_obj[UART0_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)
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

static void hc32_uart1_rx_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart1_rx_flag = 1;
    hc32_uart_rx_irq_handler(&uart_obj[UART1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart1_cts_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_cts_irq_handler(&uart_obj[UART1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}

static void hc32_uart1_pei_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    hc32_uart_pei_irq_handler(&uart_obj[UART1_INDEX]);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

static const struct uart_irq_handler uart_irq_handlers[] =
{
#ifdef BSP_USING_UART0
    {   hc32_uart0_tx_irq_handler, hc32_uart0_rxerr_irq_handler, hc32_uart0_rx_irq_handler,
        hc32_uart0_cts_irq_handler, hc32_uart0_pei_irq_handler
    },
#endif
#ifdef BSP_USING_UART1
    {   hc32_uart1_tx_irq_handler, hc32_uart1_rxerr_irq_handler, hc32_uart1_rx_irq_handler,
        hc32_uart1_cts_irq_handler, hc32_uart1_pei_irq_handler
    },
#endif
};

static void hc32_uart_get_dma_config(void)
{

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

    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,TRUE);
#ifdef BSP_USING_UART0
    Sysctrl_SetPeripheralGate(SysctrlPeripheralUart0,TRUE);
#endif
#ifdef BSP_USING_UART1
    Sysctrl_SetPeripheralGate(SysctrlPeripheralUart1,TRUE);
#endif

    for (int i = 0; i < obj_num; i++)
    {
        /* init UART object */
        uart_obj[i].serial.ops    = &hc32_uart_ops;
        uart_obj[i].serial.config = config;
        uart_obj[i].config = &uart_config[i];

        /* register UART device */
        result = rt_hw_serial_register(&uart_obj[i].serial,
                                       uart_obj[i].config->name,
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
