/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rtdevice.h>
#include <board.h>

#if defined(SOC_SERIES_MM32F3277)
#include <drv_common.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define __MM32_PORT(port)  GPIO##port##_BASE
#define GET_PIN(PORTx, PIN) (rt_base_t)((16 * (((rt_base_t)__MM32_PORT(PORTx) - (rt_base_t)GPIOA_BASE) / (0x0400UL))) + PIN)

#if defined(SOC_SERIES_MM32F3277)
struct pin_irq_map
{
    rt_uint16_t pinbit;
    IRQn_Type irqno;
    rt_uint32_t extiline;
    SYSCFG_EXTILine_Type syscfg_extiline;
};
#endif

int rt_hw_pin_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_GPIO_H__ */
