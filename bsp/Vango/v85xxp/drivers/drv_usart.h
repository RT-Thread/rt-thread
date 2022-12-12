/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-01-04     iysheng           first version
 * 2021-09-07     FuC               Suit for V85xx
 * 2021-09-12     ZhuXW             Suit for V85xxP
*/

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rthw.h>
#include <rtthread.h>

/* V85XXP uart driver */
struct V85xxP_uart {
    UART_Type * uart_periph;
    IRQn_Type irqn;

    struct rt_serial_device *serial;
    char *device_name;
};

#endif
