/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-01     THEWON       first version for serialX
 */

#include <rtconfig.h>

#ifdef RT_USING_SERIAL

#include <rtdevice.h>
#include "drv_uartX.h"
#include "drv_sys.h"

//#define DRV_DEBUG
#define LOG_TAG             "drv.uart"
// #include <drv_log.h>

#if !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && !defined(BSP_USING_UART3) && \
    !defined(BSP_USING_UART4) && !defined(BSP_USING_UART5) && !defined(BSP_USING_UART6) && \
    !defined(BSP_USING_UART7) && !defined(BSP_USING_UART8) && !defined(BSP_USING_UART9) && \
    !defined(BSP_USING_UARTA)
#error "Please define at least one BSP_USING_UARTx"
/* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

static int nu_uart_flush(struct rt_serial_device *serial);

static void nu_uart_isr(int vector, void *param);

static struct nu_uart nu_uart_arr[] =
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
#ifdef BSP_USING_UARTA
    UARTA_CONFIG,
#endif
};

// for ALL uarts
static void nu_uart_isr(int vector, void *param)
{
    /* Get base address of uart register */
    nu_uart_t serial = (nu_uart_t)param;
    UART_T *uart_base = ((nu_uart_t)serial)->uart_base;

    /* Get interrupt event */
    uint32_t u32IntSts = uart_base->INTSTS;
    uint32_t u32FIFOSts = uart_base->FIFOSTS;

    if (u32IntSts & (UART_INTSTS_RDAINT_Msk | UART_INTSTS_RXTOINT_Msk)) {   // Received Data Available interrupt
        rt_hw_serial_isr(&serial->dev, RT_SERIAL_EVENT_RX_IND);
    }

    if (u32IntSts & UART_INTSTS_THREINT_Msk) {                            // Transmit Holding Register Empty interrupt
        rt_hw_serial_isr(&serial->dev, RT_SERIAL_EVENT_TX_DONE | (16<<8));
    }

    // if (uRegISR & UART_INTSTS_MODEMINT_Msk) {
        // uRegMSR = huart->Instance->MSR;
        // uRegMSR |= UART_MSR_DCTSF_Msk;
        // huart->Instance->MSR = uRegMSR;
    // }

    // if (uRegISR & UART_ISR_BUF_ERR_INT_Msk) {
        // if (uRegFSR & (UART_FSR_TX_OVER_IF_Msk)) {
            // huart->Instance->FSR = UART_FSR_TX_OVER_IF_Msk;
        // }
        // if (uRegFSR & (UART_FSR_RX_OVER_IF_Msk)) {
            // huart->Instance->FSR = UART_FSR_RX_OVER_IF_Msk;
        // }
    // }

    // if (uRegFSR & (UART_FSR_BIF_Msk | UART_FSR_FEF_Msk | UART_FSR_PEF_Msk | UART_FSR_RX_OVER_IF_Msk | UART_FSR_TX_OVER_IF_Msk)) {
        // huart->Instance->FSR = (UART_FSR_BIF_Msk | UART_FSR_FEF_Msk | UART_FSR_PEF_Msk | UART_FSR_RX_OVER_IF_Msk | UART_FSR_TX_OVER_IF_Msk);
    // }
    uart_base->INTSTS = u32IntSts;
    uart_base->FIFOSTS = u32FIFOSts;
}

/**
 * Configure uart port
 */
static rt_err_t nu_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    rt_err_t ret = RT_EOK;
    uint32_t uart_word_len = 0;
    uint32_t uart_stop_bit = 0;
    uint32_t uart_parity = 0;

    /* Get base address of uart register */
    UART_T *uart_base = ((nu_uart_t)serial)->uart_base;

    /* Check baudrate */
    RT_ASSERT(cfg->baud_rate != 0);

    /* Check word len */
    switch (cfg->data_bits) {
    case DATA_BITS_5:
        uart_word_len = UART_WORD_LEN_5;
    break;
    case DATA_BITS_6:
        uart_word_len = UART_WORD_LEN_6;
    break;
    case DATA_BITS_7:
        uart_word_len = UART_WORD_LEN_7;
    break;
    case DATA_BITS_8:
        uart_word_len = UART_WORD_LEN_8;
    break;
    default:
        uart_word_len = UART_WORD_LEN_8;
    break;
    }

    /* Check stop bit */
    switch (cfg->stop_bits) {
    case STOP_BITS_1:
        uart_stop_bit = UART_STOP_BIT_1;
    break;
    case STOP_BITS_2:
        uart_stop_bit = UART_STOP_BIT_2;
    break;
    default:
        uart_stop_bit = UART_STOP_BIT_1;
    break;
    }

    /* Check parity */
    switch (cfg->parity)
    {
    case PARITY_NONE:
        uart_parity = UART_PARITY_NONE;
    break;
    case PARITY_ODD:
        uart_parity = UART_PARITY_ODD;
    break;
    case PARITY_EVEN:
        uart_parity = UART_PARITY_EVEN;
    break;
    default:
        uart_parity = UART_PARITY_NONE;
    break;
    }

    /* Set line configuration. */
    UART_SetLineConfig(uart_base, cfg->baud_rate, uart_word_len, uart_parity, uart_stop_bit);

    return RT_EOK;
}

/**
 * Initialize uart port
 */
static rt_err_t nu_uart_init(struct rt_serial_device *serial)
{
    /* Get base address of uart register */
    UART_T *uart_base = ((nu_uart_t)serial)->uart_base;

//    nu_sys_ip_reset(((nu_uart_t)serial)->rstidx);

    /* Open Uart and set UART Baudrate */
    UART_Open(uart_base, serial->config->baud_rate);

    if (nu_uart_configure(serial, &serial->config) != RT_EOK)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t nu_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    nu_uart_t psNuUart = (nu_uart_t)serial;
    rt_err_t result = RT_EOK;
    rt_uint32_t flag;
    rt_ubase_t ctrl_arg = (rt_ubase_t)arg;

    RT_ASSERT(serial != RT_NULL);

    /* Get base address of uart register */
    UART_T *uart_base = psNuUart->uart_base;

    switch (cmd) {
    case RT_DEVICE_CTRL_OPEN:
        /* Enable interrupt. */
        rt_hw_interrupt_umask(((nu_uart_t)serial)->irqn);
    break;
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable interrupt */
        if (ctrl_arg & RT_DEVICE_FLAG_INT_TX) {
            UART_DISABLE_INT(uart_base, UART_INTEN_THREIEN_Msk);
        }
        if (ctrl_arg & RT_DEVICE_FLAG_INT_RX) {
            flag = UART_INTEN_RDAIEN_Msk | UART_INTEN_RXTOIEN_Msk | UART_INTEN_TOCNTEN_Msk;
            UART_DISABLE_INT(uart_base, flag);
        }

#ifdef RT_SERIAL_USING_DMA
        /* disable DMA */
#endif
    break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable interrupt */
        if (ctrl_arg & RT_DEVICE_FLAG_INT_TX) {
            UART_ENABLE_INT(uart_base, UART_INTEN_THREIEN_Msk);
        }
        if (ctrl_arg & RT_DEVICE_FLAG_INT_RX) {
            flag = UART_INTEN_RDAIEN_Msk | UART_INTEN_RXTOIEN_Msk | UART_INTEN_TOCNTEN_Msk;
            UART_ENABLE_INT(uart_base, flag);
        }
    break;
    case RT_DEVICE_CTRL_CONFIG:
#ifdef RT_SERIAL_USING_DMA
#endif
    break;
    case RT_DEVICE_CTRL_CLOSE:
        /* disable interrupt */
        rt_hw_interrupt_mask(psNuUart->irqn);

        /* Close UART port */
        UART_Close(uart_base);
    break;
    default :
    break;
    }
    return RT_EOK;
}

static int nu_uart_putc(struct rt_serial_device *serial, char c)
{
    UART_T *uart_base;

    RT_ASSERT(serial != RT_NULL);

    /* Get base address of uart register */
    uart_base = ((nu_uart_t)serial)->uart_base;
    /* Waiting if TX-FIFO is full. */
    while (UART_IS_TX_FULL(uart_base));
    /* Put char into TX-FIFO */
    UART_WRITE(uart_base, c);
    return 1;
}

static int nu_uart_getc(struct rt_serial_device *serial)
{
    int ch;
    UART_T *uart_base;

    RT_ASSERT(serial != RT_NULL);

    /* Get base address of uart register */
    uart_base = ((nu_uart_t)serial)->uart_base;

    /* Return failure if RX-FIFO is empty. */
    if (UART_GET_RX_EMPTY(uart_base)) {
        return -1;
    }
    /* Get char from RX-FIFO */
    ch = UART_READ(uart_base);

    return ch;
}

static int nu_uart_flush(struct rt_serial_device *serial)
{
    UART_T *uart_base;

    RT_ASSERT(serial != RT_NULL);

    /* Get base address of uart register */
    uart_base = ((nu_uart_t)serial)->uart_base;
    while(!UART_IS_TX_EMPTY(uart_base)){;}

    return 1;
}

static void nu_start_tx(struct rt_serial_device *serial)
{
    UART_T *uart_base;

    RT_ASSERT(serial != RT_NULL);

    uart_base = ((nu_uart_t)serial)->uart_base;

    /* enable interrupt */
    UART_ENABLE_INT(uart_base, UART_INTEN_THREIEN_Msk);
}

static void nu_stop_tx(struct rt_serial_device *serial)
{
    UART_T *uart_base;

    RT_ASSERT(serial != RT_NULL);

    uart_base = ((nu_uart_t)serial)->uart_base;

    /* disable interrupt */
    UART_DISABLE_INT(uart_base, UART_INTEN_THREIEN_Msk);
}

static void nu_enable_interrupt(struct rt_serial_device *serial)
{
    RT_ASSERT(serial != RT_NULL);

    rt_hw_interrupt_umask(((nu_uart_t)serial)->irqn);
}

static void nu_disable_interrupt(struct rt_serial_device *serial)
{
    RT_ASSERT(serial != RT_NULL);

    rt_hw_interrupt_mask(((nu_uart_t)serial)->irqn);
}

static const struct rt_uart_ops nu_uart_ops =
{
    .init = nu_uart_init,
    .configure = nu_uart_configure,
    .control = nu_uart_control,
    .putc = nu_uart_putc,
    .getc = nu_uart_getc,
    .flush = nu_uart_flush,
    .start_tx = nu_start_tx,
    .stop_tx = nu_stop_tx,
    .enable_interrupt = nu_enable_interrupt,
    .disable_interrupt = nu_disable_interrupt,
};

int rt_hw_uart_init(void)
{
    rt_size_t obj_num = sizeof(nu_uart_arr) / sizeof(struct nu_uart);
    rt_err_t result = 0;
    int i;

    for (i = 0; i < obj_num; i++)
    {
        /* init UART object */
        nu_uart_arr[i].dev.ops    = &nu_uart_ops;

        rt_hw_interrupt_install(nu_uart_arr[i].irqn, nu_uart_isr, &nu_uart_arr[i], nu_uart_arr[i].name);

        nu_sys_ipclk_enable(nu_uart_arr[i].clkidx);

        /* register UART device */
        result = rt_hw_serial_register(&nu_uart_arr[i].dev, nu_uart_arr[i].name,
                                       RT_DEVICE_FLAG_RDWR
                                       | RT_DEVICE_FLAG_INT_RX
                                       | RT_DEVICE_FLAG_INT_TX
                                       , NULL);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#endif /* RT_USING_SERIAL */
