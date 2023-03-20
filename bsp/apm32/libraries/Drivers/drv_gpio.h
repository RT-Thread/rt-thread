/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-08-20     Abbcc        first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <drv_common.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#define __APM32_PORT(port)  GPIO##port##_BASE

#define GET_PIN(PORTx,PIN) (rt_base_t)((16 * ( ((rt_base_t)__APM32_PORT(PORTx) - (rt_base_t)GPIOA_BASE)/(0x0400UL) )) + PIN)

struct pin_irq_map
{
    rt_uint16_t pinbit;
    IRQn_Type irqno;
};

int rt_hw_pin_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */

