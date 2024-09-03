/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-25     RT-Thread    First version for MCXC444
 * 2024-09-03     yandld       Updated to support multiple UARTs
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_uart.h"

#include "fsl_lpuart.h"
#include "fsl_port.h"
#include "fsl_clock.h"

#ifdef RT_USING_SERIAL

struct mcxc444_uart
{
    LPUART_Type *uart_base;
    IRQn_Type irqn;
    struct rt_serial_device *serial;
    char *device_name;
};

static void uart_isr(struct rt_serial_device *serial);

#define UART_DEVICE(uart_base, irq_name, device_name) \
    {                                                 \
        uart_base,                                    \
        irq_name,                                     \
        RT_NULL,                                      \
        device_name,                                  \
    }

static const struct mcxc444_uart uarts[] = {
#ifdef BSP_USING_UART0
    UART_DEVICE(LPUART0, LPUART0_IRQn, "uart0"),
#endif
#ifdef BSP_USING_UART1
    UART_DEVICE(LPUART1, LPUART1_IRQn, "uart1"),
#endif

};

#define UART_COUNT (sizeof(uarts) / sizeof(uarts[0]))

static struct rt_serial_device serial_devices[UART_COUNT];

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

    if (uart->uart_base == LPUART0)
    {
        CLOCK_SetLpuart0Clock(0x1U);
    }
    else if (uart->uart_base == LPUART1)
    {
        CLOCK_SetLpuart1Clock(0x1U);
    }

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
    uint32_t status;

    struct mcxc444_uart *uart = (struct mcxc444_uart *)serial->parent.user_data;

    status = LPUART_GetStatusFlags(uart->uart_base);

    if (status & kLPUART_RxDataRegFullFlag)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }

    if (status & kLPUART_RxOverrunFlag)
    {
        LPUART_ClearStatusFlags(uart->uart_base, kLPUART_RxOverrunFlag);
    }
}

static const struct rt_uart_ops mcxc444_uart_ops =
{
    mcxc444_configure,
    mcxc444_control,
    mcxc444_putc,
    mcxc444_getc,
};

#ifdef BSP_USING_UART0
void LPUART0_IRQHandler(void)
{
    uart_isr(&serial_devices[0]);
}
#endif

#ifdef BSP_USING_UART1
void LPUART1_IRQHandler(void)
{
    uart_isr(&serial_devices[1]);
}
#endif

int rt_hw_uart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    for (rt_size_t i = 0; i < UART_COUNT; i++)
    {
        serial_devices[i].ops = &mcxc444_uart_ops;
        serial_devices[i].config = config;

        rt_hw_serial_register(&serial_devices[i], uarts[i].device_name,
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                              (void *)&uarts[i]);
    }

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif /* RT_USING_SERIAL */
