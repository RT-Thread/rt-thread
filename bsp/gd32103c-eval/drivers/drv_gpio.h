/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-12-27     iysheng           first release
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#define __GD32_PORT(port)  GPIO##port##_BASE

#define GET_PIN(PORTx,PIN) (rt_base_t)((16 * ( ((rt_base_t)__GD32_PORT(PORTx) - (rt_base_t)GPIOA_BASE)/(0x0400UL) )) + PIN)

struct pin_irq_map
{
    rt_uint16_t pinbit;
    IRQn_Type irqno;
};

#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */

