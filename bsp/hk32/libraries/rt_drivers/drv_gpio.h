/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-08-15     Jonas        first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <board.h>
#include <rthw.h>
#include <rtdevice.h>

#define __HK32_PORT(port)  GPIO##port##_BASE

#define GET_PIN(PORTx,PIN) (rt_base_t)((16 * ( ((rt_base_t)__HK32_PORT(PORTx) - (rt_base_t)GPIOA_BASE)/(0x0400UL) )) + PIN)

/* HK32 GPIO driver */

struct pin_irq_map
{
    rt_uint16_t pinbit;
    rt_uint16_t lineno;
    IRQn_Type irqno;
};

int rt_hw_pin_init(void);

#endif /* __DRV_GPIO_H__ */

