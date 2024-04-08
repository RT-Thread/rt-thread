/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2018/10/28     Bernard           Unify UART driver for FSL library.
 * 2019/09/07     niannianyouyu     Add the driver of UART1
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_uart.h"

#include "fsl_lpuart.h"

struct fsl_uart
{
    LPUART_Type *uart_base;
    IRQn_Type irqn;

    struct rt_serial_device *serial;
    char *device_name;
};

static rt_err_t  uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg);
static rt_err_t  uart_control(struct rt_serial_device *serial, int cmd, void *arg);
static int       uart_putc(struct rt_serial_device *serial, char c);
static int       uart_getc(struct rt_serial_device *serial);
static rt_ssize_t uart_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction);

static void     uart_irq_handler(int irqno, void *param);

const struct rt_uart_ops _uart_ops =
{
    uart_configure,
    uart_control,
    uart_putc,
    uart_getc,
    uart_dma_transmit
};

static void uart_isr(struct rt_serial_device *serial);

#if defined(BSP_USING_UART0)
struct rt_serial_device serial0;

void LPUART0_IRQHandler(void)
{
    uart_isr(&serial0);
}
#endif

#if defined(BSP_USING_UART1)
struct rt_serial_device serial1;

void LPUART1_IRQHandler(void)
{
    uart_isr(&serial1);
}
#endif

static const struct fsl_uart uarts[] =
{
#ifdef BSP_USING_UART0
    {
        LPUART0,
        LPUART0_IRQn,
        &serial0,
        "uart0",
    },
    #ifdef BSP_USING_UART1
    {
        LPUART1,
        LPUART1_IRQn,
        &serial1,
        "uart1",
    },
#endif
#endif
};


/*
 * UART Initiation
 */
int rt_hw_uart_init(void)
{
    int i;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    for (i = 0; i < sizeof(uarts) / sizeof(uarts[0]); i++)
    {
        uarts[i].serial->ops    = &_uart_ops;
        uarts[i].serial->config = config;

        /* register UART device */
        rt_hw_serial_register(uarts[i].serial,
                              uarts[i].device_name,
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              (void *)&uarts[i]);
    }

    return 0;
}

/*
 * UART interface
 */
static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct fsl_uart *uart;
    lpuart_config_t config;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = (struct fsl_uart *)serial->parent.user_data;

    LPUART_GetDefaultConfig(&config);
    config.baudRate_Bps = cfg->baud_rate;

    switch (cfg->data_bits)
    {
#if defined(FSL_FEATURE_LPUART_HAS_7BIT_DATA_SUPPORT) && FSL_FEATURE_LPUART_HAS_7BIT_DATA_SUPPORT
    case DATA_BITS_7:
        config.dataBitsCount = kLPUART_SevenDataBits;
        break;
#endif

    default:
        config.dataBitsCount = kLPUART_EightDataBits;
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_2:
        config.stopBitCount = kLPUART_TwoStopBit;
        break;
    default:
        config.stopBitCount = kLPUART_OneStopBit;
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_ODD:
        config.parityMode = kLPUART_ParityOdd;
        break;
    case PARITY_EVEN:
        config.parityMode = kLPUART_ParityEven;
        break;
    default:
        config.parityMode = kLPUART_ParityDisabled;
        break;
    }

    config.enableTx = true;
    config.enableRx = true;

    CLOCK_SetIpSrc(kCLOCK_Lpuart0, kCLOCK_IpSrcFircAsync);

    uint32_t uartClkSrcFreq0 = CLOCK_GetIpFreq(kCLOCK_Lpuart0);
    LPUART_Init(uart->uart_base, &config, uartClkSrcFreq0);
    LPUART_EnableInterrupts(uart->uart_base, kLPUART_RxDataRegFullInterruptEnable);

    CLOCK_SetIpSrc(kCLOCK_Lpuart1, kCLOCK_IpSrcFircAsync);

    uint32_t uartClkSrcFreq1 = CLOCK_GetIpFreq(kCLOCK_Lpuart1);
    LPUART_Init(uart->uart_base, &config, uartClkSrcFreq1);
    LPUART_EnableInterrupts(uart->uart_base, kLPUART_RxDataRegFullInterruptEnable);

    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct fsl_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct fsl_uart *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        DisableIRQ(uart->irqn);

        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        EnableIRQ(uart->irqn);
        break;
    }

    return RT_EOK;
}

static int uart_putc(struct rt_serial_device *serial, char c)
{
    struct fsl_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct fsl_uart *)serial->parent.user_data;

    LPUART_WriteByte(uart->uart_base, c);
    while (!(LPUART_GetStatusFlags(uart->uart_base) & kLPUART_TxDataRegEmptyFlag));

    return (1);
}

static int uart_getc(struct rt_serial_device *serial)
{
    int ch;
    struct fsl_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct fsl_uart *)serial->parent.user_data;

    ch = -1;
    if (LPUART_GetStatusFlags(uart->uart_base) & kLPUART_RxDataRegFullFlag)
        ch = LPUART_ReadByte(uart->uart_base);
    return ch;
}

static rt_ssize_t uart_dma_transmit(struct rt_serial_device *serial, rt_uint8_t *buf, rt_size_t size, int direction)
{
    return (0);
}

/* UART ISR */
/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial)
{
    struct fsl_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct fsl_uart *) serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    /* UART in mode Receiver */
    if (LPUART_GetStatusFlags(uart->uart_base) & kLPUART_RxDataRegFullFlag)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }

    /* If RX overrun. */
    if (LPUART_STAT_OR_MASK & uart->uart_base->STAT)
    {
        /* Clear overrun flag, otherwise the RX does not work. */
        uart->uart_base->STAT = ((uart->uart_base->STAT & 0x3FE00000U) | LPUART_STAT_OR_MASK);
    }
}
