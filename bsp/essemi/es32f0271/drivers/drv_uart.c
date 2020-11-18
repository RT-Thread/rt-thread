/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-10-23     yuzrain       the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_uart.h"
#include "md_gpio.h"
#include "md_uart.h"

#ifdef RT_USING_SERIAL

/* es32 uart driver */
struct es32_uart
{
    UART_TypeDef *huart;
    IRQn_Type irq;
};

static rt_err_t es32f0x_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    struct es32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;

    /* Close TX/RX temporarily  */
    md_uart_disable_lcon_txen(uart->huart);
    md_uart_disable_lcon_rxen(uart->huart);

#ifdef BSP_USING_UART1
    /* Open UART1 clock */
    SET_BIT(RCU->APB2EN, RCU_APB2EN_UART1EN_MSK);

    /* Config UART1 GPIO pin */
    md_gpio_set_pull        (GPIOB, MD_GPIO_PIN_7,   MD_GPIO_PULL_UP);
    md_gpio_set_mode        (GPIOB, MD_GPIO_PIN_6,   MD_GPIO_MODE_FUNCTION);
    md_gpio_set_mode        (GPIOB, MD_GPIO_PIN_7,   MD_GPIO_MODE_FUNCTION);
    md_gpio_set_function0_7 (GPIOB, MD_GPIO_PIN_6,   MD_GPIO_AF2);
    md_gpio_set_function0_7 (GPIOB, MD_GPIO_PIN_7,   MD_GPIO_AF2);
#endif /* uart2 gpio init */

#ifdef BSP_USING_UART2
    /* Open UART2 clock */
    SET_BIT(RCU->APB1EN, RCU_APB1EN_UART2EN_MSK);

    /* Config UART2 GPIO pin */
    md_gpio_set_pull        (GPIOA, MD_GPIO_PIN_3,   MD_GPIO_PULL_UP);
    md_gpio_set_mode        (GPIOA, MD_GPIO_PIN_2,   MD_GPIO_MODE_FUNCTION);
    md_gpio_set_mode        (GPIOA, MD_GPIO_PIN_3,   MD_GPIO_MODE_FUNCTION);
    md_gpio_set_function0_7 (GPIOA, MD_GPIO_PIN_2,   MD_GPIO_AF2);
    md_gpio_set_function0_7 (GPIOA, MD_GPIO_PIN_3,   MD_GPIO_AF2);
#endif /* uart1 gpio init */

#ifdef BSP_USING_UART3
    /* Open UART3 clock */
    SET_BIT(RCU->APB1EN, RCU_APB1EN_UART3EN_MSK);

    /* Config UART3 GPIO pin */
    md_gpio_set_pull        (GPIOC, MD_GPIO_PIN_7,   MD_GPIO_PULL_UP);
    md_gpio_set_mode        (GPIOC, MD_GPIO_PIN_6,   MD_GPIO_MODE_FUNCTION);
    md_gpio_set_mode        (GPIOC, MD_GPIO_PIN_7,   MD_GPIO_MODE_FUNCTION);
    md_gpio_set_function0_7 (GPIOC, MD_GPIO_PIN_6,   MD_GPIO_AF2);
    md_gpio_set_function0_7 (GPIOC, MD_GPIO_PIN_7,   MD_GPIO_AF2);
#endif /* uart3 gpio init */

    if (cfg->bit_order == BIT_ORDER_MSB)
    {
        md_uart_set_lcon_msb(uart->huart, MD_UART_LCON_MSB_FIRST);
    }
    else
    {
        md_uart_set_lcon_msb(uart->huart, MD_UART_LCON_LSB_FIRST);
    }

    if (cfg->invert == NRZ_INVERTED)
    {
        md_uart_enable_lcon_datainv(uart->huart);
    }
    else
    {
        md_uart_disable_lcon_datainv(uart->huart);
    }

    /* Config buadrate */
    md_uart_set_brr(uart->huart, SystemCoreClock/cfg->baud_rate);
    /* Config data width */
    md_uart_set_lcon_dls(uart->huart, 8-cfg->data_bits);
    /* Config stop bits */
    md_uart_set_lcon_stop(uart->huart, cfg->stop_bits);
    /* Config parity */
    if (cfg->parity > PARITY_NONE)
    {
        md_uart_set_lcon_ps(uart->huart, cfg->parity-1);
        md_uart_enable_lcon_pe(uart->huart);
    }
    else
        md_uart_disable_lcon_pe(uart->huart);

    /* enable rx int */
    md_uart_set_fcon_rxth(uart->huart, MD_UART_FCON_RXTH_1);
    md_uart_enable_ier_rfth(uart->huart);
    md_uart_enable_lcon_txen(uart->huart);
    md_uart_enable_lcon_rxen(uart->huart);

    return RT_EOK;
}

static rt_err_t es32f0x_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct es32_uart *uart;
    RT_ASSERT(serial != RT_NULL);

    uart = (struct es32_uart *)serial->parent.user_data;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        NVIC_DisableIRQ(uart->irq);
        /* disable interrupt */
        md_uart_disable_idr_rfth(uart->huart);
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        NVIC_EnableIRQ(uart->irq);
        /* enable interrupt */
        md_uart_enable_ier_rfth(uart->huart);
        break;
    }

    return RT_EOK;
}

static int es32f0x_putc(struct rt_serial_device *serial, char c)
{
    struct es32_uart *uart;
    RT_ASSERT(serial != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;

    while (uart->huart->STAT & UART_STAT_TSBUSY_MSK);
    WRITE_REG(uart->huart->TXBUF, c);

    return 1;
}

static int es32f0x_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    struct es32_uart *uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct es32_uart *)serial->parent.user_data;

    if (uart->huart->STAT & UART_STAT_RFTH_MSK)
    {
        ch = (uint8_t)(uart->huart->RXBUF & 0xFF);
    }

    return ch;
}

static const struct rt_uart_ops es32f0x_uart_ops =
{
    es32f0x_configure,
    es32f0x_control,
    es32f0x_putc,
    es32f0x_getc,
};

#ifdef BSP_USING_UART1
/* UART1 device driver structure */
struct es32_uart uart1 =
{
    UART1,
    UART1_IRQn
};

struct rt_serial_device serial1;

void UART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (md_uart_is_active_flag_rif_rfth(UART1) == 1)
    {
        rt_hw_serial_isr(&serial1, RT_SERIAL_EVENT_RX_IND);
        md_uart_clear_flag_rfth(UART1);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2
/* UART2 device driver structure */
struct es32_uart uart2 =
{
    UART2,
    UART2_IRQn
};

struct rt_serial_device serial2;

void UART2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (md_uart_is_active_flag_rif_rfth(UART2) == 1)
    {
        rt_hw_serial_isr(&serial2, RT_SERIAL_EVENT_RX_IND);
        md_uart_clear_flag_rfth(UART2);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */

#ifdef BSP_USING_UART3
/* UART3 device driver structure */
struct es32_uart uart3 =
{
    UART3,
    UART3_IRQn
};

struct rt_serial_device serial3;

void UART3_AES_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if (md_uart_is_active_flag_rif_rfth(UART3) == 1)
    {
        rt_hw_serial_isr(&serial3, RT_SERIAL_EVENT_RX_IND);
        md_uart_clear_flag_rfth(UART3);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART3 */

int rt_hw_uart_init(void)
{
    struct es32_uart *uart;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

#ifdef BSP_USING_UART1
    uart = &uart1;
    serial1.ops = &es32f0x_uart_ops;
    serial1.config = config;

    /* register UART1 device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2
    uart = &uart2;
    serial2.ops = &es32f0x_uart_ops;
    serial2.config = config;

    /* register UART2 device */
    rt_hw_serial_register(&serial2, "uart2",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART2 */

#ifdef BSP_USING_UART3
    uart = &uart3;
    serial3.ops = &es32f0x_uart_ops;
    serial3.config = config;

    /* register UART3 device */
    rt_hw_serial_register(&serial3, "uart3",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
#endif /* BSP_USING_UART3 */

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_uart_init);

#endif
