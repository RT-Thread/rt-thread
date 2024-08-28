/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-25     RT-Thread    First version for MCXC444
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_uart.h"

#include "fsl_lpuart.h"
#include "fsl_port.h"
#include "fsl_clock.h"

#ifdef RT_USING_SERIAL

/* MCXC444 UART driver */
struct mcxc444_uart
{
    LPUART_Type *uart_base;
    IRQn_Type irqn;
    struct rt_serial_device *serial;
    char *device_name;
};

static void uart_isr(struct rt_serial_device *serial);

#if defined(BSP_USING_UART0)
struct rt_serial_device serial0;

void LPUART0_IRQHandler(void)
{
    uart_isr(&serial0);
}

static const struct mcxc444_uart uart0 =
{
    LPUART0,
    LPUART0_IRQn,
    &serial0,
    "uart0",
};
#endif

static rt_err_t mcxc444_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct mcxc444_uart *uart = (struct mcxc444_uart *)serial->parent.user_data;
    lpuart_config_t config;

    LPUART_GetDefaultConfig(&config);
    config.baudRate_Bps = cfg->baud_rate;
    config.enableTx = true;
    config.enableRx = true;

    switch (cfg->data_bits)
    {
    case DATA_BITS_8:
        config.dataBitsCount = kLPUART_EightDataBits;
        break;
    default:
        return RT_ERROR;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_1:
        config.stopBitCount = kLPUART_OneStopBit;
        break;
    case STOP_BITS_2:
        config.stopBitCount = kLPUART_TwoStopBit;
        break;
    default:
        return RT_ERROR;
    }

    switch (cfg->parity)
    {
    case PARITY_NONE:
        config.parityMode = kLPUART_ParityDisabled;
        break;
    case PARITY_ODD:
        config.parityMode = kLPUART_ParityOdd;
        break;
    case PARITY_EVEN:
        config.parityMode = kLPUART_ParityEven;
        break;
    default:
        return RT_ERROR;
    }

    CLOCK_SetLpuart0Clock(0x1U);
    LPUART_Init(uart->uart_base, &config, CLOCK_GetFreq(kCLOCK_McgIrc48MClk));

    return RT_EOK;
}

static rt_err_t mcxc444_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct mcxc444_uart *uart = (struct mcxc444_uart *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        LPUART_DisableInterrupts(uart->uart_base, kLPUART_RxDataRegFullInterruptEnable);
        DisableIRQ(uart->irqn);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        LPUART_EnableInterrupts(uart->uart_base, kLPUART_RxDataRegFullInterruptEnable);
        EnableIRQ(uart->irqn);
        break;
    }

    return RT_EOK;
}

static int mcxc444_putc(struct rt_serial_device *serial, char ch)
{
    struct mcxc444_uart *uart = (struct mcxc444_uart *)serial->parent.user_data;

    LPUART_WriteByte(uart->uart_base, ch);
    while (!(LPUART_GetStatusFlags(uart->uart_base) & kLPUART_TxDataRegEmptyFlag));

    return 1;
}

static int mcxc444_getc(struct rt_serial_device *serial)
{
    int ch;
    struct mcxc444_uart *uart = (struct mcxc444_uart *)serial->parent.user_data;

    if (LPUART_GetStatusFlags(uart->uart_base) & kLPUART_RxDataRegFullFlag)
    {
        ch = LPUART_ReadByte(uart->uart_base);
        return ch;
    }
    else
    {
        return -1;
    }
}

static void uart_isr(struct rt_serial_device *serial)
{
    struct mcxc444_uart *uart = (struct mcxc444_uart *)serial->parent.user_data;

    rt_interrupt_enter();

    if (LPUART_GetStatusFlags(uart->uart_base) & kLPUART_RxDataRegFullFlag)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }

    rt_interrupt_leave();
}

static const struct rt_uart_ops mcxc444_uart_ops =
{
    mcxc444_configure,
    mcxc444_control,
    mcxc444_putc,
    mcxc444_getc,
};

int rt_hw_uart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef BSP_USING_UART0
    serial0.ops = &mcxc444_uart_ops;
    serial0.config = config;

    rt_hw_serial_register(&serial0, uart0.device_name,
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          (void *)&uart0);
#endif

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif /* RT_USING_SERIAL */
