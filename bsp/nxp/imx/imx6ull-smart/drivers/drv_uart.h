/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-09     Lyons        first version
 */

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

#include "board.h"
#include "drv_common.h"

#ifdef RT_USING_SERIAL

#ifndef HW_UART_BUS_CLOCK
#define HW_UART_BUS_CLOCK                   80000000
#endif

#define RT_SERIAL_CONFIG_115200N81          \
{                                           \
    BAUD_RATE_115200,                       \
    DATA_BITS_8,                            \
    STOP_BITS_1,                            \
    PARITY_NONE,                            \
    BIT_ORDER_LSB,                          \
    NRZ_NORMAL,                             \
    RT_SERIAL_RB_BUFSZ,                     \
    0                                       \
}

struct imx_periph
{
    rt_uint32_t                 paddr;
    rt_uint32_t                 vaddr;
};

struct imx_uart
{
    struct rt_serial_device     parent;

    const char                  *name;
    struct imx_periph           periph;
    rt_uint32_t                 irqno;

    //[0]-tx [1]-rx
    struct imx6ull_iomuxc             gpio[2];

    rt_uint32_t                 flag;
    struct serial_configure     param;
};

#endif //#ifdef RT_USING_SERIAL
#endif //#ifndef __DRV_UART_H__

