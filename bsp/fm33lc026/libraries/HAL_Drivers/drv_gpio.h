/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-20     wudiyidashi       first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <drv_common.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

#define __FM33_PORT(port)  GPIO##port##_BASE


#define GET_PIN(PORTx,PIN) (rt_base_t)((16 * ( ((rt_base_t)__FM33_PORT(PORTx) - (rt_base_t)GPIOA_BASE)/(0x0400UL) )) + PIN)


struct pin_irq_map
{
    rt_uint16_t pin;
    rt_uint16_t irqno;
};

int rt_hw_pin_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */

