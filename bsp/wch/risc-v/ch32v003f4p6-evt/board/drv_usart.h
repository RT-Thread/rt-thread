/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rtthread.h>

int rt_hw_usart_init(void);
void rt_hw_usart_rx_poll(void);
rt_uint32_t rt_hw_usart_rx_count(void);

#endif
