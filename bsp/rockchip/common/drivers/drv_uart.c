/**
  * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    drv_uart.c
  * @author  Huibin Hong
  * @version V0.5
  * @date    10-Dec-2018
  * @brief   serial driver
  *
  ******************************************************************************
  */

#include <rthw.h>
#include <rtdevice.h>
#include <rtthread.h>

#ifdef RT_USING_UART

#include "hal_base.h"
#include "hal_bsp.h"
#include "drv_uart.h"
#include "drv_clock.h"
#ifdef RK_BSP_TEMP
#include "drv_pm.h"
#endif
#include "board.h"

/****************************************************************************
 * Private Types
 ****************************************************************************/
struct rockchip_uart
{
    const struct uart_board *uart_board;
    /* HAL */
    const struct HAL_UART_DEV *dev;

    /* irq handler */
    rt_isr_handler_t irq_handler;
};

static int rockchip_uart_irq(rt_serial_t *serial);

#define DEFINE_ROCKCHIP_UART(ID)                            \
static void rockchip_uart##ID##_irq(int irq, void *param);  \
static struct rt_serial_device serial##ID;                  \
static struct rockchip_uart rk_uart##ID =                   \
{                                                           \
    .uart_board = &g_uart##ID##_board,                      \
    .dev = &g_uart##ID##Dev,                               \
    .irq_handler = rockchip_uart##ID##_irq,                 \
};                                                          \
static void rockchip_uart##ID##_irq(int irq, void *param)   \
{                                                           \
    rockchip_uart_irq(&serial##ID);                         \
}                                                           \

#if defined(RT_USING_UART0)
DEFINE_ROCKCHIP_UART(0);
#endif /* RT_USING_UART0 */

#if defined(RT_USING_UART1)
DEFINE_ROCKCHIP_UART(1);
#endif /* RT_USING_UART1 */

#if defined(RT_USING_UART2)
DEFINE_ROCKCHIP_UART(2);
#endif /* RT_USING_UART2 */

#if defined(RT_USING_UART3)
DEFINE_ROCKCHIP_UART(3);
#endif /* RT_USING_UART3 */

#if defined(RT_USING_UART4)
DEFINE_ROCKCHIP_UART(4);
#endif /* RT_USING_UART4 */

#if defined(RT_USING_UART5)
DEFINE_ROCKCHIP_UART(5);
#endif /* RT_USING_UART5 */

#if defined(RT_USING_UART6)
DEFINE_ROCKCHIP_UART(6);
#endif /* RT_USING_UART6 */

#if defined(RT_USING_UART7)
DEFINE_ROCKCHIP_UART(7);
#endif /* RT_USING_UART7 */

#if defined(RT_USING_UART8)
DEFINE_ROCKCHIP_UART(8);
#endif /* RT_USING_UART8 */

#if defined(RT_USING_UART9)
DEFINE_ROCKCHIP_UART(9);
#endif /* RT_USING_UART9 */

static struct rockchip_uart *rk_uart_table[] =
{
#if defined(RT_USING_UART0)
    &rk_uart0,
#endif
#if defined(RT_USING_UART1)
    &rk_uart1,
#endif
#if defined(RT_USING_UART2)
    &rk_uart2,
#endif
#if defined(RT_USING_UART3)
    &rk_uart3,
#endif
#if defined(RT_USING_UART4)
    &rk_uart4,
#endif
#if defined(RT_USING_UART5)
    &rk_uart5,
#endif
#if defined(RT_USING_UART6)
    &rk_uart6,
#endif
#if defined(RT_USING_UART7)
    &rk_uart7,
#endif
#if defined(RT_USING_UART8)
    &rk_uart8,
#endif
#if defined(RT_USING_UART9)
    &rk_uart9,
#endif
};

static struct rt_serial_device *rt_serial_table[] =
{
#if defined(RT_USING_UART0)
    &serial0,
#endif
#if defined(RT_USING_UART1)
    &serial1,
#endif
#if defined(RT_USING_UART2)
    &serial2,
#endif
#if defined(RT_USING_UART3)
    &serial3,
#endif
#if defined(RT_USING_UART4)
    &serial4,
#endif
#if defined(RT_USING_UART5)
    &serial5,
#endif
#if defined(RT_USING_UART6)
    &serial6,
#endif
#if defined(RT_USING_UART7)
    &serial7,
#endif
#if defined(RT_USING_UART8)
    &serial8,
#endif
#if defined(RT_USING_UART9)
    &serial9,
#endif
};

static int rockchip_uart_putc(rt_serial_t *serial, char c)
{
    struct rockchip_uart *uart = RT_NULL;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct rockchip_uart *)serial->parent.user_data;

    HAL_UART_SerialOutChar(uart->dev->pReg, c);
    return 1;
}

static int rockchip_uart_getc(rt_serial_t *serial)
{
    rt_uint8_t c = 0;
    int ret = -1;

    struct rockchip_uart *uart = RT_NULL;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct rockchip_uart *)serial->parent.user_data;

    ret = HAL_UART_SerialIn(uart->dev->pReg, &c, 1);

    if (ret <= 0)
    {
        return -1;
    }
    else
    {
        ret = c;
        return ret;
    }
}

int rt_hw_console_channel(void)
{
#if defined(RT_CONSOLE_DEVICE_NAME)
#if defined(RT_USING_UART0)
    if (!strcmp(RT_CONSOLE_DEVICE_NAME, "uart0"))
        return 0;
#endif
#if defined(RT_USING_UART1)
    if (!strcmp(RT_CONSOLE_DEVICE_NAME, "uart1"))
        return 1;
#endif
#if defined(RT_USING_UART2)
    if (!strcmp(RT_CONSOLE_DEVICE_NAME, "uart2"))
        return 2;
#endif
#if defined(RT_USING_UART3)
    if (!strcmp(RT_CONSOLE_DEVICE_NAME, "uart3"))
        return 3;
#endif
#if defined(RT_USING_UART4)
    if (!strcmp(RT_CONSOLE_DEVICE_NAME, "uart4"))
        return 4;
#endif
#if defined(RT_USING_UART5)
    if (!strcmp(RT_CONSOLE_DEVICE_NAME, "uart5"))
        return 5;
#endif
#if defined(RT_USING_UART6)
    if (!strcmp(RT_CONSOLE_DEVICE_NAME, "uart6"))
        return 6;
#endif
#if defined(RT_USING_UART7)
    if (!strcmp(RT_CONSOLE_DEVICE_NAME, "uart7"))
        return 7;
#endif
#if defined(RT_USING_UART8)
    if (!strcmp(RT_CONSOLE_DEVICE_NAME, "uart8"))
        return 8;
#endif
#if defined(RT_USING_UART9)
    if (!strcmp(RT_CONSOLE_DEVICE_NAME, "uart9"))
        return 9;
#endif
#endif

    return -RT_EINVAL;
}

void rt_hw_console_output(const char *str)
{
    struct rockchip_uart *uart = RT_NULL;

#if defined(RT_CONSOLE_DEVICE_NAME)
#if defined(RT_USING_UART0)
    if (!strcmp(RT_CONSOLE_DEVICE_NAME, "uart0"))
        uart = &rk_uart0;
#endif
#if defined(RT_USING_UART1)
    if (!strcmp(RT_CONSOLE_DEVICE_NAME, "uart1"))
        uart = &rk_uart1;
#endif
#if defined(RT_USING_UART2)
    if (!strcmp(RT_CONSOLE_DEVICE_NAME, "uart2"))
        uart = &rk_uart2;
#endif
#if defined(RT_USING_UART3)
    if (!strcmp(RT_CONSOLE_DEVICE_NAME, "uart3"))
        uart = &rk_uart3;
#endif
#if defined(RT_USING_UART4)
    if (!strcmp(RT_CONSOLE_DEVICE_NAME, "uart4"))
        uart = &rk_uart4;
#endif
#if defined(RT_USING_UART5)
    if (!strcmp(RT_CONSOLE_DEVICE_NAME, "uart5"))
        uart = &rk_uart5;
#endif
#if defined(RT_USING_UART6)
    if (!strcmp(RT_CONSOLE_DEVICE_NAME, "uart6"))
        uart = &rk_uart6;
#endif
#if defined(RT_USING_UART7)
    if (!strcmp(RT_CONSOLE_DEVICE_NAME, "uart7"))
        uart = &rk_uart7;
#endif
#if defined(RT_USING_UART8)
    if (!strcmp(RT_CONSOLE_DEVICE_NAME, "uart8"))
        uart = &rk_uart8;
#endif
#if defined(RT_USING_UART9)
    if (!strcmp(RT_CONSOLE_DEVICE_NAME, "uart9"))
        uart = &rk_uart9;
#endif
#endif

    if (!uart)
        return;

    while (*str)
    {
        if (*str == '\n')
            HAL_UART_SerialOutChar(uart->dev->pReg, '\r');

        HAL_UART_SerialOutChar(uart->dev->pReg, *str);
        str++;
    }
}

static rt_err_t rockchip_uart_configure(rt_serial_t *serial, struct serial_configure *cfg)
{
    struct rockchip_uart *uart = RT_NULL;
    struct HAL_UART_CONFIG hal_uart_config;
    const struct HAL_UART_DEV *dev;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct rockchip_uart *)serial->parent.user_data;
    dev = uart->dev;

    if (cfg->stop_bits == STOP_BITS_1)
        hal_uart_config.stopBit = UART_ONE_STOPBIT;
    else if (cfg->stop_bits == STOP_BITS_2)
        hal_uart_config.stopBit = UART_ONE_AND_HALF_OR_TWO_STOPBIT;
    else
        rt_kprintf("STOP_BITS_3 and STOP_BITS_4 are not supported\n");

    if (cfg->parity == PARITY_ODD)
        hal_uart_config.parity = UART_ODD_PARITY;
    else if (cfg->parity == PARITY_EVEN)
        hal_uart_config.parity = UART_EVEN_PARITY;
    else
        hal_uart_config.parity = UART_PARITY_DISABLE;

    hal_uart_config.baudRate = cfg->baud_rate;
    hal_uart_config.dataBit = cfg->data_bits;

    HAL_UART_Init(dev, &hal_uart_config);
#ifdef RK_BSP_TEMP
    if (dev->isAutoFlow && (cfg->flow_ctrl == RT_SERIAL_AUTO_FLOW_ENABLE))
        HAL_UART_EnableAutoFlowControl(dev->pReg);
    else
        HAL_UART_DisableAutoFlowControl(dev->pReg);
#endif
    rt_hw_interrupt_umask(dev->irqNum);

    return RT_EOK;
}

static rt_err_t rockchip_uart_control(rt_serial_t *serial, int cmd, void *arg)
{
    struct rockchip_uart *uart = RT_NULL;
    struct UART_REG *hw_base = RT_NULL;
    const struct HAL_UART_DEV *dev;
    rt_uint32_t flag = (rt_uint32_t)arg;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct rockchip_uart *)serial->parent.user_data;
    hw_base = uart->dev->pReg;
    dev = uart->dev;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        if (flag == RT_DEVICE_FLAG_INT_RX)
            HAL_UART_DisableIrq(hw_base, UART_IER_RDI);
        else if (flag == RT_DEVICE_FLAG_INT_TX)
            HAL_UART_DisableIrq(hw_base, UART_IER_THRI);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        if (flag == RT_DEVICE_FLAG_INT_RX)
            HAL_UART_EnableIrq(hw_base, UART_IER_RDI);
        else if (flag == RT_DEVICE_FLAG_INT_TX)
            HAL_UART_EnableIrq(hw_base, UART_IER_THRI);
        break;
    case RT_DEVICE_CTRL_CONFIG:
        if (flag == RT_DEVICE_FLAG_DMA_RX)
            HAL_UART_EnableIrq(hw_base, UART_IER_RDI);
        break;
#ifdef RK_BSP_TEMP
    case RT_DEVICE_CTRL_HW_OPEN:
        clk_enable_by_id(dev->sclkGateID);
        break;
    case RT_DEVICE_CTRL_HW_CLOSE:
        clk_disable_by_id(dev->sclkGateID);
        break;
#endif
    }

    return RT_EOK;
}

static int rockchip_uart_irq(rt_serial_t *serial)
{
    rt_uint32_t iir = 0;
    struct rockchip_uart *uart = RT_NULL;
    struct UART_REG *hw_base = RT_NULL;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct rockchip_uart *)serial->parent.user_data;
    hw_base = uart->dev->pReg;

    rt_interrupt_enter();

    iir = HAL_UART_GetIrqID(hw_base);

    switch (iir)
    {
    case UART_IIR_RDI:
    case UART_IIR_RX_TIMEOUT:
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
        break;

    case UART_IIR_THRI:
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);
        break;

    default:
        HAL_UART_HandleIrq(hw_base);
        break;
    }

    rt_interrupt_leave();
    return 0;
}

static const struct rt_uart_ops rockchip_uart_ops =
{
    rockchip_uart_configure,
    rockchip_uart_control,
    rockchip_uart_putc,
    rockchip_uart_getc,
};

#ifdef RT_USING_PM

static struct UART_SAVE_CONFIG pUartSave;

static int rockchip_uart_suspend(const struct rt_device *device)
{
    struct rockchip_uart *uart = RT_NULL;
    const struct HAL_UART_DEV *dev;

    RT_ASSERT(device != RT_NULL);
    uart = (struct rockchip_uart *)device->user_data;
    dev = uart->dev;

    rt_hw_interrupt_mask(dev->irqNum);
    HAL_UART_Suspend(dev->pReg, &pUartSave);
    clk_disable_by_id(dev->pclkGateID);
    clk_disable_by_id(dev->sclkGateID);
    return RT_EOK;
}

static void rockchip_uart_resume(const struct rt_device *device)
{
    struct rockchip_uart *uart = RT_NULL;
    const struct HAL_UART_DEV *dev;

    RT_ASSERT(device != RT_NULL);
    uart = (struct rockchip_uart *)device->user_data;
    dev = uart->dev;

    clk_enable_by_id(dev->pclkGateID);
    clk_enable_by_id(dev->sclkGateID);
    HAL_UART_Reset(dev->pReg);
    HAL_UART_Resume(dev->pReg, &pUartSave);
    rt_hw_interrupt_umask(dev->irqNum);
}

static const struct rt_device_pm_ops rockchip_uart_pm_ops =
{
    .suspend = rockchip_uart_suspend,
    .resume = rockchip_uart_resume,
};

int rockchip_rt_hw_uart_pm_register(void)
{
    int i = 0;
    struct rockchip_uart *uart;
    struct rt_serial_device *serial;
    const struct uart_board *uart_board;

    for (i = 0; i < HAL_ARRAY_SIZE(rk_uart_table); i++)
    {
        uart = rk_uart_table[i];
        if (uart)
        {
            rt_bool_t is_console;
            uart_board = uart->uart_board;

#ifdef RT_CONSOLE_DEVICE_NAME
            if (!strcmp(RT_CONSOLE_DEVICE_NAME, uart_board->name))
                is_console = true;
            else
                is_console = false;
#else
            is_console = false;
#endif

            serial = rt_serial_table[i];
            serial->ops = &rockchip_uart_ops;
#ifdef RK_BSP_TEMP
            if (!is_console && !uart_board->en_irq_wake)
                rt_pm_register_device(&serial->parent, &rockchip_uart_pm_ops);
#endif
        }
    }

    return 0;
}
INIT_PREV_EXPORT(rockchip_rt_hw_uart_pm_register);

#endif

void rt_hw_usart_init(void)
{
    int i = 0;
    struct rockchip_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    struct rt_serial_device *serial;
    const struct HAL_UART_DEV *dev;
    const struct uart_board *uart_board;

    for (i = 0; i < HAL_ARRAY_SIZE(rk_uart_table); i++)
    {
        uart = rk_uart_table[i];
        if (uart)
        {
            rt_bool_t is_console;     /* uart is used for console */

            dev = uart->dev;
            uart_board = uart->uart_board;

            if (uart_board->baud_rate)
            {
                config.baud_rate = uart_board->baud_rate;
            }

#ifdef RT_CONSOLE_DEVICE_NAME
            if (!strcmp(RT_CONSOLE_DEVICE_NAME, uart_board->name))
            {
                is_console = true;
            }
            else
            {
                is_console = false;
            }
#else
            is_console = false;
#endif

            config.bufsz = uart_board->bufer_size;
            serial = rt_serial_table[i];
            serial->ops = &rockchip_uart_ops;
            serial->config = config;

            /* enable uart clk here */
            clk_enable_by_id(dev->pclkGateID);
            clk_enable_by_id(dev->sclkGateID);

            if (!is_console)
                HAL_UART_Reset(dev->pReg);

            /* register UARTx device */
            rt_hw_serial_register(serial, uart_board->name,
                                  uart_board->dev_flag, (void *)uart);

            /* enable interrupt */
            rt_hw_interrupt_install(dev->irqNum, uart->irq_handler,
                                    RT_NULL, uart_board->name);
            rt_hw_interrupt_mask(dev->irqNum);
        }
    }
}
#endif
