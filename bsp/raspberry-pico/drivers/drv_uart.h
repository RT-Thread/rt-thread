/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2021-01-28     flybreak       first version
 * 2023-09-26     1ridic         Integrate with RT-Thread driver framework.
 */

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include <rthw.h>
#include <rtthread.h>

#ifdef RT_USING_SERIAL
int rt_hw_uart_init(void);
#endif /* RT_USING_SERIAL */

#endif /* __DRV_UART_H__ */
