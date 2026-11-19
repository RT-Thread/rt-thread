/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-02-20     yeml           the first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

struct pin_irq_map
{
    rt_uint16_t pinbit;
    IRQn_Type irq_port;
};

#define __TAE32_PORT(port)  GPIO##port##_BASE

#define GET_PIN(PORTx,PIN) (rt_base_t)((16 * ( ((rt_base_t)__TAE32_PORT(PORTx) - (rt_base_t)GPIOA_BASE)/(0x1000UL) )) + PIN)

#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */
