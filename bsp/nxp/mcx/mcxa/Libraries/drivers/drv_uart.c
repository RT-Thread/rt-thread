/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-06     yandld       The first version for MCX
 * 2024-11-11     hywing       add more UART channels
 */
#include <rtdevice.h>
#include "drv_uart.h"
#include "fsl_lpuart.h"

#ifdef RT_USING_SERIAL

struct mcx_uart
{
    struct rt_serial_device     *serial;
    LPUART_Type                 *uart_base;
    IRQn_Type                   irqn;
    clock_name_t                clock_src;
    clock_attach_id_t           clock_attach_id;
    clock_ip_name_t             clock_ip_name;
    clock_div_name_t            clock_div_name;
    char *device_name;
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
#if defined(BSP_USING_UART2)
struct rt_serial_device serial2;

void LPUART2_IRQHandler(void)
{
    uart_isr(&serial2);
}
#endif

static const struct mcx_uart uarts[] =
{
#ifdef BSP_USING_UART0
    {
        &serial0,
        LPUART0,
        LPUART0_IRQn,
        kCLOCK_Fro12M,
        kFRO12M_to_LPUART0,
        kCLOCK_GateLPUART0,
        kCLOCK_DivLPUART0,
        "uart0",
    },
#endif
#ifdef BSP_USING_UART1
    {
        &serial1,
        LPUART1,
        LPUART1_IRQn,
        kCLOCK_Fro12M,
        kFRO12M_to_LPUART1,
        kCLOCK_GateLPUART1,
        kCLOCK_DivLPUART1,
        "uart1",
    },
#endif
#ifdef BSP_USING_UART2
    {
        &serial2,
        LPUART2,
        LPUART2_IRQn,
        kCLOCK_Fro12M,
        kFRO12M_to_LPUART2,
        kCLOCK_GateLPUART2,
        kCLOCK_DivLPUART2,
        "uart2",
    },
#endif
};

static rt_err_t mcx_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct mcx_uart *uart;
    lpuart_config_t config;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = (struct mcx_uart *)serial->parent.user_data;

    CLOCK_SetClockDiv(uart->clock_div_name, 1u);
    CLOCK_AttachClk(uart->clock_attach_id);
    CLOCK_EnableClock(uart->clock_ip_name);

    LPUART_GetDefaultConfig(&config);
    config.baudRate_Bps = cfg->baud_rate;

    switch (cfg->data_bits)
    {
        case DATA_BITS_7:
            config.dataBitsCount = kLPUART_SevenDataBits;
            break;

        default:
            config.dataBitsCount = kLPUART_EightDataBits;
            break;
    }

    config.enableTx     = true;
    config.enableRx     = true;

    LPUART_Init(uart->uart_base, &config, CLOCK_GetFreq(uart->clock_src));

    return RT_EOK;
}

static rt_err_t mcx_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct mcx_uart *uart = (struct mcx_uart *)serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        LPUART_DisableInterrupts(uart->uart_base, kLPUART_RxDataRegFullInterruptEnable);
        DisableIRQ(uart->irqn);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        LPUART_EnableInterrupts(uart->uart_base, kLPUART_RxDataRegFullInterruptEnable);
        EnableIRQ(uart->irqn);
        break;
    }

    return RT_EOK;
}

static int mcx_putc(struct rt_serial_device *serial, char ch)
{
    struct mcx_uart *uart = (struct mcx_uart *)serial->parent.user_data;

    while(!(kLPUART_TxDataRegEmptyFlag & LPUART_GetStatusFlags(uart->uart_base)));
    LPUART_WriteByte(uart->uart_base, ch);

    return 1;
}

static int mcx_getc(struct rt_serial_device *serial)
{
    struct mcx_uart *uart = (struct mcx_uart *)serial->parent.user_data;

    if (kLPUART_RxDataRegFullInterruptEnable & LPUART_GetStatusFlags(uart->uart_base))
    {
        return LPUART_ReadByte(uart->uart_base);
    }
    else
    {
        return -1;
    }
}

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial)
{
    struct mcx_uart *uart;

    RT_ASSERT(serial != RT_NULL);

    uart = (struct mcx_uart *) serial->parent.user_data;
    RT_ASSERT(uart != RT_NULL);

    /* enter interrupt */
    rt_interrupt_enter();

    /* UART in mode Receiver -------------------------------------------------*/
    rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);

    /* leave interrupt */
    rt_interrupt_leave();
}

static const struct rt_uart_ops mcx_uart_ops =
{
    mcx_configure,
    mcx_control,
    mcx_putc,
    mcx_getc,
};

int rt_hw_uart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    int i;

    for (i = 0; i < sizeof(uarts) / sizeof(uarts[0]); i++)
    {
        uarts[i].serial->ops    = &mcx_uart_ops;
        uarts[i].serial->config = config;

        /* register UART device */
        rt_hw_serial_register(uarts[i].serial, uarts[i].device_name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, (void *)&uarts[i]);
    }

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);
#endif /*BSP_USING_SERIAL */
