/*
 * File      : uart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-15     Haley        the first version
 */
 
#include <rtdevice.h>
#include "am_mcu_apollo.h"
#include "board.h"

/* USART0 */
#define AM_UART0_INST         0

#define UART0_GPIO_RX         2
#define UART0_GPIO_CFG_RX     AM_HAL_PIN_2_UART0RX
#define UART0_GPIO_TX         1
#define UART0_GPIO_CFG_TX     AM_HAL_PIN_1_UART0TX

/* USART1 */
#define AM_UART1_INST         1

#define UART1_GPIO_RX         9
#define UART1_GPIO_CFG_RX     AM_HAL_PIN_9_UART1RX
#define UART1_GPIO_TX         8
#define UART1_GPIO_CFG_TX     AM_HAL_PIN_8_UART1TX

/* AM uart driver */
struct am_uart
{
    uint32_t uart_device;
    uint32_t uart_interrupt;
};

/**
 * @brief UART configuration settings
 *
 */
am_hal_uart_config_t g_sUartConfig =
{
    115200, // ui32BaudRate
    AM_HAL_UART_DATA_BITS_8, // ui32DataBits
    false, // bTwoStopBits
    AM_HAL_UART_PARITY_NONE, // ui32Parity
    AM_HAL_UART_FLOW_CTRL_NONE, // ui32FlowCtrl
};

/**
 * @brief Enable the UART
 *
 * @param Uart driver
 *
 * This function is Enable the UART
 *
 * @return None.
 */
static void rt_hw_uart_enable(struct am_uart* uart)
{
    /* Enable the UART clock */
    am_hal_uart_clock_enable(uart->uart_device);

    /* Enable the UART */
    am_hal_uart_enable(uart->uart_device);

#if defined(RT_USING_UART0)
    /* Make sure the UART RX and TX pins are enabled */
    am_hal_gpio_pin_config(UART0_GPIO_TX, UART0_GPIO_CFG_TX);
    am_hal_gpio_pin_config(UART0_GPIO_RX, UART0_GPIO_CFG_RX | AM_HAL_GPIO_PULL12K);
#endif /* RT_USING_UART0 */

#if defined(RT_USING_UART1)
    /* Make sure the UART RX and TX pins are enabled */
    am_hal_gpio_pin_config(UART1_GPIO_TX, UART1_GPIO_CFG_TX);
    am_hal_gpio_pin_config(UART1_GPIO_RX, UART1_GPIO_CFG_RX | AM_HAL_GPIO_PULL12K);
#endif /* RT_USING_UART1 */
}

/**
 * @brief Disable the UART
 *
 * @param Uart driver
 *
 * This function is Disable the UART
 *
 * @return None.
 */
static void rt_hw_uart_disable(struct am_uart* uart)
{
    /* Clear all interrupts before sleeping as having a pending UART interrupt burns power */
    am_hal_uart_int_clear(uart->uart_device, 0xFFFFFFFF);

    /* Disable the UART */
    am_hal_uart_disable(uart->uart_device);

#if defined(RT_USING_UART0)
    /* Disable the UART pins */
    am_hal_gpio_pin_config(UART0_GPIO_TX, AM_HAL_PIN_DISABLE);
    am_hal_gpio_pin_config(UART0_GPIO_RX, AM_HAL_PIN_DISABLE);
#endif /* RT_USING_UART0 */

#if defined(RT_USING_UART1)
    /* Disable the UART pins */
    am_hal_gpio_pin_config(UART1_GPIO_TX, AM_HAL_PIN_DISABLE);
    am_hal_gpio_pin_config(UART1_GPIO_RX, AM_HAL_PIN_DISABLE);
#endif /* RT_USING_UART1 */

    /* Disable the UART clock */
    am_hal_uart_clock_disable(uart->uart_device);
}

/**
 * @brief UART-based string print function.
 *
 * @param Send buff
 *
 * This function is used for printing a string via the UART, which for some
 * MCU devices may be multi-module.
 *
 * @return None.
 */
void rt_hw_uart_send_string(char *pcString)
{
    am_hal_uart_string_transmit_polled(AM_UART0_INST, pcString);

    /* Wait until busy bit clears to make sure UART fully transmitted last byte */
    while ( am_hal_uart_flags_get(AM_UART0_INST) & AM_HAL_UART_FR_BUSY );
}

static rt_err_t am_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct am_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    uart = (struct am_uart *)serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);

    /* Get the configure */
    g_sUartConfig.ui32BaudRate = cfg->baud_rate;
    g_sUartConfig.ui32DataBits = cfg->data_bits;

    if (cfg->stop_bits == STOP_BITS_1)
        g_sUartConfig.bTwoStopBits = false;
    else if (cfg->stop_bits == STOP_BITS_2)
        g_sUartConfig.bTwoStopBits = true;

    g_sUartConfig.ui32Parity = cfg->parity;
    g_sUartConfig.ui32FlowCtrl = AM_HAL_UART_PARITY_NONE;

    /* Configure the UART */
    am_hal_uart_config(uart->uart_device, &g_sUartConfig);

    /* Enable the UART */
    am_hal_uart_enable(uart->uart_device);

    return RT_EOK;
}

static rt_err_t am_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct am_uart* uart;
    //rt_uint32_t ctrl_arg = (rt_uint32_t)(arg);

    RT_ASSERT(serial != RT_NULL);
    uart = (struct am_uart *)serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);

    switch (cmd)
    {
        /* disable interrupt */
        case RT_DEVICE_CTRL_CLR_INT:
            rt_hw_uart_disable(uart);
            break;
        /* enable interrupt */
        case RT_DEVICE_CTRL_SET_INT:
            rt_hw_uart_enable(uart);
            break;
        /* UART config */
        case RT_DEVICE_CTRL_CONFIG :
            break;
    }

    return RT_EOK;
}

static int am_putc(struct rt_serial_device *serial, char c)
{
    struct am_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct am_uart *)serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);

    am_hal_uart_char_transmit_polled(uart->uart_device, c);

    return 1;
}

static int am_getc(struct rt_serial_device *serial)
{
    char c;
    int ch;
    struct am_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct am_uart *)serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);

    ch = -1;
    if ((am_hal_uart_flags_get(uart->uart_device) & AM_HAL_UART_FR_RX_EMPTY) == 0)
    {
        am_hal_uart_char_receive_polled(uart->uart_device, &c);
        ch = c & 0xff;
    }

    return ch;
}

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial)
{
    uint32_t status;
    struct am_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct am_uart *) serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);

    /* Read the interrupt status */
    status = am_hal_uart_int_status_get(uart->uart_device, false);

    //rt_kprintf("status is %d\r\n", status);

    /* Clear the UART interrupt */
    am_hal_uart_int_clear(uart->uart_device, status);

    if (status & (AM_HAL_UART_INT_RX_TMOUT))
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }

    if (status & AM_HAL_UART_INT_RX)
    {
        rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_IND);
    }

    if (status & AM_HAL_UART_INT_TX)
    {
        // rt_hw_serial_isr(serial, RT_SERIAL_EVENT_TX_DONE);
    }
}

static const struct rt_uart_ops am_uart_ops =
{
    am_configure,
    am_control,
    am_putc,
    am_getc,
};

#if defined(RT_USING_UART0)
/* UART0 device driver structure */
struct am_uart uart0 =
{
    AM_UART0_INST,
    AM_HAL_INTERRUPT_UART0
};
static struct rt_serial_device serial0;

void am_uart0_isr(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial0);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* RT_USING_UART0 */

#if defined(RT_USING_UART1)
/* UART1 device driver structure */
struct am_uart uart1 =
{
    AM_UART1_INST,
    AM_HAL_INTERRUPT_UART1
};
static struct rt_serial_device serial1;

void am_uart1_isr(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial1);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* RT_USING_UART1 */

static void GPIO_Configuration(void)
{
#if defined(RT_USING_UART0)
    /* Make sure the UART RX and TX pins are enabled */
    am_hal_gpio_pin_config(UART0_GPIO_TX, UART0_GPIO_CFG_TX);
    am_hal_gpio_pin_config(UART0_GPIO_RX, UART0_GPIO_CFG_RX | AM_HAL_GPIO_PULL12K);
#endif /* RT_USING_UART0 */

#if defined(RT_USING_UART1)
    /* Make sure the UART RX and TX pins are enabled */
    am_hal_gpio_pin_config(UART1_GPIO_TX, UART1_GPIO_CFG_TX);
    am_hal_gpio_pin_config(UART1_GPIO_RX, UART1_GPIO_CFG_RX | AM_HAL_GPIO_PULL12K);
#endif /* RT_USING_UART1 */
}

static void RCC_Configuration(struct am_uart* uart)
{
    /* Power on the selected UART */
    am_hal_uart_pwrctrl_enable(uart->uart_device);

    /* Start the UART interface, apply the desired configuration settings */
    am_hal_uart_clock_enable(uart->uart_device);

    /* Disable the UART before configuring it */
    am_hal_uart_disable(uart->uart_device);

    /* Configure the UART */
    am_hal_uart_config(uart->uart_device, &g_sUartConfig);

    /* Enable the UART */
    am_hal_uart_enable(uart->uart_device);

    /* Enable the UART FIFO */
    am_hal_uart_fifo_config(uart->uart_device, AM_HAL_UART_TX_FIFO_1_2 | AM_HAL_UART_RX_FIFO_1_2);
}

static void NVIC_Configuration(struct am_uart* uart)
{
    /* Enable interrupts */
    am_hal_uart_int_enable(uart->uart_device, AM_HAL_UART_INT_RX_TMOUT | AM_HAL_UART_INT_RX);

    /* Enable the uart interrupt in the NVIC */
    am_hal_interrupt_enable(uart->uart_interrupt);
}

/**
 * @brief Initialize the UART
 *
 * This function initialize the UART
 *
 * @return None.
 */
void rt_hw_uart_init(void)
{
    struct am_uart* uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    GPIO_Configuration();

#if defined(RT_USING_UART0)
    uart = &uart0;
    config.baud_rate = BAUD_RATE_115200;

    RCC_Configuration(uart);
    NVIC_Configuration(uart);

    serial0.ops    = &am_uart_ops;
    serial0.config = config;

    /* register UART1 device */
    rt_hw_serial_register(&serial0, "uart0",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          RT_DEVICE_FLAG_INT_TX, uart);
#endif /* RT_USING_UART0 */

#if defined(RT_USING_UART1)
    uart = &uart1;
    config.baud_rate = BAUD_RATE_115200;

    RCC_Configuration(uart);
    NVIC_Configuration(uart);

    serial1.ops    = &am_uart_ops;
    serial1.config = config;

    /* register UART1 device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          RT_DEVICE_FLAG_INT_TX, uart);
#endif /* RT_USING_UART1 */
}

/*@}*/
