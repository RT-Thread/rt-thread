/*
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-9-1       DongBowen    first version
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rtthread.h>
#include "rtdevice.h"

#include "board_config.h"

/* hc config class */
struct hc_uart_cfg
{
    const char *name;
    M0P_UART_TypeDef *uart;
    en_sysctrl_peripheral_gate_t uart_periph;
    IRQn_Type irqn;

    en_gpio_port_t rx_port;
    en_gpio_pin_t rx_pin;
    en_gpio_af_t rx_af;

    en_gpio_port_t tx_port;
    en_gpio_pin_t tx_pin;
    en_gpio_af_t tx_af;
};

/* hc uart dirver class */
struct hc_uart
{
    struct hc_uart_cfg *cfg;
    struct rt_serial_device serial_device;
};

#ifdef BSP_USING_UART0
#ifndef UART0_CFG
#define UART0_CFG                                   \
    {                                               \
        .name = "uart0",                            \
        .uart = M0P_UART0,                          \
        .uart_periph = SysctrlPeripheralUart0,      \
        .irqn = UART0_2_IRQn,                       \
        .rx_port = UART0_RX_PORT,                   \
        .rx_pin = UART0_RX_PIN,                     \
        .rx_af = UART0_RX_AF,                       \
        .tx_port = UART0_TX_PORT,                   \
        .tx_pin = UART0_TX_PIN,                     \
        .tx_af = UART0_TX_AF,                       \
    }
#endif /* UART0_CFG */
#endif /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1
#ifndef UART1_CFG
#define UART1_CFG                                   \
    {                                               \
        .name = "uart1",                            \
        .uart = M0P_UART1,                          \
        .uart_periph = SysctrlPeripheralUart1,      \
        .irqn = UART1_3_IRQn,                       \
        .rx_port = UART1_RX_PORT,                   \
        .rx_pin = UART1_RX_PIN,                     \
        .rx_af = UART1_RX_AF,                       \
        .tx_port = UART1_TX_PORT,                   \
        .tx_pin = UART1_TX_PIN,                     \
        .tx_af = UART1_TX_AF,                       \
    }
#endif /* UART1_CFG */
#endif /* BSP_USING_UART1 */

int rt_hw_uart_init(void);

#endif /* __DRV_USART_H__ */
