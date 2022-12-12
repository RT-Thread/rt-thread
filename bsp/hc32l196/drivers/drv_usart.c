/*
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-9-1       DongBowen    first version
 */

#include "drv_usart.h"
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

#ifdef RT_USING_SERIAL
#ifdef BSP_USING_UART

#if !defined(BSP_USING_UART0) && !defined(BSP_USING_UART1) && !defined(BSP_USING_UART2) && \
    !defined(BSP_USING_UART3)
    #error "Please define at least one BSP_USING_UARTx"
    /* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
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
};

static struct hc_uart_cfg uart_cfg[] =
{
#ifdef BSP_USING_UART0
    UART0_CFG,
#endif
#ifdef BSP_USING_UART1
    UART1_CFG,
#endif
#ifdef BSP_USING_UART2
    UART2_CFG,
#endif
#ifdef BSP_USING_UART3
    UART3_CFG,
#endif
};

static struct hc_uart uart_drv[sizeof(uart_cfg) / sizeof(uart_cfg[0])] = {0};

static rt_err_t _uart_init(struct rt_serial_device *serial_device, struct serial_configure *configure)
{
    stc_gpio_cfg_t stcGpioCfg;
    stc_uart_cfg_t stcCfg;

    struct hc_uart_cfg *cfg;
    RT_ASSERT(serial_device != RT_NULL);
    RT_ASSERT(configure != RT_NULL);
    cfg = serial_device->parent.user_data;

    /* configure rx and tx gpio */
    rt_memset(&stcGpioCfg, 0, sizeof(stcGpioCfg));
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
    stcGpioCfg.enDir = GpioDirOut;
    Gpio_Init(cfg->tx_port, cfg->tx_pin, &stcGpioCfg);
    Gpio_SetAfMode(cfg->tx_port, cfg->tx_pin, cfg->tx_af);
    stcGpioCfg.enDir = GpioDirIn;
    Gpio_Init(cfg->rx_port, cfg->rx_pin, &stcGpioCfg);
    Gpio_SetAfMode(cfg->rx_port, cfg->rx_pin, cfg->rx_af);

    /* configure uart */
    rt_memset(&stcCfg, 0, sizeof(stcCfg));

    Sysctrl_SetPeripheralGate(cfg->uart_periph, TRUE);

    stcCfg.stcBaud.u32Baud = configure->baud_rate;
    stcCfg.stcBaud.enClkDiv = UartMsk8Or16Div;
    stcCfg.stcBaud.u32Pclk = Sysctrl_GetPClkFreq();

    switch (configure->data_bits)
    {
    case DATA_BITS_8:
        break;
    default:
        break;
    }

    switch (configure->stop_bits)
    {
    case STOP_BITS_1:
        stcCfg.enStopBit = UartMsk1bit;
        break;
    case STOP_BITS_2:
        stcCfg.enStopBit = UartMsk2bit;
        break;
    default:
        stcCfg.enStopBit = UartMsk1bit;
        break;
    }

    switch (configure->parity)
    {
    case PARITY_NONE:
        stcCfg.enMmdorCk = UartMskDataOrAddr;
        stcCfg.enRunMode = UartMskMode1;
        break;
    case PARITY_ODD:
        stcCfg.enMmdorCk = UartMskOdd;
        stcCfg.enRunMode = UartMskMode3;
        break;
    case PARITY_EVEN:
        stcCfg.enMmdorCk = UartMskEven;
        stcCfg.enRunMode = UartMskMode3;
        break;
    default:
        stcCfg.enMmdorCk = UartMskDataOrAddr;
        stcCfg.enRunMode = UartMskMode1;
        break;
    }

    Uart_Init(cfg->uart, &stcCfg);

    Uart_ClrStatus(cfg->uart, UartRC);
    Uart_ClrStatus(cfg->uart, UartTC);

    rt_hw_us_delay(2);
    return RT_EOK;
}

static rt_err_t _uart_control(struct rt_serial_device *serial_device, int cmd, void *arg)
{
    struct hc_uart_cfg *cfg;
    RT_ASSERT(serial_device != RT_NULL);
    cfg = serial_device->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        Uart_DisableIrq(cfg->uart, UartRxIrq);
        EnableNvic(cfg->irqn, IrqLevel3, FALSE);
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        Uart_EnableIrq(cfg->uart, UartRxIrq);
        EnableNvic(cfg->irqn, IrqLevel3, TRUE);
        break;
    }
    return RT_EOK;
}

static int _uart_putc(struct rt_serial_device *serial_device, char c)
{
    struct hc_uart_cfg *cfg;
    RT_ASSERT(serial_device != RT_NULL);
    cfg = serial_device->parent.user_data;

    Uart_SendDataPoll(cfg->uart, (uint8_t)c);
    return 1;
}

static int _uart_getc(struct rt_serial_device *serial_device)
{
    int ch;
    struct hc_uart_cfg *cfg;
    RT_ASSERT(serial_device != RT_NULL);
    cfg = serial_device->parent.user_data;

    ch = -1;

    if (Uart_GetStatus(cfg->uart, UartRC))
    {
        Uart_ClrStatus(cfg->uart, UartRC);
        ch = Uart_ReceiveData(cfg->uart);
    }

    return ch;
}

static const struct rt_uart_ops _uart_ops =
{
    .configure = _uart_init,
    .control = _uart_control,
    .putc = _uart_putc,
    .getc = _uart_getc,
    .dma_transmit = RT_NULL
};

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void rt_hw_uart_isr(struct rt_serial_device *serial_device)
{
    struct hc_uart_cfg *cfg;
    uint32_t status;
    RT_ASSERT(serial_device != RT_NULL);

    cfg = serial_device->parent.user_data;
    status = cfg->uart->ISR;

    /* UART in mode Receiver -------------------------------------------------*/
    if (status & (1 << UartFE))
    {
        Uart_ClrStatus(cfg->uart, UartFE);
    }
    if (status & (1 << UartPE))
    {
        Uart_ClrStatus(cfg->uart, UartPE);
    }
    if (status & (1 << UartRC))
    {
        rt_hw_serial_isr(serial_device, RT_SERIAL_EVENT_RX_IND);
    }
}

#if defined(BSP_USING_UART0)
void Uart0_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_hw_uart_isr(&(uart_drv[UART0_INDEX].serial_device));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART0 */

#if defined(BSP_USING_UART1)
void Uart1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_hw_uart_isr(&(uart_drv[UART1_INDEX].serial_device));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
void Uart2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_hw_uart_isr(&(uart_drv[UART2_INDEX].serial_device));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
void Uart3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_hw_uart_isr(&(uart_drv[UART3_INDEX].serial_device));

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART3 */

int rt_hw_uart_init(void)
{
    struct serial_configure cfg = RT_SERIAL_CONFIG_DEFAULT;
    int i = 0;
    rt_err_t result = RT_EOK;

    for (i = 0; i < sizeof(uart_cfg) / sizeof(uart_cfg[0]); i++)
    {
        uart_drv[i].cfg = &uart_cfg[i];
        uart_drv[i].serial_device.ops = &_uart_ops;
        uart_drv[i].serial_device.config = cfg;
        /* register UART device */
        result = rt_hw_serial_register(&uart_drv[i].serial_device, uart_drv[i].cfg->name,
                                       RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, uart_drv[i].cfg);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif /* BSP_USING_UART */
#endif /* RT_USING_SERIAL */
