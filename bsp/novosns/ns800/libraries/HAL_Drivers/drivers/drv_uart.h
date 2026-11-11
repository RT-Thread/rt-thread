/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-30     SummerGift   first version
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>

#define UART_CTRL_SET_BLOCK_TIMEOUT     0x20

/* ns800 config class */
struct ns800_uart_config
{
    const char *name;
    UART_TypeDef *Instance;
    IRQn_Type rx_irq_type;
    IRQn_Type tx_irq_type;
    void (*irq_handler)(void);
    GPIO_TypeDef *rx_port;
    GPIO_PinNum rx_pin;
    GPIO_AltFunc rx_mux;
    rt_uint32_t rx_pad;
    GPIO_Direction rx_direction;
    rt_bool_t rx_drive_max;
    GPIO_TypeDef *tx_port;
    GPIO_PinNum tx_pin;
    GPIO_AltFunc tx_mux;
    rt_uint32_t tx_pad;
    GPIO_Direction tx_direction;
    rt_bool_t tx_drive_max;
    rt_uint32_t tx_block_timeout;
    rt_uint16_t rx_bufsz;
    rt_uint16_t tx_bufsz;
};

typedef struct {
    UART_TypeDef *Instance;

    rt_uint32_t baud_rate;

    rt_uint8_t data_bits;
    rt_uint8_t stop_bits;
    rt_uint8_t parity;
    rt_uint8_t bit_order;
    rt_uint8_t invert;
    rt_uint8_t bufsz;
    rt_uint8_t flowcontrol;
    rt_uint8_t reserved;
}UART_HandleTypeDef;

/* ns800 uart dirver class */
struct ns800_uart
{
    UART_HandleTypeDef handle;
    struct ns800_uart_config *config;
    rt_uint32_t DR_mask;
    rt_uint32_t tx_block_timeout;
    struct rt_serial_device serial;
};


int rt_hw_uart_init(void);

#endif  /* __DRV_USART_H__ */

