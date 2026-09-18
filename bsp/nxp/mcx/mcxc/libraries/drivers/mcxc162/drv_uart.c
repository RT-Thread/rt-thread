/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtdevice.h>

#include "drv_uart.h"
#include "fsl_clock.h"
#include "fsl_lpuart.h"

#if defined(RT_USING_SERIAL) && \
    (defined(BSP_USING_UART0) || defined(BSP_USING_UART1) || defined(BSP_USING_UART2))

struct mcxc162_uart
{
    struct rt_serial_device serial;
    LPUART_Type *base;
    IRQn_Type irqn;
    clock_attach_id_t clock_attach;
    clock_div_name_t clock_div;
    rt_uint8_t instance;
    const char *name;
};

static void mcxc162_uart_isr(struct mcxc162_uart *uart);

#ifdef BSP_USING_UART0
static struct mcxc162_uart uart0 = {
    .base = LPUART0,
    .irqn = LPUART0_IRQn,
    .clock_attach = kFRO_LF_DIV_to_LPUART0,
    .clock_div = kCLOCK_DivLPUART0,
    .instance = 0U,
    .name = "uart0",
};

void LPUART0_IRQHandler(void)
{
    mcxc162_uart_isr(&uart0);
}
#endif

#ifdef BSP_USING_UART1
static struct mcxc162_uart uart1 = {
    .base = LPUART1,
    .irqn = LPUART1_IRQn,
    .clock_attach = kFRO_LF_DIV_to_LPUART1,
    .clock_div = kCLOCK_DivLPUART1,
    .instance = 1U,
    .name = "uart1",
};

void LPUART1_IRQHandler(void)
{
    mcxc162_uart_isr(&uart1);
}
#endif

#ifdef BSP_USING_UART2
static struct mcxc162_uart uart2 = {
    .base = LPUART2,
    .irqn = LPUART2_IRQn,
    .clock_attach = kFRO_LF_DIV_to_LPUART2,
    .clock_div = kCLOCK_DivLPUART2,
    .instance = 2U,
    .name = "uart2",
};

void LPUART2_IRQHandler(void)
{
    mcxc162_uart_isr(&uart2);
}
#endif

static struct mcxc162_uart * const uarts[] = {
#ifdef BSP_USING_UART0
    &uart0,
#endif
#ifdef BSP_USING_UART1
    &uart1,
#endif
#ifdef BSP_USING_UART2
    &uart2,
#endif
};

static rt_err_t mcxc162_uart_configure(struct rt_serial_device *serial,
                                       struct serial_configure *cfg)
{
    struct mcxc162_uart *uart = serial->parent.user_data;
    lpuart_config_t config;

    LPUART_GetDefaultConfig(&config);
    config.baudRate_Bps = cfg->baud_rate;
    config.enableTx = true;
    config.enableRx = true;
    config.isMsb = cfg->bit_order == BIT_ORDER_MSB;

    if (cfg->invert != NRZ_NORMAL || cfg->flowcontrol != RT_SERIAL_FLOWCONTROL_NONE)
    {
        return -RT_EINVAL;
    }

    switch (cfg->data_bits)
    {
    case DATA_BITS_7:
        config.dataBitsCount = kLPUART_SevenDataBits;
        break;
    case DATA_BITS_8:
        config.dataBitsCount = kLPUART_EightDataBits;
        break;
    default:
        return -RT_EINVAL;
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
        return -RT_EINVAL;
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
        return -RT_EINVAL;
    }

    CLOCK_SetClockDiv(uart->clock_div, 1U);
    CLOCK_AttachClk(uart->clock_attach);

    if (LPUART_Init(uart->base, &config,
                    CLOCK_GetLpuartClkFreq(uart->instance)) != kStatus_Success)
    {
        return -RT_ERROR;
    }
    if ((serial->parent.open_flag & RT_DEVICE_FLAG_INT_RX) != 0U)
    {
        LPUART_EnableInterrupts(uart->base, kLPUART_RxDataRegFullInterruptEnable);
        NVIC_ClearPendingIRQ(uart->irqn);
        EnableIRQ(uart->irqn);
    }

    return RT_EOK;
}

static rt_err_t mcxc162_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct mcxc162_uart *uart = serial->parent.user_data;

    (void)arg;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        LPUART_DisableInterrupts(uart->base, kLPUART_RxDataRegFullInterruptEnable);
        DisableIRQ(uart->irqn);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        LPUART_EnableInterrupts(uart->base, kLPUART_RxDataRegFullInterruptEnable);
        EnableIRQ(uart->irqn);
        break;
    default:
        break;
    }

    return RT_EOK;
}

static int mcxc162_uart_putc(struct rt_serial_device *serial, char ch)
{
    struct mcxc162_uart *uart = serial->parent.user_data;

    while ((LPUART_GetStatusFlags(uart->base) & kLPUART_TxDataRegEmptyFlag) == 0U)
    {
    }
    LPUART_WriteByte(uart->base, (uint8_t)ch);

    return 1;
}

static int mcxc162_uart_getc(struct rt_serial_device *serial)
{
    struct mcxc162_uart *uart = serial->parent.user_data;

    if ((LPUART_GetStatusFlags(uart->base) & kLPUART_RxDataRegFullFlag) != 0U)
    {
        return LPUART_ReadByte(uart->base);
    }

    return -1;
}

static void mcxc162_uart_isr(struct mcxc162_uart *uart)
{
    uint32_t status;
    uint32_t errors = kLPUART_RxOverrunFlag | kLPUART_NoiseErrorFlag |
                      kLPUART_FramingErrorFlag | kLPUART_ParityErrorFlag;

    rt_interrupt_enter();

    status = LPUART_GetStatusFlags(uart->base);
    if ((status & kLPUART_RxDataRegFullFlag) != 0U)
    {
        rt_hw_serial_isr(&uart->serial, RT_SERIAL_EVENT_RX_IND);
    }
    if ((status & errors) != 0U)
    {
        LPUART_ClearStatusFlags(uart->base, status & errors);
    }

    rt_interrupt_leave();
}

static const struct rt_uart_ops mcxc162_uart_ops = {
    .configure = mcxc162_uart_configure,
    .control = mcxc162_uart_control,
    .putc = mcxc162_uart_putc,
    .getc = mcxc162_uart_getc,
};

int rt_hw_uart_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    rt_uint32_t i;
    rt_err_t result;

    for (i = 0U; i < sizeof(uarts) / sizeof(uarts[0]); i++)
    {
        uarts[i]->serial.ops = &mcxc162_uart_ops;
        uarts[i]->serial.config = config;
        result = rt_hw_serial_register(&uarts[i]->serial, uarts[i]->name,
                                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                                       uarts[i]);
        if (result != RT_EOK)
        {
            return result;
        }
    }

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif /* RT_USING_SERIAL && BSP_USING_UARTx */
